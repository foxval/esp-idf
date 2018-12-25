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

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "common/bt_defs.h"
#include "common/bt_trace.h"
#include "osi/alarm.h"
#include "osi/allocator.h"
#include "device/bdaddr.h"
#include "btc/btc_config.h"
#include "btc/btc_util.h"
#include "osi/config.h"
#include "osi/osi.h"
#include "osi/mutex.h"

#include "stack/bt_types.h"
#include "btc/btc_config.h"

const char *btc_key_name[] = {
    "",
    "DEV_CLASS",            /* BTC_CONFIG_DEV_CLASS */
    "PIN_LENGTH",           /* BTC_CONFIG_PIN_LENGTH */
    "LINK_KEY_TYPE",        /* BTC_CONFIG_LINK_KEY_TYPE */
    "LINK_KEY",             /* BTC_CONFIG_LINK_KEY */
    "DEV_TYPE",             /* BTC_CONFIG_DEV_TYPE */
    "ADDR_TYPE",            /* BTC_CONFIG_ADDR_TYPE */
    "LE_KEY_PENC",          /* BTC_CONFIG_LE_KEY_PENC */
    "LE_KEY_PID",           /* BTC_CONFIG_LE_KEY_PID */
    "LE_KEY_PCSRK",         /* BTC_CONFIG_LE_KEY_PCSRK */
    "LE_KEY_LENC",          /* BTC_CONFIG_LE_KEY_LENC */
    "LE_KEY_LID",           /* BTC_CONFIG_LE_KEY_LID */
    "LE_KEY_LCSRK",         /* BTC_CONFIG_LE_KEY_LCSRK */
    "LE_LOCAL_KEY_IR",      /* BTC_CONFIG_LE_LOCAL_KEY_IR */
    "LE_LOCAL_KEY_IRK",     /* BTC_CONFIG_LE_LOCAL_KEY_IRK */
    "LE_LOCAL_KEY_DHK",     /* BTC_CONFIG_LE_LOCAL_KEY_DHK */
    "LE_LOCAL_KEY_ER"       /* BTC_CONFIG_LE_LOCAL_KEY_ER */
};

static const char *CONFIG_FILE_PATH = "bt_config.conf";
static const period_ms_t CONFIG_SETTLE_PERIOD_MS = 3000;

static osi_mutex_t lock;  // protects operations on |config|.
static config_t *config;

// Module lifecycle functions

bool btc_config_init(void)
{
    osi_mutex_new(&lock);
    config = config_new(CONFIG_FILE_PATH);
    if (!config) {
        BTC_TRACE_ERROR("%s unable to allocate a config object.\n", __func__);
        osi_mutex_free(&lock);
        return false;
    }

    return true;
}

bool btc_config_shut_down(void)
{
    btc_config_flush();
    return true;
}

bool btc_config_clean_up(void)
{
    btc_config_flush();

    config_free(config);
    osi_mutex_free(&lock);
    config = NULL;
    return true;
}

bool btc_config_has_section(const char *section)
{
    assert(config != NULL);
    assert(section != NULL);

    return config_has_section(config, section);
}

bool btc_config_exist(const char *section, btc_key_type_t key)
{
    assert(config != NULL);
    assert(section != NULL);

    return config_has_key(config, section, key);
}

bool btc_config_get_int(const char *section, btc_key_type_t key, int *value)
{
    assert(config != NULL);
    assert(section != NULL);
    assert(value != NULL);

    uint16_t length = sizeof(int);
    int val = 0;
    bool ret = config_get(config, section, key, &val, &length);
    if (ret && length == sizeof(int)) {
        *value = val;
        return true;
    }

    return false;
}

bool btc_config_set_int(const char *section, btc_key_type_t key, int value)
{
    assert(config != NULL);
    assert(section != NULL);

    config_set(config, section, key, &value, sizeof(int));

    return true;
}

bool btc_config_get_str(const char *section, btc_key_type_t key, char *value, int *size_bytes)
{
    assert(config != NULL);
    assert(section != NULL);
    assert(value != NULL);
    assert(size_bytes != NULL);

    bool ret = config_get(config, section, key, value, (uint16_t *)size_bytes);

    if (!ret) {
        return false;
    }

    return true;
}

bool btc_config_set_str(const char *section, btc_key_type_t key, const char *value)
{
    assert(config != NULL);
    assert(section != NULL);
    assert(value != NULL);

    config_set(config, section, key, (void *)value, strlen(value));

    return true;
}

bool btc_config_get_bin(const char *section, btc_key_type_t key, uint8_t *value, size_t *length)
{
    assert(config != NULL);
    assert(section != NULL);
    assert(value != NULL);
    assert(length != NULL);

    return config_get(config, section, key, value, (uint16_t *)length);
}

size_t btc_config_get_bin_length(const char *section, btc_key_type_t key)
{
    assert(config != NULL);
    assert(section != NULL);

    uint16_t length = 0;
    config_get(config, section, key, NULL, &length);

    return (size_t)length;
}

bool btc_config_set_bin(const char *section, btc_key_type_t key, const uint8_t *value, size_t length)
{
    assert(config != NULL);
    assert(section != NULL);

    if (length > 0) {
        assert(value != NULL);
    }

    config_set(config, section, key, (void *)value, length);
    return true;
}

