/* Copyright 2018 Espressif Systems (Shanghai) PTE LTD
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//  mbcontroller.h
//  mbcontroller common header

#ifndef _MODBUS_CONTROLLER_COMMON
#define _MODBUS_CONTROLLER_COMMON

#include <stdint.h>                 // for standard int types definition
#include <stddef.h>                 // for NULL and std defines
#include "string.h"                 // for strerror()
#include "errno.h"                  // for errno
#include "esp_err.h"                // for error handling
#include "driver/uart.h"            // for uart port number defines
#include "sdkconfig.h"              // for KConfig options

#define MB_CONTROLLER_STACK_SIZE            (CONFIG_MB_CONTROLLER_STACK_SIZE)   // Stack size for Modbus controller
#define MB_CONTROLLER_PRIORITY              (CONFIG_MB_SERIAL_TASK_PRIO - 1)    // priority of MB controller task

// Default port defines
#define MB_DEVICE_ADDRESS   (1)             // Default slave device address in Modbus
#define MB_DEVICE_SPEED     (115200)        // Default Modbus speed for now hard defined
#define MB_UART_PORT        (UART_NUM_2)    // Default UART port number
#define MB_PAR_INFO_TOUT    (10)            // Timeout for get parameter info
#define MB_PARITY_NONE      (UART_PARITY_DISABLE)

#if CONFIG_MB_SERIAL_MASTER_RTU_ENABLED > 0 || CONFIG_MB_SERIAL_MASTER_ASCII_ENABLED > 0
#include "mbcontroller_master.h"
#else
#include "mbcontroller_slave.h"
#endif

#endif
