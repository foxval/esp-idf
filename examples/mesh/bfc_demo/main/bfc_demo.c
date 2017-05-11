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
#include "mesh_config.h"
#include "mesh_wifi.h"
#include "mesh_tcpip.h"
#include "mesh_log.h"
#include "bfc_light.h"
#include "bfc_usr_config.h"

/*******************************************************
 *                Variable Definitions
 *******************************************************/
static const char *TAG = "bfc_demo";
void mesh_usr_task(void *pvParameter);
void esp_mesh_event_cb(esp_mesh_event_t event);

/*******************************************************
 *                Function Declarations
 *******************************************************/
extern void mesh_bfc_start(void);
extern void mesh_bfc_stop(void);
extern esp_err_t esp_mesh_usr_init(void);

/*******************************************************
 *                Function Definitions
 *******************************************************/
void esp_mesh_connected(void)
{
    if (esp_mesh_get_hop() == 1) {
        /* layer one: pink */
        mesh_bfc_gpio_set(RGB_LIGHT_PINK);
    } else if (esp_mesh_get_hop() == 2) {
        /* layer two: yellow */
        mesh_bfc_gpio_set(RGB_LIGHT_YELLOW);
    } else if (esp_mesh_get_hop() == 3) {
        /* layer one: red */
        mesh_bfc_gpio_set(RGB_LIGHT_RED);
    } else if (esp_mesh_get_hop() == 4) {
        /* layer one: blue */
        mesh_bfc_gpio_set(RGB_LIGHT_BLUE);
    } else if (esp_mesh_get_hop() == 5) {
        /* layer one: green */
        mesh_bfc_gpio_set(RGB_LIGHT_GREEN);
    } else if (esp_mesh_get_hop() >= 6) {
        /* layer one: white */
        mesh_bfc_gpio_set(RGB_LIGHT_WARNING);
    } else {
        mesh_bfc_gpio_set(1);
    }
}

void esp_mesh_disconnected(void)
{
    mesh_bfc_gpio_set(RGB_LIGHT_WARNING);
}

void esp_mesh_event_cb(esp_mesh_event_t event)
{
    switch (event) {

        case ESP_MESH_EVENT_SUCCESS:
            MESH_LOGI("MESH_EVENT_SUCCESS")
            ;
            break;

        case ESP_MESH_EVENT_NO_AP_FOUND:
            /* no AP found */
            MESH_LOGE("Error: no AP found after scan %d times\n",
                    MESH_DEFAULT_NO_AP_RETRIES)
            ;
            /* TODO handler for the failure */
            break;

        case ESP_MESH_EVENT_PARENT_DONE:
            /* parent selected */
            MESH_LOGI("MESH_EVENT_PARENT_DONE")
            ;
            if (esp_mesh_is_root()) {
                esp_mesh_tcpip_enable_dhcp();
            } else {
                esp_mesh_tcpip_disable_dhcp();
            }
            break;

        case ESP_MESH_EVENT_CONNECTED:
            /* wifi connected */
            MESH_LOGI("MESH_EVENT_CONNECTED layer:%d", esp_mesh_get_hop())
            ;
            esp_mesh_connected();
            mesh_bfc_start();

            break;

        case ESP_MESH_EVENT_DISCONNECTED:
            /* wifi disconnected */
            MESH_LOGI("MESH_EVENT_DISCONNECTED")
            ;
            esp_mesh_disconnected();
//            mesh_bfc_stop();
            if (esp_mesh_is_root()) {
                esp_mesh_tcp_client_stop();
            }
            break;

        case ESP_MESH_EVENT_LAYER_CHANGE:
            /* mesh device layer changes */
            MESH_LOGI("MESH_EVENT_LAYER_CHANGE, layer:%d", esp_mesh_get_hop())
            ;
            esp_mesh_connected();
            if (!esp_mesh_is_root()) {
                /* non-root */
                esp_mesh_tcp_client_stop();
            }
            break;

        case ESP_MESH_EVENT_TCP_CONNECT:
            /* root starts to connect to server */
            MESH_LOGI("MESH_EVENT_TCP_CONNECT")
            ;
            if (esp_mesh_is_root()) {
                esp_mesh_tcp_client_start(MESH_SERVER_HOSTNAME,
                        strlen(MESH_SERVER_HOSTNAME), MESH_SERVER_PORT);
            }
            break;

        case ESP_MESH_EVENT_TCP_CONNECTED:
            /* root connects with server */
            MESH_LOGI("MESH_EVENT_TCP_CONNECTED")
            ;
            break;

        case ESP_MESH_EVENT_TCP_DISCONNECTED:
            /* root disconnects with server */
            MESH_LOGI("MESH_EVENT_TCP_DISCONNECTED")
            ;
            break;

        case ESP_MESH_EVENT_FAIL:
            MESH_LOGI("MESH_EVENT_FAIL")
            ;
            break;

        default:
            MESH_LOGI("Unknown mesh event")
            ;
            break;
    }
}

void mesh_usr_task(void *pvParameter)
{
    esp_mesh_enable(esp_mesh_event_cb, MESH_ONLINE);
    vTaskDelete(NULL);
}

void app_main(void)
{

    mesh_bfc_light_init();

    if (esp_mesh_wifi_init(MESH_ROUTER_CHANNEL, ESP_MESH_CONNECT_MAX) != ESP_OK) {
        return;
    }
#if 0
    {
        wifi_config_t config;
        memset(&config, 0, sizeof(config));
        esp_wifi_get_config(ESP_IF_WIFI_AP, &config);
        MESH_LOGI("softAP:%s, channel:%d, max connections:%d\n",
                (char* ) config.ap.ssid, config.ap.channel,
                config.ap.max_connection);
    }
#endif
    if (esp_mesh_usr_init() != ESP_OK) {
        return;
    }

    xTaskCreate(mesh_usr_task, "mudt", 4096, NULL, 5, NULL);
}
