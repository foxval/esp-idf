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

#ifndef __BTC_CONFIG_H__
#define __BTC_CONFIG_H__

#include <stdbool.h>
#include <stddef.h>

#include "stack/bt_types.h"

#define BTC_CONFIG_FILE_MAX_SIZE    CONFIG_FILE_MAX_SIZE

/**
 * Bit mask
 */
#define BTC_CONFIG_DEV_CLASS                1
#define BTC_CONFIG_PIN_LENGTH               2
#define BTC_CONFIG_LINK_KEY_TYPE            3
#define BTC_CONFIG_LINK_KEY                 4

#define BTC_CONFIG_DEV_TYPE                 5
#define BTC_CONFIG_ADDR_TYPE                6
#define BTC_CONFIG_LE_KEY_PENC              7
#define BTC_CONFIG_LE_KEY_PID               8
#define BTC_CONFIG_LE_KEY_PCSRK             9
#define BTC_CONFIG_LE_KEY_LENC              10
#define BTC_CONFIG_LE_KEY_LID               11
#define BTC_CONFIG_LE_KEY_LCSRK             12

#define BTC_CONFIG_LE_LOCAL_KEY_IR          13
#define BTC_CONFIG_LE_LOCAL_KEY_IRK         14
#define BTC_CONFIG_LE_LOCAL_KEY_DHK         15
#define BTC_CONFIG_LE_LOCAL_KEY_ER          16
typedef uint8_t btc_key_type_t;

typedef struct btc_config_section_iter_t btc_config_section_iter_t;

bool btc_config_init(void);
bool btc_config_shut_down(void);
bool btc_config_clean_up(void);

bool btc_config_has_section(const char *section);
bool btc_config_exist(const char *section, btc_key_type_t key);
bool btc_config_get_int(const char *section, btc_key_type_t key, int *value);
bool btc_config_set_int(const char *section, btc_key_type_t key, int value);
bool btc_config_get_str(const char *section, btc_key_type_t key, char *value, int *size_bytes);
bool btc_config_set_str(const char *section, btc_key_type_t key, const char *value);
bool btc_config_get_bin(const char *section, btc_key_type_t key, uint8_t *value, size_t *length);
bool btc_config_set_bin(const char *section, btc_key_type_t key, const uint8_t *value, size_t length);
bool btc_config_remove(const char *section, btc_key_type_t key);
bool btc_config_remove_section(const char *section);

size_t btc_config_get_bin_length(const char *section, btc_key_type_t key);

const btc_config_section_iter_t *btc_config_section_begin(void);
const btc_config_section_iter_t *btc_config_section_end(void);
const btc_config_section_iter_t *btc_config_section_next(const btc_config_section_iter_t *section);
const char *btc_config_section_name(const btc_config_section_iter_t *section);

void btc_config_flush(void);
void btc_config_clear(void);

void btc_config_lock(void);
void btc_config_unlock(void);


const char *bdaddr_to_section_name(const bt_bdaddr_t *addr, char *string, size_t size);
bool section_name_is_bdaddr(const char *string);
bool section_name_to_bdaddr(const char *string, bt_bdaddr_t *addr);
#endif
