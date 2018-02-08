// Copyright 2017-2018 Espressif Systems (Shanghai) PTE LTD
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

#include "esp_err.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "mesh_light.h"

/*******************************************************
 *                Constants
 *******************************************************/
/* RGB configuration on ESP-WROVER-KIT board */
#define LEDC_IO_0    (0)
#define LEDC_IO_1    (2)
#define LEDC_IO_2    (4)
#define LEDC_IO_3    (5)

/*******************************************************
 *                Variable Definitions
 *******************************************************/
static bool bool_light_inited = false;

/*******************************************************
 *                Function Definitions
 *******************************************************/
esp_err_t mesh_light_init(void)
{
    if (bool_light_inited == true) {
        return ESP_OK;
    }
    bool_light_inited = true;

    ledc_timer_config_t ledc_timer = {
        //set timer counter bit number
        .bit_num = LEDC_TIMER_13_BIT,
        //set frequency of pwm
        .freq_hz = 5000,
        //timer mode,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        //timer index
        .timer_num = LEDC_TIMER_0
    };
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel = {
        //set LEDC channel 0
        .channel = LEDC_CHANNEL_0,
        //set the duty for initialization.(duty range is 0 ~ ((2**bit_num)-1)
        .duty = 100,
        //GPIO number
        .gpio_num = LEDC_IO_0,
        //GPIO INTR TYPE, as an example, we enable fade_end interrupt here.
        .intr_type = LEDC_INTR_FADE_END,
        //set LEDC mode, from ledc_mode_t
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        //set LEDC timer source, if different channel use one timer,
        //the frequency and bit_num of these channels should be the same
        .timer_sel = LEDC_TIMER_0
    };
    //set the configuration
    ledc_channel_config(&ledc_channel);

    //config ledc channel1
    ledc_channel.channel = LEDC_CHANNEL_1;
    ledc_channel.gpio_num = LEDC_IO_1;
    ledc_channel_config(&ledc_channel);
    //config ledc channel2
    ledc_channel.channel = LEDC_CHANNEL_2;
    ledc_channel.gpio_num = LEDC_IO_2;
    ledc_channel_config(&ledc_channel);
    //config ledc channel3
    ledc_channel.channel = LEDC_CHANNEL_3;
    ledc_channel.gpio_num = LEDC_IO_3;
    ledc_channel_config(&ledc_channel);

    //initialize fade service.
    ledc_fade_func_install(0);
    //default on
    mesh_gpio_set(RGB_LIGHT_INIT);
    return ESP_OK;
}

esp_err_t mesh_gpio_set(int value)
{
    switch (value) {
    case RGB_LIGHT_RED:
        /* Red */
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 3000);
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, 0);
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2, 0);
        break;
    case RGB_LIGHT_GREEN:
        /* Green */
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 0);
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, 3000);
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2, 0);
        break;
    case RGB_LIGHT_BLUE:
        /* Blue */
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 0);
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, 0);
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2, 3000);
        break;
    case RGB_LIGHT_YELLOW:
        /* Yellow */
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 3000);
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, 3000);
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2, 0);
        break;
    case RGB_LIGHT_PINK:
        /* Pink */
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 3000);
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, 0);
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2, 3000);
        break;
    case RGB_LIGHT_INIT:
        /* can't say */
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 0);
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, 3000);
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2, 3000);
        break;
    case RGB_LIGHT_WARNING:
        /* warning */
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 3000);
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, 3000);
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2, 3000);
        break;
    default:
        /* off */
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 0);
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, 0);
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2, 0);
    }

    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2);

    return ESP_OK;
}

esp_err_t mesh_gpio_get(int *value)
{
    int val_0 = ledc_get_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
    if (val_0 == 0) {
        *value = 0;
    } else {
        *value = 100;
    }
    return ESP_OK;
}

