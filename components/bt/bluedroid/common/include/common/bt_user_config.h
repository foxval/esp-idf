// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
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

#ifndef __BT_USER_CONFIG_H__
#define __BT_USER_CONFIG_H__




/* All the configuration from SDK defined here */

#include "sdkconfig.h"
#include "esp_task.h"


/**********************************************************
 * Thread/Task reference
 **********************************************************/
#ifdef CONFIG_BLUEDROID_PINNED_TO_CORE
#define UC_TASK_PINNED_TO_CORE              (CONFIG_BLUEDROID_PINNED_TO_CORE < portNUM_PROCESSORS ? CONFIG_BLUEDROID_PINNED_TO_CORE : tskNO_AFFINITY)
#else
#define UC_TASK_PINNED_TO_CORE              (0)
#endif

#ifdef CONFIG_BTC_TASK_STACK_SIZE
#define UC_BTC_TASK_STACK_SIZE              CONFIG_BTC_TASK_STACK_SIZE
#else
#define UC_BTC_TASK_STACK_SIZE              3072
#endif

#ifdef CONFIG_A2DP_SINK_TASK_STACK_SIZE
#define UC_A2DP_SINK_TASK_STACK_SIZE        CONFIG_A2DP_SINK_TASK_STACK_SIZE
#else
#define UC_A2DP_SINK_TASK_STACK_SIZE        2048
#endif
#ifdef CONFIG_A2DP_SOURCE_TASK_STACK_SIZE
#define UC_A2DP_SOURCE_TASK_STACK_SIZE      CONFIG_A2DP_SOURCE_TASK_STACK_SIZE
#else
#define UC_A2DP_SOURCE_TASK_STACK_SIZE      2048
#endif

/**********************************************************
 * Profile reference
 **********************************************************/
//Classic BT reference
#ifdef CONFIG_CLASSIC_BT_ENABLED
#define UC_CLASSIC_BT_ENABLED               TRUE
#else
#define UC_CLASSIC_BT_ENABLED               FALSE
#endif

//A2DP
#ifdef CONFIG_A2DP_ENABLE
#define UC_A2DP_ENABLED                     TRUE
#else
#define UC_A2DP_ENABLED                     FALSE
#endif

//SPP
#ifdef CONFIG_BT_SPP_ENABLED
#define UC_BT_SPP_ENABLED                   TRUE
#else
#define UC_BT_SPP_ENABLED                   FALSE
#endif

//HFP
#ifdef CONFIG_HFP_CLIENT_ENABLE
#define UC_HFP_CLIENT_ENABLED               TRUE
#else
#define UC_HFP_CLIENT_ENABLED               FALSE
#endif


//GATTS
#ifdef CONFIG_GATTS_ENABLE
#define UC_GATTS_ENABLED                    TRUE
#else
#define UC_GATTS_ENABLED                    FALSE
#endif

//GATTC
#ifdef CONFIG_GATTC_ENABLE
#define UC_GATTC_ENABLED                    TRUE
#else
#define UC_GATTC_ENABLED                    FALSE
#endif

//GATTC CACHE
#ifdef CONFIG_GATTC_CACHE_NVS_FLASH
#define UC_GATTC_CACHE_NVS_FLASH_ENABLED    TRUE
#else
#define UC_GATTC_CACHE_NVS_FLASH_ENABLED    FALSE
#endif

//SMP
#ifdef CONFIG_SMP_ENABLE
#define UC_SMP_ENABLED                      TRUE
#else
#define UC_SMP_ENABLED                      FALSE
#endif


//BT ACL CONNECTIONS
#ifdef CONFIG_BT_ACL_CONNECTIONS
#define UC_BT_ACL_CONNECTIONS               CONFIG_BT_ACL_CONNECTIONS
#else
#define UC_BT_ACL_CONNECTIONS               5
#endif

//HOST QUEUE CONGEST CHECK
#ifdef CONFIG_BLE_HOST_QUEUE_CONGESTION_CHECK
#define UC_BLE_HOST_QUEUE_CONGESTION_CHECK  TRUE
#else
#define UC_BLE_HOST_QUEUE_CONGESTION_CHECK  FALSE
#endif


//SCO VOICE OVER HCI
#ifdef CONFIG_HFP_AUDIO_DATA_PATH_HCI
#define UC_AUDIO_DATA_PATH_HCI              TRUE
#else
#define UC_AUDIO_DATA_PATH_HCI              FALSE
#endif


/**********************************************************
 * Memory reference
 **********************************************************/
//DYNAMIC ENV ALLOCATOR
#ifdef CONFIG_BT_BLE_DYNAMIC_ENV_MEMORY
#define UC_BT_BLE_DYNAMIC_ENV_MEMORY        TRUE
#else
#define UC_BT_BLE_DYNAMIC_ENV_MEMORY        FALSE
#endif

