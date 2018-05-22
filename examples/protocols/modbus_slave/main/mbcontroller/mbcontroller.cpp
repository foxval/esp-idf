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

//  mbcontroller.cpp
//  Implementation of the Class MbController

#include "mbcontroller.h"

#ifdef ESP_PLATFORM
//#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG
#include "esp_log.h"
static const char* TAG = "MODBUS_CONTROLLER";
#else
#define ESP_LOGD(...)
#endif

// Note: This class uses mixed coding standard due to legacy code used from other modules

#define MB_CHECK(a, str, ret_val) \
    if (!(a)) { \
        ESP_LOGE(TAG,"%s(%d): %s", __FUNCTION__, __LINE__, str); \
        return (ret_val); \
    }

MbController* pMbController = NULL;
static TaskHandle_t mbControllerTaskHandle = NULL;
static QueueHandle_t mbControllerNotificationQueueHandle = NULL;
static EventGroupHandle_t mbControllerEventGroup = NULL;

// Wrapper for the task
static void modbus_task(void *pvParameters) {
    assert(pMbController != NULL);
    pMbController->run();
}

MbController::MbController() : usRegInputBuf(&inputRegParams)
{
    ucMbType = MB_RTU;
    ucMbAddress = MB_DEVICE_ADDRESS;
    ucMbPort = MB_UART_PORT;
    ulMbSpeed = MB_DEVICE_SPEED;
    usMbParity = MB_PAR_NONE;

    // The modbus holding regs start address
    //usRegHoldingStart = REG_HOLDING_START;
    //usRegCoilsStart = REG_COILS_START;
    //usRegInputStart = REG_INPUT_START;


    // Set initial state of buffer
    //memset((void*)&usRegHoldingBuf, 0x00, REG_HOLDING_NREGS*2);
    //memset((void*) &usRegCoilsBuf, 0x00, REG_COILS_NREGS * 2);
    usRegCoilsBuf = ((uint16_t*)&coilRegParams);
    usRegCoilNregs = (sizeof(coilRegParams) >> 1);
    assert(usRegCoilNregs >= 1);

    usRegInputBuf->dataChan0 = 1.34; // todo: default values for debugging
    usRegInputBuf->dataChan1 = 2.56; // change later to NAN
    usRegInputBuf->dataChan2 = 3.78;
    usRegInputBuf->dataChan3 = 4.90;
    // Set number of registers for input registers
    usRegInputNregs = (sizeof(inputRegParams) >> 1);
    //pLookupTable = g_stLookupRegisters;
    tLookupRegisters reg = pLookupTable[g_numLookupRegisters - 1];

    // Get number of holding regs = last parameter modbus offset lookup table
    usRegHoldingNregs = reg.offset + (reg.size >> 1);

    pMbController = this;
    // Initialization of active context of the modbus controller
    init();

    started = 0;
}

MbController::~MbController()
{
    // We should not get here because this class will not be deleted once activated
    assert(0);
}

esp_err_t MbController::setMbParameters(eMBMode eMode, uint8_t ucSlaveAddress,
        uint8_t ucPort, uint32_t ulBaudRate, eMBParity eParity)
{
    MB_CHECK(((eMode == MB_RTU) || (eMode == MB_ASCII)), "mb wrong mode",
            ESP_FAIL);
    MB_CHECK((ucSlaveAddress <= MB_ADDRESS_MAX), "mb wrong slave address",
            ESP_FAIL);
    MB_CHECK((ucPort <= UART_NUM_2), "mb wrong port", ESP_FAIL);
    MB_CHECK((eParity <= MB_PAR_EVEN), "mb wrong parity", ESP_FAIL);
    ucMbType = eMode;
    ucMbAddress = ucSlaveAddress;
    ucMbPort = ucPort;
    ulMbSpeed = ulBaudRate;
    usMbParity = eParity;
    return ESP_OK;
}

