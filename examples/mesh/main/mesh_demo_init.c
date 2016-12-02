/* ESP32-MESH Demo Init

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"

#include "mesh.h"
#include "mesh_wifi.h"
#include "mesh_usr_config.h"

bool mesh_router_init();
bool mesh_usr_init();

bool MESH_FUNC_ATTR mesh_router_init()
{
    wifi_sta_config_t sta;

    MESH_PRINT("mesh version:\n");
    esp32_mesh_print_ver();

    MESH_MEMSET(&sta, 0, sizeof(sta));
    MESH_MEMCPY(sta.ssid, MESH_ROUTER_SSID, MESH_STRLEN(MESH_ROUTER_SSID));
    MESH_MEMCPY(sta.password, MESH_ROUTER_PASSWD, MESH_STRLEN(MESH_ROUTER_PASSWD));

    if (!esp32_mesh_set_router(&sta)) {
        MESH_PRINT("set router fail\n");
        return false;
    }

    return true;
}

bool MESH_FUNC_ATTR mesh_usr_init()
{
    /*
     * set the AP password of mesh node
     */
    if (!esp32_mesh_encrypt_init(MESH_AUTH, (uint8_t *)MESH_PASSWD, MESH_STRLEN(MESH_PASSWD))) {
        MESH_PRINT("set pw fail\n");
        return false;
    }

    /*
     * if you want set max_hop > 4
     * please make the heap is avaliable
     * mac_route_table_size = (4^max_hop - 1)/3 * 6
     */
    if (!esp32_mesh_set_max_hops(MESH_MAX_HOP)) {
        //MESH_PRINT("fail, max_hop:%d\n", esp32_mesh_get_max_hops());
        MESH_PRINT("fail, max_hop:%d\n", MESH_MAX_HOP);
        return false;
    }

    /*
     * mesh_ssid_prefix
     * mesh_group_id and mesh_ssid_prefix represent mesh network
     */
#if 0
    if (!esp32_mesh_set_ssid_prefix(MESH_SSID_PREFIX, MESH_STRLEN(MESH_SSID_PREFIX))) {
        MESH_PRINT("set prefix fail\n");
        return false;
    }
#endif
    /*
     * mesh_group_id
     * mesh_group_id and mesh_ssid_prefix represent mesh network
     */
    if (!esp32_mesh_group_id_init((uint8_t *)MESH_GROUP_ID, sizeof(MESH_GROUP_ID))) {
        MESH_PRINT("set grp id fail\n");
        return false;
    }

    /*
     * set cloud server ip and port for mesh node
     */
    if (!esp32_mesh_server_init((ip_addr_t *)MESH_SERVER_IP, MESH_SERVER_PORT)) {
        MESH_PRINT("server_init fail\n");
        return false;
    }

    if (!mesh_router_init()) {
        MESH_PRINT("router init fail\n");
        return false;
    }
#if 0
    /*
     * when new child joins current AP, system will call the callback
     */
    esp32_mesh_regist_usr_cb(esp_mesh_new_child_notify);

    /*
     * when node fails to rebuild mesh, system will call the callback
     */
    esp32_mesh_regist_rebuild_fail_cb((esp32_mesh_usr_callback)esp_mesh_rebuild_fail);
#endif
    return true;
}
