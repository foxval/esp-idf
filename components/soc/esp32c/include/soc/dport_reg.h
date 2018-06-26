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
#ifndef _SOC_DPORT_REG_H_
#define _SOC_DPORT_REG_H_

#if 1
#include"extmem_reg.h"
#include"interrupt_reg.h"
#include"system_reg.h"
#include "sensitive_reg.h"
#include "soc.h"

#ifndef __ASSEMBLER__
#include "dport_access.h"
#endif
#else
#ifdef __cplusplus
extern "C" {
#endif
#include "soc.h"

#ifndef __ASSEMBLER__
#include "dport_access.h"
#endif

#define DPORT_PRO_BOOT_REMAP_CTRL_REG          (DR_REG_DPORT_BASE + 0x000)
/* DPORT_PRO_BOOT_REMAP : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_BOOT_REMAP  (BIT(0))
#define DPORT_PRO_BOOT_REMAP_M  (BIT(0))
#define DPORT_PRO_BOOT_REMAP_V  0x1
#define DPORT_PRO_BOOT_REMAP_S  0

#define DPORT_APP_BOOT_REMAP_CTRL_REG          (DR_REG_DPORT_BASE + 0x004)
/* DPORT_APP_BOOT_REMAP : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: */
#define DPORT_APP_BOOT_REMAP  (BIT(0))
#define DPORT_APP_BOOT_REMAP_M  (BIT(0))
#define DPORT_APP_BOOT_REMAP_V  0x1
#define DPORT_APP_BOOT_REMAP_S  0

#define DPORT_ACCESS_CHECK_REG          (DR_REG_DPORT_BASE + 0x008)
/* DPORT_ACCESS_CHECK_APP : RO ;bitpos:[8] ;default: 1'b0 ; */
/*description: */
#define DPORT_ACCESS_CHECK_APP  (BIT(8))
#define DPORT_ACCESS_CHECK_APP_M  (BIT(8))
#define DPORT_ACCESS_CHECK_APP_V  0x1
#define DPORT_ACCESS_CHECK_APP_S  8
/* DPORT_ACCESS_CHECK_PRO : RO ;bitpos:[0] ;default: 1'b0 ; */
/*description: */
#define DPORT_ACCESS_CHECK_PRO  (BIT(0))
#define DPORT_ACCESS_CHECK_PRO_M  (BIT(0))
#define DPORT_ACCESS_CHECK_PRO_V  0x1
#define DPORT_ACCESS_CHECK_PRO_S  0

#define DPORT_PRO_DPORT_APB_MASK0_REG          (DR_REG_DPORT_BASE + 0x00C)
/* DPORT_PRODPORT_APB_MASK0 : R/W ;bitpos:[31:0] ;default: 32'h0 ; */
/*description: */
#define DPORT_PRODPORT_APB_MASK0  0xFFFFFFFF
#define DPORT_PRODPORT_APB_MASK0_M  ((DPORT_PRODPORT_APB_MASK0_V)<<(DPORT_PRODPORT_APB_MASK0_S))
#define DPORT_PRODPORT_APB_MASK0_V  0xFFFFFFFF
#define DPORT_PRODPORT_APB_MASK0_S  0

#define DPORT_PRO_DPORT_APB_MASK1_REG          (DR_REG_DPORT_BASE + 0x010)
/* DPORT_PRODPORT_APB_MASK1 : R/W ;bitpos:[31:0] ;default: 32'h0 ; */
/*description: */
#define DPORT_PRODPORT_APB_MASK1  0xFFFFFFFF
#define DPORT_PRODPORT_APB_MASK1_M  ((DPORT_PRODPORT_APB_MASK1_V)<<(DPORT_PRODPORT_APB_MASK1_S))
#define DPORT_PRODPORT_APB_MASK1_V  0xFFFFFFFF
#define DPORT_PRODPORT_APB_MASK1_S  0

#define DPORT_APP_DPORT_APB_MASK0_REG          (DR_REG_DPORT_BASE + 0x014)
/* DPORT_APPDPORT_APB_MASK0 : R/W ;bitpos:[31:0] ;default: 32'h0 ; */
/*description: */
#define DPORT_APPDPORT_APB_MASK0  0xFFFFFFFF
#define DPORT_APPDPORT_APB_MASK0_M  ((DPORT_APPDPORT_APB_MASK0_V)<<(DPORT_APPDPORT_APB_MASK0_S))
#define DPORT_APPDPORT_APB_MASK0_V  0xFFFFFFFF
#define DPORT_APPDPORT_APB_MASK0_S  0

#define DPORT_APP_DPORT_APB_MASK1_REG          (DR_REG_DPORT_BASE + 0x018)
/* DPORT_APPDPORT_APB_MASK1 : R/W ;bitpos:[31:0] ;default: 32'h0 ; */
/*description: */
#define DPORT_APPDPORT_APB_MASK1  0xFFFFFFFF
#define DPORT_APPDPORT_APB_MASK1_M  ((DPORT_APPDPORT_APB_MASK1_V)<<(DPORT_APPDPORT_APB_MASK1_S))
#define DPORT_APPDPORT_APB_MASK1_V  0xFFFFFFFF
#define DPORT_APPDPORT_APB_MASK1_S  0

#define DPORT_PERI_CLK_EN_REG          (DR_REG_DPORT_BASE + 0x01C)
/* DPORT_PERI_CLK_EN : R/W ;bitpos:[31:0] ;default: 32'h0 ; */
/*description: */
#define DPORT_PERI_CLK_EN  0xFFFFFFFF
#define DPORT_PERI_CLK_EN_M  ((DPORT_PERI_CLK_EN_V)<<(DPORT_PERI_CLK_EN_S))
#define DPORT_PERI_CLK_EN_V  0xFFFFFFFF
#define DPORT_PERI_CLK_EN_S  0

#define DPORT_PERI_RST_EN_REG          (DR_REG_DPORT_BASE + 0x020)
/* DPORT_PERI_RST_EN : R/W ;bitpos:[31:0] ;default: 32'hffffffff ; */
/*description: */
#define DPORT_PERI_RST_EN  0xFFFFFFFF
#define DPORT_PERI_RST_EN_M  ((DPORT_PERI_RST_EN_V)<<(DPORT_PERI_RST_EN_S))
#define DPORT_PERI_RST_EN_V  0xFFFFFFFF
#define DPORT_PERI_RST_EN_S  0

/* The following bits apply to DPORT_PERI_CLK_EN_REG, DPORT_PERI_RST_EN_REG
 */
#define DPORT_PERI_EN_AES (1<<0)
#define DPORT_PERI_EN_SHA (1<<1)
#define DPORT_PERI_EN_RSA (1<<2)
/* NB: Secure boot reset will hold SHA & AES in reset */
#define DPORT_PERI_EN_SECUREBOOT (1<<3)
/* NB: Digital signature reset will hold AES & RSA in reset */
#define DPORT_PERI_EN_DIGITAL_SIGNATURE (1<<4)
#define DPORT_PERI_EN_PRO_ALONE_GPIO (1<<5)
#define DPORT_PERI_EN_APP_ALONE_GPIO (1<<6)
#define DPORT_PERI_EN_ASSIST_DEBUG (1<<7) 


#define DPORT_WIFI_BB_CFG_REG          (DR_REG_DPORT_BASE + 0x024)
/* DPORT_WIFI_BB_CFG : R/W ;bitpos:[31:0] ;default: 32'h0 ; */
/*description: */
#define DPORT_WIFI_BB_CFG  0xFFFFFFFF
#define DPORT_WIFI_BB_CFG_M  ((DPORT_WIFI_BB_CFG_V)<<(DPORT_WIFI_BB_CFG_S))
#define DPORT_WIFI_BB_CFG_V  0xFFFFFFFF
#define DPORT_WIFI_BB_CFG_S  0

#define DPORT_WIFI_BB_CFG_2_REG          (DR_REG_DPORT_BASE + 0x028)
/* DPORT_WIFI_BB_CFG_2 : R/W ;bitpos:[31:0] ;default: 32'h0 ; */
/*description: */
#define DPORT_WIFI_BB_CFG_2  0xFFFFFFFF
#define DPORT_WIFI_BB_CFG_2_M  ((DPORT_WIFI_BB_CFG_2_V)<<(DPORT_WIFI_BB_CFG_2_S))
#define DPORT_WIFI_BB_CFG_2_V  0xFFFFFFFF
#define DPORT_WIFI_BB_CFG_2_S  0

#define DPORT_APPCPU_CTRL_A_REG          (DR_REG_DPORT_BASE + 0x02C)
/* DPORT_APPCPU_RESETTING : R/W ;bitpos:[0] ;default: 1'b1 ; */
/*description: */
#define DPORT_APPCPU_RESETTING  (BIT(0))
#define DPORT_APPCPU_RESETTING_M  (BIT(0))
#define DPORT_APPCPU_RESETTING_V  0x1
#define DPORT_APPCPU_RESETTING_S  0

#define DPORT_APPCPU_CTRL_B_REG          (DR_REG_DPORT_BASE + 0x030)
/* DPORT_APPCPU_CLKGATE_EN : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: */
#define DPORT_APPCPU_CLKGATE_EN  (BIT(0))
#define DPORT_APPCPU_CLKGATE_EN_M  (BIT(0))
#define DPORT_APPCPU_CLKGATE_EN_V  0x1
#define DPORT_APPCPU_CLKGATE_EN_S  0

#define DPORT_APPCPU_CTRL_C_REG          (DR_REG_DPORT_BASE + 0x034)
/* DPORT_APPCPU_RUNSTALL : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: */
#define DPORT_APPCPU_RUNSTALL  (BIT(0))
#define DPORT_APPCPU_RUNSTALL_M  (BIT(0))
#define DPORT_APPCPU_RUNSTALL_V  0x1
#define DPORT_APPCPU_RUNSTALL_S  0

#define DPORT_APPCPU_CTRL_D_REG          (DR_REG_DPORT_BASE + 0x038)
/* DPORT_APPCPU_BOOT_ADDR : R/W ;bitpos:[31:0] ;default: 32'h0 ; */
/*description: */
#define DPORT_APPCPU_BOOT_ADDR  0xFFFFFFFF
#define DPORT_APPCPU_BOOT_ADDR_M  ((DPORT_APPCPU_BOOT_ADDR_V)<<(DPORT_APPCPU_BOOT_ADDR_S))
#define DPORT_APPCPU_BOOT_ADDR_V  0xFFFFFFFF
#define DPORT_APPCPU_BOOT_ADDR_S  0

#define DPORT_CPU_PER_CONF_REG          (DR_REG_DPORT_BASE + 0x03C)
/* DPORT_CPU_WAIT_MODE_FORCE_ON : R/W ;bitpos:[3] ;default: 1'b1 ; */
/*description: */
#define DPORT_CPU_WAIT_MODE_FORCE_ON  (BIT(3))
#define DPORT_CPU_WAIT_MODE_FORCE_ON_M  (BIT(3))
#define DPORT_CPU_WAIT_MODE_FORCE_ON_V  0x1
#define DPORT_CPU_WAIT_MODE_FORCE_ON_S  3
/* DPORT_PLL_FREQ_SEL : R/W ;bitpos:[2] ;default: 1'b0 ; */
/*description: */
#define DPORT_PLL_FREQ_SEL  (BIT(2))
#define DPORT_PLL_FREQ_SEL_M  (BIT(2))
#define DPORT_PLL_FREQ_SEL_V  0x1
#define DPORT_PLL_FREQ_SEL_S  2
/* DPORT_CPUPERIOD_SEL : R/W ;bitpos:[1:0] ;default: 2'b0 ; */
/*description: */
#define DPORT_CPUPERIOD_SEL  0x00000003
#define DPORT_CPUPERIOD_SEL_M  ((DPORT_CPUPERIOD_SEL_V)<<(DPORT_CPUPERIOD_SEL_S))
#define DPORT_CPUPERIOD_SEL_V  0x3
#define DPORT_CPUPERIOD_SEL_S  0

#define DPORT_JTAG_CTRL_REG          (DR_REG_DPORT_BASE + 0x040)
/* DPORT_CANCEL_EFUSE_DISABLE_JTAG_TEMPORARY : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: */
#define DPORT_CANCEL_EFUSE_DISABLE_JTAG_TEMPORARY  (BIT(0))
#define DPORT_CANCEL_EFUSE_DISABLE_JTAG_TEMPORARY_M  (BIT(0))
#define DPORT_CANCEL_EFUSE_DISABLE_JTAG_TEMPORARY_V  0x1
#define DPORT_CANCEL_EFUSE_DISABLE_JTAG_TEMPORARY_S  0

#define DPORT_PRO_CACHE_CTRL_REG          (DR_REG_DPORT_BASE + 0x044)
/* DPORT_PRO_CACHE_UNLOCK_DONE : RO ;bitpos:[28] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_CACHE_UNLOCK_DONE  (BIT(28))
#define DPORT_PRO_CACHE_UNLOCK_DONE_M  (BIT(28))
#define DPORT_PRO_CACHE_UNLOCK_DONE_V  0x1
#define DPORT_PRO_CACHE_UNLOCK_DONE_S  28
/* DPORT_PRO_CACHE_UNLOCK_ENA : R/W ;bitpos:[27] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_CACHE_UNLOCK_ENA  (BIT(27))
#define DPORT_PRO_CACHE_UNLOCK_ENA_M  (BIT(27))
#define DPORT_PRO_CACHE_UNLOCK_ENA_V  0x1
#define DPORT_PRO_CACHE_UNLOCK_ENA_S  27
/* DPORT_SLAVE_REQ : RO ;bitpos:[26] ;default: 1'b0 ; */
/*description: */
#define DPORT_SLAVE_REQ  (BIT(26))
#define DPORT_SLAVE_REQ_M  (BIT(26))
#define DPORT_SLAVE_REQ_V  0x1
#define DPORT_SLAVE_REQ_S  26
/* DPORT_AHB_SPI_REQ : RO ;bitpos:[25] ;default: 1'b0 ; */
/*description: */
#define DPORT_AHB_SPI_REQ  (BIT(25))
#define DPORT_AHB_SPI_REQ_M  (BIT(25))
#define DPORT_AHB_SPI_REQ_V  0x1
#define DPORT_AHB_SPI_REQ_S  25
/* DPORT_PRO_SLAVE_REQ : RO ;bitpos:[24] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_SLAVE_REQ  (BIT(24))
#define DPORT_PRO_SLAVE_REQ_M  (BIT(24))
#define DPORT_PRO_SLAVE_REQ_V  0x1
#define DPORT_PRO_SLAVE_REQ_S  24
/* DPORT_PRO_AHB_SPI_REQ : RO ;bitpos:[23] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_AHB_SPI_REQ  (BIT(23))
#define DPORT_PRO_AHB_SPI_REQ_M  (BIT(23))
#define DPORT_PRO_AHB_SPI_REQ_V  0x1
#define DPORT_PRO_AHB_SPI_REQ_S  23
/* DPORT_PRO_CACHESETSIZEMODE : R/W ;bitpos:[22:21] ;default: 2'b0 ; */
/*description: */
#define DPORT_PRO_CACHESETSIZEMODE  0x00000003
#define DPORT_PRO_CACHESETSIZEMODE_M  ((DPORT_PRO_CACHESETSIZEMODE_V)<<(DPORT_PRO_CACHESETSIZEMODE_S))
#define DPORT_PRO_CACHESETSIZEMODE_V  0x3
#define DPORT_PRO_CACHESETSIZEMODE_S  21
/* DPORT_PRO_CACHEBLOCKSIZEMODE : R/W ;bitpos:[20:19] ;default: 2'b0 ; */
/*description: */
#define DPORT_PRO_CACHEBLOCKSIZEMODE  0x00000003
#define DPORT_PRO_CACHEBLOCKSIZEMODE_M  ((DPORT_PRO_CACHEBLOCKSIZEMODE_V)<<(DPORT_PRO_CACHEBLOCKSIZEMODE_S))
#define DPORT_PRO_CACHEBLOCKSIZEMODE_V  0x3
#define DPORT_PRO_CACHEBLOCKSIZEMODE_S  19
/* DPORT_PRO_CACHE_PRELOADDONE : RO ;bitpos:[18] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_CACHE_PRELOADDONE  (BIT(18))
#define DPORT_PRO_CACHE_PRELOADDONE_M  (BIT(18))
#define DPORT_PRO_CACHE_PRELOADDONE_V  0x1
#define DPORT_PRO_CACHE_PRELOADDONE_S  18
/* DPORT_PRO_CACHE_PRELOADENA : R/W ;bitpos:[17] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_CACHE_PRELOADENA  (BIT(17))
#define DPORT_PRO_CACHE_PRELOADENA_M  (BIT(17))
#define DPORT_PRO_CACHE_PRELOADENA_V  0x1
#define DPORT_PRO_CACHE_PRELOADENA_S  17
/* DPORT_PRO_CACHE_AUTOLOADDONE : RO ;bitpos:[16] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_CACHE_AUTOLOADDONE  (BIT(16))
#define DPORT_PRO_CACHE_AUTOLOADDONE_M  (BIT(16))
#define DPORT_PRO_CACHE_AUTOLOADDONE_V  0x1
#define DPORT_PRO_CACHE_AUTOLOADDONE_S  16
/* DPORT_PRO_CACHE_AUTOLOADENA : R/W ;bitpos:[15] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_CACHE_AUTOLOADENA  (BIT(15))
#define DPORT_PRO_CACHE_AUTOLOADENA_M  (BIT(15))
#define DPORT_PRO_CACHE_AUTOLOADENA_V  0x1
#define DPORT_PRO_CACHE_AUTOLOADENA_S  15
/* DPORT_PRO_DRAM_HL : R/W ;bitpos:[14] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_DRAM_HL  (BIT(14))
#define DPORT_PRO_DRAM_HL_M  (BIT(14))
#define DPORT_PRO_DRAM_HL_V  0x1
#define DPORT_PRO_DRAM_HL_S  14
/* DPORT_PRO_DRAM_SPLIT : R/W ;bitpos:[13] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_DRAM_SPLIT  (BIT(13))
#define DPORT_PRO_DRAM_SPLIT_M  (BIT(13))
#define DPORT_PRO_DRAM_SPLIT_V  0x1
#define DPORT_PRO_DRAM_SPLIT_S  13
/* DPORT_PRO_CACHE_LOCK1_EN : R/W ;bitpos:[12] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_CACHE_LOCK1_EN  (BIT(12))
#define DPORT_PRO_CACHE_LOCK1_EN_M  (BIT(12))
#define DPORT_PRO_CACHE_LOCK1_EN_V  0x1
#define DPORT_PRO_CACHE_LOCK1_EN_S  12
/* DPORT_PRO_CACHE_LOCK0_EN : R/W ;bitpos:[11] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_CACHE_LOCK0_EN  (BIT(11))
#define DPORT_PRO_CACHE_LOCK0_EN_M  (BIT(11))
#define DPORT_PRO_CACHE_LOCK0_EN_V  0x1
#define DPORT_PRO_CACHE_LOCK0_EN_S  11
/* DPORT_PRO_CACHE_CLEAN_DONE : RO ;bitpos:[10] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_CACHE_CLEAN_DONE  (BIT(10))
#define DPORT_PRO_CACHE_CLEAN_DONE_M  (BIT(10))
#define DPORT_PRO_CACHE_CLEAN_DONE_V  0x1
#define DPORT_PRO_CACHE_CLEAN_DONE_S  10
/* DPORT_PRO_CACHE_CLEAN_ENA : R/W ;bitpos:[9] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_CACHE_CLEAN_ENA  (BIT(9))
#define DPORT_PRO_CACHE_CLEAN_ENA_M  (BIT(9))
#define DPORT_PRO_CACHE_CLEAN_ENA_V  0x1
#define DPORT_PRO_CACHE_CLEAN_ENA_S  9
/* DPORT_PRO_CACHE_FLUSH_DONE : RO ;bitpos:[8] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_CACHE_FLUSH_DONE  (BIT(8))
#define DPORT_PRO_CACHE_FLUSH_DONE_M  (BIT(8))
#define DPORT_PRO_CACHE_FLUSH_DONE_V  0x1
#define DPORT_PRO_CACHE_FLUSH_DONE_S  8
/* DPORT_PRO_CACHE_FLUSH_ENA : R/W ;bitpos:[7] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_CACHE_FLUSH_ENA  (BIT(7))
#define DPORT_PRO_CACHE_FLUSH_ENA_M  (BIT(7))
#define DPORT_PRO_CACHE_FLUSH_ENA_V  0x1
#define DPORT_PRO_CACHE_FLUSH_ENA_S  7
/* DPORT_PRO_CACHE_INVALIDATE_DONE : RO ;bitpos:[6] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_CACHE_INVALIDATE_DONE  (BIT(6))
#define DPORT_PRO_CACHE_INVALIDATE_DONE_M  (BIT(6))
#define DPORT_PRO_CACHE_INVALIDATE_DONE_V  0x1
#define DPORT_PRO_CACHE_INVALIDATE_DONE_S  6
/* DPORT_PRO_CACHE_INVALIDATE_ENA : R/W ;bitpos:[5] ;default: 1'b1 ; */
/*description: */
#define DPORT_PRO_CACHE_INVALIDATE_ENA  (BIT(5))
#define DPORT_PRO_CACHE_INVALIDATE_ENA_M  (BIT(5))
#define DPORT_PRO_CACHE_INVALIDATE_ENA_V  0x1
#define DPORT_PRO_CACHE_INVALIDATE_ENA_S  5
/* DPORT_PRO_CACHE_MODE : R/W ;bitpos:[4:2] ;default: 3'b0 ; */
/*description: */
#define DPORT_PRO_CACHE_MODE  0x00000007
#define DPORT_PRO_CACHE_MODE_M  ((DPORT_PRO_CACHE_MODE_V)<<(DPORT_PRO_CACHE_MODE_S))
#define DPORT_PRO_CACHE_MODE_V  0x7
#define DPORT_PRO_CACHE_MODE_S  2
/* DPORT_PRO_CACHE_ENABLE : R/W ;bitpos:[1] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_CACHE_ENABLE  (BIT(1))
#define DPORT_PRO_CACHE_ENABLE_M  (BIT(1))
#define DPORT_PRO_CACHE_ENABLE_V  0x1
#define DPORT_PRO_CACHE_ENABLE_S  1
/* DPORT_PRO_CACHE_CLK_ON : R/W ;bitpos:[0] ;default: 1'b1 ; */
/*description: */
#define DPORT_PRO_CACHE_CLK_ON  (BIT(0))
#define DPORT_PRO_CACHE_CLK_ON_M  (BIT(0))
#define DPORT_PRO_CACHE_CLK_ON_V  0x1
#define DPORT_PRO_CACHE_CLK_ON_S  0

#define DPORT_PRO_CACHE_CTRL1_REG          (DR_REG_DPORT_BASE + 0x048)
/* DPORT_PRO_CMMU_PD : R/W ;bitpos:[12] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_CMMU_PD  (BIT(12))
#define DPORT_PRO_CMMU_PD_M  (BIT(12))
#define DPORT_PRO_CMMU_PD_V  0x1
#define DPORT_PRO_CMMU_PD_S  12
/* DPORT_PRO_CMMU_FORCE_ON : R/W ;bitpos:[11] ;default: 1'b1 ; */
/*description: */
#define DPORT_PRO_CMMU_FORCE_ON  (BIT(11))
#define DPORT_PRO_CMMU_FORCE_ON_M  (BIT(11))
#define DPORT_PRO_CMMU_FORCE_ON_V  0x1
#define DPORT_PRO_CMMU_FORCE_ON_S  11
/* DPORT_PRO_CMMU_SRAM_PAGE_MODE : R/W ;bitpos:[8:6] ;default: 3'd0 ; */
/*description: */
#define DPORT_PRO_CMMU_SRAM_PAGE_MODE  0x00000007
#define DPORT_PRO_CMMU_SRAM_PAGE_MODE_M  ((DPORT_PRO_CMMU_SRAM_PAGE_MODE_V)<<(DPORT_PRO_CMMU_SRAM_PAGE_MODE_S))
#define DPORT_PRO_CMMU_SRAM_PAGE_MODE_V  0x7
#define DPORT_PRO_CMMU_SRAM_PAGE_MODE_S  6
/* DPORT_PRO_CACHE_MASK_OPSDRAM : R/W ;bitpos:[5] ;default: 1'b1 ; */
/*description: */
#define DPORT_PRO_CACHE_MASK_OPSDRAM  (BIT(5))
#define DPORT_PRO_CACHE_MASK_OPSDRAM_M  (BIT(5))
#define DPORT_PRO_CACHE_MASK_OPSDRAM_V  0x1
#define DPORT_PRO_CACHE_MASK_OPSDRAM_S  5
/* DPORT_PRO_CACHE_MASK_DROM0 : R/W ;bitpos:[4] ;default: 1'b1 ; */
/*description: */
#if 0
#define DPORT_PRO_CACHE_MASK_DROM0  (BIT(4))
#define DPORT_PRO_CACHE_MASK_DROM0_M  (BIT(4))
#define DPORT_PRO_CACHE_MASK_DROM0_V  0x1
#define DPORT_PRO_CACHE_MASK_DROM0_S  4
#endif
/* DPORT_PRO_CACHE_MASK_DRAM1 : R/W ;bitpos:[3] ;default: 1'b1 ; */
/*description: */
#define DPORT_PRO_CACHE_MASK_DRAM1  (BIT(3))
#define DPORT_PRO_CACHE_MASK_DRAM1_M  (BIT(3))
#define DPORT_PRO_CACHE_MASK_DRAM1_V  0x1
#define DPORT_PRO_CACHE_MASK_DRAM1_S  3

#define DPORT_PRO_CACHE_LOCK0_ADDR_REG          (DR_REG_DPORT_BASE + 0x04C)
/* DPORT_PRO_CACHE_LOCK0_ADDR : R/W ;bitpos:[31:0] ;default: 10'h0 ; */
/*description: */
#define DPORT_PRO_CACHE_LOCK0_ADDR  0xFFFFFFFF
#define DPORT_PRO_CACHE_LOCK0_ADDR_M  ((DPORT_PRO_CACHE_LOCK0_ADDR_V)<<(DPORT_PRO_CACHE_LOCK0_ADDR_S))
#define DPORT_PRO_CACHE_LOCK0_ADDR_V  0xFFFFFFFF
#define DPORT_PRO_CACHE_LOCK0_ADDR_S  0

#define DPORT_PRO_CACHE_LOCK0_SIZE_REG          (DR_REG_DPORT_BASE + 0x050)
/* DPORT_PRO_CACHE_LOCK0_SIZE : R/W ;bitpos:[15:0] ;default: 16'h0 ; */
/*description: */
#define DPORT_PRO_CACHE_LOCK0_SIZE  0x0000FFFF
#define DPORT_PRO_CACHE_LOCK0_SIZE_M  ((DPORT_PRO_CACHE_LOCK0_SIZE_V)<<(DPORT_PRO_CACHE_LOCK0_SIZE_S))
#define DPORT_PRO_CACHE_LOCK0_SIZE_V  0xFFFF
#define DPORT_PRO_CACHE_LOCK0_SIZE_S  0

#define DPORT_PRO_CACHE_LOCK1_ADDR_REG          (DR_REG_DPORT_BASE + 0x054)
/* DPORT_PRO_CACHE_LOCK1_ADDR : R/W ;bitpos:[31:0] ;default: 10'h0 ; */
/*description: */
#define DPORT_PRO_CACHE_LOCK1_ADDR  0xFFFFFFFF
#define DPORT_PRO_CACHE_LOCK1_ADDR_M  ((DPORT_PRO_CACHE_LOCK1_ADDR_V)<<(DPORT_PRO_CACHE_LOCK1_ADDR_S))
#define DPORT_PRO_CACHE_LOCK1_ADDR_V  0xFFFFFFFF
#define DPORT_PRO_CACHE_LOCK1_ADDR_S  0

#define DPORT_PRO_CACHE_LOCK1_SIZE_REG          (DR_REG_DPORT_BASE + 0x058)
/* DPORT_PRO_CACHE_LOCK1_SIZE : R/W ;bitpos:[15:0] ;default: 16'h0 ; */
/*description: */
#define DPORT_PRO_CACHE_LOCK1_SIZE  0x0000FFFF
#define DPORT_PRO_CACHE_LOCK1_SIZE_M  ((DPORT_PRO_CACHE_LOCK1_SIZE_V)<<(DPORT_PRO_CACHE_LOCK1_SIZE_S))
#define DPORT_PRO_CACHE_LOCK1_SIZE_V  0xFFFF
#define DPORT_PRO_CACHE_LOCK1_SIZE_S  0

#define DPORT_TRACEMEM_MUX_MODE_REG          (DR_REG_DPORT_BASE + 0x05C)
/* DPORT_TRACEMEM_MUX_MODE : R/W ;bitpos:[1:0] ;default: 2'b0 ; */
/*description: */
#define DPORT_TRACEMEM_MUX_MODE  0x00000003
#define DPORT_TRACEMEM_MUX_MODE_M  ((DPORT_TRACEMEM_MUX_MODE_V)<<(DPORT_TRACEMEM_MUX_MODE_S))
#define DPORT_TRACEMEM_MUX_MODE_V  0x3
#define DPORT_TRACEMEM_MUX_MODE_S  0

#define DPORT_PRO_TRACEMEM_ENA_REG          (DR_REG_DPORT_BASE + 0x060)
/* DPORT_PRO_TRACEMEM_ENA : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_TRACEMEM_ENA  (BIT(0))
#define DPORT_PRO_TRACEMEM_ENA_M  (BIT(0))
#define DPORT_PRO_TRACEMEM_ENA_V  0x1
#define DPORT_PRO_TRACEMEM_ENA_S  0

#define DPORT_CACHE_MUX_MODE_REG          (DR_REG_DPORT_BASE + 0x064)
/* DPORT_CACHE_MUX_MODE : R/W ;bitpos:[1:0] ;default: 2'b0 ; */
/*description: */
#define DPORT_CACHE_MUX_MODE  0x00000003
#define DPORT_CACHE_MUX_MODE_M  ((DPORT_CACHE_MUX_MODE_V)<<(DPORT_CACHE_MUX_MODE_S))
#define DPORT_CACHE_MUX_MODE_V  0x3
#define DPORT_CACHE_MUX_MODE_S  0

#define DPORT_IMMU_PAGE_MODE_REG          (DR_REG_DPORT_BASE + 0x068)
/* DPORT_IMMU_PAGE_MODE : R/W ;bitpos:[2:1] ;default: 2'b0 ; */
/*description: */
#define DPORT_IMMU_PAGE_MODE  0x00000003
#define DPORT_IMMU_PAGE_MODE_M  ((DPORT_IMMU_PAGE_MODE_V)<<(DPORT_IMMU_PAGE_MODE_S))
#define DPORT_IMMU_PAGE_MODE_V  0x3
#define DPORT_IMMU_PAGE_MODE_S  1

#define DPORT_DMMU_PAGE_MODE_REG          (DR_REG_DPORT_BASE + 0x06C)
/* DPORT_DMMU_PAGE_MODE : R/W ;bitpos:[2:1] ;default: 2'b0 ; */
/*description: */
#define DPORT_DMMU_PAGE_MODE  0x00000003
#define DPORT_DMMU_PAGE_MODE_M  ((DPORT_DMMU_PAGE_MODE_V)<<(DPORT_DMMU_PAGE_MODE_S))
#define DPORT_DMMU_PAGE_MODE_V  0x3
#define DPORT_DMMU_PAGE_MODE_S  1

#define DPORT_CLOCK_GATE_REG          (DR_REG_DPORT_BASE + 0x070)
/* DPORT_CLK_EN : R/W ;bitpos:[0] ;default: 1'b1 ; */
/*description: */
#define DPORT_CLK_EN  (BIT(0))
#define DPORT_CLK_EN_M  (BIT(0))
#define DPORT_CLK_EN_V  0x1
#define DPORT_CLK_EN_S  0

#define DPORT_MEM_PD_MASK_REG          (DR_REG_DPORT_BASE + 0x074)
/* DPORT_LSLP_MEM_PD_MASK : R/W ;bitpos:[0] ;default: 1'b1 ; */
/*description: */
#define DPORT_LSLP_MEM_PD_MASK  (BIT(0))
#define DPORT_LSLP_MEM_PD_MASK_M  (BIT(0))
#define DPORT_LSLP_MEM_PD_MASK_V  0x1
#define DPORT_LSLP_MEM_PD_MASK_S  0

#define DPORT_ROM_PD_CTRL_REG          (DR_REG_DPORT_BASE + 0x078)
/* DPORT_SHARE_ROM_PD : R/W ;bitpos:[7:2] ;default: 6'h0 ; */
/*description: */
#define DPORT_SHARE_ROM_PD  0x0000003F
#define DPORT_SHARE_ROM_PD_M  ((DPORT_SHARE_ROM_PD_V)<<(DPORT_SHARE_ROM_PD_S))
#define DPORT_SHARE_ROM_PD_V  0x3F
#define DPORT_SHARE_ROM_PD_S  2
/* DPORT_APP_ROM_PD : R/W ;bitpos:[1] ;default: 1'h0 ; */
/*description: */
#define DPORT_APP_ROM_PD  (BIT(1))
#define DPORT_APP_ROM_PD_M  (BIT(1))
#define DPORT_APP_ROM_PD_V  0x1
#define DPORT_APP_ROM_PD_S  1
/* DPORT_PRO_ROM_PD : R/W ;bitpos:[0] ;default: 1'h0 ; */
/*description: */
#define DPORT_PRO_ROM_PD  (BIT(0))
#define DPORT_PRO_ROM_PD_M  (BIT(0))
#define DPORT_PRO_ROM_PD_V  0x1
#define DPORT_PRO_ROM_PD_S  0

#define DPORT_ROM_FO_CTRL_REG          (DR_REG_DPORT_BASE + 0x07C)
/* DPORT_SHARE_ROM_FO : R/W ;bitpos:[7:2] ;default: 6'h0 ; */
/*description: */
#define DPORT_SHARE_ROM_FO  0x0000003F
#define DPORT_SHARE_ROM_FO_M  ((DPORT_SHARE_ROM_FO_V)<<(DPORT_SHARE_ROM_FO_S))
#define DPORT_SHARE_ROM_FO_V  0x3F
#define DPORT_SHARE_ROM_FO_S  2
/* DPORT_APP_ROM_FO : R/W ;bitpos:[1] ;default: 1'h1 ; */
/*description: */
#define DPORT_APP_ROM_FO  (BIT(1))
#define DPORT_APP_ROM_FO_M  (BIT(1))
#define DPORT_APP_ROM_FO_V  0x1
#define DPORT_APP_ROM_FO_S  1
/* DPORT_PRO_ROM_FO : R/W ;bitpos:[0] ;default: 1'h1 ; */
/*description: */
#define DPORT_PRO_ROM_FO  (BIT(0))
#define DPORT_PRO_ROM_FO_M  (BIT(0))
#define DPORT_PRO_ROM_FO_V  0x1
#define DPORT_PRO_ROM_FO_S  0

#define DPORT_SRAM_PD_CTRL_0_REG          (DR_REG_DPORT_BASE + 0x080)
/* DPORT_SRAM_PD_0 : R/W ;bitpos:[31:0] ;default: 32'h0 ; */
/*description: */
#define DPORT_SRAM_PD_0  0xFFFFFFFF
#define DPORT_SRAM_PD_0_M  ((DPORT_SRAM_PD_0_V)<<(DPORT_SRAM_PD_0_S))
#define DPORT_SRAM_PD_0_V  0xFFFFFFFF
#define DPORT_SRAM_PD_0_S  0

#define DPORT_SRAM_PD_CTRL_1_REG          (DR_REG_DPORT_BASE + 0x084)
/* DPORT_SRAM_PD_1 : R/W ;bitpos:[0] ;default: 1'h0 ; */
/*description: */
#define DPORT_SRAM_PD_1  (BIT(0))
#define DPORT_SRAM_PD_1_M  (BIT(0))
#define DPORT_SRAM_PD_1_V  0x1
#define DPORT_SRAM_PD_1_S  0

#define DPORT_SRAM_FO_CTRL_0_REG          (DR_REG_DPORT_BASE + 0x088)
/* DPORT_SRAM_FO_0 : R/W ;bitpos:[31:0] ;default: 32'hffffffff ; */
/*description: */
#define DPORT_SRAM_FO_0  0xFFFFFFFF
#define DPORT_SRAM_FO_0_M  ((DPORT_SRAM_FO_0_V)<<(DPORT_SRAM_FO_0_S))
#define DPORT_SRAM_FO_0_V  0xFFFFFFFF
#define DPORT_SRAM_FO_0_S  0

#define DPORT_SRAM_FO_CTRL_1_REG          (DR_REG_DPORT_BASE + 0x08C)
/* DPORT_SRAM_FO_1 : R/W ;bitpos:[0] ;default: 1'h1 ; */
/*description: */
#define DPORT_SRAM_FO_1  (BIT(0))
#define DPORT_SRAM_FO_1_M  (BIT(0))
#define DPORT_SRAM_FO_1_V  0x1
#define DPORT_SRAM_FO_1_S  0

#define DPORT_IRAM_DRAM_AHB_SEL_REG          (DR_REG_DPORT_BASE + 0x090)
/* DPORT_MAC_DUMP_MODE : R/W ;bitpos:[6:5] ;default: 2'h0 ; */
/*description: */
#define DPORT_MAC_DUMP_MODE  0x00000003
#define DPORT_MAC_DUMP_MODE_M  ((DPORT_MAC_DUMP_MODE_V)<<(DPORT_MAC_DUMP_MODE_S))
#define DPORT_MAC_DUMP_MODE_V  0x3
#define DPORT_MAC_DUMP_MODE_S  5
/* DPORT_MASK_AHB : R/W ;bitpos:[4] ;default: 1'b0 ; */
/*description: */
#define DPORT_MASK_AHB  (BIT(4))
#define DPORT_MASK_AHB_M  (BIT(4))
#define DPORT_MASK_AHB_V  0x1
#define DPORT_MASK_AHB_S  4
/* DPORT_MASK_APP_DRAM : R/W ;bitpos:[3] ;default: 1'b0 ; */
/*description: */
#define DPORT_MASK_APP_DRAM  (BIT(3))
#define DPORT_MASK_APP_DRAM_M  (BIT(3))
#define DPORT_MASK_APP_DRAM_V  0x1
#define DPORT_MASK_APP_DRAM_S  3
/* DPORT_MASK_PRO_DRAM : R/W ;bitpos:[2] ;default: 1'b0 ; */
/*description: */
#define DPORT_MASK_PRO_DRAM  (BIT(2))
#define DPORT_MASK_PRO_DRAM_M  (BIT(2))
#define DPORT_MASK_PRO_DRAM_V  0x1
#define DPORT_MASK_PRO_DRAM_S  2
/* DPORT_MASK_APP_IRAM : R/W ;bitpos:[1] ;default: 1'b0 ; */
/*description: */
#define DPORT_MASK_APP_IRAM  (BIT(1))
#define DPORT_MASK_APP_IRAM_M  (BIT(1))
#define DPORT_MASK_APP_IRAM_V  0x1
#define DPORT_MASK_APP_IRAM_S  1
/* DPORT_MASK_PRO_IRAM : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: */
#define DPORT_MASK_PRO_IRAM  (BIT(0))
#define DPORT_MASK_PRO_IRAM_M  (BIT(0))
#define DPORT_MASK_PRO_IRAM_V  0x1
#define DPORT_MASK_PRO_IRAM_S  0

#define DPORT_TAG_FO_CTRL_REG          (DR_REG_DPORT_BASE + 0x094)
/* DPORT_APP_CACHE_TAG_PD : R/W ;bitpos:[9] ;default: 1'b0 ; */
/*description: */
#define DPORT_APP_CACHE_TAG_PD  (BIT(9))
#define DPORT_APP_CACHE_TAG_PD_M  (BIT(9))
#define DPORT_APP_CACHE_TAG_PD_V  0x1
#define DPORT_APP_CACHE_TAG_PD_S  9
/* DPORT_APP_CACHE_TAG_FORCE_ON : R/W ;bitpos:[8] ;default: 1'b1 ; */
/*description: */
#define DPORT_APP_CACHE_TAG_FORCE_ON  (BIT(8))
#define DPORT_APP_CACHE_TAG_FORCE_ON_M  (BIT(8))
#define DPORT_APP_CACHE_TAG_FORCE_ON_V  0x1
#define DPORT_APP_CACHE_TAG_FORCE_ON_S  8
/* DPORT_PRO_CACHE_TAG_PD : R/W ;bitpos:[1] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_CACHE_TAG_PD  (BIT(1))
#define DPORT_PRO_CACHE_TAG_PD_M  (BIT(1))
#define DPORT_PRO_CACHE_TAG_PD_V  0x1
#define DPORT_PRO_CACHE_TAG_PD_S  1
/* DPORT_PRO_CACHE_TAG_FORCE_ON : R/W ;bitpos:[0] ;default: 1'b1 ; */
/*description: */
#define DPORT_PRO_CACHE_TAG_FORCE_ON  (BIT(0))
#define DPORT_PRO_CACHE_TAG_FORCE_ON_M  (BIT(0))
#define DPORT_PRO_CACHE_TAG_FORCE_ON_V  0x1
#define DPORT_PRO_CACHE_TAG_FORCE_ON_S  0

#define DPORT_AHB_LITE_MASK_REG          (DR_REG_DPORT_BASE + 0x098)
/* DPORT_AHB_LITE_SDHOST_PID_REG : R/W ;bitpos:[13:11] ;default: 3'b0 ; */
/*description: */
#define DPORT_AHB_LITE_SDHOST_PID_REG  0x00000007
#define DPORT_AHB_LITE_SDHOST_PID_REG_M  ((DPORT_AHB_LITE_SDHOST_PID_REG_V)<<(DPORT_AHB_LITE_SDHOST_PID_REG_S))
#define DPORT_AHB_LITE_SDHOST_PID_REG_V  0x7
#define DPORT_AHB_LITE_SDHOST_PID_REG_S  11
/* DPORT_AHB_LITE_MASK_APPDPORT : R/W ;bitpos:[10] ;default: 1'b0 ; */
/*description: */
#define DPORT_AHB_LITE_MASK_APPDPORT  (BIT(10))
#define DPORT_AHB_LITE_MASK_APPDPORT_M  (BIT(10))
#define DPORT_AHB_LITE_MASK_APPDPORT_V  0x1
#define DPORT_AHB_LITE_MASK_APPDPORT_S  10
/* DPORT_AHB_LITE_MASK_PRODPORT : R/W ;bitpos:[9] ;default: 1'b0 ; */
/*description: */
#define DPORT_AHB_LITE_MASK_PRODPORT  (BIT(9))
#define DPORT_AHB_LITE_MASK_PRODPORT_M  (BIT(9))
#define DPORT_AHB_LITE_MASK_PRODPORT_V  0x1
#define DPORT_AHB_LITE_MASK_PRODPORT_S  9
/* DPORT_AHB_LITE_MASK_SDIO : R/W ;bitpos:[8] ;default: 1'b0 ; */
/*description: */
#define DPORT_AHB_LITE_MASK_SDIO  (BIT(8))
#define DPORT_AHB_LITE_MASK_SDIO_M  (BIT(8))
#define DPORT_AHB_LITE_MASK_SDIO_V  0x1
#define DPORT_AHB_LITE_MASK_SDIO_S  8
/* DPORT_AHB_LITE_MASK_APP : R/W ;bitpos:[4] ;default: 1'b0 ; */
/*description: */
#define DPORT_AHB_LITE_MASK_APP  (BIT(4))
#define DPORT_AHB_LITE_MASK_APP_M  (BIT(4))
#define DPORT_AHB_LITE_MASK_APP_V  0x1
#define DPORT_AHB_LITE_MASK_APP_S  4
/* DPORT_AHB_LITE_MASK_PRO : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: */
#define DPORT_AHB_LITE_MASK_PRO  (BIT(0))
#define DPORT_AHB_LITE_MASK_PRO_M  (BIT(0))
#define DPORT_AHB_LITE_MASK_PRO_V  0x1
#define DPORT_AHB_LITE_MASK_PRO_S  0

#define DPORT_AHB_MPU_TABLE_0_REG          (DR_REG_DPORT_BASE + 0x09C)
/* DPORT_AHB_ACCESS_GRANT_0 : R/W ;bitpos:[31:0] ;default: 32'hffffffff ; */
/*description: */
#define DPORT_AHB_ACCESS_GRANT_0  0xFFFFFFFF
#define DPORT_AHB_ACCESS_GRANT_0_M  ((DPORT_AHB_ACCESS_GRANT_0_V)<<(DPORT_AHB_ACCESS_GRANT_0_S))
#define DPORT_AHB_ACCESS_GRANT_0_V  0xFFFFFFFF
#define DPORT_AHB_ACCESS_GRANT_0_S  0

#define DPORT_AHB_MPU_TABLE_1_REG          (DR_REG_DPORT_BASE + 0x0A0)
/* DPORT_AHB_ACCESS_GRANT_1 : R/W ;bitpos:[8:0] ;default: 9'h1ff ; */
/*description: */
#define DPORT_AHB_ACCESS_GRANT_1  0x000001FF
#define DPORT_AHB_ACCESS_GRANT_1_M  ((DPORT_AHB_ACCESS_GRANT_1_V)<<(DPORT_AHB_ACCESS_GRANT_1_S))
#define DPORT_AHB_ACCESS_GRANT_1_V  0x1FF
#define DPORT_AHB_ACCESS_GRANT_1_S  0

#define DPORT_PERIP_CLK_EN_REG          (DR_REG_DPORT_BASE + 0x0A4)
/* DPORT_SYSTIMER_CLK_EN : R/W ;bitpos:[29] ;default: 1'b1 ; */
/*description: */
#define DPORT_SYSTIMER_CLK_EN  (BIT(29))
#define DPORT_SYSTIMER_CLK_EN_M  (BIT(29))
#define DPORT_SYSTIMER_CLK_EN_V  0x1
#define DPORT_SYSTIMER_CLK_EN_S  29
/* DPORT_APB_SARADC_CLK_EN : R/W ;bitpos:[28] ;default: 1'b1 ; */
/*description: */
#define DPORT_APB_SARADC_CLK_EN  (BIT(28))
#define DPORT_APB_SARADC_CLK_EN_M  (BIT(28))
#define DPORT_APB_SARADC_CLK_EN_V  0x1
#define DPORT_APB_SARADC_CLK_EN_S  28
/* DPORT_SPI_DMA1_CLK_EN : R/W ;bitpos:[27] ;default: 1'b1 ; */
/*description: */
#define DPORT_SPI_DMA1_CLK_EN  (BIT(27))
#define DPORT_SPI_DMA1_CLK_EN_M  (BIT(27))
#define DPORT_SPI_DMA1_CLK_EN_V  0x1
#define DPORT_SPI_DMA1_CLK_EN_S  27
/* DPORT_PWM3_CLK_EN : R/W ;bitpos:[26] ;default: 1'b0 ; */
/*description: */
#define DPORT_PWM3_CLK_EN  (BIT(26))
#define DPORT_PWM3_CLK_EN_M  (BIT(26))
#define DPORT_PWM3_CLK_EN_V  0x1
#define DPORT_PWM3_CLK_EN_S  26
/* DPORT_PWM2_CLK_EN : R/W ;bitpos:[25] ;default: 1'b0 ; */
/*description: */
#define DPORT_PWM2_CLK_EN  (BIT(25))
#define DPORT_PWM2_CLK_EN_M  (BIT(25))
#define DPORT_PWM2_CLK_EN_V  0x1
#define DPORT_PWM2_CLK_EN_S  25
/* DPORT_UART_MEM_CLK_EN : R/W ;bitpos:[24] ;default: 1'b1 ; */
/*description: */
#define DPORT_UART_MEM_CLK_EN  (BIT(24))
#define DPORT_UART_MEM_CLK_EN_M  (BIT(24))
#define DPORT_UART_MEM_CLK_EN_V  0x1
#define DPORT_UART_MEM_CLK_EN_S  24
/* DPORT_UART2_CLK_EN : R/W ;bitpos:[23] ;default: 1'b1 ; */
/*description: */
#define DPORT_UART2_CLK_EN  (BIT(23))
#define DPORT_UART2_CLK_EN_M  (BIT(23))
#define DPORT_UART2_CLK_EN_V  0x1
#define DPORT_UART2_CLK_EN_S  23
/* DPORT_SPI_DMA0_CLK_EN : R/W ;bitpos:[22] ;default: 1'b1 ; */
/*description: */
#define DPORT_SPI_DMA0_CLK_EN  (BIT(22))
#define DPORT_SPI_DMA0_CLK_EN_M  (BIT(22))
#define DPORT_SPI_DMA0_CLK_EN_V  0x1
#define DPORT_SPI_DMA0_CLK_EN_S  22
/* DPORT_I2S1_CLK_EN : R/W ;bitpos:[21] ;default: 1'b0 ; */
/*description: */
#define DPORT_I2S1_CLK_EN  (BIT(21))
#define DPORT_I2S1_CLK_EN_M  (BIT(21))
#define DPORT_I2S1_CLK_EN_V  0x1
#define DPORT_I2S1_CLK_EN_S  21
/* DPORT_PWM1_CLK_EN : R/W ;bitpos:[20] ;default: 1'b0 ; */
/*description: */
#define DPORT_PWM1_CLK_EN  (BIT(20))
#define DPORT_PWM1_CLK_EN_M  (BIT(20))
#define DPORT_PWM1_CLK_EN_V  0x1
#define DPORT_PWM1_CLK_EN_S  20
/* DPORT_CAN_CLK_EN : R/W ;bitpos:[19] ;default: 1'b0 ; */
/*description: */
#define DPORT_CAN_CLK_EN  (BIT(19))
#define DPORT_CAN_CLK_EN_M  (BIT(19))
#define DPORT_CAN_CLK_EN_V  0x1
#define DPORT_CAN_CLK_EN_S  19
/* DPORT_I2C_EXT1_CLK_EN : R/W ;bitpos:[18] ;default: 1'b0 ; */
/*description: */
#define DPORT_I2C_EXT1_CLK_EN  (BIT(18))
#define DPORT_I2C_EXT1_CLK_EN_M  (BIT(18))
#define DPORT_I2C_EXT1_CLK_EN_V  0x1
#define DPORT_I2C_EXT1_CLK_EN_S  18
/* DPORT_PWM0_CLK_EN : R/W ;bitpos:[17] ;default: 1'b0 ; */
/*description: */
#define DPORT_PWM0_CLK_EN  (BIT(17))
#define DPORT_PWM0_CLK_EN_M  (BIT(17))
#define DPORT_PWM0_CLK_EN_V  0x1
#define DPORT_PWM0_CLK_EN_S  17
/* DPORT_SPI3_CLK_EN : R/W ;bitpos:[16] ;default: 1'b1 ; */
/*description: */
#define DPORT_SPI3_CLK_EN  (BIT(16))
#define DPORT_SPI3_CLK_EN_M  (BIT(16))
#define DPORT_SPI3_CLK_EN_V  0x1
#define DPORT_SPI3_CLK_EN_S  16
/* DPORT_TIMERGROUP1_CLK_EN : R/W ;bitpos:[15] ;default: 1'b1 ; */
/*description: */
#define DPORT_TIMERGROUP1_CLK_EN  (BIT(15))
#define DPORT_TIMERGROUP1_CLK_EN_M  (BIT(15))
#define DPORT_TIMERGROUP1_CLK_EN_V  0x1
#define DPORT_TIMERGROUP1_CLK_EN_S  15
/* DPORT_EFUSE_CLK_EN : R/W ;bitpos:[14] ;default: 1'b1 ; */
/*description: */
#define DPORT_EFUSE_CLK_EN  (BIT(14))
#define DPORT_EFUSE_CLK_EN_M  (BIT(14))
#define DPORT_EFUSE_CLK_EN_V  0x1
#define DPORT_EFUSE_CLK_EN_S  14
/* DPORT_TIMERGROUP_CLK_EN : R/W ;bitpos:[13] ;default: 1'b1 ; */
/*description: */
#define DPORT_TIMERGROUP_CLK_EN  (BIT(13))
#define DPORT_TIMERGROUP_CLK_EN_M  (BIT(13))
#define DPORT_TIMERGROUP_CLK_EN_V  0x1
#define DPORT_TIMERGROUP_CLK_EN_S  13
/* DPORT_UHCI1_CLK_EN : R/W ;bitpos:[12] ;default: 1'b0 ; */
/*description: */
#define DPORT_UHCI1_CLK_EN  (BIT(12))
#define DPORT_UHCI1_CLK_EN_M  (BIT(12))
#define DPORT_UHCI1_CLK_EN_V  0x1
#define DPORT_UHCI1_CLK_EN_S  12
/* DPORT_LEDC_CLK_EN : R/W ;bitpos:[11] ;default: 1'b0 ; */
/*description: */
#define DPORT_LEDC_CLK_EN  (BIT(11))
#define DPORT_LEDC_CLK_EN_M  (BIT(11))
#define DPORT_LEDC_CLK_EN_V  0x1
#define DPORT_LEDC_CLK_EN_S  11
/* DPORT_PCNT_CLK_EN : R/W ;bitpos:[10] ;default: 1'b0 ; */
/*description: */
#define DPORT_PCNT_CLK_EN  (BIT(10))
#define DPORT_PCNT_CLK_EN_M  (BIT(10))
#define DPORT_PCNT_CLK_EN_V  0x1
#define DPORT_PCNT_CLK_EN_S  10
/* DPORT_RMT_CLK_EN : R/W ;bitpos:[9] ;default: 1'b0 ; */
/*description: */
#define DPORT_RMT_CLK_EN  (BIT(9))
#define DPORT_RMT_CLK_EN_M  (BIT(9))
#define DPORT_RMT_CLK_EN_V  0x1
#define DPORT_RMT_CLK_EN_S  9
/* DPORT_UHCI0_CLK_EN : R/W ;bitpos:[8] ;default: 1'b0 ; */
/*description: */
#define DPORT_UHCI0_CLK_EN  (BIT(8))
#define DPORT_UHCI0_CLK_EN_M  (BIT(8))
#define DPORT_UHCI0_CLK_EN_V  0x1
#define DPORT_UHCI0_CLK_EN_S  8
/* DPORT_I2C_EXT0_CLK_EN : R/W ;bitpos:[7] ;default: 1'b0 ; */
/*description: */
#define DPORT_I2C_EXT0_CLK_EN  (BIT(7))
#define DPORT_I2C_EXT0_CLK_EN_M  (BIT(7))
#define DPORT_I2C_EXT0_CLK_EN_V  0x1
#define DPORT_I2C_EXT0_CLK_EN_S  7
/* DPORT_SPI2_CLK_EN : R/W ;bitpos:[6] ;default: 1'b1 ; */
/*description: */
#define DPORT_SPI2_CLK_EN  (BIT(6))
#define DPORT_SPI2_CLK_EN_M  (BIT(6))
#define DPORT_SPI2_CLK_EN_V  0x1
#define DPORT_SPI2_CLK_EN_S  6
/* DPORT_UART1_CLK_EN : R/W ;bitpos:[5] ;default: 1'b1 ; */
/*description: */
#define DPORT_UART1_CLK_EN  (BIT(5))
#define DPORT_UART1_CLK_EN_M  (BIT(5))
#define DPORT_UART1_CLK_EN_V  0x1
#define DPORT_UART1_CLK_EN_S  5
/* DPORT_I2S0_CLK_EN : R/W ;bitpos:[4] ;default: 1'b0 ; */
/*description: */
#define DPORT_I2S0_CLK_EN  (BIT(4))
#define DPORT_I2S0_CLK_EN_M  (BIT(4))
#define DPORT_I2S0_CLK_EN_V  0x1
#define DPORT_I2S0_CLK_EN_S  4
/* DPORT_WDG_CLK_EN : R/W ;bitpos:[3] ;default: 1'b1 ; */
/*description: */
#define DPORT_WDG_CLK_EN  (BIT(3))
#define DPORT_WDG_CLK_EN_M  (BIT(3))
#define DPORT_WDG_CLK_EN_V  0x1
#define DPORT_WDG_CLK_EN_S  3
/* DPORT_UART_CLK_EN : R/W ;bitpos:[2] ;default: 1'b1 ; */
/*description: */
#define DPORT_UART_CLK_EN  (BIT(2))
#define DPORT_UART_CLK_EN_M  (BIT(2))
#define DPORT_UART_CLK_EN_V  0x1
#define DPORT_UART_CLK_EN_S  2
/* DPORT_SPI01_CLK_EN : R/W ;bitpos:[1] ;default: 1'b1 ; */
/*description: */
#define DPORT_SPI01_CLK_EN  (BIT(1))
#define DPORT_SPI01_CLK_EN_M  (BIT(1))
#define DPORT_SPI01_CLK_EN_V  0x1
#define DPORT_SPI01_CLK_EN_S  1
/* DPORT_TIMERS_CLK_EN : R/W ;bitpos:[0] ;default: 1'b1 ; */
/*description: */
#define DPORT_TIMERS_CLK_EN  (BIT(0))
#define DPORT_TIMERS_CLK_EN_M  (BIT(0))
#define DPORT_TIMERS_CLK_EN_V  0x1
#define DPORT_TIMERS_CLK_EN_S  0

#define DPORT_PERIP_RST_EN_REG          (DR_REG_DPORT_BASE + 0x0A8)
/* DPORT_SYSTIMER_RST : R/W ;bitpos:[29] ;default: 1'b0 ; */
/*description: */
#define DPORT_SYSTIMER_RST  (BIT(29))
#define DPORT_SYSTIMER_RST_M  (BIT(29))
#define DPORT_SYSTIMER_RST_V  0x1
#define DPORT_SYSTIMER_RST_S  29
/* DPORT_APB_SARADC_RST : R/W ;bitpos:[28] ;default: 1'b0 ; */
/*description: */
#define DPORT_APB_SARADC_RST  (BIT(28))
#define DPORT_APB_SARADC_RST_M  (BIT(28))
#define DPORT_APB_SARADC_RST_V  0x1
#define DPORT_APB_SARADC_RST_S  28
/* DPORT_SPI_DMA1_RST : R/W ;bitpos:[27] ;default: 1'b0 ; */
/*description: */
#define DPORT_SPI_DMA1_RST  (BIT(27))
#define DPORT_SPI_DMA1_RST_M  (BIT(27))
#define DPORT_SPI_DMA1_RST_V  0x1
#define DPORT_SPI_DMA1_RST_S  27
/* DPORT_PWM3_RST : R/W ;bitpos:[26] ;default: 1'b0 ; */
/*description: */
#define DPORT_PWM3_RST  (BIT(26))
#define DPORT_PWM3_RST_M  (BIT(26))
#define DPORT_PWM3_RST_V  0x1
#define DPORT_PWM3_RST_S  26
/* DPORT_PWM2_RST : R/W ;bitpos:[25] ;default: 1'b0 ; */
/*description: */
#define DPORT_PWM2_RST  (BIT(25))
#define DPORT_PWM2_RST_M  (BIT(25))
#define DPORT_PWM2_RST_V  0x1
#define DPORT_PWM2_RST_S  25
/* DPORT_UART_MEM_RST : R/W ;bitpos:[24] ;default: 1'b0 ; */
/*description: */
#define DPORT_UART_MEM_RST  (BIT(24))
#define DPORT_UART_MEM_RST_M  (BIT(24))
#define DPORT_UART_MEM_RST_V  0x1
#define DPORT_UART_MEM_RST_S  24
/* DPORT_UART2_RST : R/W ;bitpos:[23] ;default: 1'b0 ; */
/*description: */
#define DPORT_UART2_RST  (BIT(23))
#define DPORT_UART2_RST_M  (BIT(23))
#define DPORT_UART2_RST_V  0x1
#define DPORT_UART2_RST_S  23
/* DPORT_SPI_DMA0_RST : R/W ;bitpos:[22] ;default: 1'b0 ; */
/*description: */
#define DPORT_SPI_DMA0_RST  (BIT(22))
#define DPORT_SPI_DMA0_RST_M  (BIT(22))
#define DPORT_SPI_DMA0_RST_V  0x1
#define DPORT_SPI_DMA0_RST_S  22
/* DPORT_I2S1_RST : R/W ;bitpos:[21] ;default: 1'b0 ; */
/*description: */
#define DPORT_I2S1_RST  (BIT(21))
#define DPORT_I2S1_RST_M  (BIT(21))
#define DPORT_I2S1_RST_V  0x1
#define DPORT_I2S1_RST_S  21
/* DPORT_PWM1_RST : R/W ;bitpos:[20] ;default: 1'b0 ; */
/*description: */
#define DPORT_PWM1_RST  (BIT(20))
#define DPORT_PWM1_RST_M  (BIT(20))
#define DPORT_PWM1_RST_V  0x1
#define DPORT_PWM1_RST_S  20
/* DPORT_CAN_RST : R/W ;bitpos:[19] ;default: 1'b0 ; */
/*description: */
#define DPORT_CAN_RST  (BIT(19))
#define DPORT_CAN_RST_M  (BIT(19))
#define DPORT_CAN_RST_V  0x1
#define DPORT_CAN_RST_S  19
/* DPORT_I2C_EXT1_RST : R/W ;bitpos:[18] ;default: 1'b0 ; */
/*description: */
#define DPORT_I2C_EXT1_RST  (BIT(18))
#define DPORT_I2C_EXT1_RST_M  (BIT(18))
#define DPORT_I2C_EXT1_RST_V  0x1
#define DPORT_I2C_EXT1_RST_S  18
/* DPORT_PWM0_RST : R/W ;bitpos:[17] ;default: 1'b0 ; */
/*description: */
#define DPORT_PWM0_RST  (BIT(17))
#define DPORT_PWM0_RST_M  (BIT(17))
#define DPORT_PWM0_RST_V  0x1
#define DPORT_PWM0_RST_S  17
/* DPORT_SPI3_RST : R/W ;bitpos:[16] ;default: 1'b0 ; */
/*description: */
#define DPORT_SPI3_RST  (BIT(16))
#define DPORT_SPI3_RST_M  (BIT(16))
#define DPORT_SPI3_RST_V  0x1
#define DPORT_SPI3_RST_S  16
/* DPORT_TIMERGROUP1_RST : R/W ;bitpos:[15] ;default: 1'b0 ; */
/*description: */
#define DPORT_TIMERGROUP1_RST  (BIT(15))
#define DPORT_TIMERGROUP1_RST_M  (BIT(15))
#define DPORT_TIMERGROUP1_RST_V  0x1
#define DPORT_TIMERGROUP1_RST_S  15
/* DPORT_EFUSE_RST : R/W ;bitpos:[14] ;default: 1'b0 ; */
/*description: */
#define DPORT_EFUSE_RST  (BIT(14))
#define DPORT_EFUSE_RST_M  (BIT(14))
#define DPORT_EFUSE_RST_V  0x1
#define DPORT_EFUSE_RST_S  14
/* DPORT_TIMERGROUP_RST : R/W ;bitpos:[13] ;default: 1'b0 ; */
/*description: */
#define DPORT_TIMERGROUP_RST  (BIT(13))
#define DPORT_TIMERGROUP_RST_M  (BIT(13))
#define DPORT_TIMERGROUP_RST_V  0x1
#define DPORT_TIMERGROUP_RST_S  13
/* DPORT_UHCI1_RST : R/W ;bitpos:[12] ;default: 1'b0 ; */
/*description: */
#define DPORT_UHCI1_RST  (BIT(12))
#define DPORT_UHCI1_RST_M  (BIT(12))
#define DPORT_UHCI1_RST_V  0x1
#define DPORT_UHCI1_RST_S  12
/* DPORT_LEDC_RST : R/W ;bitpos:[11] ;default: 1'b0 ; */
/*description: */
#define DPORT_LEDC_RST  (BIT(11))
#define DPORT_LEDC_RST_M  (BIT(11))
#define DPORT_LEDC_RST_V  0x1
#define DPORT_LEDC_RST_S  11
/* DPORT_PCNT_RST : R/W ;bitpos:[10] ;default: 1'b0 ; */
/*description: */
#define DPORT_PCNT_RST  (BIT(10))
#define DPORT_PCNT_RST_M  (BIT(10))
#define DPORT_PCNT_RST_V  0x1
#define DPORT_PCNT_RST_S  10
/* DPORT_RMT_RST : R/W ;bitpos:[9] ;default: 1'b0 ; */
/*description: */
#define DPORT_RMT_RST  (BIT(9))
#define DPORT_RMT_RST_M  (BIT(9))
#define DPORT_RMT_RST_V  0x1
#define DPORT_RMT_RST_S  9
/* DPORT_UHCI0_RST : R/W ;bitpos:[8] ;default: 1'b0 ; */
/*description: */
#define DPORT_UHCI0_RST  (BIT(8))
#define DPORT_UHCI0_RST_M  (BIT(8))
#define DPORT_UHCI0_RST_V  0x1
#define DPORT_UHCI0_RST_S  8
/* DPORT_I2C_EXT0_RST : R/W ;bitpos:[7] ;default: 1'b0 ; */
/*description: */
#define DPORT_I2C_EXT0_RST  (BIT(7))
#define DPORT_I2C_EXT0_RST_M  (BIT(7))
#define DPORT_I2C_EXT0_RST_V  0x1
#define DPORT_I2C_EXT0_RST_S  7
/* DPORT_SPI2_RST : R/W ;bitpos:[6] ;default: 1'b0 ; */
/*description: */
#define DPORT_SPI2_RST  (BIT(6))
#define DPORT_SPI2_RST_M  (BIT(6))
#define DPORT_SPI2_RST_V  0x1
#define DPORT_SPI2_RST_S  6
/* DPORT_UART1_RST : R/W ;bitpos:[5] ;default: 1'b0 ; */
/*description: */
#define DPORT_UART1_RST  (BIT(5))
#define DPORT_UART1_RST_M  (BIT(5))
#define DPORT_UART1_RST_V  0x1
#define DPORT_UART1_RST_S  5
/* DPORT_I2S0_RST : R/W ;bitpos:[4] ;default: 1'b0 ; */
/*description: */
#define DPORT_I2S0_RST  (BIT(4))
#define DPORT_I2S0_RST_M  (BIT(4))
#define DPORT_I2S0_RST_V  0x1
#define DPORT_I2S0_RST_S  4
/* DPORT_WDG_RST : R/W ;bitpos:[3] ;default: 1'b0 ; */
/*description: */
#define DPORT_WDG_RST  (BIT(3))
#define DPORT_WDG_RST_M  (BIT(3))
#define DPORT_WDG_RST_V  0x1
#define DPORT_WDG_RST_S  3
/* DPORT_UART_RST : R/W ;bitpos:[2] ;default: 1'b0 ; */
/*description: */
#define DPORT_UART_RST  (BIT(2))
#define DPORT_UART_RST_M  (BIT(2))
#define DPORT_UART_RST_V  0x1
#define DPORT_UART_RST_S  2
/* DPORT_SPI01_RST : R/W ;bitpos:[1] ;default: 1'b0 ; */
/*description: */
#define DPORT_SPI01_RST  (BIT(1))
#define DPORT_SPI01_RST_M  (BIT(1))
#define DPORT_SPI01_RST_V  0x1
#define DPORT_SPI01_RST_S  1
/* DPORT_TIMERS_RST : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: */
#define DPORT_TIMERS_RST  (BIT(0))
#define DPORT_TIMERS_RST_M  (BIT(0))
#define DPORT_TIMERS_RST_V  0x1
#define DPORT_TIMERS_RST_S  0

#define DPORT_SLAVE_SPI_CONFIG_REG          (DR_REG_DPORT_BASE + 0x0AC)
/* DPORT_SPI_DECRYPT_ENABLE : R/W ;bitpos:[12] ;default: 1'b0 ; */
/*description: */
#define DPORT_SPI_DECRYPT_ENABLE  (BIT(12))
#define DPORT_SPI_DECRYPT_ENABLE_M  (BIT(12))
#define DPORT_SPI_DECRYPT_ENABLE_V  0x1
#define DPORT_SPI_DECRYPT_ENABLE_S  12
/* DPORT_SPI_ENCRYPT_ENABLE : R/W ;bitpos:[8] ;default: 1'b0 ; */
/*description: */
#define DPORT_SPI_ENCRYPT_ENABLE  (BIT(8))
#define DPORT_SPI_ENCRYPT_ENABLE_M  (BIT(8))
#define DPORT_SPI_ENCRYPT_ENABLE_V  0x1
#define DPORT_SPI_ENCRYPT_ENABLE_S  8
/* DPORT_SLAVE_SPI_MASK_APP : R/W ;bitpos:[4] ;default: 1'b0 ; */
/*description: */
#define DPORT_SLAVE_SPI_MASK_APP  (BIT(4))
#define DPORT_SLAVE_SPI_MASK_APP_M  (BIT(4))
#define DPORT_SLAVE_SPI_MASK_APP_V  0x1
#define DPORT_SLAVE_SPI_MASK_APP_S  4
/* DPORT_SLAVE_SPI_MASK_PRO : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: */
#define DPORT_SLAVE_SPI_MASK_PRO  (BIT(0))
#define DPORT_SLAVE_SPI_MASK_PRO_M  (BIT(0))
#define DPORT_SLAVE_SPI_MASK_PRO_V  0x1
#define DPORT_SLAVE_SPI_MASK_PRO_S  0

#define DPORT_WIFI_CLK_EN_REG          (DR_REG_DPORT_BASE + 0x0B0)
/* DPORT_WIFI_CLK_EN : R/W ;bitpos:[31:0] ;default: 32'hfffce030 ; */
/*description: */
#define DPORT_WIFI_CLK_EN  0xFFFFFFFF
#define DPORT_WIFI_CLK_EN_M  ((DPORT_WIFI_CLK_EN_V)<<(DPORT_WIFI_CLK_EN_S))
#define DPORT_WIFI_CLK_EN_V  0xFFFFFFFF
#define DPORT_WIFI_CLK_EN_S  0

/* Mask for all Wifi clock bits - 0, 1, 2, 3, 6, 7, 8, 9, 10, 15 */
#define DPORT_WIFI_CLK_WIFI_EN  0x000007cf
#define DPORT_WIFI_CLK_WIFI_EN_M  ((DPORT_WIFI_CLK_WIFI_EN_V)<<(DPORT_WIFI_CLK_WIFI_EN_S))
#define DPORT_WIFI_CLK_WIFI_EN_V  0x7cf
#define DPORT_WIFI_CLK_WIFI_EN_S  0
/* Mask for all Bluetooth clock bits - 11, 16, 17 */
#define DPORT_WIFI_CLK_BT_EN  0x61
#define DPORT_WIFI_CLK_BT_EN_M  ((DPORT_WIFI_CLK_BT_EN_V)<<(DPORT_WIFI_CLK_BT_EN_S))
#define DPORT_WIFI_CLK_BT_EN_V  0x61
#define DPORT_WIFI_CLK_BT_EN_S  11
/* Mask for clock bits used by both WIFI and Bluetooth, bit 0, 3, 6, 7, 8, 9 */
#define DPORT_WIFI_CLK_WIFI_BT_COMMON_M 0x000003c9
//bluetooth baseband bit11
#define DPORT_BT_BASEBAND_EN  BIT(11)
//bluetooth LC bit16 and bit17
#define DPORT_BT_LC_EN  (BIT(16)|BIT(17))

/* Remaining single bit clock masks */
#define DPORT_WIFI_CLK_SDIOSLAVE_EN  BIT(4)
#define DPORT_WIFI_CLK_UNUSED_BIT5  BIT(5)
#define DPORT_WIFI_CLK_UNUSED_BIT12  BIT(12)
#define DPORT_WIFI_CLK_SDIO_HOST_EN  BIT(13)
#define DPORT_WIFI_CLK_EMAC_EN  BIT(14)
#define DPORT_WIFI_CLK_RNG_EN  BIT(15)


#define DPORT_CORE_RST_EN_REG         DPORT_WIFI_RST_EN_REG
#define DPORT_WIFI_RST_EN_REG          (DR_REG_DPORT_BASE + 0x0B4)
/* DPORT_WIFI_RST : R/W ;bitpos:[31:0] ;default: 32'h0 ; */
/*description: */
#define DPORT_WIFI_RST  0xFFFFFFFF
#define DPORT_WIFI_RST_M  ((DPORT_WIFI_RST_V)<<(DPORT_WIFI_RST_S))
#define DPORT_WIFI_RST_V  0xFFFFFFFF
#define DPORT_WIFI_RST_S  0
#define DPORT_RW_BTLP_RST (BIT(10))
#define DPORT_RW_BTMAC_RST (BIT(9))
#define DPORT_MACPWR_RST (BIT(8))
#define DPORT_EMAC_RST (BIT(7))
#define DPORT_SDIO_HOST_RST (BIT(6))
#define DPORT_SDIO_RST (BIT(5))
#define DPORT_BTMAC_RST (BIT(4))
#define DPORT_BT_RST (BIT(3))
#define DPORT_MAC_RST (BIT(2))
#define DPORT_FE_RST (BIT(1))
#define DPORT_BB_RST (BIT(0))  

#define DPORT_BT_LPCK_DIV_INT_REG          (DR_REG_DPORT_BASE + 0x0B8)
/* DPORT_BTEXTWAKEUP_REQ : R/W ;bitpos:[12] ;default: 1'b0 ; */
/*description: */
#define DPORT_BTEXTWAKEUP_REQ  (BIT(12))
#define DPORT_BTEXTWAKEUP_REQ_M  (BIT(12))
#define DPORT_BTEXTWAKEUP_REQ_V  0x1
#define DPORT_BTEXTWAKEUP_REQ_S  12
/* DPORT_BT_LPCK_DIV_NUM : R/W ;bitpos:[11:0] ;default: 12'd255 ; */
/*description: */
#define DPORT_BT_LPCK_DIV_NUM  0x00000FFF
#define DPORT_BT_LPCK_DIV_NUM_M  ((DPORT_BT_LPCK_DIV_NUM_V)<<(DPORT_BT_LPCK_DIV_NUM_S))
#define DPORT_BT_LPCK_DIV_NUM_V  0xFFF
#define DPORT_BT_LPCK_DIV_NUM_S  0

#define DPORT_BT_LPCK_DIV_FRAC_REG          (DR_REG_DPORT_BASE + 0x0BC)
/* DPORT_LPCLK_SEL_XTAL32K : R/W ;bitpos:[27] ;default: 1'b0 ; */
/*description: */
#define DPORT_LPCLK_SEL_XTAL32K  (BIT(27))
#define DPORT_LPCLK_SEL_XTAL32K_M  (BIT(27))
#define DPORT_LPCLK_SEL_XTAL32K_V  0x1
#define DPORT_LPCLK_SEL_XTAL32K_S  27
/* DPORT_LPCLK_SEL_XTAL : R/W ;bitpos:[26] ;default: 1'b0 ; */
/*description: */
#define DPORT_LPCLK_SEL_XTAL  (BIT(26))
#define DPORT_LPCLK_SEL_XTAL_M  (BIT(26))
#define DPORT_LPCLK_SEL_XTAL_V  0x1
#define DPORT_LPCLK_SEL_XTAL_S  26
/* DPORT_LPCLK_SEL_8M : R/W ;bitpos:[25] ;default: 1'b1 ; */
/*description: */
#define DPORT_LPCLK_SEL_8M  (BIT(25))
#define DPORT_LPCLK_SEL_8M_M  (BIT(25))
#define DPORT_LPCLK_SEL_8M_V  0x1
#define DPORT_LPCLK_SEL_8M_S  25
/* DPORT_LPCLK_SEL_RTC_SLOW : R/W ;bitpos:[24] ;default: 1'b0 ; */
/*description: */
#define DPORT_LPCLK_SEL_RTC_SLOW  (BIT(24))
#define DPORT_LPCLK_SEL_RTC_SLOW_M  (BIT(24))
#define DPORT_LPCLK_SEL_RTC_SLOW_V  0x1
#define DPORT_LPCLK_SEL_RTC_SLOW_S  24
/* DPORT_BT_LPCK_DIV_A : R/W ;bitpos:[23:12] ;default: 12'd1 ; */
/*description: */
#define DPORT_BT_LPCK_DIV_A  0x00000FFF
#define DPORT_BT_LPCK_DIV_A_M  ((DPORT_BT_LPCK_DIV_A_V)<<(DPORT_BT_LPCK_DIV_A_S))
#define DPORT_BT_LPCK_DIV_A_V  0xFFF
#define DPORT_BT_LPCK_DIV_A_S  12
/* DPORT_BT_LPCK_DIV_B : R/W ;bitpos:[11:0] ;default: 12'd1 ; */
/*description: */
#define DPORT_BT_LPCK_DIV_B  0x00000FFF
#define DPORT_BT_LPCK_DIV_B_M  ((DPORT_BT_LPCK_DIV_B_V)<<(DPORT_BT_LPCK_DIV_B_S))
#define DPORT_BT_LPCK_DIV_B_V  0xFFF
#define DPORT_BT_LPCK_DIV_B_S  0

#define DPORT_CPU_INTR_FROM_CPU_0_REG          (DR_REG_DPORT_BASE + 0x0C0)
/* DPORT_CPU_INTR_FROM_CPU_0 : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: */
#define DPORT_CPU_INTR_FROM_CPU_0  (BIT(0))
#define DPORT_CPU_INTR_FROM_CPU_0_M  (BIT(0))
#define DPORT_CPU_INTR_FROM_CPU_0_V  0x1
#define DPORT_CPU_INTR_FROM_CPU_0_S  0

#define DPORT_CPU_INTR_FROM_CPU_1_REG          (DR_REG_DPORT_BASE + 0x0C4)
/* DPORT_CPU_INTR_FROM_CPU_1 : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: */
#define DPORT_CPU_INTR_FROM_CPU_1  (BIT(0))
#define DPORT_CPU_INTR_FROM_CPU_1_M  (BIT(0))
#define DPORT_CPU_INTR_FROM_CPU_1_V  0x1
#define DPORT_CPU_INTR_FROM_CPU_1_S  0

#define DPORT_CPU_INTR_FROM_CPU_2_REG          (DR_REG_DPORT_BASE + 0x0C8)
/* DPORT_CPU_INTR_FROM_CPU_2 : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: */
#define DPORT_CPU_INTR_FROM_CPU_2  (BIT(0))
#define DPORT_CPU_INTR_FROM_CPU_2_M  (BIT(0))
#define DPORT_CPU_INTR_FROM_CPU_2_V  0x1
#define DPORT_CPU_INTR_FROM_CPU_2_S  0

#define DPORT_CPU_INTR_FROM_CPU_3_REG          (DR_REG_DPORT_BASE + 0x0CC)
/* DPORT_CPU_INTR_FROM_CPU_3 : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: */
#define DPORT_CPU_INTR_FROM_CPU_3  (BIT(0))
#define DPORT_CPU_INTR_FROM_CPU_3_M  (BIT(0))
#define DPORT_CPU_INTR_FROM_CPU_3_V  0x1
#define DPORT_CPU_INTR_FROM_CPU_3_S  0

#define DPORT_PRO_INTR_STATUS_0_REG          (DR_REG_DPORT_BASE + 0x0D0)
/* DPORT_PRO_INTR_STATUS_0 : RO ;bitpos:[31:0] ;default: 32'h0 ; */
/*description: */
#define DPORT_PRO_INTR_STATUS_0  0xFFFFFFFF
#define DPORT_PRO_INTR_STATUS_0_M  ((DPORT_PRO_INTR_STATUS_0_V)<<(DPORT_PRO_INTR_STATUS_0_S))
#define DPORT_PRO_INTR_STATUS_0_V  0xFFFFFFFF
#define DPORT_PRO_INTR_STATUS_0_S  0

#define DPORT_PRO_INTR_STATUS_1_REG          (DR_REG_DPORT_BASE + 0x0D4)
/* DPORT_PRO_INTR_STATUS_1 : RO ;bitpos:[31:0] ;default: 32'h0 ; */
/*description: */
#define DPORT_PRO_INTR_STATUS_1  0xFFFFFFFF
#define DPORT_PRO_INTR_STATUS_1_M  ((DPORT_PRO_INTR_STATUS_1_V)<<(DPORT_PRO_INTR_STATUS_1_S))
#define DPORT_PRO_INTR_STATUS_1_V  0xFFFFFFFF
#define DPORT_PRO_INTR_STATUS_1_S  0

#define DPORT_PRO_INTR_STATUS_2_REG          (DR_REG_DPORT_BASE + 0x0D8)
/* DPORT_PRO_INTR_STATUS_2 : RO ;bitpos:[31:0] ;default: 32'h0 ; */
/*description: */
#define DPORT_PRO_INTR_STATUS_2  0xFFFFFFFF
#define DPORT_PRO_INTR_STATUS_2_M  ((DPORT_PRO_INTR_STATUS_2_V)<<(DPORT_PRO_INTR_STATUS_2_S))
#define DPORT_PRO_INTR_STATUS_2_V  0xFFFFFFFF
#define DPORT_PRO_INTR_STATUS_2_S  0

#define DPORT_PRO_MAC_INTR_MAP_REG          (DR_REG_DPORT_BASE + 0x0DC)
/* DPORT_PRO_MAC_INTR_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_MAC_INTR_MAP  0x0000001F
#define DPORT_PRO_MAC_INTR_MAP_M  ((DPORT_PRO_MAC_INTR_MAP_V)<<(DPORT_PRO_MAC_INTR_MAP_S))
#define DPORT_PRO_MAC_INTR_MAP_V  0x1F
#define DPORT_PRO_MAC_INTR_MAP_S  0

#define DPORT_PRO_MAC_NMI_MAP_REG          (DR_REG_DPORT_BASE + 0x0E0)
/* DPORT_PRO_MAC_NMI_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_MAC_NMI_MAP  0x0000001F
#define DPORT_PRO_MAC_NMI_MAP_M  ((DPORT_PRO_MAC_NMI_MAP_V)<<(DPORT_PRO_MAC_NMI_MAP_S))
#define DPORT_PRO_MAC_NMI_MAP_V  0x1F
#define DPORT_PRO_MAC_NMI_MAP_S  0

#define DPORT_PRO_BB_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x0E4)
/* DPORT_PRO_BB_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_BB_INT_MAP  0x0000001F
#define DPORT_PRO_BB_INT_MAP_M  ((DPORT_PRO_BB_INT_MAP_V)<<(DPORT_PRO_BB_INT_MAP_S))
#define DPORT_PRO_BB_INT_MAP_V  0x1F
#define DPORT_PRO_BB_INT_MAP_S  0

#define DPORT_PRO_BT_MAC_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x0E8)
/* DPORT_PRO_BT_MAC_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_BT_MAC_INT_MAP  0x0000001F
#define DPORT_PRO_BT_MAC_INT_MAP_M  ((DPORT_PRO_BT_MAC_INT_MAP_V)<<(DPORT_PRO_BT_MAC_INT_MAP_S))
#define DPORT_PRO_BT_MAC_INT_MAP_V  0x1F
#define DPORT_PRO_BT_MAC_INT_MAP_S  0

#define DPORT_PRO_BT_BB_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x0EC)
/* DPORT_PRO_BT_BB_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_BT_BB_INT_MAP  0x0000001F
#define DPORT_PRO_BT_BB_INT_MAP_M  ((DPORT_PRO_BT_BB_INT_MAP_V)<<(DPORT_PRO_BT_BB_INT_MAP_S))
#define DPORT_PRO_BT_BB_INT_MAP_V  0x1F
#define DPORT_PRO_BT_BB_INT_MAP_S  0

#define DPORT_PRO_BT_BB_NMI_MAP_REG          (DR_REG_DPORT_BASE + 0x0F0)
/* DPORT_PRO_BT_BB_NMI_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_BT_BB_NMI_MAP  0x0000001F
#define DPORT_PRO_BT_BB_NMI_MAP_M  ((DPORT_PRO_BT_BB_NMI_MAP_V)<<(DPORT_PRO_BT_BB_NMI_MAP_S))
#define DPORT_PRO_BT_BB_NMI_MAP_V  0x1F
#define DPORT_PRO_BT_BB_NMI_MAP_S  0

#define DPORT_PRO_RWBT_IRQ_MAP_REG          (DR_REG_DPORT_BASE + 0x0F4)
/* DPORT_PRO_RWBT_IRQ_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_RWBT_IRQ_MAP  0x0000001F
#define DPORT_PRO_RWBT_IRQ_MAP_M  ((DPORT_PRO_RWBT_IRQ_MAP_V)<<(DPORT_PRO_RWBT_IRQ_MAP_S))
#define DPORT_PRO_RWBT_IRQ_MAP_V  0x1F
#define DPORT_PRO_RWBT_IRQ_MAP_S  0

#define DPORT_PRO_RWBLE_IRQ_MAP_REG          (DR_REG_DPORT_BASE + 0x0F8)
/* DPORT_PRO_RWBLE_IRQ_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_RWBLE_IRQ_MAP  0x0000001F
#define DPORT_PRO_RWBLE_IRQ_MAP_M  ((DPORT_PRO_RWBLE_IRQ_MAP_V)<<(DPORT_PRO_RWBLE_IRQ_MAP_S))
#define DPORT_PRO_RWBLE_IRQ_MAP_V  0x1F
#define DPORT_PRO_RWBLE_IRQ_MAP_S  0

#define DPORT_PRO_RWBT_NMI_MAP_REG          (DR_REG_DPORT_BASE + 0x0FC)
/* DPORT_PRO_RWBT_NMI_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_RWBT_NMI_MAP  0x0000001F
#define DPORT_PRO_RWBT_NMI_MAP_M  ((DPORT_PRO_RWBT_NMI_MAP_V)<<(DPORT_PRO_RWBT_NMI_MAP_S))
#define DPORT_PRO_RWBT_NMI_MAP_V  0x1F
#define DPORT_PRO_RWBT_NMI_MAP_S  0

#define DPORT_PRO_RWBLE_NMI_MAP_REG          (DR_REG_DPORT_BASE + 0x100)
/* DPORT_PRO_RWBLE_NMI_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_RWBLE_NMI_MAP  0x0000001F
#define DPORT_PRO_RWBLE_NMI_MAP_M  ((DPORT_PRO_RWBLE_NMI_MAP_V)<<(DPORT_PRO_RWBLE_NMI_MAP_S))
#define DPORT_PRO_RWBLE_NMI_MAP_V  0x1F
#define DPORT_PRO_RWBLE_NMI_MAP_S  0

#define DPORT_PRO_SLC0_INTR_MAP_REG          (DR_REG_DPORT_BASE + 0x104)
/* DPORT_PRO_SLC0_INTR_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_SLC0_INTR_MAP  0x0000001F
#define DPORT_PRO_SLC0_INTR_MAP_M  ((DPORT_PRO_SLC0_INTR_MAP_V)<<(DPORT_PRO_SLC0_INTR_MAP_S))
#define DPORT_PRO_SLC0_INTR_MAP_V  0x1F
#define DPORT_PRO_SLC0_INTR_MAP_S  0

#define DPORT_PRO_SLC1_INTR_MAP_REG          (DR_REG_DPORT_BASE + 0x108)
/* DPORT_PRO_SLC1_INTR_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_SLC1_INTR_MAP  0x0000001F
#define DPORT_PRO_SLC1_INTR_MAP_M  ((DPORT_PRO_SLC1_INTR_MAP_V)<<(DPORT_PRO_SLC1_INTR_MAP_S))
#define DPORT_PRO_SLC1_INTR_MAP_V  0x1F
#define DPORT_PRO_SLC1_INTR_MAP_S  0

#define DPORT_PRO_UHCI0_INTR_MAP_REG          (DR_REG_DPORT_BASE + 0x10C)
/* DPORT_PRO_UHCI0_INTR_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_UHCI0_INTR_MAP  0x0000001F
#define DPORT_PRO_UHCI0_INTR_MAP_M  ((DPORT_PRO_UHCI0_INTR_MAP_V)<<(DPORT_PRO_UHCI0_INTR_MAP_S))
#define DPORT_PRO_UHCI0_INTR_MAP_V  0x1F
#define DPORT_PRO_UHCI0_INTR_MAP_S  0

#define DPORT_PRO_UHCI1_INTR_MAP_REG          (DR_REG_DPORT_BASE + 0x110)
/* DPORT_PRO_UHCI1_INTR_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_UHCI1_INTR_MAP  0x0000001F
#define DPORT_PRO_UHCI1_INTR_MAP_M  ((DPORT_PRO_UHCI1_INTR_MAP_V)<<(DPORT_PRO_UHCI1_INTR_MAP_S))
#define DPORT_PRO_UHCI1_INTR_MAP_V  0x1F
#define DPORT_PRO_UHCI1_INTR_MAP_S  0

#define DPORT_PRO_TG_T0_LEVEL_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x114)
/* DPORT_PRO_TG_T0_LEVEL_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_TG_T0_LEVEL_INT_MAP  0x0000001F
#define DPORT_PRO_TG_T0_LEVEL_INT_MAP_M  ((DPORT_PRO_TG_T0_LEVEL_INT_MAP_V)<<(DPORT_PRO_TG_T0_LEVEL_INT_MAP_S))
#define DPORT_PRO_TG_T0_LEVEL_INT_MAP_V  0x1F
#define DPORT_PRO_TG_T0_LEVEL_INT_MAP_S  0

#define DPORT_PRO_TG_T1_LEVEL_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x118)
/* DPORT_PRO_TG_T1_LEVEL_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_TG_T1_LEVEL_INT_MAP  0x0000001F
#define DPORT_PRO_TG_T1_LEVEL_INT_MAP_M  ((DPORT_PRO_TG_T1_LEVEL_INT_MAP_V)<<(DPORT_PRO_TG_T1_LEVEL_INT_MAP_S))
#define DPORT_PRO_TG_T1_LEVEL_INT_MAP_V  0x1F
#define DPORT_PRO_TG_T1_LEVEL_INT_MAP_S  0

#define DPORT_PRO_TG_WDT_LEVEL_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x11C)
/* DPORT_PRO_TG_WDT_LEVEL_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_TG_WDT_LEVEL_INT_MAP  0x0000001F
#define DPORT_PRO_TG_WDT_LEVEL_INT_MAP_M  ((DPORT_PRO_TG_WDT_LEVEL_INT_MAP_V)<<(DPORT_PRO_TG_WDT_LEVEL_INT_MAP_S))
#define DPORT_PRO_TG_WDT_LEVEL_INT_MAP_V  0x1F
#define DPORT_PRO_TG_WDT_LEVEL_INT_MAP_S  0

#define DPORT_PRO_TG_LACT_LEVEL_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x120)
/* DPORT_PRO_TG_LACT_LEVEL_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_TG_LACT_LEVEL_INT_MAP  0x0000001F
#define DPORT_PRO_TG_LACT_LEVEL_INT_MAP_M  ((DPORT_PRO_TG_LACT_LEVEL_INT_MAP_V)<<(DPORT_PRO_TG_LACT_LEVEL_INT_MAP_S))
#define DPORT_PRO_TG_LACT_LEVEL_INT_MAP_V  0x1F
#define DPORT_PRO_TG_LACT_LEVEL_INT_MAP_S  0

#define DPORT_PRO_TG1_T0_LEVEL_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x124)
/* DPORT_PRO_TG1_T0_LEVEL_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_TG1_T0_LEVEL_INT_MAP  0x0000001F
#define DPORT_PRO_TG1_T0_LEVEL_INT_MAP_M  ((DPORT_PRO_TG1_T0_LEVEL_INT_MAP_V)<<(DPORT_PRO_TG1_T0_LEVEL_INT_MAP_S))
#define DPORT_PRO_TG1_T0_LEVEL_INT_MAP_V  0x1F
#define DPORT_PRO_TG1_T0_LEVEL_INT_MAP_S  0

#define DPORT_PRO_TG1_T1_LEVEL_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x128)
/* DPORT_PRO_TG1_T1_LEVEL_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_TG1_T1_LEVEL_INT_MAP  0x0000001F
#define DPORT_PRO_TG1_T1_LEVEL_INT_MAP_M  ((DPORT_PRO_TG1_T1_LEVEL_INT_MAP_V)<<(DPORT_PRO_TG1_T1_LEVEL_INT_MAP_S))
#define DPORT_PRO_TG1_T1_LEVEL_INT_MAP_V  0x1F
#define DPORT_PRO_TG1_T1_LEVEL_INT_MAP_S  0

#define DPORT_PRO_TG1_WDT_LEVEL_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x12C)
/* DPORT_PRO_TG1_WDT_LEVEL_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_TG1_WDT_LEVEL_INT_MAP  0x0000001F
#define DPORT_PRO_TG1_WDT_LEVEL_INT_MAP_M  ((DPORT_PRO_TG1_WDT_LEVEL_INT_MAP_V)<<(DPORT_PRO_TG1_WDT_LEVEL_INT_MAP_S))
#define DPORT_PRO_TG1_WDT_LEVEL_INT_MAP_V  0x1F
#define DPORT_PRO_TG1_WDT_LEVEL_INT_MAP_S  0

#define DPORT_PRO_TG1_LACT_LEVEL_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x130)
/* DPORT_PRO_TG1_LACT_LEVEL_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_TG1_LACT_LEVEL_INT_MAP  0x0000001F
#define DPORT_PRO_TG1_LACT_LEVEL_INT_MAP_M  ((DPORT_PRO_TG1_LACT_LEVEL_INT_MAP_V)<<(DPORT_PRO_TG1_LACT_LEVEL_INT_MAP_S))
#define DPORT_PRO_TG1_LACT_LEVEL_INT_MAP_V  0x1F
#define DPORT_PRO_TG1_LACT_LEVEL_INT_MAP_S  0

#define DPORT_PRO_GPIO_INTERRUPT_PRO_MAP_REG          (DR_REG_DPORT_BASE + 0x134)
/* DPORT_PRO_GPIO_INTERRUPT_PRO_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_GPIO_INTERRUPT_PRO_MAP  0x0000001F
#define DPORT_PRO_GPIO_INTERRUPT_PRO_MAP_M  ((DPORT_PRO_GPIO_INTERRUPT_PRO_MAP_V)<<(DPORT_PRO_GPIO_INTERRUPT_PRO_MAP_S))
#define DPORT_PRO_GPIO_INTERRUPT_PRO_MAP_V  0x1F
#define DPORT_PRO_GPIO_INTERRUPT_PRO_MAP_S  0

#define DPORT_PRO_GPIO_INTERRUPT_PRO_NMI_MAP_REG          (DR_REG_DPORT_BASE + 0x138)
/* DPORT_PRO_GPIO_INTERRUPT_PRO_NMI_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_GPIO_INTERRUPT_PRO_NMI_MAP  0x0000001F
#define DPORT_PRO_GPIO_INTERRUPT_PRO_NMI_MAP_M  ((DPORT_PRO_GPIO_INTERRUPT_PRO_NMI_MAP_V)<<(DPORT_PRO_GPIO_INTERRUPT_PRO_NMI_MAP_S))
#define DPORT_PRO_GPIO_INTERRUPT_PRO_NMI_MAP_V  0x1F
#define DPORT_PRO_GPIO_INTERRUPT_PRO_NMI_MAP_S  0

#define DPORT_PRO_ALONE_GPIO_IN_INTR_PRO_MAP_REG          (DR_REG_DPORT_BASE + 0x13C)
/* DPORT_PRO_ALONE_GPIO_IN_INTR_PRO_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_ALONE_GPIO_IN_INTR_PRO_MAP  0x0000001F
#define DPORT_PRO_ALONE_GPIO_IN_INTR_PRO_MAP_M  ((DPORT_PRO_ALONE_GPIO_IN_INTR_PRO_MAP_V)<<(DPORT_PRO_ALONE_GPIO_IN_INTR_PRO_MAP_S))
#define DPORT_PRO_ALONE_GPIO_IN_INTR_PRO_MAP_V  0x1F
#define DPORT_PRO_ALONE_GPIO_IN_INTR_PRO_MAP_S  0

#define DPORT_PRO_CPU_INTR_FROM_CPU_0_MAP_REG          (DR_REG_DPORT_BASE + 0x140)
/* DPORT_PRO_CPU_INTR_FROM_CPU_0_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_CPU_INTR_FROM_CPU_0_MAP  0x0000001F
#define DPORT_PRO_CPU_INTR_FROM_CPU_0_MAP_M  ((DPORT_PRO_CPU_INTR_FROM_CPU_0_MAP_V)<<(DPORT_PRO_CPU_INTR_FROM_CPU_0_MAP_S))
#define DPORT_PRO_CPU_INTR_FROM_CPU_0_MAP_V  0x1F
#define DPORT_PRO_CPU_INTR_FROM_CPU_0_MAP_S  0

#define DPORT_PRO_CPU_INTR_FROM_CPU_1_MAP_REG          (DR_REG_DPORT_BASE + 0x144)
/* DPORT_PRO_CPU_INTR_FROM_CPU_1_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_CPU_INTR_FROM_CPU_1_MAP  0x0000001F
#define DPORT_PRO_CPU_INTR_FROM_CPU_1_MAP_M  ((DPORT_PRO_CPU_INTR_FROM_CPU_1_MAP_V)<<(DPORT_PRO_CPU_INTR_FROM_CPU_1_MAP_S))
#define DPORT_PRO_CPU_INTR_FROM_CPU_1_MAP_V  0x1F
#define DPORT_PRO_CPU_INTR_FROM_CPU_1_MAP_S  0

#define DPORT_PRO_CPU_INTR_FROM_CPU_2_MAP_REG          (DR_REG_DPORT_BASE + 0x148)
/* DPORT_PRO_CPU_INTR_FROM_CPU_2_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_CPU_INTR_FROM_CPU_2_MAP  0x0000001F
#define DPORT_PRO_CPU_INTR_FROM_CPU_2_MAP_M  ((DPORT_PRO_CPU_INTR_FROM_CPU_2_MAP_V)<<(DPORT_PRO_CPU_INTR_FROM_CPU_2_MAP_S))
#define DPORT_PRO_CPU_INTR_FROM_CPU_2_MAP_V  0x1F
#define DPORT_PRO_CPU_INTR_FROM_CPU_2_MAP_S  0

#define DPORT_PRO_CPU_INTR_FROM_CPU_3_MAP_REG          (DR_REG_DPORT_BASE + 0x14C)
/* DPORT_PRO_CPU_INTR_FROM_CPU_3_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_CPU_INTR_FROM_CPU_3_MAP  0x0000001F
#define DPORT_PRO_CPU_INTR_FROM_CPU_3_MAP_M  ((DPORT_PRO_CPU_INTR_FROM_CPU_3_MAP_V)<<(DPORT_PRO_CPU_INTR_FROM_CPU_3_MAP_S))
#define DPORT_PRO_CPU_INTR_FROM_CPU_3_MAP_V  0x1F
#define DPORT_PRO_CPU_INTR_FROM_CPU_3_MAP_S  0

#define DPORT_PRO_SPI_INTR_0_MAP_REG          (DR_REG_DPORT_BASE + 0x150)
/* DPORT_PRO_SPI_INTR_0_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_SPI_INTR_0_MAP  0x0000001F
#define DPORT_PRO_SPI_INTR_0_MAP_M  ((DPORT_PRO_SPI_INTR_0_MAP_V)<<(DPORT_PRO_SPI_INTR_0_MAP_S))
#define DPORT_PRO_SPI_INTR_0_MAP_V  0x1F
#define DPORT_PRO_SPI_INTR_0_MAP_S  0

#define DPORT_PRO_SPI_INTR_1_MAP_REG          (DR_REG_DPORT_BASE + 0x154)
/* DPORT_PRO_SPI_INTR_1_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_SPI_INTR_1_MAP  0x0000001F
#define DPORT_PRO_SPI_INTR_1_MAP_M  ((DPORT_PRO_SPI_INTR_1_MAP_V)<<(DPORT_PRO_SPI_INTR_1_MAP_S))
#define DPORT_PRO_SPI_INTR_1_MAP_V  0x1F
#define DPORT_PRO_SPI_INTR_1_MAP_S  0

#define DPORT_PRO_SPI_INTR_2_MAP_REG          (DR_REG_DPORT_BASE + 0x158)
/* DPORT_PRO_SPI_INTR_2_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_SPI_INTR_2_MAP  0x0000001F
#define DPORT_PRO_SPI_INTR_2_MAP_M  ((DPORT_PRO_SPI_INTR_2_MAP_V)<<(DPORT_PRO_SPI_INTR_2_MAP_S))
#define DPORT_PRO_SPI_INTR_2_MAP_V  0x1F
#define DPORT_PRO_SPI_INTR_2_MAP_S  0

#define DPORT_PRO_SPI_INTR_3_MAP_REG          (DR_REG_DPORT_BASE + 0x15C)
/* DPORT_PRO_SPI_INTR_3_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_SPI_INTR_3_MAP  0x0000001F
#define DPORT_PRO_SPI_INTR_3_MAP_M  ((DPORT_PRO_SPI_INTR_3_MAP_V)<<(DPORT_PRO_SPI_INTR_3_MAP_S))
#define DPORT_PRO_SPI_INTR_3_MAP_V  0x1F
#define DPORT_PRO_SPI_INTR_3_MAP_S  0

#define DPORT_PRO_I2S0_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x160)
/* DPORT_PRO_I2S0_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_I2S0_INT_MAP  0x0000001F
#define DPORT_PRO_I2S0_INT_MAP_M  ((DPORT_PRO_I2S0_INT_MAP_V)<<(DPORT_PRO_I2S0_INT_MAP_S))
#define DPORT_PRO_I2S0_INT_MAP_V  0x1F
#define DPORT_PRO_I2S0_INT_MAP_S  0

#define DPORT_PRO_I2S1_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x164)
/* DPORT_PRO_I2S1_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_I2S1_INT_MAP  0x0000001F
#define DPORT_PRO_I2S1_INT_MAP_M  ((DPORT_PRO_I2S1_INT_MAP_V)<<(DPORT_PRO_I2S1_INT_MAP_S))
#define DPORT_PRO_I2S1_INT_MAP_V  0x1F
#define DPORT_PRO_I2S1_INT_MAP_S  0

#define DPORT_PRO_UART_INTR_MAP_REG          (DR_REG_DPORT_BASE + 0x168)
/* DPORT_PRO_UART_INTR_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_UART_INTR_MAP  0x0000001F
#define DPORT_PRO_UART_INTR_MAP_M  ((DPORT_PRO_UART_INTR_MAP_V)<<(DPORT_PRO_UART_INTR_MAP_S))
#define DPORT_PRO_UART_INTR_MAP_V  0x1F
#define DPORT_PRO_UART_INTR_MAP_S  0

#define DPORT_PRO_UART1_INTR_MAP_REG          (DR_REG_DPORT_BASE + 0x16C)
/* DPORT_PRO_UART1_INTR_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_UART1_INTR_MAP  0x0000001F
#define DPORT_PRO_UART1_INTR_MAP_M  ((DPORT_PRO_UART1_INTR_MAP_V)<<(DPORT_PRO_UART1_INTR_MAP_S))
#define DPORT_PRO_UART1_INTR_MAP_V  0x1F
#define DPORT_PRO_UART1_INTR_MAP_S  0

#define DPORT_PRO_UART2_INTR_MAP_REG          (DR_REG_DPORT_BASE + 0x170)
/* DPORT_PRO_UART2_INTR_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_UART2_INTR_MAP  0x0000001F
#define DPORT_PRO_UART2_INTR_MAP_M  ((DPORT_PRO_UART2_INTR_MAP_V)<<(DPORT_PRO_UART2_INTR_MAP_S))
#define DPORT_PRO_UART2_INTR_MAP_V  0x1F
#define DPORT_PRO_UART2_INTR_MAP_S  0

#define DPORT_PRO_SDIO_HOST_INTERRUPT_MAP_REG          (DR_REG_DPORT_BASE + 0x174)
/* DPORT_PRO_SDIO_HOST_INTERRUPT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_SDIO_HOST_INTERRUPT_MAP  0x0000001F
#define DPORT_PRO_SDIO_HOST_INTERRUPT_MAP_M  ((DPORT_PRO_SDIO_HOST_INTERRUPT_MAP_V)<<(DPORT_PRO_SDIO_HOST_INTERRUPT_MAP_S))
#define DPORT_PRO_SDIO_HOST_INTERRUPT_MAP_V  0x1F
#define DPORT_PRO_SDIO_HOST_INTERRUPT_MAP_S  0

#define DPORT_PRO_PWM0_INTR_MAP_REG          (DR_REG_DPORT_BASE + 0x178)
/* DPORT_PRO_PWM0_INTR_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_PWM0_INTR_MAP  0x0000001F
#define DPORT_PRO_PWM0_INTR_MAP_M  ((DPORT_PRO_PWM0_INTR_MAP_V)<<(DPORT_PRO_PWM0_INTR_MAP_S))
#define DPORT_PRO_PWM0_INTR_MAP_V  0x1F
#define DPORT_PRO_PWM0_INTR_MAP_S  0

#define DPORT_PRO_PWM1_INTR_MAP_REG          (DR_REG_DPORT_BASE + 0x17C)
/* DPORT_PRO_PWM1_INTR_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_PWM1_INTR_MAP  0x0000001F
#define DPORT_PRO_PWM1_INTR_MAP_M  ((DPORT_PRO_PWM1_INTR_MAP_V)<<(DPORT_PRO_PWM1_INTR_MAP_S))
#define DPORT_PRO_PWM1_INTR_MAP_V  0x1F
#define DPORT_PRO_PWM1_INTR_MAP_S  0

#define DPORT_PRO_PWM2_INTR_MAP_REG          (DR_REG_DPORT_BASE + 0x180)
/* DPORT_PRO_PWM2_INTR_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_PWM2_INTR_MAP  0x0000001F
#define DPORT_PRO_PWM2_INTR_MAP_M  ((DPORT_PRO_PWM2_INTR_MAP_V)<<(DPORT_PRO_PWM2_INTR_MAP_S))
#define DPORT_PRO_PWM2_INTR_MAP_V  0x1F
#define DPORT_PRO_PWM2_INTR_MAP_S  0

#define DPORT_PRO_PWM3_INTR_MAP_REG          (DR_REG_DPORT_BASE + 0x184)
/* DPORT_PRO_PWM3_INTR_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_PWM3_INTR_MAP  0x0000001F
#define DPORT_PRO_PWM3_INTR_MAP_M  ((DPORT_PRO_PWM3_INTR_MAP_V)<<(DPORT_PRO_PWM3_INTR_MAP_S))
#define DPORT_PRO_PWM3_INTR_MAP_V  0x1F
#define DPORT_PRO_PWM3_INTR_MAP_S  0

#define DPORT_PRO_LEDC_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x188)
/* DPORT_PRO_LEDC_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_LEDC_INT_MAP  0x0000001F
#define DPORT_PRO_LEDC_INT_MAP_M  ((DPORT_PRO_LEDC_INT_MAP_V)<<(DPORT_PRO_LEDC_INT_MAP_S))
#define DPORT_PRO_LEDC_INT_MAP_V  0x1F
#define DPORT_PRO_LEDC_INT_MAP_S  0

#define DPORT_PRO_EFUSE_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x18C)
/* DPORT_PRO_EFUSE_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_EFUSE_INT_MAP  0x0000001F
#define DPORT_PRO_EFUSE_INT_MAP_M  ((DPORT_PRO_EFUSE_INT_MAP_V)<<(DPORT_PRO_EFUSE_INT_MAP_S))
#define DPORT_PRO_EFUSE_INT_MAP_V  0x1F
#define DPORT_PRO_EFUSE_INT_MAP_S  0

#define DPORT_PRO_CAN_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x190)
/* DPORT_PRO_CAN_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_CAN_INT_MAP  0x0000001F
#define DPORT_PRO_CAN_INT_MAP_M  ((DPORT_PRO_CAN_INT_MAP_V)<<(DPORT_PRO_CAN_INT_MAP_S))
#define DPORT_PRO_CAN_INT_MAP_V  0x1F
#define DPORT_PRO_CAN_INT_MAP_S  0

#define DPORT_PRO_RTC_CORE_INTR_MAP_REG          (DR_REG_DPORT_BASE + 0x194)
/* DPORT_PRO_RTC_CORE_INTR_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_RTC_CORE_INTR_MAP  0x0000001F
#define DPORT_PRO_RTC_CORE_INTR_MAP_M  ((DPORT_PRO_RTC_CORE_INTR_MAP_V)<<(DPORT_PRO_RTC_CORE_INTR_MAP_S))
#define DPORT_PRO_RTC_CORE_INTR_MAP_V  0x1F
#define DPORT_PRO_RTC_CORE_INTR_MAP_S  0

#define DPORT_PRO_RMT_INTR_MAP_REG          (DR_REG_DPORT_BASE + 0x198)
/* DPORT_PRO_RMT_INTR_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_RMT_INTR_MAP  0x0000001F
#define DPORT_PRO_RMT_INTR_MAP_M  ((DPORT_PRO_RMT_INTR_MAP_V)<<(DPORT_PRO_RMT_INTR_MAP_S))
#define DPORT_PRO_RMT_INTR_MAP_V  0x1F
#define DPORT_PRO_RMT_INTR_MAP_S  0

#define DPORT_PRO_PCNT_INTR_MAP_REG          (DR_REG_DPORT_BASE + 0x19C)
/* DPORT_PRO_PCNT_INTR_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_PCNT_INTR_MAP  0x0000001F
#define DPORT_PRO_PCNT_INTR_MAP_M  ((DPORT_PRO_PCNT_INTR_MAP_V)<<(DPORT_PRO_PCNT_INTR_MAP_S))
#define DPORT_PRO_PCNT_INTR_MAP_V  0x1F
#define DPORT_PRO_PCNT_INTR_MAP_S  0

#define DPORT_PRO_I2C_EXT0_INTR_MAP_REG          (DR_REG_DPORT_BASE + 0x1A0)
/* DPORT_PRO_I2C_EXT0_INTR_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_I2C_EXT0_INTR_MAP  0x0000001F
#define DPORT_PRO_I2C_EXT0_INTR_MAP_M  ((DPORT_PRO_I2C_EXT0_INTR_MAP_V)<<(DPORT_PRO_I2C_EXT0_INTR_MAP_S))
#define DPORT_PRO_I2C_EXT0_INTR_MAP_V  0x1F
#define DPORT_PRO_I2C_EXT0_INTR_MAP_S  0

#define DPORT_PRO_I2C_EXT1_INTR_MAP_REG          (DR_REG_DPORT_BASE + 0x1A4)
/* DPORT_PRO_I2C_EXT1_INTR_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_I2C_EXT1_INTR_MAP  0x0000001F
#define DPORT_PRO_I2C_EXT1_INTR_MAP_M  ((DPORT_PRO_I2C_EXT1_INTR_MAP_V)<<(DPORT_PRO_I2C_EXT1_INTR_MAP_S))
#define DPORT_PRO_I2C_EXT1_INTR_MAP_V  0x1F
#define DPORT_PRO_I2C_EXT1_INTR_MAP_S  0

#define DPORT_PRO_RSA_INTR_MAP_REG          (DR_REG_DPORT_BASE + 0x1A8)
/* DPORT_PRO_RSA_INTR_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_RSA_INTR_MAP  0x0000001F
#define DPORT_PRO_RSA_INTR_MAP_M  ((DPORT_PRO_RSA_INTR_MAP_V)<<(DPORT_PRO_RSA_INTR_MAP_S))
#define DPORT_PRO_RSA_INTR_MAP_V  0x1F
#define DPORT_PRO_RSA_INTR_MAP_S  0

#define DPORT_PRO_SPI1_DMA_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x1AC)
/* DPORT_PRO_SPI1_DMA_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_SPI1_DMA_INT_MAP  0x0000001F
#define DPORT_PRO_SPI1_DMA_INT_MAP_M  ((DPORT_PRO_SPI1_DMA_INT_MAP_V)<<(DPORT_PRO_SPI1_DMA_INT_MAP_S))
#define DPORT_PRO_SPI1_DMA_INT_MAP_V  0x1F
#define DPORT_PRO_SPI1_DMA_INT_MAP_S  0

#define DPORT_PRO_SPI2_DMA_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x1B0)
/* DPORT_PRO_SPI2_DMA_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_SPI2_DMA_INT_MAP  0x0000001F
#define DPORT_PRO_SPI2_DMA_INT_MAP_M  ((DPORT_PRO_SPI2_DMA_INT_MAP_V)<<(DPORT_PRO_SPI2_DMA_INT_MAP_S))
#define DPORT_PRO_SPI2_DMA_INT_MAP_V  0x1F
#define DPORT_PRO_SPI2_DMA_INT_MAP_S  0

#define DPORT_PRO_SPI3_DMA_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x1B4)
/* DPORT_PRO_SPI3_DMA_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_SPI3_DMA_INT_MAP  0x0000001F
#define DPORT_PRO_SPI3_DMA_INT_MAP_M  ((DPORT_PRO_SPI3_DMA_INT_MAP_V)<<(DPORT_PRO_SPI3_DMA_INT_MAP_S))
#define DPORT_PRO_SPI3_DMA_INT_MAP_V  0x1F
#define DPORT_PRO_SPI3_DMA_INT_MAP_S  0

#define DPORT_PRO_WDG_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x1B8)
/* DPORT_PRO_WDG_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_WDG_INT_MAP  0x0000001F
#define DPORT_PRO_WDG_INT_MAP_M  ((DPORT_PRO_WDG_INT_MAP_V)<<(DPORT_PRO_WDG_INT_MAP_S))
#define DPORT_PRO_WDG_INT_MAP_V  0x1F
#define DPORT_PRO_WDG_INT_MAP_S  0

#define DPORT_PRO_TIMER_INT1_MAP_REG          (DR_REG_DPORT_BASE + 0x1BC)
/* DPORT_PRO_TIMER_INT1_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_TIMER_INT1_MAP  0x0000001F
#define DPORT_PRO_TIMER_INT1_MAP_M  ((DPORT_PRO_TIMER_INT1_MAP_V)<<(DPORT_PRO_TIMER_INT1_MAP_S))
#define DPORT_PRO_TIMER_INT1_MAP_V  0x1F
#define DPORT_PRO_TIMER_INT1_MAP_S  0

#define DPORT_PRO_TIMER_INT2_MAP_REG          (DR_REG_DPORT_BASE + 0x1C0)
/* DPORT_PRO_TIMER_INT2_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_TIMER_INT2_MAP  0x0000001F
#define DPORT_PRO_TIMER_INT2_MAP_M  ((DPORT_PRO_TIMER_INT2_MAP_V)<<(DPORT_PRO_TIMER_INT2_MAP_S))
#define DPORT_PRO_TIMER_INT2_MAP_V  0x1F
#define DPORT_PRO_TIMER_INT2_MAP_S  0

#define DPORT_PRO_TG_T0_EDGE_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x1C4)
/* DPORT_PRO_TG_T0_EDGE_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_TG_T0_EDGE_INT_MAP  0x0000001F
#define DPORT_PRO_TG_T0_EDGE_INT_MAP_M  ((DPORT_PRO_TG_T0_EDGE_INT_MAP_V)<<(DPORT_PRO_TG_T0_EDGE_INT_MAP_S))
#define DPORT_PRO_TG_T0_EDGE_INT_MAP_V  0x1F
#define DPORT_PRO_TG_T0_EDGE_INT_MAP_S  0

#define DPORT_PRO_TG_T1_EDGE_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x1C8)
/* DPORT_PRO_TG_T1_EDGE_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_TG_T1_EDGE_INT_MAP  0x0000001F
#define DPORT_PRO_TG_T1_EDGE_INT_MAP_M  ((DPORT_PRO_TG_T1_EDGE_INT_MAP_V)<<(DPORT_PRO_TG_T1_EDGE_INT_MAP_S))
#define DPORT_PRO_TG_T1_EDGE_INT_MAP_V  0x1F
#define DPORT_PRO_TG_T1_EDGE_INT_MAP_S  0

#define DPORT_PRO_TG_WDT_EDGE_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x1CC)
/* DPORT_PRO_TG_WDT_EDGE_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_TG_WDT_EDGE_INT_MAP  0x0000001F
#define DPORT_PRO_TG_WDT_EDGE_INT_MAP_M  ((DPORT_PRO_TG_WDT_EDGE_INT_MAP_V)<<(DPORT_PRO_TG_WDT_EDGE_INT_MAP_S))
#define DPORT_PRO_TG_WDT_EDGE_INT_MAP_V  0x1F
#define DPORT_PRO_TG_WDT_EDGE_INT_MAP_S  0

#define DPORT_PRO_TG_LACT_EDGE_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x1D0)
/* DPORT_PRO_TG_LACT_EDGE_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_TG_LACT_EDGE_INT_MAP  0x0000001F
#define DPORT_PRO_TG_LACT_EDGE_INT_MAP_M  ((DPORT_PRO_TG_LACT_EDGE_INT_MAP_V)<<(DPORT_PRO_TG_LACT_EDGE_INT_MAP_S))
#define DPORT_PRO_TG_LACT_EDGE_INT_MAP_V  0x1F
#define DPORT_PRO_TG_LACT_EDGE_INT_MAP_S  0

#define DPORT_PRO_TG1_T0_EDGE_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x1D4)
/* DPORT_PRO_TG1_T0_EDGE_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_TG1_T0_EDGE_INT_MAP  0x0000001F
#define DPORT_PRO_TG1_T0_EDGE_INT_MAP_M  ((DPORT_PRO_TG1_T0_EDGE_INT_MAP_V)<<(DPORT_PRO_TG1_T0_EDGE_INT_MAP_S))
#define DPORT_PRO_TG1_T0_EDGE_INT_MAP_V  0x1F
#define DPORT_PRO_TG1_T0_EDGE_INT_MAP_S  0

#define DPORT_PRO_TG1_T1_EDGE_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x1D8)
/* DPORT_PRO_TG1_T1_EDGE_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_TG1_T1_EDGE_INT_MAP  0x0000001F
#define DPORT_PRO_TG1_T1_EDGE_INT_MAP_M  ((DPORT_PRO_TG1_T1_EDGE_INT_MAP_V)<<(DPORT_PRO_TG1_T1_EDGE_INT_MAP_S))
#define DPORT_PRO_TG1_T1_EDGE_INT_MAP_V  0x1F
#define DPORT_PRO_TG1_T1_EDGE_INT_MAP_S  0

#define DPORT_PRO_TG1_WDT_EDGE_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x1DC)
/* DPORT_PRO_TG1_WDT_EDGE_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_TG1_WDT_EDGE_INT_MAP  0x0000001F
#define DPORT_PRO_TG1_WDT_EDGE_INT_MAP_M  ((DPORT_PRO_TG1_WDT_EDGE_INT_MAP_V)<<(DPORT_PRO_TG1_WDT_EDGE_INT_MAP_S))
#define DPORT_PRO_TG1_WDT_EDGE_INT_MAP_V  0x1F
#define DPORT_PRO_TG1_WDT_EDGE_INT_MAP_S  0

#define DPORT_PRO_TG1_LACT_EDGE_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x1E0)
/* DPORT_PRO_TG1_LACT_EDGE_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_TG1_LACT_EDGE_INT_MAP  0x0000001F
#define DPORT_PRO_TG1_LACT_EDGE_INT_MAP_M  ((DPORT_PRO_TG1_LACT_EDGE_INT_MAP_V)<<(DPORT_PRO_TG1_LACT_EDGE_INT_MAP_S))
#define DPORT_PRO_TG1_LACT_EDGE_INT_MAP_V  0x1F
#define DPORT_PRO_TG1_LACT_EDGE_INT_MAP_S  0

#define DPORT_PRO_MEM_IA_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x1E4)
/* DPORT_PRO_MEM_IA_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_MEM_IA_INT_MAP  0x0000001F
#define DPORT_PRO_MEM_IA_INT_MAP_M  ((DPORT_PRO_MEM_IA_INT_MAP_V)<<(DPORT_PRO_MEM_IA_INT_MAP_S))
#define DPORT_PRO_MEM_IA_INT_MAP_V  0x1F
#define DPORT_PRO_MEM_IA_INT_MAP_S  0

#define DPORT_PRO_CACHE_IA_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x1E8)
/* DPORT_PRO_CACHE_IA_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_CACHE_IA_INT_MAP  0x0000001F
#define DPORT_PRO_CACHE_IA_INT_MAP_M  ((DPORT_PRO_CACHE_IA_INT_MAP_V)<<(DPORT_PRO_CACHE_IA_INT_MAP_S))
#define DPORT_PRO_CACHE_IA_INT_MAP_V  0x1F
#define DPORT_PRO_CACHE_IA_INT_MAP_S  0

#define DPORT_SYSTIMER_TARGET0_EDGE_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x1EC)
/* DPORT_PRO_SYSTIMER_TARGET0_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_SYSTIMER_TARGET0_INT_MAP  0x0000001F
#define DPORT_PRO_SYSTIMER_TARGET0_INT_MAP_M  ((DPORT_PRO_SYSTIMER_TARGET0_INT_MAP_V)<<(DPORT_PRO_SYSTIMER_TARGET0_INT_MAP_S))
#define DPORT_PRO_SYSTIMER_TARGET0_INT_MAP_V  0x1F
#define DPORT_PRO_SYSTIMER_TARGET0_INT_MAP_S  0

#define DPORT_SYSTIMER_TARGET1_EDGE_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x1F0)
/* DPORT_PRO_SYSTIMER_TARGET1_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_SYSTIMER_TARGET1_INT_MAP  0x0000001F
#define DPORT_PRO_SYSTIMER_TARGET1_INT_MAP_M  ((DPORT_PRO_SYSTIMER_TARGET1_INT_MAP_V)<<(DPORT_PRO_SYSTIMER_TARGET1_INT_MAP_S))
#define DPORT_PRO_SYSTIMER_TARGET1_INT_MAP_V  0x1F
#define DPORT_PRO_SYSTIMER_TARGET1_INT_MAP_S  0

#define DPORT_SYSTIMER_TARGET2_EDGE_INT_MAP_REG          (DR_REG_DPORT_BASE + 0x1F4)
/* DPORT_PRO_SYSTIMER_TARGET2_INT_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_SYSTIMER_TARGET2_INT_MAP  0x0000001F
#define DPORT_PRO_SYSTIMER_TARGET2_INT_MAP_M  ((DPORT_PRO_SYSTIMER_TARGET2_INT_MAP_V)<<(DPORT_PRO_SYSTIMER_TARGET2_INT_MAP_S))
#define DPORT_PRO_SYSTIMER_TARGET2_INT_MAP_V  0x1F
#define DPORT_PRO_SYSTIMER_TARGET2_INT_MAP_S  0

#define DPORT_PRO_ASSIST_DEBUG_INTR_MAP_REG          (DR_REG_DPORT_BASE + 0x1F8)
/* DPORT_PRO_ASSIST_DEBUG_INTR_MAP : R/W ;bitpos:[4:0] ;default: 5'd16 ; */
/*description: */
#define DPORT_PRO_ASSIST_DEBUG_INTR_MAP  0x0000001F
#define DPORT_PRO_ASSIST_DEBUG_INTR_MAP_M  ((DPORT_PRO_ASSIST_DEBUG_INTR_MAP_V)<<(DPORT_PRO_ASSIST_DEBUG_INTR_MAP_S))
#define DPORT_PRO_ASSIST_DEBUG_INTR_MAP_V  0x1F
#define DPORT_PRO_ASSIST_DEBUG_INTR_MAP_S  0

#define DPORT_RSA_PD_CTRL_REG          (DR_REG_DPORT_BASE + 0x1FC)
/* DPORT_RSA_PD : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: */
#define DPORT_RSA_PD  (BIT(0))
#define DPORT_RSA_PD_M  (BIT(0))
#define DPORT_RSA_PD_V  0x1
#define DPORT_RSA_PD_S  0

#define DPORT_FRONT_END_MEM_PD_REG          (DR_REG_DPORT_BASE + 0x200)
/* DPORT_DC_MEM_FORCE_PD : R/W ;bitpos:[5] ;default: 1'b0 ; */
/*description: */
#define DPORT_DC_MEM_FORCE_PD  (BIT(5))
#define DPORT_DC_MEM_FORCE_PD_M  (BIT(5))
#define DPORT_DC_MEM_FORCE_PD_V  0x1
#define DPORT_DC_MEM_FORCE_PD_S  5
/* DPORT_DC_MEM_FORCE_PU : R/W ;bitpos:[4] ;default: 1'b1 ; */
/*description: */
#define DPORT_DC_MEM_FORCE_PU  (BIT(4))
#define DPORT_DC_MEM_FORCE_PU_M  (BIT(4))
#define DPORT_DC_MEM_FORCE_PU_V  0x1
#define DPORT_DC_MEM_FORCE_PU_S  4
/* DPORT_PBUS_MEM_FORCE_PD : R/W ;bitpos:[3] ;default: 1'b0 ; */
/*description: */
#define DPORT_PBUS_MEM_FORCE_PD  (BIT(3))
#define DPORT_PBUS_MEM_FORCE_PD_M  (BIT(3))
#define DPORT_PBUS_MEM_FORCE_PD_V  0x1
#define DPORT_PBUS_MEM_FORCE_PD_S  3
/* DPORT_PBUS_MEM_FORCE_PU : R/W ;bitpos:[2] ;default: 1'b1 ; */
/*description: */
#define DPORT_PBUS_MEM_FORCE_PU  (BIT(2))
#define DPORT_PBUS_MEM_FORCE_PU_M  (BIT(2))
#define DPORT_PBUS_MEM_FORCE_PU_V  0x1
#define DPORT_PBUS_MEM_FORCE_PU_S  2
/* DPORT_AGC_MEM_FORCE_PD : R/W ;bitpos:[1] ;default: 1'b0 ; */
/*description: */
#define DPORT_AGC_MEM_FORCE_PD  (BIT(1))
#define DPORT_AGC_MEM_FORCE_PD_M  (BIT(1))
#define DPORT_AGC_MEM_FORCE_PD_V  0x1
#define DPORT_AGC_MEM_FORCE_PD_S  1
/* DPORT_AGC_MEM_FORCE_PU : R/W ;bitpos:[0] ;default: 1'b1 ; */
/*description: */
#define DPORT_AGC_MEM_FORCE_PU  (BIT(0))
#define DPORT_AGC_MEM_FORCE_PU_M  (BIT(0))
#define DPORT_AGC_MEM_FORCE_PU_V  0x1
#define DPORT_AGC_MEM_FORCE_PU_S  0

#define DPORT_MEM_ACCESS_DBUG0_REG          (DR_REG_DPORT_BASE + 0x204)
/* DPORT_AHBLITE_IA : RO ;bitpos:[24:23] ;default: 2'b0 ; */
/*description: */
#define DPORT_AHBLITE_IA  0x00000003
#define DPORT_AHBLITE_IA_M  ((DPORT_AHBLITE_IA_V)<<(DPORT_AHBLITE_IA_S))
#define DPORT_AHBLITE_IA_V  0x3
#define DPORT_AHBLITE_IA_S  23
/* DPORT_PRO_DPORT_IA : RO ;bitpos:[22:18] ;default: 5'b0 ; */
/*description: */
#define DPORT_PRO_DPORT_IA  0x0000001F
#define DPORT_PRO_DPORT_IA_M  ((DPORT_PRO_DPORT_IA_V)<<(DPORT_PRO_DPORT_IA_S))
#define DPORT_PRO_DPORT_IA_V  0x1F
#define DPORT_PRO_DPORT_IA_S  18
/* DPORT_PRO_INTERNAL_SRAM_IA : RO ;bitpos:[17:5] ;default: 13'b0 ; */
/*description: */
#define DPORT_PRO_INTERNAL_SRAM_IA  0x00001FFF
#define DPORT_PRO_INTERNAL_SRAM_IA_M  ((DPORT_PRO_INTERNAL_SRAM_IA_V)<<(DPORT_PRO_INTERNAL_SRAM_IA_S))
#define DPORT_PRO_INTERNAL_SRAM_IA_V  0x1FFF
#define DPORT_PRO_INTERNAL_SRAM_IA_S  5
/* DPORT_PRO_SHARE_ROM_IA : RO ;bitpos:[4:2] ;default: 3'b0 ; */
/*description: */
#define DPORT_PRO_SHARE_ROM_IA  0x00000007
#define DPORT_PRO_SHARE_ROM_IA_M  ((DPORT_PRO_SHARE_ROM_IA_V)<<(DPORT_PRO_SHARE_ROM_IA_S))
#define DPORT_PRO_SHARE_ROM_IA_V  0x7
#define DPORT_PRO_SHARE_ROM_IA_S  2
/* DPORT_PRO_ROM_IA : RO ;bitpos:[1:0] ;default: 2'b0 ; */
/*description: */
#define DPORT_PRO_ROM_IA  0x00000003
#define DPORT_PRO_ROM_IA_M  ((DPORT_PRO_ROM_IA_V)<<(DPORT_PRO_ROM_IA_S))
#define DPORT_PRO_ROM_IA_V  0x3
#define DPORT_PRO_ROM_IA_S  0

#define DPORT_MEM_ACCESS_DBUG1_REG          (DR_REG_DPORT_BASE + 0x208)
/* DPORT_APP_DPORT_IA : RO ;bitpos:[21:17] ;default: 5'b0 ; */
/*description: */
#define DPORT_APP_DPORT_IA  0x0000001F
#define DPORT_APP_DPORT_IA_M  ((DPORT_APP_DPORT_IA_V)<<(DPORT_APP_DPORT_IA_S))
#define DPORT_APP_DPORT_IA_V  0x1F
#define DPORT_APP_DPORT_IA_S  17
/* DPORT_APP_INTERNAL_SRAM_IA : RO ;bitpos:[16:5] ;default: 12'b0 ; */
/*description: */
#define DPORT_APP_INTERNAL_SRAM_IA  0x00000FFF
#define DPORT_APP_INTERNAL_SRAM_IA_M  ((DPORT_APP_INTERNAL_SRAM_IA_V)<<(DPORT_APP_INTERNAL_SRAM_IA_S))
#define DPORT_APP_INTERNAL_SRAM_IA_V  0xFFF
#define DPORT_APP_INTERNAL_SRAM_IA_S  5
/* DPORT_APP_SHARE_ROM_IA : RO ;bitpos:[4:2] ;default: 3'b0 ; */
/*description: */
#define DPORT_APP_SHARE_ROM_IA  0x00000007
#define DPORT_APP_SHARE_ROM_IA_M  ((DPORT_APP_SHARE_ROM_IA_V)<<(DPORT_APP_SHARE_ROM_IA_S))
#define DPORT_APP_SHARE_ROM_IA_V  0x7
#define DPORT_APP_SHARE_ROM_IA_S  2
/* DPORT_APP_ROM_IA : RO ;bitpos:[1:0] ;default: 2'b0 ; */
/*description: */
#define DPORT_APP_ROM_IA  0x00000003
#define DPORT_APP_ROM_IA_M  ((DPORT_APP_ROM_IA_V)<<(DPORT_APP_ROM_IA_S))
#define DPORT_APP_ROM_IA_V  0x3
#define DPORT_APP_ROM_IA_S  0

#define DPORT_PRO_MEM_IA_INT_CTRL_REG          (DR_REG_DPORT_BASE + 0x20C)
/* DPORT_PRO_MEM_IA_INT_CLR : R/W ;bitpos:[25] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_MEM_IA_INT_CLR  (BIT(25))
#define DPORT_PRO_MEM_IA_INT_CLR_M  (BIT(25))
#define DPORT_PRO_MEM_IA_INT_CLR_V  0x1
#define DPORT_PRO_MEM_IA_INT_CLR_S  25
/* DPORT_PRO_MEM_IA_INT_EN : R/W ;bitpos:[24:0] ;default: 25'b0 ; */
/*description: */
#define DPORT_PRO_MEM_IA_INT_EN  0x01FFFFFF
#define DPORT_PRO_MEM_IA_INT_EN_M  ((DPORT_PRO_MEM_IA_INT_EN_V)<<(DPORT_PRO_MEM_IA_INT_EN_S))
#define DPORT_PRO_MEM_IA_INT_EN_V  0x1FFFFFF
#define DPORT_PRO_MEM_IA_INT_EN_S  0

#define DPORT_PRO_CACHE_IA_INT_EN_REG          (DR_REG_DPORT_BASE + 0x210)
/* DPORT_PRO_CACHE_INT_CLR : R/W ;bitpos:[15] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_CACHE_INT_CLR  (BIT(15))
#define DPORT_PRO_CACHE_INT_CLR_M  (BIT(15))
#define DPORT_PRO_CACHE_INT_CLR_V  0x1
#define DPORT_PRO_CACHE_INT_CLR_S  15
/* DPORT_PRO_CACHE_IA_INT_EN : R/W ;bitpos:[14:1] ;default: 14'b0 ; */
/*description: */
#define DPORT_PRO_CACHE_IA_INT_EN  0x00003FFF
#define DPORT_PRO_CACHE_IA_INT_EN_M  ((DPORT_PRO_CACHE_IA_INT_EN_V)<<(DPORT_PRO_CACHE_IA_INT_EN_S))
#define DPORT_PRO_CACHE_IA_INT_EN_V  0x3FFF
#define DPORT_PRO_CACHE_IA_INT_EN_S  1

/* Contents of DPORT_CACHE_IA_INT_EN field: */
/* DPORT_CACHE_IA_INT_PRO_OPPOSITE : R/W ;bitpos:[6] ;default: 1'b0 ; */
/*description: PRO CPU invalid access to APP CPU cache when cache disabled */
#define DPORT_CACHE_IA_INT_PRO_OPPOSITE    BIT(6)
#define DPORT_CACHE_IA_INT_PRO_OPPOSITE_M  BIT(6)
#define DPORT_CACHE_IA_INT_PRO_OPPOSITE_V  (1)
#define DPORT_CACHE_IA_INT_PRO_OPPOSITE_S  (6)
/* DPORT_CACHE_IA_INT_PRO_DRAM1 : R/W ;bitpos:[5] ;default: 1'b0 ; */
/*description: PRO CPU invalid access to DRAM1 when cache is disabled */
#define DPORT_CACHE_IA_INT_PRO_DRAM1    BIT(5)
#define DPORT_CACHE_IA_INT_PRO_DRAM1_M  BIT(5)
#define DPORT_CACHE_IA_INT_PRO_DRAM1_V  (1)
#define DPORT_CACHE_IA_INT_PRO_DRAM1_S  (5)
/* DPORT_CACHE_IA_INT_PRO_IROM0 : R/W ;bitpos:[4] ;default: 1'b0 ; */
/*description: PRO CPU invalid access to IROM0 when cache is disabled */
#define DPORT_CACHE_IA_INT_PRO_IROM0    BIT(4)
#define DPORT_CACHE_IA_INT_PRO_IROM0_M  BIT(4)
#define DPORT_CACHE_IA_INT_PRO_IROM0_V  (1)
#define DPORT_CACHE_IA_INT_PRO_IROM0_S  (4)
/* DPORT_CACHE_IA_INT_PRO_IRAM1 : R/W ;bitpos:[3] ;default: 1'b0 ; */
/*description: PRO CPU invalid access to IRAM1 when cache is disabled */
#define DPORT_CACHE_IA_INT_PRO_IRAM1    BIT(3)
#define DPORT_CACHE_IA_INT_PRO_IRAM1_M  BIT(3)
#define DPORT_CACHE_IA_INT_PRO_IRAM1_V  (1)
#define DPORT_CACHE_IA_INT_PRO_IRAM1_S  (3)
/* DPORT_CACHE_IA_INT_PRO_IRAM0 : R/W ;bitpos:[2] ;default: 1'b0 ; */
/*description: PRO CPU invalid access to IRAM0 when cache is disabled */
#define DPORT_CACHE_IA_INT_PRO_IRAM0    BIT(2)
#define DPORT_CACHE_IA_INT_PRO_IRAM0_M  BIT(2)
#define DPORT_CACHE_IA_INT_PRO_IRAM0_V  (1)
#define DPORT_CACHE_IA_INT_PRO_IRAM0_S  (2)
/* DPORT_CACHE_IA_INT_PRO_DROM0 : R/W ;bitpos:[1] ;default: 1'b0 ; */
/*description: PRO CPU invalid access to DROM0 when cache is disabled */
#define DPORT_CACHE_IA_INT_PRO_DROM0    BIT(1)
#define DPORT_CACHE_IA_INT_PRO_DROM0_M  BIT(1)
#define DPORT_CACHE_IA_INT_PRO_DROM0_V  (1)
#define DPORT_CACHE_IA_INT_PRO_DROM0_S  (1)

/* DPORT_PRO_CACHE_DBG_EN : R/W ;bitpos:[0] ;default: 1'b1 ; */
/*description: */
#define DPORT_PRO_CACHE_DBG_EN  (BIT(0))
#define DPORT_PRO_CACHE_DBG_EN_M  (BIT(0))
#define DPORT_PRO_CACHE_DBG_EN_V  0x1
#define DPORT_PRO_CACHE_DBG_EN_S  0

#define DPORT_PRO_DCACHE_DBUG1_REG          (DR_REG_DPORT_BASE + 0x214)
/* DPORT_PRO_SLAVE_WDATA_V : RO ;bitpos:[22] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_SLAVE_WDATA_V  (BIT(22))
#define DPORT_PRO_SLAVE_WDATA_V_M  (BIT(22))
#define DPORT_PRO_SLAVE_WDATA_V_V  0x1
#define DPORT_PRO_SLAVE_WDATA_V_S  22
/* DPORT_PRO_SLAVE_WR : RO ;bitpos:[21] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_SLAVE_WR  (BIT(21))
#define DPORT_PRO_SLAVE_WR_M  (BIT(21))
#define DPORT_PRO_SLAVE_WR_V  0x1
#define DPORT_PRO_SLAVE_WR_S  21
/* DPORT_PRO_SYNCSIZECHECKFAIL : RO ;bitpos:[7] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_SYNCSIZECHECKFAIL  (BIT(7))
#define DPORT_PRO_SYNCSIZECHECKFAIL_M  (BIT(7))
#define DPORT_PRO_SYNCSIZECHECKFAIL_V  0x1
#define DPORT_PRO_SYNCSIZECHECKFAIL_S  7
/* DPORT_PRO_CACHE_IA : RO ;bitpos:[6:1] ;default: 6'b0 ; */
/*description: */
#define DPORT_PRO_CACHE_IA  0x0000003F
#define DPORT_PRO_CACHE_IA_M  ((DPORT_PRO_CACHE_IA_V)<<(DPORT_PRO_CACHE_IA_S))
#define DPORT_PRO_CACHE_IA_V  0x3F
#define DPORT_PRO_CACHE_IA_S  1
/* DPORT_PRO_CACHE_MMU_IA : RO ;bitpos:[0] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_CACHE_MMU_IA  (BIT(0))
#define DPORT_PRO_CACHE_MMU_IA_M  (BIT(0))
#define DPORT_PRO_CACHE_MMU_IA_V  0x1
#define DPORT_PRO_CACHE_MMU_IA_S  0

#define DPORT_PRO_DCACHE_DBUG2_REG          (DR_REG_DPORT_BASE + 0x218)
/* DPORT_PRO_CACHE_STATE : RO ;bitpos:[11:0] ;default: 12'b0 ; */
/*description: */
#define DPORT_PRO_CACHE_STATE  0x00000FFF
#define DPORT_PRO_CACHE_STATE_M  ((DPORT_PRO_CACHE_STATE_V)<<(DPORT_PRO_CACHE_STATE_S))
#define DPORT_PRO_CACHE_STATE_V  0xFFF
#define DPORT_PRO_CACHE_STATE_S  0

#define DPORT_PRO_DCACHE_DBUG3_REG          (DR_REG_DPORT_BASE + 0x21C)
/* DPORT_PRO_CACHE_IRAM0_PID_ERROR : RO ;bitpos:[15] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_CACHE_IRAM0_PID_ERROR  (BIT(15))
#define DPORT_PRO_CACHE_IRAM0_PID_ERROR_M  (BIT(15))
#define DPORT_PRO_CACHE_IRAM0_PID_ERROR_V  0x1
#define DPORT_PRO_CACHE_IRAM0_PID_ERROR_S  15
/* DPORT_PRO_CPU_DISABLED_CACHE_IA : RO ;bitpos:[14:9] ;default: 6'b0 ; */
/*description: */
#define DPORT_PRO_CPU_DISABLED_CACHE_IA  0x0000003F
#define DPORT_PRO_CPU_DISABLED_CACHE_IA_M  ((DPORT_PRO_CPU_DISABLED_CACHE_IA_V)<<(DPORT_PRO_CPU_DISABLED_CACHE_IA_S))
#define DPORT_PRO_CPU_DISABLED_CACHE_IA_V  0x3F
#define DPORT_PRO_CPU_DISABLED_CACHE_IA_S  9

#define DPORT_PRO_DCACHE_DBUG4_REG          (DR_REG_DPORT_BASE + 0x220)
/* DPORT_PRO_DRAM1ADDR0_IA : RO ;bitpos:[19:0] ;default: 20'b0 ; */
/*description: */
#define DPORT_PRO_DRAM1ADDR0_IA  0x000FFFFF
#define DPORT_PRO_DRAM1ADDR0_IA_M  ((DPORT_PRO_DRAM1ADDR0_IA_V)<<(DPORT_PRO_DRAM1ADDR0_IA_S))
#define DPORT_PRO_DRAM1ADDR0_IA_V  0xFFFFF
#define DPORT_PRO_DRAM1ADDR0_IA_S  0

#define DPORT_PRO_DCACHE_DBUG5_REG          (DR_REG_DPORT_BASE + 0x224)
/* DPORT_PRO_DROM0ADDR0_IA : RO ;bitpos:[19:0] ;default: 20'b0 ; */
/*description: */
#define DPORT_PRO_DROM0ADDR0_IA  0x000FFFFF
#define DPORT_PRO_DROM0ADDR0_IA_M  ((DPORT_PRO_DROM0ADDR0_IA_V)<<(DPORT_PRO_DROM0ADDR0_IA_S))
#define DPORT_PRO_DROM0ADDR0_IA_V  0xFFFFF
#define DPORT_PRO_DROM0ADDR0_IA_S  0

#define DPORT_PRO_DCACHE_DBUG6_REG          (DR_REG_DPORT_BASE + 0x228)
/* DPORT_PRO_IRAM0ADDR_IA : RO ;bitpos:[19:0] ;default: 20'b0 ; */
/*description: */
#define DPORT_PRO_IRAM0ADDR_IA  0x000FFFFF
#define DPORT_PRO_IRAM0ADDR_IA_M  ((DPORT_PRO_IRAM0ADDR_IA_V)<<(DPORT_PRO_IRAM0ADDR_IA_S))
#define DPORT_PRO_IRAM0ADDR_IA_V  0xFFFFF
#define DPORT_PRO_IRAM0ADDR_IA_S  0

#define DPORT_PRO_DCACHE_DBUG7_REG          (DR_REG_DPORT_BASE + 0x22C)
/* DPORT_PRO_IRAM1ADDR_IA : RO ;bitpos:[19:0] ;default: 20'b0 ; */
/*description: */
#define DPORT_PRO_IRAM1ADDR_IA  0x000FFFFF
#define DPORT_PRO_IRAM1ADDR_IA_M  ((DPORT_PRO_IRAM1ADDR_IA_V)<<(DPORT_PRO_IRAM1ADDR_IA_S))
#define DPORT_PRO_IRAM1ADDR_IA_V  0xFFFFF
#define DPORT_PRO_IRAM1ADDR_IA_S  0

#define DPORT_PRO_DCACHE_DBUG8_REG          (DR_REG_DPORT_BASE + 0x230)
/* DPORT_PRO_IROM0ADDR_IA : RO ;bitpos:[19:0] ;default: 20'b0 ; */
/*description: */
#define DPORT_PRO_IROM0ADDR_IA  0x000FFFFF
#define DPORT_PRO_IROM0ADDR_IA_M  ((DPORT_PRO_IROM0ADDR_IA_V)<<(DPORT_PRO_IROM0ADDR_IA_S))
#define DPORT_PRO_IROM0ADDR_IA_V  0xFFFFF
#define DPORT_PRO_IROM0ADDR_IA_S  0

#define DPORT_PRO_DCACHE_DBUG9_REG          (DR_REG_DPORT_BASE + 0x234)
/* DPORT_PRO_OPSDRAMADDR_IA : RO ;bitpos:[19:0] ;default: 20'b0 ; */
/*description: */
#define DPORT_PRO_OPSDRAMADDR_IA  0x000FFFFF
#define DPORT_PRO_OPSDRAMADDR_IA_M  ((DPORT_PRO_OPSDRAMADDR_IA_V)<<(DPORT_PRO_OPSDRAMADDR_IA_S))
#define DPORT_PRO_OPSDRAMADDR_IA_V  0xFFFFF
#define DPORT_PRO_OPSDRAMADDR_IA_S  0

#define DPORT_SECURE_BOOT_CTRL_REG          (DR_REG_DPORT_BASE + 0x238)
/* DPORT_SW_BOOTLOADER_SEL : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: */
#define DPORT_SW_BOOTLOADER_SEL  (BIT(0))
#define DPORT_SW_BOOTLOADER_SEL_M  (BIT(0))
#define DPORT_SW_BOOTLOADER_SEL_V  0x1
#define DPORT_SW_BOOTLOADER_SEL_S  0

#define DPORT_SPI_DMA_CHAN_SEL_REG          (DR_REG_DPORT_BASE + 0x23C)
/* DPORT_SPI3_DMA_CHAN_SEL : R/W ;bitpos:[5:4] ;default: 2'b00 ; */
/*description: */
#define DPORT_SPI3_DMA_CHAN_SEL  0x00000003
#define DPORT_SPI3_DMA_CHAN_SEL_M  ((DPORT_SPI3_DMA_CHAN_SEL_V)<<(DPORT_SPI3_DMA_CHAN_SEL_S))
#define DPORT_SPI3_DMA_CHAN_SEL_V  0x3
#define DPORT_SPI3_DMA_CHAN_SEL_S  4
/* DPORT_SPI2_DMA_CHAN_SEL : R/W ;bitpos:[3:2] ;default: 2'b00 ; */
/*description: */
#define DPORT_SPI2_DMA_CHAN_SEL  0x00000003
#define DPORT_SPI2_DMA_CHAN_SEL_M  ((DPORT_SPI2_DMA_CHAN_SEL_V)<<(DPORT_SPI2_DMA_CHAN_SEL_S))
#define DPORT_SPI2_DMA_CHAN_SEL_V  0x3
#define DPORT_SPI2_DMA_CHAN_SEL_S  2
/* DPORT_SPI1_DMA_CHAN_SEL : R/W ;bitpos:[1:0] ;default: 2'b00 ; */
/*description: */
#define DPORT_SPI1_DMA_CHAN_SEL  0x00000003
#define DPORT_SPI1_DMA_CHAN_SEL_M  ((DPORT_SPI1_DMA_CHAN_SEL_V)<<(DPORT_SPI1_DMA_CHAN_SEL_S))
#define DPORT_SPI1_DMA_CHAN_SEL_V  0x3
#define DPORT_SPI1_DMA_CHAN_SEL_S  0

#define DPORT_PRO_VECBASE_CTRL_REG          (DR_REG_DPORT_BASE + 0x240)
/* DPORT_PRO_OUT_VECBASE_SEL : R/W ;bitpos:[1:0] ;default: 2'b0 ; */
/*description: */
#define DPORT_PRO_OUT_VECBASE_SEL  0x00000003
#define DPORT_PRO_OUT_VECBASE_SEL_M  ((DPORT_PRO_OUT_VECBASE_SEL_V)<<(DPORT_PRO_OUT_VECBASE_SEL_S))
#define DPORT_PRO_OUT_VECBASE_SEL_V  0x3
#define DPORT_PRO_OUT_VECBASE_SEL_S  0

#define DPORT_PRO_VECBASE_SET_REG          (DR_REG_DPORT_BASE + 0x244)
/* DPORT_PRO_OUT_VECBASE_REG : R/W ;bitpos:[21:0] ;default: 22'b0 ; */
/*description: */
#define DPORT_PRO_OUT_VECBASE_REG  0x003FFFFF
#define DPORT_PRO_OUT_VECBASE_REG_M  ((DPORT_PRO_OUT_VECBASE_REG_V)<<(DPORT_PRO_OUT_VECBASE_REG_S))
#define DPORT_PRO_OUT_VECBASE_REG_V  0x3FFFFF
#define DPORT_PRO_OUT_VECBASE_REG_S  0

#define DPORT_APP_VECBASE_CTRL_REG          (DR_REG_DPORT_BASE + 0x248)
/* DPORT_APP_OUT_VECBASE_SEL : R/W ;bitpos:[1:0] ;default: 2'b0 ; */
/*description: */
#define DPORT_APP_OUT_VECBASE_SEL  0x00000003
#define DPORT_APP_OUT_VECBASE_SEL_M  ((DPORT_APP_OUT_VECBASE_SEL_V)<<(DPORT_APP_OUT_VECBASE_SEL_S))
#define DPORT_APP_OUT_VECBASE_SEL_V  0x3
#define DPORT_APP_OUT_VECBASE_SEL_S  0

#define DPORT_APP_VECBASE_SET_REG          (DR_REG_DPORT_BASE + 0x24C)
/* DPORT_APP_OUT_VECBASE_REG : R/W ;bitpos:[21:0] ;default: 22'b0 ; */
/*description: */
#define DPORT_APP_OUT_VECBASE_REG  0x003FFFFF
#define DPORT_APP_OUT_VECBASE_REG_M  ((DPORT_APP_OUT_VECBASE_REG_V)<<(DPORT_APP_OUT_VECBASE_REG_S))
#define DPORT_APP_OUT_VECBASE_REG_V  0x3FFFFF
#define DPORT_APP_OUT_VECBASE_REG_S  0

#define DPORT_PRO_CMMU_EXC_RECORD0_REG          (DR_REG_DPORT_BASE + 0x250)
/* DPORT_PRO_CMMU_EXC_RECORD0 : RO ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_PRO_CMMU_EXC_RECORD0  0xFFFFFFFF
#define DPORT_PRO_CMMU_EXC_RECORD0_M  ((DPORT_PRO_CMMU_EXC_RECORD0_V)<<(DPORT_PRO_CMMU_EXC_RECORD0_S))
#define DPORT_PRO_CMMU_EXC_RECORD0_V  0xFFFFFFFF
#define DPORT_PRO_CMMU_EXC_RECORD0_S  0

#define DPORT_PRO_CMMU_EXC_RECORD1_REG          (DR_REG_DPORT_BASE + 0x254)
/* DPORT_PRO_CMMU_EXC_RECORD1 : RO ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_PRO_CMMU_EXC_RECORD1  0xFFFFFFFF
#define DPORT_PRO_CMMU_EXC_RECORD1_M  ((DPORT_PRO_CMMU_EXC_RECORD1_V)<<(DPORT_PRO_CMMU_EXC_RECORD1_S))
#define DPORT_PRO_CMMU_EXC_RECORD1_V  0xFFFFFFFF
#define DPORT_PRO_CMMU_EXC_RECORD1_S  0

#define DPORT_APP_CMMU_EXC_RECORD0_REG          (DR_REG_DPORT_BASE + 0x258)
/* DPORT_APP_CMMU_EXC_RECORD0 : RO ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_APP_CMMU_EXC_RECORD0  0xFFFFFFFF
#define DPORT_APP_CMMU_EXC_RECORD0_M  ((DPORT_APP_CMMU_EXC_RECORD0_V)<<(DPORT_APP_CMMU_EXC_RECORD0_S))
#define DPORT_APP_CMMU_EXC_RECORD0_V  0xFFFFFFFF
#define DPORT_APP_CMMU_EXC_RECORD0_S  0

#define DPORT_APP_CMMU_EXC_RECORD1_REG          (DR_REG_DPORT_BASE + 0x25C)
/* DPORT_APP_CMMU_EXC_RECORD1 : RO ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_APP_CMMU_EXC_RECORD1  0xFFFFFFFF
#define DPORT_APP_CMMU_EXC_RECORD1_M  ((DPORT_APP_CMMU_EXC_RECORD1_V)<<(DPORT_APP_CMMU_EXC_RECORD1_S))
#define DPORT_APP_CMMU_EXC_RECORD1_V  0xFFFFFFFF
#define DPORT_APP_CMMU_EXC_RECORD1_S  0

#define DPORT_PRO_CACHE_MEM_SYNC0_REG          (DR_REG_DPORT_BASE + 0x260)
/* DPORT_PRO_MEMSYNCADDR : R/W ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_PRO_MEMSYNCADDR  0xFFFFFFFF
#define DPORT_PRO_MEMSYNCADDR_M  ((DPORT_PRO_MEMSYNCADDR_V)<<(DPORT_PRO_MEMSYNCADDR_S))
#define DPORT_PRO_MEMSYNCADDR_V  0xFFFFFFFF
#define DPORT_PRO_MEMSYNCADDR_S  0

#define DPORT_PRO_CACHE_MEM_SYNC1_REG          (DR_REG_DPORT_BASE + 0x264)
/* DPORT_PRO_MEMSYNCSIZE : R/W ;bitpos:[22:0] ;default: 23'h400000 ; */
/*description: */
#define DPORT_PRO_MEMSYNCSIZE  0x007FFFFF
#define DPORT_PRO_MEMSYNCSIZE_M  ((DPORT_PRO_MEMSYNCSIZE_V)<<(DPORT_PRO_MEMSYNCSIZE_S))
#define DPORT_PRO_MEMSYNCSIZE_V  0x7FFFFF
#define DPORT_PRO_MEMSYNCSIZE_S  0

#define DPORT_PRO_CACHE_PRELOADADDR_REG          (DR_REG_DPORT_BASE + 0x268)
/* DPORT_PRO_CACHE_PRELOADADDR : R/W ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_PRO_CACHE_PRELOADADDR  0xFFFFFFFF
#define DPORT_PRO_CACHE_PRELOADADDR_M  ((DPORT_PRO_CACHE_PRELOADADDR_V)<<(DPORT_PRO_CACHE_PRELOADADDR_S))
#define DPORT_PRO_CACHE_PRELOADADDR_V  0xFFFFFFFF
#define DPORT_PRO_CACHE_PRELOADADDR_S  0

#define DPORT_PRO_CACHE_PRELOADSIZE_REG          (DR_REG_DPORT_BASE + 0x26C)
/* DPORT_PRO_CACHE_PRELOADSIZE : R/W ;bitpos:[15:0] ;default: 16'h8000 ; */
/*description: */
#define DPORT_PRO_CACHE_PRELOADSIZE  0x0000FFFF
#define DPORT_PRO_CACHE_PRELOADSIZE_M  ((DPORT_PRO_CACHE_PRELOADSIZE_V)<<(DPORT_PRO_CACHE_PRELOADSIZE_S))
#define DPORT_PRO_CACHE_PRELOADSIZE_V  0xFFFF
#define DPORT_PRO_CACHE_PRELOADSIZE_S  0

#define DPORT_PRO_CACHE_FLASH_RD_MISS_CNT_REG          (DR_REG_DPORT_BASE + 0x270)
/* DPORT_PRO_CPUFLASH_RD_MISSCNT : RO ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_PRO_CPUFLASH_RD_MISSCNT  0xFFFFFFFF
#define DPORT_PRO_CPUFLASH_RD_MISSCNT_M  ((DPORT_PRO_CPUFLASH_RD_MISSCNT_V)<<(DPORT_PRO_CPUFLASH_RD_MISSCNT_S))
#define DPORT_PRO_CPUFLASH_RD_MISSCNT_V  0xFFFFFFFF
#define DPORT_PRO_CPUFLASH_RD_MISSCNT_S  0

#define DPORT_PRO_CACHE_SRAM_RD_MISS_CNT_REG          (DR_REG_DPORT_BASE + 0x274)
/* DPORT_PRO_CPUSRAM_RD_MISSCNT : RO ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_PRO_CPUSRAM_RD_MISSCNT  0xFFFFFFFF
#define DPORT_PRO_CPUSRAM_RD_MISSCNT_M  ((DPORT_PRO_CPUSRAM_RD_MISSCNT_V)<<(DPORT_PRO_CPUSRAM_RD_MISSCNT_S))
#define DPORT_PRO_CPUSRAM_RD_MISSCNT_V  0xFFFFFFFF
#define DPORT_PRO_CPUSRAM_RD_MISSCNT_S  0

#define DPORT_PRO_CACHE_SRAM_WR_MISS_CNT_REG          (DR_REG_DPORT_BASE + 0x278)
/* DPORT_PRO_CPUSRAM_WR_MISSCNT : RO ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_PRO_CPUSRAM_WR_MISSCNT  0xFFFFFFFF
#define DPORT_PRO_CPUSRAM_WR_MISSCNT_M  ((DPORT_PRO_CPUSRAM_WR_MISSCNT_V)<<(DPORT_PRO_CPUSRAM_WR_MISSCNT_S))
#define DPORT_PRO_CPUSRAM_WR_MISSCNT_V  0xFFFFFFFF
#define DPORT_PRO_CPUSRAM_WR_MISSCNT_S  0

#define DPORT_PRO_CACHE_FLASH_RD_WB_CNT_REG          (DR_REG_DPORT_BASE + 0x27C)
/* DPORT_PRO_CPUFLASH_RD_WBCNT : RO ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_PRO_CPUFLASH_RD_WBCNT  0xFFFFFFFF
#define DPORT_PRO_CPUFLASH_RD_WBCNT_M  ((DPORT_PRO_CPUFLASH_RD_WBCNT_V)<<(DPORT_PRO_CPUFLASH_RD_WBCNT_S))
#define DPORT_PRO_CPUFLASH_RD_WBCNT_V  0xFFFFFFFF
#define DPORT_PRO_CPUFLASH_RD_WBCNT_S  0

#define DPORT_PRO_CACHE_SRAM_RD_WB_CNT_REG          (DR_REG_DPORT_BASE + 0x280)
/* DPORT_PRO_CPUSRAM_RD_WBCNT : RO ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_PRO_CPUSRAM_RD_WBCNT  0xFFFFFFFF
#define DPORT_PRO_CPUSRAM_RD_WBCNT_M  ((DPORT_PRO_CPUSRAM_RD_WBCNT_V)<<(DPORT_PRO_CPUSRAM_RD_WBCNT_S))
#define DPORT_PRO_CPUSRAM_RD_WBCNT_V  0xFFFFFFFF
#define DPORT_PRO_CPUSRAM_RD_WBCNT_S  0

#define DPORT_PRO_CACHE_SRAM_WR_WB_CNT_REG          (DR_REG_DPORT_BASE + 0x284)
/* DPORT_PRO_CPUSRAM_WR_WBCNT : RO ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_PRO_CPUSRAM_WR_WBCNT  0xFFFFFFFF
#define DPORT_PRO_CPUSRAM_WR_WBCNT_M  ((DPORT_PRO_CPUSRAM_WR_WBCNT_V)<<(DPORT_PRO_CPUSRAM_WR_WBCNT_S))
#define DPORT_PRO_CPUSRAM_WR_WBCNT_V  0xFFFFFFFF
#define DPORT_PRO_CPUSRAM_WR_WBCNT_S  0

#define DPORT_PRO_CACHE_FLASH_RD_CNT_REG          (DR_REG_DPORT_BASE + 0x288)
/* DPORT_PRO_CPUFLASH_RDCNT : RO ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_PRO_CPUFLASH_RDCNT  0xFFFFFFFF
#define DPORT_PRO_CPUFLASH_RDCNT_M  ((DPORT_PRO_CPUFLASH_RDCNT_V)<<(DPORT_PRO_CPUFLASH_RDCNT_S))
#define DPORT_PRO_CPUFLASH_RDCNT_V  0xFFFFFFFF
#define DPORT_PRO_CPUFLASH_RDCNT_S  0

#define DPORT_PRO_CACHE_SRAM_RD_CNT_REG          (DR_REG_DPORT_BASE + 0x28C)
/* DPORT_PRO_CPUSRAM_RDCNT : RO ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_PRO_CPUSRAM_RDCNT  0xFFFFFFFF
#define DPORT_PRO_CPUSRAM_RDCNT_M  ((DPORT_PRO_CPUSRAM_RDCNT_V)<<(DPORT_PRO_CPUSRAM_RDCNT_S))
#define DPORT_PRO_CPUSRAM_RDCNT_V  0xFFFFFFFF
#define DPORT_PRO_CPUSRAM_RDCNT_S  0

#define DPORT_PRO_CACHE_SRAM_WR_CNT_REG          (DR_REG_DPORT_BASE + 0x290)
/* DPORT_PRO_CPUSRAM_WRCNT : RO ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_PRO_CPUSRAM_WRCNT  0xFFFFFFFF
#define DPORT_PRO_CPUSRAM_WRCNT_M  ((DPORT_PRO_CPUSRAM_WRCNT_V)<<(DPORT_PRO_CPUSRAM_WRCNT_S))
#define DPORT_PRO_CPUSRAM_WRCNT_V  0xFFFFFFFF
#define DPORT_PRO_CPUSRAM_WRCNT_S  0

#define DPORT_PRO_CACHE_CPUQUITCHECK_CNT_REG          (DR_REG_DPORT_BASE + 0x294)
/* DPORT_PRO_CPUQUITCHECK_CNT : RO ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_PRO_CPUQUITCHECK_CNT  0xFFFFFFFF
#define DPORT_PRO_CPUQUITCHECK_CNT_M  ((DPORT_PRO_CPUQUITCHECK_CNT_V)<<(DPORT_PRO_CPUQUITCHECK_CNT_S))
#define DPORT_PRO_CPUQUITCHECK_CNT_V  0xFFFFFFFF
#define DPORT_PRO_CPUQUITCHECK_CNT_S  0

#define DPORT_PRO_CACHE_ACCESS_CNT_CLR_REG          (DR_REG_DPORT_BASE + 0x298)
/* DPORT_PRO_CACHE_CNT_OVERFLOW : RO ;bitpos:[1] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_CACHE_CNT_OVERFLOW  (BIT(1))
#define DPORT_PRO_CACHE_CNT_OVERFLOW_M  (BIT(1))
#define DPORT_PRO_CACHE_CNT_OVERFLOW_V  0x1
#define DPORT_PRO_CACHE_CNT_OVERFLOW_S  1
/* DPORT_PRO_CACHE_ACCESS_CNT_CLR : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_CACHE_ACCESS_CNT_CLR  (BIT(0))
#define DPORT_PRO_CACHE_ACCESS_CNT_CLR_M  (BIT(0))
#define DPORT_PRO_CACHE_ACCESS_CNT_CLR_V  0x1
#define DPORT_PRO_CACHE_ACCESS_CNT_CLR_S  0

#define DPORT_SWITCH_ICACHE_PATH_REG          (DR_REG_DPORT_BASE + 0x29C)
/* DPORT_SWITCH_ICACHE_PATH : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: */
#define DPORT_SWITCH_ICACHE_PATH  (BIT(0))
#define DPORT_SWITCH_ICACHE_PATH_M  (BIT(0))
#define DPORT_SWITCH_ICACHE_PATH_V  0x1
#define DPORT_SWITCH_ICACHE_PATH_S  0

#define DPORT_BUSTOEXTMEM_ENA_REG          (DR_REG_DPORT_BASE + 0x2A0)
/* DPORT_DMA_BLOCKSIZEMODE : R/W ;bitpos:[20:19] ;default: 2'b1 ; */
/*description: */
#define DPORT_DMA_BLOCKSIZEMODE  0x00000003
#define DPORT_DMA_BLOCKSIZEMODE_M  ((DPORT_DMA_BLOCKSIZEMODE_V)<<(DPORT_DMA_BLOCKSIZEMODE_S))
#define DPORT_DMA_BLOCKSIZEMODE_V  0x3
#define DPORT_DMA_BLOCKSIZEMODE_S  19
/* DPORT_SPI_DMA_TX_PID : R/W ;bitpos:[18:16] ;default: 3'd0 ; */
/*description: */
#define DPORT_SPI_DMA_TX_PID  0x00000007
#define DPORT_SPI_DMA_TX_PID_M  ((DPORT_SPI_DMA_TX_PID_V)<<(DPORT_SPI_DMA_TX_PID_S))
#define DPORT_SPI_DMA_TX_PID_V  0x7
#define DPORT_SPI_DMA_TX_PID_S  16
/* DPORT_SPI_DMA_RX_PID : R/W ;bitpos:[15:13] ;default: 3'd0 ; */
/*description: */
#define DPORT_SPI_DMA_RX_PID  0x00000007
#define DPORT_SPI_DMA_RX_PID_M  ((DPORT_SPI_DMA_RX_PID_V)<<(DPORT_SPI_DMA_RX_PID_S))
#define DPORT_SPI_DMA_RX_PID_V  0x7
#define DPORT_SPI_DMA_RX_PID_S  13
/* DPORT_I2S1_DMA_TX_PID : R/W ;bitpos:[12:10] ;default: 3'd0 ; */
/*description: */
#define DPORT_I2S1_DMA_TX_PID  0x00000007
#define DPORT_I2S1_DMA_TX_PID_M  ((DPORT_I2S1_DMA_TX_PID_V)<<(DPORT_I2S1_DMA_TX_PID_S))
#define DPORT_I2S1_DMA_TX_PID_V  0x7
#define DPORT_I2S1_DMA_TX_PID_S  10
/* DPORT_I2S1_DMA_RX_PID : R/W ;bitpos:[9:7] ;default: 3'd0 ; */
/*description: */
#define DPORT_I2S1_DMA_RX_PID  0x00000007
#define DPORT_I2S1_DMA_RX_PID_M  ((DPORT_I2S1_DMA_RX_PID_V)<<(DPORT_I2S1_DMA_RX_PID_S))
#define DPORT_I2S1_DMA_RX_PID_V  0x7
#define DPORT_I2S1_DMA_RX_PID_S  7
/* DPORT_I2S0_DMA_TX_PID : R/W ;bitpos:[6:4] ;default: 3'd0 ; */
/*description: */
#define DPORT_I2S0_DMA_TX_PID  0x00000007
#define DPORT_I2S0_DMA_TX_PID_M  ((DPORT_I2S0_DMA_TX_PID_V)<<(DPORT_I2S0_DMA_TX_PID_S))
#define DPORT_I2S0_DMA_TX_PID_V  0x7
#define DPORT_I2S0_DMA_TX_PID_S  4
/* DPORT_I2S0_DMA_RX_PID : R/W ;bitpos:[3:1] ;default: 3'd0 ; */
/*description: */
#define DPORT_I2S0_DMA_RX_PID  0x00000007
#define DPORT_I2S0_DMA_RX_PID_M  ((DPORT_I2S0_DMA_RX_PID_V)<<(DPORT_I2S0_DMA_RX_PID_S))
#define DPORT_I2S0_DMA_RX_PID_V  0x7
#define DPORT_I2S0_DMA_RX_PID_S  1
/* DPORT_BUSTOEXTMEM_ENA : R/W ;bitpos:[0] ;default: 1'b1 ; */
/*description: */
#define DPORT_BUSTOEXTMEM_ENA  (BIT(0))
#define DPORT_BUSTOEXTMEM_ENA_M  (BIT(0))
#define DPORT_BUSTOEXTMEM_ENA_V  0x1
#define DPORT_BUSTOEXTMEM_ENA_S  0

#define DPORT_PRO_ICACHE_CTRL_REG          (DR_REG_DPORT_BASE + 0x2A4)
/* DPORT_PRO_ICACHE_UNLOCK_DONE : RO ;bitpos:[26] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_UNLOCK_DONE  (BIT(26))
#define DPORT_PRO_ICACHE_UNLOCK_DONE_M  (BIT(26))
#define DPORT_PRO_ICACHE_UNLOCK_DONE_V  0x1
#define DPORT_PRO_ICACHE_UNLOCK_DONE_S  26
/* DPORT_PRO_ICACHE_UNLOCK_ENA : R/W ;bitpos:[25] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_UNLOCK_ENA  (BIT(25))
#define DPORT_PRO_ICACHE_UNLOCK_ENA_M  (BIT(25))
#define DPORT_PRO_ICACHE_UNLOCK_ENA_V  0x1
#define DPORT_PRO_ICACHE_UNLOCK_ENA_S  25
/* DPORT_PRO_ICACHE_SLAVE_REQ : RO ;bitpos:[24] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_SLAVE_REQ  (BIT(24))
#define DPORT_PRO_ICACHE_SLAVE_REQ_M  (BIT(24))
#define DPORT_PRO_ICACHE_SLAVE_REQ_V  0x1
#define DPORT_PRO_ICACHE_SLAVE_REQ_S  24
/* DPORT_PRO_ICACHE_AHB_SPI_REQ : RO ;bitpos:[23] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_AHB_SPI_REQ  (BIT(23))
#define DPORT_PRO_ICACHE_AHB_SPI_REQ_M  (BIT(23))
#define DPORT_PRO_ICACHE_AHB_SPI_REQ_V  0x1
#define DPORT_PRO_ICACHE_AHB_SPI_REQ_S  23
/* DPORT_PRO_ICACHESETSIZEMODE : R/W ;bitpos:[22:21] ;default: 2'b0 ; */
/*description: */
#define DPORT_PRO_ICACHESETSIZEMODE  0x00000003
#define DPORT_PRO_ICACHESETSIZEMODE_M  ((DPORT_PRO_ICACHESETSIZEMODE_V)<<(DPORT_PRO_ICACHESETSIZEMODE_S))
#define DPORT_PRO_ICACHESETSIZEMODE_V  0x3
#define DPORT_PRO_ICACHESETSIZEMODE_S  21
/* DPORT_PRO_ICACHEBLOCKSIZEMODE : R/W ;bitpos:[20:19] ;default: 2'b0 ; */
/*description: */
#define DPORT_PRO_ICACHEBLOCKSIZEMODE  0x00000003
#define DPORT_PRO_ICACHEBLOCKSIZEMODE_M  ((DPORT_PRO_ICACHEBLOCKSIZEMODE_V)<<(DPORT_PRO_ICACHEBLOCKSIZEMODE_S))
#define DPORT_PRO_ICACHEBLOCKSIZEMODE_V  0x3
#define DPORT_PRO_ICACHEBLOCKSIZEMODE_S  19
/* DPORT_PRO_ICACHE_PRELOADDONE : RO ;bitpos:[18] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_PRELOADDONE  (BIT(18))
#define DPORT_PRO_ICACHE_PRELOADDONE_M  (BIT(18))
#define DPORT_PRO_ICACHE_PRELOADDONE_V  0x1
#define DPORT_PRO_ICACHE_PRELOADDONE_S  18
/* DPORT_PRO_ICACHE_PRELOADENA : R/W ;bitpos:[17] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_PRELOADENA  (BIT(17))
#define DPORT_PRO_ICACHE_PRELOADENA_M  (BIT(17))
#define DPORT_PRO_ICACHE_PRELOADENA_V  0x1
#define DPORT_PRO_ICACHE_PRELOADENA_S  17
/* DPORT_PRO_ICACHE_AUTOLOADDONE : RO ;bitpos:[16] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_AUTOLOADDONE  (BIT(16))
#define DPORT_PRO_ICACHE_AUTOLOADDONE_M  (BIT(16))
#define DPORT_PRO_ICACHE_AUTOLOADDONE_V  0x1
#define DPORT_PRO_ICACHE_AUTOLOADDONE_S  16
/* DPORT_PRO_ICACHE_AUTOLOADENA : R/W ;bitpos:[15] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_AUTOLOADENA  (BIT(15))
#define DPORT_PRO_ICACHE_AUTOLOADENA_M  (BIT(15))
#define DPORT_PRO_ICACHE_AUTOLOADENA_V  0x1
#define DPORT_PRO_ICACHE_AUTOLOADENA_S  15
/* DPORT_PRO_ICACHE_DRAM_HL : R/W ;bitpos:[14] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_DRAM_HL  (BIT(14))
#define DPORT_PRO_ICACHE_DRAM_HL_M  (BIT(14))
#define DPORT_PRO_ICACHE_DRAM_HL_V  0x1
#define DPORT_PRO_ICACHE_DRAM_HL_S  14
/* DPORT_PRO_ICACHE_DRAM_SPLIT : R/W ;bitpos:[13] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_DRAM_SPLIT  (BIT(13))
#define DPORT_PRO_ICACHE_DRAM_SPLIT_M  (BIT(13))
#define DPORT_PRO_ICACHE_DRAM_SPLIT_V  0x1
#define DPORT_PRO_ICACHE_DRAM_SPLIT_S  13
/* DPORT_PRO_ICACHE_LOCK1_EN : R/W ;bitpos:[12] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_LOCK1_EN  (BIT(12))
#define DPORT_PRO_ICACHE_LOCK1_EN_M  (BIT(12))
#define DPORT_PRO_ICACHE_LOCK1_EN_V  0x1
#define DPORT_PRO_ICACHE_LOCK1_EN_S  12
/* DPORT_PRO_ICACHE_LOCK0_EN : R/W ;bitpos:[11] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_LOCK0_EN  (BIT(11))
#define DPORT_PRO_ICACHE_LOCK0_EN_M  (BIT(11))
#define DPORT_PRO_ICACHE_LOCK0_EN_V  0x1
#define DPORT_PRO_ICACHE_LOCK0_EN_S  11
/* DPORT_PRO_ICACHE_FLUSH_DONE : RO ;bitpos:[10] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_FLUSH_DONE  (BIT(10))
#define DPORT_PRO_ICACHE_FLUSH_DONE_M  (BIT(10))
#define DPORT_PRO_ICACHE_FLUSH_DONE_V  0x1
#define DPORT_PRO_ICACHE_FLUSH_DONE_S  10
/* DPORT_PRO_ICACHE_FLUSH_ENA : R/W ;bitpos:[9] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_FLUSH_ENA  (BIT(9))
#define DPORT_PRO_ICACHE_FLUSH_ENA_M  (BIT(9))
#define DPORT_PRO_ICACHE_FLUSH_ENA_V  0x1
#define DPORT_PRO_ICACHE_FLUSH_ENA_S  9
/* DPORT_PRO_ICACHE_CLEAN_DONE : RO ;bitpos:[8] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_CLEAN_DONE  (BIT(8))
#define DPORT_PRO_ICACHE_CLEAN_DONE_M  (BIT(8))
#define DPORT_PRO_ICACHE_CLEAN_DONE_V  0x1
#define DPORT_PRO_ICACHE_CLEAN_DONE_S  8
/* DPORT_PRO_ICACHE_CLEAN_ENA : R/W ;bitpos:[7] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_CLEAN_ENA  (BIT(7))
#define DPORT_PRO_ICACHE_CLEAN_ENA_M  (BIT(7))
#define DPORT_PRO_ICACHE_CLEAN_ENA_V  0x1
#define DPORT_PRO_ICACHE_CLEAN_ENA_S  7
/* DPORT_PRO_ICACHE_INVALIDATE_DONE : RO ;bitpos:[6] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_INVALIDATE_DONE  (BIT(6))
#define DPORT_PRO_ICACHE_INVALIDATE_DONE_M  (BIT(6))
#define DPORT_PRO_ICACHE_INVALIDATE_DONE_V  0x1
#define DPORT_PRO_ICACHE_INVALIDATE_DONE_S  6
/* DPORT_PRO_ICACHE_INVALIDATE_ENA : R/W ;bitpos:[5] ;default: 1'b1 ; */
/*description: */
#define DPORT_PRO_ICACHE_INVALIDATE_ENA  (BIT(5))
#define DPORT_PRO_ICACHE_INVALIDATE_ENA_M  (BIT(5))
#define DPORT_PRO_ICACHE_INVALIDATE_ENA_V  0x1
#define DPORT_PRO_ICACHE_INVALIDATE_ENA_S  5
/* DPORT_PRO_ICACHE_MODE : R/W ;bitpos:[4:2] ;default: 3'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_MODE  0x00000007
#define DPORT_PRO_ICACHE_MODE_M  ((DPORT_PRO_ICACHE_MODE_V)<<(DPORT_PRO_ICACHE_MODE_S))
#define DPORT_PRO_ICACHE_MODE_V  0x7
#define DPORT_PRO_ICACHE_MODE_S  2
/* DPORT_PRO_ICACHE_ENABLE : R/W ;bitpos:[1] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_ENABLE  (BIT(1))
#define DPORT_PRO_ICACHE_ENABLE_M  (BIT(1))
#define DPORT_PRO_ICACHE_ENABLE_V  0x1
#define DPORT_PRO_ICACHE_ENABLE_S  1
/* DPORT_PRO_ICACHE_CLK_ON : R/W ;bitpos:[0] ;default: 1'b1 ; */
/*description: */
#define DPORT_PRO_ICACHE_CLK_ON  (BIT(0))
#define DPORT_PRO_ICACHE_CLK_ON_M  (BIT(0))
#define DPORT_PRO_ICACHE_CLK_ON_V  0x1
#define DPORT_PRO_ICACHE_CLK_ON_S  0

#define DPORT_PRO_ICACHE_CTRL1_REG          (DR_REG_DPORT_BASE + 0x2A8)
/* DPORT_PRO_ICMMU_PD : R/W ;bitpos:[12] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_ICMMU_PD  (BIT(12))
#define DPORT_PRO_ICMMU_PD_M  (BIT(12))
#define DPORT_PRO_ICMMU_PD_V  0x1
#define DPORT_PRO_ICMMU_PD_S  12
/* DPORT_PRO_ICMMU_FORCE_ON : R/W ;bitpos:[11] ;default: 1'b1 ; */
/*description: */
#define DPORT_PRO_ICMMU_FORCE_ON  (BIT(11))
#define DPORT_PRO_ICMMU_FORCE_ON_M  (BIT(11))
#define DPORT_PRO_ICMMU_FORCE_ON_V  0x1
#define DPORT_PRO_ICMMU_FORCE_ON_S  11
/* DPORT_PRO_ICMMU_FLASH_PAGE_MODE : R/W ;bitpos:[10:9] ;default: 2'b0 ; */
/*description: */
#define DPORT_PRO_ICMMU_FLASH_PAGE_MODE  0x00000003
#define DPORT_PRO_ICMMU_FLASH_PAGE_MODE_M  ((DPORT_PRO_ICMMU_FLASH_PAGE_MODE_V)<<(DPORT_PRO_ICMMU_FLASH_PAGE_MODE_S))
#define DPORT_PRO_ICMMU_FLASH_PAGE_MODE_V  0x3
#define DPORT_PRO_ICMMU_FLASH_PAGE_MODE_S  9
/* DPORT_PRO_ICACHE_MASK_OPSDRAM : R/W ;bitpos:[5] ;default: 1'b1 ; */
/*description: */
#define DPORT_PRO_ICACHE_MASK_OPSDRAM  (BIT(5))
#define DPORT_PRO_ICACHE_MASK_OPSDRAM_M  (BIT(5))
#define DPORT_PRO_ICACHE_MASK_OPSDRAM_V  0x1
#define DPORT_PRO_ICACHE_MASK_OPSDRAM_S  5
/* DPORT_PRO_ICACHE_MASK_DROM0 : R/W ;bitpos:[4] ;default: 1'b1 ; */
/*description: */
#define DPORT_PRO_ICACHE_MASK_DROM0  (BIT(4))
#define DPORT_PRO_ICACHE_MASK_DROM0_M  (BIT(4))
#define DPORT_PRO_ICACHE_MASK_DROM0_V  0x1
#define DPORT_PRO_ICACHE_MASK_DROM0_S  4
/* DPORT_PRO_ICACHE_MASK_IROM0 : R/W ;bitpos:[2] ;default: 1'b1 ; */
/*description: */
#define DPORT_PRO_ICACHE_MASK_IROM0  (BIT(2))
#define DPORT_PRO_ICACHE_MASK_IROM0_M  (BIT(2))
#define DPORT_PRO_ICACHE_MASK_IROM0_V  0x1
#define DPORT_PRO_ICACHE_MASK_IROM0_S  2
/* DPORT_PRO_ICACHE_MASK_IRAM1 : R/W ;bitpos:[1] ;default: 1'b1 ; */
/*description: */
#define DPORT_PRO_ICACHE_MASK_IRAM1  (BIT(1))
#define DPORT_PRO_ICACHE_MASK_IRAM1_M  (BIT(1))
#define DPORT_PRO_ICACHE_MASK_IRAM1_V  0x1
#define DPORT_PRO_ICACHE_MASK_IRAM1_S  1
/* DPORT_PRO_ICACHE_MASK_IRAM0 : R/W ;bitpos:[0] ;default: 1'b1 ; */
/*description: */
#define DPORT_PRO_ICACHE_MASK_IRAM0  (BIT(0))
#define DPORT_PRO_ICACHE_MASK_IRAM0_M  (BIT(0))
#define DPORT_PRO_ICACHE_MASK_IRAM0_V  0x1
#define DPORT_PRO_ICACHE_MASK_IRAM0_S  0

#define DPORT_PRO_ICACHE_LOCK0_ADDR_REG          (DR_REG_DPORT_BASE + 0x2AC)
/* DPORT_PRO_ICACHE_LOCK0_ADDR : R/W ;bitpos:[31:0] ;default: 10'h0 ; */
/*description: */
#define DPORT_PRO_ICACHE_LOCK0_ADDR  0xFFFFFFFF
#define DPORT_PRO_ICACHE_LOCK0_ADDR_M  ((DPORT_PRO_ICACHE_LOCK0_ADDR_V)<<(DPORT_PRO_ICACHE_LOCK0_ADDR_S))
#define DPORT_PRO_ICACHE_LOCK0_ADDR_V  0xFFFFFFFF
#define DPORT_PRO_ICACHE_LOCK0_ADDR_S  0

#define DPORT_PRO_ICACHE_LOCK0_SIZE_REG          (DR_REG_DPORT_BASE + 0x2B0)
/* DPORT_PRO_ICACHE_LOCK0_SIZE : R/W ;bitpos:[15:0] ;default: 16'h0 ; */
/*description: */
#define DPORT_PRO_ICACHE_LOCK0_SIZE  0x0000FFFF
#define DPORT_PRO_ICACHE_LOCK0_SIZE_M  ((DPORT_PRO_ICACHE_LOCK0_SIZE_V)<<(DPORT_PRO_ICACHE_LOCK0_SIZE_S))
#define DPORT_PRO_ICACHE_LOCK0_SIZE_V  0xFFFF
#define DPORT_PRO_ICACHE_LOCK0_SIZE_S  0

#define DPORT_PRO_ICACHE_LOCK1_ADDR_REG          (DR_REG_DPORT_BASE + 0x2B4)
/* DPORT_PRO_ICACHE_LOCK1_ADDR : R/W ;bitpos:[31:0] ;default: 10'h0 ; */
/*description: */
#define DPORT_PRO_ICACHE_LOCK1_ADDR  0xFFFFFFFF
#define DPORT_PRO_ICACHE_LOCK1_ADDR_M  ((DPORT_PRO_ICACHE_LOCK1_ADDR_V)<<(DPORT_PRO_ICACHE_LOCK1_ADDR_S))
#define DPORT_PRO_ICACHE_LOCK1_ADDR_V  0xFFFFFFFF
#define DPORT_PRO_ICACHE_LOCK1_ADDR_S  0

#define DPORT_PRO_ICACHE_LOCK1_SIZE_REG          (DR_REG_DPORT_BASE + 0x2B8)
/* DPORT_PRO_ICACHE_LOCK1_SIZE : R/W ;bitpos:[15:0] ;default: 16'h0 ; */
/*description: */
#define DPORT_PRO_ICACHE_LOCK1_SIZE  0x0000FFFF
#define DPORT_PRO_ICACHE_LOCK1_SIZE_M  ((DPORT_PRO_ICACHE_LOCK1_SIZE_V)<<(DPORT_PRO_ICACHE_LOCK1_SIZE_S))
#define DPORT_PRO_ICACHE_LOCK1_SIZE_V  0xFFFF
#define DPORT_PRO_ICACHE_LOCK1_SIZE_S  0

#define DPORT_PRO_ICMMU_EXC_RECORD0_REG          (DR_REG_DPORT_BASE + 0x2BC)
/* DPORT_PRO_ICMMU_EXC_RECORD0 : RO ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_PRO_ICMMU_EXC_RECORD0  0xFFFFFFFF
#define DPORT_PRO_ICMMU_EXC_RECORD0_M  ((DPORT_PRO_ICMMU_EXC_RECORD0_V)<<(DPORT_PRO_ICMMU_EXC_RECORD0_S))
#define DPORT_PRO_ICMMU_EXC_RECORD0_V  0xFFFFFFFF
#define DPORT_PRO_ICMMU_EXC_RECORD0_S  0

#define DPORT_PRO_ICMMU_EXC_RECORD1_REG          (DR_REG_DPORT_BASE + 0x2C0)
/* DPORT_PRO_ICMMU_EXC_RECORD1 : RO ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_PRO_ICMMU_EXC_RECORD1  0xFFFFFFFF
#define DPORT_PRO_ICMMU_EXC_RECORD1_M  ((DPORT_PRO_ICMMU_EXC_RECORD1_V)<<(DPORT_PRO_ICMMU_EXC_RECORD1_S))
#define DPORT_PRO_ICMMU_EXC_RECORD1_V  0xFFFFFFFF
#define DPORT_PRO_ICMMU_EXC_RECORD1_S  0

#define DPORT_PRO_ICACHE_MEM_SYNC0_REG          (DR_REG_DPORT_BASE + 0x2C4)
/* DPORT_PRO_ICACHE_MEMSYNCADDR : R/W ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_MEMSYNCADDR  0xFFFFFFFF
#define DPORT_PRO_ICACHE_MEMSYNCADDR_M  ((DPORT_PRO_ICACHE_MEMSYNCADDR_V)<<(DPORT_PRO_ICACHE_MEMSYNCADDR_S))
#define DPORT_PRO_ICACHE_MEMSYNCADDR_V  0xFFFFFFFF
#define DPORT_PRO_ICACHE_MEMSYNCADDR_S  0

#define DPORT_PRO_ICACHE_MEM_SYNC1_REG          (DR_REG_DPORT_BASE + 0x2C8)
/* DPORT_PRO_ICACHE_MEMSYNCSIZE : R/W ;bitpos:[22:0] ;default: 23'h400000 ; */
/*description: */
#define DPORT_PRO_ICACHE_MEMSYNCSIZE  0x007FFFFF
#define DPORT_PRO_ICACHE_MEMSYNCSIZE_M  ((DPORT_PRO_ICACHE_MEMSYNCSIZE_V)<<(DPORT_PRO_ICACHE_MEMSYNCSIZE_S))
#define DPORT_PRO_ICACHE_MEMSYNCSIZE_V  0x7FFFFF
#define DPORT_PRO_ICACHE_MEMSYNCSIZE_S  0

#define DPORT_PRO_ICACHE_PRELOADADDR_REG          (DR_REG_DPORT_BASE + 0x2CC)
/* DPORT_PRO_ICACHE_PRELOADADDR : R/W ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_PRELOADADDR  0xFFFFFFFF
#define DPORT_PRO_ICACHE_PRELOADADDR_M  ((DPORT_PRO_ICACHE_PRELOADADDR_V)<<(DPORT_PRO_ICACHE_PRELOADADDR_S))
#define DPORT_PRO_ICACHE_PRELOADADDR_V  0xFFFFFFFF
#define DPORT_PRO_ICACHE_PRELOADADDR_S  0

#define DPORT_PRO_ICACHE_PRELOADSIZE_REG          (DR_REG_DPORT_BASE + 0x2D0)
/* DPORT_PRO_ICACHE_PRELOADSIZE : R/W ;bitpos:[15:0] ;default: 16'h8000 ; */
/*description: */
#define DPORT_PRO_ICACHE_PRELOADSIZE  0x0000FFFF
#define DPORT_PRO_ICACHE_PRELOADSIZE_M  ((DPORT_PRO_ICACHE_PRELOADSIZE_V)<<(DPORT_PRO_ICACHE_PRELOADSIZE_S))
#define DPORT_PRO_ICACHE_PRELOADSIZE_V  0xFFFF
#define DPORT_PRO_ICACHE_PRELOADSIZE_S  0

#define DPORT_PRO_ICACHE_AUTOLOAD_CFG_REG          (DR_REG_DPORT_BASE + 0x2D4)
/* DPORT_PRO_ICACHE_AUTOLOAD_RQST : R/W ;bitpos:[5:4] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_AUTOLOAD_RQST  0x00000003
#define DPORT_PRO_ICACHE_AUTOLOAD_RQST_M  ((DPORT_PRO_ICACHE_AUTOLOAD_RQST_V)<<(DPORT_PRO_ICACHE_AUTOLOAD_RQST_S))
#define DPORT_PRO_ICACHE_AUTOLOAD_RQST_V  0x3
#define DPORT_PRO_ICACHE_AUTOLOAD_RQST_S  4
/* DPORT_PRO_ICACHE_AUTOLOAD_ORDER : R/W ;bitpos:[3] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_AUTOLOAD_ORDER  (BIT(3))
#define DPORT_PRO_ICACHE_AUTOLOAD_ORDER_M  (BIT(3))
#define DPORT_PRO_ICACHE_AUTOLOAD_ORDER_V  0x1
#define DPORT_PRO_ICACHE_AUTOLOAD_ORDER_S  3
/* DPORT_PRO_ICACHE_AUTOLOAD_STEP : R/W ;bitpos:[2:1] ;default: 2'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_AUTOLOAD_STEP  0x00000003
#define DPORT_PRO_ICACHE_AUTOLOAD_STEP_M  ((DPORT_PRO_ICACHE_AUTOLOAD_STEP_V)<<(DPORT_PRO_ICACHE_AUTOLOAD_STEP_S))
#define DPORT_PRO_ICACHE_AUTOLOAD_STEP_V  0x3
#define DPORT_PRO_ICACHE_AUTOLOAD_STEP_S  1
/* DPORT_PRO_ICACHE_AUTOLOAD_MODE : R/W ;bitpos:[0] ;default: 1'd0 ; */
/*description: */
#define DPORT_PRO_ICACHE_AUTOLOAD_MODE  (BIT(0))
#define DPORT_PRO_ICACHE_AUTOLOAD_MODE_M  (BIT(0))
#define DPORT_PRO_ICACHE_AUTOLOAD_MODE_V  0x1
#define DPORT_PRO_ICACHE_AUTOLOAD_MODE_S  0

#define DPORT_PRO_ICACHE_AUTOLOAD_SECTION0_ADDR_REG          (DR_REG_DPORT_BASE + 0x2D8)
/* DPORT_PRO_ICACHE_AUTOLOAD_SCT0_ADDR : R/W ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_AUTOLOAD_SCT0_ADDR  0xFFFFFFFF
#define DPORT_PRO_ICACHE_AUTOLOAD_SCT0_ADDR_M  ((DPORT_PRO_ICACHE_AUTOLOAD_SCT0_ADDR_V)<<(DPORT_PRO_ICACHE_AUTOLOAD_SCT0_ADDR_S))
#define DPORT_PRO_ICACHE_AUTOLOAD_SCT0_ADDR_V  0xFFFFFFFF
#define DPORT_PRO_ICACHE_AUTOLOAD_SCT0_ADDR_S  0

#define DPORT_PRO_ICACHE_AUTOLOAD_SECTION0_SIZE_REG          (DR_REG_DPORT_BASE + 0x2DC)
/* DPORT_PRO_ICACHE_AUTOLOAD_SCT0_SIZE : R/W ;bitpos:[15:0] ;default: 16'h0 ; */
/*description: */
#define DPORT_PRO_ICACHE_AUTOLOAD_SCT0_SIZE  0x0000FFFF
#define DPORT_PRO_ICACHE_AUTOLOAD_SCT0_SIZE_M  ((DPORT_PRO_ICACHE_AUTOLOAD_SCT0_SIZE_V)<<(DPORT_PRO_ICACHE_AUTOLOAD_SCT0_SIZE_S))
#define DPORT_PRO_ICACHE_AUTOLOAD_SCT0_SIZE_V  0xFFFF
#define DPORT_PRO_ICACHE_AUTOLOAD_SCT0_SIZE_S  0

#define DPORT_PRO_ICACHE_AUTOLOAD_SECTION1_ADDR_REG          (DR_REG_DPORT_BASE + 0x2E0)
/* DPORT_PRO_ICACHE_AUTOLOAD_SCT1_ADDR : R/W ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_AUTOLOAD_SCT1_ADDR  0xFFFFFFFF
#define DPORT_PRO_ICACHE_AUTOLOAD_SCT1_ADDR_M  ((DPORT_PRO_ICACHE_AUTOLOAD_SCT1_ADDR_V)<<(DPORT_PRO_ICACHE_AUTOLOAD_SCT1_ADDR_S))
#define DPORT_PRO_ICACHE_AUTOLOAD_SCT1_ADDR_V  0xFFFFFFFF
#define DPORT_PRO_ICACHE_AUTOLOAD_SCT1_ADDR_S  0

#define DPORT_PRO_ICACHE_AUTOLOAD_SECTION1_SIZE_REG          (DR_REG_DPORT_BASE + 0x2E4)
/* DPORT_PRO_ICACHE_AUTOLOAD_SCT1_SIZE : R/W ;bitpos:[15:0] ;default: 16'h0 ; */
/*description: */
#define DPORT_PRO_ICACHE_AUTOLOAD_SCT1_SIZE  0x0000FFFF
#define DPORT_PRO_ICACHE_AUTOLOAD_SCT1_SIZE_M  ((DPORT_PRO_ICACHE_AUTOLOAD_SCT1_SIZE_V)<<(DPORT_PRO_ICACHE_AUTOLOAD_SCT1_SIZE_S))
#define DPORT_PRO_ICACHE_AUTOLOAD_SCT1_SIZE_V  0xFFFF
#define DPORT_PRO_ICACHE_AUTOLOAD_SCT1_SIZE_S  0

#define DPORT_PRO_ICACHE_FLASH_RD_MISS_CNT_REG          (DR_REG_DPORT_BASE + 0x2E8)
/* DPORT_PRO_ICACHE_CPUFLASH_RD_MISSCNT : RO ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_CPUFLASH_RD_MISSCNT  0xFFFFFFFF
#define DPORT_PRO_ICACHE_CPUFLASH_RD_MISSCNT_M  ((DPORT_PRO_ICACHE_CPUFLASH_RD_MISSCNT_V)<<(DPORT_PRO_ICACHE_CPUFLASH_RD_MISSCNT_S))
#define DPORT_PRO_ICACHE_CPUFLASH_RD_MISSCNT_V  0xFFFFFFFF
#define DPORT_PRO_ICACHE_CPUFLASH_RD_MISSCNT_S  0

#define DPORT_PRO_ICACHE_FLASH_RD_CNT_REG          (DR_REG_DPORT_BASE + 0x2EC)
/* DPORT_PRO_ICACHE_CPUFLASH_RDCNT : RO ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_CPUFLASH_RDCNT  0xFFFFFFFF
#define DPORT_PRO_ICACHE_CPUFLASH_RDCNT_M  ((DPORT_PRO_ICACHE_CPUFLASH_RDCNT_V)<<(DPORT_PRO_ICACHE_CPUFLASH_RDCNT_S))
#define DPORT_PRO_ICACHE_CPUFLASH_RDCNT_V  0xFFFFFFFF
#define DPORT_PRO_ICACHE_CPUFLASH_RDCNT_S  0

#define DPORT_PRO_ICACHE_CPUQUITCHECK_CNT_REG          (DR_REG_DPORT_BASE + 0x2F0)
/* DPORT_PRO_ICACHE_CPUQUITCHECK_CNT : RO ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_CPUQUITCHECK_CNT  0xFFFFFFFF
#define DPORT_PRO_ICACHE_CPUQUITCHECK_CNT_M  ((DPORT_PRO_ICACHE_CPUQUITCHECK_CNT_V)<<(DPORT_PRO_ICACHE_CPUQUITCHECK_CNT_S))
#define DPORT_PRO_ICACHE_CPUQUITCHECK_CNT_V  0xFFFFFFFF
#define DPORT_PRO_ICACHE_CPUQUITCHECK_CNT_S  0

#define DPORT_PRO_ICACHE_ACCESS_CNT_CLR_REG          (DR_REG_DPORT_BASE + 0x2F4)
/* DPORT_PRO_ICACHE_CNT_OVERFLOW : RO ;bitpos:[1] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_CNT_OVERFLOW  (BIT(1))
#define DPORT_PRO_ICACHE_CNT_OVERFLOW_M  (BIT(1))
#define DPORT_PRO_ICACHE_CNT_OVERFLOW_V  0x1
#define DPORT_PRO_ICACHE_CNT_OVERFLOW_S  1
/* DPORT_PRO_ICACHE_ACCESS_CNT_CLR : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_ACCESS_CNT_CLR  (BIT(0))
#define DPORT_PRO_ICACHE_ACCESS_CNT_CLR_M  (BIT(0))
#define DPORT_PRO_ICACHE_ACCESS_CNT_CLR_V  0x1
#define DPORT_PRO_ICACHE_ACCESS_CNT_CLR_S  0

#define DPORT_PRO_ICACHE_IA_INT_EN_REG          (DR_REG_DPORT_BASE + 0x2F8)
/* DPORT_PRO_ICACHE_INT_CLR : R/W ;bitpos:[15] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_INT_CLR  (BIT(15))
#define DPORT_PRO_ICACHE_INT_CLR_M  (BIT(15))
#define DPORT_PRO_ICACHE_INT_CLR_V  0x1
#define DPORT_PRO_ICACHE_INT_CLR_S  15
/* DPORT_PRO_ICACHE_IA_INT_EN : R/W ;bitpos:[14:1] ;default: 14'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_IA_INT_EN  0x00003FFF
#define DPORT_PRO_ICACHE_IA_INT_EN_M  ((DPORT_PRO_ICACHE_IA_INT_EN_V)<<(DPORT_PRO_ICACHE_IA_INT_EN_S))
#define DPORT_PRO_ICACHE_IA_INT_EN_V  0x3FFF
#define DPORT_PRO_ICACHE_IA_INT_EN_S  1
/* DPORT_PRO_ICACHE_DBG_EN : R/W ;bitpos:[0] ;default: 1'b1 ; */
/*description: */
#define DPORT_PRO_ICACHE_DBG_EN  (BIT(0))
#define DPORT_PRO_ICACHE_DBG_EN_M  (BIT(0))
#define DPORT_PRO_ICACHE_DBG_EN_V  0x1
#define DPORT_PRO_ICACHE_DBG_EN_S  0

#define DPORT_PRO_ICACHE_DBUG1_REG          (DR_REG_DPORT_BASE + 0x2FC)
/* DPORT_PRO_ICACHE_SLAVE_WDATA_V : RO ;bitpos:[22] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_SLAVE_WDATA_V  (BIT(22))
#define DPORT_PRO_ICACHE_SLAVE_WDATA_V_M  (BIT(22))
#define DPORT_PRO_ICACHE_SLAVE_WDATA_V_V  0x1
#define DPORT_PRO_ICACHE_SLAVE_WDATA_V_S  22
/* DPORT_PRO_ICACHE_SLAVE_WR : RO ;bitpos:[21] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_SLAVE_WR  (BIT(21))
#define DPORT_PRO_ICACHE_SLAVE_WR_M  (BIT(21))
#define DPORT_PRO_ICACHE_SLAVE_WR_V  0x1
#define DPORT_PRO_ICACHE_SLAVE_WR_S  21
/* DPORT_PRO_ICACHE_SYNCSIZECHECKFAIL : RO ;bitpos:[7] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_SYNCSIZECHECKFAIL  (BIT(7))
#define DPORT_PRO_ICACHE_SYNCSIZECHECKFAIL_M  (BIT(7))
#define DPORT_PRO_ICACHE_SYNCSIZECHECKFAIL_V  0x1
#define DPORT_PRO_ICACHE_SYNCSIZECHECKFAIL_S  7
/* DPORT_PRO_ICACHE_IA : RO ;bitpos:[6:1] ;default: 6'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_IA  0x0000003F
#define DPORT_PRO_ICACHE_IA_M  ((DPORT_PRO_ICACHE_IA_V)<<(DPORT_PRO_ICACHE_IA_S))
#define DPORT_PRO_ICACHE_IA_V  0x3F
#define DPORT_PRO_ICACHE_IA_S  1
/* DPORT_PRO_ICACHE_MMU_IA : RO ;bitpos:[0] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_MMU_IA  (BIT(0))
#define DPORT_PRO_ICACHE_MMU_IA_M  (BIT(0))
#define DPORT_PRO_ICACHE_MMU_IA_V  0x1
#define DPORT_PRO_ICACHE_MMU_IA_S  0

#define DPORT_PRO_ICACHE_DBUG2_REG          (DR_REG_DPORT_BASE + 0x300)
/* DPORT_PRO_ICACHE_STATE : RO ;bitpos:[11:0] ;default: 12'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_STATE  0x00000FFF
#define DPORT_PRO_ICACHE_STATE_M  ((DPORT_PRO_ICACHE_STATE_V)<<(DPORT_PRO_ICACHE_STATE_S))
#define DPORT_PRO_ICACHE_STATE_V  0xFFF
#define DPORT_PRO_ICACHE_STATE_S  0

#define DPORT_PRO_ICACHE_DBUG3_REG          (DR_REG_DPORT_BASE + 0x304)
/* DPORT_PRO_CPU_DISABLED_ICACHE_IA : RO ;bitpos:[14:9] ;default: 6'b0 ; */
/*description: */
#define DPORT_PRO_CPU_DISABLED_ICACHE_IA  0x0000003F
#define DPORT_PRO_CPU_DISABLED_ICACHE_IA_M  ((DPORT_PRO_CPU_DISABLED_ICACHE_IA_V)<<(DPORT_PRO_CPU_DISABLED_ICACHE_IA_S))
#define DPORT_PRO_CPU_DISABLED_ICACHE_IA_V  0x3F
#define DPORT_PRO_CPU_DISABLED_ICACHE_IA_S  9

#define DPORT_PROBLOCKCNT_REG          (DR_REG_DPORT_BASE + 0x308)
/* DPORT_PRO_BLOCKCNT : RO ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_PRO_BLOCKCNT  0xFFFFFFFF
#define DPORT_PRO_BLOCKCNT_M  ((DPORT_PRO_BLOCKCNT_V)<<(DPORT_PRO_BLOCKCNT_S))
#define DPORT_PRO_BLOCKCNT_V  0xFFFFFFFF
#define DPORT_PRO_BLOCKCNT_S  0

#define DPORT_APPBLOCKCNT_REG          (DR_REG_DPORT_BASE + 0x30C)
/* DPORT_APP_BLOCKCNT : RO ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_APP_BLOCKCNT  0xFFFFFFFF
#define DPORT_APP_BLOCKCNT_M  ((DPORT_APP_BLOCKCNT_V)<<(DPORT_APP_BLOCKCNT_S))
#define DPORT_APP_BLOCKCNT_V  0xFFFFFFFF
#define DPORT_APP_BLOCKCNT_S  0

#define DPORT_PROICACHEBLOCKCNT_REG          (DR_REG_DPORT_BASE + 0x310)
/* DPORT_PRO_ICACHE_BLOCKCNT : RO ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_PRO_ICACHE_BLOCKCNT  0xFFFFFFFF
#define DPORT_PRO_ICACHE_BLOCKCNT_M  ((DPORT_PRO_ICACHE_BLOCKCNT_V)<<(DPORT_PRO_ICACHE_BLOCKCNT_S))
#define DPORT_PRO_ICACHE_BLOCKCNT_V  0xFFFFFFFF
#define DPORT_PRO_ICACHE_BLOCKCNT_S  0

#define DPORT_DMABLOCKCNT_REG          (DR_REG_DPORT_BASE + 0x314)
/* DPORT_DMA_BLOCKCNT : RO ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_DMA_BLOCKCNT  0xFFFFFFFF
#define DPORT_DMA_BLOCKCNT_M  ((DPORT_DMA_BLOCKCNT_V)<<(DPORT_DMA_BLOCKCNT_S))
#define DPORT_DMA_BLOCKCNT_V  0xFFFFFFFF
#define DPORT_DMA_BLOCKCNT_S  0

#define DPORT_BUSBLOCKCNTCLR_REG          (DR_REG_DPORT_BASE + 0x318)
/* DPORT_BUSBLOCKCNTCLR : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: */
#define DPORT_BUSBLOCKCNTCLR  (BIT(0))
#define DPORT_BUSBLOCKCNTCLR_M  (BIT(0))
#define DPORT_BUSBLOCKCNTCLR_V  0x1
#define DPORT_BUSBLOCKCNTCLR_S  0

#define DPORT_RTC_FASTMEM_CONFIG_REG          (DR_REG_DPORT_BASE + 0x31C)
/* DPORT_RTC_MEM_CRC_FINISH : RO ;bitpos:[31] ;default: 1'b0 ; */
/*description: */
#define DPORT_RTC_MEM_CRC_FINISH  (BIT(31))
#define DPORT_RTC_MEM_CRC_FINISH_M  (BIT(31))
#define DPORT_RTC_MEM_CRC_FINISH_V  0x1
#define DPORT_RTC_MEM_CRC_FINISH_S  31
/* DPORT_RTC_MEM_CRC_LEN : R/W ;bitpos:[30:20] ;default: 11'h7ff ; */
/*description: */
#define DPORT_RTC_MEM_CRC_LEN  0x000007FF
#define DPORT_RTC_MEM_CRC_LEN_M  ((DPORT_RTC_MEM_CRC_LEN_V)<<(DPORT_RTC_MEM_CRC_LEN_S))
#define DPORT_RTC_MEM_CRC_LEN_V  0x7FF
#define DPORT_RTC_MEM_CRC_LEN_S  20
/* DPORT_RTC_MEM_CRC_ADDR : R/W ;bitpos:[19:9] ;default: 11'h0 ; */
/*description: */
#define DPORT_RTC_MEM_CRC_ADDR  0x000007FF
#define DPORT_RTC_MEM_CRC_ADDR_M  ((DPORT_RTC_MEM_CRC_ADDR_V)<<(DPORT_RTC_MEM_CRC_ADDR_S))
#define DPORT_RTC_MEM_CRC_ADDR_V  0x7FF
#define DPORT_RTC_MEM_CRC_ADDR_S  9
/* DPORT_RTC_MEM_CRC_START : R/W ;bitpos:[8] ;default: 1'b0 ; */
/*description: */
#define DPORT_RTC_MEM_CRC_START  (BIT(8))
#define DPORT_RTC_MEM_CRC_START_M  (BIT(8))
#define DPORT_RTC_MEM_CRC_START_V  0x1
#define DPORT_RTC_MEM_CRC_START_S  8
/* DPORT_PID_CONFIG : R/W ;bitpos:[7:0] ;default: 8'd1 ; */
/*description: */
#define DPORT_PID_CONFIG  0x000000FF
#define DPORT_PID_CONFIG_M  ((DPORT_PID_CONFIG_V)<<(DPORT_PID_CONFIG_S))
#define DPORT_PID_CONFIG_V  0xFF
#define DPORT_PID_CONFIG_S  0

#define DPORT_RTC_FASTMEM_CRC_REG          (DR_REG_DPORT_BASE + 0x320)
/* DPORT_RTC_MEM_CRC_RES : RO ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_RTC_MEM_CRC_RES  0xFFFFFFFF
#define DPORT_RTC_MEM_CRC_RES_M  ((DPORT_RTC_MEM_CRC_RES_V)<<(DPORT_RTC_MEM_CRC_RES_S))
#define DPORT_RTC_MEM_CRC_RES_V  0xFFFFFFFF
#define DPORT_RTC_MEM_CRC_RES_S  0

#define DPORT_CACHE_WRAP_AROUND_CTRL_REG          (DR_REG_DPORT_BASE + 0x324)
/* DPORT_SRAM_WR_WRAP_AROUND : R/W ;bitpos:[2] ;default: 1'b0 ; */
/*description: */
#define DPORT_SRAM_WR_WRAP_AROUND  (BIT(2))
#define DPORT_SRAM_WR_WRAP_AROUND_M  (BIT(2))
#define DPORT_SRAM_WR_WRAP_AROUND_V  0x1
#define DPORT_SRAM_WR_WRAP_AROUND_S  2
/* DPORT_SRAM_RD_WRAP_AROUND : R/W ;bitpos:[1] ;default: 1'b0 ; */
/*description: */
#define DPORT_SRAM_RD_WRAP_AROUND  (BIT(1))
#define DPORT_SRAM_RD_WRAP_AROUND_M  (BIT(1))
#define DPORT_SRAM_RD_WRAP_AROUND_V  0x1
#define DPORT_SRAM_RD_WRAP_AROUND_S  1
/* DPORT_FLASH_WRAP_AROUND : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: */
#define DPORT_FLASH_WRAP_AROUND  (BIT(0))
#define DPORT_FLASH_WRAP_AROUND_M  (BIT(0))
#define DPORT_FLASH_WRAP_AROUND_V  0x1
#define DPORT_FLASH_WRAP_AROUND_S  0

#define DPORT_PRO_CACHE_AUTOLOAD_CFG_REG          (DR_REG_DPORT_BASE + 0x328)
/* DPORT_PRO_AUTOLOAD_RQST : R/W ;bitpos:[5:4] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_AUTOLOAD_RQST  0x00000003
#define DPORT_PRO_AUTOLOAD_RQST_M  ((DPORT_PRO_AUTOLOAD_RQST_V)<<(DPORT_PRO_AUTOLOAD_RQST_S))
#define DPORT_PRO_AUTOLOAD_RQST_V  0x3
#define DPORT_PRO_AUTOLOAD_RQST_S  4
/* DPORT_PRO_AUTOLOAD_ORDER : R/W ;bitpos:[3] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_AUTOLOAD_ORDER  (BIT(3))
#define DPORT_PRO_AUTOLOAD_ORDER_M  (BIT(3))
#define DPORT_PRO_AUTOLOAD_ORDER_V  0x1
#define DPORT_PRO_AUTOLOAD_ORDER_S  3
/* DPORT_PRO_AUTOLOAD_STEP : R/W ;bitpos:[2:1] ;default: 2'b0 ; */
/*description: */
#define DPORT_PRO_AUTOLOAD_STEP  0x00000003
#define DPORT_PRO_AUTOLOAD_STEP_M  ((DPORT_PRO_AUTOLOAD_STEP_V)<<(DPORT_PRO_AUTOLOAD_STEP_S))
#define DPORT_PRO_AUTOLOAD_STEP_V  0x3
#define DPORT_PRO_AUTOLOAD_STEP_S  1
/* DPORT_PRO_AUTOLOAD_MODE : R/W ;bitpos:[0] ;default: 1'd0 ; */
/*description: */
#define DPORT_PRO_AUTOLOAD_MODE  (BIT(0))
#define DPORT_PRO_AUTOLOAD_MODE_M  (BIT(0))
#define DPORT_PRO_AUTOLOAD_MODE_V  0x1
#define DPORT_PRO_AUTOLOAD_MODE_S  0

#define DPORT_PRO_CACHE_AUTOLOAD_SECTION0_ADDR_REG          (DR_REG_DPORT_BASE + 0x32C)
/* DPORT_PRO_AUTOLOAD_SCT0_ADDR : R/W ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_PRO_AUTOLOAD_SCT0_ADDR  0xFFFFFFFF
#define DPORT_PRO_AUTOLOAD_SCT0_ADDR_M  ((DPORT_PRO_AUTOLOAD_SCT0_ADDR_V)<<(DPORT_PRO_AUTOLOAD_SCT0_ADDR_S))
#define DPORT_PRO_AUTOLOAD_SCT0_ADDR_V  0xFFFFFFFF
#define DPORT_PRO_AUTOLOAD_SCT0_ADDR_S  0

#define DPORT_PRO_CACHE_AUTOLOAD_SECTION0_SIZE_REG          (DR_REG_DPORT_BASE + 0x330)
/* DPORT_PRO_AUTOLOAD_SCT0_SIZE : R/W ;bitpos:[15:0] ;default: 16'h0 ; */
/*description: */
#define DPORT_PRO_AUTOLOAD_SCT0_SIZE  0x0000FFFF
#define DPORT_PRO_AUTOLOAD_SCT0_SIZE_M  ((DPORT_PRO_AUTOLOAD_SCT0_SIZE_V)<<(DPORT_PRO_AUTOLOAD_SCT0_SIZE_S))
#define DPORT_PRO_AUTOLOAD_SCT0_SIZE_V  0xFFFF
#define DPORT_PRO_AUTOLOAD_SCT0_SIZE_S  0

#define DPORT_PRO_CACHE_AUTOLOAD_SECTION1_ADDR_REG          (DR_REG_DPORT_BASE + 0x334)
/* DPORT_PRO_AUTOLOAD_SCT1_ADDR : R/W ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: */
#define DPORT_PRO_AUTOLOAD_SCT1_ADDR  0xFFFFFFFF
#define DPORT_PRO_AUTOLOAD_SCT1_ADDR_M  ((DPORT_PRO_AUTOLOAD_SCT1_ADDR_V)<<(DPORT_PRO_AUTOLOAD_SCT1_ADDR_S))
#define DPORT_PRO_AUTOLOAD_SCT1_ADDR_V  0xFFFFFFFF
#define DPORT_PRO_AUTOLOAD_SCT1_ADDR_S  0

#define DPORT_PRO_CACHE_AUTOLOAD_SECTION1_SIZE_REG          (DR_REG_DPORT_BASE + 0x338)
/* DPORT_PRO_AUTOLOAD_SCT1_SIZE : R/W ;bitpos:[15:0] ;default: 16'h0 ; */
/*description: */
#define DPORT_PRO_AUTOLOAD_SCT1_SIZE  0x0000FFFF
#define DPORT_PRO_AUTOLOAD_SCT1_SIZE_M  ((DPORT_PRO_AUTOLOAD_SCT1_SIZE_V)<<(DPORT_PRO_AUTOLOAD_SCT1_SIZE_S))
#define DPORT_PRO_AUTOLOAD_SCT1_SIZE_V  0xFFFF
#define DPORT_PRO_AUTOLOAD_SCT1_SIZE_S  0

#define DPORT_PRO_CACHE_DPORT_ACCESS_TAG_EN_REG          (DR_REG_DPORT_BASE + 0x33c)
/* DPORT_PRO_DPORTRDITAGEN : R/W ;bitpos:[3] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_DPORTRDITAGEN  (BIT(3))
#define DPORT_PRO_DPORTRDITAGEN_M  (BIT(3))
#define DPORT_PRO_DPORTRDITAGEN_V  0x1
#define DPORT_PRO_DPORTRDITAGEN_S  3
/* DPORT_PRO_DPORTWRITAGEN : R/W ;bitpos:[2] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_DPORTWRITAGEN  (BIT(2))
#define DPORT_PRO_DPORTWRITAGEN_M  (BIT(2))
#define DPORT_PRO_DPORTWRITAGEN_V  0x1
#define DPORT_PRO_DPORTWRITAGEN_S  2
/* DPORT_PRO_DPORTRDTAGEN : R/W ;bitpos:[1] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_DPORTRDTAGEN  (BIT(1))
#define DPORT_PRO_DPORTRDTAGEN_M  (BIT(1))
#define DPORT_PRO_DPORTRDTAGEN_V  0x1
#define DPORT_PRO_DPORTRDTAGEN_S  1
/* DPORT_PRO_DPORTWRTAGEN : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: */
#define DPORT_PRO_DPORTWRTAGEN  (BIT(0))
#define DPORT_PRO_DPORTWRTAGEN_M  (BIT(0))
#define DPORT_PRO_DPORTWRTAGEN_V  0x1
#define DPORT_PRO_DPORTWRTAGEN_S  0

#define DPORT_DATE_REG          (DR_REG_DPORT_BASE + 0xFFC)
/* DPORT_DATE : R/W ;bitpos:[27:0] ;default: 28'h1803290 ; */
/*description: */
#define DPORT_DATE  0x0FFFFFFF
#define DPORT_DATE_M  ((DPORT_DATE_V)<<(DPORT_DATE_S))
#define DPORT_DATE_V  0xFFFFFFF
#define DPORT_DATE_S  0
#define DPORT_DPORT_DATE_VERSION 0x1803290

/* Flash MMU table for PRO CPU */
#define DPORT_PRO_FLASH_MMU_TABLE ((volatile uint32_t*) 0x3FF10000)

#define DPORT_FLASH_MMU_TABLE_SIZE 0x100

#define DPORT_FLASH_MMU_TABLE_INVALID_VAL 0x100

#ifdef __cplusplus
}
#endif
#endif
/* Flash MMU table for PRO CPU */
#define DPORT_PRO_FLASH_MMU_TABLE ((volatile uint32_t*) 0x3FF05000)

#define DPORT_FLASH_MMU_TABLE_SIZE 0x100

#define DPORT_FLASH_MMU_TABLE_INVALID_VAL 0x100

#endif /*_SOC_DPORT_REG_H_ */


