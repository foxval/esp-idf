/* ESP32-MESH Demo

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
#include "mesh_performance.h"

#define MESH_DISABLE_TEST (0)

void mesh_usr_task(void *pvParameter);
void mesh_enable_cb(enum mesh_op_result_t result);
#if MESH_DISABLE_TEST
void mesh_disable_cb(enum mesh_op_result_t result);
void MESH_FUNC_ATTR mesh_disable_cb(enum mesh_op_result_t result)
{
    printf("mesh disable result:%d, heap:%u\n", result, system_get_free_heap_size());
    xTaskCreate(mesh_usr_task, "mudt", 4096, NULL, 5, NULL);
}
#endif

void MESH_FUNC_ATTR mesh_enable_cb(enum mesh_op_result_t result)
{
    printf("mesh enable result:%d, heap:%u\n", result,
            system_get_free_heap_size());
#if MESH_DISABLE_TEST
    printf("disable mesh\n");
    esp32_mesh_disable(mesh_disable_cb);
#endif
    esp32_mesh_set_wifi_retry_delay(MESH_WIFI_RETRY_DELAY);
    mesh_performance_start();
}

void MESH_FUNC_ATTR mesh_usr_task(void *pvParameter)
{
    printf("mesh demo, free heap:%u\n", system_get_free_heap_size());
    esp32_mesh_enable(mesh_enable_cb, MESH_ONLINE);
    printf("mesh demo delete!\n");
    vTaskDelete(NULL);
}

void MESH_FUNC_ATTR app_main()
{
    if (!mesh_wifi_init()) return;
    if (!mesh_usr_init()) return;
    xTaskCreate(mesh_usr_task, "mudt", 4096, NULL, 5, NULL);
}
