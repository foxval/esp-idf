// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
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

//  mbcontroller.c
//  Implementation of common mbcontroller interface

#include <stdint.h>                 // for standard int types definition
#include <stddef.h>                 // for NULL and std defines
#include "soc/soc.h"                // for BITN definitions
#include "sdkconfig.h"              // for KConfig options
#include "mbcontroller.h"

/* ----------------------- Defines ------------------------------------------*/

static mb_controller_object_t mb_controller_obj = { 0 };

esp_err_t mbcontroller_init(mb_stack_type_t stack_type) {
    esp_err_t error = ESP_FAIL;
    mb_controller_obj.stack_type = stack_type;

#if CONFIG_MB_MASTER_RTU_ENABLED > 0 || CONFIG_MB_MASTER_ASCII_ENABLED > 0
    error = mbcontroller_init_master((void*)&mb_controller_obj.stack_handler);
#else
    error = mbcontroller_init_slave((void*)&mb_controller_obj.stack_handler);
#endif
    return error;
}

