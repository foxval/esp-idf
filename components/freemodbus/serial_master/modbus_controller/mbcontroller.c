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

// mbcontroller.c
// Implementation of the modbus controller
// The modbus controller is responsible for processing of modbus packet and transfer data
// into parameter instance.

#include <sys/time.h>               // for calculation of time stamp in milliseconds
#include "esp_log.h"                // for log_write
#include <string.h>                 // for memcpy
#include "freertos/FreeRTOS.h"      // for task creation and queue access
#include "freertos/task.h"          // for task api access
#include "freertos/event_groups.h"  // for event groups
#include "freertos/queue.h"         // for queue api access
#include "mb.h"                     // for mb types definition
#include "mbutils.h"                // for mbutils functions definition for stack callback
#include "sdkconfig.h"              // for KConfig values
#include "mbcontroller.h"

static const char* MB_CONTROLLER_TAG = "MB_CONTROLLER";

#define MB_CHECK(a, ret_val, str, ...) \
    if (!(a)) { \
        ESP_LOGE(MB_CONTROLLER_TAG, "%s(%u): " str, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
        return (ret_val); \
    }

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

/*-----------------------Master mode use these variables----------------------*/
#if MB_MASTER_RTU_ENABLED > 0 || MB_MASTER_ASCII_ENABLED > 0

// The response time is average processing time + data transmission (higher on lower speeds)
// ~resp_time_ms = min_pcocessing_time_ms + ((2 packets * (header_size + packet_bytes)) * 11 bits in byte * 1000 ms_in_sec) / transmit_speed))
#define MB_RESPONSE_TIMEOUT(size) pdMS_TO_TICKS(20 + (2 * ((size << 1) + 8) * 11 * 1000 / mb_speed))

static uint8_t* mb_reg_buffer_ptr = NULL;
static uint16_t mb_reg_buffer_size = 0;

// Event group parameters
static TaskHandle_t mb_controller_task_handle = NULL;
static EventGroupHandle_t mb_controller_event_group = NULL;
static const mb_parameter_descriptor_t* mb_param_descriptor_table = NULL;
static size_t mb_param_descriptor_size = 0;

static uint8_t mb_type = 0;
static uint8_t mb_address = 0;
static uint8_t mb_port = 0;
static uint32_t mb_speed = 0;
static uint16_t mb_parity = 0;

// Modbus event processing task
static void modbus_master_task(void *pvParameters) {
    // Main Modbus stack processing cycle
    for (;;) {
        // Wait for poll events
        BaseType_t status = xEventGroupWaitBits(mb_controller_event_group,
                                                (BaseType_t)(MB_EVENT_STACK_STARTED),
                                                pdFALSE, // do not clear bits
                                                pdFALSE,
                                                portMAX_DELAY);
        // Check if stack started then poll for data
        if (status & MB_EVENT_STACK_STARTED) {
            (void)eMBMasterPoll(); // Allow stack to process data
            // Send response buffer if ready to be sent
            BOOL xSentState = xMBMasterPortSerialTxPoll();
            if (xSentState) {
                // Let state machine know that response was transmitted out
                (void)xMBMasterPortEventPost(EV_MASTER_FRAME_TRANSMITTED);
            }
        }
    }
}

// Initialization of Modbus controller resources
esp_err_t mbcontroller_init(void) {
    mb_type = MB_MODE_RTU;
    mb_address = MB_DEVICE_ADDRESS;
    mb_port = MB_UART_PORT;
    mb_speed = MB_DEVICE_SPEED;
    mb_parity = MB_PARITY_NONE;

    // Initialization of active context of the modbus controller
    BaseType_t status = 0;
    // Parameter change notification queue
    mb_controller_event_group = xEventGroupCreate();
    MB_CHECK((mb_controller_event_group != NULL), ESP_ERR_NO_MEM, "mb event group error.");
    // Create modbus controller task
    status = xTaskCreate((void*)&modbus_master_task,
                            "modbus_matask",
                            MB_CONTROLLER_STACK_SIZE,
                            NULL,                       // No parameters
                            MB_CONTROLLER_PRIORITY,
                            &mb_controller_task_handle);
    if (status != pdPASS) {
        vTaskDelete(mb_controller_task_handle);
        MB_CHECK((status == pdPASS), ESP_ERR_NO_MEM,
                "mb controller task creation error, xTaskCreate() returns (0x%x).",
                (uint32_t)status);
    }
    assert(mb_controller_task_handle != NULL); // The task is created but handle is incorrect
    return ESP_OK;
}

// Modbus controller stack start function
esp_err_t mbcontroller_start(void)
{
    eMBErrorCode status = MB_EIO;
    // Initialize Modbus stack using mbcontroller parameters
    status = eMBMasterInit((eMBMode)mb_type, (UCHAR)mb_port,
                            (ULONG)mb_speed, (eMBParity)mb_parity);
    MB_CHECK((status == MB_ENOERR), ESP_ERR_INVALID_STATE,
            "mb stack initialization failure, eMBInit() returns (0x%x).", status);
    status = eMBMasterEnable();
    MB_CHECK((status == MB_ENOERR), ESP_ERR_INVALID_STATE,
            "mb stack set slave ID failure, eMBEnable() returned (0x%x).", (uint32_t)status);
    // Set the mbcontroller start flag
    EventBits_t flag = xEventGroupSetBits(mb_controller_event_group,
                                            (EventBits_t)MB_EVENT_STACK_STARTED);
    MB_CHECK((flag & MB_EVENT_STACK_STARTED),
                ESP_ERR_INVALID_STATE, "mb stack start event set error.");
    return ESP_OK;
}

// Modbus controller destroy function
esp_err_t mbcontroller_destroy(void)
{
    eMBErrorCode mb_error = MB_ENOERR;
    // Stop polling by clearing correspondent bit in the event group
    EventBits_t flag = xEventGroupClearBits(mb_controller_event_group,
                                    (EventBits_t)MB_EVENT_STACK_STARTED);
    MB_CHECK((flag & MB_EVENT_STACK_STARTED),
                ESP_ERR_INVALID_STATE, "mb stack stop event failure.");
    // Desable and then destroy the Modbus stack
    mb_error = eMBMasterDisable();
    MB_CHECK((mb_error == MB_ENOERR), ESP_ERR_INVALID_STATE, "mb stack disable failure.");
    (void)vTaskDelete(mb_controller_task_handle);
    (void)vEventGroupDelete(mb_controller_event_group);
    mb_error = eMBMasterClose();
    MB_CHECK((mb_error == MB_ENOERR), ESP_ERR_INVALID_STATE,
            "mb stack close failure returned (0x%x).", (uint32_t)mb_error);
    return ESP_OK;
}

// Setup Modbus controller parameters
esp_err_t mbcontroller_setup(const mb_communication_info_t comm_info)
{
    MB_CHECK(((comm_info.mode == MB_MODE_RTU) || (comm_info.mode == MB_MODE_ASCII)),
                ESP_ERR_INVALID_ARG, "mb incorrect mode = (0x%x).",
                (uint32_t)comm_info.mode);
    MB_CHECK((comm_info.port <= UART_NUM_2), ESP_ERR_INVALID_ARG,
                "mb wrong port to set = (0x%x).", (uint32_t)comm_info.port);
    MB_CHECK((comm_info.parity <= UART_PARITY_EVEN), ESP_ERR_INVALID_ARG,
                "mb wrong parity option = (0x%x).", (uint32_t)comm_info.parity);
    mb_type = (uint8_t)comm_info.mode;
    mb_port = (uint8_t)comm_info.port;
    mb_speed = (uint32_t)comm_info.baudrate;
    mb_parity = (uint8_t)comm_info.parity;
    return ESP_OK;
}

// Set Modbus parameter description table
esp_err_t mbcontroller_set_descriptor(const mb_parameter_descriptor_t* descriptor, const uint16_t num_elements)
{
    MB_CHECK((descriptor != NULL), ESP_ERR_INVALID_ARG, "mb incorrect descriptor.");
    MB_CHECK((num_elements >= 1), ESP_ERR_INVALID_ARG, "mb table size is incorrect.");

    const mb_parameter_descriptor_t *reg_ptr = descriptor;
    // Go through all items in the table to check all Modbus registers
    for (uint16_t counter = 0; counter < (num_elements); counter++, reg_ptr++)
    {
        // Below is the code to check consistency of the table format and required fields.
        MB_CHECK((reg_ptr->cid == counter), ESP_ERR_INVALID_ARG, "mb descriptor cid field is incorrect.");
        MB_CHECK((reg_ptr->param_key != NULL), ESP_ERR_INVALID_ARG, "mb descriptor param key is incorrect.");
        MB_CHECK((reg_ptr->mb_size > 0), ESP_ERR_INVALID_ARG, "mb descriptor param size is incorrect.");
    }
    mb_param_descriptor_table = descriptor;
    mb_param_descriptor_size = num_elements;
    return ESP_OK;
}

// Send custom Modbus request defined as mb_param_request_t structure
esp_err_t mbcontroller_send_request(mb_param_request_t* request, void* data_ptr)
{
    MB_CHECK((request != NULL), ESP_ERR_INVALID_ARG, "mb request structure.");
    MB_CHECK((data_ptr != NULL), ESP_ERR_INVALID_ARG, "mb incorrect data pointer.");

    eMBMasterReqErrCode mb_error = MB_MRE_NO_REG;
    esp_err_t error = ESP_FAIL;

    uint8_t mb_slave_addr = request->slave_addr;
    uint8_t mb_command = request->command;
    uint16_t mb_offset = request->reg_start;
    uint16_t mb_size = request->reg_size;

    // Timeout value for packet processing
    uint32_t timeout = 0;
    size_t pack_length = 0;

    // Set the buffer for callback function processing of received data
    mb_reg_buffer_ptr = (uint8_t*)data_ptr;
    mb_reg_buffer_size = mb_size;

    // Calls appropriate request function to send request and waits response
    switch(mb_command)
    {
        case MB_FUNC_READ_COILS:
            pack_length = (mb_size >= 8) ? (mb_size >> 3) : 1;
            timeout = MB_RESPONSE_TIMEOUT(pack_length);
            mb_error = eMBMasterReqReadCoils((UCHAR)mb_slave_addr, (USHORT)mb_offset,
                                               (USHORT)mb_size , (LONG)timeout );
            break;
        case MB_FUNC_WRITE_SINGLE_COIL:
            timeout = MB_RESPONSE_TIMEOUT(1);
            mb_error = eMBMasterReqWriteCoil((UCHAR)mb_slave_addr, (USHORT)mb_offset,
                                                *(USHORT*)data_ptr, (LONG)timeout );
            break;
        case MB_FUNC_WRITE_MULTIPLE_COILS:
            pack_length = (mb_size >= 8) ? (mb_size >> 3) : 1;
            timeout = MB_RESPONSE_TIMEOUT(pack_length);
            mb_error = eMBMasterReqWriteMultipleCoils((UCHAR)mb_slave_addr, (USHORT)mb_offset,
                                                            (USHORT)mb_size, (UCHAR*)data_ptr, (LONG)timeout);
            break;
        case MB_FUNC_READ_DISCRETE_INPUTS:
            pack_length = (mb_size >= 8) ? (mb_size >> 3) : 1;
            timeout = MB_RESPONSE_TIMEOUT(pack_length);
            mb_error = eMBMasterReqReadDiscreteInputs((UCHAR)mb_slave_addr, (USHORT)mb_offset,
                                                        (USHORT)mb_size, (LONG)timeout );
            break;
        case MB_FUNC_READ_HOLDING_REGISTER:
            timeout = MB_RESPONSE_TIMEOUT(mb_size);
            mb_error = eMBMasterReqReadHoldingRegister((UCHAR)mb_slave_addr, (USHORT)mb_offset,
                                                            (USHORT)mb_size, (LONG)timeout );
            break;
        case MB_FUNC_WRITE_REGISTER:
            timeout = MB_RESPONSE_TIMEOUT(1);
            mb_error = eMBMasterReqWriteHoldingRegister( (UCHAR)mb_slave_addr, (USHORT)mb_offset,
                                                            *(USHORT*)data_ptr, (LONG)timeout );
            break;

        case MB_FUNC_WRITE_MULTIPLE_REGISTERS:
            timeout = MB_RESPONSE_TIMEOUT(mb_size);
            mb_error = eMBMasterReqWriteMultipleHoldingRegister( (UCHAR)mb_slave_addr,
                                                                    (USHORT)mb_offset, (USHORT)mb_size,
                                                                    (USHORT*)data_ptr, (LONG)timeout );
            break;
        case MB_FUNC_READWRITE_MULTIPLE_REGISTERS:
            timeout = MB_RESPONSE_TIMEOUT(mb_size << 1);
            mb_error = eMBMasterReqReadWriteMultipleHoldingRegister( (UCHAR)mb_slave_addr, (USHORT)mb_offset,
                                                                       (USHORT)mb_size, (USHORT*)data_ptr,
                                                                       (USHORT)mb_offset, (USHORT)mb_size,
                                                                       (LONG)timeout );
            break;
        case MB_FUNC_READ_INPUT_REGISTER:
            timeout = MB_RESPONSE_TIMEOUT(mb_size);
            mb_error = eMBMasterReqReadInputRegister( (UCHAR)mb_slave_addr, (USHORT)mb_offset,
                                                        (USHORT)mb_size, (LONG) timeout );
            break;
        default:
            ESP_LOGE(MB_CONTROLLER_TAG, "%s: Incorrect function in request (%u) ",
                                                    __FUNCTION__, mb_command);
            mb_error = MB_MRE_NO_REG;
            break;
    }

    // Propagate the Modbus errors to higher level
    switch(mb_error)
    {
        case MB_MRE_NO_ERR:
            error = ESP_OK;
            break;

        case MB_MRE_NO_REG:
            error = ESP_ERR_NOT_SUPPORTED;
            break;

        case MB_MRE_TIMEDOUT:
            error = ESP_ERR_TIMEOUT;
                break;

        case MB_MRE_EXE_FUN:
        case MB_MRE_REV_DATA:
            error = ESP_ERR_INVALID_RESPONSE;
            break;
        default:
            error = ESP_FAIL;
            break;
    }

    return error;
}

esp_err_t mbcontroller_get_cid_info(uint16_t cid, const mb_parameter_descriptor_t** param_buffer)
{
    MB_CHECK((param_buffer != NULL), ESP_ERR_INVALID_ARG, "mb incorrect data buffer pointer.");
    MB_CHECK((mb_param_descriptor_table != NULL), ESP_ERR_INVALID_ARG, "mb incorrect descriptor table or not set.");
    MB_CHECK((cid < mb_param_descriptor_size), ESP_ERR_NOT_FOUND, "mb incorrect cid of characteristic.");

    // It is assumed that characteristics cid increased in the table
    const mb_parameter_descriptor_t* reg_info = &mb_param_descriptor_table[cid];

    MB_CHECK((reg_info->param_key != NULL), ESP_ERR_INVALID_ARG, "mb incorrect characteristic key.");
    *param_buffer = reg_info;
    return ESP_OK;
}

// Helper function to get modbus command for each type of Modbus register area
static uint8_t mbcontroller_get_command(mb_param_type_t param_type, mb_param_mode_t mode)
{
    uint8_t command = 0;
    switch(param_type)
    { //
        case MB_PARAM_HOLDING:
            command = (mode == MB_PARAM_WRITE) ? MB_FUNC_WRITE_MULTIPLE_REGISTERS : MB_FUNC_READ_HOLDING_REGISTER;
            break;
        case MB_PARAM_INPUT:
            command = MB_FUNC_READ_INPUT_REGISTER;
            break;
        case MB_PARAM_COIL:
            command = (mode == MB_PARAM_WRITE) ? MB_FUNC_WRITE_MULTIPLE_COILS : MB_FUNC_READ_COILS;
            break;
        case MB_PARAM_DISCRETE:
            if (mode != MB_PARAM_WRITE) {
                command = MB_FUNC_READ_DISCRETE_INPUTS;
            } else {
                ESP_LOGE(MB_CONTROLLER_TAG, "%s: Incorrect mode (%u)", __FUNCTION__, (uint8_t)mode);
            }
            break;
        default:
            ESP_LOGE(MB_CONTROLLER_TAG, "%s: Incorrect param type (%u)", __FUNCTION__, param_type);
            break;
    }
    return command;
}

// Helper function to set parameter buffer according to its type
static esp_err_t mbcontroller_set_param_data(void* dest, void* src, mb_descr_type_t param_type, size_t param_size)
{
    esp_err_t err = ESP_OK;
    MB_CHECK((dest != NULL), ESP_ERR_INVALID_ARG, "incorrect parameter pointer.");
    MB_CHECK((src != NULL), ESP_ERR_INVALID_ARG, "incorrect parameter pointer.");
    // Transfer parameter data into value of characteristic
    switch(param_type)
    {
        case PARAM_TYPE_U8:
            *((uint8_t*)dest) = *((uint8_t*)src);
            break;
        case PARAM_TYPE_U16:
            *((uint16_t*)dest) = *((uint16_t*)src);
            break;
        case PARAM_TYPE_U32:
            *((uint32_t*)dest) = *((uint32_t*)src);
            break;
        case PARAM_TYPE_FLOAT:
            *((float*)dest) = *(float*)src;
            break;
        case PARAM_TYPE_ASCII:
            memcpy((void*)dest, (void*)src, (size_t)param_size);
            break;
        default:
            ESP_LOGE(MB_CONTROLLER_TAG, "%s: Incorrect param type (%u).",
                        __FUNCTION__, (uint16_t)param_type);
            err = ESP_ERR_NOT_SUPPORTED;
            break;
    }
    return err;
}

// Search parameter by name in the parameter description table and fills Modbus request fields accordingly
static esp_err_t mbcontroller_set_request(char* name, mb_param_mode_t mode, mb_param_request_t* request,
                                                mb_parameter_descriptor_t* reg_data)
{
    esp_err_t error = ESP_ERR_NOT_FOUND;
    MB_CHECK((name != NULL), ESP_ERR_INVALID_ARG, "mb incorrect parameter name.");
    MB_CHECK((request != NULL), ESP_ERR_INVALID_ARG, "mb incorrect request parameter.");
    MB_CHECK((mode <= MB_PARAM_WRITE), ESP_ERR_INVALID_ARG, "mb incorrect mode.");
    assert(mb_param_descriptor_table != NULL);
    const mb_parameter_descriptor_t* reg_ptr = mb_param_descriptor_table;
    for (uint16_t counter = 0; counter < (mb_param_descriptor_size); counter++, reg_ptr++)
    {
        // Check the length of name and parameter key strings from table
        size_t param_key_len = strlen((const char*)reg_ptr->param_key);
        if (param_key_len != strlen((const char*)name)) {
            continue; // The length of strings is different then check next record in the table
        }
        // Compare the name of parameter with parameter key from table
        uint8_t comp_result = memcmp((const char*)name, (const char*)reg_ptr->param_key, (size_t)param_key_len);
        if (comp_result == 0) {
            // The correct line is found in the table and reg_ptr points to the found parameter description
            request->slave_addr = reg_ptr->mb_slave_addr;
            request->reg_start = reg_ptr->mb_reg_start;
            request->reg_size = reg_ptr->mb_size;
            request->command = mbcontroller_get_command(reg_ptr->mb_param_type, mode);
            MB_CHECK((request->command > 0), ESP_ERR_INVALID_ARG, "mb incorrect command or parameter type.");
            if (reg_data != NULL) {
                *reg_data = *reg_ptr; // Set the cid registered parameter data
            }
            error = ESP_OK;
            break;
        }
    }
    return error;
}

// Get parameter data for corresponding characteristic
esp_err_t mbcontroller_get_parameter(uint16_t cid, char* name, uint8_t* value, uint8_t *type)
{
    MB_CHECK((name != NULL), ESP_ERR_INVALID_ARG, "mb incorrect descriptor.");
    MB_CHECK((type != NULL), ESP_ERR_INVALID_ARG, "type pointer is incorrect.");
    esp_err_t error = ESP_ERR_INVALID_RESPONSE;
    mb_param_request_t request ;
    mb_parameter_descriptor_t reg_info = { 0 };
    uint8_t param_buffer[PARAM_MAX_SIZE] = { 0 };

    error = mbcontroller_set_request(name, MB_PARAM_READ, &request, &reg_info);
    if ((error == ESP_OK) && (cid == reg_info.cid)) {
        error = mbcontroller_send_request(&request, &param_buffer[0]);
        if (error == ESP_OK) {
            // If data pointer is NULL then we don't need to set value (it is still in the cache of cid)
            if (value != NULL) {
                error = mbcontroller_set_param_data((void*)value, (void*)&param_buffer[0],
                                                    reg_info.param_type, reg_info.param_size);
                MB_CHECK((error == ESP_OK), ESP_ERR_INVALID_STATE, "fail to set parameter data.");
            }
            ESP_LOGD(MB_CONTROLLER_TAG, "%s: Good response for get cid(%u) = %s",
                                    __FUNCTION__, (int)reg_info.cid, (char*)esp_err_to_name(error));
        } else {
            ESP_LOGD(MB_CONTROLLER_TAG, "%s: Bad response to get cid(%u) = %s",
                                            __FUNCTION__, reg_info.cid, (char*)esp_err_to_name(error));
        }
        // Set the type of parameter found in the table
        *type = reg_info.param_type;
    } else {
        ESP_LOGD(MB_CONTROLLER_TAG, "%s: The cid(%u) not found in the data dictionary.",
                                                    __FUNCTION__, reg_info.cid);
    }
    return error;
}

// Set parameter value for characteristic selected by name and cid
esp_err_t mbcontroller_set_parameter(uint16_t cid, char* name, uint8_t* value, uint8_t *type)
{
    MB_CHECK((name != NULL), ESP_ERR_INVALID_ARG, "mb incorrect descriptor.");
    MB_CHECK((value != NULL), ESP_ERR_INVALID_ARG, "value pointer is incorrect.");
    MB_CHECK((type != NULL), ESP_ERR_INVALID_ARG, "type pointer is incorrect.");

    esp_err_t error = ESP_ERR_INVALID_RESPONSE;
    mb_param_request_t request ;
    mb_parameter_descriptor_t reg_info = { 0 };
    uint8_t param_buffer[PARAM_MAX_SIZE] = { 0 };

    error = mbcontroller_set_request(name, MB_PARAM_WRITE, &request, &reg_info);
    if ((error == ESP_OK) && (cid == reg_info.cid)) {
        // Transfer value of characteristic into parameter buffer
        error = mbcontroller_set_param_data((void*)&param_buffer[0], (void*)value,
                                                reg_info.param_type, reg_info.param_size);
        MB_CHECK((error == ESP_OK), ESP_ERR_INVALID_STATE, "failure to set parameter data.");
        // Send request to write characteristic data
        error = mbcontroller_send_request(&request, &param_buffer[0]);
        if (error == ESP_OK) {
            ESP_LOGD(MB_CONTROLLER_TAG, "%s: Good response for set cid(%u) = %s",
                                    __FUNCTION__, (int)reg_info.cid, (char*)esp_err_to_name(error));
        } else {
            ESP_LOGD(MB_CONTROLLER_TAG, "%s: Bad response to set cid(%u) = %s",
                                    __FUNCTION__, reg_info.cid, (char*)esp_err_to_name(error));
        }
        // Set the type of parameter found in the table
        *type = reg_info.param_type;
    } else {
        ESP_LOGE(MB_CONTROLLER_TAG, "%s: The requested cid(%u) not found in the data dictionary.",
                                    __FUNCTION__, reg_info.cid);
    }
    return error;
}

/* ----------------------- Callback functions for Modbus stack ---------------------------------*/
// These are executed by modbus stack to read appropriate type of registers.

/**
 * Modbus master input register callback function.
 *
 * @param pucRegBuffer input register buffer
 * @param usAddress input register address
 * @param usNRegs input register number
 *
 * @return result
 */
// Callback function for reading of MB Input Registers
eMBErrorCode eMBMasterRegInputCB(UCHAR * pucRegBuffer, USHORT usAddress,
                                USHORT usNRegs)
{
    assert(pucRegBuffer != NULL);
    USHORT usRegInputNregs = (USHORT)mb_reg_buffer_size; // Number of input registers to be transferred
    UCHAR* pucInputBuffer = (UCHAR*)mb_reg_buffer_ptr; // Get instance address
    USHORT usRegs = usNRegs;
    eMBErrorCode eStatus = MB_ENOERR;
    //USHORT iRegIndex;
    // If input or configuration parameters are incorrect then return an error to stack layer
    if ((pucInputBuffer != NULL)
            && (usNRegs >= 1)
            && (usRegInputNregs == usRegs)) {
        while (usRegs > 0) {
            _XFER_2_RD(pucInputBuffer, pucRegBuffer);
            usRegs -= 1;
        }
    } else {
        eStatus = MB_ENOREG;
    }
    return eStatus;
}

/**
 * Modbus master holding register callback function.
 *
 * @param pucRegBuffer holding register buffer
 * @param usAddress holding register address
 * @param usNRegs holding register number
 * @param eMode read or write
 *
 * @return result
 */
// Callback function for reading of MB Holding Registers
// Executed by stack when request to read/write holding registers is received
eMBErrorCode eMBMasterRegHoldingCB(UCHAR * pucRegBuffer, USHORT usAddress,
        USHORT usNRegs, eMBRegisterMode eMode)
{
    assert(pucRegBuffer != NULL);
    USHORT usRegHoldingNregs = (USHORT)mb_reg_buffer_size;
    UCHAR* pucHoldingBuffer = (UCHAR*)mb_reg_buffer_ptr;
    eMBErrorCode eStatus = MB_ENOERR;
    USHORT usRegs = usNRegs;
    // Check input and configuration parameters for correctness
    if ((pucHoldingBuffer != NULL)
            && (usRegHoldingNregs == usNRegs)
            && (usNRegs >= 1)) {
        switch (eMode) {
            case MB_REG_WRITE:
                while (usRegs > 0) {
                    _XFER_2_RD(pucRegBuffer, pucHoldingBuffer);
                    usRegs -= 1;
                };
                break;
            case MB_REG_READ:
                while (usRegs > 0) {
                    _XFER_2_WR(pucHoldingBuffer, pucRegBuffer);
                    pucHoldingBuffer += 2;
                    usRegs -= 1;
                };
                break;
        }
    } else {
        eStatus = MB_ENOREG;
    }
    return eStatus;
}

/**
 * Modbus master coils callback function.
 *
 * @param pucRegBuffer coils buffer
 * @param usAddress coils address
 * @param usNCoils coils number
 * @param eMode read or write
 *
 * @return result
 */
// Callback function for reading of MB Coils Registers
eMBErrorCode eMBMasterRegCoilsCB(UCHAR* pucRegBuffer, USHORT usAddress,
        USHORT usNCoils, eMBRegisterMode eMode)
{
    assert(NULL != pucRegBuffer);
    USHORT usRegCoilNregs = (USHORT)mb_reg_buffer_size;
    UCHAR* pucRegCoilsBuf = (UCHAR*)mb_reg_buffer_ptr;
    eMBErrorCode eStatus = MB_ENOERR;
    USHORT iRegIndex;
    USHORT usCoils = usNCoils;
    usAddress--; // The address is already + 1
    if ((usRegCoilNregs >= 1)
            && (pucRegCoilsBuf != NULL)
            && (usNCoils == usRegCoilNregs)) {
        iRegIndex = (usAddress % 8);
        switch (eMode) {
            case MB_REG_WRITE:
                while (usCoils > 0) {
                    UCHAR ucResult = xMBUtilGetBits((UCHAR*)pucRegCoilsBuf, iRegIndex, 1);
                    xMBUtilSetBits(pucRegBuffer, iRegIndex - (usAddress % 8) , 1, ucResult);
                    iRegIndex++;
                    usCoils--;
                }
                break;
            case MB_REG_READ:
                while (usCoils > 0) {
                    UCHAR ucResult = xMBUtilGetBits(pucRegBuffer, iRegIndex - (usAddress % 8), 1);
                    xMBUtilSetBits((uint8_t*)pucRegCoilsBuf, iRegIndex, 1, ucResult);
                    iRegIndex++;
                    usCoils--;
                }
                break;
        } // switch ( eMode )
    } else {
        // If the configuration or input parameters are incorrect then return error to stack
        eStatus = MB_ENOREG;
    }
    return eStatus;
}

/**
 * Modbus master discrete callback function.
 *
 * @param pucRegBuffer discrete buffer
 * @param usAddress discrete address
 * @param usNDiscrete discrete number
 *
 * @return result
 */
// Callback function for reading of MB Discrete Input Registers
eMBErrorCode eMBMasterRegDiscreteCB(UCHAR * pucRegBuffer, USHORT usAddress,
                            USHORT usNDiscrete)
{
    assert(pucRegBuffer != NULL);
    USHORT usRegDiscreteNregs = (USHORT)mb_reg_buffer_size;
    UCHAR* pucRegDiscreteBuf = (UCHAR*)mb_reg_buffer_ptr;
    eMBErrorCode eStatus = MB_ENOERR;
    USHORT iRegBitIndex, iNReg;
    UCHAR* pucDiscreteInputBuf;
    iNReg = usNDiscrete / 8 + 1;
    pucDiscreteInputBuf = (UCHAR*) pucRegDiscreteBuf;
    // It is already plus one in Modbus function method.
    usAddress--;
    if ((usRegDiscreteNregs >= 1)
            && (pucRegDiscreteBuf != NULL)
            && (usNDiscrete >= 1)) {
        iRegBitIndex = (USHORT)(usAddress) % 8; // Get bit index
        while (iNReg > 1)
        {
            xMBUtilSetBits(pucDiscreteInputBuf++, iRegBitIndex, 8, *pucRegBuffer++);
            iNReg--;
        }
        // last discrete
        usNDiscrete = usNDiscrete % 8;
        // xMBUtilSetBits has bug when ucNBits is zero
        if (usNDiscrete != 0)
        {
            xMBUtilSetBits(pucDiscreteInputBuf, iRegBitIndex, usNDiscrete, *pucRegBuffer++);
        }
    } else {
        eStatus = MB_ENOREG;
    }
    return eStatus;
}

#endif // MB_MASTER_RTU_ENABLED > 0 || MB_MASTER_ASCII_ENABLED > 0
