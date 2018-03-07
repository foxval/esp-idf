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
#ifndef _SOC_RTC_IO_REG_H_
#define _SOC_RTC_IO_REG_H_


#ifdef __cplusplus
extern "C" {
#endif
#include "soc.h"
#define RTC_GPIO_OUT_REG          (DR_REG_RTCIO_BASE + 0x0)
/* RTC_GPIO_OUT_DATA : R/W ;bitpos:[31:14] ;default: 0 ; */
/*description: RTC GPIO 0 ~ 17 output data*/
#define RTC_GPIO_OUT_DATA  0x0003FFFF
#define RTC_GPIO_OUT_DATA_M  ((RTC_GPIO_OUT_DATA_V)<<(RTC_GPIO_OUT_DATA_S))
#define RTC_GPIO_OUT_DATA_V  0x3FFFF
#define RTC_GPIO_OUT_DATA_S  14

#define RTC_GPIO_OUT_W1TS_REG          (DR_REG_RTCIO_BASE + 0x4)
/* RTC_GPIO_OUT_DATA_W1TS : WO ;bitpos:[31:14] ;default: 0 ; */
/*description: RTC GPIO 0 ~ 17 output data write 1 to set*/
#define RTC_GPIO_OUT_DATA_W1TS  0x0003FFFF
#define RTC_GPIO_OUT_DATA_W1TS_M  ((RTC_GPIO_OUT_DATA_W1TS_V)<<(RTC_GPIO_OUT_DATA_W1TS_S))
#define RTC_GPIO_OUT_DATA_W1TS_V  0x3FFFF
#define RTC_GPIO_OUT_DATA_W1TS_S  14

#define RTC_GPIO_OUT_W1TC_REG          (DR_REG_RTCIO_BASE + 0x8)
/* RTC_GPIO_OUT_DATA_W1TC : WO ;bitpos:[31:14] ;default: 0 ; */
/*description: RTC GPIO 0 ~ 17 output data write 1 to clear*/
#define RTC_GPIO_OUT_DATA_W1TC  0x0003FFFF
#define RTC_GPIO_OUT_DATA_W1TC_M  ((RTC_GPIO_OUT_DATA_W1TC_V)<<(RTC_GPIO_OUT_DATA_W1TC_S))
#define RTC_GPIO_OUT_DATA_W1TC_V  0x3FFFF
#define RTC_GPIO_OUT_DATA_W1TC_S  14

#define RTC_GPIO_ENABLE_REG          (DR_REG_RTCIO_BASE + 0xc)
/* RTC_GPIO_ENABLE : R/W ;bitpos:[31:14] ;default: 0 ; */
/*description: RTC GPIO 0 ~ 17 enable*/
#define RTC_GPIO_ENABLE  0x0003FFFF
#define RTC_GPIO_ENABLE_M  ((RTC_GPIO_ENABLE_V)<<(RTC_GPIO_ENABLE_S))
#define RTC_GPIO_ENABLE_V  0x3FFFF
#define RTC_GPIO_ENABLE_S  14

#define RTC_GPIO_ENABLE_W1TS_REG          (DR_REG_RTCIO_BASE + 0x10)
/* RTC_GPIO_ENABLE_W1TS : WO ;bitpos:[31:14] ;default: 0 ; */
/*description: RTC GPIO 0 ~ 17 enable write 1 to set*/
#define RTC_GPIO_ENABLE_W1TS  0x0003FFFF
#define RTC_GPIO_ENABLE_W1TS_M  ((RTC_GPIO_ENABLE_W1TS_V)<<(RTC_GPIO_ENABLE_W1TS_S))
#define RTC_GPIO_ENABLE_W1TS_V  0x3FFFF
#define RTC_GPIO_ENABLE_W1TS_S  14

#define RTC_GPIO_ENABLE_W1TC_REG          (DR_REG_RTCIO_BASE + 0x14)
/* RTC_GPIO_ENABLE_W1TC : WO ;bitpos:[31:14] ;default: 0 ; */
/*description: RTC GPIO 0 ~ 17 enable write 1 to clear*/
#define RTC_GPIO_ENABLE_W1TC  0x0003FFFF
#define RTC_GPIO_ENABLE_W1TC_M  ((RTC_GPIO_ENABLE_W1TC_V)<<(RTC_GPIO_ENABLE_W1TC_S))
#define RTC_GPIO_ENABLE_W1TC_V  0x3FFFF
#define RTC_GPIO_ENABLE_W1TC_S  14

#define RTC_GPIO_STATUS_REG          (DR_REG_RTCIO_BASE + 0x18)
/* RTC_GPIO_STATUS_INT : R/W ;bitpos:[31:14] ;default: 0 ; */
/*description: RTC GPIO 0 ~ 17 interrupt status*/
#define RTC_GPIO_STATUS_INT  0x0003FFFF
#define RTC_GPIO_STATUS_INT_M  ((RTC_GPIO_STATUS_INT_V)<<(RTC_GPIO_STATUS_INT_S))
#define RTC_GPIO_STATUS_INT_V  0x3FFFF
#define RTC_GPIO_STATUS_INT_S  14

#define RTC_GPIO_STATUS_W1TS_REG          (DR_REG_RTCIO_BASE + 0x1c)
/* RTC_GPIO_STATUS_INT_W1TS : WO ;bitpos:[31:14] ;default: 0 ; */
/*description: RTC GPIO 0 ~ 17 interrupt status write 1 to set*/
#define RTC_GPIO_STATUS_INT_W1TS  0x0003FFFF
#define RTC_GPIO_STATUS_INT_W1TS_M  ((RTC_GPIO_STATUS_INT_W1TS_V)<<(RTC_GPIO_STATUS_INT_W1TS_S))
#define RTC_GPIO_STATUS_INT_W1TS_V  0x3FFFF
#define RTC_GPIO_STATUS_INT_W1TS_S  14

#define RTC_GPIO_STATUS_W1TC_REG          (DR_REG_RTCIO_BASE + 0x20)
/* RTC_GPIO_STATUS_INT_W1TC : WO ;bitpos:[31:14] ;default: 0 ; */
/*description: RTC GPIO 0 ~ 17 interrupt status write 1 to clear*/
#define RTC_GPIO_STATUS_INT_W1TC  0x0003FFFF
#define RTC_GPIO_STATUS_INT_W1TC_M  ((RTC_GPIO_STATUS_INT_W1TC_V)<<(RTC_GPIO_STATUS_INT_W1TC_S))
#define RTC_GPIO_STATUS_INT_W1TC_V  0x3FFFF
#define RTC_GPIO_STATUS_INT_W1TC_S  14

#define RTC_GPIO_IN_REG          (DR_REG_RTCIO_BASE + 0x24)
/* RTC_GPIO_IN_NEXT : RO ;bitpos:[31:14] ;default:  ; */
/*description: RTC GPIO input data*/
#define RTC_GPIO_IN_NEXT  0x0003FFFF
#define RTC_GPIO_IN_NEXT_M  ((RTC_GPIO_IN_NEXT_V)<<(RTC_GPIO_IN_NEXT_S))
#define RTC_GPIO_IN_NEXT_V  0x3FFFF
#define RTC_GPIO_IN_NEXT_S  14

#define RTC_GPIO_PIN0_REG          (DR_REG_RTCIO_BASE + 0x28)
/* RTC_GPIO_PIN0_WAKEUP_ENABLE : R/W ;bitpos:[10] ;default: 0 ; */
/*description: RTC GPIO wakeup enable bit*/
#define RTC_GPIO_PIN0_WAKEUP_ENABLE  (BIT(10))
#define RTC_GPIO_PIN0_WAKEUP_ENABLE_M  (BIT(10))
#define RTC_GPIO_PIN0_WAKEUP_ENABLE_V  0x1
#define RTC_GPIO_PIN0_WAKEUP_ENABLE_S  10
/* RTC_GPIO_PIN0_INT_TYPE : R/W ;bitpos:[9:7] ;default: 0 ; */
/*description: if set to 0: GPIO interrupt disable   if set to 1: rising edge
 trigger   if set to 2: falling edge trigger  if set to 3: any edge trigger  if set to 4: low level trigger   if set to 5: high level trigger*/
#define RTC_GPIO_PIN0_INT_TYPE  0x00000007
#define RTC_GPIO_PIN0_INT_TYPE_M  ((RTC_GPIO_PIN0_INT_TYPE_V)<<(RTC_GPIO_PIN0_INT_TYPE_S))
#define RTC_GPIO_PIN0_INT_TYPE_V  0x7
#define RTC_GPIO_PIN0_INT_TYPE_S  7
/* RTC_GPIO_PIN0_PAD_DRIVER : R/W ;bitpos:[2] ;default: 0 ; */
/*description: if set to 0: normal output  if set to 1: open drain*/
#define RTC_GPIO_PIN0_PAD_DRIVER  (BIT(2))
#define RTC_GPIO_PIN0_PAD_DRIVER_M  (BIT(2))
#define RTC_GPIO_PIN0_PAD_DRIVER_V  0x1
#define RTC_GPIO_PIN0_PAD_DRIVER_S  2

#define RTC_GPIO_PIN1_REG          (DR_REG_RTCIO_BASE + 0x2c)
/* RTC_GPIO_PIN1_WAKEUP_ENABLE : R/W ;bitpos:[10] ;default: 0 ; */
/*description: RTC GPIO wakeup enable bit*/
#define RTC_GPIO_PIN1_WAKEUP_ENABLE  (BIT(10))
#define RTC_GPIO_PIN1_WAKEUP_ENABLE_M  (BIT(10))
#define RTC_GPIO_PIN1_WAKEUP_ENABLE_V  0x1
#define RTC_GPIO_PIN1_WAKEUP_ENABLE_S  10
/* RTC_GPIO_PIN1_INT_TYPE : R/W ;bitpos:[9:7] ;default: 0 ; */
/*description: if set to 0: GPIO interrupt disable   if set to 1: rising edge
 trigger   if set to 2: falling edge trigger  if set to 3: any edge trigger  if set to 4: low level trigger   if set to 5: high level trigger*/
#define RTC_GPIO_PIN1_INT_TYPE  0x00000007
#define RTC_GPIO_PIN1_INT_TYPE_M  ((RTC_GPIO_PIN1_INT_TYPE_V)<<(RTC_GPIO_PIN1_INT_TYPE_S))
#define RTC_GPIO_PIN1_INT_TYPE_V  0x7
#define RTC_GPIO_PIN1_INT_TYPE_S  7
/* RTC_GPIO_PIN1_PAD_DRIVER : R/W ;bitpos:[2] ;default: 0 ; */
/*description: if set to 0: normal output  if set to 1: open drain*/
#define RTC_GPIO_PIN1_PAD_DRIVER  (BIT(2))
#define RTC_GPIO_PIN1_PAD_DRIVER_M  (BIT(2))
#define RTC_GPIO_PIN1_PAD_DRIVER_V  0x1
#define RTC_GPIO_PIN1_PAD_DRIVER_S  2

#define RTC_GPIO_PIN2_REG          (DR_REG_RTCIO_BASE + 0x30)
/* RTC_GPIO_PIN2_WAKEUP_ENABLE : R/W ;bitpos:[10] ;default: 0 ; */
/*description: RTC GPIO wakeup enable bit*/
#define RTC_GPIO_PIN2_WAKEUP_ENABLE  (BIT(10))
#define RTC_GPIO_PIN2_WAKEUP_ENABLE_M  (BIT(10))
#define RTC_GPIO_PIN2_WAKEUP_ENABLE_V  0x1
#define RTC_GPIO_PIN2_WAKEUP_ENABLE_S  10
/* RTC_GPIO_PIN2_INT_TYPE : R/W ;bitpos:[9:7] ;default: 0 ; */
/*description: if set to 0: GPIO interrupt disable   if set to 1: rising edge
 trigger   if set to 2: falling edge trigger  if set to 3: any edge trigger  if set to 4: low level trigger   if set to 5: high level trigger*/
#define RTC_GPIO_PIN2_INT_TYPE  0x00000007
#define RTC_GPIO_PIN2_INT_TYPE_M  ((RTC_GPIO_PIN2_INT_TYPE_V)<<(RTC_GPIO_PIN2_INT_TYPE_S))
#define RTC_GPIO_PIN2_INT_TYPE_V  0x7
#define RTC_GPIO_PIN2_INT_TYPE_S  7
/* RTC_GPIO_PIN2_PAD_DRIVER : R/W ;bitpos:[2] ;default: 0 ; */
/*description: if set to 0: normal output  if set to 1: open drain*/
#define RTC_GPIO_PIN2_PAD_DRIVER  (BIT(2))
#define RTC_GPIO_PIN2_PAD_DRIVER_M  (BIT(2))
#define RTC_GPIO_PIN2_PAD_DRIVER_V  0x1
#define RTC_GPIO_PIN2_PAD_DRIVER_S  2

#define RTC_GPIO_PIN3_REG          (DR_REG_RTCIO_BASE + 0x34)
/* RTC_GPIO_PIN3_WAKEUP_ENABLE : R/W ;bitpos:[10] ;default: 0 ; */
/*description: RTC GPIO wakeup enable bit*/
#define RTC_GPIO_PIN3_WAKEUP_ENABLE  (BIT(10))
#define RTC_GPIO_PIN3_WAKEUP_ENABLE_M  (BIT(10))
#define RTC_GPIO_PIN3_WAKEUP_ENABLE_V  0x1
#define RTC_GPIO_PIN3_WAKEUP_ENABLE_S  10
/* RTC_GPIO_PIN3_INT_TYPE : R/W ;bitpos:[9:7] ;default: 0 ; */
/*description: if set to 0: GPIO interrupt disable   if set to 1: rising edge
 trigger   if set to 2: falling edge trigger  if set to 3: any edge trigger  if set to 4: low level trigger   if set to 5: high level trigger*/
#define RTC_GPIO_PIN3_INT_TYPE  0x00000007
#define RTC_GPIO_PIN3_INT_TYPE_M  ((RTC_GPIO_PIN3_INT_TYPE_V)<<(RTC_GPIO_PIN3_INT_TYPE_S))
#define RTC_GPIO_PIN3_INT_TYPE_V  0x7
#define RTC_GPIO_PIN3_INT_TYPE_S  7
/* RTC_GPIO_PIN3_PAD_DRIVER : R/W ;bitpos:[2] ;default: 0 ; */
/*description: if set to 0: normal output  if set to 1: open drain*/
#define RTC_GPIO_PIN3_PAD_DRIVER  (BIT(2))
#define RTC_GPIO_PIN3_PAD_DRIVER_M  (BIT(2))
#define RTC_GPIO_PIN3_PAD_DRIVER_V  0x1
#define RTC_GPIO_PIN3_PAD_DRIVER_S  2

#define RTC_GPIO_PIN4_REG          (DR_REG_RTCIO_BASE + 0x38)
/* RTC_GPIO_PIN4_WAKEUP_ENABLE : R/W ;bitpos:[10] ;default: 0 ; */
/*description: RTC GPIO wakeup enable bit*/
#define RTC_GPIO_PIN4_WAKEUP_ENABLE  (BIT(10))
#define RTC_GPIO_PIN4_WAKEUP_ENABLE_M  (BIT(10))
#define RTC_GPIO_PIN4_WAKEUP_ENABLE_V  0x1
#define RTC_GPIO_PIN4_WAKEUP_ENABLE_S  10
/* RTC_GPIO_PIN4_INT_TYPE : R/W ;bitpos:[9:7] ;default: 0 ; */
/*description: if set to 0: GPIO interrupt disable   if set to 1: rising edge
 trigger   if set to 2: falling edge trigger  if set to 3: any edge trigger  if set to 4: low level trigger   if set to 5: high level trigger*/
#define RTC_GPIO_PIN4_INT_TYPE  0x00000007
#define RTC_GPIO_PIN4_INT_TYPE_M  ((RTC_GPIO_PIN4_INT_TYPE_V)<<(RTC_GPIO_PIN4_INT_TYPE_S))
#define RTC_GPIO_PIN4_INT_TYPE_V  0x7
#define RTC_GPIO_PIN4_INT_TYPE_S  7
/* RTC_GPIO_PIN4_PAD_DRIVER : R/W ;bitpos:[2] ;default: 0 ; */
/*description: if set to 0: normal output  if set to 1: open drain*/
#define RTC_GPIO_PIN4_PAD_DRIVER  (BIT(2))
#define RTC_GPIO_PIN4_PAD_DRIVER_M  (BIT(2))
#define RTC_GPIO_PIN4_PAD_DRIVER_V  0x1
#define RTC_GPIO_PIN4_PAD_DRIVER_S  2

#define RTC_GPIO_PIN5_REG          (DR_REG_RTCIO_BASE + 0x3c)
/* RTC_GPIO_PIN5_WAKEUP_ENABLE : R/W ;bitpos:[10] ;default: 0 ; */
/*description: RTC GPIO wakeup enable bit*/
#define RTC_GPIO_PIN5_WAKEUP_ENABLE  (BIT(10))
#define RTC_GPIO_PIN5_WAKEUP_ENABLE_M  (BIT(10))
#define RTC_GPIO_PIN5_WAKEUP_ENABLE_V  0x1
#define RTC_GPIO_PIN5_WAKEUP_ENABLE_S  10
/* RTC_GPIO_PIN5_INT_TYPE : R/W ;bitpos:[9:7] ;default: 0 ; */
/*description: if set to 0: GPIO interrupt disable   if set to 1: rising edge
 trigger   if set to 2: falling edge trigger  if set to 3: any edge trigger  if set to 4: low level trigger   if set to 5: high level trigger*/
#define RTC_GPIO_PIN5_INT_TYPE  0x00000007
#define RTC_GPIO_PIN5_INT_TYPE_M  ((RTC_GPIO_PIN5_INT_TYPE_V)<<(RTC_GPIO_PIN5_INT_TYPE_S))
#define RTC_GPIO_PIN5_INT_TYPE_V  0x7
#define RTC_GPIO_PIN5_INT_TYPE_S  7
/* RTC_GPIO_PIN5_PAD_DRIVER : R/W ;bitpos:[2] ;default: 0 ; */
/*description: if set to 0: normal output  if set to 1: open drain*/
#define RTC_GPIO_PIN5_PAD_DRIVER  (BIT(2))
#define RTC_GPIO_PIN5_PAD_DRIVER_M  (BIT(2))
#define RTC_GPIO_PIN5_PAD_DRIVER_V  0x1
#define RTC_GPIO_PIN5_PAD_DRIVER_S  2

#define RTC_GPIO_PIN6_REG          (DR_REG_RTCIO_BASE + 0x40)
/* RTC_GPIO_PIN6_WAKEUP_ENABLE : R/W ;bitpos:[10] ;default: 0 ; */
/*description: RTC GPIO wakeup enable bit*/
#define RTC_GPIO_PIN6_WAKEUP_ENABLE  (BIT(10))
#define RTC_GPIO_PIN6_WAKEUP_ENABLE_M  (BIT(10))
#define RTC_GPIO_PIN6_WAKEUP_ENABLE_V  0x1
#define RTC_GPIO_PIN6_WAKEUP_ENABLE_S  10
/* RTC_GPIO_PIN6_INT_TYPE : R/W ;bitpos:[9:7] ;default: 0 ; */
/*description: if set to 0: GPIO interrupt disable   if set to 1: rising edge
 trigger   if set to 2: falling edge trigger  if set to 3: any edge trigger  if set to 4: low level trigger   if set to 5: high level trigger*/
#define RTC_GPIO_PIN6_INT_TYPE  0x00000007
#define RTC_GPIO_PIN6_INT_TYPE_M  ((RTC_GPIO_PIN6_INT_TYPE_V)<<(RTC_GPIO_PIN6_INT_TYPE_S))
#define RTC_GPIO_PIN6_INT_TYPE_V  0x7
#define RTC_GPIO_PIN6_INT_TYPE_S  7
/* RTC_GPIO_PIN6_PAD_DRIVER : R/W ;bitpos:[2] ;default: 0 ; */
/*description: if set to 0: normal output  if set to 1: open drain*/
#define RTC_GPIO_PIN6_PAD_DRIVER  (BIT(2))
#define RTC_GPIO_PIN6_PAD_DRIVER_M  (BIT(2))
#define RTC_GPIO_PIN6_PAD_DRIVER_V  0x1
#define RTC_GPIO_PIN6_PAD_DRIVER_S  2

#define RTC_GPIO_PIN7_REG          (DR_REG_RTCIO_BASE + 0x44)
/* RTC_GPIO_PIN7_WAKEUP_ENABLE : R/W ;bitpos:[10] ;default: 0 ; */
/*description: RTC GPIO wakeup enable bit*/
#define RTC_GPIO_PIN7_WAKEUP_ENABLE  (BIT(10))
#define RTC_GPIO_PIN7_WAKEUP_ENABLE_M  (BIT(10))
#define RTC_GPIO_PIN7_WAKEUP_ENABLE_V  0x1
#define RTC_GPIO_PIN7_WAKEUP_ENABLE_S  10
/* RTC_GPIO_PIN7_INT_TYPE : R/W ;bitpos:[9:7] ;default: 0 ; */
/*description: if set to 0: GPIO interrupt disable   if set to 1: rising edge
 trigger   if set to 2: falling edge trigger  if set to 3: any edge trigger  if set to 4: low level trigger   if set to 5: high level trigger*/
#define RTC_GPIO_PIN7_INT_TYPE  0x00000007
#define RTC_GPIO_PIN7_INT_TYPE_M  ((RTC_GPIO_PIN7_INT_TYPE_V)<<(RTC_GPIO_PIN7_INT_TYPE_S))
#define RTC_GPIO_PIN7_INT_TYPE_V  0x7
#define RTC_GPIO_PIN7_INT_TYPE_S  7
/* RTC_GPIO_PIN7_PAD_DRIVER : R/W ;bitpos:[2] ;default: 0 ; */
/*description: if set to 0: normal output  if set to 1: open drain*/
#define RTC_GPIO_PIN7_PAD_DRIVER  (BIT(2))
#define RTC_GPIO_PIN7_PAD_DRIVER_M  (BIT(2))
#define RTC_GPIO_PIN7_PAD_DRIVER_V  0x1
#define RTC_GPIO_PIN7_PAD_DRIVER_S  2

#define RTC_GPIO_PIN8_REG          (DR_REG_RTCIO_BASE + 0x48)
/* RTC_GPIO_PIN8_WAKEUP_ENABLE : R/W ;bitpos:[10] ;default: 0 ; */
/*description: RTC GPIO wakeup enable bit*/
#define RTC_GPIO_PIN8_WAKEUP_ENABLE  (BIT(10))
#define RTC_GPIO_PIN8_WAKEUP_ENABLE_M  (BIT(10))
#define RTC_GPIO_PIN8_WAKEUP_ENABLE_V  0x1
#define RTC_GPIO_PIN8_WAKEUP_ENABLE_S  10
/* RTC_GPIO_PIN8_INT_TYPE : R/W ;bitpos:[9:7] ;default: 0 ; */
/*description: if set to 0: GPIO interrupt disable   if set to 1: rising edge
 trigger   if set to 2: falling edge trigger  if set to 3: any edge trigger  if set to 4: low level trigger   if set to 5: high level trigger*/
#define RTC_GPIO_PIN8_INT_TYPE  0x00000007
#define RTC_GPIO_PIN8_INT_TYPE_M  ((RTC_GPIO_PIN8_INT_TYPE_V)<<(RTC_GPIO_PIN8_INT_TYPE_S))
#define RTC_GPIO_PIN8_INT_TYPE_V  0x7
#define RTC_GPIO_PIN8_INT_TYPE_S  7
/* RTC_GPIO_PIN8_PAD_DRIVER : R/W ;bitpos:[2] ;default: 0 ; */
/*description: if set to 0: normal output  if set to 1: open drain*/
#define RTC_GPIO_PIN8_PAD_DRIVER  (BIT(2))
#define RTC_GPIO_PIN8_PAD_DRIVER_M  (BIT(2))
#define RTC_GPIO_PIN8_PAD_DRIVER_V  0x1
#define RTC_GPIO_PIN8_PAD_DRIVER_S  2

#define RTC_GPIO_PIN9_REG          (DR_REG_RTCIO_BASE + 0x4c)
/* RTC_GPIO_PIN9_WAKEUP_ENABLE : R/W ;bitpos:[10] ;default: 0 ; */
/*description: RTC GPIO wakeup enable bit*/
#define RTC_GPIO_PIN9_WAKEUP_ENABLE  (BIT(10))
#define RTC_GPIO_PIN9_WAKEUP_ENABLE_M  (BIT(10))
#define RTC_GPIO_PIN9_WAKEUP_ENABLE_V  0x1
#define RTC_GPIO_PIN9_WAKEUP_ENABLE_S  10
/* RTC_GPIO_PIN9_INT_TYPE : R/W ;bitpos:[9:7] ;default: 0 ; */
/*description: if set to 0: GPIO interrupt disable   if set to 1: rising edge
 trigger   if set to 2: falling edge trigger  if set to 3: any edge trigger  if set to 4: low level trigger   if set to 5: high level trigger*/
#define RTC_GPIO_PIN9_INT_TYPE  0x00000007
#define RTC_GPIO_PIN9_INT_TYPE_M  ((RTC_GPIO_PIN9_INT_TYPE_V)<<(RTC_GPIO_PIN9_INT_TYPE_S))
#define RTC_GPIO_PIN9_INT_TYPE_V  0x7
#define RTC_GPIO_PIN9_INT_TYPE_S  7
/* RTC_GPIO_PIN9_PAD_DRIVER : R/W ;bitpos:[2] ;default: 0 ; */
/*description: if set to 0: normal output  if set to 1: open drain*/
#define RTC_GPIO_PIN9_PAD_DRIVER  (BIT(2))
#define RTC_GPIO_PIN9_PAD_DRIVER_M  (BIT(2))
#define RTC_GPIO_PIN9_PAD_DRIVER_V  0x1
#define RTC_GPIO_PIN9_PAD_DRIVER_S  2

#define RTC_GPIO_PIN10_REG          (DR_REG_RTCIO_BASE + 0x50)
/* RTC_GPIO_PIN10_WAKEUP_ENABLE : R/W ;bitpos:[10] ;default: 0 ; */
/*description: RTC GPIO wakeup enable bit*/
#define RTC_GPIO_PIN10_WAKEUP_ENABLE  (BIT(10))
#define RTC_GPIO_PIN10_WAKEUP_ENABLE_M  (BIT(10))
#define RTC_GPIO_PIN10_WAKEUP_ENABLE_V  0x1
#define RTC_GPIO_PIN10_WAKEUP_ENABLE_S  10
/* RTC_GPIO_PIN10_INT_TYPE : R/W ;bitpos:[9:7] ;default: 0 ; */
/*description: if set to 0: GPIO interrupt disable   if set to 1: rising edge
 trigger   if set to 2: falling edge trigger  if set to 3: any edge trigger  if set to 4: low level trigger   if set to 5: high level trigger*/
#define RTC_GPIO_PIN10_INT_TYPE  0x00000007
#define RTC_GPIO_PIN10_INT_TYPE_M  ((RTC_GPIO_PIN10_INT_TYPE_V)<<(RTC_GPIO_PIN10_INT_TYPE_S))
#define RTC_GPIO_PIN10_INT_TYPE_V  0x7
#define RTC_GPIO_PIN10_INT_TYPE_S  7
/* RTC_GPIO_PIN10_PAD_DRIVER : R/W ;bitpos:[2] ;default: 0 ; */
/*description: if set to 0: normal output  if set to 1: open drain*/
#define RTC_GPIO_PIN10_PAD_DRIVER  (BIT(2))
#define RTC_GPIO_PIN10_PAD_DRIVER_M  (BIT(2))
#define RTC_GPIO_PIN10_PAD_DRIVER_V  0x1
#define RTC_GPIO_PIN10_PAD_DRIVER_S  2

#define RTC_GPIO_PIN11_REG          (DR_REG_RTCIO_BASE + 0x54)
/* RTC_GPIO_PIN11_WAKEUP_ENABLE : R/W ;bitpos:[10] ;default: 0 ; */
/*description: RTC GPIO wakeup enable bit*/
#define RTC_GPIO_PIN11_WAKEUP_ENABLE  (BIT(10))
#define RTC_GPIO_PIN11_WAKEUP_ENABLE_M  (BIT(10))
#define RTC_GPIO_PIN11_WAKEUP_ENABLE_V  0x1
#define RTC_GPIO_PIN11_WAKEUP_ENABLE_S  10
/* RTC_GPIO_PIN11_INT_TYPE : R/W ;bitpos:[9:7] ;default: 0 ; */
/*description: if set to 0: GPIO interrupt disable   if set to 1: rising edge
 trigger   if set to 2: falling edge trigger  if set to 3: any edge trigger  if set to 4: low level trigger   if set to 5: high level trigger*/
#define RTC_GPIO_PIN11_INT_TYPE  0x00000007
#define RTC_GPIO_PIN11_INT_TYPE_M  ((RTC_GPIO_PIN11_INT_TYPE_V)<<(RTC_GPIO_PIN11_INT_TYPE_S))
#define RTC_GPIO_PIN11_INT_TYPE_V  0x7
#define RTC_GPIO_PIN11_INT_TYPE_S  7
/* RTC_GPIO_PIN11_PAD_DRIVER : R/W ;bitpos:[2] ;default: 0 ; */
/*description: if set to 0: normal output  if set to 1: open drain*/
#define RTC_GPIO_PIN11_PAD_DRIVER  (BIT(2))
#define RTC_GPIO_PIN11_PAD_DRIVER_M  (BIT(2))
#define RTC_GPIO_PIN11_PAD_DRIVER_V  0x1
#define RTC_GPIO_PIN11_PAD_DRIVER_S  2

#define RTC_GPIO_PIN12_REG          (DR_REG_RTCIO_BASE + 0x58)
/* RTC_GPIO_PIN12_WAKEUP_ENABLE : R/W ;bitpos:[10] ;default: 0 ; */
/*description: RTC GPIO wakeup enable bit*/
#define RTC_GPIO_PIN12_WAKEUP_ENABLE  (BIT(10))
#define RTC_GPIO_PIN12_WAKEUP_ENABLE_M  (BIT(10))
#define RTC_GPIO_PIN12_WAKEUP_ENABLE_V  0x1
#define RTC_GPIO_PIN12_WAKEUP_ENABLE_S  10
/* RTC_GPIO_PIN12_INT_TYPE : R/W ;bitpos:[9:7] ;default: 0 ; */
/*description: if set to 0: GPIO interrupt disable   if set to 1: rising edge
 trigger   if set to 2: falling edge trigger  if set to 3: any edge trigger  if set to 4: low level trigger   if set to 5: high level trigger*/
#define RTC_GPIO_PIN12_INT_TYPE  0x00000007
#define RTC_GPIO_PIN12_INT_TYPE_M  ((RTC_GPIO_PIN12_INT_TYPE_V)<<(RTC_GPIO_PIN12_INT_TYPE_S))
#define RTC_GPIO_PIN12_INT_TYPE_V  0x7
#define RTC_GPIO_PIN12_INT_TYPE_S  7
/* RTC_GPIO_PIN12_PAD_DRIVER : R/W ;bitpos:[2] ;default: 0 ; */
/*description: if set to 0: normal output  if set to 1: open drain*/
#define RTC_GPIO_PIN12_PAD_DRIVER  (BIT(2))
#define RTC_GPIO_PIN12_PAD_DRIVER_M  (BIT(2))
#define RTC_GPIO_PIN12_PAD_DRIVER_V  0x1
#define RTC_GPIO_PIN12_PAD_DRIVER_S  2

#define RTC_GPIO_PIN13_REG          (DR_REG_RTCIO_BASE + 0x5c)
/* RTC_GPIO_PIN13_WAKEUP_ENABLE : R/W ;bitpos:[10] ;default: 0 ; */
/*description: RTC GPIO wakeup enable bit*/
#define RTC_GPIO_PIN13_WAKEUP_ENABLE  (BIT(10))
#define RTC_GPIO_PIN13_WAKEUP_ENABLE_M  (BIT(10))
#define RTC_GPIO_PIN13_WAKEUP_ENABLE_V  0x1
#define RTC_GPIO_PIN13_WAKEUP_ENABLE_S  10
/* RTC_GPIO_PIN13_INT_TYPE : R/W ;bitpos:[9:7] ;default: 0 ; */
/*description: if set to 0: GPIO interrupt disable   if set to 1: rising edge
 trigger   if set to 2: falling edge trigger  if set to 3: any edge trigger  if set to 4: low level trigger   if set to 5: high level trigger*/
#define RTC_GPIO_PIN13_INT_TYPE  0x00000007
#define RTC_GPIO_PIN13_INT_TYPE_M  ((RTC_GPIO_PIN13_INT_TYPE_V)<<(RTC_GPIO_PIN13_INT_TYPE_S))
#define RTC_GPIO_PIN13_INT_TYPE_V  0x7
#define RTC_GPIO_PIN13_INT_TYPE_S  7
/* RTC_GPIO_PIN13_PAD_DRIVER : R/W ;bitpos:[2] ;default: 0 ; */
/*description: if set to 0: normal output  if set to 1: open drain*/
#define RTC_GPIO_PIN13_PAD_DRIVER  (BIT(2))
#define RTC_GPIO_PIN13_PAD_DRIVER_M  (BIT(2))
#define RTC_GPIO_PIN13_PAD_DRIVER_V  0x1
#define RTC_GPIO_PIN13_PAD_DRIVER_S  2

#define RTC_GPIO_PIN14_REG          (DR_REG_RTCIO_BASE + 0x60)
/* RTC_GPIO_PIN14_WAKEUP_ENABLE : R/W ;bitpos:[10] ;default: 0 ; */
/*description: RTC GPIO wakeup enable bit*/
#define RTC_GPIO_PIN14_WAKEUP_ENABLE  (BIT(10))
#define RTC_GPIO_PIN14_WAKEUP_ENABLE_M  (BIT(10))
#define RTC_GPIO_PIN14_WAKEUP_ENABLE_V  0x1
#define RTC_GPIO_PIN14_WAKEUP_ENABLE_S  10
/* RTC_GPIO_PIN14_INT_TYPE : R/W ;bitpos:[9:7] ;default: 0 ; */
/*description: if set to 0: GPIO interrupt disable   if set to 1: rising edge
 trigger   if set to 2: falling edge trigger  if set to 3: any edge trigger  if set to 4: low level trigger   if set to 5: high level trigger*/
#define RTC_GPIO_PIN14_INT_TYPE  0x00000007
#define RTC_GPIO_PIN14_INT_TYPE_M  ((RTC_GPIO_PIN14_INT_TYPE_V)<<(RTC_GPIO_PIN14_INT_TYPE_S))
#define RTC_GPIO_PIN14_INT_TYPE_V  0x7
#define RTC_GPIO_PIN14_INT_TYPE_S  7
/* RTC_GPIO_PIN14_PAD_DRIVER : R/W ;bitpos:[2] ;default: 0 ; */
/*description: if set to 0: normal output  if set to 1: open drain*/
#define RTC_GPIO_PIN14_PAD_DRIVER  (BIT(2))
#define RTC_GPIO_PIN14_PAD_DRIVER_M  (BIT(2))
#define RTC_GPIO_PIN14_PAD_DRIVER_V  0x1
#define RTC_GPIO_PIN14_PAD_DRIVER_S  2

#define RTC_GPIO_PIN15_REG          (DR_REG_RTCIO_BASE + 0x64)
/* RTC_GPIO_PIN15_WAKEUP_ENABLE : R/W ;bitpos:[10] ;default: 0 ; */
/*description: RTC GPIO wakeup enable bit*/
#define RTC_GPIO_PIN15_WAKEUP_ENABLE  (BIT(10))
#define RTC_GPIO_PIN15_WAKEUP_ENABLE_M  (BIT(10))
#define RTC_GPIO_PIN15_WAKEUP_ENABLE_V  0x1
#define RTC_GPIO_PIN15_WAKEUP_ENABLE_S  10
/* RTC_GPIO_PIN15_INT_TYPE : R/W ;bitpos:[9:7] ;default: 0 ; */
/*description: if set to 0: GPIO interrupt disable   if set to 1: rising edge
 trigger   if set to 2: falling edge trigger  if set to 3: any edge trigger  if set to 4: low level trigger   if set to 5: high level trigger*/
#define RTC_GPIO_PIN15_INT_TYPE  0x00000007
#define RTC_GPIO_PIN15_INT_TYPE_M  ((RTC_GPIO_PIN15_INT_TYPE_V)<<(RTC_GPIO_PIN15_INT_TYPE_S))
#define RTC_GPIO_PIN15_INT_TYPE_V  0x7
#define RTC_GPIO_PIN15_INT_TYPE_S  7
/* RTC_GPIO_PIN15_PAD_DRIVER : R/W ;bitpos:[2] ;default: 0 ; */
/*description: if set to 0: normal output  if set to 1: open drain*/
#define RTC_GPIO_PIN15_PAD_DRIVER  (BIT(2))
#define RTC_GPIO_PIN15_PAD_DRIVER_M  (BIT(2))
#define RTC_GPIO_PIN15_PAD_DRIVER_V  0x1
#define RTC_GPIO_PIN15_PAD_DRIVER_S  2

#define RTC_GPIO_PIN16_REG          (DR_REG_RTCIO_BASE + 0x68)
/* RTC_GPIO_PIN16_WAKEUP_ENABLE : R/W ;bitpos:[10] ;default: 0 ; */
/*description: RTC GPIO wakeup enable bit*/
#define RTC_GPIO_PIN16_WAKEUP_ENABLE  (BIT(10))
#define RTC_GPIO_PIN16_WAKEUP_ENABLE_M  (BIT(10))
#define RTC_GPIO_PIN16_WAKEUP_ENABLE_V  0x1
#define RTC_GPIO_PIN16_WAKEUP_ENABLE_S  10
/* RTC_GPIO_PIN16_INT_TYPE : R/W ;bitpos:[9:7] ;default: 0 ; */
/*description: if set to 0: GPIO interrupt disable   if set to 1: rising edge
 trigger   if set to 2: falling edge trigger  if set to 3: any edge trigger  if set to 4: low level trigger   if set to 5: high level trigger*/
#define RTC_GPIO_PIN16_INT_TYPE  0x00000007
#define RTC_GPIO_PIN16_INT_TYPE_M  ((RTC_GPIO_PIN16_INT_TYPE_V)<<(RTC_GPIO_PIN16_INT_TYPE_S))
#define RTC_GPIO_PIN16_INT_TYPE_V  0x7
#define RTC_GPIO_PIN16_INT_TYPE_S  7
/* RTC_GPIO_PIN16_PAD_DRIVER : R/W ;bitpos:[2] ;default: 0 ; */
/*description: if set to 0: normal output  if set to 1: open drain*/
#define RTC_GPIO_PIN16_PAD_DRIVER  (BIT(2))
#define RTC_GPIO_PIN16_PAD_DRIVER_M  (BIT(2))
#define RTC_GPIO_PIN16_PAD_DRIVER_V  0x1
#define RTC_GPIO_PIN16_PAD_DRIVER_S  2

#define RTC_GPIO_PIN17_REG          (DR_REG_RTCIO_BASE + 0x6c)
/* RTC_GPIO_PIN17_WAKEUP_ENABLE : R/W ;bitpos:[10] ;default: 0 ; */
/*description: RTC GPIO wakeup enable bit*/
#define RTC_GPIO_PIN17_WAKEUP_ENABLE  (BIT(10))
#define RTC_GPIO_PIN17_WAKEUP_ENABLE_M  (BIT(10))
#define RTC_GPIO_PIN17_WAKEUP_ENABLE_V  0x1
#define RTC_GPIO_PIN17_WAKEUP_ENABLE_S  10
/* RTC_GPIO_PIN17_INT_TYPE : R/W ;bitpos:[9:7] ;default: 0 ; */
/*description: if set to 0: GPIO interrupt disable   if set to 1: rising edge
 trigger   if set to 2: falling edge trigger  if set to 3: any edge trigger  if set to 4: low level trigger   if set to 5: high level trigger*/
#define RTC_GPIO_PIN17_INT_TYPE  0x00000007
#define RTC_GPIO_PIN17_INT_TYPE_M  ((RTC_GPIO_PIN17_INT_TYPE_V)<<(RTC_GPIO_PIN17_INT_TYPE_S))
#define RTC_GPIO_PIN17_INT_TYPE_V  0x7
#define RTC_GPIO_PIN17_INT_TYPE_S  7
/* RTC_GPIO_PIN17_PAD_DRIVER : R/W ;bitpos:[2] ;default: 0 ; */
/*description: if set to 0: normal output  if set to 1: open drain*/
#define RTC_GPIO_PIN17_PAD_DRIVER  (BIT(2))
#define RTC_GPIO_PIN17_PAD_DRIVER_M  (BIT(2))
#define RTC_GPIO_PIN17_PAD_DRIVER_V  0x1
#define RTC_GPIO_PIN17_PAD_DRIVER_S  2

#define RTC_IO_RTC_DEBUG_SEL_REG          (DR_REG_RTCIO_BASE + 0x70)
/* RTC_IO_DEBUG_12M_NO_GATING : R/W ;bitpos:[25] ;default: 1'd0 ; */
/*description: */
#define RTC_IO_DEBUG_12M_NO_GATING  (BIT(25))
#define RTC_IO_DEBUG_12M_NO_GATING_M  (BIT(25))
#define RTC_IO_DEBUG_12M_NO_GATING_V  0x1
#define RTC_IO_DEBUG_12M_NO_GATING_S  25
/* RTC_IO_DEBUG_SEL4 : R/W ;bitpos:[24:20] ;default: 5'd0 ; */
/*description: */
#define RTC_IO_DEBUG_SEL4  0x0000001F
#define RTC_IO_DEBUG_SEL4_M  ((RTC_IO_DEBUG_SEL4_V)<<(RTC_IO_DEBUG_SEL4_S))
#define RTC_IO_DEBUG_SEL4_V  0x1F
#define RTC_IO_DEBUG_SEL4_S  20
/* RTC_IO_DEBUG_SEL3 : R/W ;bitpos:[19:15] ;default: 5'd0 ; */
/*description: */
#define RTC_IO_DEBUG_SEL3  0x0000001F
#define RTC_IO_DEBUG_SEL3_M  ((RTC_IO_DEBUG_SEL3_V)<<(RTC_IO_DEBUG_SEL3_S))
#define RTC_IO_DEBUG_SEL3_V  0x1F
#define RTC_IO_DEBUG_SEL3_S  15
/* RTC_IO_DEBUG_SEL2 : R/W ;bitpos:[14:10] ;default: 5'd0 ; */
/*description: */
#define RTC_IO_DEBUG_SEL2  0x0000001F
#define RTC_IO_DEBUG_SEL2_M  ((RTC_IO_DEBUG_SEL2_V)<<(RTC_IO_DEBUG_SEL2_S))
#define RTC_IO_DEBUG_SEL2_V  0x1F
#define RTC_IO_DEBUG_SEL2_S  10
/* RTC_IO_DEBUG_SEL1 : R/W ;bitpos:[9:5] ;default: 5'd0 ; */
/*description: */
#define RTC_IO_DEBUG_SEL1  0x0000001F
#define RTC_IO_DEBUG_SEL1_M  ((RTC_IO_DEBUG_SEL1_V)<<(RTC_IO_DEBUG_SEL1_S))
#define RTC_IO_DEBUG_SEL1_V  0x1F
#define RTC_IO_DEBUG_SEL1_S  5
/* RTC_IO_DEBUG_SEL0 : R/W ;bitpos:[4:0] ;default: 5'd0 ; */
/*description: */
#define RTC_IO_DEBUG_SEL0  0x0000001F
#define RTC_IO_DEBUG_SEL0_M  ((RTC_IO_DEBUG_SEL0_V)<<(RTC_IO_DEBUG_SEL0_S))
#define RTC_IO_DEBUG_SEL0_V  0x1F
#define RTC_IO_DEBUG_SEL0_S  0
#define RTC_IO_DEBUG_SEL0_8M       1
#define RTC_IO_DEBUG_SEL0_32K_XTAL 4
#define RTC_IO_DEBUG_SEL0_150K_OSC 5

#define RTC_IO_DIG_PAD_HOLD_REG          (DR_REG_RTCIO_BASE + 0x74)
/* RTC_IO_DIG_PAD_HOLD : R/W ;bitpos:[31:0] ;default: 0 ; */
/*description: Digital pad hold. Bit0 – U0RXD  bit1 – U0TXD  bit2 – SD_CLK
  bit3 – SD_DATA0  bit4 – SD_DATA1  bit5 – SD_DATA2  bit6 – SD_SATA3  bit7 – SD_CMD  bit8 – GPIO5  bit9 – GPIO16  bit10 – GPIO17  bit11 – GPIO18  bit12 – GPIO19  bit13 – GPIO20  bit14 – GPIO21  bit15 – GPIO22  bit16 – GPIO23.*/
#define RTC_IO_DIG_PAD_HOLD  0xFFFFFFFF
#define RTC_IO_DIG_PAD_HOLD_M  ((RTC_IO_DIG_PAD_HOLD_V)<<(RTC_IO_DIG_PAD_HOLD_S))
#define RTC_IO_DIG_PAD_HOLD_V  0xFFFFFFFF
#define RTC_IO_DIG_PAD_HOLD_S  0

#define RTC_IO_HALL_SENS_REG          (DR_REG_RTCIO_BASE + 0x78)
/* RTC_IO_XPD_HALL : R/W ;bitpos:[31] ;default: 1'd0 ; */
/*description: Power on hall sensor and connect to VP and VN*/
#define RTC_IO_XPD_HALL  (BIT(31))
#define RTC_IO_XPD_HALL_M  (BIT(31))
#define RTC_IO_XPD_HALL_V  0x1
#define RTC_IO_XPD_HALL_S  31
/* RTC_IO_HALL_PHASE : R/W ;bitpos:[30] ;default: 1'd0 ; */
/*description: Reverse phase of hall sensor*/
#define RTC_IO_HALL_PHASE  (BIT(30))
#define RTC_IO_HALL_PHASE_M  (BIT(30))
#define RTC_IO_HALL_PHASE_V  0x1
#define RTC_IO_HALL_PHASE_S  30

#define RTC_IO_SENSOR_PADS_REG          (DR_REG_RTCIO_BASE + 0x7c)
/* RTC_IO_SENSE1_HOLD : R/W ;bitpos:[31] ;default: 1'd0 ; */
/*description: SENSE1 hold*/
#define RTC_IO_SENSE1_HOLD  (BIT(31))
#define RTC_IO_SENSE1_HOLD_M  (BIT(31))
#define RTC_IO_SENSE1_HOLD_V  0x1
#define RTC_IO_SENSE1_HOLD_S  31
/* RTC_IO_SENSE2_HOLD : R/W ;bitpos:[30] ;default: 1'd0 ; */
/*description: SENSE2 hold*/
#define RTC_IO_SENSE2_HOLD  (BIT(30))
#define RTC_IO_SENSE2_HOLD_M  (BIT(30))
#define RTC_IO_SENSE2_HOLD_V  0x1
#define RTC_IO_SENSE2_HOLD_S  30
/* RTC_IO_SENSE3_HOLD : R/W ;bitpos:[29] ;default: 1'd0 ; */
/*description: SENSE3 hold*/
#define RTC_IO_SENSE3_HOLD  (BIT(29))
#define RTC_IO_SENSE3_HOLD_M  (BIT(29))
#define RTC_IO_SENSE3_HOLD_V  0x1
#define RTC_IO_SENSE3_HOLD_S  29
/* RTC_IO_SENSE4_HOLD : R/W ;bitpos:[28] ;default: 1'd0 ; */
/*description: SENSE4 hold*/
#define RTC_IO_SENSE4_HOLD  (BIT(28))
#define RTC_IO_SENSE4_HOLD_M  (BIT(28))
#define RTC_IO_SENSE4_HOLD_V  0x1
#define RTC_IO_SENSE4_HOLD_S  28
/* RTC_IO_SENSE1_MUX_SEL : R/W ;bitpos:[27] ;default: 1'd0 ; */
/*description: 1: use RTC GPIO 0: use digital GPIO*/
#define RTC_IO_SENSE1_MUX_SEL  (BIT(27))
#define RTC_IO_SENSE1_MUX_SEL_M  (BIT(27))
#define RTC_IO_SENSE1_MUX_SEL_V  0x1
#define RTC_IO_SENSE1_MUX_SEL_S  27
/* RTC_IO_SENSE2_MUX_SEL : R/W ;bitpos:[26] ;default: 1'd0 ; */
/*description: 1: use RTC GPIO 0: use digital GPIO*/
#define RTC_IO_SENSE2_MUX_SEL  (BIT(26))
#define RTC_IO_SENSE2_MUX_SEL_M  (BIT(26))
#define RTC_IO_SENSE2_MUX_SEL_V  0x1
#define RTC_IO_SENSE2_MUX_SEL_S  26
/* RTC_IO_SENSE3_MUX_SEL : R/W ;bitpos:[25] ;default: 1'd0 ; */
/*description: 1: use RTC GPIO 0: use digital GPIO*/
#define RTC_IO_SENSE3_MUX_SEL  (BIT(25))
#define RTC_IO_SENSE3_MUX_SEL_M  (BIT(25))
#define RTC_IO_SENSE3_MUX_SEL_V  0x1
#define RTC_IO_SENSE3_MUX_SEL_S  25
/* RTC_IO_SENSE4_MUX_SEL : R/W ;bitpos:[24] ;default: 1'd0 ; */
/*description: 1: use RTC GPIO 0: use digital GPIO*/
#define RTC_IO_SENSE4_MUX_SEL  (BIT(24))
#define RTC_IO_SENSE4_MUX_SEL_M  (BIT(24))
#define RTC_IO_SENSE4_MUX_SEL_V  0x1
#define RTC_IO_SENSE4_MUX_SEL_S  24
/* RTC_IO_SENSE1_FUN_SEL : R/W ;bitpos:[23:22] ;default: 2'd0 ; */
/*description: SENSE1 function sel*/
#define RTC_IO_SENSE1_FUN_SEL  0x00000003
#define RTC_IO_SENSE1_FUN_SEL_M  ((RTC_IO_SENSE1_FUN_SEL_V)<<(RTC_IO_SENSE1_FUN_SEL_S))
#define RTC_IO_SENSE1_FUN_SEL_V  0x3
#define RTC_IO_SENSE1_FUN_SEL_S  22
/* RTC_IO_SENSE1_SLP_SEL : R/W ;bitpos:[21] ;default: 1'd0 ; */
/*description: 1: enable sleep mode during sleep 0: no sleep mode*/
#define RTC_IO_SENSE1_SLP_SEL  (BIT(21))
#define RTC_IO_SENSE1_SLP_SEL_M  (BIT(21))
#define RTC_IO_SENSE1_SLP_SEL_V  0x1
#define RTC_IO_SENSE1_SLP_SEL_S  21
/* RTC_IO_SENSE1_SLP_IE : R/W ;bitpos:[20] ;default: 1'd0 ; */
/*description: input enable in sleep mode*/
#define RTC_IO_SENSE1_SLP_IE  (BIT(20))
#define RTC_IO_SENSE1_SLP_IE_M  (BIT(20))
#define RTC_IO_SENSE1_SLP_IE_V  0x1
#define RTC_IO_SENSE1_SLP_IE_S  20
/* RTC_IO_SENSE1_FUN_IE : R/W ;bitpos:[19] ;default: 1'd0 ; */
/*description: input enable in work mode*/
#define RTC_IO_SENSE1_FUN_IE  (BIT(19))
#define RTC_IO_SENSE1_FUN_IE_M  (BIT(19))
#define RTC_IO_SENSE1_FUN_IE_V  0x1
#define RTC_IO_SENSE1_FUN_IE_S  19
/* RTC_IO_SENSE2_FUN_SEL : R/W ;bitpos:[18:17] ;default: 2'd0 ; */
/*description: SENSE2 function sel*/
#define RTC_IO_SENSE2_FUN_SEL  0x00000003
#define RTC_IO_SENSE2_FUN_SEL_M  ((RTC_IO_SENSE2_FUN_SEL_V)<<(RTC_IO_SENSE2_FUN_SEL_S))
#define RTC_IO_SENSE2_FUN_SEL_V  0x3
#define RTC_IO_SENSE2_FUN_SEL_S  17
/* RTC_IO_SENSE2_SLP_SEL : R/W ;bitpos:[16] ;default: 1'd0 ; */
/*description: 1: enable sleep mode during sleep 0: no sleep mode*/
#define RTC_IO_SENSE2_SLP_SEL  (BIT(16))
#define RTC_IO_SENSE2_SLP_SEL_M  (BIT(16))
#define RTC_IO_SENSE2_SLP_SEL_V  0x1
#define RTC_IO_SENSE2_SLP_SEL_S  16
/* RTC_IO_SENSE2_SLP_IE : R/W ;bitpos:[15] ;default: 1'd0 ; */
/*description: input enable in sleep mode*/
#define RTC_IO_SENSE2_SLP_IE  (BIT(15))
#define RTC_IO_SENSE2_SLP_IE_M  (BIT(15))
#define RTC_IO_SENSE2_SLP_IE_V  0x1
#define RTC_IO_SENSE2_SLP_IE_S  15
/* RTC_IO_SENSE2_FUN_IE : R/W ;bitpos:[14] ;default: 1'd0 ; */
/*description: input enable in work mode*/
#define RTC_IO_SENSE2_FUN_IE  (BIT(14))
#define RTC_IO_SENSE2_FUN_IE_M  (BIT(14))
#define RTC_IO_SENSE2_FUN_IE_V  0x1
#define RTC_IO_SENSE2_FUN_IE_S  14
/* RTC_IO_SENSE3_FUN_SEL : R/W ;bitpos:[13:12] ;default: 2'd0 ; */
/*description: SENSE3 function sel*/
#define RTC_IO_SENSE3_FUN_SEL  0x00000003
#define RTC_IO_SENSE3_FUN_SEL_M  ((RTC_IO_SENSE3_FUN_SEL_V)<<(RTC_IO_SENSE3_FUN_SEL_S))
#define RTC_IO_SENSE3_FUN_SEL_V  0x3
#define RTC_IO_SENSE3_FUN_SEL_S  12
/* RTC_IO_SENSE3_SLP_SEL : R/W ;bitpos:[11] ;default: 1'd0 ; */
/*description: 1: enable sleep mode during sleep 0: no sleep mode*/
#define RTC_IO_SENSE3_SLP_SEL  (BIT(11))
#define RTC_IO_SENSE3_SLP_SEL_M  (BIT(11))
#define RTC_IO_SENSE3_SLP_SEL_V  0x1
#define RTC_IO_SENSE3_SLP_SEL_S  11
/* RTC_IO_SENSE3_SLP_IE : R/W ;bitpos:[10] ;default: 1'd0 ; */
/*description: input enable in sleep mode*/
#define RTC_IO_SENSE3_SLP_IE  (BIT(10))
#define RTC_IO_SENSE3_SLP_IE_M  (BIT(10))
#define RTC_IO_SENSE3_SLP_IE_V  0x1
#define RTC_IO_SENSE3_SLP_IE_S  10
/* RTC_IO_SENSE3_FUN_IE : R/W ;bitpos:[9] ;default: 1'd0 ; */
/*description: input enable in work mode*/
#define RTC_IO_SENSE3_FUN_IE  (BIT(9))
#define RTC_IO_SENSE3_FUN_IE_M  (BIT(9))
#define RTC_IO_SENSE3_FUN_IE_V  0x1
#define RTC_IO_SENSE3_FUN_IE_S  9
/* RTC_IO_SENSE4_FUN_SEL : R/W ;bitpos:[8:7] ;default: 2'd0 ; */
/*description: SENSE4 function sel*/
#define RTC_IO_SENSE4_FUN_SEL  0x00000003
#define RTC_IO_SENSE4_FUN_SEL_M  ((RTC_IO_SENSE4_FUN_SEL_V)<<(RTC_IO_SENSE4_FUN_SEL_S))
#define RTC_IO_SENSE4_FUN_SEL_V  0x3
#define RTC_IO_SENSE4_FUN_SEL_S  7
/* RTC_IO_SENSE4_SLP_SEL : R/W ;bitpos:[6] ;default: 1'd0 ; */
/*description: 1: enable sleep mode during sleep 0: no sleep mode*/
#define RTC_IO_SENSE4_SLP_SEL  (BIT(6))
#define RTC_IO_SENSE4_SLP_SEL_M  (BIT(6))
#define RTC_IO_SENSE4_SLP_SEL_V  0x1
#define RTC_IO_SENSE4_SLP_SEL_S  6
/* RTC_IO_SENSE4_SLP_IE : R/W ;bitpos:[5] ;default: 1'd0 ; */
/*description: input enable in sleep mode*/
#define RTC_IO_SENSE4_SLP_IE  (BIT(5))
#define RTC_IO_SENSE4_SLP_IE_M  (BIT(5))
#define RTC_IO_SENSE4_SLP_IE_V  0x1
#define RTC_IO_SENSE4_SLP_IE_S  5
/* RTC_IO_SENSE4_FUN_IE : R/W ;bitpos:[4] ;default: 1'd0 ; */
/*description: input enable in work mode*/
#define RTC_IO_SENSE4_FUN_IE  (BIT(4))
#define RTC_IO_SENSE4_FUN_IE_M  (BIT(4))
#define RTC_IO_SENSE4_FUN_IE_V  0x1
#define RTC_IO_SENSE4_FUN_IE_S  4

#define RTC_IO_ADC_PAD_REG          (DR_REG_RTCIO_BASE + 0x80)
/* RTC_IO_ADC1_DRV : R/W ;bitpos:[31:30] ;default: 2'd2 ; */
/*description: ADC1_DRV*/
#define RTC_IO_ADC1_DRV  0x00000003
#define RTC_IO_ADC1_DRV_M  ((RTC_IO_ADC1_DRV_V)<<(RTC_IO_ADC1_DRV_S))
#define RTC_IO_ADC1_DRV_V  0x3
#define RTC_IO_ADC1_DRV_S  30
/* RTC_IO_ADC1_HOLD : R/W ;bitpos:[29] ;default: 1'd0 ; */
/*description: ADC1 hold*/
#define RTC_IO_ADC1_HOLD  (BIT(29))
#define RTC_IO_ADC1_HOLD_M  (BIT(29))
#define RTC_IO_ADC1_HOLD_V  0x1
#define RTC_IO_ADC1_HOLD_S  29
/* RTC_IO_ADC1_RDE : R/W ;bitpos:[28] ;default: 1'd0 ; */
/*description: ADC1_RDE*/
#define RTC_IO_ADC1_RDE  (BIT(28))
#define RTC_IO_ADC1_RDE_M  (BIT(28))
#define RTC_IO_ADC1_RDE_V  0x1
#define RTC_IO_ADC1_RDE_S  28
/* RTC_IO_ADC1_RUE : R/W ;bitpos:[27] ;default: 1'd0 ; */
/*description: ADC1_RUE*/
#define RTC_IO_ADC1_RUE  (BIT(27))
#define RTC_IO_ADC1_RUE_M  (BIT(27))
#define RTC_IO_ADC1_RUE_V  0x1
#define RTC_IO_ADC1_RUE_S  27
/* RTC_IO_ADC1_MUX_SEL : R/W ;bitpos:[26] ;default: 1'd0 ; */
/*description: 1: use RTC GPIO 0: use digital GPIO*/
#define RTC_IO_ADC1_MUX_SEL  (BIT(26))
#define RTC_IO_ADC1_MUX_SEL_M  (BIT(26))
#define RTC_IO_ADC1_MUX_SEL_V  0x1
#define RTC_IO_ADC1_MUX_SEL_S  26
/* RTC_IO_ADC1_FUN_SEL : R/W ;bitpos:[25:24] ;default: 2'd0 ; */
/*description: ADC1 function sel*/
#define RTC_IO_ADC1_FUN_SEL  0x00000003
#define RTC_IO_ADC1_FUN_SEL_M  ((RTC_IO_ADC1_FUN_SEL_V)<<(RTC_IO_ADC1_FUN_SEL_S))
#define RTC_IO_ADC1_FUN_SEL_V  0x3
#define RTC_IO_ADC1_FUN_SEL_S  24
/* RTC_IO_ADC1_SLP_SEL : R/W ;bitpos:[23] ;default: 1'd0 ; */
/*description: 1: enable sleep mode during sleep 0: no sleep mode*/
#define RTC_IO_ADC1_SLP_SEL  (BIT(23))
#define RTC_IO_ADC1_SLP_SEL_M  (BIT(23))
#define RTC_IO_ADC1_SLP_SEL_V  0x1
#define RTC_IO_ADC1_SLP_SEL_S  23
/* RTC_IO_ADC1_SLP_IE : R/W ;bitpos:[22] ;default: 1'd0 ; */
/*description: input enable in sleep mode*/
#define RTC_IO_ADC1_SLP_IE  (BIT(22))
#define RTC_IO_ADC1_SLP_IE_M  (BIT(22))
#define RTC_IO_ADC1_SLP_IE_V  0x1
#define RTC_IO_ADC1_SLP_IE_S  22
/* RTC_IO_ADC1_FUN_IE : R/W ;bitpos:[21] ;default: 1'd0 ; */
/*description: input enable in work mode*/
#define RTC_IO_ADC1_FUN_IE  (BIT(21))
#define RTC_IO_ADC1_FUN_IE_M  (BIT(21))
#define RTC_IO_ADC1_FUN_IE_V  0x1
#define RTC_IO_ADC1_FUN_IE_S  21
/* RTC_IO_ADC2_DRV : R/W ;bitpos:[20:19] ;default: 2'd2 ; */
/*description: ADC2_DRV*/
#define RTC_IO_ADC2_DRV  0x00000003
#define RTC_IO_ADC2_DRV_M  ((RTC_IO_ADC2_DRV_V)<<(RTC_IO_ADC2_DRV_S))
#define RTC_IO_ADC2_DRV_V  0x3
#define RTC_IO_ADC2_DRV_S  19
/* RTC_IO_ADC2_HOLD : R/W ;bitpos:[18] ;default: 1'd0 ; */
/*description: ADC2 hold*/
#define RTC_IO_ADC2_HOLD  (BIT(18))
#define RTC_IO_ADC2_HOLD_M  (BIT(18))
#define RTC_IO_ADC2_HOLD_V  0x1
#define RTC_IO_ADC2_HOLD_S  18
/* RTC_IO_ADC2_RDE : R/W ;bitpos:[17] ;default: 1'd0 ; */
/*description: ADC2_RDE*/
#define RTC_IO_ADC2_RDE  (BIT(17))
#define RTC_IO_ADC2_RDE_M  (BIT(17))
#define RTC_IO_ADC2_RDE_V  0x1
#define RTC_IO_ADC2_RDE_S  17
/* RTC_IO_ADC2_RUE : R/W ;bitpos:[16] ;default: 1'd0 ; */
/*description: ADC2_RUE*/
#define RTC_IO_ADC2_RUE  (BIT(16))
#define RTC_IO_ADC2_RUE_M  (BIT(16))
#define RTC_IO_ADC2_RUE_V  0x1
#define RTC_IO_ADC2_RUE_S  16
/* RTC_IO_ADC2_MUX_SEL : R/W ;bitpos:[15] ;default: 1'd0 ; */
/*description: 1: use RTC GPIO 0: use digital GPIO*/
#define RTC_IO_ADC2_MUX_SEL  (BIT(15))
#define RTC_IO_ADC2_MUX_SEL_M  (BIT(15))
#define RTC_IO_ADC2_MUX_SEL_V  0x1
#define RTC_IO_ADC2_MUX_SEL_S  15
/* RTC_IO_ADC2_FUN_SEL : R/W ;bitpos:[14:13] ;default: 2'd0 ; */
/*description: ADC2 function sel*/
#define RTC_IO_ADC2_FUN_SEL  0x00000003
#define RTC_IO_ADC2_FUN_SEL_M  ((RTC_IO_ADC2_FUN_SEL_V)<<(RTC_IO_ADC2_FUN_SEL_S))
#define RTC_IO_ADC2_FUN_SEL_V  0x3
#define RTC_IO_ADC2_FUN_SEL_S  13
/* RTC_IO_ADC2_SLP_SEL : R/W ;bitpos:[12] ;default: 1'd0 ; */
/*description: 1: enable sleep mode during sleep 0: no sleep mode*/
#define RTC_IO_ADC2_SLP_SEL  (BIT(12))
#define RTC_IO_ADC2_SLP_SEL_M  (BIT(12))
#define RTC_IO_ADC2_SLP_SEL_V  0x1
#define RTC_IO_ADC2_SLP_SEL_S  12
/* RTC_IO_ADC2_SLP_IE : R/W ;bitpos:[11] ;default: 1'd0 ; */
/*description: input enable in sleep mode*/
#define RTC_IO_ADC2_SLP_IE  (BIT(11))
#define RTC_IO_ADC2_SLP_IE_M  (BIT(11))
#define RTC_IO_ADC2_SLP_IE_V  0x1
#define RTC_IO_ADC2_SLP_IE_S  11
/* RTC_IO_ADC2_FUN_IE : R/W ;bitpos:[10] ;default: 1'd0 ; */
/*description: input enable in work mode*/
#define RTC_IO_ADC2_FUN_IE  (BIT(10))
#define RTC_IO_ADC2_FUN_IE_M  (BIT(10))
#define RTC_IO_ADC2_FUN_IE_V  0x1
#define RTC_IO_ADC2_FUN_IE_S  10

#define RTC_IO_PAD_DAC1_REG          (DR_REG_RTCIO_BASE + 0x84)
/* RTC_IO_PDAC1_DRV : R/W ;bitpos:[31:30] ;default: 2'd2 ; */
/*description: PDAC1_DRV*/
#define RTC_IO_PDAC1_DRV  0x00000003
#define RTC_IO_PDAC1_DRV_M  ((RTC_IO_PDAC1_DRV_V)<<(RTC_IO_PDAC1_DRV_S))
#define RTC_IO_PDAC1_DRV_V  0x3
#define RTC_IO_PDAC1_DRV_S  30
/* RTC_IO_PDAC1_HOLD : R/W ;bitpos:[29] ;default: 1'd0 ; */
/*description: PDAC1 hold*/
#define RTC_IO_PDAC1_HOLD  (BIT(29))
#define RTC_IO_PDAC1_HOLD_M  (BIT(29))
#define RTC_IO_PDAC1_HOLD_V  0x1
#define RTC_IO_PDAC1_HOLD_S  29
/* RTC_IO_PDAC1_RDE : R/W ;bitpos:[28] ;default: 1'd0 ; */
/*description: PDAC1_RDE*/
#define RTC_IO_PDAC1_RDE  (BIT(28))
#define RTC_IO_PDAC1_RDE_M  (BIT(28))
#define RTC_IO_PDAC1_RDE_V  0x1
#define RTC_IO_PDAC1_RDE_S  28
/* RTC_IO_PDAC1_RUE : R/W ;bitpos:[27] ;default: 1'd0 ; */
/*description: PDAC1_RUE*/
#define RTC_IO_PDAC1_RUE  (BIT(27))
#define RTC_IO_PDAC1_RUE_M  (BIT(27))
#define RTC_IO_PDAC1_RUE_V  0x1
#define RTC_IO_PDAC1_RUE_S  27
/* RTC_IO_PDAC1_DAC : R/W ;bitpos:[26:19] ;default: 8'd0 ; */
/*description: PDAC1_DAC*/
#define RTC_IO_PDAC1_DAC  0x000000FF
#define RTC_IO_PDAC1_DAC_M  ((RTC_IO_PDAC1_DAC_V)<<(RTC_IO_PDAC1_DAC_S))
#define RTC_IO_PDAC1_DAC_V  0xFF
#define RTC_IO_PDAC1_DAC_S  19
/* RTC_IO_PDAC1_XPD_DAC : R/W ;bitpos:[18] ;default: 1'd0 ; */
/*description: PDAC1_XPD_DAC*/
#define RTC_IO_PDAC1_XPD_DAC  (BIT(18))
#define RTC_IO_PDAC1_XPD_DAC_M  (BIT(18))
#define RTC_IO_PDAC1_XPD_DAC_V  0x1
#define RTC_IO_PDAC1_XPD_DAC_S  18
/* RTC_IO_PDAC1_MUX_SEL : R/W ;bitpos:[17] ;default: 1'd0 ; */
/*description: 1: use RTC GPIO 0: use digital GPIO*/
#define RTC_IO_PDAC1_MUX_SEL  (BIT(17))
#define RTC_IO_PDAC1_MUX_SEL_M  (BIT(17))
#define RTC_IO_PDAC1_MUX_SEL_V  0x1
#define RTC_IO_PDAC1_MUX_SEL_S  17
/* RTC_IO_PDAC1_FUN_SEL : R/W ;bitpos:[16:15] ;default: 2'd0 ; */
/*description: PDAC1 function sel*/
#define RTC_IO_PDAC1_FUN_SEL  0x00000003
#define RTC_IO_PDAC1_FUN_SEL_M  ((RTC_IO_PDAC1_FUN_SEL_V)<<(RTC_IO_PDAC1_FUN_SEL_S))
#define RTC_IO_PDAC1_FUN_SEL_V  0x3
#define RTC_IO_PDAC1_FUN_SEL_S  15
/* RTC_IO_PDAC1_SLP_SEL : R/W ;bitpos:[14] ;default: 1'd0 ; */
/*description: 1: enable sleep mode during sleep 0: no sleep mode*/
#define RTC_IO_PDAC1_SLP_SEL  (BIT(14))
#define RTC_IO_PDAC1_SLP_SEL_M  (BIT(14))
#define RTC_IO_PDAC1_SLP_SEL_V  0x1
#define RTC_IO_PDAC1_SLP_SEL_S  14
/* RTC_IO_PDAC1_SLP_IE : R/W ;bitpos:[13] ;default: 1'd0 ; */
/*description: input enable in sleep mode*/
#define RTC_IO_PDAC1_SLP_IE  (BIT(13))
#define RTC_IO_PDAC1_SLP_IE_M  (BIT(13))
#define RTC_IO_PDAC1_SLP_IE_V  0x1
#define RTC_IO_PDAC1_SLP_IE_S  13
/* RTC_IO_PDAC1_SLP_OE : R/W ;bitpos:[12] ;default: 1'd0 ; */
/*description: output enable in sleep mode*/
#define RTC_IO_PDAC1_SLP_OE  (BIT(12))
#define RTC_IO_PDAC1_SLP_OE_M  (BIT(12))
#define RTC_IO_PDAC1_SLP_OE_V  0x1
#define RTC_IO_PDAC1_SLP_OE_S  12
/* RTC_IO_PDAC1_FUN_IE : R/W ;bitpos:[11] ;default: 1'd0 ; */
/*description: input enable in work mode*/
#define RTC_IO_PDAC1_FUN_IE  (BIT(11))
#define RTC_IO_PDAC1_FUN_IE_M  (BIT(11))
#define RTC_IO_PDAC1_FUN_IE_V  0x1
#define RTC_IO_PDAC1_FUN_IE_S  11
/* RTC_IO_PDAC1_DAC_XPD_FORCE : R/W ;bitpos:[10] ;default: 1'd0 ; */
/*description: 1: use reg_pdac1_xpd_dac to control PDAC1_XPD_DAC 0: use SAR
 ADC FSM to control PDAC1_XPD_DAC*/
#define RTC_IO_PDAC1_DAC_XPD_FORCE  (BIT(10))
#define RTC_IO_PDAC1_DAC_XPD_FORCE_M  (BIT(10))
#define RTC_IO_PDAC1_DAC_XPD_FORCE_V  0x1
#define RTC_IO_PDAC1_DAC_XPD_FORCE_S  10

#define RTC_IO_PAD_DAC2_REG          (DR_REG_RTCIO_BASE + 0x88)
/* RTC_IO_PDAC2_DRV : R/W ;bitpos:[31:30] ;default: 2'd2 ; */
/*description: PDAC2_DRV*/
#define RTC_IO_PDAC2_DRV  0x00000003
#define RTC_IO_PDAC2_DRV_M  ((RTC_IO_PDAC2_DRV_V)<<(RTC_IO_PDAC2_DRV_S))
#define RTC_IO_PDAC2_DRV_V  0x3
#define RTC_IO_PDAC2_DRV_S  30
/* RTC_IO_PDAC2_HOLD : R/W ;bitpos:[29] ;default: 1'd0 ; */
/*description: PDAC2 hold*/
#define RTC_IO_PDAC2_HOLD  (BIT(29))
#define RTC_IO_PDAC2_HOLD_M  (BIT(29))
#define RTC_IO_PDAC2_HOLD_V  0x1
#define RTC_IO_PDAC2_HOLD_S  29
/* RTC_IO_PDAC2_RDE : R/W ;bitpos:[28] ;default: 1'd0 ; */
/*description: PDAC2_RDE*/
#define RTC_IO_PDAC2_RDE  (BIT(28))
#define RTC_IO_PDAC2_RDE_M  (BIT(28))
#define RTC_IO_PDAC2_RDE_V  0x1
#define RTC_IO_PDAC2_RDE_S  28
/* RTC_IO_PDAC2_RUE : R/W ;bitpos:[27] ;default: 1'd0 ; */
/*description: PDAC2_RUE*/
#define RTC_IO_PDAC2_RUE  (BIT(27))
#define RTC_IO_PDAC2_RUE_M  (BIT(27))
#define RTC_IO_PDAC2_RUE_V  0x1
#define RTC_IO_PDAC2_RUE_S  27
/* RTC_IO_PDAC2_DAC : R/W ;bitpos:[26:19] ;default: 8'd0 ; */
/*description: PDAC2_DAC*/
#define RTC_IO_PDAC2_DAC  0x000000FF
#define RTC_IO_PDAC2_DAC_M  ((RTC_IO_PDAC2_DAC_V)<<(RTC_IO_PDAC2_DAC_S))
#define RTC_IO_PDAC2_DAC_V  0xFF
#define RTC_IO_PDAC2_DAC_S  19
/* RTC_IO_PDAC2_XPD_DAC : R/W ;bitpos:[18] ;default: 1'd0 ; */
/*description: PDAC2_XPD_DAC*/
#define RTC_IO_PDAC2_XPD_DAC  (BIT(18))
#define RTC_IO_PDAC2_XPD_DAC_M  (BIT(18))
#define RTC_IO_PDAC2_XPD_DAC_V  0x1
#define RTC_IO_PDAC2_XPD_DAC_S  18
/* RTC_IO_PDAC2_MUX_SEL : R/W ;bitpos:[17] ;default: 1'd0 ; */
/*description: 1: use RTC GPIO 0: use digital GPIO*/
#define RTC_IO_PDAC2_MUX_SEL  (BIT(17))
#define RTC_IO_PDAC2_MUX_SEL_M  (BIT(17))
#define RTC_IO_PDAC2_MUX_SEL_V  0x1
#define RTC_IO_PDAC2_MUX_SEL_S  17
/* RTC_IO_PDAC2_FUN_SEL : R/W ;bitpos:[16:15] ;default: 2'd0 ; */
/*description: PDAC1 function sel*/
#define RTC_IO_PDAC2_FUN_SEL  0x00000003
#define RTC_IO_PDAC2_FUN_SEL_M  ((RTC_IO_PDAC2_FUN_SEL_V)<<(RTC_IO_PDAC2_FUN_SEL_S))
#define RTC_IO_PDAC2_FUN_SEL_V  0x3
#define RTC_IO_PDAC2_FUN_SEL_S  15
/* RTC_IO_PDAC2_SLP_SEL : R/W ;bitpos:[14] ;default: 1'd0 ; */
/*description: 1: enable sleep mode during sleep 0: no sleep mode*/
#define RTC_IO_PDAC2_SLP_SEL  (BIT(14))
#define RTC_IO_PDAC2_SLP_SEL_M  (BIT(14))
#define RTC_IO_PDAC2_SLP_SEL_V  0x1
#define RTC_IO_PDAC2_SLP_SEL_S  14
/* RTC_IO_PDAC2_SLP_IE : R/W ;bitpos:[13] ;default: 1'd0 ; */
/*description: input enable in sleep mode*/
#define RTC_IO_PDAC2_SLP_IE  (BIT(13))
#define RTC_IO_PDAC2_SLP_IE_M  (BIT(13))
#define RTC_IO_PDAC2_SLP_IE_V  0x1
#define RTC_IO_PDAC2_SLP_IE_S  13
/* RTC_IO_PDAC2_SLP_OE : R/W ;bitpos:[12] ;default: 1'd0 ; */
/*description: output enable in sleep mode*/
#define RTC_IO_PDAC2_SLP_OE  (BIT(12))
#define RTC_IO_PDAC2_SLP_OE_M  (BIT(12))
#define RTC_IO_PDAC2_SLP_OE_V  0x1
#define RTC_IO_PDAC2_SLP_OE_S  12
/* RTC_IO_PDAC2_FUN_IE : R/W ;bitpos:[11] ;default: 1'd0 ; */
/*description: input enable in work mode*/
#define RTC_IO_PDAC2_FUN_IE  (BIT(11))
#define RTC_IO_PDAC2_FUN_IE_M  (BIT(11))
#define RTC_IO_PDAC2_FUN_IE_V  0x1
#define RTC_IO_PDAC2_FUN_IE_S  11
/* RTC_IO_PDAC2_DAC_XPD_FORCE : R/W ;bitpos:[10] ;default: 1'd0 ; */
/*description: 1: use reg_pdac2_xpd_dac to control PDAC2_XPD_DAC 0: use SAR
 ADC FSM to control PDAC2_XPD_DAC*/
#define RTC_IO_PDAC2_DAC_XPD_FORCE  (BIT(10))
#define RTC_IO_PDAC2_DAC_XPD_FORCE_M  (BIT(10))
#define RTC_IO_PDAC2_DAC_XPD_FORCE_V  0x1
#define RTC_IO_PDAC2_DAC_XPD_FORCE_S  10

#define RTC_IO_XTAL_32K_PAD_REG          (DR_REG_RTCIO_BASE + 0x8c)
/* RTC_IO_X32N_DRV : R/W ;bitpos:[31:30] ;default: 2'd2 ; */
/*description: X32N_DRV*/
#define RTC_IO_X32N_DRV  0x00000003
#define RTC_IO_X32N_DRV_M  ((RTC_IO_X32N_DRV_V)<<(RTC_IO_X32N_DRV_S))
#define RTC_IO_X32N_DRV_V  0x3
#define RTC_IO_X32N_DRV_S  30
/* RTC_IO_X32N_HOLD : R/W ;bitpos:[29] ;default: 1'd0 ; */
/*description: X32N hold*/
#define RTC_IO_X32N_HOLD  (BIT(29))
#define RTC_IO_X32N_HOLD_M  (BIT(29))
#define RTC_IO_X32N_HOLD_V  0x1
#define RTC_IO_X32N_HOLD_S  29
/* RTC_IO_X32N_RDE : R/W ;bitpos:[28] ;default: 1'd0 ; */
/*description: X32N_RDE*/
#define RTC_IO_X32N_RDE  (BIT(28))
#define RTC_IO_X32N_RDE_M  (BIT(28))
#define RTC_IO_X32N_RDE_V  0x1
#define RTC_IO_X32N_RDE_S  28
/* RTC_IO_X32N_RUE : R/W ;bitpos:[27] ;default: 1'd0 ; */
/*description: X32N_RUE*/
#define RTC_IO_X32N_RUE  (BIT(27))
#define RTC_IO_X32N_RUE_M  (BIT(27))
#define RTC_IO_X32N_RUE_V  0x1
#define RTC_IO_X32N_RUE_S  27
/* RTC_IO_X32P_DRV : R/W ;bitpos:[26:25] ;default: 2'd2 ; */
/*description: X32P_DRV*/
#define RTC_IO_X32P_DRV  0x00000003
#define RTC_IO_X32P_DRV_M  ((RTC_IO_X32P_DRV_V)<<(RTC_IO_X32P_DRV_S))
#define RTC_IO_X32P_DRV_V  0x3
#define RTC_IO_X32P_DRV_S  25
/* RTC_IO_X32P_HOLD : R/W ;bitpos:[24] ;default: 1'd0 ; */
/*description: X32N hold*/
#define RTC_IO_X32P_HOLD  (BIT(24))
#define RTC_IO_X32P_HOLD_M  (BIT(24))
#define RTC_IO_X32P_HOLD_V  0x1
#define RTC_IO_X32P_HOLD_S  24
/* RTC_IO_X32P_RDE : R/W ;bitpos:[23] ;default: 1'd0 ; */
/*description: X32N RDE*/
#define RTC_IO_X32P_RDE  (BIT(23))
#define RTC_IO_X32P_RDE_M  (BIT(23))
#define RTC_IO_X32P_RDE_V  0x1
#define RTC_IO_X32P_RDE_S  23
/* RTC_IO_X32P_RUE : R/W ;bitpos:[22] ;default: 1'd0 ; */
/*description: X32N RUE*/
#define RTC_IO_X32P_RUE  (BIT(22))
#define RTC_IO_X32P_RUE_M  (BIT(22))
#define RTC_IO_X32P_RUE_V  0x1
#define RTC_IO_X32P_RUE_S  22
/* RTC_IO_DAC_XTAL_32K : R/W ;bitpos:[21:20] ;default: 2'b01 ; */
/*description: 32K XTAL bias current DAC.*/
#define RTC_IO_DAC_XTAL_32K  0x00000003
#define RTC_IO_DAC_XTAL_32K_M  ((RTC_IO_DAC_XTAL_32K_V)<<(RTC_IO_DAC_XTAL_32K_S))
#define RTC_IO_DAC_XTAL_32K_V  0x3
#define RTC_IO_DAC_XTAL_32K_S  20
/* RTC_IO_XPD_XTAL_32K : R/W ;bitpos:[19] ;default: 1'd0 ; */
/*description: Power up 32kHz crystal oscillator*/
#define RTC_IO_XPD_XTAL_32K  (BIT(19))
#define RTC_IO_XPD_XTAL_32K_M  (BIT(19))
#define RTC_IO_XPD_XTAL_32K_V  0x1
#define RTC_IO_XPD_XTAL_32K_S  19
/* RTC_IO_X32N_MUX_SEL : R/W ;bitpos:[18] ;default: 1'd0 ; */
/*description: 1: use RTC GPIO 0: use digital GPIO*/
#define RTC_IO_X32N_MUX_SEL  (BIT(18))
#define RTC_IO_X32N_MUX_SEL_M  (BIT(18))
#define RTC_IO_X32N_MUX_SEL_V  0x1
#define RTC_IO_X32N_MUX_SEL_S  18
/* RTC_IO_X32P_MUX_SEL : R/W ;bitpos:[17] ;default: 1'd0 ; */
/*description: 1: use RTC GPIO 0: use digital GPIO*/
#define RTC_IO_X32P_MUX_SEL  (BIT(17))
#define RTC_IO_X32P_MUX_SEL_M  (BIT(17))
#define RTC_IO_X32P_MUX_SEL_V  0x1
#define RTC_IO_X32P_MUX_SEL_S  17
/* RTC_IO_X32N_FUN_SEL : R/W ;bitpos:[16:15] ;default: 2'd0 ; */
/*description: X32N function sel*/
#define RTC_IO_X32N_FUN_SEL  0x00000003
#define RTC_IO_X32N_FUN_SEL_M  ((RTC_IO_X32N_FUN_SEL_V)<<(RTC_IO_X32N_FUN_SEL_S))
#define RTC_IO_X32N_FUN_SEL_V  0x3
#define RTC_IO_X32N_FUN_SEL_S  15
/* RTC_IO_X32N_SLP_SEL : R/W ;bitpos:[14] ;default: 1'd0 ; */
/*description: 1: enable sleep mode during sleep 0: no sleep mode*/
#define RTC_IO_X32N_SLP_SEL  (BIT(14))
#define RTC_IO_X32N_SLP_SEL_M  (BIT(14))
#define RTC_IO_X32N_SLP_SEL_V  0x1
#define RTC_IO_X32N_SLP_SEL_S  14
/* RTC_IO_X32N_SLP_IE : R/W ;bitpos:[13] ;default: 1'd0 ; */
/*description: input enable in sleep mode*/
#define RTC_IO_X32N_SLP_IE  (BIT(13))
#define RTC_IO_X32N_SLP_IE_M  (BIT(13))
#define RTC_IO_X32N_SLP_IE_V  0x1
#define RTC_IO_X32N_SLP_IE_S  13
/* RTC_IO_X32N_SLP_OE : R/W ;bitpos:[12] ;default: 1'd0 ; */
/*description: output enable in sleep mode*/
#define RTC_IO_X32N_SLP_OE  (BIT(12))
#define RTC_IO_X32N_SLP_OE_M  (BIT(12))
#define RTC_IO_X32N_SLP_OE_V  0x1
#define RTC_IO_X32N_SLP_OE_S  12
/* RTC_IO_X32N_FUN_IE : R/W ;bitpos:[11] ;default: 1'd0 ; */
/*description: input enable in work mode*/
#define RTC_IO_X32N_FUN_IE  (BIT(11))
#define RTC_IO_X32N_FUN_IE_M  (BIT(11))
#define RTC_IO_X32N_FUN_IE_V  0x1
#define RTC_IO_X32N_FUN_IE_S  11
/* RTC_IO_X32P_FUN_SEL : R/W ;bitpos:[10:9] ;default: 2'd0 ; */
/*description: X32P function sel*/
#define RTC_IO_X32P_FUN_SEL  0x00000003
#define RTC_IO_X32P_FUN_SEL_M  ((RTC_IO_X32P_FUN_SEL_V)<<(RTC_IO_X32P_FUN_SEL_S))
#define RTC_IO_X32P_FUN_SEL_V  0x3
#define RTC_IO_X32P_FUN_SEL_S  9
/* RTC_IO_X32P_SLP_SEL : R/W ;bitpos:[8] ;default: 1'd0 ; */
/*description: 1: enable sleep mode during sleep 0: no sleep mode*/
#define RTC_IO_X32P_SLP_SEL  (BIT(8))
#define RTC_IO_X32P_SLP_SEL_M  (BIT(8))
#define RTC_IO_X32P_SLP_SEL_V  0x1
#define RTC_IO_X32P_SLP_SEL_S  8
/* RTC_IO_X32P_SLP_IE : R/W ;bitpos:[7] ;default: 1'd0 ; */
/*description: input enable in sleep mode*/
#define RTC_IO_X32P_SLP_IE  (BIT(7))
#define RTC_IO_X32P_SLP_IE_M  (BIT(7))
#define RTC_IO_X32P_SLP_IE_V  0x1
#define RTC_IO_X32P_SLP_IE_S  7
/* RTC_IO_X32P_SLP_OE : R/W ;bitpos:[6] ;default: 1'd0 ; */
/*description: output enable in sleep mode*/
#define RTC_IO_X32P_SLP_OE  (BIT(6))
#define RTC_IO_X32P_SLP_OE_M  (BIT(6))
#define RTC_IO_X32P_SLP_OE_V  0x1
#define RTC_IO_X32P_SLP_OE_S  6
/* RTC_IO_X32P_FUN_IE : R/W ;bitpos:[5] ;default: 1'd0 ; */
/*description: input enable in work mode*/
#define RTC_IO_X32P_FUN_IE  (BIT(5))
#define RTC_IO_X32P_FUN_IE_M  (BIT(5))
#define RTC_IO_X32P_FUN_IE_V  0x1
#define RTC_IO_X32P_FUN_IE_S  5
/* RTC_IO_DRES_XTAL_32K : R/W ;bitpos:[4:3] ;default: 2'b10 ; */
/*description: 32K XTAL resistor bias control.*/
#define RTC_IO_DRES_XTAL_32K  0x00000003
#define RTC_IO_DRES_XTAL_32K_M  ((RTC_IO_DRES_XTAL_32K_V)<<(RTC_IO_DRES_XTAL_32K_S))
#define RTC_IO_DRES_XTAL_32K_V  0x3
#define RTC_IO_DRES_XTAL_32K_S  3
/* RTC_IO_DBIAS_XTAL_32K : R/W ;bitpos:[2:1] ;default: 2'b00 ; */
/*description: 32K XTAL self-bias reference control.*/
#define RTC_IO_DBIAS_XTAL_32K  0x00000003
#define RTC_IO_DBIAS_XTAL_32K_M  ((RTC_IO_DBIAS_XTAL_32K_V)<<(RTC_IO_DBIAS_XTAL_32K_S))
#define RTC_IO_DBIAS_XTAL_32K_V  0x3
#define RTC_IO_DBIAS_XTAL_32K_S  1

#define RTC_IO_TOUCH_CFG_REG          (DR_REG_RTCIO_BASE + 0x90)
/* RTC_IO_TOUCH_XPD_BIAS : R/W ;bitpos:[31] ;default: 1'd0 ; */
/*description: TOUCH_XPD_BIAS*/
#define RTC_IO_TOUCH_XPD_BIAS  (BIT(31))
#define RTC_IO_TOUCH_XPD_BIAS_M  (BIT(31))
#define RTC_IO_TOUCH_XPD_BIAS_V  0x1
#define RTC_IO_TOUCH_XPD_BIAS_S  31
/* RTC_IO_TOUCH_DREFH : R/W ;bitpos:[30:29] ;default: 2'b11 ; */
/*description: TOUCH_DREFH*/
#define RTC_IO_TOUCH_DREFH  0x00000003
#define RTC_IO_TOUCH_DREFH_M  ((RTC_IO_TOUCH_DREFH_V)<<(RTC_IO_TOUCH_DREFH_S))
#define RTC_IO_TOUCH_DREFH_V  0x3
#define RTC_IO_TOUCH_DREFH_S  29
/* RTC_IO_TOUCH_DREFL : R/W ;bitpos:[28:27] ;default: 2'b00 ; */
/*description: TOUCH_DREFL*/
#define RTC_IO_TOUCH_DREFL  0x00000003
#define RTC_IO_TOUCH_DREFL_M  ((RTC_IO_TOUCH_DREFL_V)<<(RTC_IO_TOUCH_DREFL_S))
#define RTC_IO_TOUCH_DREFL_V  0x3
#define RTC_IO_TOUCH_DREFL_S  27
/* RTC_IO_TOUCH_DRANGE : R/W ;bitpos:[26:25] ;default: 2'b11 ; */
/*description: TOUCH_DRANGE*/
#define RTC_IO_TOUCH_DRANGE  0x00000003
#define RTC_IO_TOUCH_DRANGE_M  ((RTC_IO_TOUCH_DRANGE_V)<<(RTC_IO_TOUCH_DRANGE_S))
#define RTC_IO_TOUCH_DRANGE_V  0x3
#define RTC_IO_TOUCH_DRANGE_S  25
/* RTC_IO_TOUCH_DCUR : R/W ;bitpos:[24:23] ;default: 2'b00 ; */
/*description: TOUCH_DCUR*/
#define RTC_IO_TOUCH_DCUR  0x00000003
#define RTC_IO_TOUCH_DCUR_M  ((RTC_IO_TOUCH_DCUR_V)<<(RTC_IO_TOUCH_DCUR_S))
#define RTC_IO_TOUCH_DCUR_V  0x3
#define RTC_IO_TOUCH_DCUR_S  23

#define RTC_IO_TOUCH_PAD0_REG          (DR_REG_RTCIO_BASE + 0x94)
/* RTC_IO_TOUCH_PAD0_HOLD : R/W ;bitpos:[31] ;default: 1'd0 ; */
/*description: hold*/
#define RTC_IO_TOUCH_PAD0_HOLD  (BIT(31))
#define RTC_IO_TOUCH_PAD0_HOLD_M  (BIT(31))
#define RTC_IO_TOUCH_PAD0_HOLD_V  0x1
#define RTC_IO_TOUCH_PAD0_HOLD_S  31
/* RTC_IO_TOUCH_PAD0_DRV : R/W ;bitpos:[30:29] ;default: 2'd2 ; */
/*description: DRV*/
#define RTC_IO_TOUCH_PAD0_DRV  0x00000003
#define RTC_IO_TOUCH_PAD0_DRV_M  ((RTC_IO_TOUCH_PAD0_DRV_V)<<(RTC_IO_TOUCH_PAD0_DRV_S))
#define RTC_IO_TOUCH_PAD0_DRV_V  0x3
#define RTC_IO_TOUCH_PAD0_DRV_S  29
/* RTC_IO_TOUCH_PAD0_RDE : R/W ;bitpos:[28] ;default: 1'd1 ; */
/*description: RDE*/
#define RTC_IO_TOUCH_PAD0_RDE  (BIT(28))
#define RTC_IO_TOUCH_PAD0_RDE_M  (BIT(28))
#define RTC_IO_TOUCH_PAD0_RDE_V  0x1
#define RTC_IO_TOUCH_PAD0_RDE_S  28
/* RTC_IO_TOUCH_PAD0_RUE : R/W ;bitpos:[27] ;default: 1'd0 ; */
/*description: RUE*/
#define RTC_IO_TOUCH_PAD0_RUE  (BIT(27))
#define RTC_IO_TOUCH_PAD0_RUE_M  (BIT(27))
#define RTC_IO_TOUCH_PAD0_RUE_V  0x1
#define RTC_IO_TOUCH_PAD0_RUE_S  27
/* RTC_IO_TOUCH_PAD0_DAC : R/W ;bitpos:[25:23] ;default: 3'h4 ; */
/*description: TOUCH_DAC*/
#define RTC_IO_TOUCH_PAD0_DAC  0x00000007
#define RTC_IO_TOUCH_PAD0_DAC_M  ((RTC_IO_TOUCH_PAD0_DAC_V)<<(RTC_IO_TOUCH_PAD0_DAC_S))
#define RTC_IO_TOUCH_PAD0_DAC_V  0x7
#define RTC_IO_TOUCH_PAD0_DAC_S  23
/* RTC_IO_TOUCH_PAD0_START : R/W ;bitpos:[22] ;default: 1'd0 ; */
/*description: TOUCH_START*/
#define RTC_IO_TOUCH_PAD0_START  (BIT(22))
#define RTC_IO_TOUCH_PAD0_START_M  (BIT(22))
#define RTC_IO_TOUCH_PAD0_START_V  0x1
#define RTC_IO_TOUCH_PAD0_START_S  22
/* RTC_IO_TOUCH_PAD0_TIE_OPT : R/W ;bitpos:[21] ;default: 1'd0 ; */
/*description: TOUCH_TIE_OPT*/
#define RTC_IO_TOUCH_PAD0_TIE_OPT  (BIT(21))
#define RTC_IO_TOUCH_PAD0_TIE_OPT_M  (BIT(21))
#define RTC_IO_TOUCH_PAD0_TIE_OPT_V  0x1
#define RTC_IO_TOUCH_PAD0_TIE_OPT_S  21
/* RTC_IO_TOUCH_PAD0_XPD : R/W ;bitpos:[20] ;default: 1'd0 ; */
/*description: TOUCH_XPD*/
#define RTC_IO_TOUCH_PAD0_XPD  (BIT(20))
#define RTC_IO_TOUCH_PAD0_XPD_M  (BIT(20))
#define RTC_IO_TOUCH_PAD0_XPD_V  0x1
#define RTC_IO_TOUCH_PAD0_XPD_S  20
/* RTC_IO_TOUCH_PAD0_MUX_SEL : R/W ;bitpos:[19] ;default: 1'd0 ; */
/*description: 1: use RTC GPIO 0: use digital GPIO*/
#define RTC_IO_TOUCH_PAD0_MUX_SEL  (BIT(19))
#define RTC_IO_TOUCH_PAD0_MUX_SEL_M  (BIT(19))
#define RTC_IO_TOUCH_PAD0_MUX_SEL_V  0x1
#define RTC_IO_TOUCH_PAD0_MUX_SEL_S  19
/* RTC_IO_TOUCH_PAD0_FUN_SEL : R/W ;bitpos:[18:17] ;default: 2'd0 ; */
/*description: function sel*/
#define RTC_IO_TOUCH_PAD0_FUN_SEL  0x00000003
#define RTC_IO_TOUCH_PAD0_FUN_SEL_M  ((RTC_IO_TOUCH_PAD0_FUN_SEL_V)<<(RTC_IO_TOUCH_PAD0_FUN_SEL_S))
#define RTC_IO_TOUCH_PAD0_FUN_SEL_V  0x3
#define RTC_IO_TOUCH_PAD0_FUN_SEL_S  17
/* RTC_IO_TOUCH_PAD0_SLP_SEL : R/W ;bitpos:[16] ;default: 1'd0 ; */
/*description: 1: enable sleep mode during sleep 0: no sleep mode*/
#define RTC_IO_TOUCH_PAD0_SLP_SEL  (BIT(16))
#define RTC_IO_TOUCH_PAD0_SLP_SEL_M  (BIT(16))
#define RTC_IO_TOUCH_PAD0_SLP_SEL_V  0x1
#define RTC_IO_TOUCH_PAD0_SLP_SEL_S  16
/* RTC_IO_TOUCH_PAD0_SLP_IE : R/W ;bitpos:[15] ;default: 1'd0 ; */
/*description: input enable in sleep mode*/
#define RTC_IO_TOUCH_PAD0_SLP_IE  (BIT(15))
#define RTC_IO_TOUCH_PAD0_SLP_IE_M  (BIT(15))
#define RTC_IO_TOUCH_PAD0_SLP_IE_V  0x1
#define RTC_IO_TOUCH_PAD0_SLP_IE_S  15
/* RTC_IO_TOUCH_PAD0_SLP_OE : R/W ;bitpos:[14] ;default: 1'd0 ; */
/*description: output enable in sleep mode*/
#define RTC_IO_TOUCH_PAD0_SLP_OE  (BIT(14))
#define RTC_IO_TOUCH_PAD0_SLP_OE_M  (BIT(14))
#define RTC_IO_TOUCH_PAD0_SLP_OE_V  0x1
#define RTC_IO_TOUCH_PAD0_SLP_OE_S  14
/* RTC_IO_TOUCH_PAD0_FUN_IE : R/W ;bitpos:[13] ;default: 1'd0 ; */
/*description: input enable in work mode*/
#define RTC_IO_TOUCH_PAD0_FUN_IE  (BIT(13))
#define RTC_IO_TOUCH_PAD0_FUN_IE_M  (BIT(13))
#define RTC_IO_TOUCH_PAD0_FUN_IE_V  0x1
#define RTC_IO_TOUCH_PAD0_FUN_IE_S  13
/* RTC_IO_TOUCH_PAD0_TO_GPIO : R/W ;bitpos:[12] ;default: 1'd0 ; */
/*description: */
#define RTC_IO_TOUCH_PAD0_TO_GPIO  (BIT(12))
#define RTC_IO_TOUCH_PAD0_TO_GPIO_M  (BIT(12))
#define RTC_IO_TOUCH_PAD0_TO_GPIO_V  0x1
#define RTC_IO_TOUCH_PAD0_TO_GPIO_S  12

#define RTC_IO_TOUCH_PAD1_REG          (DR_REG_RTCIO_BASE + 0x98)
/* RTC_IO_TOUCH_PAD1_HOLD : R/W ;bitpos:[31] ;default: 1'd0 ; */
/*description: hold*/
#define RTC_IO_TOUCH_PAD1_HOLD  (BIT(31))
#define RTC_IO_TOUCH_PAD1_HOLD_M  (BIT(31))
#define RTC_IO_TOUCH_PAD1_HOLD_V  0x1
#define RTC_IO_TOUCH_PAD1_HOLD_S  31
/* RTC_IO_TOUCH_PAD1_DRV : R/W ;bitpos:[30:29] ;default: 2'd2 ; */
/*description: DRV*/
#define RTC_IO_TOUCH_PAD1_DRV  0x00000003
#define RTC_IO_TOUCH_PAD1_DRV_M  ((RTC_IO_TOUCH_PAD1_DRV_V)<<(RTC_IO_TOUCH_PAD1_DRV_S))
#define RTC_IO_TOUCH_PAD1_DRV_V  0x3
#define RTC_IO_TOUCH_PAD1_DRV_S  29
/* RTC_IO_TOUCH_PAD1_RDE : R/W ;bitpos:[28] ;default: 1'd0 ; */
/*description: RDE*/
#define RTC_IO_TOUCH_PAD1_RDE  (BIT(28))
#define RTC_IO_TOUCH_PAD1_RDE_M  (BIT(28))
#define RTC_IO_TOUCH_PAD1_RDE_V  0x1
#define RTC_IO_TOUCH_PAD1_RDE_S  28
/* RTC_IO_TOUCH_PAD1_RUE : R/W ;bitpos:[27] ;default: 1'd1 ; */
/*description: RUE*/
#define RTC_IO_TOUCH_PAD1_RUE  (BIT(27))
#define RTC_IO_TOUCH_PAD1_RUE_M  (BIT(27))
#define RTC_IO_TOUCH_PAD1_RUE_V  0x1
#define RTC_IO_TOUCH_PAD1_RUE_S  27
/* RTC_IO_TOUCH_PAD1_DAC : R/W ;bitpos:[25:23] ;default: 3'h4 ; */
/*description: TOUCH_DAC*/
#define RTC_IO_TOUCH_PAD1_DAC  0x00000007
#define RTC_IO_TOUCH_PAD1_DAC_M  ((RTC_IO_TOUCH_PAD1_DAC_V)<<(RTC_IO_TOUCH_PAD1_DAC_S))
#define RTC_IO_TOUCH_PAD1_DAC_V  0x7
#define RTC_IO_TOUCH_PAD1_DAC_S  23
/* RTC_IO_TOUCH_PAD1_START : R/W ;bitpos:[22] ;default: 1'd0 ; */
/*description: TOUCH_START*/
#define RTC_IO_TOUCH_PAD1_START  (BIT(22))
#define RTC_IO_TOUCH_PAD1_START_M  (BIT(22))
#define RTC_IO_TOUCH_PAD1_START_V  0x1
#define RTC_IO_TOUCH_PAD1_START_S  22
/* RTC_IO_TOUCH_PAD1_TIE_OPT : R/W ;bitpos:[21] ;default: 1'd0 ; */
/*description: TOUCH_TIE_OPT*/
#define RTC_IO_TOUCH_PAD1_TIE_OPT  (BIT(21))
#define RTC_IO_TOUCH_PAD1_TIE_OPT_M  (BIT(21))
#define RTC_IO_TOUCH_PAD1_TIE_OPT_V  0x1
#define RTC_IO_TOUCH_PAD1_TIE_OPT_S  21
/* RTC_IO_TOUCH_PAD1_XPD : R/W ;bitpos:[20] ;default: 1'd0 ; */
/*description: TOUCH_XPD*/
#define RTC_IO_TOUCH_PAD1_XPD  (BIT(20))
#define RTC_IO_TOUCH_PAD1_XPD_M  (BIT(20))
#define RTC_IO_TOUCH_PAD1_XPD_V  0x1
#define RTC_IO_TOUCH_PAD1_XPD_S  20
/* RTC_IO_TOUCH_PAD1_MUX_SEL : R/W ;bitpos:[19] ;default: 1'd0 ; */
/*description: 1: use RTC GPIO 0: use digital GPIO*/
#define RTC_IO_TOUCH_PAD1_MUX_SEL  (BIT(19))
#define RTC_IO_TOUCH_PAD1_MUX_SEL_M  (BIT(19))
#define RTC_IO_TOUCH_PAD1_MUX_SEL_V  0x1
#define RTC_IO_TOUCH_PAD1_MUX_SEL_S  19
/* RTC_IO_TOUCH_PAD1_FUN_SEL : R/W ;bitpos:[18:17] ;default: 2'd0 ; */
/*description: function sel*/
#define RTC_IO_TOUCH_PAD1_FUN_SEL  0x00000003
#define RTC_IO_TOUCH_PAD1_FUN_SEL_M  ((RTC_IO_TOUCH_PAD1_FUN_SEL_V)<<(RTC_IO_TOUCH_PAD1_FUN_SEL_S))
#define RTC_IO_TOUCH_PAD1_FUN_SEL_V  0x3
#define RTC_IO_TOUCH_PAD1_FUN_SEL_S  17
/* RTC_IO_TOUCH_PAD1_SLP_SEL : R/W ;bitpos:[16] ;default: 1'd0 ; */
/*description: 1: enable sleep mode during sleep 0: no sleep mode*/
#define RTC_IO_TOUCH_PAD1_SLP_SEL  (BIT(16))
#define RTC_IO_TOUCH_PAD1_SLP_SEL_M  (BIT(16))
#define RTC_IO_TOUCH_PAD1_SLP_SEL_V  0x1
#define RTC_IO_TOUCH_PAD1_SLP_SEL_S  16
/* RTC_IO_TOUCH_PAD1_SLP_IE : R/W ;bitpos:[15] ;default: 1'd0 ; */
/*description: input enable in sleep mode*/
#define RTC_IO_TOUCH_PAD1_SLP_IE  (BIT(15))
#define RTC_IO_TOUCH_PAD1_SLP_IE_M  (BIT(15))
#define RTC_IO_TOUCH_PAD1_SLP_IE_V  0x1
#define RTC_IO_TOUCH_PAD1_SLP_IE_S  15
/* RTC_IO_TOUCH_PAD1_SLP_OE : R/W ;bitpos:[14] ;default: 1'd0 ; */
/*description: output enable in sleep mode*/
#define RTC_IO_TOUCH_PAD1_SLP_OE  (BIT(14))
#define RTC_IO_TOUCH_PAD1_SLP_OE_M  (BIT(14))
#define RTC_IO_TOUCH_PAD1_SLP_OE_V  0x1
#define RTC_IO_TOUCH_PAD1_SLP_OE_S  14
/* RTC_IO_TOUCH_PAD1_FUN_IE : R/W ;bitpos:[13] ;default: 1'd0 ; */
/*description: input enable in work mode*/
#define RTC_IO_TOUCH_PAD1_FUN_IE  (BIT(13))
#define RTC_IO_TOUCH_PAD1_FUN_IE_M  (BIT(13))
#define RTC_IO_TOUCH_PAD1_FUN_IE_V  0x1
#define RTC_IO_TOUCH_PAD1_FUN_IE_S  13
/* RTC_IO_TOUCH_PAD1_TO_GPIO : R/W ;bitpos:[12] ;default: 1'd0 ; */
/*description: */
#define RTC_IO_TOUCH_PAD1_TO_GPIO  (BIT(12))
#define RTC_IO_TOUCH_PAD1_TO_GPIO_M  (BIT(12))
#define RTC_IO_TOUCH_PAD1_TO_GPIO_V  0x1
#define RTC_IO_TOUCH_PAD1_TO_GPIO_S  12

#define RTC_IO_TOUCH_PAD2_REG          (DR_REG_RTCIO_BASE + 0x9c)
/* RTC_IO_TOUCH_PAD2_HOLD : R/W ;bitpos:[31] ;default: 1'd0 ; */
/*description: hold*/
#define RTC_IO_TOUCH_PAD2_HOLD  (BIT(31))
#define RTC_IO_TOUCH_PAD2_HOLD_M  (BIT(31))
#define RTC_IO_TOUCH_PAD2_HOLD_V  0x1
#define RTC_IO_TOUCH_PAD2_HOLD_S  31
/* RTC_IO_TOUCH_PAD2_DRV : R/W ;bitpos:[30:29] ;default: 2'd2 ; */
/*description: DRV*/
#define RTC_IO_TOUCH_PAD2_DRV  0x00000003
#define RTC_IO_TOUCH_PAD2_DRV_M  ((RTC_IO_TOUCH_PAD2_DRV_V)<<(RTC_IO_TOUCH_PAD2_DRV_S))
#define RTC_IO_TOUCH_PAD2_DRV_V  0x3
#define RTC_IO_TOUCH_PAD2_DRV_S  29
/* RTC_IO_TOUCH_PAD2_RDE : R/W ;bitpos:[28] ;default: 1'd1 ; */
/*description: RDE*/
#define RTC_IO_TOUCH_PAD2_RDE  (BIT(28))
#define RTC_IO_TOUCH_PAD2_RDE_M  (BIT(28))
#define RTC_IO_TOUCH_PAD2_RDE_V  0x1
#define RTC_IO_TOUCH_PAD2_RDE_S  28
/* RTC_IO_TOUCH_PAD2_RUE : R/W ;bitpos:[27] ;default: 1'd0 ; */
/*description: RUE*/
#define RTC_IO_TOUCH_PAD2_RUE  (BIT(27))
#define RTC_IO_TOUCH_PAD2_RUE_M  (BIT(27))
#define RTC_IO_TOUCH_PAD2_RUE_V  0x1
#define RTC_IO_TOUCH_PAD2_RUE_S  27
/* RTC_IO_TOUCH_PAD2_DAC : R/W ;bitpos:[25:23] ;default: 3'h4 ; */
/*description: TOUCH_DAC*/
#define RTC_IO_TOUCH_PAD2_DAC  0x00000007
#define RTC_IO_TOUCH_PAD2_DAC_M  ((RTC_IO_TOUCH_PAD2_DAC_V)<<(RTC_IO_TOUCH_PAD2_DAC_S))
#define RTC_IO_TOUCH_PAD2_DAC_V  0x7
#define RTC_IO_TOUCH_PAD2_DAC_S  23
/* RTC_IO_TOUCH_PAD2_START : R/W ;bitpos:[22] ;default: 1'd0 ; */
/*description: TOUCH_START*/
#define RTC_IO_TOUCH_PAD2_START  (BIT(22))
#define RTC_IO_TOUCH_PAD2_START_M  (BIT(22))
#define RTC_IO_TOUCH_PAD2_START_V  0x1
#define RTC_IO_TOUCH_PAD2_START_S  22
/* RTC_IO_TOUCH_PAD2_TIE_OPT : R/W ;bitpos:[21] ;default: 1'd0 ; */
/*description: TOUCH_TIE_OPT*/
#define RTC_IO_TOUCH_PAD2_TIE_OPT  (BIT(21))
#define RTC_IO_TOUCH_PAD2_TIE_OPT_M  (BIT(21))
#define RTC_IO_TOUCH_PAD2_TIE_OPT_V  0x1
#define RTC_IO_TOUCH_PAD2_TIE_OPT_S  21
/* RTC_IO_TOUCH_PAD2_XPD : R/W ;bitpos:[20] ;default: 1'd0 ; */
/*description: TOUCH_XPD*/
#define RTC_IO_TOUCH_PAD2_XPD  (BIT(20))
#define RTC_IO_TOUCH_PAD2_XPD_M  (BIT(20))
#define RTC_IO_TOUCH_PAD2_XPD_V  0x1
#define RTC_IO_TOUCH_PAD2_XPD_S  20
/* RTC_IO_TOUCH_PAD2_MUX_SEL : R/W ;bitpos:[19] ;default: 1'd0 ; */
/*description: 1: use RTC GPIO 0: use digital GPIO*/
#define RTC_IO_TOUCH_PAD2_MUX_SEL  (BIT(19))
#define RTC_IO_TOUCH_PAD2_MUX_SEL_M  (BIT(19))
#define RTC_IO_TOUCH_PAD2_MUX_SEL_V  0x1
#define RTC_IO_TOUCH_PAD2_MUX_SEL_S  19
/* RTC_IO_TOUCH_PAD2_FUN_SEL : R/W ;bitpos:[18:17] ;default: 2'd0 ; */
/*description: function sel*/
#define RTC_IO_TOUCH_PAD2_FUN_SEL  0x00000003
#define RTC_IO_TOUCH_PAD2_FUN_SEL_M  ((RTC_IO_TOUCH_PAD2_FUN_SEL_V)<<(RTC_IO_TOUCH_PAD2_FUN_SEL_S))
#define RTC_IO_TOUCH_PAD2_FUN_SEL_V  0x3
#define RTC_IO_TOUCH_PAD2_FUN_SEL_S  17
/* RTC_IO_TOUCH_PAD2_SLP_SEL : R/W ;bitpos:[16] ;default: 1'd0 ; */
/*description: 1: enable sleep mode during sleep 0: no sleep mode*/
#define RTC_IO_TOUCH_PAD2_SLP_SEL  (BIT(16))
#define RTC_IO_TOUCH_PAD2_SLP_SEL_M  (BIT(16))
#define RTC_IO_TOUCH_PAD2_SLP_SEL_V  0x1
#define RTC_IO_TOUCH_PAD2_SLP_SEL_S  16
/* RTC_IO_TOUCH_PAD2_SLP_IE : R/W ;bitpos:[15] ;default: 1'd0 ; */
/*description: input enable in sleep mode*/
#define RTC_IO_TOUCH_PAD2_SLP_IE  (BIT(15))
#define RTC_IO_TOUCH_PAD2_SLP_IE_M  (BIT(15))
#define RTC_IO_TOUCH_PAD2_SLP_IE_V  0x1
#define RTC_IO_TOUCH_PAD2_SLP_IE_S  15
/* RTC_IO_TOUCH_PAD2_SLP_OE : R/W ;bitpos:[14] ;default: 1'd0 ; */
/*description: output enable in sleep mode*/
#define RTC_IO_TOUCH_PAD2_SLP_OE  (BIT(14))
#define RTC_IO_TOUCH_PAD2_SLP_OE_M  (BIT(14))
#define RTC_IO_TOUCH_PAD2_SLP_OE_V  0x1
#define RTC_IO_TOUCH_PAD2_SLP_OE_S  14
/* RTC_IO_TOUCH_PAD2_FUN_IE : R/W ;bitpos:[13] ;default: 1'd0 ; */
/*description: input enable in work mode*/
#define RTC_IO_TOUCH_PAD2_FUN_IE  (BIT(13))
#define RTC_IO_TOUCH_PAD2_FUN_IE_M  (BIT(13))
#define RTC_IO_TOUCH_PAD2_FUN_IE_V  0x1
#define RTC_IO_TOUCH_PAD2_FUN_IE_S  13
/* RTC_IO_TOUCH_PAD2_TO_GPIO : R/W ;bitpos:[12] ;default: 1'd0 ; */
/*description: */
#define RTC_IO_TOUCH_PAD2_TO_GPIO  (BIT(12))
#define RTC_IO_TOUCH_PAD2_TO_GPIO_M  (BIT(12))
#define RTC_IO_TOUCH_PAD2_TO_GPIO_V  0x1
#define RTC_IO_TOUCH_PAD2_TO_GPIO_S  12

#define RTC_IO_TOUCH_PAD3_REG          (DR_REG_RTCIO_BASE + 0xa0)
/* RTC_IO_TOUCH_PAD3_HOLD : R/W ;bitpos:[31] ;default: 1'd0 ; */
/*description: hold*/
#define RTC_IO_TOUCH_PAD3_HOLD  (BIT(31))
#define RTC_IO_TOUCH_PAD3_HOLD_M  (BIT(31))
#define RTC_IO_TOUCH_PAD3_HOLD_V  0x1
#define RTC_IO_TOUCH_PAD3_HOLD_S  31
/* RTC_IO_TOUCH_PAD3_DRV : R/W ;bitpos:[30:29] ;default: 2'd2 ; */
/*description: DRV*/
#define RTC_IO_TOUCH_PAD3_DRV  0x00000003
#define RTC_IO_TOUCH_PAD3_DRV_M  ((RTC_IO_TOUCH_PAD3_DRV_V)<<(RTC_IO_TOUCH_PAD3_DRV_S))
#define RTC_IO_TOUCH_PAD3_DRV_V  0x3
#define RTC_IO_TOUCH_PAD3_DRV_S  29
/* RTC_IO_TOUCH_PAD3_RDE : R/W ;bitpos:[28] ;default: 1'd0 ; */
/*description: RDE*/
#define RTC_IO_TOUCH_PAD3_RDE  (BIT(28))
#define RTC_IO_TOUCH_PAD3_RDE_M  (BIT(28))
#define RTC_IO_TOUCH_PAD3_RDE_V  0x1
#define RTC_IO_TOUCH_PAD3_RDE_S  28
/* RTC_IO_TOUCH_PAD3_RUE : R/W ;bitpos:[27] ;default: 1'd1 ; */
/*description: RUE*/
#define RTC_IO_TOUCH_PAD3_RUE  (BIT(27))
#define RTC_IO_TOUCH_PAD3_RUE_M  (BIT(27))
#define RTC_IO_TOUCH_PAD3_RUE_V  0x1
#define RTC_IO_TOUCH_PAD3_RUE_S  27
/* RTC_IO_TOUCH_PAD3_DAC : R/W ;bitpos:[25:23] ;default: 3'h4 ; */
/*description: TOUCH_DAC*/
#define RTC_IO_TOUCH_PAD3_DAC  0x00000007
#define RTC_IO_TOUCH_PAD3_DAC_M  ((RTC_IO_TOUCH_PAD3_DAC_V)<<(RTC_IO_TOUCH_PAD3_DAC_S))
#define RTC_IO_TOUCH_PAD3_DAC_V  0x7
#define RTC_IO_TOUCH_PAD3_DAC_S  23
/* RTC_IO_TOUCH_PAD3_START : R/W ;bitpos:[22] ;default: 1'd0 ; */
/*description: TOUCH_START*/
#define RTC_IO_TOUCH_PAD3_START  (BIT(22))
#define RTC_IO_TOUCH_PAD3_START_M  (BIT(22))
#define RTC_IO_TOUCH_PAD3_START_V  0x1
#define RTC_IO_TOUCH_PAD3_START_S  22
/* RTC_IO_TOUCH_PAD3_TIE_OPT : R/W ;bitpos:[21] ;default: 1'd0 ; */
/*description: TOUCH_TIE_OPT*/
#define RTC_IO_TOUCH_PAD3_TIE_OPT  (BIT(21))
#define RTC_IO_TOUCH_PAD3_TIE_OPT_M  (BIT(21))
#define RTC_IO_TOUCH_PAD3_TIE_OPT_V  0x1
#define RTC_IO_TOUCH_PAD3_TIE_OPT_S  21
/* RTC_IO_TOUCH_PAD3_XPD : R/W ;bitpos:[20] ;default: 1'd0 ; */
/*description: TOUCH_XPD*/
#define RTC_IO_TOUCH_PAD3_XPD  (BIT(20))
#define RTC_IO_TOUCH_PAD3_XPD_M  (BIT(20))
#define RTC_IO_TOUCH_PAD3_XPD_V  0x1
#define RTC_IO_TOUCH_PAD3_XPD_S  20
/* RTC_IO_TOUCH_PAD3_MUX_SEL : R/W ;bitpos:[19] ;default: 1'd0 ; */
/*description: 1: use RTC GPIO 0: use digital GPIO*/
#define RTC_IO_TOUCH_PAD3_MUX_SEL  (BIT(19))
#define RTC_IO_TOUCH_PAD3_MUX_SEL_M  (BIT(19))
#define RTC_IO_TOUCH_PAD3_MUX_SEL_V  0x1
#define RTC_IO_TOUCH_PAD3_MUX_SEL_S  19
/* RTC_IO_TOUCH_PAD3_FUN_SEL : R/W ;bitpos:[18:17] ;default: 2'd0 ; */
/*description: function sel*/
#define RTC_IO_TOUCH_PAD3_FUN_SEL  0x00000003
#define RTC_IO_TOUCH_PAD3_FUN_SEL_M  ((RTC_IO_TOUCH_PAD3_FUN_SEL_V)<<(RTC_IO_TOUCH_PAD3_FUN_SEL_S))
#define RTC_IO_TOUCH_PAD3_FUN_SEL_V  0x3
#define RTC_IO_TOUCH_PAD3_FUN_SEL_S  17
/* RTC_IO_TOUCH_PAD3_SLP_SEL : R/W ;bitpos:[16] ;default: 1'd0 ; */
/*description: 1: enable sleep mode during sleep 0: no sleep mode*/
#define RTC_IO_TOUCH_PAD3_SLP_SEL  (BIT(16))
#define RTC_IO_TOUCH_PAD3_SLP_SEL_M  (BIT(16))
#define RTC_IO_TOUCH_PAD3_SLP_SEL_V  0x1
#define RTC_IO_TOUCH_PAD3_SLP_SEL_S  16
/* RTC_IO_TOUCH_PAD3_SLP_IE : R/W ;bitpos:[15] ;default: 1'd0 ; */
/*description: input enable in sleep mode*/
#define RTC_IO_TOUCH_PAD3_SLP_IE  (BIT(15))
#define RTC_IO_TOUCH_PAD3_SLP_IE_M  (BIT(15))
#define RTC_IO_TOUCH_PAD3_SLP_IE_V  0x1
#define RTC_IO_TOUCH_PAD3_SLP_IE_S  15
/* RTC_IO_TOUCH_PAD3_SLP_OE : R/W ;bitpos:[14] ;default: 1'd0 ; */
/*description: output enable in sleep mode*/
#define RTC_IO_TOUCH_PAD3_SLP_OE  (BIT(14))
#define RTC_IO_TOUCH_PAD3_SLP_OE_M  (BIT(14))
#define RTC_IO_TOUCH_PAD3_SLP_OE_V  0x1
#define RTC_IO_TOUCH_PAD3_SLP_OE_S  14
/* RTC_IO_TOUCH_PAD3_FUN_IE : R/W ;bitpos:[13] ;default: 1'd0 ; */
/*description: input enable in work mode*/
#define RTC_IO_TOUCH_PAD3_FUN_IE  (BIT(13))
#define RTC_IO_TOUCH_PAD3_FUN_IE_M  (BIT(13))
#define RTC_IO_TOUCH_PAD3_FUN_IE_V  0x1
#define RTC_IO_TOUCH_PAD3_FUN_IE_S  13
/* RTC_IO_TOUCH_PAD3_TO_GPIO : R/W ;bitpos:[12] ;default: 1'd0 ; */
/*description: */
#define RTC_IO_TOUCH_PAD3_TO_GPIO  (BIT(12))
#define RTC_IO_TOUCH_PAD3_TO_GPIO_M  (BIT(12))
#define RTC_IO_TOUCH_PAD3_TO_GPIO_V  0x1
#define RTC_IO_TOUCH_PAD3_TO_GPIO_S  12

#define RTC_IO_TOUCH_PAD4_REG          (DR_REG_RTCIO_BASE + 0xa4)
/* RTC_IO_TOUCH_PAD4_HOLD : R/W ;bitpos:[31] ;default: 1'd0 ; */
/*description: hold*/
#define RTC_IO_TOUCH_PAD4_HOLD  (BIT(31))
#define RTC_IO_TOUCH_PAD4_HOLD_M  (BIT(31))
#define RTC_IO_TOUCH_PAD4_HOLD_V  0x1
#define RTC_IO_TOUCH_PAD4_HOLD_S  31
/* RTC_IO_TOUCH_PAD4_DRV : R/W ;bitpos:[30:29] ;default: 2'd2 ; */
/*description: DRV*/
#define RTC_IO_TOUCH_PAD4_DRV  0x00000003
#define RTC_IO_TOUCH_PAD4_DRV_M  ((RTC_IO_TOUCH_PAD4_DRV_V)<<(RTC_IO_TOUCH_PAD4_DRV_S))
#define RTC_IO_TOUCH_PAD4_DRV_V  0x3
#define RTC_IO_TOUCH_PAD4_DRV_S  29
/* RTC_IO_TOUCH_PAD4_RDE : R/W ;bitpos:[28] ;default: 1'd1 ; */
/*description: RDE*/
#define RTC_IO_TOUCH_PAD4_RDE  (BIT(28))
#define RTC_IO_TOUCH_PAD4_RDE_M  (BIT(28))
#define RTC_IO_TOUCH_PAD4_RDE_V  0x1
#define RTC_IO_TOUCH_PAD4_RDE_S  28
/* RTC_IO_TOUCH_PAD4_RUE : R/W ;bitpos:[27] ;default: 1'd0 ; */
/*description: RUE*/
#define RTC_IO_TOUCH_PAD4_RUE  (BIT(27))
#define RTC_IO_TOUCH_PAD4_RUE_M  (BIT(27))
#define RTC_IO_TOUCH_PAD4_RUE_V  0x1
#define RTC_IO_TOUCH_PAD4_RUE_S  27
/* RTC_IO_TOUCH_PAD4_DAC : R/W ;bitpos:[25:23] ;default: 3'h4 ; */
/*description: TOUCH_DAC*/
#define RTC_IO_TOUCH_PAD4_DAC  0x00000007
#define RTC_IO_TOUCH_PAD4_DAC_M  ((RTC_IO_TOUCH_PAD4_DAC_V)<<(RTC_IO_TOUCH_PAD4_DAC_S))
#define RTC_IO_TOUCH_PAD4_DAC_V  0x7
#define RTC_IO_TOUCH_PAD4_DAC_S  23
/* RTC_IO_TOUCH_PAD4_START : R/W ;bitpos:[22] ;default: 1'd0 ; */
/*description: TOUCH_START*/
#define RTC_IO_TOUCH_PAD4_START  (BIT(22))
#define RTC_IO_TOUCH_PAD4_START_M  (BIT(22))
#define RTC_IO_TOUCH_PAD4_START_V  0x1
#define RTC_IO_TOUCH_PAD4_START_S  22
/* RTC_IO_TOUCH_PAD4_TIE_OPT : R/W ;bitpos:[21] ;default: 1'd0 ; */
/*description: TOUCH_TIE_OPT*/
#define RTC_IO_TOUCH_PAD4_TIE_OPT  (BIT(21))
#define RTC_IO_TOUCH_PAD4_TIE_OPT_M  (BIT(21))
#define RTC_IO_TOUCH_PAD4_TIE_OPT_V  0x1
#define RTC_IO_TOUCH_PAD4_TIE_OPT_S  21
/* RTC_IO_TOUCH_PAD4_XPD : R/W ;bitpos:[20] ;default: 1'd0 ; */
/*description: TOUCH_XPD*/
#define RTC_IO_TOUCH_PAD4_XPD  (BIT(20))
#define RTC_IO_TOUCH_PAD4_XPD_M  (BIT(20))
#define RTC_IO_TOUCH_PAD4_XPD_V  0x1
#define RTC_IO_TOUCH_PAD4_XPD_S  20
/* RTC_IO_TOUCH_PAD4_MUX_SEL : R/W ;bitpos:[19] ;default: 1'd0 ; */
/*description: 1: use RTC GPIO 0: use digital GPIO*/
#define RTC_IO_TOUCH_PAD4_MUX_SEL  (BIT(19))
#define RTC_IO_TOUCH_PAD4_MUX_SEL_M  (BIT(19))
#define RTC_IO_TOUCH_PAD4_MUX_SEL_V  0x1
#define RTC_IO_TOUCH_PAD4_MUX_SEL_S  19
/* RTC_IO_TOUCH_PAD4_FUN_SEL : R/W ;bitpos:[18:17] ;default: 2'd0 ; */
/*description: function sel*/
#define RTC_IO_TOUCH_PAD4_FUN_SEL  0x00000003
#define RTC_IO_TOUCH_PAD4_FUN_SEL_M  ((RTC_IO_TOUCH_PAD4_FUN_SEL_V)<<(RTC_IO_TOUCH_PAD4_FUN_SEL_S))
#define RTC_IO_TOUCH_PAD4_FUN_SEL_V  0x3
#define RTC_IO_TOUCH_PAD4_FUN_SEL_S  17
/* RTC_IO_TOUCH_PAD4_SLP_SEL : R/W ;bitpos:[16] ;default: 1'd0 ; */
/*description: 1: enable sleep mode during sleep 0: no sleep mode*/
#define RTC_IO_TOUCH_PAD4_SLP_SEL  (BIT(16))
#define RTC_IO_TOUCH_PAD4_SLP_SEL_M  (BIT(16))
#define RTC_IO_TOUCH_PAD4_SLP_SEL_V  0x1
#define RTC_IO_TOUCH_PAD4_SLP_SEL_S  16
/* RTC_IO_TOUCH_PAD4_SLP_IE : R/W ;bitpos:[15] ;default: 1'd0 ; */
/*description: input enable in sleep mode*/
#define RTC_IO_TOUCH_PAD4_SLP_IE  (BIT(15))
#define RTC_IO_TOUCH_PAD4_SLP_IE_M  (BIT(15))
#define RTC_IO_TOUCH_PAD4_SLP_IE_V  0x1
#define RTC_IO_TOUCH_PAD4_SLP_IE_S  15
/* RTC_IO_TOUCH_PAD4_SLP_OE : R/W ;bitpos:[14] ;default: 1'd0 ; */
/*description: output enable in sleep mode*/
#define RTC_IO_TOUCH_PAD4_SLP_OE  (BIT(14))
#define RTC_IO_TOUCH_PAD4_SLP_OE_M  (BIT(14))
#define RTC_IO_TOUCH_PAD4_SLP_OE_V  0x1
#define RTC_IO_TOUCH_PAD4_SLP_OE_S  14
/* RTC_IO_TOUCH_PAD4_FUN_IE : R/W ;bitpos:[13] ;default: 1'd0 ; */
/*description: input enable in work mode*/
#define RTC_IO_TOUCH_PAD4_FUN_IE  (BIT(13))
#define RTC_IO_TOUCH_PAD4_FUN_IE_M  (BIT(13))
#define RTC_IO_TOUCH_PAD4_FUN_IE_V  0x1
#define RTC_IO_TOUCH_PAD4_FUN_IE_S  13
/* RTC_IO_TOUCH_PAD4_TO_GPIO : R/W ;bitpos:[12] ;default: 1'd0 ; */
/*description: */
#define RTC_IO_TOUCH_PAD4_TO_GPIO  (BIT(12))
#define RTC_IO_TOUCH_PAD4_TO_GPIO_M  (BIT(12))
#define RTC_IO_TOUCH_PAD4_TO_GPIO_V  0x1
#define RTC_IO_TOUCH_PAD4_TO_GPIO_S  12

#define RTC_IO_TOUCH_PAD5_REG          (DR_REG_RTCIO_BASE + 0xa8)
/* RTC_IO_TOUCH_PAD5_HOLD : R/W ;bitpos:[31] ;default: 1'd0 ; */
/*description: hold*/
#define RTC_IO_TOUCH_PAD5_HOLD  (BIT(31))
#define RTC_IO_TOUCH_PAD5_HOLD_M  (BIT(31))
#define RTC_IO_TOUCH_PAD5_HOLD_V  0x1
#define RTC_IO_TOUCH_PAD5_HOLD_S  31
/* RTC_IO_TOUCH_PAD5_DRV : R/W ;bitpos:[30:29] ;default: 2'd2 ; */
/*description: DRV*/
#define RTC_IO_TOUCH_PAD5_DRV  0x00000003
#define RTC_IO_TOUCH_PAD5_DRV_M  ((RTC_IO_TOUCH_PAD5_DRV_V)<<(RTC_IO_TOUCH_PAD5_DRV_S))
#define RTC_IO_TOUCH_PAD5_DRV_V  0x3
#define RTC_IO_TOUCH_PAD5_DRV_S  29
/* RTC_IO_TOUCH_PAD5_RDE : R/W ;bitpos:[28] ;default: 1'd1 ; */
/*description: RDE*/
#define RTC_IO_TOUCH_PAD5_RDE  (BIT(28))
#define RTC_IO_TOUCH_PAD5_RDE_M  (BIT(28))
#define RTC_IO_TOUCH_PAD5_RDE_V  0x1
#define RTC_IO_TOUCH_PAD5_RDE_S  28
/* RTC_IO_TOUCH_PAD5_RUE : R/W ;bitpos:[27] ;default: 1'd0 ; */
/*description: RUE*/
#define RTC_IO_TOUCH_PAD5_RUE  (BIT(27))
#define RTC_IO_TOUCH_PAD5_RUE_M  (BIT(27))
#define RTC_IO_TOUCH_PAD5_RUE_V  0x1
#define RTC_IO_TOUCH_PAD5_RUE_S  27
/* RTC_IO_TOUCH_PAD5_DAC : R/W ;bitpos:[25:23] ;default: 3'h4 ; */
/*description: TOUCH_DAC*/
#define RTC_IO_TOUCH_PAD5_DAC  0x00000007
#define RTC_IO_TOUCH_PAD5_DAC_M  ((RTC_IO_TOUCH_PAD5_DAC_V)<<(RTC_IO_TOUCH_PAD5_DAC_S))
#define RTC_IO_TOUCH_PAD5_DAC_V  0x7
#define RTC_IO_TOUCH_PAD5_DAC_S  23
/* RTC_IO_TOUCH_PAD5_START : R/W ;bitpos:[22] ;default: 1'd0 ; */
/*description: TOUCH_START*/
#define RTC_IO_TOUCH_PAD5_START  (BIT(22))
#define RTC_IO_TOUCH_PAD5_START_M  (BIT(22))
#define RTC_IO_TOUCH_PAD5_START_V  0x1
#define RTC_IO_TOUCH_PAD5_START_S  22
/* RTC_IO_TOUCH_PAD5_TIE_OPT : R/W ;bitpos:[21] ;default: 1'd0 ; */
/*description: TOUCH_TIE_OPT*/
#define RTC_IO_TOUCH_PAD5_TIE_OPT  (BIT(21))
#define RTC_IO_TOUCH_PAD5_TIE_OPT_M  (BIT(21))
#define RTC_IO_TOUCH_PAD5_TIE_OPT_V  0x1
#define RTC_IO_TOUCH_PAD5_TIE_OPT_S  21
/* RTC_IO_TOUCH_PAD5_XPD : R/W ;bitpos:[20] ;default: 1'd0 ; */
/*description: TOUCH_XPD*/
#define RTC_IO_TOUCH_PAD5_XPD  (BIT(20))
#define RTC_IO_TOUCH_PAD5_XPD_M  (BIT(20))
#define RTC_IO_TOUCH_PAD5_XPD_V  0x1
#define RTC_IO_TOUCH_PAD5_XPD_S  20
/* RTC_IO_TOUCH_PAD5_MUX_SEL : R/W ;bitpos:[19] ;default: 1'd0 ; */
/*description: 1: use RTC GPIO 0: use digital GPIO*/
#define RTC_IO_TOUCH_PAD5_MUX_SEL  (BIT(19))
#define RTC_IO_TOUCH_PAD5_MUX_SEL_M  (BIT(19))
#define RTC_IO_TOUCH_PAD5_MUX_SEL_V  0x1
#define RTC_IO_TOUCH_PAD5_MUX_SEL_S  19
/* RTC_IO_TOUCH_PAD5_FUN_SEL : R/W ;bitpos:[18:17] ;default: 2'd0 ; */
/*description: function sel*/
#define RTC_IO_TOUCH_PAD5_FUN_SEL  0x00000003
#define RTC_IO_TOUCH_PAD5_FUN_SEL_M  ((RTC_IO_TOUCH_PAD5_FUN_SEL_V)<<(RTC_IO_TOUCH_PAD5_FUN_SEL_S))
#define RTC_IO_TOUCH_PAD5_FUN_SEL_V  0x3
#define RTC_IO_TOUCH_PAD5_FUN_SEL_S  17
/* RTC_IO_TOUCH_PAD5_SLP_SEL : R/W ;bitpos:[16] ;default: 1'd0 ; */
/*description: 1: enable sleep mode during sleep 0: no sleep mode*/
#define RTC_IO_TOUCH_PAD5_SLP_SEL  (BIT(16))
#define RTC_IO_TOUCH_PAD5_SLP_SEL_M  (BIT(16))
#define RTC_IO_TOUCH_PAD5_SLP_SEL_V  0x1
#define RTC_IO_TOUCH_PAD5_SLP_SEL_S  16
/* RTC_IO_TOUCH_PAD5_SLP_IE : R/W ;bitpos:[15] ;default: 1'd0 ; */
/*description: input enable in sleep mode*/
#define RTC_IO_TOUCH_PAD5_SLP_IE  (BIT(15))
#define RTC_IO_TOUCH_PAD5_SLP_IE_M  (BIT(15))
#define RTC_IO_TOUCH_PAD5_SLP_IE_V  0x1
#define RTC_IO_TOUCH_PAD5_SLP_IE_S  15
/* RTC_IO_TOUCH_PAD5_SLP_OE : R/W ;bitpos:[14] ;default: 1'd0 ; */
/*description: output enable in sleep mode*/
#define RTC_IO_TOUCH_PAD5_SLP_OE  (BIT(14))
#define RTC_IO_TOUCH_PAD5_SLP_OE_M  (BIT(14))
#define RTC_IO_TOUCH_PAD5_SLP_OE_V  0x1
#define RTC_IO_TOUCH_PAD5_SLP_OE_S  14
/* RTC_IO_TOUCH_PAD5_FUN_IE : R/W ;bitpos:[13] ;default: 1'd0 ; */
/*description: input enable in work mode*/
#define RTC_IO_TOUCH_PAD5_FUN_IE  (BIT(13))
#define RTC_IO_TOUCH_PAD5_FUN_IE_M  (BIT(13))
#define RTC_IO_TOUCH_PAD5_FUN_IE_V  0x1
#define RTC_IO_TOUCH_PAD5_FUN_IE_S  13
/* RTC_IO_TOUCH_PAD5_TO_GPIO : R/W ;bitpos:[12] ;default: 1'd0 ; */
/*description: */
#define RTC_IO_TOUCH_PAD5_TO_GPIO  (BIT(12))
#define RTC_IO_TOUCH_PAD5_TO_GPIO_M  (BIT(12))
#define RTC_IO_TOUCH_PAD5_TO_GPIO_V  0x1
#define RTC_IO_TOUCH_PAD5_TO_GPIO_S  12

#define RTC_IO_TOUCH_PAD6_REG          (DR_REG_RTCIO_BASE + 0xac)
/* RTC_IO_TOUCH_PAD6_HOLD : R/W ;bitpos:[31] ;default: 1'd0 ; */
/*description: hold*/
#define RTC_IO_TOUCH_PAD6_HOLD  (BIT(31))
#define RTC_IO_TOUCH_PAD6_HOLD_M  (BIT(31))
#define RTC_IO_TOUCH_PAD6_HOLD_V  0x1
#define RTC_IO_TOUCH_PAD6_HOLD_S  31
/* RTC_IO_TOUCH_PAD6_DRV : R/W ;bitpos:[30:29] ;default: 2'd2 ; */
/*description: DRV*/
#define RTC_IO_TOUCH_PAD6_DRV  0x00000003
#define RTC_IO_TOUCH_PAD6_DRV_M  ((RTC_IO_TOUCH_PAD6_DRV_V)<<(RTC_IO_TOUCH_PAD6_DRV_S))
#define RTC_IO_TOUCH_PAD6_DRV_V  0x3
#define RTC_IO_TOUCH_PAD6_DRV_S  29
/* RTC_IO_TOUCH_PAD6_RDE : R/W ;bitpos:[28] ;default: 1'd0 ; */
/*description: RDE*/
#define RTC_IO_TOUCH_PAD6_RDE  (BIT(28))
#define RTC_IO_TOUCH_PAD6_RDE_M  (BIT(28))
#define RTC_IO_TOUCH_PAD6_RDE_V  0x1
#define RTC_IO_TOUCH_PAD6_RDE_S  28
/* RTC_IO_TOUCH_PAD6_RUE : R/W ;bitpos:[27] ;default: 1'd1 ; */
/*description: RUE*/
#define RTC_IO_TOUCH_PAD6_RUE  (BIT(27))
#define RTC_IO_TOUCH_PAD6_RUE_M  (BIT(27))
#define RTC_IO_TOUCH_PAD6_RUE_V  0x1
#define RTC_IO_TOUCH_PAD6_RUE_S  27
/* RTC_IO_TOUCH_PAD6_DAC : R/W ;bitpos:[25:23] ;default: 3'h4 ; */
/*description: TOUCH_DAC*/
#define RTC_IO_TOUCH_PAD6_DAC  0x00000007
#define RTC_IO_TOUCH_PAD6_DAC_M  ((RTC_IO_TOUCH_PAD6_DAC_V)<<(RTC_IO_TOUCH_PAD6_DAC_S))
#define RTC_IO_TOUCH_PAD6_DAC_V  0x7
#define RTC_IO_TOUCH_PAD6_DAC_S  23
/* RTC_IO_TOUCH_PAD6_START : R/W ;bitpos:[22] ;default: 1'd0 ; */
/*description: TOUCH_START*/
#define RTC_IO_TOUCH_PAD6_START  (BIT(22))
#define RTC_IO_TOUCH_PAD6_START_M  (BIT(22))
#define RTC_IO_TOUCH_PAD6_START_V  0x1
#define RTC_IO_TOUCH_PAD6_START_S  22
/* RTC_IO_TOUCH_PAD6_TIE_OPT : R/W ;bitpos:[21] ;default: 1'd0 ; */
/*description: TOUCH_TIE_OPT*/
#define RTC_IO_TOUCH_PAD6_TIE_OPT  (BIT(21))
#define RTC_IO_TOUCH_PAD6_TIE_OPT_M  (BIT(21))
#define RTC_IO_TOUCH_PAD6_TIE_OPT_V  0x1
#define RTC_IO_TOUCH_PAD6_TIE_OPT_S  21
/* RTC_IO_TOUCH_PAD6_XPD : R/W ;bitpos:[20] ;default: 1'd0 ; */
/*description: TOUCH_XPD*/
#define RTC_IO_TOUCH_PAD6_XPD  (BIT(20))
#define RTC_IO_TOUCH_PAD6_XPD_M  (BIT(20))
#define RTC_IO_TOUCH_PAD6_XPD_V  0x1
#define RTC_IO_TOUCH_PAD6_XPD_S  20
/* RTC_IO_TOUCH_PAD6_MUX_SEL : R/W ;bitpos:[19] ;default: 1'd0 ; */
/*description: 1: use RTC GPIO 0: use digital GPIO*/
#define RTC_IO_TOUCH_PAD6_MUX_SEL  (BIT(19))
#define RTC_IO_TOUCH_PAD6_MUX_SEL_M  (BIT(19))
#define RTC_IO_TOUCH_PAD6_MUX_SEL_V  0x1
#define RTC_IO_TOUCH_PAD6_MUX_SEL_S  19
/* RTC_IO_TOUCH_PAD6_FUN_SEL : R/W ;bitpos:[18:17] ;default: 2'd0 ; */
/*description: function sel*/
#define RTC_IO_TOUCH_PAD6_FUN_SEL  0x00000003
#define RTC_IO_TOUCH_PAD6_FUN_SEL_M  ((RTC_IO_TOUCH_PAD6_FUN_SEL_V)<<(RTC_IO_TOUCH_PAD6_FUN_SEL_S))
#define RTC_IO_TOUCH_PAD6_FUN_SEL_V  0x3
#define RTC_IO_TOUCH_PAD6_FUN_SEL_S  17
/* RTC_IO_TOUCH_PAD6_SLP_SEL : R/W ;bitpos:[16] ;default: 1'd0 ; */
/*description: 1: enable sleep mode during sleep 0: no sleep mode*/
#define RTC_IO_TOUCH_PAD6_SLP_SEL  (BIT(16))
#define RTC_IO_TOUCH_PAD6_SLP_SEL_M  (BIT(16))
#define RTC_IO_TOUCH_PAD6_SLP_SEL_V  0x1
#define RTC_IO_TOUCH_PAD6_SLP_SEL_S  16
/* RTC_IO_TOUCH_PAD6_SLP_IE : R/W ;bitpos:[15] ;default: 1'd0 ; */
/*description: input enable in sleep mode*/
#define RTC_IO_TOUCH_PAD6_SLP_IE  (BIT(15))
#define RTC_IO_TOUCH_PAD6_SLP_IE_M  (BIT(15))
#define RTC_IO_TOUCH_PAD6_SLP_IE_V  0x1
#define RTC_IO_TOUCH_PAD6_SLP_IE_S  15
/* RTC_IO_TOUCH_PAD6_SLP_OE : R/W ;bitpos:[14] ;default: 1'd0 ; */
/*description: output enable in sleep mode*/
#define RTC_IO_TOUCH_PAD6_SLP_OE  (BIT(14))
#define RTC_IO_TOUCH_PAD6_SLP_OE_M  (BIT(14))
#define RTC_IO_TOUCH_PAD6_SLP_OE_V  0x1
#define RTC_IO_TOUCH_PAD6_SLP_OE_S  14
/* RTC_IO_TOUCH_PAD6_FUN_IE : R/W ;bitpos:[13] ;default: 1'd0 ; */
/*description: input enable in work mode*/
#define RTC_IO_TOUCH_PAD6_FUN_IE  (BIT(13))
#define RTC_IO_TOUCH_PAD6_FUN_IE_M  (BIT(13))
#define RTC_IO_TOUCH_PAD6_FUN_IE_V  0x1
#define RTC_IO_TOUCH_PAD6_FUN_IE_S  13
/* RTC_IO_TOUCH_PAD6_TO_GPIO : R/W ;bitpos:[12] ;default: 1'd0 ; */
/*description: */
#define RTC_IO_TOUCH_PAD6_TO_GPIO  (BIT(12))
#define RTC_IO_TOUCH_PAD6_TO_GPIO_M  (BIT(12))
#define RTC_IO_TOUCH_PAD6_TO_GPIO_V  0x1
#define RTC_IO_TOUCH_PAD6_TO_GPIO_S  12

#define RTC_IO_TOUCH_PAD7_REG          (DR_REG_RTCIO_BASE + 0xb0)
/* RTC_IO_TOUCH_PAD7_HOLD : R/W ;bitpos:[31] ;default: 1'd0 ; */
/*description: hold*/
#define RTC_IO_TOUCH_PAD7_HOLD  (BIT(31))
#define RTC_IO_TOUCH_PAD7_HOLD_M  (BIT(31))
#define RTC_IO_TOUCH_PAD7_HOLD_V  0x1
#define RTC_IO_TOUCH_PAD7_HOLD_S  31
/* RTC_IO_TOUCH_PAD7_DRV : R/W ;bitpos:[30:29] ;default: 2'd2 ; */
/*description: DRV*/
#define RTC_IO_TOUCH_PAD7_DRV  0x00000003
#define RTC_IO_TOUCH_PAD7_DRV_M  ((RTC_IO_TOUCH_PAD7_DRV_V)<<(RTC_IO_TOUCH_PAD7_DRV_S))
#define RTC_IO_TOUCH_PAD7_DRV_V  0x3
#define RTC_IO_TOUCH_PAD7_DRV_S  29
/* RTC_IO_TOUCH_PAD7_RDE : R/W ;bitpos:[28] ;default: 1'd0 ; */
/*description: RDE*/
#define RTC_IO_TOUCH_PAD7_RDE  (BIT(28))
#define RTC_IO_TOUCH_PAD7_RDE_M  (BIT(28))
#define RTC_IO_TOUCH_PAD7_RDE_V  0x1
#define RTC_IO_TOUCH_PAD7_RDE_S  28
/* RTC_IO_TOUCH_PAD7_RUE : R/W ;bitpos:[27] ;default: 1'd0 ; */
/*description: RUE*/
#define RTC_IO_TOUCH_PAD7_RUE  (BIT(27))
#define RTC_IO_TOUCH_PAD7_RUE_M  (BIT(27))
#define RTC_IO_TOUCH_PAD7_RUE_V  0x1
#define RTC_IO_TOUCH_PAD7_RUE_S  27
/* RTC_IO_TOUCH_PAD7_DAC : R/W ;bitpos:[25:23] ;default: 3'h4 ; */
/*description: TOUCH_DAC*/
#define RTC_IO_TOUCH_PAD7_DAC  0x00000007
#define RTC_IO_TOUCH_PAD7_DAC_M  ((RTC_IO_TOUCH_PAD7_DAC_V)<<(RTC_IO_TOUCH_PAD7_DAC_S))
#define RTC_IO_TOUCH_PAD7_DAC_V  0x7
#define RTC_IO_TOUCH_PAD7_DAC_S  23
/* RTC_IO_TOUCH_PAD7_START : R/W ;bitpos:[22] ;default: 1'd0 ; */
/*description: TOUCH_START*/
#define RTC_IO_TOUCH_PAD7_START  (BIT(22))
#define RTC_IO_TOUCH_PAD7_START_M  (BIT(22))
#define RTC_IO_TOUCH_PAD7_START_V  0x1
#define RTC_IO_TOUCH_PAD7_START_S  22
/* RTC_IO_TOUCH_PAD7_TIE_OPT : R/W ;bitpos:[21] ;default: 1'd0 ; */
/*description: TOUCH_TIE_OPT*/
#define RTC_IO_TOUCH_PAD7_TIE_OPT  (BIT(21))
#define RTC_IO_TOUCH_PAD7_TIE_OPT_M  (BIT(21))
#define RTC_IO_TOUCH_PAD7_TIE_OPT_V  0x1
#define RTC_IO_TOUCH_PAD7_TIE_OPT_S  21
/* RTC_IO_TOUCH_PAD7_XPD : R/W ;bitpos:[20] ;default: 1'd0 ; */
/*description: TOUCH_XPD*/
#define RTC_IO_TOUCH_PAD7_XPD  (BIT(20))
#define RTC_IO_TOUCH_PAD7_XPD_M  (BIT(20))
#define RTC_IO_TOUCH_PAD7_XPD_V  0x1
#define RTC_IO_TOUCH_PAD7_XPD_S  20
/* RTC_IO_TOUCH_PAD7_MUX_SEL : R/W ;bitpos:[19] ;default: 1'd0 ; */
/*description: 1: use RTC GPIO 0: use digital GPIO*/
#define RTC_IO_TOUCH_PAD7_MUX_SEL  (BIT(19))
#define RTC_IO_TOUCH_PAD7_MUX_SEL_M  (BIT(19))
#define RTC_IO_TOUCH_PAD7_MUX_SEL_V  0x1
#define RTC_IO_TOUCH_PAD7_MUX_SEL_S  19
/* RTC_IO_TOUCH_PAD7_FUN_SEL : R/W ;bitpos:[18:17] ;default: 2'd0 ; */
/*description: function sel*/
#define RTC_IO_TOUCH_PAD7_FUN_SEL  0x00000003
#define RTC_IO_TOUCH_PAD7_FUN_SEL_M  ((RTC_IO_TOUCH_PAD7_FUN_SEL_V)<<(RTC_IO_TOUCH_PAD7_FUN_SEL_S))
#define RTC_IO_TOUCH_PAD7_FUN_SEL_V  0x3
#define RTC_IO_TOUCH_PAD7_FUN_SEL_S  17
/* RTC_IO_TOUCH_PAD7_SLP_SEL : R/W ;bitpos:[16] ;default: 1'd0 ; */
/*description: 1: enable sleep mode during sleep 0: no sleep mode*/
#define RTC_IO_TOUCH_PAD7_SLP_SEL  (BIT(16))
#define RTC_IO_TOUCH_PAD7_SLP_SEL_M  (BIT(16))
#define RTC_IO_TOUCH_PAD7_SLP_SEL_V  0x1
#define RTC_IO_TOUCH_PAD7_SLP_SEL_S  16
/* RTC_IO_TOUCH_PAD7_SLP_IE : R/W ;bitpos:[15] ;default: 1'd0 ; */
/*description: input enable in sleep mode*/
#define RTC_IO_TOUCH_PAD7_SLP_IE  (BIT(15))
#define RTC_IO_TOUCH_PAD7_SLP_IE_M  (BIT(15))
#define RTC_IO_TOUCH_PAD7_SLP_IE_V  0x1
#define RTC_IO_TOUCH_PAD7_SLP_IE_S  15
/* RTC_IO_TOUCH_PAD7_SLP_OE : R/W ;bitpos:[14] ;default: 1'd0 ; */
/*description: output enable in sleep mode*/
#define RTC_IO_TOUCH_PAD7_SLP_OE  (BIT(14))
#define RTC_IO_TOUCH_PAD7_SLP_OE_M  (BIT(14))
#define RTC_IO_TOUCH_PAD7_SLP_OE_V  0x1
#define RTC_IO_TOUCH_PAD7_SLP_OE_S  14
/* RTC_IO_TOUCH_PAD7_FUN_IE : R/W ;bitpos:[13] ;default: 1'd0 ; */
/*description: input enable in work mode*/
#define RTC_IO_TOUCH_PAD7_FUN_IE  (BIT(13))
#define RTC_IO_TOUCH_PAD7_FUN_IE_M  (BIT(13))
#define RTC_IO_TOUCH_PAD7_FUN_IE_V  0x1
#define RTC_IO_TOUCH_PAD7_FUN_IE_S  13
/* RTC_IO_TOUCH_PAD7_TO_GPIO : R/W ;bitpos:[12] ;default: 1'd0 ; */
/*description: */
#define RTC_IO_TOUCH_PAD7_TO_GPIO  (BIT(12))
#define RTC_IO_TOUCH_PAD7_TO_GPIO_M  (BIT(12))
#define RTC_IO_TOUCH_PAD7_TO_GPIO_V  0x1
#define RTC_IO_TOUCH_PAD7_TO_GPIO_S  12

#define RTC_IO_TOUCH_PAD8_REG          (DR_REG_RTCIO_BASE + 0xb4)
/* RTC_IO_TOUCH_PAD8_DAC : R/W ;bitpos:[25:23] ;default: 3'h4 ; */
/*description: TOUCH_DAC*/
#define RTC_IO_TOUCH_PAD8_DAC  0x00000007
#define RTC_IO_TOUCH_PAD8_DAC_M  ((RTC_IO_TOUCH_PAD8_DAC_V)<<(RTC_IO_TOUCH_PAD8_DAC_S))
#define RTC_IO_TOUCH_PAD8_DAC_V  0x7
#define RTC_IO_TOUCH_PAD8_DAC_S  23
/* RTC_IO_TOUCH_PAD8_START : R/W ;bitpos:[22] ;default: 1'd0 ; */
/*description: TOUCH_START*/
#define RTC_IO_TOUCH_PAD8_START  (BIT(22))
#define RTC_IO_TOUCH_PAD8_START_M  (BIT(22))
#define RTC_IO_TOUCH_PAD8_START_V  0x1
#define RTC_IO_TOUCH_PAD8_START_S  22
/* RTC_IO_TOUCH_PAD8_TIE_OPT : R/W ;bitpos:[21] ;default: 1'd0 ; */
/*description: TOUCH_TIE_OPT*/
#define RTC_IO_TOUCH_PAD8_TIE_OPT  (BIT(21))
#define RTC_IO_TOUCH_PAD8_TIE_OPT_M  (BIT(21))
#define RTC_IO_TOUCH_PAD8_TIE_OPT_V  0x1
#define RTC_IO_TOUCH_PAD8_TIE_OPT_S  21
/* RTC_IO_TOUCH_PAD8_XPD : R/W ;bitpos:[20] ;default: 1'd0 ; */
/*description: TOUCH_XPD*/
#define RTC_IO_TOUCH_PAD8_XPD  (BIT(20))
#define RTC_IO_TOUCH_PAD8_XPD_M  (BIT(20))
#define RTC_IO_TOUCH_PAD8_XPD_V  0x1
#define RTC_IO_TOUCH_PAD8_XPD_S  20
/* RTC_IO_TOUCH_PAD8_TO_GPIO : R/W ;bitpos:[19] ;default: 1'd0 ; */
/*description: */
#define RTC_IO_TOUCH_PAD8_TO_GPIO  (BIT(19))
#define RTC_IO_TOUCH_PAD8_TO_GPIO_M  (BIT(19))
#define RTC_IO_TOUCH_PAD8_TO_GPIO_V  0x1
#define RTC_IO_TOUCH_PAD8_TO_GPIO_S  19

#define RTC_IO_TOUCH_PAD9_REG          (DR_REG_RTCIO_BASE + 0xb8)
/* RTC_IO_TOUCH_PAD9_DAC : R/W ;bitpos:[25:23] ;default: 3'h4 ; */
/*description: TOUCH_DAC*/
#define RTC_IO_TOUCH_PAD9_DAC  0x00000007
#define RTC_IO_TOUCH_PAD9_DAC_M  ((RTC_IO_TOUCH_PAD9_DAC_V)<<(RTC_IO_TOUCH_PAD9_DAC_S))
#define RTC_IO_TOUCH_PAD9_DAC_V  0x7
#define RTC_IO_TOUCH_PAD9_DAC_S  23
/* RTC_IO_TOUCH_PAD9_START : R/W ;bitpos:[22] ;default: 1'd0 ; */
/*description: TOUCH_START*/
#define RTC_IO_TOUCH_PAD9_START  (BIT(22))
#define RTC_IO_TOUCH_PAD9_START_M  (BIT(22))
#define RTC_IO_TOUCH_PAD9_START_V  0x1
#define RTC_IO_TOUCH_PAD9_START_S  22
/* RTC_IO_TOUCH_PAD9_TIE_OPT : R/W ;bitpos:[21] ;default: 1'd0 ; */
/*description: TOUCH_TIE_OPT*/
#define RTC_IO_TOUCH_PAD9_TIE_OPT  (BIT(21))
#define RTC_IO_TOUCH_PAD9_TIE_OPT_M  (BIT(21))
#define RTC_IO_TOUCH_PAD9_TIE_OPT_V  0x1
#define RTC_IO_TOUCH_PAD9_TIE_OPT_S  21
/* RTC_IO_TOUCH_PAD9_XPD : R/W ;bitpos:[20] ;default: 1'd0 ; */
/*description: TOUCH_XPD*/
#define RTC_IO_TOUCH_PAD9_XPD  (BIT(20))
#define RTC_IO_TOUCH_PAD9_XPD_M  (BIT(20))
#define RTC_IO_TOUCH_PAD9_XPD_V  0x1
#define RTC_IO_TOUCH_PAD9_XPD_S  20
/* RTC_IO_TOUCH_PAD9_TO_GPIO : R/W ;bitpos:[19] ;default: 1'd0 ; */
/*description: */
#define RTC_IO_TOUCH_PAD9_TO_GPIO  (BIT(19))
#define RTC_IO_TOUCH_PAD9_TO_GPIO_M  (BIT(19))
#define RTC_IO_TOUCH_PAD9_TO_GPIO_V  0x1
#define RTC_IO_TOUCH_PAD9_TO_GPIO_S  19

#define RTC_IO_EXT_WAKEUP0_REG          (DR_REG_RTCIO_BASE + 0xbc)
/* RTC_IO_EXT_WAKEUP0_SEL : R/W ;bitpos:[31:27] ;default: 5'd0 ; */
/*description: */
#define RTC_IO_EXT_WAKEUP0_SEL  0x0000001F
#define RTC_IO_EXT_WAKEUP0_SEL_M  ((RTC_IO_EXT_WAKEUP0_SEL_V)<<(RTC_IO_EXT_WAKEUP0_SEL_S))
#define RTC_IO_EXT_WAKEUP0_SEL_V  0x1F
#define RTC_IO_EXT_WAKEUP0_SEL_S  27

#define RTC_IO_XTL_EXT_CTR_REG          (DR_REG_RTCIO_BASE + 0xc0)
/* RTC_IO_XTL_EXT_CTR_SEL : R/W ;bitpos:[31:27] ;default: 5'd0 ; */
/*description: select RTC GPIO 0 ~ 17 to control XTAL*/
#define RTC_IO_XTL_EXT_CTR_SEL  0x0000001F
#define RTC_IO_XTL_EXT_CTR_SEL_M  ((RTC_IO_XTL_EXT_CTR_SEL_V)<<(RTC_IO_XTL_EXT_CTR_SEL_S))
#define RTC_IO_XTL_EXT_CTR_SEL_V  0x1F
#define RTC_IO_XTL_EXT_CTR_SEL_S  27

#define RTC_IO_SAR_I2C_IO_REG          (DR_REG_RTCIO_BASE + 0xc4)
/* RTC_IO_SAR_I2C_SDA_SEL : R/W ;bitpos:[31:30] ;default: 2'd0 ; */
/*description: */
#define RTC_IO_SAR_I2C_SDA_SEL  0x00000003
#define RTC_IO_SAR_I2C_SDA_SEL_M  ((RTC_IO_SAR_I2C_SDA_SEL_V)<<(RTC_IO_SAR_I2C_SDA_SEL_S))
#define RTC_IO_SAR_I2C_SDA_SEL_V  0x3
#define RTC_IO_SAR_I2C_SDA_SEL_S  30
/* RTC_IO_SAR_I2C_SCL_SEL : R/W ;bitpos:[29:28] ;default: 2'd0 ; */
/*description: */
#define RTC_IO_SAR_I2C_SCL_SEL  0x00000003
#define RTC_IO_SAR_I2C_SCL_SEL_M  ((RTC_IO_SAR_I2C_SCL_SEL_V)<<(RTC_IO_SAR_I2C_SCL_SEL_S))
#define RTC_IO_SAR_I2C_SCL_SEL_V  0x3
#define RTC_IO_SAR_I2C_SCL_SEL_S  28
/* RTC_IO_SAR_DEBUG_BIT_SEL : R/W ;bitpos:[27:23] ;default: 5'h0 ; */
/*description: */
#define RTC_IO_SAR_DEBUG_BIT_SEL  0x0000001F
#define RTC_IO_SAR_DEBUG_BIT_SEL_M  ((RTC_IO_SAR_DEBUG_BIT_SEL_V)<<(RTC_IO_SAR_DEBUG_BIT_SEL_S))
#define RTC_IO_SAR_DEBUG_BIT_SEL_V  0x1F
#define RTC_IO_SAR_DEBUG_BIT_SEL_S  23

#define RTC_IO_DATE_REG          (DR_REG_RTCIO_BASE + 0xc8)
/* RTC_IO_IO_DATE : R/W ;bitpos:[27:0] ;default: 28'h1611300 ; */
/*description: */
#define RTC_IO_IO_DATE  0x0FFFFFFF
#define RTC_IO_IO_DATE_M  ((RTC_IO_IO_DATE_V)<<(RTC_IO_IO_DATE_S))
#define RTC_IO_IO_DATE_V  0xFFFFFFF
#define RTC_IO_IO_DATE_S  0
#define RTC_IO_RTC_IO_DATE_VERSION 0x1611300

#ifdef __cplusplus
}
#endif



#endif /*_SOC_RTC_IO_REG_H_ */


