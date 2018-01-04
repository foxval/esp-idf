// Copyright 2016-2017 Espressif Systems (Shanghai) PTE LTD
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

#ifndef __ESP_MESH_INTERNAL_H__
#define __ESP_MESH_INTERNAL_H__

#include "esp_err.h"
#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include "esp_wifi_internal.h"
#include "esp_wifi_crypto_types.h"

/*******************************************************
 *                Constants
 *******************************************************/

/*******************************************************
 *                Structures
 *******************************************************/
typedef struct {
    int scan;
    int vote;
    int fail;
    int monitor_ie;
} mesh_attempts_t;


typedef struct {
    const mesh_crypto_funcs_t *crypto_funcs;
} mesh_crypto_config_t;

extern const mesh_crypto_funcs_t g_wifi_default_mesh_crypto_funcs;

/*******************************************************
 *                Function Definitions
 *******************************************************/
/**
 * @brief     set mesh AP beacon interval(not implemented yet)
 *
 * @param     interval  beacon interval(ms)
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_set_beacon_interval(int interval_ms);

/**
 * @brief     get mesh AP beacon interval
 *
 * @param     void
 *
 * @return    beacon interval(ms)
 *
 */
esp_err_t esp_mesh_get_beacon_interval(int *interval_ms);

/**
 * @brief    set attempts for mesh self-organized networking
 *
 * @param    attempts
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_set_attempts(mesh_attempts_t *attempts);

/**
 * @brief    get attempts for mesh self-organized networking
 *
 * @param    attempts
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_get_attempts(mesh_attempts_t *attempts);

/**
 * @brief     set rssi threshold
 *
 * @param     rssi  rssi threshold
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_set_rssi_threshold(int rssi);

/**
 * @brief     get rssi threshold
 *
 * @param     void
 *
 * @return    rssi threshold
 */
int esp_mesh_get_rssi_threshold(void);

typedef struct {
    int duration_ms; /* parent monitor duration */
    int cnx_rssi; /* threshold for keeping a good connection */
    int select_rssi; /* threshold for parent selection, should be a value greater than switch_rssi*/
    int switch_rssi; /* threshold for action to reselect a better parent */
    int backoff_rssi; /* threshold for connecting to the root */
} mesh_switch_parent_t;

/**
 * @brief     set parameters for parent switch
 *
 * @param     paras
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_set_switch_parent_paras(mesh_switch_parent_t *paras);

/**
 * @brief     get parameters for parent switch
 *
 * @param     paras
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_get_switch_parent_paras(mesh_switch_parent_t *paras);

/**
 * @brief     set queue size(must be called before esp_mesh_start())
 *
 * @param     qsize default:72(min:36, max:105)
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_set_xon_qsize(int qsize);

/**
 * @brief     get queue size
 *
 * @param     qsize
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
int esp_mesh_get_xon_qsize(void);

/**
 * @brief     print the number of txQ waiting
 *
 * @param     void
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_print_txQ_waiting(void);

/**
 * @brief     print the number of rxQ waiting
 *
 * @param     void
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_print_rxQ_waiting(void);


#endif /* __ESP_MESH_INTERNAL_H__ */
