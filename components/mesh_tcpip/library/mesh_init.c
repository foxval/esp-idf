#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event_loop.h"
#include "mesh.h"
#include "mesh_wifi.h"
#include "mesh_route.h"
#include "mesh_tcpip.h"
#include "mesh_config.h"
#include "mesh_common.h"
#include "mesh_parent.h"
#include "mesh_schedule.h"

void MESH_FUNC_ATTR esp32_mesh_event_set_cb(system_event_cb_t event_cb)
{
    esp_event_loop_set_cb(event_cb, NULL);
}

void MESH_FUNC_ATTR mesh_print_task_info()
{
#if 0
    static char t_info_buf[2048];
    MESH_MEMSET(t_info_buf, 0, sizeof(t_info_buf));
    vTaskList((char *)t_info_buf);
    MESH_PRINT(t_info_buf);
#endif
}

bool MESH_FUNC_ATTR mesh_wifi_init()
{
    static bool init = false;
    printf("%s\n", __func__);

    if (init)
        return true;
    init = true;

    mesh_print_task_info();

    ESP_ERROR_CHECK(nvs_flash_init());
    system_init();

    tcpip_adapter_init();
    ESP_ERROR_CHECK(tcpip_adapter_dhcps_stop(TCPIP_ADAPTER_IF_AP));

    ESP_ERROR_CHECK(esp_event_loop_init(mesh_event_cb, NULL));
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_FLASH));
    //ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));
    //ESP_ERROR_CHECK(esp_wifi_start());
    esp_wifi_set_mode(WIFI_MODE_APSTA);
    esp_wifi_start();

    printf("%s-exit\n", __func__);
    return true;
}
