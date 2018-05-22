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

//  nvmanager.cpp
//  Implementation of the Class NvManager

#include "nvmanager.h"
#include "stdio.h"              // for using printf
#include "freertos/FreeRTOS.h"  // for portMUX_TYPE

#ifdef ESP_PLATFORM
// #define LOG_LOCAL_LEVEL ESP_LOG_DEBUG
#include "esp_log.h"
static const char* TAG = "MODBUS_NVMGR";
#else
#define ESP_LOGD(...)
#endif

// Todo: pointer to modbus NV manager
NvManager* pNvManager = NULL;
static portMUX_TYPE mbNvMux = portMUX_INITIALIZER_UNLOCKED;

__attribute__((always_inline))
static inline __attribute__((always_inline)) int enter_critical(void) {
    MB_NVMGR_ENTER_CRITICAL(&mbNvMux);
    //ets_intr_lock();
    return 1;
}

__attribute__((always_inline))
static inline __attribute__((always_inline)) int exit_critical(void) {
    MB_NVMGR_EXIT_CRITICAL(&mbNvMux);
    //ets_intr_unlock();
    return 0;
}

// The class of NvManager 
// This class is responsible for storage of parameter data in NVS
// memory according to parameter description
NvManager::NvManager() : oNvManager(*this), pLookupTable(&g_stLookupRegisters[0])
{
    pNvManager = this;
    error = 0;
    //init();
}

// Returns last error returned from NVS driver API call
esp_err_t NvManager::getLastError(void)
{
    return error;
}

// Todo: Note: This method shadows the base class init method
// This method initialize namespace for modbus parameters
esp_err_t NvManager::initNv(void)
{
    // Initialize NV Storage
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES) {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    // Open name space
    error = nvs_open(MB_NVS_NAMESPACE, NVS_READWRITE, &mbNvsHandle);
    ESP_ERROR_CHECK(error);

    // Save initialization error code as status to check later
    if((error != ESP_OK) || (err != ESP_OK)) {
        nvsInitStatus = ESP_FAIL;
    } else {
        nvsInitStatus = ESP_OK;
    }
    // Erase namespace to check initialization
    //nvs_erase_all(mbNvsHandle);
    return error;
}

NvManager::~NvManager()
{
    // We should not get here because it is singleton and we suppress deletion of it
    nvs_close(mbNvsHandle);
    assert(0);
}

