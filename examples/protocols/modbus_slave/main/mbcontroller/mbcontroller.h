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
//  Implementation of the Class MbController

#if !defined(_CMODBUS_CONTROLLER)
#define _CMODBUS_CONTROLLER

#include <stdint.h>                 // for standard int types definition
#include <stddef.h>                 // for NULL and std defines
#include <string.h>                 // for memset
#include <limits.h>                 // for ULONG_MAX in notify
#include <stdio.h>
#include "freertos/FreeRTOS.h"      // for task creation and queue access
#include "freertos/task.h"
#include "freertos/event_groups.h"  // for event groups

#include "driver/gpio.h"            // for pin manipulation for debugging
#include "sdkconfig.h"
#include "mb.h"                     // for mb types definition
#include "mbutils.h"                // for mbutils functions definition

#include "lookup_tables.h"          // for parameter discriptions
#include "nvmanager.h"              // for mb nv manager access
#include "deviceparams.h"           // for device parameters structure

/* ----------------------- Defines ------------------------------------------*/

#define REG_DISCRETE_INPUT_START        (0)
#define REG_DISCRETE_INPUT_NREGS        (16)

#define REG_INPUT_START                 (0) // 1000
//#define REG_INPUT_NREGS                 (8)

#define REG_HOLDING_START               (0) // 0x0401
//#define REG_HOLDING_NREGS               (33640)

#define REG_COILS_START                 (0) // 1000
//#define REG_COILS_NREGS                 (50) // 1000

#define MBCONTROLLER_STACK_SIZE         (configMINIMAL_STACK_SIZE * 4)
#define MBCONTROLLER_PRIORITY           (configMAX_PRIORITIES - 4)
#define MBCONTROLLER_NOTIFY_QUEUE_SIZE  (10)
#define MBCONTROLLER_NOTIFY_TIMEOUT     (10)

// Default port defines
#define MB_DEVICE_ADDRESS   (1) // Device address in Modbus
#define MB_DEVICE_SPEED     (115200) // Modbus speed for now hard defined
#define MB_UART_PORT        (2)
#define MB_IO_LED           (GPIO_NUM_18) // pin manipulation for debugging

// Event group for parameters notification
typedef enum
{
    MB_EVENT_NO_EVENTS = 0x00,
    MB_EVENT_HOLDING_REG_WR = BIT0,         /*!< Modbus Event Write Holding registers. */
    MB_EVENT_HOLDING_REG_RD = BIT1,         /*!< Modbus Event Read Holding registers. */
    MB_EVENT_INPUT_REG_RD = BIT3,           /*!< Modbus Event Read Input registers. */
    MB_EVENT_COILS_WR = BIT4,               /*!< Modbus Event Write Coils. */
    MB_EVENT_COILS_RD = BIT5,               /*!< Modbus Event Read Coils. */
    MB_EVENT_DISCRETE_RD = BIT6,               /*!< Modbus Event Read Discrete bits. */
    MB_EVENT_UNKNOWN = BIT7
} eMbEventGroup;

// Handles the endianness while transfer 4 byte data into buffer
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

// This is section for C++ defines of the class, above is shared
#ifdef __cplusplus

class MbController : public NvManager
{
public:
        MbController();
        virtual ~MbController();
        void init(void);
        void run(void);
        esp_err_t start(void);
        esp_err_t setMbParameters(eMBMode eMode, uint8_t ucSlaveAddress, \
                                    uint8_t ucPort, uint32_t ulBaudRate, eMBParity eParity );
        tLookupRegisters* findParameter(uint16_t parIndex);
        esp_err_t isParamCorrect(uint16_t parIndex);
        esp_err_t processParameter(uint16_t parIndex);
        eMBErrorCode readHoldingRegs(uint8_t* pucRegBuffer,  uint16_t iRegIndex, uint16_t usNRegs);
        eMBErrorCode writeHoldingRegs(uint8_t* pucRegBuffer,  uint16_t iRegIndex, uint16_t usNRegs);
        eMBErrorCode processHoldingRegs(uint8_t* pucRegBuffer, uint16_t usAddress, uint16_t usNRegs, eMBRegisterMode eMode );
        eMBErrorCode processCoils(uint8_t* pucRegBuffer, uint16_t usAddress, uint16_t usNCoils, eMBRegisterMode eMode );
        eMBErrorCode processInputs(uint8_t* pucRegBuffer, uint16_t usAddress, uint16_t usNRegs );
        eMBErrorCode processDiscretes(uint8_t* pucRegBuffer, uint16_t usAddress, uint16_t usNDiscrete);

private:
        //tLookupRegisters const* pLookupTable;
        //uint16_t usRegHoldingStart;
        //uint16_t usRegInputStart;
        //uint16_t usRegCoilsStart;
        //uint16_t usRegDiscreteStart;
        uint16_t usRegHoldingNregs;
        uint16_t usRegInputNregs;
        uint16_t usRegCoilNregs;
        //uint16_t usRegCoilsBuf[REG_COILS_NREGS];
        uint16_t* usRegCoilsBuf;

