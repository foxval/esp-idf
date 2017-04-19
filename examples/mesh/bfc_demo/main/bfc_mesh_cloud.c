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

#include "mesh.h"
#include "mesh_log.h"
#include "mesh_wifi.h"
#include "mesh_common.h"
#include "bfc_cloud.h"

/*******************************************************
 *                Constants
 *******************************************************/
static const char *TAG = "mesh_bfc_cloud";

#define BFC_PING_PERIOD_MS (10000)

/*******************************************************
 *                Function Declarations
 *******************************************************/
void mesh_bfc_rx(void);
void mesh_bfc_task_tx(void *pvParameter);
void mesh_bfc_task_rx(void *pvParameter);
void mesh_bfc_tx(void);

/*******************************************************
 *                Function Definitions
 *******************************************************/
void mesh_bfc_tx(void)
{
    uint8_t ping_buf[49];
    int old_time = 0;
    int cur_time = 0;

    while (1) {
        cur_time = system_get_time();
        mesh_bfc_pack_ping(ping_buf, sizeof(ping_buf));
        mesh_hdr_t* header = (mesh_hdr_t *) ping_buf;
        MESH_LOGI(
                "[%d]ms, Send PING to server, len:%d, SRC:"MACSTR", AP:%02x:%02x:%02x:%02x:%02x:%02x, heap:%d",
                (cur_time - old_time) / 1000, header->len,
                MAC2STR(header->src_addr), ping_buf[36], ping_buf[37],
                ping_buf[38], ping_buf[39], ping_buf[40], ping_buf[41],
                esp_get_free_heap_size());
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
        esp_mesh_send(header, header->len, 3000);
        vTaskDelay(BFC_PING_PERIOD_MS / portTICK_RATE_MS);
    }
}

void mesh_bfc_rx(void)
{
    int size;
    uint16_t len = 256;
    uint8_t recv_buf[256];
    void *buf = (void*) recv_buf;
    int header_size = sizeof(mesh_hdr_t);
    int oe_size = 0;
    int offset = 0;
    int old_time = 0, cur_time = system_get_time();

    while (1) {
        while ((size = esp_mesh_recv(buf, len, portMAX_DELAY)) > 0) {
            mesh_hdr_t *header = (mesh_hdr_t *) buf;
//            MESH_LOGW("[%d]ms, Receive from server, len:%d, DST:"MACSTR", heap:%d",
//                    (cur_time - old_time) / 1000, size,
//                    MAC2STR(header->dst_addr), esp_get_free_heap_size());
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
    static bool is_started = false;
    if (is_started) {
        return;
    }
    is_started = true;

    xTaskCreate(mesh_bfc_task_tx, "MPTX", 2048, NULL, 5, NULL);
    xTaskCreate(mesh_bfc_task_rx, "MPRX", 2048, NULL, 5, NULL);
}
