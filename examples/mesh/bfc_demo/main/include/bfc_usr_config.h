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

#ifndef _BFC_USR_CONFIG_H_
#define _BFC_USR_CONFIG_H_

#include <stdint.h>
#include "esp_wifi_types.h"

//#define INTERNAL_FORWARDING_TEST
#define INTERNAL_FORWARDING_MAX_NODE_NUM   (5)

/*******************************************************
 *                Constants
 *******************************************************/
#define MESH_ROUTER_SSID     "udp2"            /*THE ROUTER SSID*/
#define MESH_ROUTER_PASSWD   "qwertyuiop"      /*THE ROUTER PASSWORD*/
#define MESH_ROUTER_CHANNEL  (9)
#define MESH_SSID_PREFIX     "MESH32"          /*SET THE DEFAULT MESH SSID PREFIX;THE FINAL SSID OF SOFTAP WOULD BE "MESH_SSID_PREFIX_X_YYYYYY"*/
#define MESH_AUTH            WIFI_AUTH_OPEN    /*AUTH_MODE OF SOFTAP FOR EACH MESH NODE*/
#define MESH_PASSWD          "123123123"       /*SET PASSWORD OF SOFTAP FOR EACH MESH NODE*/
#define MESH_MAX_HOP         (5)               /*MAX_HOPS OF MESH NETWORK*/

/*******************************************************
 *                Variable Definitions
 *******************************************************/
static const uint16_t MESH_SERVER_PORT = 7000; /*PORT USED BY USER IOT SERVER FOR MESH SERVICE*/
static const uint8_t MESH_SERVER_IP[4] = { 192, 168, 1, 110 }; /*USER IOT SERVER IP ADDRESS*/
static const char MESH_SERVER_HOSTNAME[] = "192.168.1.100";
static const uint32_t UART_BAUD_RATIO = 115200; /*UART BAUD RATIO*/
static const uint8_t MESH_GROUP_ID[6] = { 0x18, 0xfe, 0x34, 0x32, 0x00, 0x50 }; /*MESH_GROUP_ID REPRESENTS ONE MESH NETWORK*/
static const uint8_t MESH_ROUTER_BSSID[6] =
        { 0xF0, 0xB4, 0x29, 0x2C, 0x7C, 0x72 }; /*MAC OF ROUTER*/
static const uint8_t MESH_IFORWARDING_ADDR[6] = { 0x30, 0xae, 0xa4, 2, 0x55,
        0x7d }; /*MAC OF INTERNAL FORWARDING*/

#endif /* _BFC_USR_CONFIG_H_ */
