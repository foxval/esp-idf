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
#include "mesh_wifi.h"
#include "mesh_config.h"
#include "mesh_common.h"

/*******************************************************
 *                Function Definitions
 *******************************************************/
void esp_mesh_event_set_cb(system_event_cb_t event_cb)
{
    esp_event_loop_set_cb(event_cb, NULL);
}

esp_err_t esp_mesh_wifi_init(uint8_t channel, uint8_t max_connections)
{
    static bool init = false;
    if (init) {
        return ESP_OK;
    }
    init = true;
    ESP_ERROR_CHECK(nvs_flash_init());
    system_init();
    tcpip_adapter_init();
    ESP_ERROR_CHECK(tcpip_adapter_dhcps_stop(TCPIP_ADAPTER_IF_AP));
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT()
    ;
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_FLASH));
    esp_wifi_set_mode(WIFI_MODE_APSTA);
    {
        /* Change softAP settings */
        uint8_t mac[6];
        char ssid[32] = { 0, };
        wifi_config_t config;
        memset(&config, 0, sizeof(config));
        esp_wifi_get_mac(ESP_IF_WIFI_STA, mac);
        sprintf(ssid, "ESP_%02X%02X%02X", mac[3], mac[4], mac[5]);
        memcpy(config.ap.ssid, ssid, strlen(ssid));
        config.ap.ssid_len = strlen(ssid);
        config.ap.authmode = WIFI_AUTH_OPEN;
        config.ap.channel = channel;
        config.ap.max_connection = max_connections;
        esp_wifi_set_config(ESP_IF_WIFI_AP, &config);
    }

    esp_mesh_wifi_start();

    return ESP_OK;
}
