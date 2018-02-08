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

#ifndef _MESH_CLOUD_H_
#define _MESH_CLOUD_H_

/*******************************************************
 *                Enumerations
 *******************************************************/
enum {
    BFC_SEND, BFC_ACK = 128,
};

enum BFC_CMD {
    BFC_CMD_PING,
    BFC_CMD_RPC,
    BFC_CMD_CONFIG,
    BFC_CMD_SET ,
    BFC_CMD_GET ,
};

enum BFC_PROTO_VALUE {
    BFC_VALUE_TOKEN ,
    BFC_VALUE_ADDRESS,
    BFC_VALUE_VERSION ,
    BFC_VALUE_PARENT ,
    BFC_VALUE_RSSI ,
    BFC_VALUE_BRIGHTNESS ,
    BFC_VALUE_REBOOT,
};

/*******************************************************
 *                Structures
 *******************************************************/

typedef struct {
    uint8_t token_id;
    uint16_t token_val;
} bfc_token_t;

/*******************************************************
 *                Function Definitions
 *******************************************************/
void mesh_process_received_data(mesh_addr_t *from, uint8_t *buf, uint16_t len);

#endif /* _MESH_CLOUD_H_ */
