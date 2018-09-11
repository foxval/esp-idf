// Copyright 2016-2017 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include "pm_trace.h"
#include "driver/gpio.h"
#include "soc/gpio_reg.h"
#ifdef CONFIG_CHIP_IS_ESP32C
#include "rom/ets_sys.h"
#endif

/* GPIOs to use for tracing of esp_pm events.
 * Two entries in the array for each type, one for each CPU.
 * Feel free to change when debugging.
 */
#ifdef CONFIG_CHIP_IS_ESP32
static const int DRAM_ATTR s_trace_io[] = {
        BIT(4),  BIT(5),  // ESP_PM_TRACE_IDLE
        BIT(16), BIT(17), // ESP_PM_TRACE_TICK
        BIT(18), BIT(18), // ESP_PM_TRACE_FREQ_SWITCH
        BIT(19), BIT(19), // ESP_PM_TRACE_CCOMPARE_UPDATE
        BIT(25), BIT(26), // ESP_PM_TRACE_ISR_HOOK
        BIT(27), BIT(27), // ESP_PM_TRACE_SLEEP
};
#elif defined CONFIG_CHIP_IS_ESP32C
#ifdef CONFIG_HARDWARE_IS_FPGA
static const int DRAM_ATTR s_trace_io[] = {
        1, 0, // ESP_PM_TRACE_WIFI
        2, 0, // ESP_PM_TRACE_IDLE
        3, 0, // ESP_PM_TRACE_SLEEP
        4, 0, // ESP_PM_TRACE_REJECT
        5, 0, // ESP_PM_TRACE_TBTT
        8,0,  // ESP_PM_TRACE_BEACON
        21,0, // ESP_PM_TRACE_ISR
};
#else
static const int DRAM_ATTR s_trace_io[] = {
        2, 0, // ESP_PM_TRACE_WIFI
        3, 0, // ESP_PM_TRACE_IDLE
        4, 0, // ESP_PM_TRACE_SLEEP
        5, 0, // ESP_PM_TRACE_REJECT
        6, 0, // ESP_PM_TRACE_TBTT
        7, 0, // ESP_PM_TRACE_BEACON
        8, 0, // ESP_PM_TRACE_ISR
};
#endif
#endif

void esp_pm_trace_init()
{
#ifdef CONFIG_CHIP_IS_ESP32
    for (size_t i = 0; i < sizeof(s_trace_io)/sizeof(s_trace_io[0]); ++i) {
        int io = __builtin_ffs(s_trace_io[i]);
        if (io == 0) {
            continue;
        }
        gpio_set_direction(io - 1, GPIO_MODE_OUTPUT);
    }
#elif defined CONFIG_CHIP_IS_ESP32C
    for (size_t i = 0; i < sizeof(s_trace_io)/sizeof(s_trace_io[0]); ++i) {
        gpio_pad_pullup(s_trace_io[2 * i]);
        GPIO_OUTPUT_SET(s_trace_io[2 * i], 1);
    }
    //esp_pm_trace_test();
#endif
}

void IRAM_ATTR esp_pm_trace_enter(esp_pm_trace_event_t event, int core_id)
{
#ifdef CONFIG_CHIP_IS_ESP32
    REG_WRITE(GPIO_OUT_W1TS_REG, s_trace_io[2 * event + core_id]);
#elif defined CONFIG_CHIP_IS_ESP32C
    GPIO_OUTPUT_SET(s_trace_io[2 * event + core_id], 0);
#endif
}

void IRAM_ATTR esp_pm_trace_exit(esp_pm_trace_event_t event, int core_id)
{
#ifdef CONFIG_CHIP_IS_ESP32
    REG_WRITE(GPIO_OUT_W1TC_REG, s_trace_io[2 * event + core_id]);
#elif defined CONFIG_CHIP_IS_ESP32C
    GPIO_OUTPUT_SET(s_trace_io[2 * event + core_id], 1);
#endif
}

#ifdef CONFIG_CHIP_IS_ESP32C
void esp_pm_trace_test(void)
{
    for (size_t i = 0; i < 0x7fffffff; i++) {
        for (size_t j = 0; j < sizeof(s_trace_io)/sizeof(s_trace_io[0]); j++) {
        	GPIO_OUTPUT_SET(s_trace_io[2 * j], !!(i&(1<<j)));
        }
        ets_delay_us(1000);
    }
}
#endif
