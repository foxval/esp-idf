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
#include "mesh_log.h"
#include "mesh_cloud.h"
#include "mesh_light.h"
#include "mesh_config.h"
#include "mesh_tcpip.h"
#include "nvs.h"

/*******************************************************
 *                Constants
 *******************************************************/
#define DATA_SIZE (1024)

/*******************************************************
 *                Variable Definitions
 *******************************************************/
static const char *TAG = "mesh_main";
static bool is_running = true;

/*******************************************************
 *                Function Declarations
 *******************************************************/
esp_err_t esp_mesh_comm_p2p_start(void);
esp_err_t esp_mesh_comm_server_start(void);
esp_err_t esp_mesh_api_test(void);

/*******************************************************
 *                Function Definitions
 *******************************************************/

void esp_mesh_connected(void)
{
    int layer = esp_mesh_get_layer();
    if (layer == 1) {
        /* layer one: pink */
        mesh_gpio_set(RGB_LIGHT_PINK);
    } else if (layer == 2) {
        /* layer two: yellow */
        mesh_gpio_set(RGB_LIGHT_YELLOW);
    } else if (layer == 3) {
        /* layer one: red */
        mesh_gpio_set(RGB_LIGHT_RED);
    } else if (layer == 4) {
        /* layer one: blue */
        mesh_gpio_set(RGB_LIGHT_BLUE);
    } else if (layer == 5) {
        /* layer one: green */
        mesh_gpio_set(RGB_LIGHT_GREEN);
    } else if (layer >= 6) {
        /* layer one: white */
        mesh_gpio_set(RGB_LIGHT_WARNING);
    } else {
        mesh_gpio_set(1);
    }
}

void esp_mesh_disconnected(void)
{
    mesh_gpio_set(RGB_LIGHT_WARNING);
}

void esp_mesh_event_cb(mesh_event_t event)
{
    switch (event) {

        case MESH_EVENT_SUCCESS:
            MESH_LOGI("MESH_EVENT_SUCCESS")
            ;
            break;

        case MESH_EVENT_NO_AP_FOUND:
            /* no AP found */
            MESH_LOGE("err: no AP found after scan %d times\n",
                    MESH_SCAN_RETRIES)
            ;
            /* TODO handler for the failure */
            break;

        case MESH_EVENT_CONNECTED:
            /* wifi connected */
            MESH_LOGI("MESH_EVENT_CONNECTED layer:%d", esp_mesh_get_layer())
            ;
            if (esp_mesh_is_root()) {
                esp_mesh_enable_dhcp();
            } else {
                esp_mesh_disable_dhcp();
            }
            esp_mesh_connected();
            esp_mesh_api_test();
#ifdef MESH_P2P_FORWARD_TEST
            esp_mesh_comm_p2p_start();
#else /* MESH_P2P_FORWARD_TEST */
            esp_mesh_comm_server_start();
#endif /* MESH_P2P_FORWARD_TEST */
            break;

        case MESH_EVENT_DISCONNECTED:
            /* wifi disconnected */
            MESH_LOGI("MESH_EVENT_DISCONNECTED")
            ;
            esp_mesh_disconnected();
#ifndef MESH_P2P_FORWARD_TEST
            if (esp_mesh_is_root()) {
                esp_mesh_tcp_client_stop();
            }
#endif /* MESH_P2P_FORWARD_TEST */
            break;

        case MESH_EVENT_LAYER_CHANGE:
            /* mesh device layer changes */
            MESH_LOGI("MESH_EVENT_LAYER_CHANGE, layer:%d", esp_mesh_get_layer())
            ;
            esp_mesh_connected();
#ifndef MESH_P2P_FORWARD_TEST
            if (!esp_mesh_is_root()) {
                /* non-root */
                esp_mesh_tcp_client_stop();
            }
#endif /* MESH_P2P_FORWARD_TEST */
            break;

        case MESH_EVENT_ROOT_GOT_IP:
            /* root starts to connect to server */
            MESH_LOGI("MESH_EVENT_ROOT_GOT_IP")
            ;
#ifndef MESH_P2P_FORWARD_TEST
            if (esp_mesh_is_root()) {
                esp_mesh_tcp_client_start(MESH_SERVER_HOSTNAME,
                        strlen(MESH_SERVER_HOSTNAME), MESH_SERVER_PORT);
            }
#endif /* MESH_P2P_FORWARD_TEST */
            break;

        case MESH_EVENT_FAIL:
            MESH_LOGI("MESH_EVENT_FAIL")
            ;
            break;

        default:
            MESH_LOGI("unknown mesh event")
            ;
            break;
    }
}