//MEMORY ALLOCATOR
#ifdef CONFIG_BT_ALLOCATION_FROM_SPIRAM_FIRST
#define UC_HEAP_ALLOCATION_FROM_SPIRAM_FIRST     TRUE
#else
#define UC_HEAP_ALLOCATION_FROM_SPIRAM_FIRST     FALSE
#endif

//MEMORY DEBUG
#ifdef CONFIG_BLUEDROID_MEM_DEBUG
#define UC_HEAP_MEMORY_DEBUG                TRUE
#else
#define UC_BLUEDROID_MEM_DEBUG              FALSE
#endif


/**********************************************************
 * Trace reference
 **********************************************************/
#ifdef CONFIG_LOG_DEFAULT_LEVEL
#define UC_LOG_DEFAULT_LEVEL                CONFIG_LOG_DEFAULT_LEVEL
#else
#define UC_LOG_DEFAULT_LEVEL                3
#endif
#ifdef CONFIG_LOG_BOOTLOADER_LEVEL
#define UC_LOG_BOOTLOADER_LEVEL             CONFIG_LOG_BOOTLOADER_LEVEL
#else
#define UC_LOG_BOOTLOADER_LEVEL             3
#endif

#ifdef CONFIG_BT_STACK_NO_LOG
#define UC_BT_STACK_NO_LOG                  CONFIG_BT_STACK_NO_LOG
#else
#define UC_BT_STACK_NO_LOG                  FALSE
#endif

#define UC_TRACE_LEVEL_NONE                 0          /* No trace messages to be generated    */
#define UC_TRACE_LEVEL_ERROR                1          /* Error condition trace messages       */
#define UC_TRACE_LEVEL_WARNING              2          /* Warning condition trace messages     */
#define UC_TRACE_LEVEL_API                  3          /* API traces                           */
#define UC_TRACE_LEVEL_EVENT                4          /* Debug messages for events            */
#define UC_TRACE_LEVEL_DEBUG                5          /* Full debug messages                  */
#define UC_TRACE_LEVEL_VERBOSE              6          /* Verbose debug messages               */

#ifdef CONFIG_HCI_INITIAL_TRACE_LEVEL
#define UC_HCI_INITIAL_TRACE_LEVEL          CONFIG_HCI_INITIAL_TRACE_LEVEL
#else
#define UC_HCI_INITIAL_TRACE_LEVEL          UC_TRACE_LEVEL_WARNING
#endif

#ifdef CONFIG_BTM_INITIAL_TRACE_LEVEL
#define UC_BTM_INITIAL_TRACE_LEVEL          CONFIG_BTM_INITIAL_TRACE_LEVEL
#else
#define UC_BTM_INITIAL_TRACE_LEVEL          UC_TRACE_LEVEL_WARNING
#endif

#ifdef CONFIG_L2CAP_INITIAL_TRACE_LEVEL
#define UC_L2CAP_INITIAL_TRACE_LEVEL        CONFIG_L2CAP_INITIAL_TRACE_LEVEL
#else
#define UC_L2CAP_INITIAL_TRACE_LEVEL        UC_TRACE_LEVEL_WARNING
#endif

#ifdef CONFIG_RFCOMM_INITIAL_TRACE_LEVEL
#define UC_RFCOMM_INITIAL_TRACE_LEVEL       CONFIG_RFCOMM_INITIAL_TRACE_LEVEL
#else
#define UC_RFCOMM_INITIAL_TRACE_LEVEL       UC_TRACE_LEVEL_WARNING
#endif

#ifdef CONFIG_SDP_INITIAL_TRACE_LEVEL
#define UC_SDP_INITIAL_TRACE_LEVEL          CONFIG_SDP_INITIAL_TRACE_LEVEL
#else
#define UC_SDP_INITIAL_TRACE_LEVEL          UC_TRACE_LEVEL_WARNING
#endif

#ifdef CONFIG_GAP_INITIAL_TRACE_LEVEL
#define UC_GAP_INITIAL_TRACE_LEVEL          CONFIG_GAP_INITIAL_TRACE_LEVEL
#else
#define UC_GAP_INITIAL_TRACE_LEVEL          UC_TRACE_LEVEL_WARNING
#endif

#ifdef CONFIG_BNEP_INITIAL_TRACE_LEVEL
#define UC_BNEP_INITIAL_TRACE_LEVEL         CONFIG_BNEP_INITIAL_TRACE_LEVEL
#else
#define UC_BNEP_INITIAL_TRACE_LEVEL         UC_TRACE_LEVEL_WARNING
#endif

