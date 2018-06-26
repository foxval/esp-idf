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
#ifndef _SOC_SENSITIVE_REG_H_
#define _SOC_SENSITIVE_REG_H_


#ifdef __cplusplus
extern "C" {
#endif
#include "soc.h"
#define DPORT_PMS_SDIO_0_REG          (DR_REG_SENSITIVE_BASE + 0x000)
/* DPORT_PMS_SDIO_DISABLE : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: */
#define DPORT_PMS_SDIO_DISABLE  (BIT(0))
#define DPORT_PMS_SDIO_DISABLE_M  (BIT(0))
#define DPORT_PMS_SDIO_DISABLE_V  0x1
#define DPORT_PMS_SDIO_DISABLE_S  0

#define DPORT_PMS_MAC_DUMP_0_REG          (DR_REG_SENSITIVE_BASE + 0x004)
/* DPORT_PMS_MAC_DUMP_CONNECT : R/W ;bitpos:[11:0] ;default: 12'b000011100100 ; */
/*description: */
#define DPORT_PMS_MAC_DUMP_CONNECT  0x00000FFF
#define DPORT_PMS_MAC_DUMP_CONNECT_M  ((DPORT_PMS_MAC_DUMP_CONNECT_V)<<(DPORT_PMS_MAC_DUMP_CONNECT_S))
#define DPORT_PMS_MAC_DUMP_CONNECT_V  0xFFF
#define DPORT_PMS_MAC_DUMP_CONNECT_S  0

#define DPORT_PMS_PRO_IRAM0_0_REG          (DR_REG_SENSITIVE_BASE + 0x008)
/* DPORT_PMS_PRO_IRAM0_RTCFAST_H_W : R/W ;bitpos:[16] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_IRAM0_RTCFAST_H_W  (BIT(16))
#define DPORT_PMS_PRO_IRAM0_RTCFAST_H_W_M  (BIT(16))
#define DPORT_PMS_PRO_IRAM0_RTCFAST_H_W_V  0x1
#define DPORT_PMS_PRO_IRAM0_RTCFAST_H_W_S  16
/* DPORT_PMS_PRO_IRAM0_RTCFAST_H_R : R/W ;bitpos:[15] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_IRAM0_RTCFAST_H_R  (BIT(15))
#define DPORT_PMS_PRO_IRAM0_RTCFAST_H_R_M  (BIT(15))
#define DPORT_PMS_PRO_IRAM0_RTCFAST_H_R_V  0x1
#define DPORT_PMS_PRO_IRAM0_RTCFAST_H_R_S  15
/* DPORT_PMS_PRO_IRAM0_RTCFAST_H_F : R/W ;bitpos:[14] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_IRAM0_RTCFAST_H_F  (BIT(14))
#define DPORT_PMS_PRO_IRAM0_RTCFAST_H_F_M  (BIT(14))
#define DPORT_PMS_PRO_IRAM0_RTCFAST_H_F_V  0x1
#define DPORT_PMS_PRO_IRAM0_RTCFAST_H_F_S  14
/* DPORT_PMS_PRO_IRAM0_RTCFAST_L_W : R/W ;bitpos:[13] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_IRAM0_RTCFAST_L_W  (BIT(13))
#define DPORT_PMS_PRO_IRAM0_RTCFAST_L_W_M  (BIT(13))
#define DPORT_PMS_PRO_IRAM0_RTCFAST_L_W_V  0x1
#define DPORT_PMS_PRO_IRAM0_RTCFAST_L_W_S  13
/* DPORT_PMS_PRO_IRAM0_RTCFAST_L_R : R/W ;bitpos:[12] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_IRAM0_RTCFAST_L_R  (BIT(12))
#define DPORT_PMS_PRO_IRAM0_RTCFAST_L_R_M  (BIT(12))
#define DPORT_PMS_PRO_IRAM0_RTCFAST_L_R_V  0x1
#define DPORT_PMS_PRO_IRAM0_RTCFAST_L_R_S  12
/* DPORT_PMS_PRO_IRAM0_RTCFAST_L_F : R/W ;bitpos:[11] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_IRAM0_RTCFAST_L_F  (BIT(11))
#define DPORT_PMS_PRO_IRAM0_RTCFAST_L_F_M  (BIT(11))
#define DPORT_PMS_PRO_IRAM0_RTCFAST_L_F_V  0x1
#define DPORT_PMS_PRO_IRAM0_RTCFAST_L_F_S  11
/* DPORT_PMS_PRO_IRAM0_RTCFAST_SPLTADDR : R/W ;bitpos:[10:0] ;default: 11'b0 ; */
/*description: */
#define DPORT_PMS_PRO_IRAM0_RTCFAST_SPLTADDR  0x000007FF
#define DPORT_PMS_PRO_IRAM0_RTCFAST_SPLTADDR_M  ((DPORT_PMS_PRO_IRAM0_RTCFAST_SPLTADDR_V)<<(DPORT_PMS_PRO_IRAM0_RTCFAST_SPLTADDR_S))
#define DPORT_PMS_PRO_IRAM0_RTCFAST_SPLTADDR_V  0x7FF
#define DPORT_PMS_PRO_IRAM0_RTCFAST_SPLTADDR_S  0

#define DPORT_PMS_PRO_IRAM0_1_REG          (DR_REG_SENSITIVE_BASE + 0x00C)
/* DPORT_PMS_PRO_IRAM0_SRAM_2_W : R/W ;bitpos:[8] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_IRAM0_SRAM_2_W  (BIT(8))
#define DPORT_PMS_PRO_IRAM0_SRAM_2_W_M  (BIT(8))
#define DPORT_PMS_PRO_IRAM0_SRAM_2_W_V  0x1
#define DPORT_PMS_PRO_IRAM0_SRAM_2_W_S  8
/* DPORT_PMS_PRO_IRAM0_SRAM_2_R : R/W ;bitpos:[7] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_IRAM0_SRAM_2_R  (BIT(7))
#define DPORT_PMS_PRO_IRAM0_SRAM_2_R_M  (BIT(7))
#define DPORT_PMS_PRO_IRAM0_SRAM_2_R_V  0x1
#define DPORT_PMS_PRO_IRAM0_SRAM_2_R_S  7
/* DPORT_PMS_PRO_IRAM0_SRAM_2_F : R/W ;bitpos:[6] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_IRAM0_SRAM_2_F  (BIT(6))
#define DPORT_PMS_PRO_IRAM0_SRAM_2_F_M  (BIT(6))
#define DPORT_PMS_PRO_IRAM0_SRAM_2_F_V  0x1
#define DPORT_PMS_PRO_IRAM0_SRAM_2_F_S  6
/* DPORT_PMS_PRO_IRAM0_SRAM_1_W : R/W ;bitpos:[5] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_IRAM0_SRAM_1_W  (BIT(5))
#define DPORT_PMS_PRO_IRAM0_SRAM_1_W_M  (BIT(5))
#define DPORT_PMS_PRO_IRAM0_SRAM_1_W_V  0x1
#define DPORT_PMS_PRO_IRAM0_SRAM_1_W_S  5
/* DPORT_PMS_PRO_IRAM0_SRAM_1_R : R/W ;bitpos:[4] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_IRAM0_SRAM_1_R  (BIT(4))
#define DPORT_PMS_PRO_IRAM0_SRAM_1_R_M  (BIT(4))
#define DPORT_PMS_PRO_IRAM0_SRAM_1_R_V  0x1
#define DPORT_PMS_PRO_IRAM0_SRAM_1_R_S  4
/* DPORT_PMS_PRO_IRAM0_SRAM_1_F : R/W ;bitpos:[3] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_IRAM0_SRAM_1_F  (BIT(3))
#define DPORT_PMS_PRO_IRAM0_SRAM_1_F_M  (BIT(3))
#define DPORT_PMS_PRO_IRAM0_SRAM_1_F_V  0x1
#define DPORT_PMS_PRO_IRAM0_SRAM_1_F_S  3
/* DPORT_PMS_PRO_IRAM0_SRAM_0_W : R/W ;bitpos:[2] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_IRAM0_SRAM_0_W  (BIT(2))
#define DPORT_PMS_PRO_IRAM0_SRAM_0_W_M  (BIT(2))
#define DPORT_PMS_PRO_IRAM0_SRAM_0_W_V  0x1
#define DPORT_PMS_PRO_IRAM0_SRAM_0_W_S  2
/* DPORT_PMS_PRO_IRAM0_SRAM_0_R : R/W ;bitpos:[1] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_IRAM0_SRAM_0_R  (BIT(1))
#define DPORT_PMS_PRO_IRAM0_SRAM_0_R_M  (BIT(1))
#define DPORT_PMS_PRO_IRAM0_SRAM_0_R_V  0x1
#define DPORT_PMS_PRO_IRAM0_SRAM_0_R_S  1
/* DPORT_PMS_PRO_IRAM0_SRAM_0_F : R/W ;bitpos:[0] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_IRAM0_SRAM_0_F  (BIT(0))
#define DPORT_PMS_PRO_IRAM0_SRAM_0_F_M  (BIT(0))
#define DPORT_PMS_PRO_IRAM0_SRAM_0_F_V  0x1
#define DPORT_PMS_PRO_IRAM0_SRAM_0_F_S  0

#define DPORT_PMS_PRO_IRAM0_2_REG          (DR_REG_SENSITIVE_BASE + 0x010)
/* DPORT_PMS_PRO_IRAM0_SRAM_3_H_W : R/W ;bitpos:[23] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_IRAM0_SRAM_3_H_W  (BIT(23))
#define DPORT_PMS_PRO_IRAM0_SRAM_3_H_W_M  (BIT(23))
#define DPORT_PMS_PRO_IRAM0_SRAM_3_H_W_V  0x1
#define DPORT_PMS_PRO_IRAM0_SRAM_3_H_W_S  23
/* DPORT_PMS_PRO_IRAM0_SRAM_3_H_R : R/W ;bitpos:[22] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_IRAM0_SRAM_3_H_R  (BIT(22))
#define DPORT_PMS_PRO_IRAM0_SRAM_3_H_R_M  (BIT(22))
#define DPORT_PMS_PRO_IRAM0_SRAM_3_H_R_V  0x1
#define DPORT_PMS_PRO_IRAM0_SRAM_3_H_R_S  22
/* DPORT_PMS_PRO_IRAM0_SRAM_3_H_F : R/W ;bitpos:[21] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_IRAM0_SRAM_3_H_F  (BIT(21))
#define DPORT_PMS_PRO_IRAM0_SRAM_3_H_F_M  (BIT(21))
#define DPORT_PMS_PRO_IRAM0_SRAM_3_H_F_V  0x1
#define DPORT_PMS_PRO_IRAM0_SRAM_3_H_F_S  21
/* DPORT_PMS_PRO_IRAM0_SRAM_3_L_W : R/W ;bitpos:[20] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_IRAM0_SRAM_3_L_W  (BIT(20))
#define DPORT_PMS_PRO_IRAM0_SRAM_3_L_W_M  (BIT(20))
#define DPORT_PMS_PRO_IRAM0_SRAM_3_L_W_V  0x1
#define DPORT_PMS_PRO_IRAM0_SRAM_3_L_W_S  20
/* DPORT_PMS_PRO_IRAM0_SRAM_3_L_R : R/W ;bitpos:[19] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_IRAM0_SRAM_3_L_R  (BIT(19))
#define DPORT_PMS_PRO_IRAM0_SRAM_3_L_R_M  (BIT(19))
#define DPORT_PMS_PRO_IRAM0_SRAM_3_L_R_V  0x1
#define DPORT_PMS_PRO_IRAM0_SRAM_3_L_R_S  19
/* DPORT_PMS_PRO_IRAM0_SRAM_3_L_F : R/W ;bitpos:[18] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_IRAM0_SRAM_3_L_F  (BIT(18))
#define DPORT_PMS_PRO_IRAM0_SRAM_3_L_F_M  (BIT(18))
#define DPORT_PMS_PRO_IRAM0_SRAM_3_L_F_V  0x1
#define DPORT_PMS_PRO_IRAM0_SRAM_3_L_F_S  18
/* DPORT_PMS_PRO_IRAM0_SRAM_3_SPLTADDR : R/W ;bitpos:[17:0] ;default: 18'b0 ; */
/*description: */
#define DPORT_PMS_PRO_IRAM0_SRAM_3_SPLTADDR  0x0003FFFF
#define DPORT_PMS_PRO_IRAM0_SRAM_3_SPLTADDR_M  ((DPORT_PMS_PRO_IRAM0_SRAM_3_SPLTADDR_V)<<(DPORT_PMS_PRO_IRAM0_SRAM_3_SPLTADDR_S))
#define DPORT_PMS_PRO_IRAM0_SRAM_3_SPLTADDR_V  0x3FFFF
#define DPORT_PMS_PRO_IRAM0_SRAM_3_SPLTADDR_S  0

#define DPORT_PMS_PRO_IRAM0_3_REG          (DR_REG_SENSITIVE_BASE + 0x014)
/* DPORT_PMS_PRO_IRAM0_ILG_INTR : RO ;bitpos:[2] ;default: 1'b0 ; */
/*description: */
#define DPORT_PMS_PRO_IRAM0_ILG_INTR  (BIT(2))
#define DPORT_PMS_PRO_IRAM0_ILG_INTR_M  (BIT(2))
#define DPORT_PMS_PRO_IRAM0_ILG_INTR_V  0x1
#define DPORT_PMS_PRO_IRAM0_ILG_INTR_S  2
/* DPORT_PMS_PRO_IRAM0_ILG_EN : R/W ;bitpos:[1] ;default: 1'b0 ; */
/*description: */
#define DPORT_PMS_PRO_IRAM0_ILG_EN  (BIT(1))
#define DPORT_PMS_PRO_IRAM0_ILG_EN_M  (BIT(1))
#define DPORT_PMS_PRO_IRAM0_ILG_EN_V  0x1
#define DPORT_PMS_PRO_IRAM0_ILG_EN_S  1
/* DPORT_PMS_PRO_IRAM0_ILG_CLR : R/W ;bitpos:[0] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_IRAM0_ILG_CLR  (BIT(0))
#define DPORT_PMS_PRO_IRAM0_ILG_CLR_M  (BIT(0))
#define DPORT_PMS_PRO_IRAM0_ILG_CLR_V  0x1
#define DPORT_PMS_PRO_IRAM0_ILG_CLR_S  0

#define DPORT_PMS_PRO_IRAM0_4_REG          (DR_REG_SENSITIVE_BASE + 0x018)
/* DPORT_PMS_PRO_IRAM0_ILG_ST : RO ;bitpos:[21:0] ;default: 22'b0 ; */
/*description: */
#define DPORT_PMS_PRO_IRAM0_ILG_ST  0x003FFFFF
#define DPORT_PMS_PRO_IRAM0_ILG_ST_M  ((DPORT_PMS_PRO_IRAM0_ILG_ST_V)<<(DPORT_PMS_PRO_IRAM0_ILG_ST_S))
#define DPORT_PMS_PRO_IRAM0_ILG_ST_V  0x3FFFFF
#define DPORT_PMS_PRO_IRAM0_ILG_ST_S  0

#define DPORT_PMS_PRO_DRAM0_0_REG          (DR_REG_SENSITIVE_BASE + 0x01C)
/* DPORT_PMS_PRO_DRAM0_RTCFAST_H_W : R/W ;bitpos:[14] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_DRAM0_RTCFAST_H_W  (BIT(14))
#define DPORT_PMS_PRO_DRAM0_RTCFAST_H_W_M  (BIT(14))
#define DPORT_PMS_PRO_DRAM0_RTCFAST_H_W_V  0x1
#define DPORT_PMS_PRO_DRAM0_RTCFAST_H_W_S  14
/* DPORT_PMS_PRO_DRAM0_RTCFAST_H_R : R/W ;bitpos:[13] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_DRAM0_RTCFAST_H_R  (BIT(13))
#define DPORT_PMS_PRO_DRAM0_RTCFAST_H_R_M  (BIT(13))
#define DPORT_PMS_PRO_DRAM0_RTCFAST_H_R_V  0x1
#define DPORT_PMS_PRO_DRAM0_RTCFAST_H_R_S  13
/* DPORT_PMS_PRO_DRAM0_RTCFAST_L_W : R/W ;bitpos:[12] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_DRAM0_RTCFAST_L_W  (BIT(12))
#define DPORT_PMS_PRO_DRAM0_RTCFAST_L_W_M  (BIT(12))
#define DPORT_PMS_PRO_DRAM0_RTCFAST_L_W_V  0x1
#define DPORT_PMS_PRO_DRAM0_RTCFAST_L_W_S  12
/* DPORT_PMS_PRO_DRAM0_RTCFAST_L_R : R/W ;bitpos:[11] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_DRAM0_RTCFAST_L_R  (BIT(11))
#define DPORT_PMS_PRO_DRAM0_RTCFAST_L_R_M  (BIT(11))
#define DPORT_PMS_PRO_DRAM0_RTCFAST_L_R_V  0x1
#define DPORT_PMS_PRO_DRAM0_RTCFAST_L_R_S  11
/* DPORT_PMS_PRO_DRAM0_RTCFAST_SPLTADDR : R/W ;bitpos:[10:0] ;default: 11'b0 ; */
/*description: */
#define DPORT_PMS_PRO_DRAM0_RTCFAST_SPLTADDR  0x000007FF
#define DPORT_PMS_PRO_DRAM0_RTCFAST_SPLTADDR_M  ((DPORT_PMS_PRO_DRAM0_RTCFAST_SPLTADDR_V)<<(DPORT_PMS_PRO_DRAM0_RTCFAST_SPLTADDR_S))
#define DPORT_PMS_PRO_DRAM0_RTCFAST_SPLTADDR_V  0x7FF
#define DPORT_PMS_PRO_DRAM0_RTCFAST_SPLTADDR_S  0

#define DPORT_PMS_PRO_DRAM0_1_REG          (DR_REG_SENSITIVE_BASE + 0x020)
/* DPORT_PMS_PRO_DRAM0_SRAM_3_H_W : R/W ;bitpos:[26] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_DRAM0_SRAM_3_H_W  (BIT(26))
#define DPORT_PMS_PRO_DRAM0_SRAM_3_H_W_M  (BIT(26))
#define DPORT_PMS_PRO_DRAM0_SRAM_3_H_W_V  0x1
#define DPORT_PMS_PRO_DRAM0_SRAM_3_H_W_S  26
/* DPORT_PMS_PRO_DRAM0_SRAM_3_H_R : R/W ;bitpos:[25] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_DRAM0_SRAM_3_H_R  (BIT(25))
#define DPORT_PMS_PRO_DRAM0_SRAM_3_H_R_M  (BIT(25))
#define DPORT_PMS_PRO_DRAM0_SRAM_3_H_R_V  0x1
#define DPORT_PMS_PRO_DRAM0_SRAM_3_H_R_S  25
/* DPORT_PMS_PRO_DRAM0_SRAM_3_L_W : R/W ;bitpos:[24] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_DRAM0_SRAM_3_L_W  (BIT(24))
#define DPORT_PMS_PRO_DRAM0_SRAM_3_L_W_M  (BIT(24))
#define DPORT_PMS_PRO_DRAM0_SRAM_3_L_W_V  0x1
#define DPORT_PMS_PRO_DRAM0_SRAM_3_L_W_S  24
/* DPORT_PMS_PRO_DRAM0_SRAM_3_L_R : R/W ;bitpos:[23] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_DRAM0_SRAM_3_L_R  (BIT(23))
#define DPORT_PMS_PRO_DRAM0_SRAM_3_L_R_M  (BIT(23))
#define DPORT_PMS_PRO_DRAM0_SRAM_3_L_R_V  0x1
#define DPORT_PMS_PRO_DRAM0_SRAM_3_L_R_S  23
/* DPORT_PMS_PRO_DRAM0_SRAM_3_SPLTADDR : R/W ;bitpos:[22:6] ;default: 17'b0 ; */
/*description: */
#define DPORT_PMS_PRO_DRAM0_SRAM_3_SPLTADDR  0x0001FFFF
#define DPORT_PMS_PRO_DRAM0_SRAM_3_SPLTADDR_M  ((DPORT_PMS_PRO_DRAM0_SRAM_3_SPLTADDR_V)<<(DPORT_PMS_PRO_DRAM0_SRAM_3_SPLTADDR_S))
#define DPORT_PMS_PRO_DRAM0_SRAM_3_SPLTADDR_V  0x1FFFF
#define DPORT_PMS_PRO_DRAM0_SRAM_3_SPLTADDR_S  6
/* DPORT_PMS_PRO_DRAM0_SRAM_2_W : R/W ;bitpos:[5] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_DRAM0_SRAM_2_W  (BIT(5))
#define DPORT_PMS_PRO_DRAM0_SRAM_2_W_M  (BIT(5))
#define DPORT_PMS_PRO_DRAM0_SRAM_2_W_V  0x1
#define DPORT_PMS_PRO_DRAM0_SRAM_2_W_S  5
/* DPORT_PMS_PRO_DRAM0_SRAM_2_R : R/W ;bitpos:[4] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_DRAM0_SRAM_2_R  (BIT(4))
#define DPORT_PMS_PRO_DRAM0_SRAM_2_R_M  (BIT(4))
#define DPORT_PMS_PRO_DRAM0_SRAM_2_R_V  0x1
#define DPORT_PMS_PRO_DRAM0_SRAM_2_R_S  4
/* DPORT_PMS_PRO_DRAM0_SRAM_1_W : R/W ;bitpos:[3] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_DRAM0_SRAM_1_W  (BIT(3))
#define DPORT_PMS_PRO_DRAM0_SRAM_1_W_M  (BIT(3))
#define DPORT_PMS_PRO_DRAM0_SRAM_1_W_V  0x1
#define DPORT_PMS_PRO_DRAM0_SRAM_1_W_S  3
/* DPORT_PMS_PRO_DRAM0_SRAM_1_R : R/W ;bitpos:[2] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_DRAM0_SRAM_1_R  (BIT(2))
#define DPORT_PMS_PRO_DRAM0_SRAM_1_R_M  (BIT(2))
#define DPORT_PMS_PRO_DRAM0_SRAM_1_R_V  0x1
#define DPORT_PMS_PRO_DRAM0_SRAM_1_R_S  2
/* DPORT_PMS_PRO_DRAM0_SRAM_0_W : R/W ;bitpos:[1] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_DRAM0_SRAM_0_W  (BIT(1))
#define DPORT_PMS_PRO_DRAM0_SRAM_0_W_M  (BIT(1))
#define DPORT_PMS_PRO_DRAM0_SRAM_0_W_V  0x1
#define DPORT_PMS_PRO_DRAM0_SRAM_0_W_S  1
/* DPORT_PMS_PRO_DRAM0_SRAM_0_R : R/W ;bitpos:[0] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_DRAM0_SRAM_0_R  (BIT(0))
#define DPORT_PMS_PRO_DRAM0_SRAM_0_R_M  (BIT(0))
#define DPORT_PMS_PRO_DRAM0_SRAM_0_R_V  0x1
#define DPORT_PMS_PRO_DRAM0_SRAM_0_R_S  0

#define DPORT_PMS_PRO_DRAM0_2_REG          (DR_REG_SENSITIVE_BASE + 0x024)
/* DPORT_PMS_PRO_DRAM0_ILG_INTR : RO ;bitpos:[2] ;default: 1'b0 ; */
/*description: */
#define DPORT_PMS_PRO_DRAM0_ILG_INTR  (BIT(2))
#define DPORT_PMS_PRO_DRAM0_ILG_INTR_M  (BIT(2))
#define DPORT_PMS_PRO_DRAM0_ILG_INTR_V  0x1
#define DPORT_PMS_PRO_DRAM0_ILG_INTR_S  2
/* DPORT_PMS_PRO_DRAM0_ILG_EN : R/W ;bitpos:[1] ;default: 1'b0 ; */
/*description: */
#define DPORT_PMS_PRO_DRAM0_ILG_EN  (BIT(1))
#define DPORT_PMS_PRO_DRAM0_ILG_EN_M  (BIT(1))
#define DPORT_PMS_PRO_DRAM0_ILG_EN_V  0x1
#define DPORT_PMS_PRO_DRAM0_ILG_EN_S  1
/* DPORT_PMS_PRO_DRAM0_ILG_CLR : R/W ;bitpos:[0] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_DRAM0_ILG_CLR  (BIT(0))
#define DPORT_PMS_PRO_DRAM0_ILG_CLR_M  (BIT(0))
#define DPORT_PMS_PRO_DRAM0_ILG_CLR_V  0x1
#define DPORT_PMS_PRO_DRAM0_ILG_CLR_S  0

#define DPORT_PMS_PRO_DRAM0_3_REG          (DR_REG_SENSITIVE_BASE + 0x028)
/* DPORT_PMS_PRO_DRAM0_ILG_ST : RO ;bitpos:[22:0] ;default: 23'b0 ; */
/*description: */
#define DPORT_PMS_PRO_DRAM0_ILG_ST  0x007FFFFF
#define DPORT_PMS_PRO_DRAM0_ILG_ST_M  ((DPORT_PMS_PRO_DRAM0_ILG_ST_V)<<(DPORT_PMS_PRO_DRAM0_ILG_ST_S))
#define DPORT_PMS_PRO_DRAM0_ILG_ST_V  0x7FFFFF
#define DPORT_PMS_PRO_DRAM0_ILG_ST_S  0

#define DPORT_PMS_PRO_DPORT_0_REG          (DR_REG_SENSITIVE_BASE + 0x02C)
/* DPORT_PMS_PRO_DPORT_RTCSLOW_H_W : R/W ;bitpos:[14] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_DPORT_RTCSLOW_H_W  (BIT(14))
#define DPORT_PMS_PRO_DPORT_RTCSLOW_H_W_M  (BIT(14))
#define DPORT_PMS_PRO_DPORT_RTCSLOW_H_W_V  0x1
#define DPORT_PMS_PRO_DPORT_RTCSLOW_H_W_S  14
/* DPORT_PMS_PRO_DPORT_RTCSLOW_H_R : R/W ;bitpos:[13] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_DPORT_RTCSLOW_H_R  (BIT(13))
#define DPORT_PMS_PRO_DPORT_RTCSLOW_H_R_M  (BIT(13))
#define DPORT_PMS_PRO_DPORT_RTCSLOW_H_R_V  0x1
#define DPORT_PMS_PRO_DPORT_RTCSLOW_H_R_S  13
/* DPORT_PMS_PRO_DPORT_RTCSLOW_L_W : R/W ;bitpos:[12] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_DPORT_RTCSLOW_L_W  (BIT(12))
#define DPORT_PMS_PRO_DPORT_RTCSLOW_L_W_M  (BIT(12))
#define DPORT_PMS_PRO_DPORT_RTCSLOW_L_W_V  0x1
#define DPORT_PMS_PRO_DPORT_RTCSLOW_L_W_S  12
/* DPORT_PMS_PRO_DPORT_RTCSLOW_L_R : R/W ;bitpos:[11] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_DPORT_RTCSLOW_L_R  (BIT(11))
#define DPORT_PMS_PRO_DPORT_RTCSLOW_L_R_M  (BIT(11))
#define DPORT_PMS_PRO_DPORT_RTCSLOW_L_R_V  0x1
#define DPORT_PMS_PRO_DPORT_RTCSLOW_L_R_S  11
/* DPORT_PMS_PRO_DPORT_RTCSLOW_SPLTADDR : R/W ;bitpos:[10:0] ;default: 11'b0 ; */
/*description: */
#define DPORT_PMS_PRO_DPORT_RTCSLOW_SPLTADDR  0x000007FF
#define DPORT_PMS_PRO_DPORT_RTCSLOW_SPLTADDR_M  ((DPORT_PMS_PRO_DPORT_RTCSLOW_SPLTADDR_V)<<(DPORT_PMS_PRO_DPORT_RTCSLOW_SPLTADDR_S))
#define DPORT_PMS_PRO_DPORT_RTCSLOW_SPLTADDR_V  0x7FF
#define DPORT_PMS_PRO_DPORT_RTCSLOW_SPLTADDR_S  0

#define DPORT_PMS_PRO_DPORT_1_REG          (DR_REG_SENSITIVE_BASE + 0x030)
/* DPORT_PMS_PRO_DPORT_ILG_INTR : RO ;bitpos:[2] ;default: 1'b0 ; */
/*description: */
#define DPORT_PMS_PRO_DPORT_ILG_INTR  (BIT(2))
#define DPORT_PMS_PRO_DPORT_ILG_INTR_M  (BIT(2))
#define DPORT_PMS_PRO_DPORT_ILG_INTR_V  0x1
#define DPORT_PMS_PRO_DPORT_ILG_INTR_S  2
/* DPORT_PMS_PRO_DPORT_ILG_EN : R/W ;bitpos:[1] ;default: 1'b0 ; */
/*description: */
#define DPORT_PMS_PRO_DPORT_ILG_EN  (BIT(1))
#define DPORT_PMS_PRO_DPORT_ILG_EN_M  (BIT(1))
#define DPORT_PMS_PRO_DPORT_ILG_EN_V  0x1
#define DPORT_PMS_PRO_DPORT_ILG_EN_S  1
/* DPORT_PMS_PRO_DPORT_ILG_CLR : R/W ;bitpos:[0] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_DPORT_ILG_CLR  (BIT(0))
#define DPORT_PMS_PRO_DPORT_ILG_CLR_M  (BIT(0))
#define DPORT_PMS_PRO_DPORT_ILG_CLR_V  0x1
#define DPORT_PMS_PRO_DPORT_ILG_CLR_S  0

#define DPORT_PMS_PRO_DPORT_2_REG          (DR_REG_SENSITIVE_BASE + 0x034)
/* DPORT_PMS_PRO_DPORT_ILG_ST : RO ;bitpos:[22:0] ;default: 23'b0 ; */
/*description: */
#define DPORT_PMS_PRO_DPORT_ILG_ST  0x007FFFFF
#define DPORT_PMS_PRO_DPORT_ILG_ST_M  ((DPORT_PMS_PRO_DPORT_ILG_ST_V)<<(DPORT_PMS_PRO_DPORT_ILG_ST_S))
#define DPORT_PMS_PRO_DPORT_ILG_ST_V  0x7FFFFF
#define DPORT_PMS_PRO_DPORT_ILG_ST_S  0

#define DPORT_PMS_PRO_AHB_0_REG          (DR_REG_SENSITIVE_BASE + 0x038)
/* DPORT_PMS_PRO_AHB_RTCSLOW_0_H_W : R/W ;bitpos:[16] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_AHB_RTCSLOW_0_H_W  (BIT(16))
#define DPORT_PMS_PRO_AHB_RTCSLOW_0_H_W_M  (BIT(16))
#define DPORT_PMS_PRO_AHB_RTCSLOW_0_H_W_V  0x1
#define DPORT_PMS_PRO_AHB_RTCSLOW_0_H_W_S  16
/* DPORT_PMS_PRO_AHB_RTCSLOW_0_H_R : R/W ;bitpos:[15] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_AHB_RTCSLOW_0_H_R  (BIT(15))
#define DPORT_PMS_PRO_AHB_RTCSLOW_0_H_R_M  (BIT(15))
#define DPORT_PMS_PRO_AHB_RTCSLOW_0_H_R_V  0x1
#define DPORT_PMS_PRO_AHB_RTCSLOW_0_H_R_S  15
/* DPORT_PMS_PRO_AHB_RTCSLOW_0_H_F : R/W ;bitpos:[14] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_AHB_RTCSLOW_0_H_F  (BIT(14))
#define DPORT_PMS_PRO_AHB_RTCSLOW_0_H_F_M  (BIT(14))
#define DPORT_PMS_PRO_AHB_RTCSLOW_0_H_F_V  0x1
#define DPORT_PMS_PRO_AHB_RTCSLOW_0_H_F_S  14
/* DPORT_PMS_PRO_AHB_RTCSLOW_0_L_W : R/W ;bitpos:[13] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_AHB_RTCSLOW_0_L_W  (BIT(13))
#define DPORT_PMS_PRO_AHB_RTCSLOW_0_L_W_M  (BIT(13))
#define DPORT_PMS_PRO_AHB_RTCSLOW_0_L_W_V  0x1
#define DPORT_PMS_PRO_AHB_RTCSLOW_0_L_W_S  13
/* DPORT_PMS_PRO_AHB_RTCSLOW_0_L_R : R/W ;bitpos:[12] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_AHB_RTCSLOW_0_L_R  (BIT(12))
#define DPORT_PMS_PRO_AHB_RTCSLOW_0_L_R_M  (BIT(12))
#define DPORT_PMS_PRO_AHB_RTCSLOW_0_L_R_V  0x1
#define DPORT_PMS_PRO_AHB_RTCSLOW_0_L_R_S  12
/* DPORT_PMS_PRO_AHB_RTCSLOW_0_L_F : R/W ;bitpos:[11] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_AHB_RTCSLOW_0_L_F  (BIT(11))
#define DPORT_PMS_PRO_AHB_RTCSLOW_0_L_F_M  (BIT(11))
#define DPORT_PMS_PRO_AHB_RTCSLOW_0_L_F_V  0x1
#define DPORT_PMS_PRO_AHB_RTCSLOW_0_L_F_S  11
/* DPORT_PMS_PRO_AHB_RTCSLOW_0_SPLTADDR : R/W ;bitpos:[10:0] ;default: 11'b0 ; */
/*description: */
#define DPORT_PMS_PRO_AHB_RTCSLOW_0_SPLTADDR  0x000007FF
#define DPORT_PMS_PRO_AHB_RTCSLOW_0_SPLTADDR_M  ((DPORT_PMS_PRO_AHB_RTCSLOW_0_SPLTADDR_V)<<(DPORT_PMS_PRO_AHB_RTCSLOW_0_SPLTADDR_S))
#define DPORT_PMS_PRO_AHB_RTCSLOW_0_SPLTADDR_V  0x7FF
#define DPORT_PMS_PRO_AHB_RTCSLOW_0_SPLTADDR_S  0

#define DPORT_PMS_PRO_AHB_1_REG          (DR_REG_SENSITIVE_BASE + 0x03C)
/* DPORT_PMS_PRO_AHB_RTCSLOW_1_H_W : R/W ;bitpos:[16] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_AHB_RTCSLOW_1_H_W  (BIT(16))
#define DPORT_PMS_PRO_AHB_RTCSLOW_1_H_W_M  (BIT(16))
#define DPORT_PMS_PRO_AHB_RTCSLOW_1_H_W_V  0x1
#define DPORT_PMS_PRO_AHB_RTCSLOW_1_H_W_S  16
/* DPORT_PMS_PRO_AHB_RTCSLOW_1_H_R : R/W ;bitpos:[15] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_AHB_RTCSLOW_1_H_R  (BIT(15))
#define DPORT_PMS_PRO_AHB_RTCSLOW_1_H_R_M  (BIT(15))
#define DPORT_PMS_PRO_AHB_RTCSLOW_1_H_R_V  0x1
#define DPORT_PMS_PRO_AHB_RTCSLOW_1_H_R_S  15
/* DPORT_PMS_PRO_AHB_RTCSLOW_1_H_F : R/W ;bitpos:[14] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_AHB_RTCSLOW_1_H_F  (BIT(14))
#define DPORT_PMS_PRO_AHB_RTCSLOW_1_H_F_M  (BIT(14))
#define DPORT_PMS_PRO_AHB_RTCSLOW_1_H_F_V  0x1
#define DPORT_PMS_PRO_AHB_RTCSLOW_1_H_F_S  14
/* DPORT_PMS_PRO_AHB_RTCSLOW_1_L_W : R/W ;bitpos:[13] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_AHB_RTCSLOW_1_L_W  (BIT(13))
#define DPORT_PMS_PRO_AHB_RTCSLOW_1_L_W_M  (BIT(13))
#define DPORT_PMS_PRO_AHB_RTCSLOW_1_L_W_V  0x1
#define DPORT_PMS_PRO_AHB_RTCSLOW_1_L_W_S  13
/* DPORT_PMS_PRO_AHB_RTCSLOW_1_L_R : R/W ;bitpos:[12] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_AHB_RTCSLOW_1_L_R  (BIT(12))
#define DPORT_PMS_PRO_AHB_RTCSLOW_1_L_R_M  (BIT(12))
#define DPORT_PMS_PRO_AHB_RTCSLOW_1_L_R_V  0x1
#define DPORT_PMS_PRO_AHB_RTCSLOW_1_L_R_S  12
/* DPORT_PMS_PRO_AHB_RTCSLOW_1_L_F : R/W ;bitpos:[11] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_AHB_RTCSLOW_1_L_F  (BIT(11))
#define DPORT_PMS_PRO_AHB_RTCSLOW_1_L_F_M  (BIT(11))
#define DPORT_PMS_PRO_AHB_RTCSLOW_1_L_F_V  0x1
#define DPORT_PMS_PRO_AHB_RTCSLOW_1_L_F_S  11
/* DPORT_PMS_PRO_AHB_RTCSLOW_1_SPLTADDR : R/W ;bitpos:[10:0] ;default: 11'b0 ; */
/*description: */
#define DPORT_PMS_PRO_AHB_RTCSLOW_1_SPLTADDR  0x000007FF
#define DPORT_PMS_PRO_AHB_RTCSLOW_1_SPLTADDR_M  ((DPORT_PMS_PRO_AHB_RTCSLOW_1_SPLTADDR_V)<<(DPORT_PMS_PRO_AHB_RTCSLOW_1_SPLTADDR_S))
#define DPORT_PMS_PRO_AHB_RTCSLOW_1_SPLTADDR_V  0x7FF
#define DPORT_PMS_PRO_AHB_RTCSLOW_1_SPLTADDR_S  0

#define DPORT_PMS_PRO_AHB_2_REG          (DR_REG_SENSITIVE_BASE + 0x040)
/* DPORT_PMS_PRO_AHB_ILG_INTR : RO ;bitpos:[2] ;default: 1'b0 ; */
/*description: */
#define DPORT_PMS_PRO_AHB_ILG_INTR  (BIT(2))
#define DPORT_PMS_PRO_AHB_ILG_INTR_M  (BIT(2))
#define DPORT_PMS_PRO_AHB_ILG_INTR_V  0x1
#define DPORT_PMS_PRO_AHB_ILG_INTR_S  2
/* DPORT_PMS_PRO_AHB_ILG_EN : R/W ;bitpos:[1] ;default: 1'b0 ; */
/*description: */
#define DPORT_PMS_PRO_AHB_ILG_EN  (BIT(1))
#define DPORT_PMS_PRO_AHB_ILG_EN_M  (BIT(1))
#define DPORT_PMS_PRO_AHB_ILG_EN_V  0x1
#define DPORT_PMS_PRO_AHB_ILG_EN_S  1
/* DPORT_PMS_PRO_AHB_ILG_CLR : R/W ;bitpos:[0] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_AHB_ILG_CLR  (BIT(0))
#define DPORT_PMS_PRO_AHB_ILG_CLR_M  (BIT(0))
#define DPORT_PMS_PRO_AHB_ILG_CLR_V  0x1
#define DPORT_PMS_PRO_AHB_ILG_CLR_S  0

#define DPORT_PMS_PRO_AHB_3_REG          (DR_REG_SENSITIVE_BASE + 0x044)
/* DPORT_PMS_PRO_AHB_ILG_ST : RO ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_PMS_PRO_AHB_ILG_ST  0xFFFFFFFF
#define DPORT_PMS_PRO_AHB_ILG_ST_M  ((DPORT_PMS_PRO_AHB_ILG_ST_V)<<(DPORT_PMS_PRO_AHB_ILG_ST_S))
#define DPORT_PMS_PRO_AHB_ILG_ST_V  0xFFFFFFFF
#define DPORT_PMS_PRO_AHB_ILG_ST_S  0

#define DPORT_PMS_PRO_TRACE_0_REG          (DR_REG_SENSITIVE_BASE + 0x048)
/* DPORT_PMS_PRO_TRACE_DISABLE : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: */
#define DPORT_PMS_PRO_TRACE_DISABLE  (BIT(0))
#define DPORT_PMS_PRO_TRACE_DISABLE_M  (BIT(0))
#define DPORT_PMS_PRO_TRACE_DISABLE_V  0x1
#define DPORT_PMS_PRO_TRACE_DISABLE_S  0

#define DPORT_PMS_PRO_CACHE_0_REG          (DR_REG_SENSITIVE_BASE + 0x04C)
/* DPORT_PMS_PRO_CACHE_CONNECT : R/W ;bitpos:[11:0] ;default: 12'b0 ; */
/*description: */
#define DPORT_PMS_PRO_CACHE_CONNECT  0x00000FFF
#define DPORT_PMS_PRO_CACHE_CONNECT_M  ((DPORT_PMS_PRO_CACHE_CONNECT_V)<<(DPORT_PMS_PRO_CACHE_CONNECT_S))
#define DPORT_PMS_PRO_CACHE_CONNECT_V  0xFFF
#define DPORT_PMS_PRO_CACHE_CONNECT_S  0

#define DPORT_PMS_PRO_CACHE_1_REG          (DR_REG_SENSITIVE_BASE + 0x050)
/* DPORT_PMS_PRO_CACHE_ILG_INTR : RO ;bitpos:[2] ;default: 1'b0 ; */
/*description: */
#define DPORT_PMS_PRO_CACHE_ILG_INTR  (BIT(2))
#define DPORT_PMS_PRO_CACHE_ILG_INTR_M  (BIT(2))
#define DPORT_PMS_PRO_CACHE_ILG_INTR_V  0x1
#define DPORT_PMS_PRO_CACHE_ILG_INTR_S  2
/* DPORT_PMS_PRO_CACHE_ILG_EN : R/W ;bitpos:[1] ;default: 1'b0 ; */
/*description: */
#define DPORT_PMS_PRO_CACHE_ILG_EN  (BIT(1))
#define DPORT_PMS_PRO_CACHE_ILG_EN_M  (BIT(1))
#define DPORT_PMS_PRO_CACHE_ILG_EN_V  0x1
#define DPORT_PMS_PRO_CACHE_ILG_EN_S  1
/* DPORT_PMS_PRO_CACHE_ILG_CLR : R/W ;bitpos:[0] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_PRO_CACHE_ILG_CLR  (BIT(0))
#define DPORT_PMS_PRO_CACHE_ILG_CLR_M  (BIT(0))
#define DPORT_PMS_PRO_CACHE_ILG_CLR_V  0x1
#define DPORT_PMS_PRO_CACHE_ILG_CLR_S  0

#define DPORT_PMS_PRO_CACHE_2_REG          (DR_REG_SENSITIVE_BASE + 0x054)
/* DPORT_PMS_PRO_CACHE_ILG_ST_I : RO ;bitpos:[16:0] ;default: 17'b0 ; */
/*description: */
#define DPORT_PMS_PRO_CACHE_ILG_ST_I  0x0001FFFF
#define DPORT_PMS_PRO_CACHE_ILG_ST_I_M  ((DPORT_PMS_PRO_CACHE_ILG_ST_I_V)<<(DPORT_PMS_PRO_CACHE_ILG_ST_I_S))
#define DPORT_PMS_PRO_CACHE_ILG_ST_I_V  0x1FFFF
#define DPORT_PMS_PRO_CACHE_ILG_ST_I_S  0

#define DPORT_PMS_PRO_CACHE_3_REG          (DR_REG_SENSITIVE_BASE + 0x058)
/* DPORT_PMS_PRO_CACHE_ILG_ST_D : RO ;bitpos:[16:0] ;default: 17'b0 ; */
/*description: */
#define DPORT_PMS_PRO_CACHE_ILG_ST_D  0x0001FFFF
#define DPORT_PMS_PRO_CACHE_ILG_ST_D_M  ((DPORT_PMS_PRO_CACHE_ILG_ST_D_V)<<(DPORT_PMS_PRO_CACHE_ILG_ST_D_S))
#define DPORT_PMS_PRO_CACHE_ILG_ST_D_V  0x1FFFF
#define DPORT_PMS_PRO_CACHE_ILG_ST_D_S  0

#define DPORT_PMS_DMA_APB_I_0_REG          (DR_REG_SENSITIVE_BASE + 0x05C)
/* DPORT_PMS_DMA_APB_I_SRAM_3_H_W : R/W ;bitpos:[26] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_APB_I_SRAM_3_H_W  (BIT(26))
#define DPORT_PMS_DMA_APB_I_SRAM_3_H_W_M  (BIT(26))
#define DPORT_PMS_DMA_APB_I_SRAM_3_H_W_V  0x1
#define DPORT_PMS_DMA_APB_I_SRAM_3_H_W_S  26
/* DPORT_PMS_DMA_APB_I_SRAM_3_H_R : R/W ;bitpos:[25] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_APB_I_SRAM_3_H_R  (BIT(25))
#define DPORT_PMS_DMA_APB_I_SRAM_3_H_R_M  (BIT(25))
#define DPORT_PMS_DMA_APB_I_SRAM_3_H_R_V  0x1
#define DPORT_PMS_DMA_APB_I_SRAM_3_H_R_S  25
/* DPORT_PMS_DMA_APB_I_SRAM_3_L_W : R/W ;bitpos:[24] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_APB_I_SRAM_3_L_W  (BIT(24))
#define DPORT_PMS_DMA_APB_I_SRAM_3_L_W_M  (BIT(24))
#define DPORT_PMS_DMA_APB_I_SRAM_3_L_W_V  0x1
#define DPORT_PMS_DMA_APB_I_SRAM_3_L_W_S  24
/* DPORT_PMS_DMA_APB_I_SRAM_3_L_R : R/W ;bitpos:[23] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_APB_I_SRAM_3_L_R  (BIT(23))
#define DPORT_PMS_DMA_APB_I_SRAM_3_L_R_M  (BIT(23))
#define DPORT_PMS_DMA_APB_I_SRAM_3_L_R_V  0x1
#define DPORT_PMS_DMA_APB_I_SRAM_3_L_R_S  23
/* DPORT_PMS_DMA_APB_I_SRAM_3_SPLTADDR : R/W ;bitpos:[22:6] ;default: 17'b0 ; */
/*description: */
#define DPORT_PMS_DMA_APB_I_SRAM_3_SPLTADDR  0x0001FFFF
#define DPORT_PMS_DMA_APB_I_SRAM_3_SPLTADDR_M  ((DPORT_PMS_DMA_APB_I_SRAM_3_SPLTADDR_V)<<(DPORT_PMS_DMA_APB_I_SRAM_3_SPLTADDR_S))
#define DPORT_PMS_DMA_APB_I_SRAM_3_SPLTADDR_V  0x1FFFF
#define DPORT_PMS_DMA_APB_I_SRAM_3_SPLTADDR_S  6
/* DPORT_PMS_DMA_APB_I_SRAM_2_W : R/W ;bitpos:[5] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_APB_I_SRAM_2_W  (BIT(5))
#define DPORT_PMS_DMA_APB_I_SRAM_2_W_M  (BIT(5))
#define DPORT_PMS_DMA_APB_I_SRAM_2_W_V  0x1
#define DPORT_PMS_DMA_APB_I_SRAM_2_W_S  5
/* DPORT_PMS_DMA_APB_I_SRAM_2_R : R/W ;bitpos:[4] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_APB_I_SRAM_2_R  (BIT(4))
#define DPORT_PMS_DMA_APB_I_SRAM_2_R_M  (BIT(4))
#define DPORT_PMS_DMA_APB_I_SRAM_2_R_V  0x1
#define DPORT_PMS_DMA_APB_I_SRAM_2_R_S  4
/* DPORT_PMS_DMA_APB_I_SRAM_1_W : R/W ;bitpos:[3] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_APB_I_SRAM_1_W  (BIT(3))
#define DPORT_PMS_DMA_APB_I_SRAM_1_W_M  (BIT(3))
#define DPORT_PMS_DMA_APB_I_SRAM_1_W_V  0x1
#define DPORT_PMS_DMA_APB_I_SRAM_1_W_S  3
/* DPORT_PMS_DMA_APB_I_SRAM_1_R : R/W ;bitpos:[2] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_APB_I_SRAM_1_R  (BIT(2))
#define DPORT_PMS_DMA_APB_I_SRAM_1_R_M  (BIT(2))
#define DPORT_PMS_DMA_APB_I_SRAM_1_R_V  0x1
#define DPORT_PMS_DMA_APB_I_SRAM_1_R_S  2
/* DPORT_PMS_DMA_APB_I_SRAM_0_W : R/W ;bitpos:[1] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_APB_I_SRAM_0_W  (BIT(1))
#define DPORT_PMS_DMA_APB_I_SRAM_0_W_M  (BIT(1))
#define DPORT_PMS_DMA_APB_I_SRAM_0_W_V  0x1
#define DPORT_PMS_DMA_APB_I_SRAM_0_W_S  1
/* DPORT_PMS_DMA_APB_I_SRAM_0_R : R/W ;bitpos:[0] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_APB_I_SRAM_0_R  (BIT(0))
#define DPORT_PMS_DMA_APB_I_SRAM_0_R_M  (BIT(0))
#define DPORT_PMS_DMA_APB_I_SRAM_0_R_V  0x1
#define DPORT_PMS_DMA_APB_I_SRAM_0_R_S  0

#define DPORT_PMS_DMA_APB_I_1_REG          (DR_REG_SENSITIVE_BASE + 0x060)
/* DPORT_PMS_DMA_APB_I_ILG_INTR : RO ;bitpos:[2] ;default: 1'b0 ; */
/*description: */
#define DPORT_PMS_DMA_APB_I_ILG_INTR  (BIT(2))
#define DPORT_PMS_DMA_APB_I_ILG_INTR_M  (BIT(2))
#define DPORT_PMS_DMA_APB_I_ILG_INTR_V  0x1
#define DPORT_PMS_DMA_APB_I_ILG_INTR_S  2
/* DPORT_PMS_DMA_APB_I_ILG_EN : R/W ;bitpos:[1] ;default: 1'b0 ; */
/*description: */
#define DPORT_PMS_DMA_APB_I_ILG_EN  (BIT(1))
#define DPORT_PMS_DMA_APB_I_ILG_EN_M  (BIT(1))
#define DPORT_PMS_DMA_APB_I_ILG_EN_V  0x1
#define DPORT_PMS_DMA_APB_I_ILG_EN_S  1
/* DPORT_PMS_DMA_APB_I_ILG_CLR : R/W ;bitpos:[0] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_APB_I_ILG_CLR  (BIT(0))
#define DPORT_PMS_DMA_APB_I_ILG_CLR_M  (BIT(0))
#define DPORT_PMS_DMA_APB_I_ILG_CLR_V  0x1
#define DPORT_PMS_DMA_APB_I_ILG_CLR_S  0

#define DPORT_PMS_DMA_APB_I_2_REG          (DR_REG_SENSITIVE_BASE + 0x064)
/* DPORT_PMS_DMA_APB_I_ILG_ST : RO ;bitpos:[22:0] ;default: 23'b0 ; */
/*description: */
#define DPORT_PMS_DMA_APB_I_ILG_ST  0x007FFFFF
#define DPORT_PMS_DMA_APB_I_ILG_ST_M  ((DPORT_PMS_DMA_APB_I_ILG_ST_V)<<(DPORT_PMS_DMA_APB_I_ILG_ST_S))
#define DPORT_PMS_DMA_APB_I_ILG_ST_V  0x7FFFFF
#define DPORT_PMS_DMA_APB_I_ILG_ST_S  0

#define DPORT_PMS_DMA_RX_I_0_REG          (DR_REG_SENSITIVE_BASE + 0x068)
/* DPORT_PMS_DMA_RX_I_SRAM_3_H_W : R/W ;bitpos:[26] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_RX_I_SRAM_3_H_W  (BIT(26))
#define DPORT_PMS_DMA_RX_I_SRAM_3_H_W_M  (BIT(26))
#define DPORT_PMS_DMA_RX_I_SRAM_3_H_W_V  0x1
#define DPORT_PMS_DMA_RX_I_SRAM_3_H_W_S  26
/* DPORT_PMS_DMA_RX_I_SRAM_3_H_R : R/W ;bitpos:[25] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_RX_I_SRAM_3_H_R  (BIT(25))
#define DPORT_PMS_DMA_RX_I_SRAM_3_H_R_M  (BIT(25))
#define DPORT_PMS_DMA_RX_I_SRAM_3_H_R_V  0x1
#define DPORT_PMS_DMA_RX_I_SRAM_3_H_R_S  25
/* DPORT_PMS_DMA_RX_I_SRAM_3_L_W : R/W ;bitpos:[24] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_RX_I_SRAM_3_L_W  (BIT(24))
#define DPORT_PMS_DMA_RX_I_SRAM_3_L_W_M  (BIT(24))
#define DPORT_PMS_DMA_RX_I_SRAM_3_L_W_V  0x1
#define DPORT_PMS_DMA_RX_I_SRAM_3_L_W_S  24
/* DPORT_PMS_DMA_RX_I_SRAM_3_L_R : R/W ;bitpos:[23] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_RX_I_SRAM_3_L_R  (BIT(23))
#define DPORT_PMS_DMA_RX_I_SRAM_3_L_R_M  (BIT(23))
#define DPORT_PMS_DMA_RX_I_SRAM_3_L_R_V  0x1
#define DPORT_PMS_DMA_RX_I_SRAM_3_L_R_S  23
/* DPORT_PMS_DMA_RX_I_SRAM_3_SPLTADDR : R/W ;bitpos:[22:6] ;default: 17'b0 ; */
/*description: */
#define DPORT_PMS_DMA_RX_I_SRAM_3_SPLTADDR  0x0001FFFF
#define DPORT_PMS_DMA_RX_I_SRAM_3_SPLTADDR_M  ((DPORT_PMS_DMA_RX_I_SRAM_3_SPLTADDR_V)<<(DPORT_PMS_DMA_RX_I_SRAM_3_SPLTADDR_S))
#define DPORT_PMS_DMA_RX_I_SRAM_3_SPLTADDR_V  0x1FFFF
#define DPORT_PMS_DMA_RX_I_SRAM_3_SPLTADDR_S  6
/* DPORT_PMS_DMA_RX_I_SRAM_2_W : R/W ;bitpos:[5] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_RX_I_SRAM_2_W  (BIT(5))
#define DPORT_PMS_DMA_RX_I_SRAM_2_W_M  (BIT(5))
#define DPORT_PMS_DMA_RX_I_SRAM_2_W_V  0x1
#define DPORT_PMS_DMA_RX_I_SRAM_2_W_S  5
/* DPORT_PMS_DMA_RX_I_SRAM_2_R : R/W ;bitpos:[4] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_RX_I_SRAM_2_R  (BIT(4))
#define DPORT_PMS_DMA_RX_I_SRAM_2_R_M  (BIT(4))
#define DPORT_PMS_DMA_RX_I_SRAM_2_R_V  0x1
#define DPORT_PMS_DMA_RX_I_SRAM_2_R_S  4
/* DPORT_PMS_DMA_RX_I_SRAM_1_W : R/W ;bitpos:[3] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_RX_I_SRAM_1_W  (BIT(3))
#define DPORT_PMS_DMA_RX_I_SRAM_1_W_M  (BIT(3))
#define DPORT_PMS_DMA_RX_I_SRAM_1_W_V  0x1
#define DPORT_PMS_DMA_RX_I_SRAM_1_W_S  3
/* DPORT_PMS_DMA_RX_I_SRAM_1_R : R/W ;bitpos:[2] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_RX_I_SRAM_1_R  (BIT(2))
#define DPORT_PMS_DMA_RX_I_SRAM_1_R_M  (BIT(2))
#define DPORT_PMS_DMA_RX_I_SRAM_1_R_V  0x1
#define DPORT_PMS_DMA_RX_I_SRAM_1_R_S  2
/* DPORT_PMS_DMA_RX_I_SRAM_0_W : R/W ;bitpos:[1] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_RX_I_SRAM_0_W  (BIT(1))
#define DPORT_PMS_DMA_RX_I_SRAM_0_W_M  (BIT(1))
#define DPORT_PMS_DMA_RX_I_SRAM_0_W_V  0x1
#define DPORT_PMS_DMA_RX_I_SRAM_0_W_S  1
/* DPORT_PMS_DMA_RX_I_SRAM_0_R : R/W ;bitpos:[0] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_RX_I_SRAM_0_R  (BIT(0))
#define DPORT_PMS_DMA_RX_I_SRAM_0_R_M  (BIT(0))
#define DPORT_PMS_DMA_RX_I_SRAM_0_R_V  0x1
#define DPORT_PMS_DMA_RX_I_SRAM_0_R_S  0

#define DPORT_PMS_DMA_RX_I_1_REG          (DR_REG_SENSITIVE_BASE + 0x06C)
/* DPORT_PMS_DMA_RX_I_ILG_INTR : RO ;bitpos:[2] ;default: 1'b0 ; */
/*description: */
#define DPORT_PMS_DMA_RX_I_ILG_INTR  (BIT(2))
#define DPORT_PMS_DMA_RX_I_ILG_INTR_M  (BIT(2))
#define DPORT_PMS_DMA_RX_I_ILG_INTR_V  0x1
#define DPORT_PMS_DMA_RX_I_ILG_INTR_S  2
/* DPORT_PMS_DMA_RX_I_ILG_EN : R/W ;bitpos:[1] ;default: 1'b0 ; */
/*description: */
#define DPORT_PMS_DMA_RX_I_ILG_EN  (BIT(1))
#define DPORT_PMS_DMA_RX_I_ILG_EN_M  (BIT(1))
#define DPORT_PMS_DMA_RX_I_ILG_EN_V  0x1
#define DPORT_PMS_DMA_RX_I_ILG_EN_S  1
/* DPORT_PMS_DMA_RX_I_ILG_CLR : R/W ;bitpos:[0] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_RX_I_ILG_CLR  (BIT(0))
#define DPORT_PMS_DMA_RX_I_ILG_CLR_M  (BIT(0))
#define DPORT_PMS_DMA_RX_I_ILG_CLR_V  0x1
#define DPORT_PMS_DMA_RX_I_ILG_CLR_S  0

#define DPORT_PMS_DMA_RX_I_2_REG          (DR_REG_SENSITIVE_BASE + 0x070)
/* DPORT_PMS_DMA_RX_I_ILG_ST : RO ;bitpos:[22:0] ;default: 23'b0 ; */
/*description: */
#define DPORT_PMS_DMA_RX_I_ILG_ST  0x007FFFFF
#define DPORT_PMS_DMA_RX_I_ILG_ST_M  ((DPORT_PMS_DMA_RX_I_ILG_ST_V)<<(DPORT_PMS_DMA_RX_I_ILG_ST_S))
#define DPORT_PMS_DMA_RX_I_ILG_ST_V  0x7FFFFF
#define DPORT_PMS_DMA_RX_I_ILG_ST_S  0

#define DPORT_PMS_DMA_TX_I_0_REG          (DR_REG_SENSITIVE_BASE + 0x074)
/* DPORT_PMS_DMA_TX_I_SRAM_3_H_W : R/W ;bitpos:[26] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_TX_I_SRAM_3_H_W  (BIT(26))
#define DPORT_PMS_DMA_TX_I_SRAM_3_H_W_M  (BIT(26))
#define DPORT_PMS_DMA_TX_I_SRAM_3_H_W_V  0x1
#define DPORT_PMS_DMA_TX_I_SRAM_3_H_W_S  26
/* DPORT_PMS_DMA_TX_I_SRAM_3_H_R : R/W ;bitpos:[25] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_TX_I_SRAM_3_H_R  (BIT(25))
#define DPORT_PMS_DMA_TX_I_SRAM_3_H_R_M  (BIT(25))
#define DPORT_PMS_DMA_TX_I_SRAM_3_H_R_V  0x1
#define DPORT_PMS_DMA_TX_I_SRAM_3_H_R_S  25
/* DPORT_PMS_DMA_TX_I_SRAM_3_L_W : R/W ;bitpos:[24] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_TX_I_SRAM_3_L_W  (BIT(24))
#define DPORT_PMS_DMA_TX_I_SRAM_3_L_W_M  (BIT(24))
#define DPORT_PMS_DMA_TX_I_SRAM_3_L_W_V  0x1
#define DPORT_PMS_DMA_TX_I_SRAM_3_L_W_S  24
/* DPORT_PMS_DMA_TX_I_SRAM_3_L_R : R/W ;bitpos:[23] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_TX_I_SRAM_3_L_R  (BIT(23))
#define DPORT_PMS_DMA_TX_I_SRAM_3_L_R_M  (BIT(23))
#define DPORT_PMS_DMA_TX_I_SRAM_3_L_R_V  0x1
#define DPORT_PMS_DMA_TX_I_SRAM_3_L_R_S  23
/* DPORT_PMS_DMA_TX_I_SRAM_3_SPLTADDR : R/W ;bitpos:[22:6] ;default: 17'b0 ; */
/*description: */
#define DPORT_PMS_DMA_TX_I_SRAM_3_SPLTADDR  0x0001FFFF
#define DPORT_PMS_DMA_TX_I_SRAM_3_SPLTADDR_M  ((DPORT_PMS_DMA_TX_I_SRAM_3_SPLTADDR_V)<<(DPORT_PMS_DMA_TX_I_SRAM_3_SPLTADDR_S))
#define DPORT_PMS_DMA_TX_I_SRAM_3_SPLTADDR_V  0x1FFFF
#define DPORT_PMS_DMA_TX_I_SRAM_3_SPLTADDR_S  6
/* DPORT_PMS_DMA_TX_I_SRAM_2_W : R/W ;bitpos:[5] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_TX_I_SRAM_2_W  (BIT(5))
#define DPORT_PMS_DMA_TX_I_SRAM_2_W_M  (BIT(5))
#define DPORT_PMS_DMA_TX_I_SRAM_2_W_V  0x1
#define DPORT_PMS_DMA_TX_I_SRAM_2_W_S  5
/* DPORT_PMS_DMA_TX_I_SRAM_2_R : R/W ;bitpos:[4] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_TX_I_SRAM_2_R  (BIT(4))
#define DPORT_PMS_DMA_TX_I_SRAM_2_R_M  (BIT(4))
#define DPORT_PMS_DMA_TX_I_SRAM_2_R_V  0x1
#define DPORT_PMS_DMA_TX_I_SRAM_2_R_S  4
/* DPORT_PMS_DMA_TX_I_SRAM_1_W : R/W ;bitpos:[3] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_TX_I_SRAM_1_W  (BIT(3))
#define DPORT_PMS_DMA_TX_I_SRAM_1_W_M  (BIT(3))
#define DPORT_PMS_DMA_TX_I_SRAM_1_W_V  0x1
#define DPORT_PMS_DMA_TX_I_SRAM_1_W_S  3
/* DPORT_PMS_DMA_TX_I_SRAM_1_R : R/W ;bitpos:[2] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_TX_I_SRAM_1_R  (BIT(2))
#define DPORT_PMS_DMA_TX_I_SRAM_1_R_M  (BIT(2))
#define DPORT_PMS_DMA_TX_I_SRAM_1_R_V  0x1
#define DPORT_PMS_DMA_TX_I_SRAM_1_R_S  2
/* DPORT_PMS_DMA_TX_I_SRAM_0_W : R/W ;bitpos:[1] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_TX_I_SRAM_0_W  (BIT(1))
#define DPORT_PMS_DMA_TX_I_SRAM_0_W_M  (BIT(1))
#define DPORT_PMS_DMA_TX_I_SRAM_0_W_V  0x1
#define DPORT_PMS_DMA_TX_I_SRAM_0_W_S  1
/* DPORT_PMS_DMA_TX_I_SRAM_0_R : R/W ;bitpos:[0] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_TX_I_SRAM_0_R  (BIT(0))
#define DPORT_PMS_DMA_TX_I_SRAM_0_R_M  (BIT(0))
#define DPORT_PMS_DMA_TX_I_SRAM_0_R_V  0x1
#define DPORT_PMS_DMA_TX_I_SRAM_0_R_S  0

#define DPORT_PMS_DMA_TX_I_1_REG          (DR_REG_SENSITIVE_BASE + 0x078)
/* DPORT_PMS_DMA_TX_I_ILG_INTR : RO ;bitpos:[2] ;default: 1'b0 ; */
/*description: */
#define DPORT_PMS_DMA_TX_I_ILG_INTR  (BIT(2))
#define DPORT_PMS_DMA_TX_I_ILG_INTR_M  (BIT(2))
#define DPORT_PMS_DMA_TX_I_ILG_INTR_V  0x1
#define DPORT_PMS_DMA_TX_I_ILG_INTR_S  2
/* DPORT_PMS_DMA_TX_I_ILG_EN : R/W ;bitpos:[1] ;default: 1'b0 ; */
/*description: */
#define DPORT_PMS_DMA_TX_I_ILG_EN  (BIT(1))
#define DPORT_PMS_DMA_TX_I_ILG_EN_M  (BIT(1))
#define DPORT_PMS_DMA_TX_I_ILG_EN_V  0x1
#define DPORT_PMS_DMA_TX_I_ILG_EN_S  1
/* DPORT_PMS_DMA_TX_I_ILG_CLR : R/W ;bitpos:[0] ;default: 1'b1 ; */
/*description: */
#define DPORT_PMS_DMA_TX_I_ILG_CLR  (BIT(0))
#define DPORT_PMS_DMA_TX_I_ILG_CLR_M  (BIT(0))
#define DPORT_PMS_DMA_TX_I_ILG_CLR_V  0x1
#define DPORT_PMS_DMA_TX_I_ILG_CLR_S  0

#define DPORT_PMS_DMA_TX_I_2_REG          (DR_REG_SENSITIVE_BASE + 0x07C)
/* DPORT_PMS_DMA_TX_I_ILG_ST : RO ;bitpos:[22:0] ;default: 23'b0 ; */
/*description: */
#define DPORT_PMS_DMA_TX_I_ILG_ST  0x007FFFFF
#define DPORT_PMS_DMA_TX_I_ILG_ST_M  ((DPORT_PMS_DMA_TX_I_ILG_ST_V)<<(DPORT_PMS_DMA_TX_I_ILG_ST_S))
#define DPORT_PMS_DMA_TX_I_ILG_ST_V  0x7FFFFF
#define DPORT_PMS_DMA_TX_I_ILG_ST_S  0

#define DPORT_PRO_BOOT_LOCATION_REG          (DR_REG_SENSITIVE_BASE + 0x080)
/* DPORT_PRO_BOOT_REMAP : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_BOOT_REMAP  (BIT(0))
#define DPORT_PRO_BOOT_REMAP_M  (BIT(0))
#define DPORT_PRO_BOOT_REMAP_V  0x1
#define DPORT_PRO_BOOT_REMAP_S  0

#define DPORT_APB_PERIPHERAL_STATUS_REG          (DR_REG_SENSITIVE_BASE + 0x084)
/* DPORT_APB_PERIPHERAL_SPLIT_BURST : R/W ;bitpos:[0] ;default: 1'b1 ; */
/*description: */
#define DPORT_APB_PERIPHERAL_SPLIT_BURST  (BIT(0))
#define DPORT_APB_PERIPHERAL_SPLIT_BURST_M  (BIT(0))
#define DPORT_APB_PERIPHERAL_SPLIT_BURST_V  0x1
#define DPORT_APB_PERIPHERAL_SPLIT_BURST_S  0

#define DPORT_PMS_OCCUPY_0_REG          (DR_REG_SENSITIVE_BASE + 0x088)
/* DPORT_PMS_OCCUPY_CACHE : R/W ;bitpos:[2:0] ;default: 3'b000 ; */
/*description: */
#define DPORT_PMS_OCCUPY_CACHE  0x00000007
#define DPORT_PMS_OCCUPY_CACHE_M  ((DPORT_PMS_OCCUPY_CACHE_V)<<(DPORT_PMS_OCCUPY_CACHE_S))
#define DPORT_PMS_OCCUPY_CACHE_V  0x7
#define DPORT_PMS_OCCUPY_CACHE_S  0

#define DPORT_PMS_OCCUPY_1_REG          (DR_REG_SENSITIVE_BASE + 0x08C)
/* DPORT_PMS_OCCUPY_MAC_DUMP : R/W ;bitpos:[3:0] ;default: 4'b0000 ; */
/*description: */
#define DPORT_PMS_OCCUPY_MAC_DUMP  0x0000000F
#define DPORT_PMS_OCCUPY_MAC_DUMP_M  ((DPORT_PMS_OCCUPY_MAC_DUMP_V)<<(DPORT_PMS_OCCUPY_MAC_DUMP_S))
#define DPORT_PMS_OCCUPY_MAC_DUMP_V  0xF
#define DPORT_PMS_OCCUPY_MAC_DUMP_S  0

#define DPORT_PMS_OCCUPY_2_REG          (DR_REG_SENSITIVE_BASE + 0x090)
/* DPORT_PMS_OCCUPY_PRO_TRACE : R/W ;bitpos:[25:0] ;default: 26'b0 ; */
/*description: */
#define DPORT_PMS_OCCUPY_PRO_TRACE  0x03FFFFFF
#define DPORT_PMS_OCCUPY_PRO_TRACE_M  ((DPORT_PMS_OCCUPY_PRO_TRACE_V)<<(DPORT_PMS_OCCUPY_PRO_TRACE_S))
#define DPORT_PMS_OCCUPY_PRO_TRACE_V  0x3FFFFFF
#define DPORT_PMS_OCCUPY_PRO_TRACE_S  0

#define SENSITIVE_CLOCK_GATE_REG          (DR_REG_SENSITIVE_BASE + 0x094)
/* SENSITIVE_CLK_EN : R/W ;bitpos:[0] ;default: 1'b1 ; */
/*description: */
#define SENSITIVE_CLK_EN  (BIT(0))
#define SENSITIVE_CLK_EN_M  (BIT(0))
#define SENSITIVE_CLK_EN_V  0x1
#define SENSITIVE_CLK_EN_S  0

#define SENSITIVE_DATE_REG          (DR_REG_SENSITIVE_BASE + 0xFFC)
/* SENSITIVE_DATE : R/W ;bitpos:[27:0] ;default: 28'h1804130 ; */
/*description: */
#define SENSITIVE_DATE  0x0FFFFFFF
#define SENSITIVE_DATE_M  ((SENSITIVE_DATE_V)<<(SENSITIVE_DATE_S))
#define SENSITIVE_DATE_V  0xFFFFFFF
#define SENSITIVE_DATE_S  0

#ifdef __cplusplus
}
#endif



#endif /*_SOC_SENSITIVE_REG_H_ */


