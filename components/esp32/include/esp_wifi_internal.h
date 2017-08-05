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

/*
 * All the APIs declared here are internal only APIs, it can only be used by 
 * espressif internal modules, such as SSC, LWIP, TCPIP adapter etc, espressif 
 * customers are not recommended to use them.
 *
 * If someone really want to use specified APIs declared in here, please contact
 * espressif AE/developer to make sure you know the limitations or risk of 
 * the API, otherwise you may get unexpected behavior!!!
 *
 */


#ifndef __ESP_WIFI_INTERNAL_H__
#define __ESP_WIFI_INTERNAL_H__

#include <stdint.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "rom/queue.h"
#include "esp_err.h"
#include "esp_wifi_types.h"
#include "esp_event.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  get whether the wifi driver is allowed to transmit data or not
  *
  * @return
  *     - true  : upper layer should stop to transmit data to wifi driver
  *     - false : upper layer can transmit data to wifi driver
  */
bool esp_wifi_internal_tx_is_stop(void);

/**
  * @brief  free the rx buffer which allocated by wifi driver
  *
  * @param  void* buffer: rx buffer pointer
  */
void esp_wifi_internal_free_rx_buffer(void* buffer);

/**
  * @brief  transmit the buffer via wifi driver
  *
  * @param  wifi_interface_t wifi_if : wifi interface id
  * @param  void *buffer : the buffer to be tansmit
  * @param  u16_t len : the length of buffer
  *
  * @return
  *    - ERR_OK  : Successfully transmit the buffer to wifi driver
  *    - ERR_MEM : Out of memory
  *    - ERR_IF : WiFi driver error
  *    - ERR_ARG : Invalid argument
  */
int esp_wifi_internal_tx(wifi_interface_t wifi_if, void *buffer, u16_t len);

/**
  * @brief     The WiFi RX callback function
  *
  *            Each time the WiFi need to forward the packets to high layer, the callback function will be called
  */
typedef esp_err_t (*wifi_rxcb_t)(void *buffer, uint16_t len, void *eb);

/**
  * @brief     Set the WiFi RX callback
  *
  * @attention 1. Currently we support only one RX callback for each interface
  *
  * @param     wifi_interface_t ifx : interface
  * @param     wifi_rxcb_t fn : WiFi RX callback
  *
  * @return
  *     - ESP_OK : succeed
  *     - others : fail
  */
esp_err_t esp_wifi_internal_reg_rxcb(wifi_interface_t ifx, wifi_rxcb_t fn);

/**
  * @brief     Notify WIFI driver that the station got ip successfully
  *
  * @return
  *     - ESP_OK : succeed
  *     - others : fail
  */
esp_err_t esp_wifi_internal_set_sta_ip(void);

/**
  * @brief   Transmit the buffer via wifi driver
  *
  * @param   wifi_interface_t ifx : wifi interface id
  * @param   void* buffer : the buffer to be transmitted
  * @param   uint16_t len : the length of buffer
  * @param   uint8_t* dst: pointer to the destination mac address
  *
  * @return
  *    - ERR_OK  : succeed
  *    - ERR_MEM : Out of memory
  *    - ERR_IF  : WiFi driver error
  *    - ERR_ARG : Invalid argument
  */
esp_err_t esp_wifi_mesh_tx(wifi_interface_t ifx, void* buffer, uint16_t len, wifi_mac_t* dst);

/**
  * @brief   Define function pointer for mesh receive callback
  *
  * @param   wifi_interface_t ifx : pointer to wifi interface id
  * @param   void* buffer : the buffer to be transmitted
  * @param   uint16_t len : the length of buffer
  * @param   uint8_t* src: pointer to the source mac address
  */
typedef void (*esp_wifi_mesh_rxcb_t) (wifi_interface_t ifx, const void* buffer, uint16_t len, const wifi_mac_t* src);

/**
  * @brief   Register the mesh receive callback function
  *
  * @param   esp_wifi_mesh_rxcb_t fn : mesh receive callback
  */
void esp_wifi_mesh_reg_rxcb(esp_wifi_mesh_rxcb_t fn);

/**
  * @brief   Get scanned AP ie length
  *
  * @param   int type : specify an ie type
  * @param   int* len : store the returned ie length
  *
  * @return  ESP_OK : succeed
  *          others : fail
  */
esp_err_t esp_wifi_scan_get_cur_ap_info(int type, int* len);

/**
  * @brief   Get scanned AP ie record
  *
  * @param   int type : specify an ie type
  * @param   wifi_ap_record_t* ap_records : store the returned AP record
  * @param   void* buffer : store the ie data
  *
  * @return  ESP_OK : succeed
  *          others : fail
  */
esp_err_t esp_wifi_scan_get_cur_ap_record(int type, wifi_ap_record_t* ap_records,  void* buffer);

typedef struct {
    uint8_t eid;
    uint8_t len;
    uint8_t oui[3];
    uint8_t type;
    uint8_t version;
    uint8_t mesh_type;
    uint8_t mesh_id[6];
    uint8_t layer_cap;
    uint8_t layer_lvl;
    uint8_t dev_cap;
    uint8_t dev_assoc;
    uint8_t leaf_cap;
    uint8_t leaf_assoc;
    uint16_t total_cap;
    uint16_t total_assoc;
    uint16_t leaf_left;
    uint16_t scan_ap_num;
    int8_t ap_rssi;
    int8_t router_rssi;
    uint8_t flag;
    uint8_t rc_addr[6];
    int8_t rc_rssi;
    uint8_t vote_addr[6];
    int8_t vote_rssi;
    uint8_t vote_ttl;
    uint8_t child[6];
}wifi_vnd_mesh_assoc_t;

/**
  * @brief   Initialize the mesh associate structure
  *
  * @return  none
  */
esp_err_t esp_wifi_vnd_mesh_init(void);

/**
  * @brief   De-initialize the mesh associate structure
  *
  * @return  none
  */
esp_err_t esp_wifi_vnd_mesh_deinit(void);

/**
  * @brief   Set the mesh associate structure
  *
  * @param   const wifi_vnd_mesh_assoc_t* assoc : pointer to a mesh associate structure
  * @return  none
  */
esp_err_t esp_wifi_vnd_mesh_set(const wifi_vnd_mesh_assoc_t* assoc);

/**
  * @brief   Get the mesh associate structure value
  *
  * @param   wifi_vnd_mesh_assoc_t* assoc : pointer to a mesh associate structure
  * @return  none
  */
esp_err_t esp_wifi_vnd_mesh_get(wifi_vnd_mesh_assoc_t* assoc);

typedef enum {
	ESP_VND_MESH_ASSOC_TYPE_IDLE,
	ESP_VND_MESH_ASSOC_TYPE_ROOT,
	ESP_VND_MESH_ASSOC_TYPE_NODE,
	ESP_VND_MESH_ASSOC_TYPE_LEAF,
}wifi_vnd_mesh_type_t;

#define ESP_VND_MESH_ASSOC_TYPE             (1)
#define ESP_VND_MESH_ASSOC_VERSION          (2)

#define ESP_VND_MESH_ASSOC_LAYER_CAP_MAX    (128)
#define ESP_VND_MESH_ASSOC_DEV_CAP_MAX      (32)
#define ESP_VND_MESH_ASSOC_LEAF_CAP_MAX     (32)

#ifdef __cplusplus
}
#endif

#endif /* __ESP_WIFI_H__ */
