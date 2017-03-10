/* ESP32-MESH Bin Demo

 This example code is in the Public Domain (or CC0 licensed, at your option.)

 Unless required by applicable law or agreed to in writing, this
 software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 CONDITIONS OF ANY KIND, either express or implied.
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"

#include "mesh.h"
#include "mesh_wifi.h"
#include "mesh_demo.h"
#include "mesh_json.h"
#include "mesh_performance.h"

void MESH_FUNC_ATTR
mesh_json_bcast_test()
{
    char buf[32];
    uint8_t src[6];
    uint8_t dst[6];
    struct mesh_header_format *header = NULL;

    esp_wifi_get_mac(WIFI_IF_STA, src);

    MESH_MEMSET(buf, 0, sizeof(buf));
    MESH_SPRINTF(buf, "%s", "{\"bcast\":\"");
    MESH_SPRINTF(buf + MESH_STRLEN(buf), MACSTR, MAC2STR(src));
    MESH_SPRINTF(buf + MESH_STRLEN(buf), "%s", "\"}\r\n");

    MESH_MEMSET(dst, 0, sizeof(dst)); // use bcast to get all the devices working in mesh from root.
    header = (struct mesh_header_format *) esp32_mesh_create_packet(dst, // destiny address (bcast)
            src,     // source address
            M_PROTO_JSON,      // packe with JSON format
            MESH_STRLEN(buf),  // data length
            false,   // no option
            0);       // option total len
    if (!header) {
        MESH_PRINT("bcast create packet fail\n");
        return;
    }

    if (!esp32_mesh_set_usr_data(header, buf, MESH_STRLEN(buf))) {
        MESH_PRINT("bcast set user data fail\n");
        MESH_FREE(header);
        return;
    }

    if (esp32_mesh_send(header, header->len, MESH_JSON_MAX_WAIT) < 0) {
        MESH_PRINT("bcast mesh is busy\n");
    }

    MESH_FREE(header);
}

void MESH_FUNC_ATTR
mesh_json_ucast_test()
{
    char buf[32];
    uint8_t src[6];
    uint8_t dst[6];
    struct mesh_header_format *header = NULL;

    /*
     * root device doesn't send ucast to parent
     */
    if (esp32_mesh_get_hop() == ESP_MESH_HOP_ONE) return;

    esp_wifi_get_mac(WIFI_IF_STA, src);
    esp32_mesh_get_parent_mac(dst);

    /*
     * current node sends ucast to parent
     */
    MESH_MEMSET(buf, 0, sizeof(buf));
    MESH_SPRINTF(buf, "%s", "{\"p2p\":\"");
    MESH_SPRINTF(buf + MESH_STRLEN(buf), MACSTR, MAC2STR(src));
    MESH_SPRINTF(buf + MESH_STRLEN(buf), "%s", "\"}\r\n");

    header = (struct mesh_header_format *) esp32_mesh_create_packet(dst, // destiny address
            src,     // source address
            M_PROTO_JSON,      // packe with JSON format
            MESH_STRLEN(buf),  // data length
            false,   // no option
            0);      // option total len
    if (!header) {
        MESH_PRINT("p2p create packet fail\n");
        return;
    }

    if (!esp32_mesh_set_usr_data(header, buf, MESH_STRLEN(buf))) {
        MESH_PRINT("p2p set user data fail\n");
        MESH_FREE(header);
        return;
    }

    if (esp32_mesh_send(header, header->len, MESH_JSON_MAX_WAIT) < 0) {
        MESH_PRINT("p2p mesh is busy\n");
    }

    MESH_FREE(header);
}

