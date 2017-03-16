/* Mesh Demo with BFC Server

 This example code is in the Public Domain (or CC0 licensed, at your option.)

 Unless required by applicable law or agreed to in writing, this
 software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 CONDITIONS OF ANY KIND, either express or implied.
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "mesh.h"
#include "mesh_log.h"
#include "mesh_wifi.h"
#include "mesh_common.h"
#include "bfc_cloud.h"

static const char *TAG = "mesh_bfc_cloud";
void mesh_bfc_rx(void);
void mesh_bfc_task_tx(void *pvParameter);
void mesh_bfc_task_rx(void *pvParameter);
void mesh_bfc_tx(void);

void mesh_bfc_tx(void)
{
    uint8_t ping_buf[49];
    int old_time = 0;
    int cur_time = 0;

    while (1) {
        cur_time = system_get_time();
        mesh_bfc_pack_ping(ping_buf, sizeof(ping_buf));
        struct mesh_header_format* header =
                (struct mesh_header_format*) ping_buf;
        MESH_LOGI(
                "[%d]ms, Send PING to server, len:%d, SRC:"MACSTR", AP:%02x:%02x:%02x:%02x:%02x:%02x, heap:%d",
                (cur_time - old_time) / 1000, header->len,
                MAC2STR(header->src_addr), ping_buf[36], ping_buf[37],
                ping_buf[38], ping_buf[39], ping_buf[40], ping_buf[41], system_get_free_heap_size());
        old_time = cur_time;
#if 0
        {
            MESH_LOGW("");
            int i;
            for (i = 0; i < header->len; i++) {
                printf("%x ", ping_buf[i]);
            }
            printf("\n");
        }
#endif

        esp32_mesh_send(header, header->len, 3000);
        vTaskDelay(5000 / portTICK_RATE_MS);
    }
}

void mesh_bfc_rx(void)
{
    int size;
    uint16_t len = 256;
    uint8_t recv_buf[256];
    void *buf = (void*) recv_buf;
    int header_size = sizeof(struct mesh_header_format);
    int oe_size = 0;
    int offset = 0;
    int old_time = 0, cur_time = system_get_time();

    while (1) {
        while ((size = esp32_mesh_recv(buf, len, portMAX_DELAY)) > 0) {
            struct mesh_header_format *header =
                    (struct mesh_header_format *) buf;
            MESH_LOGW("[%d]ms, Receive from server, len:%d, DST:"MACSTR", heap:%d",
                    (cur_time - old_time) / 1000, size,
                    MAC2STR(header->dst_addr), system_get_free_heap_size());
            oe_size = 0;
            if (size > header_size) {
                if (header->oe) {
                    oe_size = header->option->ot_len;
                }
                offset = header_size + oe_size;
                mesh_bfc_process_received_data(buf + offset,
                        header->len - offset);
            }
        }
    }
}

void mesh_bfc_task_tx(void *pvParameter)
{
    mesh_bfc_tx();
    vTaskDelete(NULL);
}

void mesh_bfc_task_rx(void *pvParameter)
{
    mesh_bfc_rx();
    vTaskDelete(NULL);
}

void mesh_bfc_start(void)
{
    xTaskCreate(mesh_bfc_task_tx, "MPTX", 2048, NULL, 5, NULL);
    xTaskCreate(mesh_bfc_task_rx, "MPRX", 2048, NULL, 5, NULL);
}