// Goes through all lines in lookup table to find information about parameter
tLookupRegisters* MbController::findParameter(uint16_t parIndex)
{
    tLookupRegisters* pItem = NULL;
    uint16_t index;
    bool found = FALSE;

    // The cycle for all lines in lookup table to get correct description
    // of system parameter parIndex
    for (index = 0, pItem = (tLookupRegisters*) pLookupTable;
            index < g_numLookupRegisters; index++, pItem++) {
        if ((pItem != NULL) && (parIndex == pItem->offset)) {
            // if parameter index found in the lookup table then stop cycle
            found = TRUE;
            break;
        }
    }
    if (found != TRUE) {
        pItem = NULL;
    }

    // NULL - means not found
    return pItem;
}

esp_err_t MbController::isParamCorrect(uint16_t parIndex)
{
    return ESP_OK;
}

// Executes write check or other options associated with each parameter
esp_err_t MbController::processParameter(uint16_t parIndex)
{
    tLookupRegisters* pRegInfo = NULL;
    esp_err_t err = ESP_FAIL;
    pRegInfo = findParameter(parIndex);

    if (pRegInfo != NULL) {
        // The function return 0 if ok cast to esp_err_t
        err = (esp_err_t) pRegInfo->cmdFuncPtr((uint8_t*) pRegInfo, NULL);
    }
    return err;
}

// Initialize of active object task and its parameters
void MbController::init(void)
{
    BaseType_t status = 0;
    // Initialization of modbus NV manager to store MB parameters
    esp_err_t error = oNvManager.initNv();
    ESP_ERROR_CHECK(error);
    // Read initial values of MB parameters into device parameters structure
    error = oNvManager.readAllFromNv();
    //error = ESP_ERR_NVS_NOT_FOUND;
    if (error == ESP_ERR_NVS_NOT_FOUND) { // If parameter name space is not initialized
        error = oNvManager.initDefault();
        ESP_ERROR_CHECK(error);
        error = oNvManager.readAllFromNv();
    }

    // We create the active object task here but it will start later
    status = xTaskCreate(&modbus_task, "modbus_task",
                        MBCONTROLLER_STACK_SIZE,
                        NULL,
                        MBCONTROLLER_PRIORITY, &mbControllerTaskHandle);

    assert(status == pdPASS);
    assert(mbControllerTaskHandle != NULL);

    // Parameter change notification queue
    mbControllerNotificationQueueHandle = xQueueCreate(
            MBCONTROLLER_NOTIFY_QUEUE_SIZE, sizeof(tLookupRegisters*));
    assert(mbControllerNotificationQueueHandle != NULL);

    mbControllerEventGroup = xEventGroupCreate();
    assert(mbControllerEventGroup != NULL);
}