const btc_config_section_iter_t *btc_config_section_begin(void)
{
    assert(config != NULL);
    return (const btc_config_section_iter_t *)config_section_begin(config);
}

const btc_config_section_iter_t *btc_config_section_end(void)
{
    assert(config != NULL);
    return (const btc_config_section_iter_t *)config_section_end(config);
}

const btc_config_section_iter_t *btc_config_section_next(const btc_config_section_iter_t *section)
{
    assert(config != NULL);
    assert(section != NULL);
    return (const btc_config_section_iter_t *)config_section_next((const config_section_node_t *)section);
}

const char *btc_config_section_name(const btc_config_section_iter_t *section)
{
    assert(config != NULL);
    assert(section != NULL);
    return config_section_name((const config_section_node_t *)section);
}



bool btc_config_remove(const char *section, btc_key_type_t key)
{
    assert(config != NULL);
    assert(section != NULL);

    return config_remove_key(config, section, key);
}

bool btc_config_remove_section(const char *section)
{
    assert(config != NULL);
    assert(section != NULL);

    return config_remove_section(config, section);
}

void btc_config_flush(void)
{
    assert(config != NULL);

    config_save(config);
}

void btc_config_clear(void)
{
    assert(config != NULL);

    config_clear(config);
}

void btc_config_lock(void)
{
    osi_mutex_lock(&lock, OSI_MUTEX_MAX_TIMEOUT);
}

void btc_config_unlock(void)
{
    osi_mutex_unlock(&lock);
}

static void btc_config_show_section(const char *sec_name) {
    btc_key_type_t key;
    int value_int;
    uint8_t value[BTC_CONFIG_FILE_MAX_SIZE];
    size_t length = BTC_CONFIG_FILE_MAX_SIZE;

    printf("[%s]\n", sec_name);
    for (key = BTC_CONFIG_DEV_CLASS; key <= BTC_CONFIG_LE_LOCAL_KEY_ER; key++) {
        if (btc_config_exist(sec_name, key)) {
            if (key == BTC_CONFIG_PIN_LENGTH ||
                key == BTC_CONFIG_LINK_KEY_TYPE ||
                key == BTC_CONFIG_DEV_TYPE ||
                key == BTC_CONFIG_ADDR_TYPE) {
                btc_config_get_int(sec_name, key, &value_int);
                printf("%s = ", btc_key_name[key]);
                printf("%d\n", value_int);
            } else {
                length = BTC_CONFIG_FILE_MAX_SIZE;
                btc_config_get_bin(sec_name, key, value, &length);
                printf("%s = ", btc_key_name[key]);
                for (int i = 0; i < length; ++i) {
                    printf("%02x", value[i]);
                }
                printf("\n");
            }
        }
    }
    printf("\n");
}

/**
 * This function is used for debug. It print all message in config.
 * Extern then call it when you needed.
 */
void btc_config_show(void)
{
    assert(config != NULL);

    const btc_config_section_iter_t *sec;
    const char *sec_name;

    printf("\n----------------------------\n");
    for (sec = btc_config_section_begin(); sec != btc_config_section_end(); sec = btc_config_section_next(sec)) {
        sec_name = btc_config_section_name(sec);
        btc_config_show_section(sec_name);
    }
    printf("----------------------------\n\n");
}

static inline bool ets_isxdigit(char c)
{
    if ((c >= '0') && (c <= '9')) {
        return true;
    }
    if ((c >= 'a') && (c <= 'f')) {
        return true;
    }
    return ((c >= 'A') && (c <= 'F'));
}

const char *bdaddr_to_section_name(const bt_bdaddr_t *addr, char *string, size_t size)
{
    assert(addr != NULL);
    assert(string != NULL);

    if (size < 18) {
        return NULL;
    }

    const uint8_t *ptr = addr->address;
    sprintf(string, "%02x%02x%02x%02x%02x%02x",
            ptr[0], ptr[1], ptr[2],
            ptr[3], ptr[4], ptr[5]);
    return string;
}

bool section_name_is_bdaddr(const char *string)
{
    assert(string != NULL);

    size_t len = strlen(string);
    if (len != 12) {
        return false;
    }

    for (size_t i = 0; i < len; ++i) {
        // All chars must be a hex digit.
        if (!ets_isxdigit(string[i])) {
            return false;
        }
    }

    return true;
}

bool section_name_to_bdaddr(const char *string, bt_bdaddr_t *addr)
{
    assert(string != NULL);
    assert(addr != NULL);

    bt_bdaddr_t new_addr;
    uint8_t *ptr = new_addr.address;
    uint32_t ptr_32[6];
    bool ret  = sscanf(string, "%02x%02x%02x%02x%02x%02x",
                      &ptr_32[0], &ptr_32[1], &ptr_32[2], &ptr_32[3], &ptr_32[4], &ptr_32[5]) == 6;
    if (ret) {
        for (uint8_t i = 0; i < 6; i++){
            ptr[i] = (uint8_t) ptr_32[i];
        }
        memcpy(addr, &new_addr, sizeof(bt_bdaddr_t));
    }

    return ret;
}