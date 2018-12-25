// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#define LOG_TAG "bt_osi_config"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "osi/config.h"
#include "common/bt_trace.h"
#include "osi/allocator.h"

// The default section name for config
#define CONFIG_DEFAULT_SECTION "Global"

static void config_parse(config_t *config);
static const char* TAG = "config";

/*********************************************************************
 * APIs of section                                                   *
 *********************************************************************/
static section_node_t *section_node_find(const config_t *config, const char *section_name);
static void section_node_free(void *ptr);

static section_t *section_new(void);
static void section_free(section_t *section);
static section_t *section_get(const config_t *config, const char *name);
static bool section_set(const config_t *config, const char *name, section_t *section);

/*********************************************************************
 * APIs of entry                                                     *
 *********************************************************************/
static entry_t *entry_new(section_t *section, config_type_t config_type, uint8_t *value, uint16_t length);
static bool entry_free(section_t *section, entry_t *entry);
static entry_t *entry_get(section_t *section, config_type_t config_type);
static entry_t *entry_set(section_t *section, config_type_t config_type, uint8_t *value, uint16_t length);

static config_t *config_new_empty(void)
{
    config_t *config = malloc(sizeof(config_t));
    if (!config) {
        ESP_LOGE(TAG, "%s unable to allocate memory for config_t.", __func__);
        goto error;
    }

    config->sections = list_new(section_node_free);
    if (!config->sections) {
        ESP_LOGE(TAG, "%s unable to allocate list for sections.", __func__);
        goto error;
    }

    return config;

error:;
    config_free(config);
    return NULL;
}

config_t *config_new(const char *filename)
{
    assert(filename != NULL);

    config_t *config = config_new_empty();
    if (!config) {
        return NULL;
    }

    config->name = osi_strdup(filename);
    config_parse(config);

    return config;
}

void config_free(config_t *config)
{
    if (!config) {
        return;
    }

    list_free(config->sections);
    free(config->name);
    free(config);
}

void config_clear(config_t *config)
{
    if (!config) {
        return;
    }

    nvs_handle fp;
    esp_err_t err = nvs_open(config->name, NVS_READWRITE, &fp);
    if (err != ESP_OK) {
        // Never run to here.
        ESP_LOGE(TAG, "ERROR: Open nvs failed");
        nvs_close(fp);
        return false;
    }

    nvs_erase_all(fp);
    nvs_close(fp);

    list_clear(config->sections);
}

bool config_has_section(const config_t *config, const char *section_name)
{
    assert(config != NULL);
    assert(section_name != NULL);

    return (section_node_find(config, section_name) != NULL);
}

bool config_has_key(const config_t *config, const char *section_name, config_type_t key)
{
    assert(config != NULL);
    assert(section_name != NULL);

    section_node_t *sec = section_node_find(config, section_name);
    if (sec == NULL) {
        return false;
    }
    if (sec->bit_mask & (1 << key)) {
        return true;
    }
    return false;
}

bool config_get(const config_t *config, const char *section_name, const config_type_t key, void *value,  uint16_t *length)
{
    assert(config != NULL);
    assert(section_name != NULL);

    if (!config_has_key(config, section_name, key)) {
        *length = 0;
        return false;
    }

    section_t *section = section_get(config, section_name);
    if (section == NULL) {
        *length = 0;
        return false;
    }
    entry_t *entry = entry_get(section, key);
    if (entry == NULL) {
        *length = 0;
        return false;
    }
    if (*length == 0 || entry->length > *length) {
        // Buf for value is not long enough
        *length = entry->length;
        return false;
    }

    *length = entry->length;
    memcpy(value, entry->value, entry->length);

    section_free(section);
    return true;
}

void config_set(config_t *config, const char *section_name, const config_type_t key, void *value, uint16_t length)
{
    assert(config != NULL);
    assert(section_name != NULL);
    assert(key != CONFIG_SECTONS);

    section_t *section;
    section_node_t *sec = section_node_find(config, section_name);
    if (!sec) {
        size_t len = strlen(section_name);
        if (len > 15){
            ESP_LOGE(TAG, "ERROR: name is too long.");
            return;
        }

        sec = malloc(sizeof(section_node_t));
        sec->name = osi_strdup(section_name);
        sec->bit_mask = 0;
        list_append(config->sections, sec);

        section = section_new();
    } else {
        section = section_get(config, section_name);
    }

    if(section == NULL) {
        ESP_LOGE(TAG, "ERROR: %s failed.", __func__);
        return;
    }

    sec->bit_mask |= (1 << key);
    entry_set(section, key, value, length);
    section_set(config, section_name, section);
    section_free(section);
}