// Helper method to read holding registers
eMBErrorCode MbController::readHoldingRegs(uint8_t* pucRegBuffer,
        uint16_t iRegIndex, uint16_t usNRegs)
{
    assert(pucRegBuffer != NULL);
    assert(usNRegs >= 1);
    eMBErrorCode eStatus = MB_ENOERR;
    tLookupRegisters* pRegInfo = NULL;
    uint8_t* parAddress = NULL;
    const char* keyName = NULL;
    uint8_t nvParamData[24] = { 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0 };

    while ((usNRegs > 0)) {
        // Get parameter descriptor from object dictionary
        // for each read parameter based on start register index
        pRegInfo = findParameter(iRegIndex);
        if (pRegInfo != NULL) {
            // Parameter is found in lookup table then start its write check function
            // pRegInfo->cmdFuncPtr(pRegInfo, pucRegBuffer);
            // Read NV parameter directly from memory if it does't have allocated space
            if ((pRegInfo->paramOffset == 0)
                    && (pRegInfo->access & LKUP_ACCESS_TYPE_NV)) {
                parAddress = (uint8_t*) &nvParamData[0];
                // Todo: leave it with assert check for now
                //assert(pNvManager->readParameter(pRegInfo, parAddress) != 0);
            } else { /*if(pRegInfo->paramOffset != 0)*/
                // Else initialize storage address to OD storage field address
                parAddress = GET_PARAMETER_ADDRESS(pRegInfo);
                assert(parAddress != NULL);
            }
            // uint16_t parOffset = pRegInfo->offset;
            // Get parameter size and type from Data Dictionary
            uint8_t parSize = pRegInfo->size;
            uint8_t parType = pRegInfo->type;
            keyName = pRegInfo->parKey;
            ESP_LOGI(TAG, "READ Param: %s\r\n", (const char*) keyName);
            // Process each parameter according to type in lookup table
            while (parSize > 0) {
                switch (parType) {
                case LKUP_TYPE_U16:
                    _XFER_2_RD(pucRegBuffer, parAddress)
                    ;
                    iRegIndex++;
                    parSize -= 2;
                    usNRegs--;
                    break;

                case LKUP_TYPE_U8:
                    *pucRegBuffer++ = (uint8_t) (parAddress[1]);
                    *pucRegBuffer++ = 0;
                    iRegIndex++;
                    parSize -= 1;
                    usNRegs--;
                    break;

                case LKUP_TYPE_U32:
                    _XFER_4_RD(pucRegBuffer, parAddress)
                    ;
                    iRegIndex += 2;
                    parSize -= 4;
                    usNRegs -= 2;
                    break;

                case LKUP_TYPE_FLOAT:
                    _XFER_4_RD(pucRegBuffer, parAddress)
                    ;
                    iRegIndex += 2;
                    parSize -= 4;
                    usNRegs -= 2;
                    break;

                case LKUP_TYPE_ASCII:
                    while (parSize > 0) {
                        _XFER_2_RD(pucRegBuffer, parAddress);
                        parAddress += 2;
                        //pucRegBuffer += 2;
                        iRegIndex++;
                        parSize -= 2;
                        usNRegs--;
                    }
                    break;

                default:
                    // We don't read unsupported type of parameter
                    assert(0);
                    break;
                } // switch(parType)
            } //while(parSize > 0)
        } else { // (pRegInfo == NULL)
            eStatus = MB_ENOREG;
            break;
        }
    } // while((usNRegs > 0))
    return eStatus;
}