esp_err_t NvManager::writeParameter(tLookupRegisters *parInfo, void* paramData, uint8_t forceUpdate)
{
    assert(paramData != NULL);
    assert(parInfo != NULL);
    ESP_ERROR_CHECK(nvsInitStatus); // Check if nvs initialized correctly
    // Get NV parameter key from data dictionary
    const char* parKey = parInfo->parKey;
    // Get parameter type from data dictionary
    uint8_t parType = parInfo->type;
    // Parameter buffer
    uint8_t paramNew[] = {  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    uint8_t paramOld[] = {  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    // Copy parameter data to temporary parameter storage
    memcpy(&paramNew[0], paramData, parInfo->size);
    error = readParameter(parInfo, paramOld);
    if((error == ESP_OK) || (error == ESP_ERR_NVS_NOT_FOUND)) {
        // If new parameter is the same as stored then just to skip
        // else write parameter if it has NV attribute set
        // Force flag allows initial initialization of namespace parameters
        int checkPars = memcmp(paramNew, paramOld, parInfo->size);
        if(((checkPars != 0) || (forceUpdate > 0)) &&
                (parInfo->access & LKUP_ACCESS_TYPE_NV_MASK)) {
            switch(parType) {
                // Set parameter data in NVS storage according to type
                case LKUP_TYPE_U8:
                    error = nvs_set_u8(mbNvsHandle, parKey, *(uint8_t*)&paramNew[0]);
                    ESP_LOGD(TAG, "MB_get_U8_data: %s, %u %x", parKey, *(uint8_t*)&paramNew[0], (int16_t)error);
                    break;
                case LKUP_TYPE_U16:
                    error = nvs_set_u16(mbNvsHandle, parKey, *(uint16_t*)&paramNew[0]);
                    ESP_LOGD(TAG, "MB_get_U16_data: %s, %u %x", parKey, *(uint16_t*)&paramNew[0], (int16_t)error);
                    break;
                case LKUP_TYPE_U32:
                    error = nvs_set_u32(mbNvsHandle, parKey, *(uint32_t*)&paramNew[0]);
                    ESP_LOGD(TAG, "MB_get_U32_data: %s, %u %x", parKey, *(uint32_t*)&paramNew[0], (int16_t)error);
                    break;
                case LKUP_TYPE_FLOAT:
                    // There is no function to write float then will use U32 instead
                    error = nvs_set_u32(mbNvsHandle, parKey, *(uint32_t*)&paramNew[0]);
                    ESP_LOGD(TAG, "MB_get_FLOAT_data: %s, %f %x", parKey, *(float*)&paramNew[0], (int16_t)error);
                    break;
                case LKUP_TYPE_ASCII:
                    /*
                    // Todo: The last char of the string can be missed due to endianess
                    // Parameter storage has limitation for strings = 15 symbols
                    // Update code later to correct endianess if required and use blob
                    error = nvs_set_str(mbNvsHandle, parKey, (char*)&paramNew[0]);
                    paramNew[MB_PAR_MAX_SIZE - 1] = 0; // Terminate parameter string
                    ESP_LOGD(TAG, "MB_set_ASCII_data: %s, %s, %d", parKey, (char*)&paramNew[0], (int16_t)error);
                    */
                    size_t size = 0;  // value will default to 0, if not set yet in NVS
                    error = nvs_get_blob(mbNvsHandle, parKey, NULL, &size);
                    if((error != ESP_OK) && (error != ESP_ERR_NVS_NOT_FOUND)) {
                        return error;
                    }
                    // Read parameter data from blob if available
                    if ((size > 0) || (error == ESP_ERR_NVS_NOT_FOUND)) {
                        // Get blob data to local buffer
                        error = nvs_get_blob(mbNvsHandle, parKey, (void*)paramNew, &size);
                        if ((error == ESP_OK) || ((error == ESP_ERR_NVS_NOT_FOUND) && (forceUpdate > 0))) {
                            // Copy parameter data to blob memory buffer (lock buffer)
                            ATOMIC_BLOCK {
                                memcpy((void*)paramNew, (void*)paramData, parInfo->size);
                            }
                            // Save parameter data into blob (nvs api include critical sections)
                            error = nvs_set_blob(mbNvsHandle, parKey, (void*)paramNew, (sizeof(paramNew)));
                        }
                    }
                    ESP_LOGD(TAG, "MB_set_ASCII_data: %s, error(%x)", parKey, (int16_t)error);
                    break;
            } // switch(parType)
        } // if((memcmp(paramNew, paramOld, parInfo->size) != 0) &&
        // If saving was successful then commit changes to NVS
        if ((error == ESP_OK) || (forceUpdate > 0)) {
            nvs_commit(mbNvsHandle);
        }
    }
    return error;
}

// Reads parameter data into variable pointed by paramData and returns an error code
esp_err_t NvManager::readParameter(tLookupRegisters *parInfo, void* paramData)
{
    assert(parInfo != NULL);
    assert(paramData != NULL);
    ESP_ERROR_CHECK(nvsInitStatus); // Check if nvs initialized correctly

    // Get parameter type
    uint8_t parType = parInfo->type;
    const char* parKey = parInfo->parKey;

    // Temporary parameter data buffer
    uint8_t tempParameter[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    switch(parType) {
        case LKUP_TYPE_U8:
            error = nvs_get_u8(mbNvsHandle, parKey, (uint8_t*)&tempParameter[0]);
            ESP_LOGD(TAG, "MB_get_U8_data: %s, %u %d", parKey, *(uint8_t*)&tempParameter[0], (int16_t)error);
            break;
        case LKUP_TYPE_U16:
            error = nvs_get_u16(mbNvsHandle, parKey, (uint16_t*)&tempParameter[0]);
            ESP_LOGD(TAG, "MB_get_U16_data: %s, %u %d", parKey, *(uint16_t*)&tempParameter[0], (int16_t)error );
            break;
        case LKUP_TYPE_U32:
            error = nvs_get_u32(mbNvsHandle, parKey, (uint32_t*)&tempParameter[0]);
            ESP_LOGD(TAG, "MB_get_U32_data: %s, %u %d", parKey, *(uint32_t*)&tempParameter[0], (int16_t)error);
            break;
        case LKUP_TYPE_FLOAT:
            // There is no function to read float then will read U32
            error = nvs_get_u32(mbNvsHandle, parKey, (uint32_t*)&tempParameter[0]);
            ESP_LOGD(TAG, "MB_get_FLOAT_data: %s, %f %d", parKey, *(float*)&tempParameter[0], (int16_t)error);
            break;
        case LKUP_TYPE_ASCII:
            /*
            // Todo: Use blob instead of string to store data (avoid size limitation)
            size_t size = (parInfo->size >= sizeof(tempParameter)) ? sizeof(tempParameter): parInfo->size;
            error = nvs_get_str(mbNvsHandle, parKey, (char*)&tempParameter[0], &size);
            tempParameter[size - 1] = 0; // Terminate parameter string
            ESP_LOGD(TAG, "MB_get_ASCII_data: %s, %s, %d", parKey, (char*)&tempParameter[0], (int16_t)error);
            */
            size_t size = 0;  // value will default to 0, if not set yet in NVS
            error = nvs_get_blob(mbNvsHandle, parKey, NULL, &size);
            if((error != ESP_OK) && (error != ESP_ERR_NVS_NOT_FOUND)) {
                return error;
            }
            if (size > 0) {
                // Get blob data to local buffer
                error = nvs_get_blob(mbNvsHandle, parKey, (void*)&tempParameter[0], &size);
                if (error == ESP_OK) {
                    // The blob data is in temporary parameter buffer
                }
            } else {
                // Clear data if blob is blank
                ATOMIC_BLOCK {
                    memset(paramData, 0, parInfo->size);
                }
            }
            ESP_LOGD(TAG, "MB_set_ASCII_data: %s, %d", parKey, (int16_t)error);
            break;
    }
    // Copy temporary parameter to parameter data if read was successful
    if(error == ESP_OK) {
        assert(parInfo->size <= MB_PAR_MAX_SIZE);
        ATOMIC_BLOCK {
            // Copy blob data into parameter
            // It uses critical section to modify external parameter data
            memcpy(paramData, &tempParameter[0], parInfo->size);
        }
    }
    return error;
}

// The method to set default parameter value into NV memory
template <typename T>
esp_err_t NvManager::writePar(T* addr, T data)
{ 
    tLookupRegisters* pItem = NULL; // Init param description structure
    esp_err_t result = ESP_OK;
    T dataTemp = data;
    // The critical section is required to access from different task
    ATOMIC_BLOCK {
      *(addr) = data; // Copy new parameter value into data storage
    }
    pItem = this->getParDescrFromPtr(addr); // Get parameter description from database
    assert(pItem != NULL); 
    assert(sizeof(data) == pItem->size); 
    // Skip writing if parameter is non-static or nonvolatile
    if(pItem->access & (LKUP_ACCESS_TYPE_STATIC | LKUP_ACCESS_TYPE_NV)) {
        error = writeParameter(pItem, (void*)&data, 0);
        if((error != ESP_OK) && (error != ESP_ERR_NVS_NOT_FOUND)) {
            result = error; // Inform about error and exit
        } else { // If write was successful then read parameter back to check correctness
            error = this->readParameter(pItem, (void*)&dataTemp);
            if(ESP_OK == error) {
                if(data == dataTemp) {
                    // Data is correct then exit
                    result = error;
                } else {
                    //printf("NvWriteError: %.5d(%d): 0x%x != 0x%x \r\n", pItem->offset, pItem->nvAddress, dataTemp, data);
                    result = ESP_ERR_INVALID_STATE; // if something went wrong during write
                }
            }
        }
    } 
    return result;
}

// This method writes default parameter values to NV memory
esp_err_t NvManager::initDefault(void)
{
    tLookupRegisters* pItem = NULL;
    //uint16_t nvAddress = 0;
    uint16_t parIndex = 0;
    uint8_t* parData = NULL;
    esp_err_t status = ESP_FAIL;
    ESP_ERROR_CHECK(nvsInitStatus); // Check if nvs initialized correctly

    // Do cycle for all NV parameters
    for(parIndex = 0, pItem = (tLookupRegisters*)pLookupTable; \
                    parIndex < g_numLookupRegisters; parIndex++, pItem++) {
        assert(pItem != NULL); // for debugging
        // Check for static or NV attribute
        if((pItem != NULL) && (pItem->access & LKUP_ACCESS_TYPE_STATIC)) {
            // Get parameter data pointer
            parData = GET_PARAMETER_ADDRESS(pItem);
            // Read parameter from NV memory
            status = writeParameter(pItem, parData, 1);
            ESP_LOGD(TAG, "MB_default_STATIC_param: %s, type=%u, status=%d", (char*)pItem->parKey, \
                                                   (uint8_t)pItem->type, (uint16_t)status);
            if(status != ESP_OK)
            {
                break; // if read was incorrect then break
            }
        } else if((pItem != NULL) && (pItem->access & LKUP_ACCESS_TYPE_NV)) {
            // NV PARAMETER does't have parameter storage in parameters structure
            // Get parameter data pointer
            parData = GET_PARAMETER_ADDRESS(pItem);
            ESP_LOGD(TAG, "MB_default_NV_param: %s, type=%u", (char*)pItem->parKey, (uint8_t)pItem->type);
        } else if((pItem != NULL) && (pItem->access & LKUP_ACCESS_TYPE_DYNAMIC)) {
            // Skip dynamic parameter initialization
            ESP_LOGD(TAG, "MB_default_DYN_param: %s, type=%u", (char*)pItem->parKey, (uint8_t)pItem->type);
        } else {
            // If incorrect parameter type is read then break means error in data dictionary
            assert(0);
        }
    }
    return status;
}

// Reads all non volatile and static values from NV memory to parameter structure
// returns error if read was incorrect and break reading
esp_err_t NvManager::readAllFromNv(void)
{
    tLookupRegisters* pItem = NULL;
    //uint16_t nvAddress = 0;
    uint16_t parIndex = 0;
    uint8_t* parData = NULL;
    esp_err_t status = ESP_FAIL;
    ESP_ERROR_CHECK(nvsInitStatus); // Check if nvs initialized correctly

    // Do cycle for all NV parameters
    for(parIndex = 0, pItem = (tLookupRegisters*)pLookupTable; \
                    parIndex < g_numLookupRegisters; parIndex++, pItem++) {
        assert(pItem != NULL); // for debugging
        // Check for static or NV attribute
        if((pItem != NULL) && (pItem->access & LKUP_ACCESS_TYPE_STATIC)) {
            // Get parameter data pointer
            parData = GET_PARAMETER_ADDRESS(pItem);
            //assert(parData != NULL);
            // Read parameter from NV memory
            status = readParameter(pItem, parData);
            ESP_LOGD(TAG, "MB_init_STATIC_param: %s, type=%u, status=%d", (char*)pItem->parKey, \
                                                    (uint8_t)pItem->type, (uint16_t)status);
            if(status != ESP_OK)
            {
                break; // if read was incorrect then break and do initialization later
            }
        } else if((pItem != NULL) && (pItem->access & LKUP_ACCESS_TYPE_NV)) {
            // NV PARAMETER does't have parameter storage in parameters structure
            // Get parameter data pointer
            parData = GET_PARAMETER_ADDRESS(pItem);
            ESP_LOGD(TAG, "MB_init_NV_param: %s, type=%u", (char*)pItem->parKey, (uint8_t)pItem->type);
            //assert(parData != NULL);
        } else if((pItem != NULL) && (pItem->access & LKUP_ACCESS_TYPE_DYNAMIC)) {
            // Skip dynamic parameter initialization
            ESP_LOGD(TAG, "MB_init_DYN_param: %s, type=%u", (char*)pItem->parKey, (uint8_t)pItem->type);
        } else {
            // If incorrect parameter type is read then break means error in data dictionary
            assert(0);
        }
    }
    return status;
}

// getParDescrFromPtr() - method gets descriptor of MB parameter by its data address
// Input: address of parameter in data structure
// Output: parameter description from lookup table
tLookupRegisters* NvManager::getParDescrFromPtr(void* parAddress)
{
    tLookupRegisters* pItem = NULL;
    assert(parAddress != NULL);
    assert(&holdingRegParams != NULL);
    uint16_t index;
    bool found = false;
    // The cycle for all lines in lookup table to get correct description
    // of system parameter
    for (index = 0, pItem = (tLookupRegisters*)pLookupTable; \
                            index < g_numLookupRegisters; index++, pItem++) {
        if(pItem != NULL) {
            uint32_t offset = (uint32_t)((uint32_t)(parAddress) - (uint32_t)(&holdingRegParams));
            if(offset == pItem->paramOffset) {
                // if parameter index found in the lookup table then stop cycle
                found = true;
                break;
            }
        }
    }
    if (found != true) {
        pItem = NULL;
    }
    // NULL - means not found
    return  pItem;
}

// Below are the wrapper functions for executions of methods from pure "C" code
extern "C" {
// extern C declarations
}
