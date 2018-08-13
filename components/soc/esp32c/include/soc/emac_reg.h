// Copyright 2017-2018 Espressif Systems (Shanghai) PTE LTD
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
#ifndef _SOC_EMAC_REG_H_
#define _SOC_EMAC_REG_H_


#ifdef __cplusplus
extern "C" {
#endif
#include "soc.h"
#define EMAC_EX_CLKOUT_CONF_REG          (DR_REG_EMAC_BASE + 0x0000)
/* EMAC_CLK_OUT_DLY_NUM : R/W ;bitpos:[9:8] ;default: 2'b0 ; */
/*description: */
#define EMAC_CLK_OUT_DLY_NUM  0x00000003
#define EMAC_CLK_OUT_DLY_NUM_M  ((EMAC_CLK_OUT_DLY_NUM_V)<<(EMAC_CLK_OUT_DLY_NUM_S))
#define EMAC_CLK_OUT_DLY_NUM_V  0x3
#define EMAC_CLK_OUT_DLY_NUM_S  8
/* EMAC_CLK_OUT_H_DIV_NUM : R/W ;bitpos:[7:4] ;default: 4'h2 ; */
/*description: */
#define EMAC_CLK_OUT_H_DIV_NUM  0x0000000F
#define EMAC_CLK_OUT_H_DIV_NUM_M  ((EMAC_CLK_OUT_H_DIV_NUM_V)<<(EMAC_CLK_OUT_H_DIV_NUM_S))
#define EMAC_CLK_OUT_H_DIV_NUM_V  0xF
#define EMAC_CLK_OUT_H_DIV_NUM_S  4
/* EMAC_CLK_OUT_DIV_NUM : R/W ;bitpos:[3:0] ;default: 4'h4 ; */
/*description: */
#define EMAC_CLK_OUT_DIV_NUM  0x0000000F
#define EMAC_CLK_OUT_DIV_NUM_M  ((EMAC_CLK_OUT_DIV_NUM_V)<<(EMAC_CLK_OUT_DIV_NUM_S))
#define EMAC_CLK_OUT_DIV_NUM_V  0xF
#define EMAC_CLK_OUT_DIV_NUM_S  0

#define EMAC_EX_OSCCLK_CONF_REG          (DR_REG_EMAC_BASE + 0x0004)
/* EMAC_OSC_CLK_SEL : R/W ;bitpos:[24] ;default: 1'd0 ; */
/*description: */
#define EMAC_OSC_CLK_SEL  (BIT(24))
#define EMAC_OSC_CLK_SEL_M  (BIT(24))
#define EMAC_OSC_CLK_SEL_V  0x1
#define EMAC_OSC_CLK_SEL_S  24
/* EMAC_OSC_H_DIV_NUM_100M : R/W ;bitpos:[23:18] ;default: 6'd0 ; */
/*description: */
#define EMAC_OSC_H_DIV_NUM_100M  0x0000003F
#define EMAC_OSC_H_DIV_NUM_100M_M  ((EMAC_OSC_H_DIV_NUM_100M_V)<<(EMAC_OSC_H_DIV_NUM_100M_S))
#define EMAC_OSC_H_DIV_NUM_100M_V  0x3F
#define EMAC_OSC_H_DIV_NUM_100M_S  18
/* EMAC_OSC_DIV_NUM_100M : R/W ;bitpos:[17:12] ;default: 6'd1 ; */
/*description: */
#define EMAC_OSC_DIV_NUM_100M  0x0000003F
#define EMAC_OSC_DIV_NUM_100M_M  ((EMAC_OSC_DIV_NUM_100M_V)<<(EMAC_OSC_DIV_NUM_100M_S))
#define EMAC_OSC_DIV_NUM_100M_V  0x3F
#define EMAC_OSC_DIV_NUM_100M_S  12
/* EMAC_OSC_H_DIV_NUM_10M : R/W ;bitpos:[11:6] ;default: 6'd9 ; */
/*description: */
#define EMAC_OSC_H_DIV_NUM_10M  0x0000003F
#define EMAC_OSC_H_DIV_NUM_10M_M  ((EMAC_OSC_H_DIV_NUM_10M_V)<<(EMAC_OSC_H_DIV_NUM_10M_S))
#define EMAC_OSC_H_DIV_NUM_10M_V  0x3F
#define EMAC_OSC_H_DIV_NUM_10M_S  6
/* EMAC_OSC_DIV_NUM_10M : R/W ;bitpos:[5:0] ;default: 6'd19 ; */
/*description: */
#define EMAC_OSC_DIV_NUM_10M  0x0000003F
#define EMAC_OSC_DIV_NUM_10M_M  ((EMAC_OSC_DIV_NUM_10M_V)<<(EMAC_OSC_DIV_NUM_10M_S))
#define EMAC_OSC_DIV_NUM_10M_V  0x3F
#define EMAC_OSC_DIV_NUM_10M_S  0

#define EMAC_EX_CLK_CTRL_REG          (DR_REG_EMAC_BASE + 0x0008)
/* EMAC_CLK_EN : R/W ;bitpos:[5] ;default: 1'h0 ; */
/*description: */
#define EMAC_CLK_EN  (BIT(5))
#define EMAC_CLK_EN_M  (BIT(5))
#define EMAC_CLK_EN_V  0x1
#define EMAC_CLK_EN_S  5
/* EMAC_MII_CLK_RX_EN : R/W ;bitpos:[4] ;default: 1'h0 ; */
/*description: */
#define EMAC_MII_CLK_RX_EN  (BIT(4))
#define EMAC_MII_CLK_RX_EN_M  (BIT(4))
#define EMAC_MII_CLK_RX_EN_V  0x1
#define EMAC_MII_CLK_RX_EN_S  4
/* EMAC_MII_CLK_TX_EN : R/W ;bitpos:[3] ;default: 1'h0 ; */
/*description: */
#define EMAC_MII_CLK_TX_EN  (BIT(3))
#define EMAC_MII_CLK_TX_EN_M  (BIT(3))
#define EMAC_MII_CLK_TX_EN_V  0x1
#define EMAC_MII_CLK_TX_EN_S  3
/* EMAC_RX_125_CLK_EN : R/W ;bitpos:[2] ;default: 1'h0 ; */
/*description: */
#define EMAC_RX_125_CLK_EN  (BIT(2))
#define EMAC_RX_125_CLK_EN_M  (BIT(2))
#define EMAC_RX_125_CLK_EN_V  0x1
#define EMAC_RX_125_CLK_EN_S  2
/* EMAC_INT_OSC_EN : R/W ;bitpos:[1] ;default: 1'h0 ; */
/*description: */
#define EMAC_INT_OSC_EN  (BIT(1))
#define EMAC_INT_OSC_EN_M  (BIT(1))
#define EMAC_INT_OSC_EN_V  0x1
#define EMAC_INT_OSC_EN_S  1
/* EMAC_EXT_OSC_EN : R/W ;bitpos:[0] ;default: 1'h0 ; */
/*description: */
#define EMAC_EXT_OSC_EN  (BIT(0))
#define EMAC_EXT_OSC_EN_M  (BIT(0))
#define EMAC_EXT_OSC_EN_V  0x1
#define EMAC_EXT_OSC_EN_S  0

#define EMAC_EX_PHYINF_CONF_REG          (DR_REG_EMAC_BASE + 0x000c)
/* EMAC_TX_ERR_OUT_EN : R/W ;bitpos:[20] ;default: 1'd0 ; */
/*description: */
#define EMAC_TX_ERR_OUT_EN  (BIT(20))
#define EMAC_TX_ERR_OUT_EN_M  (BIT(20))
#define EMAC_TX_ERR_OUT_EN_V  0x1
#define EMAC_TX_ERR_OUT_EN_S  20
/* EMAC_SCR_SMI_DLY_RX_SYNC : R/W ;bitpos:[19] ;default: 1'd0 ; */
/*description: */
#define EMAC_SCR_SMI_DLY_RX_SYNC  (BIT(19))
#define EMAC_SCR_SMI_DLY_RX_SYNC_M  (BIT(19))
#define EMAC_SCR_SMI_DLY_RX_SYNC_V  0x1
#define EMAC_SCR_SMI_DLY_RX_SYNC_S  19
/* EMAC_PMT_CTRL_EN : R/W ;bitpos:[18] ;default: 1'd0 ; */
/*description: */
#define EMAC_PMT_CTRL_EN  (BIT(18))
#define EMAC_PMT_CTRL_EN_M  (BIT(18))
#define EMAC_PMT_CTRL_EN_V  0x1
#define EMAC_PMT_CTRL_EN_S  18
/* EMAC_SBD_CLK_GATING_EN : R/W ;bitpos:[17] ;default: 1'b0 ; */
/*description: */
#define EMAC_SBD_CLK_GATING_EN  (BIT(17))
#define EMAC_SBD_CLK_GATING_EN_M  (BIT(17))
#define EMAC_SBD_CLK_GATING_EN_V  0x1
#define EMAC_SBD_CLK_GATING_EN_S  17
/* EMAC_SS_MODE : R/W ;bitpos:[16] ;default: 1'b0 ; */
/*description: */
#define EMAC_SS_MODE  (BIT(16))
#define EMAC_SS_MODE_M  (BIT(16))
#define EMAC_SS_MODE_V  0x1
#define EMAC_SS_MODE_S  16
/* EMAC_PHY_INTF_SEL : R/W ;bitpos:[15:13] ;default: 3'b0 ; */
/*description: */
#define EMAC_PHY_INTF_SEL  0x00000007
#define EMAC_PHY_INTF_SEL_M  ((EMAC_PHY_INTF_SEL_V)<<(EMAC_PHY_INTF_SEL_S))
#define EMAC_PHY_INTF_SEL_V  0x7
#define EMAC_PHY_INTF_SEL_S  13
/* EMAC_REVMII_PHY_ADDR : R/W ;bitpos:[12:8] ;default: 5'b0 ; */
/*description: */
#define EMAC_REVMII_PHY_ADDR  0x0000001F
#define EMAC_REVMII_PHY_ADDR_M  ((EMAC_REVMII_PHY_ADDR_V)<<(EMAC_REVMII_PHY_ADDR_S))
#define EMAC_REVMII_PHY_ADDR_V  0x1F
#define EMAC_REVMII_PHY_ADDR_S  8
/* EMAC_CORE_PHY_ADDR : R/W ;bitpos:[7:3] ;default: 5'b0 ; */
/*description: */
#define EMAC_CORE_PHY_ADDR  0x0000001F
#define EMAC_CORE_PHY_ADDR_M  ((EMAC_CORE_PHY_ADDR_V)<<(EMAC_CORE_PHY_ADDR_S))
#define EMAC_CORE_PHY_ADDR_V  0x1F
#define EMAC_CORE_PHY_ADDR_S  3
/* EMAC_SBD_FLOWCTRL : R/W ;bitpos:[2] ;default: 1'b0 ; */
/*description: */
#define EMAC_SBD_FLOWCTRL  (BIT(2))
#define EMAC_SBD_FLOWCTRL_M  (BIT(2))
#define EMAC_SBD_FLOWCTRL_V  0x1
#define EMAC_SBD_FLOWCTRL_S  2
/* EMAC_EXT_REVMII_RX_CLK_SEL : R/W ;bitpos:[1] ;default: 1'h0 ; */
/*description: */
#define EMAC_EXT_REVMII_RX_CLK_SEL  (BIT(1))
#define EMAC_EXT_REVMII_RX_CLK_SEL_M  (BIT(1))
#define EMAC_EXT_REVMII_RX_CLK_SEL_V  0x1
#define EMAC_EXT_REVMII_RX_CLK_SEL_S  1
/* EMAC_INT_REVMII_RX_CLK_SEL : R/W ;bitpos:[0] ;default: 1'h0 ; */
/*description: */
#define EMAC_INT_REVMII_RX_CLK_SEL  (BIT(0))
#define EMAC_INT_REVMII_RX_CLK_SEL_M  (BIT(0))
#define EMAC_INT_REVMII_RX_CLK_SEL_V  0x1
#define EMAC_INT_REVMII_RX_CLK_SEL_S  0

#define EMAC_PD_SEL_REG          (DR_REG_EMAC_BASE + 0x0010)
/* EMAC_RAM_PD_EN : R/W ;bitpos:[1:0] ;default: 1'd0 ; */
/*description: */
#define EMAC_RAM_PD_EN  0x00000003
#define EMAC_RAM_PD_EN_M  ((EMAC_RAM_PD_EN_V)<<(EMAC_RAM_PD_EN_S))
#define EMAC_RAM_PD_EN_V  0x3
#define EMAC_RAM_PD_EN_S  0

#define EMAC_EX_DATE_REG          (DR_REG_EMAC_BASE + 0x00fc)
/* EMAC_EX_DATE : R/W ;bitpos:[31:0] ;default: 32'h16042200 ; */
/*description: */
#define EMAC_EX_DATE  0xFFFFFFFF
#define EMAC_EX_DATE_M  ((EMAC_EX_DATE_V)<<(EMAC_EX_DATE_S))
#define EMAC_EX_DATE_V  0xFFFFFFFF
#define EMAC_EX_DATE_S  0

#ifdef __cplusplus
}
#endif



#endif /*_SOC_EMAC_REG_H_ */