void MESH_FUNC_ATTR
mesh_json_mcast_test()
{
#if 0
    char buf[32];
    uint8_t src[6];
    uint16_t i = 0;
    uint16_t ot_len = 0, op_count = 0;
    uint16_t dev_count = 0, max_count = 0;
    struct mesh_header_format *header = NULL;
    struct mesh_header_option_format *option = NULL;
    uint8_t dst[6] = {0x01, 0x00, 0x5E, 0x00, 0x00, 0x00};
    struct mesh_device_mac_type *list = NULL, *root = NULL;

    if (!mesh_device_get_mac_list((const struct mesh_device_mac_type **)&list, &dev_count)) {
        MESH_PRINT("mcast get mac list fail\n");
        return;
    }

    if (!mesh_device_get_root((const struct mesh_device_mac_type **)&root)) {
        MESH_PRINT("mcast get root fail\n");
        return;
    }

    dev_count ++;

    /*
     * if it is possible, we select all nodes as one mcast group
     */

    MESH_MEMSET(buf, 0, sizeof(buf));
    MESH_SPRINTF(buf, "%s", "{\"mcast\":\"");
    MESH_SPRINTF(buf + MESH_STRLEN(buf), MACSTR, MAC2STR(src));
    MESH_SPRINTF(buf + MESH_STRLEN(buf), "%s", "\"}\r\n");

    // rest len for mcast option
    max_count = (ESP_MESH_PKT_LEN_MAX - ESP_MESH_HLEN - MESH_STRLEN(buf));
    // max mcast option count
    max_count /= ESP_MESH_OPTION_MAX_LEN;
    // max device count for mcast in current packet
    max_count *= ESP_MESH_DEV_MAX_PER_OP;
    if (dev_count > max_count)
    dev_count = max_count;

    op_count = dev_count / ESP_MESH_DEV_MAX_PER_OP;
    ot_len = ESP_MESH_OT_LEN_LEN
    + op_count * (sizeof(*option) + sizeof(*root) * ESP_MESH_DEV_MAX_PER_OP)
    + sizeof(*option) + (dev_count - op_count * ESP_MESH_DEV_MAX_PER_OP) * sizeof(*root);

    header = (struct mesh_header_format *)esp32_mesh_create_packet(
            dst,// destiny address
            src,// source address
            M_PROTO_JSON,// packe with JSON format
            MESH_STRLEN(buf),// data length
            true,// option exist
            ot_len);// option total len
    if (!header) {
        MESH_PRINT("mcast create packet fail\n");
        return;
    }

    while (i < op_count) {
        option = (struct mesh_header_option_format *)esp32_mesh_create_option(
                M_O_MCAST_GRP, (uint8_t *)(list + i * ESP_MESH_DEV_MAX_PER_OP),
                (uint8_t)(sizeof(*root) * ESP_MESH_DEV_MAX_PER_OP));
        if (!option) {
            MESH_PRINT("mcast %d create option fail\n", i);
            goto MCAST_FAIL;
        }

        if (!esp32_mesh_add_option(header, option)) {
            MESH_PRINT("mcast %d set option fail\n", i);
            goto MCAST_FAIL;
        }

        i ++;
        MESH_FREE(option);
        option = NULL;
    }

    {
        char *rest_dev = NULL;
        uint8_t rest = dev_count - op_count * ESP_MESH_DEV_MAX_PER_OP;
        if (rest > 0) {
            rest_dev = (char *)MESH_ZALLOC(sizeof(*root) * rest);
            if (!rest_dev) {
                MESH_PRINT("mcast alloc the last option buf fail\n");
                goto MCAST_FAIL;
            }
            MESH_MEMCPY(rest_dev, root, sizeof(*root));
            if (list && rest > 1)
            MESH_MEMCPY(rest_dev + sizeof(*root),
                    list + i * ESP_MESH_DEV_MAX_PER_OP,
                    (rest - 1) * sizeof(*root));
            option = (struct mesh_header_option_format *)esp32_mesh_create_option(
                    M_O_MCAST_GRP, rest_dev, sizeof(*root) * rest);
            MESH_FREE(rest_dev);
            if (!option) {
                MESH_PRINT("mcast create the last option fail\n");
                goto MCAST_FAIL;
            }

            if (!esp32_mesh_add_option(header, option)) {
                MESH_PRINT("mcast set the last option fail\n");
                goto MCAST_FAIL;
            }
        }
    }

    if (!esp32_mesh_set_usr_data(header, buf, MESH_STRLEN(buf))) {
        MESH_PRINT("mcast set user data fail\n");
        goto MCAST_FAIL;
    }

    if (esp32_mesh_send(header, header->len, MESH_JSON_MAX_WAIT) < 0) {
        MESH_PRINT("mcast mesh is busy\n");
    }

    MCAST_FAIL:
    option ? MESH_FREE(option) : 0;
    header ? MESH_FREE(header) : 0;
#endif
}
