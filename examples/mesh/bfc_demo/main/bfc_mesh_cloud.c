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
#include "bfc_usr_config.h"

/*******************************************************
 *                Constants
 *******************************************************/
static const char *TAG = "mesh_bfc_cloud";
static volatile bool is_started = false;
static volatile bool is_running = true;

#ifdef INTERNAL_FORWARDING_TEST
#define BFC_PING_PERIOD_MS (100)
#else /* INTERNAL_FORWARDING_TEST */
#define BFC_PING_PERIOD_MS (10000)
#endif /* INTERNAL_FORWARDING_TEST */

/*******************************************************
 *                Function Declarations
 *******************************************************/
void mesh_bfc_tx_task_main(void *pvPara);
void mesh_bfc_rx_task_main(void *pvPara);

/*******************************************************
 *                Function Definitions
 *******************************************************/
void mesh_bfc_tx_task_main(void *pvPara)
{
    uint8_t ping_buf[49];
    int old_time = 0;
    int cur_time = 0;
    is_running = true;
#ifdef INTERNAL_FORWARDING_TEST
    uint32_t send_cnt = 0;
#endif /* INTERNAL_FORWARDING_TEST */

    while (is_running) {
        cur_time = system_get_time();
        mesh_bfc_pack_ping(ping_buf, sizeof(ping_buf));
        mesh_hdr_t* header = (mesh_hdr_t *) ping_buf;
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
#ifdef INTERNAL_FORWARDING_TEST
        send_cnt++;
        header->seq = send_cnt;
        esp_mesh_send(header, header->len, 0);
        vTaskDelay(BFC_PING_PERIOD_MS / portTICK_RATE_MS);
        MESH_LOGI(
                "[%d]ms, Send PING to server, len:%d, SRC:"MACSTR", AP:%02x:%02x:%02x:%02x:%02x:%02x, heap:%d, send_cnt:%d",
                (cur_time - old_time) / 1000, header->len,
                MAC2STR(header->src_addr), ping_buf[36], ping_buf[37],
                ping_buf[38], ping_buf[39], ping_buf[40], ping_buf[41],
                esp_get_free_heap_size(), send_cnt);
        old_time = cur_time;
#else /* INTERNAL_FORWARDING_TEST */
        esp_mesh_send(header, header->len, 0);
        vTaskDelay(BFC_PING_PERIOD_MS / portTICK_RATE_MS);
        MESH_LOGI(
                "[%d]ms, Send PING to server, len:%d, SRC:"MACSTR", AP:%02x:%02x:%02x:%02x:%02x:%02x, heap:%d",
                (cur_time - old_time) / 1000, header->len,
                MAC2STR(header->src_addr), ping_buf[36], ping_buf[37],
                ping_buf[38], ping_buf[39], ping_buf[40], ping_buf[41],
                esp_get_free_heap_size());
        old_time = cur_time;

#endif /* INTERNAL_FORWARDING_TEST */
    }

    vTaskDelete(NULL);
}

void mesh_bfc_rx_task_main(void *pvPara)
{
    int size;
    uint8_t* buf = NULL;
    uint16_t len = 1024;
    mesh_hdr_t *header = NULL;
    int header_size = sizeof(mesh_hdr_t);
    int oe_size = 0;
    int offset = 0;
    int old_time = 0, cur_time = system_get_time();
    is_running = true;
    buf = (uint8_t*) malloc(len);

#ifdef INTERNAL_FORWARDING_TEST
    int i, j;
    typedef struct
    {
        uint8_t mac[6];
        uint16_t recv_cnt;
        bool has_value;
        uint32_t recv_time;
    } child_mac_t;

    child_mac_t child_mac[INTERNAL_FORWARDING_MAX_NODE_NUM];
    memset(child_mac, 0,
    INTERNAL_FORWARDING_MAX_NODE_NUM * sizeof(child_mac_t));
#endif /* INTERNAL_FORWARDING_TEST  */

    while (is_running) {
        memset(buf, 0, len);

        while (is_running && (size = esp_mesh_recv(buf, len, portMAX_DELAY)) > 0) {
            cur_time = system_get_time();
            header = (mesh_hdr_t *) buf;

#ifdef INTERNAL_FORWARDING_TEST

            for (i = 0; i < INTERNAL_FORWARDING_MAX_NODE_NUM; i++) {
                if (child_mac[i].has_value == 0) {
                    for (j = 0; j < i; j++) {
                        if (!memcmp(child_mac[j].mac, header->src_addr, 6)) {
                            break;
                        }
                    }
                    if (j >= i && header->src_addr[0] != 0x0
                            && header->src_addr[1] != 0x0) {
                        printf("i:%d, j:%d, "MACSTR"\n", i, j,
                                MAC2STR(header->src_addr));
                        memcpy(child_mac[i].mac, header->src_addr, 6);
                        child_mac[i].has_value = 1;
                    }
                    break;
                }
            }

//            for (i = 0; i < INTERNAL_FORWARDING_MAX_NODE_NUM; i++) {
//                printf("i:%d "MACSTR"\n", i, MAC2STR(child_mac[i].mac));
//            }

            for (i = 0; i < INTERNAL_FORWARDING_MAX_NODE_NUM; i++) {
                if (child_mac[i].has_value) {
                    if (!memcmp(child_mac[i].mac, header->src_addr, 6)) {

                        child_mac[i].recv_cnt++;
                        MESH_LOGW(
                                "[%d]ms, Receive from [#%d]"MACSTR"[%d], len:%d, DST:"MACSTR", heap:%d, [%d]ms, recv/send:[%d/%d], id/lost:[#%d/%d]",
                                (cur_time - child_mac[i].recv_time) / 1000, i,
                                MAC2STR(header->src_addr),
                                child_mac[i].recv_cnt, size,
                                MAC2STR(header->dst_addr),
                                esp_get_free_heap_size(),
                                (cur_time - child_mac[i].recv_time) / 1000,
                                child_mac[i].recv_cnt, header->seq, i,
                                header->seq - child_mac[i].recv_cnt);
                        child_mac[i].recv_time = cur_time;
                        break;
                    }
                }
            }
#else /* INTERNAL_FORWARDING_TEST */

//            MESH_LOGW("[%d]ms, Receive from server/"MACSTR", len:%d, DST:"MACSTR", heap:%d",
//                    (cur_time - old_time) / 1000, MAC2STR(header->src_addr), size,
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
#endif /* INTERNAL_FORWARDING_TEST */
            memset(buf, 0, len);
        }
    }

    free(buf);
    buf = NULL;
    vTaskDelete(NULL);
}

void mesh_bfc_start(void)
{
    if (is_started) {
        return;
    }
    is_started = true;
    xTaskCreate(mesh_bfc_tx_task_main, "MBTX", 2048, NULL, 5, NULL);
    xTaskCreate(mesh_bfc_rx_task_main, "MBRX", (2048 + 1024), NULL, 5, NULL);
}

void mesh_bfc_stop(void)
{
    if (!is_started) {
        return;
    }
    is_running = false;
}