static esp_err_t esp_event_handler(void *ctx, system_event_t *event)
{
    MESH_LOGE("esp_event_handler:%d", event->event_id);
    return ESP_OK;
}

void app_main(void)
{
    mesh_cfg_t* config;

    mesh_light_init();
    ESP_ERROR_CHECK(nvs_flash_init());

#if 1
    nvs_handle handle;
    nvs_open("MESH", NVS_READWRITE, &handle);
    nvs_erase_all(handle);
    nvs_close(handle);
#endif

    tcpip_adapter_init();
    ESP_ERROR_CHECK(tcpip_adapter_dhcps_stop(TCPIP_ADAPTER_IF_AP));
    ESP_ERROR_CHECK(esp_event_loop_init(esp_event_handler, NULL));
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT()
    ;
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_FLASH));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));

    esp_mesh_init();
    config = (mesh_cfg_t*) malloc(sizeof(mesh_cfg_t));
    if (config) {
        memset(config, 0, sizeof(mesh_cfg_t));
        /* mesh ID */
        memcpy((uint8_t*) &config->mesh_id, MESH_ID, 6);
        /* mesh event callback */
        config->event_cb = &esp_mesh_event_cb;
        /* router */
        config->router.channel = MESH_ROUTER_CHANNEL;
        config->router.ssid_len = strlen(MESH_ROUTER_SSID);
        memcpy((uint8_t*) &config->router.ssid, MESH_ROUTER_SSID,
                config->router.ssid_len);
        /* map */
        config->map.max_connection = MESH_MAP_CONNECTIONS;
        memcpy((uint8_t*) &config->map.password, MESH_MAP_PASSWORD,
                strlen(MESH_MAP_PASSWORD));

        esp_mesh_set_config(config);
        esp_wifi_start();
        esp_mesh_start();
        free(config);
    } else {
        MESH_LOGE("mesh fails\n");
    }

}