bool config_remove_section(config_t *config, const char *section_name)
{
    assert(config != NULL);
    assert(section_name != NULL);

    section_node_t *sec = section_node_find(config, section_name);
    if (!sec) {
        return false;
    }

    section_set(config, section_name, NULL);

    list_remove(config->sections, sec);
    return true;
}

bool config_remove_key(config_t *config, const char *section_name, const config_type_t key)
{
    assert(config != NULL);
    assert(section_name != NULL);
    assert(key != CONFIG_SECTONS);

    if (!config_has_key(config, section_name, key)) {
        return false;
    }

    section_node_t *sec = section_node_find(config, section_name);
    if (sec == NULL) {
        return false;
    }
    if (sec->bit_mask == (1 << key)) {
        // only have one entry in section, remove it.
        return config_remove_section(config, section_name);
    }

    section_t *section = section_get(config, section_name);
    if (section ==NULL) {
        return false;
    }

    sec->bit_mask &= ~(1 << key);
    entry_t *entry = entry_get(section, key);
    entry_free(section, entry);

    section_set(config, section_name, section);
    section_free(section);
    return true;
}

const config_section_node_t *config_section_begin(const config_t *config)
{
    assert(config != NULL);
    return (const config_section_node_t *)list_begin(config->sections);
}

const config_section_node_t *config_section_end(const config_t *config)
{
    assert(config != NULL);
    return (const config_section_node_t *)list_end(config->sections);
}

const config_section_node_t *config_section_next(const config_section_node_t *node)
{
    assert(node != NULL);
    return (const config_section_node_t *)list_next((const list_node_t *)node);
}

const char *config_section_name(const config_section_node_t *node)
{
    assert(node != NULL);
    const list_node_t *lnode = (const list_node_t *)node;
    const section_node_t *sec = (const section_node_t *)list_node(lnode);
    return sec->name;
}

bool config_save(const config_t *config)
{
    assert(config != NULL);
    assert(config->name != NULL);
    assert(*(config->name) != '\0');

    section_t *section = section_new();
    if (section == NULL) {
        return false;
    }

    uint8_t entry_value[25 + 4];
    uint8_t *p;
    uint8_t entry_length = 0;

    for (const list_node_t *node = list_begin(config->sections); node != list_end(config->sections); node = list_next(node)) {
        p = entry_value;
        entry_length = 0;
        section_node_t *sec = list_node(node);
        memcpy(p, sec->name, strlen(sec->name));
        p += strlen(sec->name);
        entry_length += strlen(sec->name);
        *p = 0;
        p ++;
        entry_length ++;
        memcpy(p, &(sec->bit_mask), sizeof(config_mask_t));
        entry_length += sizeof(config_mask_t);
        entry_set(section, CONFIG_SECTONS, entry_value, entry_length);
    }

    section_set(config, CONFIG_DEFAULT_SECTION, section);
    section_free(section);

    return true;
}

static void config_parse(config_t *config)
{
    assert(config != NULL);
    assert(config->name != NULL);
    assert(*(config->name) != '\0');

    section_t *section = section_get(config, CONFIG_DEFAULT_SECTION);
    if (section == NULL || !(section->bit_mask & CONFIG_SECTONS_MASK)) {
        return;
    }

    config_mask_t *p;
    section_node_t *sec;
    entry_t *entry = entry_get(section, CONFIG_SECTONS);
    while (entry) {
        sec = malloc(sizeof(section_node_t));
        sec->name = osi_strdup((const char*)entry->value);
        p = (config_mask_t *)(entry->value + entry->length - sizeof(config_mask_t));
        sec->bit_mask = *p;
        list_append(config->sections, sec);

        entry_free(section, entry);
        entry = entry_get(section, CONFIG_SECTONS);
    }

    section_free(section);
}

/*********************************************************************
 * APIs of section                                                   *
 *********************************************************************/
static section_node_t *section_node_find(const config_t *config, const char *section_name)
{
    for (const list_node_t *node = list_begin(config->sections); node != list_end(config->sections); node = list_next(node)) {
        section_node_t *sec = list_node(node);
        if (!strcmp(sec->name, section_name)) {
            return sec;
        }
    }

    return NULL;
}

static void section_node_free(void *ptr)
{
    section_node_t *sec = ptr;
    free(sec->name);
    free(sec);
}