        uint16_t usRegDiscreteBuf[REG_DISCRETE_INPUT_NREGS];
        tInputRegParams* usRegInputBuf;
        uint8_t ucMbType;
        uint8_t ucMbAddress;
        uint8_t ucMbPort;
        uint32_t ulMbSpeed;
        uint16_t usMbParity;
        uint8_t started;
};

#else

// read/write register wrapper function
uint8_t mbRegRwCheckFunc(void* param, void* buffer);
uint8_t mbFindRegister(uint16_t parIndex);

extern void* pMBControllerTaskHandle;

/**
 * @brief Initiate modbus controller class
 *
 * @param none
 *
 * @return
 *     - ESP_OK   Success
 *     - ESP_FAIL Parameter error
 */
esp_err_t mbcontroller_init(void);

/**
 * @brief Setup Modbus communication parameters and starts communication
 *
 * @param none
 *
 * @return
 *     - ESP_OK   Success
 *     - ESP_FAIL Parameter error
 */
esp_err_t mbcontroller_start(void);

/**
 * @brief Set modbus communication parameters and start stack
 *
 * @param eMode MB_RTU, MB_ASCII
 * @param ucSlaveAddress Slave address of this controller on Modbus
 * @param ucPort - UART serial port number
 * @param ulBaudRate - UART serial port baud rate
 * @param eParity - UART serial port parity option MB_PAR_NONE, MB_PAR_ODD, MB_PAR_EVEN
 *
 * @return
 *     - ESP_OK   Success
 *     - ESP_FAIL Parameter error
 */
esp_err_t mbcontroller_setup(eMBMode eMode, uint8_t ucSlaveAddress, \
                                    uint8_t ucPort, uint32_t ulBaudRate, eMBParity eParity );
/**
 * @brief Get notification when parameter is written by modbus stack
 *        This is task blocking function.
 *
 * @param regInfo pointer to tLookupRegisters element which describes parameter
 *
 * @return
 *     - ESP_OK   Success
 *     - ESP_FAIL Parameter error
 */
esp_err_t mbcontroller_get_notification(tLookupRegisters** regInfo);

// Write parameter param - pointer to parameter field in modbus parameter structure
esp_err_t mbcontroller_write_parameter(void* param, void* paramData);

/**
 * @brief Wait for specific event on parameter change. The parameter defines
 *        mask to wait.
 *
 * @param group event bit mask to wait for change
 *
 * @return
 *     - eMbEventGroup event bits triggered
 */
eMbEventGroup mbcontroller_check_event(eMbEventGroup group);


eMBErrorCode eMBRegCoilsCB( UCHAR * pucRegBuffer,
                           USHORT usAddress,
                           USHORT usNCoils,
                           eMBRegisterMode eMode );

eMBErrorCode eMBRegDiscreteCB( UCHAR * pucRegBuffer,
                              USHORT usAddress,
                              USHORT usNDiscrete );

eMBErrorCode eMBRegHoldingCB( UCHAR * pucRegBuffer,
                             USHORT usAddress,
                             USHORT usNRegs,
                             eMBRegisterMode eMode );

#endif // __cplusplus

#endif // !defined(_CMODBUS_CONTROLLER)
