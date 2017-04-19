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

#ifndef __MESH_CONFIG_H__
#define __MESH_CONFIG_H__

#include "mesh_common.h"

/*******************************************************
 *                Constants
 *******************************************************/
#define MESH_DEFAULT_TASK_PRI              (3)
#define MESH_DEFAULT_SCAN_RETRIES          (3)
#define MESH_DEFAULT_NO_AP_RETRIES         (32)
#define MESH_DEFAULT_MAX_HOP               (10)

#define MESH_NVS_NAMESPACE                 "MESH"
#define MESH_NVS_KEY_ROUTER_NAME           "ROUTER"
#define MESH_NVS_KEY_VER_NAME              "VERSION"
#define MESH_NVS_KEY_ROOT_NAME             "ROOT"
#define MESH_NVS_KEY_GRP_ID_NAME           "GRPID"
#define MESH_NVS_KEY_ROUTER_RSSI_NAME      "RSSI"
#define MESH_NVS_KEY_LHOP_NAME             "LHOP"
#define MESH_NVS_KEY_MHOP_NAME             "MHOP"
#define MESH_NVS_KEY_ENCRYPT_NAME          "ENCRYPT"
#define MESH_NVS_KEY_RSSI_TH_NAME          "RSSITH"
#define MESH_NVS_KEY_SERVER_INFO_NAME      "SERVER"

#define MESH_TCPIP_RX_TASK_NAME            "MTRX"
#define MESH_TCPIP_RX_TASK_STACK           (1024*2)
#define MESH_TCPIP_RX_TASK_PRI             (MESH_DEFAULT_TASK_PRI + 1)

#define MESH_TCPIP_TX_TASK_NAME            "MTTX"
#define MESH_TCPIP_TX_TASK_STACK           (1024*2)
#define MESH_TCPIP_TX_TASK_PRI             (MESH_DEFAULT_TASK_PRI + 1)

#define MESH_VER_LEN                       (8)

/*******************************************************
 *                Enumerations
 *******************************************************/
enum MESH_NVS_OPERATE
{
    MESH_WRITE_ROUTER = 0x01,      // router AP information
    MESH_READ_ROUTER,
    MESH_WRITE_VERSION,            // mesh version
    MESH_READ_VERSION,
    MESH_WRITE_ROOT,               // as root flag
    MESH_READ_ROOT,
    MESH_WRITE_ROOT_ROUTER,        // router AP & as root flag (WR)
    MESH_WRITE_GRP_ID,             // mesh group id
    MESH_READ_GRP_ID,
    MESH_WRITE_ROUTER_RSSI,        // RSSI of router
    MESH_READ_ROUTER_RSSI,
    MESH_WRITE_LAST_HOP,           // the last hop
    MESH_READ_LAST_HOP,
    MESH_WRITE_MAX_HOP,            // max hop
    MESH_READ_MAX_HOP,
    MESH_WRITE_ENCRYPT,            // encrypt information
    MESH_READ_ENCRYPT,
    MESH_WRITE_RSSI_THRESHOLD,     // RSSI threshold to select parent
    MESH_READ_RSSI_THRESHOLD,
    MESH_WRITE_SERVER_INFO,        // server information
    MESH_READ_SERVER_INFO,
    MESH_NVS_ERASE_ALL,
    MESH_OPERATE_IDX_MAX,
    MESH_NVS_DESTROY,
};


#endif /* __MESH_CONFIG_H__ */
