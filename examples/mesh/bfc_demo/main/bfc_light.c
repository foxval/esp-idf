/* Mesh Demo with BFC Server

 This example code is in the Public Domain (or CC0 licensed, at your option.)

 Unless required by applicable law or agreed to in writing, this
 software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 CONDITIONS OF ANY KIND, either express or implied.
 */

#include "esp_err.h"
#include "driver/gpio.h"

#define BFC_LIGHT_GPIO GPIO_NUM_0

esp_err_t mesh_bfc_set_gpio(int value)
{
    static bool inited = false;
    if (inited == false) {
        gpio_pad_select_gpio(BFC_LIGHT_GPIO);
        /* Set the GPIO as a push/pull output */
        gpio_set_direction(BFC_LIGHT_GPIO, GPIO_MODE_OUTPUT);
        inited = true;
    }
    gpio_set_level(BFC_LIGHT_GPIO, value);
    return ESP_OK;
}

esp_err_t mesh_bfc_set_light(int brightness)
{

    return ESP_FAIL;
}

esp_err_t mesh_bfc_get_light(int* brightness)
{

    return ESP_FAIL;
}
