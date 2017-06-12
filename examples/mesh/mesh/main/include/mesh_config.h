// Copyright 2015-2017 Espressif Systems (Shanghai) PTE LTD
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

#define MESH_DUMP
#define MESH_P2P_FORWARD_TEST
#define MESH_P2P_FORWARD_MAX_NUM   (20)
#define MESH_PRE_SCAN
/*******************************************************
 *                Constants
 *******************************************************/
#define MESH_ROUTER_CHANNEL        (9)               /**< channel */
#define MESH_ROUTER_SSID           "udp2"            /**< ssid */
#define MESH_ROUTER_PASSWD         "12345678"        /**< password */

#define MESH_MAP_PASSWORD          "12345678"        /**< map password */
#define MESH_MAP_CONNECTIONS       (6)               /**< max connections */

/*******************************************************
 *                Variable Definitions
 *******************************************************/
static const uint16_t MESH_SERVER_PORT = 7000; /**< server port */
static const uint8_t MESH_SERVER_IP[4] = { 192, 168, 1, 128 }; /**< server ip */
static const char MESH_SERVER_HOSTNAME[] = "192.168.1.100"; /**< server hostname */

static const uint8_t MESH_ID[6] = { 0x18, 0xfe, 0x34, 0x32, 0x00, 0xbb }; /**< mesh id */
static const uint8_t MESH_P2P_FORWARD_ADDR[6] = { 0x30, 0xae, 0xa4, 2, 0x32,
        0xe8 }; /**< mac of P2P forwarding */

#endif /* _MESH_CONFIG_H_ */
