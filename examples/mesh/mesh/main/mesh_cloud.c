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

#include "mesh.h"
#include "mesh_common.h"
#include "mesh_log.h"
#include "mesh_cloud.h"
#include "mesh_light.h"
#include "mesh_config.h"

/*******************************************************
 *                Variable Definitions
 *******************************************************/
static const char *TAG = "mesh_cloud";

/*******************************************************
 *                Function Definitions
 *******************************************************/

esp_err_t mesh_parse_protocol(uint8_t *buf, uint16_t start_index,
        uint16_t total_length, enum BFC_CMD type)
{
    //Currently, only care about Brightness
    int brightness;

    if (start_index >= total_length) {
        MESH_LOGE("start index %d is over total length %d\n", start_index,
                total_length);
        return ESP_FAIL;
    }
    if (type == BFC_CMD_SET || type == BFC_CMD_GET) {
        switch (buf[start_index]) {
            case BFC_VALUE_PING_EN:
                break;
            case BFC_VALUE_OTA_STATUS:
                break;
            case BFC_VALUE_VERSION:
                break;
            case BFC_VALUE_IP:
                break;
            case BFC_VALUE_GROUP_ID:
                break;
            case BFC_VALUE_WIFI:
                break;
            case BFC_VALUE_REBOOT:
                break;
            case BFC_VALUE_WIFI_INFO:
                break;
            case BFC_VALUE_HEAP:
                break;
            case BFC_VALUE_NODE_INFO:
                break;
            case BFC_VALUE_EXCEPTION:
                break;
            default:
                MESH_LOGE("Unserved type:%d", buf[start_index])
                ;
                return ESP_FAIL;
        }
    }

    if (type == BFC_CMD_RPC) {
        switch (buf[start_index]) {
            case BFC_VALUE_BRIGHTNESS:
//                MESH_LOGW("brightness:%d\n", buf[start_index + 1])
                ;
                brightness = buf[start_index + 1];
                if (mesh_light_set(brightness) == ESP_FAIL) {
                    if (buf[start_index + 1] == 0) {
                        mesh_gpio_set(0);
                    } else {
#if 1
                        if (esp_mesh_get_layer() == 1) {
                            /* layer one: pink */
                            mesh_gpio_set(RGB_LIGHT_PINK);
                        } else if (esp_mesh_get_layer() == 2) {
                            /* layer two: yellow */
                            mesh_gpio_set(RGB_LIGHT_YELLOW);
                        } else if (esp_mesh_get_layer() == 3) {
                            /* layer one: red */
                            mesh_gpio_set(RGB_LIGHT_RED);
                        } else if (esp_mesh_get_layer() == 4) {
                            /* layer one: blue */
                            mesh_gpio_set(RGB_LIGHT_BLUE);
                        } else if (esp_mesh_get_layer() == 5) {
                            /* layer one: green */
                            mesh_gpio_set(RGB_LIGHT_GREEN);
                        } else if (esp_mesh_get_layer() >= 6) {
                            /* layer one: white */
                            mesh_gpio_set(RGB_LIGHT_WARNING);
                        } else {
                            mesh_gpio_set(1);
                        }

#else
                        mesh_gpio_set(1);
#endif
                    }
                }
                break;
            case BFC_VALUE_FIX_BRIGHTNESS:
                break;
            case BFC_VALUE_MODE:
                break;
            case BFC_VALUE_DELAY:
                break;
            case BFC_VALUE_PING_TIME:
                break;
            case BFC_VALUE_PUSH_TRIGGER:
                break;
            default:
                return ESP_FAIL;
        }
    }
    return ESP_OK;
}

void mesh_process_received_data(uint8_t* buf, uint16_t len)
{
//ping ack
//header: 0 10 14 0 24 a c4 3 b8 dc 0 0 0 0 0 0
//cmd   : 81 0 bf c0

//rpc
//header: 0 10 19 0 24 a c4 3 b8 dc 0 0 0 0 0 0
//cmd   : 2 0 bf c0 6 0 8 0 3

#if 0
    if (len) {
        int i;
        for (i = 0; i < len; i++) {
            printf("%x ", buf[i]);
        }
        printf("\n");
    }
#endif
    bfc_token_t token;
    token.token_id = BFC_VALUE_TOKEN;
    token.token_val = 0xbfc0;
    if (!(memcmp(&token, &buf[1], 3))) {
        return;
    }
    switch (buf[0]) {
        case BFC_ACK | BFC_CMD_PING:
            printf("Receive BFC_PING_ACK \r\n");
            break;

        case BFC_CMD_RPC:
            printf("Receive BFC_RPC\r\n");
            mesh_parse_protocol(buf, 4, len, BFC_CMD_RPC);
            break;

        case BFC_CMD_CONFIG:
            printf("Receive BFC_CONFIG\r\n");
            mesh_parse_protocol(buf, 4, len, BFC_CMD_CONFIG);
            break;
    }
}