// Class helper method to handle parameter write request
eMBErrorCode MbController::writeHoldingRegs(uint8_t* pucRegBuffer,
        uint16_t iRegIndex, uint16_t usNRegs)
{
    assert(pucRegBuffer != NULL);
    assert(usNRegs > 0);
    eMBErrorCode eStatus = MB_ENOERR;
    tLookupRegisters* pRegInfo = NULL;
    uint8_t* parAddress = NULL;
    const char* keyName = NULL;
    uint8_t nvParamData[24] = { 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0 };
    while ((usNRegs > 0)) {
        pRegInfo = findParameter(iRegIndex);
        if (pRegInfo != NULL) {
            // Parameter is found in the lookup table => execute write check function
            // pRegInfo->cmdFuncPtr(pRegInfo, pucRegBuffer);
            // Write parameter with NV attribute directly to NV memory
            // because it does't have RAM storage space allocated
            if ((pRegInfo->paramOffset == 0)
                    && (pRegInfo->access & LKUP_ACCESS_TYPE_NV)) {
                // Just initiate parameter buffer address
                parAddress = (uint8_t*) &nvParamData[0];
            } else {
                // Else initialize storage address to device parameters structure field
                parAddress = GET_PARAMETER_ADDRESS(pRegInfo);
            }
            assert(parAddress != NULL);
            keyName = pRegInfo->parKey;
            //ESP_LOGI(TAG, "WRITE Param: %s\r\n", (const char*)keyName);
            // Get parameter size from object dictionary
            uint8_t parSize = pRegInfo->size;
            // Get parameter type from object dictionary
            uint8_t parType = pRegInfo->type;
            // Get access rights for the parameter from OD
            uint8_t access = pRegInfo->access;
            // Notify subscribed observers about parameter change
            //setPar((void*) parAddress); // notify about parameter change
            while (parSize > 0) {
                switch (parType) {
                case LKUP_TYPE_U16:
                    _XFER_2_WR(parAddress, pucRegBuffer)
                    ;
                    iRegIndex++;
                    parSize -= 2;
                    usNRegs--;
                    break;

                case LKUP_TYPE_U8:
                    parAddress[1] = *pucRegBuffer++;
                    parAddress[0] = 0;
                    iRegIndex++;
                    parSize -= 1;
                    usNRegs--;
                    break;

                case LKUP_TYPE_U32:
                    _XFER_4_WR(parAddress, pucRegBuffer)
                    ;
                    iRegIndex += 2;
                    parSize -= 4;
                    usNRegs -= 2;
                    break;

                case LKUP_TYPE_FLOAT:
                    _XFER_4_WR(parAddress, pucRegBuffer)
                    ;
                    iRegIndex += 2;
                    parSize -= 4;
                    usNRegs -= 2;
                    break;

                case LKUP_TYPE_ASCII:
                    // todo: parameter setting test
                    volatile uint8_t* pParPtr = (uint8_t*) parAddress;
                    while (parSize > 0) {
                        _XFER_2_WR(pParPtr, pucRegBuffer);
                        pParPtr += 2;
                        iRegIndex++;
                        parSize -= 2;
                        usNRegs--;
                    }
                    break;

                    //default:
                    //    assert(0);
                    //    break;
                } // switch(parType)
                // Check if parameter is writable and has NV storage flag set
                if (/*!(access & LKUP_ACCESS_WRITE_PROTECT_MASK) &&*/
                (access & (LKUP_ACCESS_TYPE_STATIC | LKUP_ACCESS_TYPE_NV))) {
                    //Write parameter data into NV Memory
                    writeParameter(pRegInfo, parAddress, 0);
                    // Send notification about parameter change to main application
                    BaseType_t status = xQueueSend(mbControllerNotificationQueueHandle, &pRegInfo, 0);
                    if (pdTRUE == status) {
                        ESP_LOGI(TAG, "Send notification: %s\r\n", (const char*)keyName);
                    }
                }
            } // while(parSize > 0)
        } else {
            // if(pRegInfo == NULL)
            eStatus = MB_ENOREG;
            break;
        }
    } // while((usNRegs > 0))

    return eStatus;
}

// Executed by stack when request to read holding registers is received
eMBErrorCode MbController::processHoldingRegs(uint8_t* pucRegBuffer,
        uint16_t usAddress, uint16_t usNRegs, eMBRegisterMode eMode)
{
    assert(pucRegBuffer != NULL);
    eMBErrorCode eStatus = MB_ENOERR;
    uint16_t iRegIndex;
    const uint16_t endReg = REG_HOLDING_START + usRegHoldingNregs;
    tLookupRegisters* pRegInfo = NULL;
    eMbEventGroup bits = MB_EVENT_NO_EVENTS;

    if ((usAddress >= REG_HOLDING_START) && ((usAddress + usNRegs) <= endReg)) {
        iRegIndex = (uint16_t) (usAddress - REG_HOLDING_START - 1);
        pRegInfo = findParameter(iRegIndex);
        // Check if parameter is found in object dictionary
        // and we start reading from beginning of OD variable
        if ((pRegInfo != NULL)) {
            // If number of registers greater or equal parameter size
            // One or several whole parameters to read
            if (usNRegs >= (pRegInfo->size >> 1)) {
                switch (eMode) {
                case MB_REG_READ:
                    eStatus = readHoldingRegs(pucRegBuffer, iRegIndex, usNRegs);
                    // Send an event to notify application task about event
                    xEventGroupSetBits(mbControllerEventGroup, (EventBits_t)MB_EVENT_HOLDING_REG_RD);
                    break;

                case MB_REG_WRITE:
                    eStatus = writeHoldingRegs(pucRegBuffer, iRegIndex,
                            usNRegs);
                    // Send an event to notify application task about event
                    eMbEventGroup bits = (eMbEventGroup)xEventGroupSetBits(mbControllerEventGroup, (EventBits_t)MB_EVENT_HOLDING_REG_WR);
                    if(bits & MB_EVENT_HOLDING_REG_WR) {
                        ESP_LOGI(TAG, "MB_EVENT_HOLDING_REG_WR event set. \r\n");
                    }
                    break;
                //default:
                //    assert(0);
                //    break;
                } // switch ( eMode )
            } else
                //  if(usNRegs < (pRegInfo->size / 2))
                eStatus = MB_ENOREG; // read less registers for parameter than required
        } //if((pRegInfo != NULL)) // parameter not found or reading from middle of variable
        else
            eStatus = MB_ENOREG; // parameter not found or reading from middle of variable
    } else { // if( ( usAddress < REG_HOLDING_START )
        eStatus = MB_ENOREG;
    }

    return eStatus;
}

