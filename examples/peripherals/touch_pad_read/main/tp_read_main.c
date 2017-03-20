/* Touch Pad Read Example

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

#include "driver/touch_pad.h"


/*
  Read values sensed at all available touch pads.
  Print out values in a loop on a serial monitor.
 */
void touch_pad_read_task(void *pvParameter)
{
    while (1) {
        uint16_t touch_value;
        for (int i=0; i<TOUCH_PAD_MAX; i++) {
            ESP_ERROR_CHECK(touch_pad_read(i, &touch_value));
            printf("T%d:%4d ", i, touch_value);
        }
        printf("\n");
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    nvs_flash_init();

    // Initialize touch pad peripheral
    touch_pad_init();

    // Start task to read values sensed by pads
    xTaskCreate(&touch_pad_read_task, "touch_pad_read_task", 2048, NULL, 5, NULL);

}
