/* Mesh Demo with BFC Server

 This example code is in the Public Domain (or CC0 licensed, at your option.)

 Unless required by applicable law or agreed to in writing, this
 software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 CONDITIONS OF ANY KIND, either express or implied.
 */

#include "esp_wifi.h"
#include "esp_err.h"
#include "mesh.h"
#include "mesh_common.h"
#include "mesh_log.h"
#include "bfc_cloud.h"
#include "driver/gpio.h"

static const char *TAG = "bfc_cloud";
static bfc_t bfc = { .delay = 0, .brightness = 100, .fix_brightness = 100,
        .ping_time = 10, };

#define BLINK_GPIO GPIO_NUM_0

void mesh_bfc_set_gpio(int value)
{
    static bool inited = false;
    if (inited == false) {
        gpio_pad_select_gpio(BLINK_GPIO);
        /* Set the GPIO as a push/pull output */
        gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
        inited = true;
    }
    gpio_set_level(BLINK_GPIO, value);
}

esp_err_t mesh_bfc_set_light(int brightness)
{

    return ESP_FAIL;
}

esp_err_t mesh_bfc_get_light(int* brightness)
{

    return ESP_FAIL;
}

void mesh_bfc_pack_ping(uint8_t* ping_buf, uint8_t len)
{
    uint8_t buf[33];
    uint8_t mac[6];
    int restart_cnt = 0;
    int rssi;
    int brightness;
    wifi_ap_record_t ap;
    esp_wifi_get_rssi(&rssi);
    esp_wifi_get_mac(ESP_IF_WIFI_STA, mac);
    esp_wifi_sta_get_ap_info(&ap);

    buf[0] = BFC_SEND | BFC_CMD_PING;
    buf[1] = BFC_VALUE_TOKEN;
    buf[2] = 0xbf;
    buf[3] = 0xc0;                       // token 2 bytes
    buf[4] = BFC_VALUE_BSSID;
    MESH_MEMCPY(&buf[5], mac, 6);        // bssid 6 bytes
    buf[11] = BFC_VALUE_P_BSSID;
    MESH_MEMCPY(&buf[12], ap.bssid, 6);  // parent bssid 6 bytes
    buf[18] = BFC_VALUE_BRIGHTNESS;
    if (mesh_bfc_get_light(&brightness) == ESP_OK) {
        buf[19] = brightness;
    } else {
        buf[19] = bfc.brightness;
    }
    buf[20] = BFC_VALUE_FIX_BRIGHTNESS;
    buf[21] = bfc.fix_brightness;         // fix-brightness 1 byte
    buf[22] = BFC_VALUE_DELAY;
    buf[23] = (bfc.delay) >> 8;
    buf[24] = (bfc.delay) & 0xff;        // 0 means forever
    buf[25] = BFC_VALUE_PING_TIME;
    buf[26] = (bfc.ping_time) >> 8;
    buf[27] = (bfc.ping_time) & 0xff;    //ping time 2 bytes
    buf[28] = BFC_VALUE_RSSI;
    buf[29] = 0 - rssi;
    buf[30] = BFC_VALUE_REBOOT_CNT;
    buf[31] = restart_cnt >> 8;
    buf[32] = restart_cnt & 0xff;

    struct mesh_header_format header;
    MESH_MEMSET(&header, 0, sizeof(header));
    header.ocr = 1;
    header.proto.protocol = M_PROTO_BIN;
    header.len = sizeof(header) - 2 * sizeof(uint32_t) + sizeof(buf);
    esp_wifi_get_mac(ESP_IF_WIFI_STA, header.src_addr);
    MESH_MEMCPY(header.dst_addr, g_mesh_server_info.ip,
            sizeof(g_mesh_server_info.ip));
    MESH_MEMCPY(header.dst_addr + sizeof(g_mesh_server_info.ip),
            &g_mesh_server_info.port, sizeof(g_mesh_server_info.port));
    MESH_MEMCPY(ping_buf, (uint8_t*) &header,
            sizeof(header) - 2 * sizeof(uint32_t)); //without seq & ack
    MESH_MEMCPY(&ping_buf[16], buf, sizeof(buf));

}

esp_err_t mesh_bfc_parse_protocol(uint8_t *buf, uint16_t start_index,
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
                MESH_LOGW("%s,%d brightness: %d\n", __func__, __LINE__,
                        buf[start_index + 1])
                ;
                brightness = buf[start_index + 1];
                if (mesh_bfc_set_light(brightness) == ESP_FAIL) {
                    if (buf[start_index + 1] == 0) {
                        mesh_bfc_set_gpio(0);
                    } else {
                        mesh_bfc_set_gpio(1);
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

void mesh_bfc_process_received_data(uint8_t* buf, uint16_t len)
{

//ping ack
//header: 0 10 14 0 24 a c4 3 b8 dc 0 0 0 0 0 0
//cmd   : 81 0 bf c0

//rpc
//header: 0 10 19 0 24 a c4 3 b8 dc 0 0 0 0 0 0
//cmd   : 2 0 bf c0 6 0 8 0 3

#if 1
    if (len) {
        int i;
        for (i = 0; i < len; i++)
            printf("%x ", buf[i]);
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
            mesh_bfc_parse_protocol(buf, 4, len, BFC_CMD_RPC);
            break;

        case BFC_CMD_CONFIG:
            printf("Receive BFC_CONFIG\r\n");
            mesh_bfc_parse_protocol(buf, 4, len, BFC_CMD_CONFIG);
            break;
    }
}
