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

#ifndef _MESH_CONFIG_H_
#define _MESH_CONFIG_H_

#include <stdint.h>

/*******************************************************
 *                Macros
 *******************************************************/
#define MESH_P2P_FORWARD_MAX_NUM   (30)
#define MESH_ROUTE_TABLE_NUM       (50)

/*
 * debug
 */
#define MESH_XON_QSIZE_DBG
//#define MESH_DUMP

/*
 * test cases
 */
//#define MESH_P2P_FORWARD_TEST
//#define MESH_PRE_SCAN
#define MESH_P2P_TOS_ON
//#define MESH_OPT_RECV_DS
//#define MESH_DISABLE_SELF_ORGANIZED
//#define MESH_ROOT_WAIVE_ITSELF
//#define MESH_P2P_FORWARD_UCAST
//#define MESH_P2P_FORWARD_BCAST
//#define MESH_P2P_FORWARD_MCAST
//#define MESH_SELF_HEALING_TEST
//#define MESH_OTA_TEST
//#define MESH_P2P_FORWARD_UCAST_12M
//#define MESH_MONITOR_TX_DONE
//#define MESH_XON
//#define MESH_PRINT_ROUTING_TABLE
#define MESH_ROOT_ROUTE_UCAST
//#define MESH_ROOT_ROUTE_MCAST
//#define MESH_TCPIP_OPT_RECV_DS
//#define MESH_REPORT_TOPO

#ifdef MESH_XON
#undef MESH_P2P_FORWARD_TEST
#endif /* MESH_XON */

#if defined (MESH_SELF_HEALING_TEST) || defined(MESH_P2P_FORWARD_UCAST_12M) || defined(MESH_OTA_TEST) || defined(MESH_ROOT_WAIVE_ITSELF)
#define MESH_P2P_FORWARD_TEST
#endif /* MESH_SELF_HEALING_TEST */

#ifdef MESH_OTA_TEST
#define MESH_P2P_FORWARD_MCAST
#endif /* MESH_OTA_TEST */

#if defined(MESH_ROOT_ROUTE_UCAST) || defined(MESH_ROOT_ROUTE_MCAST)
#define MESH_P2P_FORWARD_TEST
#endif /* MESH_ROOT_ROUTE_UCAST || MESH_ROOT_ROUTE_MCAST */

#ifdef MESH_REPORT_TOPO
#define MESH_XON
#define MESH_OPT_RECV_DS
#define MESH_TCPIP_OPT_RECV_DS
#endif /* MESH_REPORT_TOPO */

/*******************************************************
 *                Constants
 *******************************************************/
#if 0
/* NETGEAR46 */
static const uint8_t MESH_ROUTER_BSSID[6] =
{   0x10, 0xda, 0x43, 0x83, 0xf3, 0x8d};
#else
static const uint8_t MESH_ROUTER_BSSID[6] = { 0x00, };
#endif
#define MESH_ROUTER_CHANNEL        (9)               /**< channel */
#define MESH_ROUTER_SSID           "ROUTER_SSID"     /**< ssid */
#define MESH_ROUTER_PASSWD         "ROUTER_PASSWD"   /**< password */

#define MESH_MAP_PASSWD            "MAP_PASSWD"      /**< map password */
#define MESH_MAP_CONNECTIONS       (6)               /**< max connections */
#define MESH_MAP_AUTHMODE          WIFI_AUTH_OPEN    /**< authentication mode */

#define MESH_PARENT_CHANNEL        MESH_ROUTER_CHANNEL
#define MESH_PARENT_SSID           "ESP_XXXXXX"
#define MESH_PARENT_PASSWD         ""

#define MESH_MAX_LAYER             (5)               /**< max layer */

/*******************************************************
 *                Variable Definitions
 *******************************************************/
static const uint16_t MESH_SERVER_PORT = 7000; /**< server port */
static const uint8_t MESH_SERVER_IP[4] = { 192, 168, 1, 107 }; /**< server ip */
static const char MESH_SERVER_HOSTNAME[] = "192.168.1.107"; /**< server hostname */

static const uint8_t MESH_ID[6] = { 0x18, 0xfe, 0x34, 0x32, 0x12, 0xdd };
static const uint8_t MESH_P2P_FORWARD_UADDR[6] = { 0x30, 0xae, 0xa4, 0x03, 0x89,
        0xa8 };