// Executed by stack to process input registers read request
eMBErrorCode MbController::processInputs(uint8_t* pucRegBuffer,
        uint16_t usAddress, uint16_t usNRegs)
{
    assert(NULL != pucRegBuffer);
    assert(usNRegs >= 1);
    assert(usRegInputNregs > 1);
    eMBErrorCode eStatus = MB_ENOERR;
    uint16_t iRegIndex;

    if ((usAddress >= REG_INPUT_START)
            && ((usAddress + usNRegs) <= (REG_INPUT_START + usRegInputNregs + 1))) {
        iRegIndex = (uint16_t) (usAddress - REG_INPUT_START - 1);
        iRegIndex <<= 1; // register Address to byte address
        uint8_t* usInputBuffer = (uint8_t*) usRegInputBuf;
        usInputBuffer += iRegIndex;
        while (usNRegs > 0) {
            _XFER_2_RD(pucRegBuffer, usInputBuffer);
            iRegIndex += 2;
            usNRegs -= 1;
        }
    } else {
        eStatus = MB_ENOREG;
    }
    return eStatus;
}

// These are not fully implemented
eMBErrorCode MbController::processCoils(uint8_t* pucRegBuffer,
        uint16_t usAddress, uint16_t usNCoils, eMBRegisterMode eMode)
{
    eMBErrorCode eStatus = MB_ENOERR;
    uint16_t iRegIndex;

    if ((usAddress >= REG_COILS_START)
            && ((usAddress + usNCoils) <= (REG_COILS_START + (usRegCoilNregs << 4) + 1))) {
        iRegIndex = (uint16_t) (usAddress - REG_COILS_START);
        switch (eMode) {
        case MB_REG_READ:
            while (usNCoils > 0) {
                UCHAR ucResult = xMBUtilGetBits((uint8_t*) usRegCoilsBuf, iRegIndex, 1);
                xMBUtilSetBits(pucRegBuffer,
                        iRegIndex - (usAddress - REG_COILS_START), 1, ucResult);
                iRegIndex++;
                usNCoils--;
            }
            // Send an event to notify application task about event
            xEventGroupSetBits(mbControllerEventGroup, (EventBits_t)MB_EVENT_COILS_WR);
            break;
        case MB_REG_WRITE:
            while (usNCoils > 0) {
                UCHAR ucResult = xMBUtilGetBits(pucRegBuffer,
                        iRegIndex - (usAddress - REG_COILS_START), 1);
                xMBUtilSetBits((uint8_t*) usRegCoilsBuf, iRegIndex, 1,
                        ucResult);
                iRegIndex++;
                usNCoils--;
            }
            // Send an event to notify application task about event
            xEventGroupSetBits(mbControllerEventGroup, (EventBits_t)MB_EVENT_COILS_RD);
            break;
        } // switch ( eMode )
    } else {
        eStatus = MB_ENOREG;
    }

    return eStatus;
}

