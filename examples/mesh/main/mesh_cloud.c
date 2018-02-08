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

#include "esp_mesh.h"
#include "mesh_log.h"
#include "mesh_cloud.h"
#include "mesh_light.h"
#include "mesh_config.h"
#include "mesh_common.h"

/*******************************************************
 *                Variable Definitions
 *******************************************************/
static const char *TAG = "mesh_cloud";

/*******************************************************
 *                Function Declarations
 *******************************************************/
extern void esp_mesh_connected_indicator(int layer);

/*******************************************************
 *                Function Definitions
 *******************************************************/
esp_err_t mesh_get_sta_list(mesh_addr_t *from)
{
    int j;
    esp_err_t err;
    mesh_data_t data = { 0, };
    wifi_sta_list_t sta_list;

    esp_wifi_ap_get_sta_list(&sta_list);
    for (j = 0; j < sta_list.num; j++) {

        ets_printf("[%d][L:%d]"MACSTR"\n", j, esp_mesh_get_layer(),
                   MAC2STR(sta_list.sta[j].mac));

    }
    data.size = sizeof(sta_list);
    data.data = (uint8_t *) &sta_list;
    data.tos = MESH_DATA_P2P;
    err = esp_mesh_send(from, &data, MESH_DATA_TODS, NULL, 0);

    MESH_LOGI("send station list to "MACSTR", size:%d, err:%d\n",
              MAC2STR(from->addr), data.size, err);

    return ESP_OK;
}

esp_err_t mesh_parse_protocol(mesh_addr_t *from, uint8_t *buf,
                              uint16_t start_index, uint16_t total_length, enum BFC_CMD type)
{
    int brightness;
    if (start_index >= total_length) {
        MESH_LOGE("start index %d is over total length %d\n", start_index,
                  total_length);
        return ESP_FAIL;
    }

    if (type == BFC_CMD_RPC) {
        switch (buf[start_index]) {
        case BFC_VALUE_BRIGHTNESS:
            brightness = buf[start_index + 1];
            if (brightness == 0) {
                mesh_gpio_set(0);
            } else {
                esp_mesh_connected_indicator(esp_mesh_get_layer());
            }
            break;
        default:
            break;
        }
    }
    return ESP_OK;
}

void mesh_process_received_data(mesh_addr_t *from, uint8_t *buf, uint16_t len)
{
    /*
     * ping ack
     * header: 0 10 14 0 24 a c4 3 b8 dc 0 0 0 0 0 0
     * cmd   : 81 0 bf c0
     *
     * rpc
     * header: 0 10 19 0 24 a c4 3 b8 dc 0 0 0 0 0 0
     * cmd   : 2 0 bf c0 6 0 8 0 3
     * */
    bfc_token_t token;
    token.token_id = BFC_VALUE_TOKEN;
    token.token_val = 0xbfc0;
    if (!(memcmp(&token, &buf[1], 3))) {
        return;
    }
    switch (buf[0]) {
    case BFC_ACK | BFC_CMD_PING:
        MESH_LOGD("Receive BFC_PING_ACK");
        break;
    case BFC_CMD_RPC:
        MESH_LOGD("Receive BFC_RPC");
        mesh_parse_protocol(from, buf, 4, len, BFC_CMD_RPC);
        break;
    case BFC_CMD_GET:
        MESH_LOGD("Receive BFC_CMD_GET");
        mesh_parse_protocol(from, buf, 4, len, BFC_CMD_GET);
        break;
    case BFC_CMD_CONFIG:
        MESH_LOGD("Receive BFC_CONFIG");
        mesh_parse_protocol(from, buf, 4, len, BFC_CMD_CONFIG);
        break;
    }
}