static section_t *section_new()
{
    section_t *section = malloc(CONFIG_FILE_MAX_SIZE);
    if (!section) {
        ESP_LOGE(TAG, "ERROR: Malloc failed.");
        return NULL;
    }
    section->bit_mask = 0;
    section->length = 0;

    return section;
}

static void section_free(section_t *section)
{
    if (!section) {
        return;
    }
    free(section);
}

static section_t *section_get(const config_t *config, const char *section_name)
{
    nvs_handle fp;
    esp_err_t err = nvs_open(config->name, NVS_READONLY, &fp);
    if (err != ESP_OK) {
        return NULL;
    }

    section_t *section = section_new();
    size_t length = CONFIG_FILE_MAX_SIZE;
    err = nvs_get_blob(fp, section_name, section, &length);
    if (err != ESP_OK) {
        // Never run to here.
        ESP_LOGE(TAG, "ERROR: nvs_get_blob failed.");
        section_free(section);
        nvs_close(fp);
        return NULL;
    }

    if (length != section->length + sizeof(section_t)) {
        // Never run to here.
        ESP_LOGE(TAG, "ERROR: nvs_get_blob return an error length.");
        section_free(section);
        nvs_close(fp);
        return NULL;
    }

    nvs_close(fp);
    return section;
}

static bool section_set(const config_t *config, const char *section_name, section_t *section)
{
    nvs_handle fp;
    esp_err_t err = nvs_open(config->name, NVS_READWRITE, &fp);
    if (err != ESP_OK) {
        // Never run to here.
        ESP_LOGE(TAG, "ERROR: Open nvs failed");
        nvs_close(fp);
        return false;
    }

    if (section == NULL) {
        nvs_erase_key(fp, section_name);
        return true;
    }

    err = nvs_set_blob(fp, section_name, section, section->length + sizeof(section_t));
    if (err != ESP_OK) {
        // Never run to here.
        ESP_LOGE(TAG, "ERROR: nvs_set_blob failed.");
        nvs_close(fp);
        return false;
    }

    nvs_close(fp);
    return true;
}

/****************************** ***************************************
 * APIs of entry                                                     *
 *********************************************************************/

static entry_t *entry_new(section_t *section, config_type_t config_type, uint8_t *value, uint16_t length)
{
    uint16_t length_new = section->length + sizeof(entry_t) + length;
    if ((length_new + sizeof(section)) > CONFIG_FILE_MAX_SIZE) {
        ESP_LOGE(TAG, "ERROR: section full. (current/max) section size: (%d/%d)", (int16_t)(section->length + sizeof(section)), length_new);
        return NULL;
    }

    entry_t *entry = (entry_t *)(section->value + section->length);
    section->length = length_new;
    section->bit_mask |= (1 << config_type);

    entry->config_type = config_type;
    entry->length = length;
    memcpy(entry->value, value, length);
    return entry;
}

static bool entry_free(section_t *section, entry_t *entry)
{
    void *entry_end = (uint8_t *)(entry->value + entry->length);
    void *section_end = (uint8_t *)(section->value + section->length);
    if (((void *)entry < (void *)(section->value))
        || (entry_end > section_end)) {
        ESP_LOGE(TAG, "ERROR: The entry is not in the section.");
        return false;
    }

    uint16_t entry_length = entry->length  + sizeof(entry_t);
    config_type_t entry_type = entry->config_type;

    uint32_t move_length = (uint32_t)(section_end - entry_end);
    memmove(entry, entry_end, move_length);

    section->length -= entry_length;

    if(entry_type == CONFIG_SECTONS && entry_get(section, entry_type) != NULL) {
        return true;
    }
    section->bit_mask &= ~(1 << entry_type);
    return true;
}

static entry_t *entry_get(section_t *section, config_type_t config_type)
{
    if (!(section->bit_mask & (1 << config_type))) {
        return NULL;
    }

    entry_t *entry;
    void *p = (void *)section->value;
    void *secton_end = section->value + section->length;
    while (p < secton_end) {
        entry = (entry_t *)p;
        if(entry->config_type == config_type) {
            return entry;
        }
        p += (sizeof(entry_t) + entry->length);
    }

    section->bit_mask &= ~(1 << config_type);
    return NULL;
}

static entry_t *entry_set(section_t *section, config_type_t config_type, uint8_t *value, uint16_t length)
{
    if (config_type == CONFIG_SECTONS) {
        return entry_new(section, config_type, value, length);
    }

    entry_t *entry = entry_get(section, config_type);
    if (entry != NULL) {
        entry_free(section, entry);
    }

    return entry_new(section, config_type, value, length);
}