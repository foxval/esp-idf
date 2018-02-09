// Copyright 2017-2018 Espressif Systems (Shanghai) PTE LTD
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

#ifndef _MESH_CONFIG_H_
#define _MESH_CONFIG_H_

#include <stdint.h>

/*******************************************************
 *                Macros
 *******************************************************/
#define MESH_ROUTE_TABLE_NUM       (50)
//#define MESH_P2P_TOS_OFF

/*******************************************************
 *                Constants
 *******************************************************/
#ifdef MESH_ROUTER_HIDDEN
static const uint8_t MESH_ROUTER_BSSID[6] = {0x74, 0xC3, 0x30, 0xF5, 0xB4, 0xF4};
#else /* MESH_ROUTER_HIDDEN */
static const uint8_t MESH_ROUTER_BSSID[6] = { 0x00, };
#endif /* MESH_ROUTER_HIDDEN */
#define MESH_ROUTER_CHANNEL        (9)               /**< channel */
#define MESH_ROUTER_SSID           "ROUTER_SSID"     /**< ssid */
#define MESH_ROUTER_PASSWD         "ROUTER_PASSWD"   /**< password */

#define MESH_MAP_PASSWD            "MAP_PASSWD"      /**< map password */
#define MESH_MAP_CONNECTIONS       (6)               /**< max connections */
#define MESH_MAP_AUTHMODE          WIFI_AUTH_OPEN    /**< authentication mode */

#define MESH_PARENT_CHANNEL        MESH_ROUTER_CHANNEL
#define MESH_PARENT_SSID           "ESP_XXXXXX"
#define MESH_PARENT_PASSWD         ""

#define MESH_MAX_LAYER             (15)              /**< max layer */



/*******************************************************
 *                Variable Definitions
 *******************************************************/
static const uint8_t MESH_ID[6] = { 0x77, 0x77, 0x77, 0x77, 0x77, 0x77 };

#endif /* _MESH_CONFIG_H_ */