void esp_mesh_p2p_tx_main(void* arg)
{
    esp_err_t ret;
    mesh_addr_t to;
    mesh_addr_t parent;
    int send_count = 0;
    uint8_t test[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    mesh_data_t data;
    data.data = test;
    data.size = sizeof(test);
    data.proto = 0;
    data.tos = 0;
    memcpy((uint8_t*) &to.addr, MESH_P2P_FORWARD_ADDR, sizeof(mesh_addr_t));

    is_running = true;
    while (is_running) {

        send_count++;
        test[3] = (send_count >> 24) & 0xff;
        test[2] = (send_count >> 16) & 0xff;
        test[1] = (send_count >> 8) & 0xff;
        test[0] = (send_count) & 0xff;
        ret = esp_mesh_send(&to, &data, MESH_DATA_P2P, NULL, 0);
        esp_mesh_get_parent_bssid(&parent);
        MESH_LOGW("[L:%d]parent:"MACSTR" to "MACSTR"[send:%d], heap:%d[%d]",
                esp_mesh_get_layer(), MAC2STR(parent.addr), MAC2STR(to.addr),
                send_count, esp_get_free_heap_size(), ret);

        vTaskDelay(3000 / portTICK_RATE_MS);
    }

    vTaskDelete(NULL);
}

void esp_mesh_p2p_rx_main(void* arg)
{
    int i, j = 0, k = -1;
    esp_err_t err;
    mesh_addr_t from;
    int send_count = 0;
    mesh_data_t data;
    struct timeval cur_time;
    int flag = 0;
    data.size = DATA_SIZE;
    data.data = (uint8_t*) malloc(DATA_SIZE);
    if (!data.data) {
        ets_printf("rx start fails\n");
        vTaskDelete(NULL);
    }
    /* forwarding trace */
    typedef struct
    {
        bool set;
        mesh_addr_t mdev;
        int recv_count;
        int send_count;
        time_t recv_time;
    } mesh_forward_t;

    mesh_forward_t mforward[MESH_P2P_FORWARD_MAX_NUM];
    memset(mforward, 0, sizeof(mesh_forward_t) * MESH_P2P_FORWARD_MAX_NUM);

    is_running = true;
    while (is_running) {

        memset(data.data, 0, DATA_SIZE);
        data.size = DATA_SIZE;
        err = esp_mesh_recv(&from, &data, portMAX_DELAY, &flag, NULL);
        gettimeofday(&cur_time, NULL);

        if (data.size > sizeof(send_count)) {
            send_count = (data.data[3] << 24) | (data.data[2] << 16)
                    | (data.data[1] << 8) | data.data[0];
        }

        for (i = k + 1; i < MESH_P2P_FORWARD_MAX_NUM; i++) {
            if (!mforward[i].set) {

                for (j = 0; j < i; j++) {
                    if (!memcmp(&mforward[j].mdev, &from,
                            sizeof(mesh_addr_t))) {
                        break;
                    }
                }
                if (j >= i) {
                    memcpy((uint8_t*) &mforward[i].mdev, (uint8_t*) &from,
                            sizeof(mesh_addr_t));
                    mforward[i].set = true;
                    k = i;
                }
                break;
            }
        }

        for (i = 0; i < MESH_P2P_FORWARD_MAX_NUM; i++) {
            if (mforward[i].set) {
                if (!memcmp(&mforward[i].mdev, &from, sizeof(mesh_addr_t))) {
                    mforward[i].recv_count++;
                    mforward[i].send_count = send_count;
                    if (mforward[i].send_count < mforward[i].recv_count) {
                        mforward[i].recv_count = 0;
                    }
                    MESH_LOGI(
                            "[%u]s receive from [#%d]"MACSTR", size:%d, heap:%d, recv/send/lost:[%d/%d%d], flag:%d[%d]",
                            (int )(cur_time.tv_sec - mforward[i].recv_time), i,
                            MAC2STR(from.addr), data.size,
                            esp_get_free_heap_size(), mforward[i].recv_count,
                            mforward[i].send_count,
                            mforward[i].send_count - mforward[i].recv_count,
                            flag, err);

                    mforward[i].recv_time = cur_time.tv_sec;
                    break;
                }
            }
        }
    }

    if (data.data) {
        free(data.data);
    }
    vTaskDelete(NULL);
}

void esp_mesh_comm_tx_main(void* arg)
{
    esp_err_t ret;
    mesh_addr_t to;
    mesh_addr_t parent;
    int send_count = 0;
    mesh_data_t data;
    memset(&data, 0, sizeof(mesh_data_t));
#define PING_SIZE (26)
    data.data = (uint8_t*) malloc(PING_SIZE);
    if (!data.data) {
        ets_printf("tx start fails\n");
        vTaskDelete(NULL);
    }

    memcpy((uint8_t*) &to.addr, MESH_SERVER_IP, sizeof(MESH_SERVER_IP));
    to.addr[5] = MESH_SERVER_PORT & 0xff;
    to.addr[4] = (MESH_SERVER_PORT >> 8) & 0xff;

    /* pack data.data */
    data.data[0] = BFC_SEND | BFC_CMD_PING;
    data.data[1] = BFC_VALUE_TOKEN;
    data.data[2] = 0xbf;
    data.data[3] = 0xc0;
    data.data[4] = BFC_VALUE_BSSID;
    esp_wifi_get_mac(ESP_IF_WIFI_STA, &data.data[5]);
    data.data[11] = BFC_VALUE_P_BSSID;
    esp_mesh_get_parent_bssid((mesh_addr_t*) &data.data[12]);
    data.data[17] -= 1;
    data.data[18] = BFC_VALUE_BRIGHTNESS;
    mesh_gpio_get((int*) &data.data[19]);
    data.data[20] = BFC_VALUE_RSSI;
    esp_wifi_get_rssi((int*) &data.data[21]);
    data.data[21] = 0 - data.data[21];

    data.size = PING_SIZE;
    data.proto = 0;
    data.tos = 0;

    is_running = true;
    while (is_running) {

        send_count++;
        data.data[25] = (send_count >> 24) & 0xff;
        data.data[24] = (send_count >> 16) & 0xff;
        data.data[23] = (send_count >> 8) & 0xff;
        data.data[22] = (send_count) & 0xff;
#ifdef MESH_DUMP
        {
            int i = 0;
            ets_printf("Ping to server[%d]\n", data.size);
            for (i = 0; i < data.size; i++) {
                ets_printf("%x ", data.data[i]);
            }
            ets_printf("\n");
        }
#endif /* MESH_DUMP */
        ret = esp_mesh_send(&to, &data, MESH_DATA_TODS, NULL, 0);
        esp_mesh_get_parent_bssid(&parent);
        MESH_LOGW("[L:%d]parent:"MACSTR" to "MACSTR"[send:%d], heap:%d[%d]",
                esp_mesh_get_layer(), MAC2STR(parent.addr), MAC2STR(to.addr),
                send_count, esp_get_free_heap_size(), ret);

        vTaskDelay(10000 / portTICK_RATE_MS);
    }

    vTaskDelete(NULL);
}

void esp_mesh_comm_rx_main(void* arg)
{
    esp_err_t err;
    mesh_addr_t from;
    mesh_data_t data;
    mesh_data_t* tcp_data;
    struct timeval cur_time;
    time_t old_time = 0;
    int flag = 0;
    int recv_size = 0;
    data.size = DATA_SIZE;
    data.data = (uint8_t*) malloc(DATA_SIZE);
    if (!data.data) {
        ets_printf("rx start fails\n");
    }

    is_running = true;
    while (is_running) {
        tcp_data = NULL;
        memset(data.data, 0, DATA_SIZE);
        data.size = DATA_SIZE;
        flag = 0;
        err = esp_mesh_recv(&from, &data, portMAX_DELAY, &flag, NULL);
        gettimeofday(&cur_time, NULL);
        if (err != ESP_OK || !data.size) {
            MESH_LOGE("err:%d, size:%d", err, data.size);
            continue;
        }
#ifdef MESH_DUMP
        {
            int i = 0;
            ets_printf("%s%s server[%d]: ",
                    (flag & MESH_DATA_TODS) ? "[TO]" : "",
                    (flag & MESH_DATA_FROMDS) ? "[FROM]" : "", data.size);
            for (i = 0; i < data.size; i++) {
                ets_printf("%x ", data.data[i]);
            }
            ets_printf("\n");
        }
#endif /* MESH_DUMP */
        recv_size = data.size;
        if (flag & MESH_DATA_TODS) {

            tcp_data = (mesh_data_t*) malloc(sizeof(mesh_data_t));
            if (!tcp_data) {
                continue;
            }
            memset(tcp_data, 0, sizeof(mesh_data_t));
            tcp_data->size = recv_size;
            tcp_data->data = (uint8_t*) malloc(recv_size);
            if (!tcp_data->data) {
                free(tcp_data);
                continue;
            }
            memcpy(tcp_data->data, data.data, recv_size);
            if (esp_mesh_send_to_server(&tcp_data, 0) != ESP_OK) {
                free(tcp_data->data);
                free(tcp_data);
            }
        } else if (flag & MESH_DATA_FROMDS) {
            mesh_process_received_data(data.data, data.size);
        }
        MESH_LOGI("[%u]s receive from "MACSTR", len:%d, flag:%d, heap:%d[%d]",
                (int )(cur_time.tv_sec - old_time), MAC2STR(from.addr),
                data.size, flag, esp_get_free_heap_size(), err);
        old_time = cur_time.tv_sec;
    }

    if (data.data) {
        free(data.data);
    }
    vTaskDelete(NULL);
}

esp_err_t esp_mesh_comm_p2p_start(void)
{
    uint8_t sta_mac[6];

    static bool is_p2p_started = false;
    if (is_p2p_started) {
        return ESP_OK;
    }

    esp_wifi_get_mac(ESP_IF_WIFI_STA, sta_mac);
    if (memcmp(MESH_P2P_FORWARD_ADDR, sta_mac, sizeof(sta_mac))) {
        xTaskCreate(esp_mesh_p2p_tx_main, "MPTX", 2048, NULL, 5, NULL);
    } else {
        xTaskCreate(esp_mesh_p2p_rx_main, "MPRX", 3072, NULL, 5, NULL);
    }

    is_p2p_started = true;
    return ESP_OK;
}

esp_err_t esp_mesh_comm_server_start(void)
{
    static bool is_started = false;
    if (is_started) {
        return ESP_OK;
    }

    xTaskCreate(esp_mesh_comm_tx_main, "MSTX", 2048, NULL, 5, NULL);
    xTaskCreate(esp_mesh_comm_rx_main, "MSRX", 2048, NULL, 5, NULL);

    is_started = true;
    return ESP_OK;
}

esp_err_t esp_mesh_api_test(void)
{
    mesh_cfg_t mesh_config;
    ESP_ERROR_CHECK(esp_mesh_get_config(&mesh_config));
    mesh_router_t mesh_router;
    ESP_ERROR_CHECK(esp_mesh_get_router(&mesh_router));
    mesh_addr_t mesh_id;
    ESP_ERROR_CHECK(esp_mesh_get_id(&mesh_id));
    MESH_LOGI("mesh type:%s",
            (esp_mesh_get_type() == MESH_ROOT) ?
                    "root" :
                    ((esp_mesh_get_type() == MESH_LEAF) ? "leaf" : "node"));
    MESH_LOGI("mesh max layer:%d", esp_mesh_get_max_layer());
    MESH_LOGI("mesh max connections:%d", esp_mesh_get_map_connections());
    MESH_LOGI("mesh beacon interval:%d", esp_mesh_get_beacon_interval());

    return ESP_OK;
}
