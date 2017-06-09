// Copyright 2015-2017 Espressif Systems (Shanghai) PTE LTD
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

#ifndef __MESH_COMMON_H__
#define __MESH_COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "malloc.h"
#include "string.h"
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_err.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include "esp_wifi_internal.h"

/*******************************************************
 *                Constants
 *******************************************************/
#define MESH_DEBUG ets_printf

/*******************************************************
 *                Type Definitions
 *******************************************************/

/*******************************************************
 *                Structures
 *******************************************************/

/*******************************************************
 *                Variables Declarations
 *******************************************************/

/*******************************************************
 *                Function Definitions
 *******************************************************/
void esp_mesh_enable_dhcp(void);
void esp_mesh_disable_dhcp(void);

#endif /* __MESH_COMMON_H__ */
