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
#include "mesh_common.h"
#include "bfc_usr_config.h"

/*******************************************************
 *                Function Definitions
 *******************************************************/
esp_err_t esp_mesh_router_init(void)
{
    wifi_sta_config_t sta;
    memset(&sta, 0, sizeof(sta));
    memcpy(sta.ssid, MESH_ROUTER_SSID, strlen(MESH_ROUTER_SSID));
    memcpy(sta.password, MESH_ROUTER_PASSWD, strlen(MESH_ROUTER_PASSWD));

    if (!esp_mesh_set_router(&sta, MESH_ROUTER_CHANNEL)) {
        MESH_PRINT("set router fail\n");
        return ESP_FAIL;
    }

    return ESP_OK;
}

esp_err_t esp_mesh_usr_init(void)
{
    /*
     * set the AP password of mesh node
     */
    if (!esp_mesh_encrypt_init(MESH_AUTH, (uint8_t *) MESH_PASSWD,
            strlen(MESH_PASSWD))) {
        MESH_PRINT("set pw fail\n");
        return ESP_FAIL;
    }

    /*
     * if you want set max_hop > 4
     * please make the heap is available
     * mac_route_table_size = (4^max_hop - 1)/3 * 6
     */
    if (!esp_mesh_set_max_hops(MESH_MAX_HOP)) {
        MESH_PRINT("fail, max_hop:%d\n", MESH_MAX_HOP);
        return ESP_FAIL;
    }

    /*
     * mesh_ssid_prefix
     * mesh_group_id and mesh_ssid_prefix represent mesh network
     */
#if 0
    if (!esp_mesh_set_ssid_prefix(MESH_SSID_PREFIX, strlen(MESH_SSID_PREFIX))) {
        MESH_PRINT("set prefix fail\n");
        return ESP_FAIL;
    }
#endif
    /*
     * mesh_group_id
     * mesh_group_id and mesh_ssid_prefix represent mesh network
     */
    if (!esp_mesh_group_id_init((uint8_t *) MESH_GROUP_ID,
            sizeof(MESH_GROUP_ID))) {
        MESH_PRINT("set grp id fail\n");
        return ESP_FAIL;
    }

    /*
     * set cloud server ip and port for mesh node
     */
    if (!esp_mesh_server_init((ip_addr_t *) MESH_SERVER_IP, MESH_SERVER_PORT)) {
        MESH_PRINT("server_init fail\n");
        return ESP_FAIL;
    }

    if (esp_mesh_router_init() != ESP_OK) {
        MESH_PRINT("router_init fail\n");
        return ESP_FAIL;
    }

#if 0
    /*
     * when new child joins current AP, system will call the callback
     */
    esp_mesh_regist_usr_cb(esp_mesh_new_child_notify);

    /*
     * when node fails to rebuild mesh, system will call the callback
     */
    esp_mesh_regist_rebuild_fail_cb((esp_mesh_usr_callback)esp_mesh_rebuild_fail);
#endif

    return ESP_OK;
}
