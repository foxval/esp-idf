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

#ifndef _MESH_CLOUD_H_
#define _MESH_CLOUD_H_

/*******************************************************
 *                Enumerations
 *******************************************************/
enum
{
    BFC_SEND, BFC_ACK = 128,
};

enum BFC_CMD
{
    BFC_CMD_PING = 1,
    BFC_CMD_RPC,
    BFC_CMD_TRIGGER,
    BFC_CMD_UPGRADE,
    BFC_CMD_CONFIG,
    BFC_CMD_SET,
    BFC_CMD_GET,
};

enum OTA_ACTION
{
    BFC_OTA_START = 1,
    BFC_OTA_OK,
    BFC_AREA_OTA,
    BFC_OTA_REBOOT,
    BFC_OTA_FAIL = 255,
};

enum BFC_PROTO_VALUE
{
    BFC_VALUE_TOKEN,
    BFC_VALUE_REBOOT_CNT,
    BFC_VALUE_BSSID,
    BFC_VALUE_VERSION,
    BFC_VALUE_P_BSSID,
    BFC_VALUE_RSSI,			    //5
    BFC_VALUE_BRIGHTNESS,
    BFC_VALUE_FIX_BRIGHTNESS,
    BFC_VALUE_DELAY,			//0 means bright permanently
    BFC_VALUE_OTA,
    BFC_VALUE_OTA_ACTION,       // 10
    BFC_VALUE_MODE = 12,
    BFC_VALUE_PING_TIME = 14,   //unit second
    BFC_VALUE_PUSH_TRIGGER,

    BFC_VALUE_PING_EN = 28,		//enable ping or not
    BFC_VALUE_WIFI,
    BFC_VALUE_GROUP_ID,
    BFC_VALUE_SSID,
    BFC_VALUE_PASSWORD,
    BFC_VALUE_REBOOT,
    BFC_VALUE_STA_AP,
    BFC_VALUE_HEAP,
    BFC_VALUE_NODE_INFO,
    BFC_VALUE_IP,
    BFC_VALUE_WIFI_INFO,
    BFC_VALUE_EXCEPTION,
    BFC_VALUE_OTA_STATUS,       // 40
    BFC_VALUE_RESPONSE = 127
};

/*******************************************************
 *                Structures
 *******************************************************/

typedef struct
{
    uint8_t token_id;
    uint16_t token_val;
} bfc_token_t;

/*******************************************************
 *                Function Definitions
 *******************************************************/
void mesh_process_received_data(uint8_t* buf, uint16_t len);

#endif /* _MESH_CLOUD_H_ */