#ifdef CONFIG_PAN_INITIAL_TRACE_LEVEL
#define UC_PAN_INITIAL_TRACE_LEVEL          CONFIG_PAN_INITIAL_TRACE_LEVEL
#else
#define UC_PAN_INITIAL_TRACE_LEVEL          UC_TRACE_LEVEL_WARNING
#endif

#ifdef CONFIG_A2D_INITIAL_TRACE_LEVEL
#define UC_A2D_INITIAL_TRACE_LEVEL          CONFIG_A2D_INITIAL_TRACE_LEVEL
#else
#define UC_A2D_INITIAL_TRACE_LEVEL          UC_TRACE_LEVEL_WARNING
#endif

#ifdef CONFIG_AVDT_INITIAL_TRACE_LEVEL
#define UC_AVDT_INITIAL_TRACE_LEVEL         CONFIG_AVDT_INITIAL_TRACE_LEVEL
#else
#define UC_AVDT_INITIAL_TRACE_LEVEL         UC_TRACE_LEVEL_WARNING
#endif

#ifdef CONFIG_AVCT_INITIAL_TRACE_LEVEL
#define UC_AVCT_INITIAL_TRACE_LEVEL         CONFIG_AVCT_INITIAL_TRACE_LEVEL
#else
#define UC_AVCT_INITIAL_TRACE_LEVEL         UC_TRACE_LEVEL_WARNING
#endif

#ifdef CONFIG_AVRC_INITIAL_TRACE_LEVEL
#define UC_AVRC_INITIAL_TRACE_LEVEL         CONFIG_AVRC_INITIAL_TRACE_LEVEL
#else
#define UC_AVRC_INITIAL_TRACE_LEVEL         UC_TRACE_LEVEL_WARNING
#endif

#ifdef CONFIG_MCA_INITIAL_TRACE_LEVEL
#define UC_MCA_INITIAL_TRACE_LEVEL          CONFIG_MCA_INITIAL_TRACE_LEVEL
#else
#define UC_MCA_INITIAL_TRACE_LEVEL          UC_TRACE_LEVEL_WARNING
#endif

#ifdef CONFIG_HID_INITIAL_TRACE_LEVEL
#define UC_HID_INITIAL_TRACE_LEVEL          CONFIG_HID_INITIAL_TRACE_LEVEL
#else
#define UC_HID_INITIAL_TRACE_LEVEL          UC_TRACE_LEVEL_WARNING
#endif

#ifdef CONFIG_APPL_INITIAL_TRACE_LEVEL
#define UC_APPL_INITIAL_TRACE_LEVEL         CONFIG_APPL_INITIAL_TRACE_LEVEL
#else
#define UC_APPL_INITIAL_TRACE_LEVEL         UC_TRACE_LEVEL_WARNING
#endif

#ifdef CONFIG_GATT_INITIAL_TRACE_LEVEL
#define UC_GATT_INITIAL_TRACE_LEVEL         CONFIG_GATT_INITIAL_TRACE_LEVEL
#else
#define UC_GATT_INITIAL_TRACE_LEVEL         UC_TRACE_LEVEL_WARNING
#endif

#ifdef CONFIG_SMP_INITIAL_TRACE_LEVEL
#define UC_SMP_INITIAL_TRACE_LEVEL          CONFIG_SMP_INITIAL_TRACE_LEVEL
#else
#define UC_SMP_INITIAL_TRACE_LEVEL          UC_TRACE_LEVEL_WARNING
#endif

#ifdef CONFIG_BTIF_INITIAL_TRACE_LEVEL
#define UC_BTIF_INITIAL_TRACE_LEVEL         CONFIG_BTIF_INITIAL_TRACE_LEVEL
#else
#define UC_BTIF_INITIAL_TRACE_LEVEL         UC_TRACE_LEVEL_WARNING
#endif

#ifdef CONFIG_BTC_INITIAL_TRACE_LEVEL
#define UC_BTC_INITIAL_TRACE_LEVEL          CONFIG_BTC_INITIAL_TRACE_LEVEL
#else
#define UC_BTC_INITIAL_TRACE_LEVEL          UC_TRACE_LEVEL_WARNING
#endif

#ifdef CONFIG_OSI_INITIAL_TRACE_LEVEL
#define UC_OSI_INITIAL_TRACE_LEVEL          CONFIG_OSI_INITIAL_TRACE_LEVEL
#else
#define UC_OSI_INITIAL_TRACE_LEVEL          UC_TRACE_LEVEL_WARNING
#endif

#ifdef CONFIG_BLUFI_INITIAL_TRACE_LEVEL
#define UC_BLUFI_INITIAL_TRACE_LEVEL        CONFIG_BLUFI_INITIAL_TRACE_LEVEL
#else
#define UC_BLUFI_INITIAL_TRACE_LEVEL        UC_TRACE_LEVEL_WARNING
#endif


#endif /* __BT_USER_CONFIG_H__ */



