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

//  mbcontroller.h
//  Implementation of the MbController

#ifndef _MODBUS_CONTROLLER_COMMON
#define _MODBUS_CONTROLLER_COMMON

#include <stdint.h>                 // for standard int types definition
#include <stddef.h>                 // for NULL and std defines
#include "string.h"                 // for strerror()
#include "errno.h"                  // for errno
#include "esp_err.h"                // for error handling
#include "sdkconfig.h"              // for KConfig options

#define MB_CONTROLLER_STACK_SIZE            (CONFIG_MB_CONTROLLER_STACK_SIZE) // Stack size for Modbus controller
#define MB_CONTROLLER_PRIORITY              (CONFIG_MB_SERIAL_TASK_PRIO - 1) // priority of MB controller task

// Default port defines
#define MB_DEVICE_ADDRESS   (1)             // Default slave device address in Modbus
#define MB_DEVICE_SPEED     (115200)        // Default Modbus speed for now hard defined
#define MB_UART_PORT        (UART_NUM_2)    // Default UART port number
#define MB_PAR_INFO_TOUT    (10)            // Timeout for get parameter info
#define MB_PARITY_NONE      (UART_PARITY_DISABLE)

#if CONFIG_MB_MASTER_RTU_ENABLED > 0 || CONFIG_MB_MASTER_ASCII_ENABLED > 0
#include "mbcontroller_master.h"
#else
#include "mbcontroller_slave.h"
#endif

#define MB_CONTROLLER_TAG "MB_CONTROLLER"

#define MB_CHECK(a, ret_val, str, ...) \
    if (!(a)) { \
        ESP_LOGE(MB_CONTROLLER_TAG, "%s(%u): " str, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
        return (ret_val); \
    }

#define MB_ASSERT(con) do { \
        if (!(con)) { ESP_LOGE(MB_CONTROLLER_TAG, "assert errno:%d, errno_str: !(%s)", errno, strerror(errno)); assert(0 && #con); } \
    } while (0)

// The Macros below handle the endianness while transfer N byte data into buffer
#define _XFER_4_RD(dst, src) { \
    *(uint8_t *)(dst)++ = *(uint8_t*)(src + 1); \
    *(uint8_t *)(dst)++ = *(uint8_t*)(src + 0); \
    *(uint8_t *)(dst)++ = *(uint8_t*)(src + 3); \
    *(uint8_t *)(dst)++ = *(uint8_t*)(src + 2); \
    (src) += 4; \
}

#define _XFER_2_RD(dst, src) { \
    *(uint8_t *)(dst)++ = *(uint8_t *)(src + 1); \
    *(uint8_t *)(dst)++ = *(uint8_t *)(src + 0); \
    (src) += 2; \
}

#define _XFER_4_WR(dst, src) { \
    *(uint8_t *)(dst + 1) = *(uint8_t *)(src)++; \
    *(uint8_t *)(dst + 0) = *(uint8_t *)(src)++; \
    *(uint8_t *)(dst + 3) = *(uint8_t *)(src)++; \
    *(uint8_t *)(dst + 2) = *(uint8_t *)(src)++ ; \
}

#define _XFER_2_WR(dst, src) { \
    *(uint8_t *)(dst + 1) = *(uint8_t *)(src)++; \
    *(uint8_t *)(dst + 0) = *(uint8_t *)(src)++; \
}

/* ----------------------- Defines ------------------------------------------*/

/**
 * @brief Type of Modbus stack
 */
typedef enum
{
    MB_SERIAL_MASTER = 0,                /*!< Modbus master mode. */
    MB_SERIAL_SLAVE = 1,                 /*!< Modbus slave mode. */
} mb_stack_type_t;

typedef void* mb_stack_handler_t;         /*!< Stack handler type. */

/**
 * @brief Device object structure
 */
typedef struct {
    mb_stack_type_t stack_type;                 /*!< Stack type */
    mb_stack_handler_t stack_handler;           /*!< Modbus communication information */
} mb_controller_object_t;

// Common interface functions declarations for both slave and master

/**
 * @brief Initialize Modbus controller and stack
 *
 * @return
 *     - ESP_OK   Success
 *     - ESP_FAIL Parameter error
 */
esp_err_t mbcontroller_init(mb_stack_type_t stack_type);

/**
 * @brief Destroy Modbus controller and stack
 *
 * @return
 *     - ESP_OK   Success
 *     - ESP_FAIL Parameter error
 */
esp_err_t (*mbcontroller_destroy)(void);

/**
 * @brief Start Modbus communication stack
 *
 * @return
 *     - ESP_OK   Success
 *     - ESP_ERR_INVALID_ARG Modbus stack start error
 */
esp_err_t (*mbcontroller_start)(void);

/**
 * @brief Set Modbus communication parameters for the controller
 *
 * @param comm_info Communication parameters structure.
 *
 * @return
 *     - ESP_OK Success
 *     - ESP_ERR_INVALID_ARG Incorrect parameter data
 */
esp_err_t (*mbcontroller_setup)(void* comm_info);

#endif
