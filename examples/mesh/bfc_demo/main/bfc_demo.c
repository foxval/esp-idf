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
#include "mesh_wifi.h"
#include "bfc_demo.h"

#define MESH_DISABLE_TEST (0)

void mesh_usr_task(void *pvParameter);
void mesh_enable_cb(enum mesh_op_result_t result);

extern void MESH_FUNC_ATTR mesh_bfc_start(void);

void mesh_enable_cb(enum mesh_op_result_t result)
{
    mesh_bfc_start();
}

void mesh_usr_task(void *pvParameter)
{
    esp32_mesh_enable(mesh_enable_cb, MESH_ONLINE);
    vTaskDelete(NULL);
}

void app_main(void)
{
    if (!mesh_wifi_init()) return;

    if (!mesh_usr_init()) return;

    xTaskCreate(mesh_usr_task, "mudt", 4096, NULL, 5, NULL);
}