// Discrete inputs processing method
eMBErrorCode MbController::processDiscretes(uint8_t* pucRegBuffer,
        uint16_t usAddress, uint16_t usNDiscrete)
{
    eMBErrorCode eStatus = MB_ENOERR;
    uint16_t iRegIndex, iRegBitIndex, iNReg;
    uint8_t* pucDiscreteInputBuf;
    uint16_t usDiscreteInputStart;

    iNReg = usNDiscrete / 8 + 1;
    pucDiscreteInputBuf = (uint8_t*) usRegDiscreteBuf;
    usDiscreteInputStart = REG_DISCRETE_INPUT_START;

    // it already plus one in modbus function method.
    usAddress--;

    if ((usAddress >= REG_DISCRETE_INPUT_START)
            && ((usAddress + usNDiscrete)
                    <= (REG_DISCRETE_INPUT_START + REG_DISCRETE_INPUT_NREGS))) {
        iRegIndex = (USHORT) (usAddress - usDiscreteInputStart) / 8;
        iRegBitIndex = (USHORT) (usAddress - usDiscreteInputStart) % 8;

        while (iNReg > 0) {
            *pucRegBuffer++ = xMBUtilGetBits(&pucDiscreteInputBuf[iRegIndex++],
                                                iRegBitIndex, 8);
            iNReg--;
        }
        pucRegBuffer--;
        /* last discrete */
        usNDiscrete = usNDiscrete % 8;
        /* filling zero to high bit */
        *pucRegBuffer = *pucRegBuffer << (8 - usNDiscrete);
        *pucRegBuffer = *pucRegBuffer >> (8 - usNDiscrete);
        // Send an event to notify application task about event
        xEventGroupSetBits(mbControllerEventGroup, (EventBits_t)MB_EVENT_DISCRETE_RD);
    } else {
        eStatus = MB_ENOREG;
    }

    return eStatus;
}

// Initialize and start Modbus processing
esp_err_t MbController::start(void)
{
    const UCHAR ucSlaveID[] = { 0xAA, 0xBB, 0xCC };
    eMBErrorCode eStatus = MB_EIO;
    esp_err_t err = ESP_FAIL;

    if (MB_ENOERR
            != (eStatus = eMBInit((eMBMode) ucMbType, ucMbAddress, ucMbPort,
                    ulMbSpeed, (eMBParity) usMbParity))) {
        // Can not initialize. Add error handling code here.
        ESP_LOGI(TAG, "MB eMBInit() failure. \r\n");
        started = 0;
    } else {
        if (MB_ENOERR != (eStatus = eMBSetSlaveID(0x34, TRUE, ucSlaveID, 3))) {
            // Can not set slave id. Check arguments
            ESP_LOGI(TAG, "MB eMBSetSlaveID() failure. \r\n");
        } else if (MB_ENOERR != (eStatus = eMBEnable())) {
            // Enable failed.
            ESP_LOGI(TAG, "MB Enable failure. \r\n");
        } else {
            started = 1;
        }
    }
    if (eStatus == MB_ENOERR) {
        err = ESP_OK;
    }
    return err;
}

void MbController::run(void)
{
    for (;;) {
        if (started == 1) {
            (void) eMBPoll(); // allow stack to process data
            (void) xMBPortSerialTxPoll(); // Send response buffer if ready
        }
    }
    (void) eMBDisable(); // we should never get here in normal case
    (void) eMBClose();
    assert(0);
}