static const uint8_t MESH_P2P_FORWARD_BADDR[6] = { 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff };
static const uint8_t MESH_P2P_FORWARD_BADDR_TX[6] = { 0x30, 0xae, 0xa4, 0x03,
        0x89, 0xa8 };
static const uint8_t MESH_P2P_FORWARD_MADDR[6] = { 0x01, 0x00, 0x5e, 0x00, 0x00,
        0x00 };
static const uint8_t MESH_BCF_LIGHT_ON[6] =
        { 0x02, 0x00, 0xbf, 0xc0, 0x06, 0x01 };
static const uint8_t MESH_BCF_LIGHT_OFF[6] = { 0x02, 0x00, 0xbf, 0xc0, 0x06,
        0x00 };

#if 1
static const uint8_t MESH_P2P_FORWARD_MADDR_NODE[30 * 6] = { 0x30, 0xae, 0xa4,
        0x03, 0x6a, 0x98, //1
        0x30, 0xae, 0xa4, 0x02, 0xa8, 0x18, //2
        0x30, 0xae, 0xa4, 0x02, 0x32, 0xe8, //3
        0x30, 0xae, 0xa4, 0x03, 0x78, 0x2c, //4
        0x30, 0xae, 0xa4, 0x03, 0x69, 0xdc, //5
        0x30, 0xae, 0xa4, 0x02, 0x3f, 0x64, //6
        0x30, 0xae, 0xa4, 0x02, 0x55, 0x7c, //7
        0x30, 0xae, 0xa4, 0x01, 0x7f, 0x9c, //8
        0x30, 0xae, 0xa4, 0x03, 0x6b, 0x34, //9
        0x30, 0xae, 0xa4, 0x03, 0x6b, 0x54, //10
        0x30, 0xae, 0xa4, 0x03, 0x6a, 0xf0, //11
        0x30, 0xae, 0xa4, 0x03, 0x71, 0x2c, //12
        0x30, 0xae, 0xa4, 0x03, 0x89, 0xa8, //13
        0x30, 0xae, 0xa4, 0x03, 0x6b, 0x60, //14
        0x30, 0xae, 0xa4, 0x02, 0xa9, 0x90, //15
        0x30, 0xae, 0xa4, 0x03, 0x85, 0xe0, //16
        0x30, 0xae, 0xa4, 0x03, 0x6f, 0x80, //17
        0x30, 0xae, 0xa4, 0x02, 0x3e, 0x7c, //18
        0x30, 0xae, 0xa4, 0x03, 0x6f, 0xb8, //19
        0x30, 0xae, 0xa4, 0x03, 0x76, 0x30, //20
        0x24, 0x0a, 0xc4, 0x11, 0x9f, 0xa0, //21
        0x30, 0xae, 0xa4, 0x03, 0x8f, 0xf8, //22
        0x24, 0x0a, 0xc4, 0x04, 0x77, 0xc0, //23
        0x30, 0xae, 0xa4, 0x03, 0x90, 0x1c, //24
        0x30, 0xae, 0xa4, 0x02, 0x33, 0x38, //25
        0x30, 0xae, 0xa4, 0x03, 0x6f, 0x98, //26
        0x30, 0xae, 0xa4, 0x02, 0xa9, 0x5c, //27
        0x30, 0xae, 0xa4, 0x01, 0x7f, 0x78, //28
        0x30, 0xae, 0xa4, 0x03, 0x6b, 0x5c, //29
        0x24, 0x0a, 0xc4, 0x0c, 0x62, 0x6c, //30
        };
#else
static const uint8_t MESH_P2P_FORWARD_MADDR_NODE[6 * 6] = {
    0x30, 0xae, 0xa4, 0x01, 0x7f, 0x9c, //8
    0x30, 0xae, 0xa4, 0x03, 0x6a, 0x98,//1
    0x30, 0xae, 0xa4, 0x03, 0x71, 0x2c,//12
    0x30, 0xae, 0xa4, 0x02, 0x32, 0xe8,//3
    0x30, 0xae, 0xa4, 0x03, 0x69, 0xdc,//5
    0x30, 0xae, 0xa4, 0x03, 0x78, 0x2c,//4
};
#endif

#endif /* _MESH_CONFIG_H_ */
