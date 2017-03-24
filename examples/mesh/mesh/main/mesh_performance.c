/* ESP-MESH Performance Demo

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
#include "mesh_common.h"
#include "mesh_performance.h"

static void mesh_performance_bench_rx();
static void mesh_performance_task_tx(void *pvParameter);
static void mesh_performance_task_rx(void *pvParameter);
static void mesh_performance_bench_tx(uint16_t len, uint32_t pkt_count);

static void MESH_FUNC_ATTR mesh_performance_bench_tx(uint16_t len,
        uint32_t pkt_count)
{
    uint32_t i;
    double bps, pps;
    uint32_t pkts = 0;
    uint32_t bytes = 0;
    uint16_t pkt_len = len;
    uint32_t start, end, diff;
    uint8_t src[MESH_HWADDR_LEN];
    uint8_t dst[MESH_HWADDR_LEN];
    struct mesh_header_format *header = NULL;

    if (len == 0 || len > ESP_MESH_PKT_LEN_MAX - ESP_MESH_HLEN)
        pkt_len = ESP_MESH_PKT_LEN_MAX - ESP_MESH_HLEN;

    esp_wifi_get_mac(WIFI_IF_STA, src);
    /*
     * root sends packet to server
     * normal nodes send packet to parent
     */
    if (esp_mesh_get_hop() == ESP_MESH_HOP_ONE) {
        MESH_MEMCPY(dst, g_mesh_server_info.ip, sizeof(g_mesh_server_info.ip));
        MESH_MEMCPY(dst + sizeof(g_mesh_server_info.ip),
                &g_mesh_server_info.port, sizeof(g_mesh_server_info.port));
    } else {
        esp_mesh_get_parent_mac(dst);
    }

    header = (struct mesh_header_format *) esp_mesh_create_packet(dst, // destiny address of parent
            src,     // source address
            M_PROTO_BIN,   // packe with JSON format
            pkt_len,       // data length
            false,  // no option
            0);     // option total len
    if (!header) {
        MESH_PRINT("create packet fail\n");
        return;
    }

    MESH_PRINT("%s\n", __func__);

    while (1) {
        pkts = 0;
        bytes = 0;
        start = system_get_time();
        MESH_PRINT("h->dst:" ESP_MESH_MACSTR "\n",
                ESP_MESH_MAC2STR(header->dst_addr));
        for (i = 0; i < pkt_count; i++) {
            if (esp_mesh_send(header, header->len, 10000) <= 0) break;

            if (esp_mesh_get_hop() == ESP_MESH_HOP_ONE)
                vTaskDelay(5000 / portTICK_RATE_MS);
            pkts++;
            bytes += header->len;
        }

        end = system_get_time();

        diff = (uint32_t) (end - start);
        pps = pkts * 1000.0 / diff;
        bps = bytes * 1000.0 / diff;
        MESH_PRINT(
                "\n\n============================================================\n");
        MESH_PRINT("ESP-MESH Performance Bench TX:\n");
        MESH_PRINT("pkt_len:%u, pkt_count:%u\n", pkt_len, pkt_count);
        MESH_PRINT("start:%u, end:%u, diff:%u\n", start, end, diff);
        MESH_PRINT("tx_pkt:%u, tx_bystes:%u\n", pkts, bytes);
        MESH_PRINT("performance:%.3f kpps, bps:%.2f kbps\n", pps, bps * 8);
        MESH_PRINT(
                "============================================================\n\n");
        if (esp_mesh_get_hop() == ESP_MESH_HOP_ONE)
            vTaskDelay(5000 / portTICK_RATE_MS);
        mesh_print_task_info();
    }
}

static void MESH_FUNC_ATTR mesh_performance_bench_rx()
{
    int res;
    double bps, pps;
    uint32_t pkts = 0;
    uint32_t bytes = 0;
    uint32_t start = 0, end, diff;
    uint16_t len = ESP_MESH_PKT_LEN_MAX;
    void *buf = MESH_ZALLOC(len);

    if (!buf) {
        MESH_PRINT("bench receive buf is NULL\n");
        return;
    }

    MESH_PRINT("%s\n", __func__);

    while (1) {
        pkts = 0;
        bytes = 0;
        start = 0;
        while ((res = esp_mesh_recv(buf, len, portMAX_DELAY)) > 0) {
#if 0
            struct mesh_header_format *header = (struct mesh_header_format *)buf;
            MESH_PRINT("recv len:%u, from:" ESP_MESH_MACSTR "\n",
                    res, ESP_MESH_MAC2STR(header->dst_addr));
#endif
            if (start == 0) start = system_get_time();
            pkts++;
            bytes += res;
            if ((pkts & 0x3FFF) == 0) break;
        }

        end = system_get_time();
        MESH_PRINT(
                "\n\n============================================================\n");
        MESH_PRINT("ESP-MESH Performance Bench RX:\n");
        diff = (uint32_t) (end - start);
        pps = pkts * 1000.0 / diff;
        bps = bytes * 1000.0 / diff;
        MESH_PRINT("start:%u, end:%u, diff:%u\n", start, end, diff);
        MESH_PRINT("rx_pkt:%u, rx_bystes:%u\n", pkts, bytes);
        MESH_PRINT("performance:%.3f kpps, bps:%.2f kbps\n", pps, bps * 8);
        MESH_PRINT(
                "============================================================\n\n");
        mesh_print_task_info();
    }
}

static void MESH_FUNC_ATTR mesh_performance_task_tx(void *pvParameter)
{
    printf("mesh performance bench tx, free heap:%u\n",
            esp_get_free_heap_size());
    mesh_performance_bench_tx(ESP_MESH_PKT_LEN_MAX - ESP_MESH_HLEN, 0x4000);
    vTaskDelete(NULL);
}

static void MESH_FUNC_ATTR mesh_performance_task_rx(void *pvParameter)
{
    printf("mesh performance bench rx, free heap:%u\n",
            esp_get_free_heap_size());
    mesh_performance_bench_rx();
    vTaskDelete(NULL);
}

void MESH_FUNC_ATTR mesh_performance_start()
{
    xTaskCreate(mesh_performance_task_tx, "MPTX", 2048, NULL, 5, NULL);
    xTaskCreate(mesh_performance_task_rx, "MPRX", 2048, NULL, 5, NULL);
}