// Below are the wrapper function for executions of methods from pure "C" code
extern "C" {

// Start modbus controller init wrapper function
esp_err_t mbcontroller_init(void) {
    esp_err_t err = ESP_FAIL;
    pMbController = new MbController();
    err = (pMbController != NULL) ? ESP_OK : ESP_FAIL;
    return err;
}

// Start modbus controller start wrapper function
esp_err_t mbcontroller_start(void)
{
    assert(pMbController != NULL);
    esp_err_t err = pMbController->start();
    return err;
}

esp_err_t mbcontroller_write_parameter(void* param, void* paramData)
{
    assert(param != NULL);
    assert(paramData != NULL);
    assert(pMbController != NULL);
    tLookupRegisters* pItem = NULL;
    pItem = pMbController->getParDescrFromPtr(param);
    assert(pItem != NULL);
    esp_err_t err = pMbController->writeParameter(pItem, paramData, 0);
    return err;
}

// Blocking function to get notification about parameter change from application task
esp_err_t mbcontroller_get_notification(tLookupRegisters **regInfo)
{
    esp_err_t err = ESP_FAIL;
    tLookupRegisters* reg = NULL;
    assert(mbControllerNotificationQueueHandle != NULL);
    BaseType_t status = xQueueReceive(mbControllerNotificationQueueHandle, &reg,
            portMAX_DELAY);
    if (status == pdTRUE) {
        *regInfo = reg;
        err = ESP_OK;
    }
    return err;
}

// Blocking function to get event on parameter group change for application task
eMbEventGroup mbcontroller_check_event(eMbEventGroup group)
{
    esp_err_t err = ESP_FAIL;
    assert(mbControllerEventGroup != NULL);
    BaseType_t status = xEventGroupWaitBits(mbControllerEventGroup, (BaseType_t)group,
                                            pdTRUE , pdFALSE, portMAX_DELAY);
    return (eMbEventGroup)status;
}

esp_err_t mbcontroller_setup(eMBMode eMode,
                            uint8_t ucSlaveAddress, uint8_t ucPort,
                            uint32_t ulBaudRate, eMBParity eParity)
{
    assert(pMbController != NULL);
    esp_err_t err = pMbController->setMbParameters(eMode, ucSlaveAddress,
            ucPort, ulBaudRate, eParity);
    if (err == ESP_OK) {
        err = pMbController->start();
    }
    return err;
}

// Register read/write wrapper function
uint8_t mbRegRwCheckFunc(void* param, void* buffer) {
    tLookupRegisters* parInfo = (tLookupRegisters*) param;
    uint8_t* parAddress = GET_PARAMETER_ADDRESS(parInfo);
    assert(parAddress != NULL);
    // todo: Write check of parameters will be added here
    return 0;
}

// Wrapper function for appropriate method of class
uint8_t mbFindRegister(uint16_t parIndex)
{
    assert(pMbController != NULL);
    pMbController->findParameter(parIndex);
    return 0;
}

/* ----------------------- Wrapper functions for Modbus stack ---------------------------------*/

// Wrapper function for reading of MB Input Registers
eMBErrorCode eMBRegInputCB(UCHAR * pucRegBuffer, USHORT usAddress,
        USHORT usNRegs)
{
    eMBErrorCode error = pMbController->processInputs(pucRegBuffer, usAddress, usNRegs);
    return error;
}

// Wrapper function for reading of MB Holding Registers
eMBErrorCode eMBRegHoldingCB(UCHAR * pucRegBuffer, USHORT usAddress,
        USHORT usNRegs, eMBRegisterMode eMode)
{
    assert(pMbController != NULL);
    eMBErrorCode error = pMbController->processHoldingRegs(pucRegBuffer,
                                                            usAddress, usNRegs, eMode);
    return error;
}

// Wrapper function for reading of MB Coils Registers
eMBErrorCode eMBRegCoilsCB(UCHAR * pucRegBuffer, USHORT usAddress,
        USHORT usNCoils, eMBRegisterMode eMode)
{
    assert(pMbController != NULL);
    eMBErrorCode error = pMbController->processCoils(pucRegBuffer, usAddress,
                                                    usNCoils, eMode);

    return error;
}

// Wrapper function for reading of MB Discrete Input Registers
eMBErrorCode eMBRegDiscreteCB(UCHAR * pucRegBuffer, USHORT usAddress,
        USHORT usNDiscrete)
{
    eMBErrorCode error = MB_ENOREG;
    assert(pMbController != NULL);
    error = pMbController->processDiscretes((uint8_t*) pucRegBuffer,
                                            (uint16_t) usAddress, (uint16_t) usNDiscrete);
    return error;
}

} // extern "C"
