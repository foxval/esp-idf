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
#ifndef _SOC_GPIO_STRUCT_H_
#define _SOC_GPIO_STRUCT_H_
#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct {
    uint32_t bt_select;                             /**/
    uint32_t out;                                   /**/
    uint32_t out_w1ts;                              /**/
    uint32_t out_w1tc;                              /**/
    union {
        struct {
            uint32_t data:      22;
            uint32_t reserved22:10;
        };
        uint32_t val;
    } out1;
    union {
        struct {
            uint32_t data:      22;
            uint32_t reserved22:10;
        };
        uint32_t val;
    } out1_w1ts;
    union {
        struct {
            uint32_t data:      22;
            uint32_t reserved22:10;
        };
        uint32_t val;
    } out1_w1tc;
    union {
        struct {
            uint32_t sel:        8;
            uint32_t reserved8: 24;
        };
        uint32_t val;
    } sdio_select;
    uint32_t enable;                                /**/
    uint32_t enable_w1ts;                           /**/
    uint32_t enable_w1tc;                           /**/
    union {
        struct {
            uint32_t data:       22;
            uint32_t reserved22: 10;
        };
        uint32_t val;
    } enable1;
    union {
        struct {
            uint32_t data:       22;
            uint32_t reserved22: 10;
        };
        uint32_t val;
    } enable1_w1ts;
    union {
        struct {
            uint32_t data:       22;
            uint32_t reserved22: 10;
        };
        uint32_t val;
    } enable1_w1tc;
    union {
        struct {
            uint32_t strapping: 16;
            uint32_t reserved16:16;
        };
        uint32_t val;
    } strap;
    uint32_t in;                                    /**/
    union {
        struct {
            uint32_t data:        22;
            uint32_t reserved22:  10;
        };
        uint32_t val;
    } in1;
    uint32_t status;                                /**/
    uint32_t status_w1ts;                           /**/
    uint32_t status_w1tc;                           /**/
    union {
        struct {
            uint32_t intr_st:         22;
            uint32_t reserved22:      10;
        };
        uint32_t val;
    } status1;
    union {
        struct {
            uint32_t intr_st:         22;
            uint32_t reserved22:      10;
        };
        uint32_t val;
    } status1_w1ts;
    union {
        struct {
            uint32_t intr_st:         22;
            uint32_t reserved22:      10;
        };
        uint32_t val;
    } status1_w1tc;
    uint32_t pcpu_int;                              /**/
    uint32_t pcpu_nmi_int;                          /**/
    uint32_t cpusdio_int;                           /**/
    union {
        struct {
            uint32_t intr:      22;
            uint32_t reserved22:10;
        };
        uint32_t val;
    } pcpu_int1;
    union {
        struct {
            uint32_t intr:          22;
            uint32_t reserved22:    10;
        };
        uint32_t val;
    } pcpu_nmi_int1;
    union {
        struct {
            uint32_t intr:      22;
            uint32_t reserved22:10;
        };
        uint32_t val;
    } cpusdio_int1;
    union {
        struct {
            uint32_t sync2_bypass:       2;
            uint32_t pad_driver:         1;
            uint32_t sync1_bypass:       2;
            uint32_t reserved5:          2;
            uint32_t int_type:           3;
            uint32_t wakeup_enable:      1;
            uint32_t config:             2;
            uint32_t int_ena:            5;
            uint32_t reserved18:        14;
        };
        uint32_t val;
    } pin[40];
    union {
        struct {
            uint32_t pin40_sync2_bypass:  2;
            uint32_t pin40_pad_driver:    1;
            uint32_t pin40_sync1_bypass:  2;
            uint32_t reserved5:           2;
            uint32_t pin40_int_type:      3;
            uint32_t pin40_wakeup_enable: 1;
            uint32_t pin40_config:        2;
            uint32_t pin40:               5;
            uint32_t reserved18:         14;
        };
        uint32_t val;
    } pin40;
    union {
        struct {
            uint32_t pin41_sync2_bypass:  2;
            uint32_t pin41_pad_driver:    1;
            uint32_t pin41_sync1_bypass:  2;
            uint32_t reserved5:           2;
            uint32_t pin41_int_type:      3;
            uint32_t pin41_wakeup_enable: 1;
            uint32_t pin41_config:        2;
            uint32_t pin41:               5;
            uint32_t reserved18:         14;
        };
        uint32_t val;
    } pin41;
    union {
        struct {
            uint32_t pin42_sync2_bypass:  2;
            uint32_t pin42_pad_driver:    1;
            uint32_t pin42_sync1_bypass:  2;
            uint32_t reserved5:           2;
            uint32_t pin42_int_type:      3;
            uint32_t pin42_wakeup_enable: 1;
            uint32_t pin42_config:        2;
            uint32_t pin42:               5;
            uint32_t reserved18:         14;
        };
        uint32_t val;
    } pin42;
    union {
        struct {
            uint32_t pin43_sync2_bypass:  2;
            uint32_t pin43_pad_driver:    1;
            uint32_t pin43_sync1_bypass:  2;
            uint32_t reserved5:           2;
            uint32_t pin43_int_type:      3;
            uint32_t pin43_wakeup_enable: 1;
            uint32_t pin43_config:        2;
            uint32_t pin43:               5;
            uint32_t reserved18:         14;
        };
        uint32_t val;
    } pin43;
    union {
        struct {
            uint32_t pin44_sync2_bypass:  2;
            uint32_t pin44_pad_driver:    1;
            uint32_t pin44_sync1_bypass:  2;
            uint32_t reserved5:           2;
            uint32_t pin44_int_type:      3;
            uint32_t pin44_wakeup_enable: 1;
            uint32_t pin44_config:        2;
            uint32_t pin44:               5;
            uint32_t reserved18:         14;
        };
        uint32_t val;
    } pin44;
    union {
        struct {
            uint32_t pin45_sync2_bypass:  2;
            uint32_t pin45_pad_driver:    1;
            uint32_t pin45_sync1_bypass:  2;
            uint32_t reserved5:           2;
            uint32_t pin45_int_type:      3;
            uint32_t pin45_wakeup_enable: 1;
            uint32_t pin45_config:        2;
            uint32_t pin45:               5;
            uint32_t reserved18:         14;
        };
        uint32_t val;
    } pin45;
    union {
        struct {
            uint32_t pin46_sync2_bypass:  2;
            uint32_t pin46_pad_driver:    1;
            uint32_t pin46_sync1_bypass:  2;
            uint32_t reserved5:           2;
            uint32_t pin46_int_type:      3;
            uint32_t pin46_wakeup_enable: 1;
            uint32_t pin46_config:        2;
            uint32_t pin46:               5;
            uint32_t reserved18:         14;
        };
        uint32_t val;
    } pin46;
    union {
        struct {
            uint32_t pin47_sync2_bypass:  2;
            uint32_t pin47_pad_driver:    1;
            uint32_t pin47_sync1_bypass:  2;
            uint32_t reserved5:           2;
            uint32_t pin47_int_type:      3;
            uint32_t pin47_wakeup_enable: 1;
            uint32_t pin47_config:        2;
            uint32_t pin47:               5;
            uint32_t reserved18:         14;
        };
        uint32_t val;
    } pin47;
    union {
        struct {
            uint32_t pin48_sync2_bypass:  2;
            uint32_t pin48_pad_driver:    1;
            uint32_t pin48_sync1_bypass:  2;
            uint32_t reserved5:           2;
            uint32_t pin48_int_type:      3;
            uint32_t pin48_wakeup_enable: 1;
            uint32_t pin48_config:        2;
            uint32_t pin48:               5;
            uint32_t reserved18:         14;
        };
        uint32_t val;
    } pin48;
    union {
        struct {
            uint32_t pin49_sync2_bypass:  2;
            uint32_t pin49_pad_driver:    1;
            uint32_t pin49_sync1_bypass:  2;
            uint32_t reserved5:           2;
            uint32_t pin49_int_type:      3;
            uint32_t pin49_wakeup_enable: 1;
            uint32_t pin49_config:        2;
            uint32_t pin49:               5;
            uint32_t reserved18:         14;
        };
        uint32_t val;
    } pin49;
    union {
        struct {
            uint32_t pin50_sync2_bypass:  2;
            uint32_t pin50_pad_driver:    1;
            uint32_t pin50_sync1_bypass:  2;
            uint32_t reserved5:           2;
            uint32_t pin50_int_type:      3;
            uint32_t pin50_wakeup_enable: 1;
            uint32_t pin50_config:        2;
            uint32_t pin50:               5;
            uint32_t reserved18:         14;
        };
        uint32_t val;
    } pin50;
    union {
        struct {
            uint32_t pin51_sync2_bypass:  2;
            uint32_t pin51_pad_driver:    1;
            uint32_t pin51_sync1_bypass:  2;
            uint32_t reserved5:           2;
            uint32_t pin51_int_type:      3;
            uint32_t pin51_wakeup_enable: 1;
            uint32_t pin51_config:        2;
            uint32_t pin51:               5;
            uint32_t reserved18:         14;
        };
        uint32_t val;
    } pin51;
    union {
        struct {
            uint32_t pin52_sync2_bypass:  2;
            uint32_t pin52_pad_driver:    1;
            uint32_t pin52_sync1_bypass:  2;
            uint32_t reserved5:           2;
            uint32_t pin52_int_type:      3;
            uint32_t pin52_wakeup_enable: 1;
            uint32_t pin52_config:        2;
            uint32_t pin52:               5;
            uint32_t reserved18:         14;
        };
        uint32_t val;
    } pin52;
    union {
        struct {
            uint32_t pin53_sync2_bypass:  2;
            uint32_t pin53_pad_driver:    1;
            uint32_t pin53_sync1_bypass:  2;
            uint32_t reserved5:           2;
            uint32_t pin53_int_type:      3;
            uint32_t pin53_wakeup_enable: 1;
            uint32_t pin53_config:        2;
            uint32_t pin53:               5;
            uint32_t reserved18:         14;
        };
        uint32_t val;
    } pin53;
    union {
        struct {
            uint32_t rtc_max:     10;
            uint32_t reserved10:  21;
            uint32_t start:        1;
        };
        uint32_t val;
    } cali_conf;
    union {
        struct {
            uint32_t value_sync2:     20;
            uint32_t reserved20:      10;
            uint32_t rdy_real:         1;
            uint32_t rdy_sync2:        1;
        };
        uint32_t val;
    } cali_data;
    union {
        struct {
            uint32_t func_sel:         6;
            uint32_t sig_in_inv:       1;
            uint32_t sig_in_sel:       1;
            uint32_t reserved8:       24;
        };
        uint32_t val;
    } func_in_sel_cfg[256];
    union {
        struct {
            uint32_t func_sel:          9;
            uint32_t inv_sel:           1;
            uint32_t oen_sel:           1;
            uint32_t oen_inv_sel:       1;
            uint32_t reserved12:       20;
        };
        uint32_t val;
    } func_out_sel_cfg[40];
    union {
        struct {
            uint32_t func40_out_sel:     9;
            uint32_t func40_out_inv_sel: 1;
            uint32_t func40_oen_sel:     1;
            uint32_t func40_oen_inv_sel: 1;
            uint32_t reserved12:        20;
        };
        uint32_t val;
    } func40_out_sel_cfg;
    union {
        struct {
            uint32_t func41_out_sel:     9;
            uint32_t func41_out_inv_sel: 1;
            uint32_t func41_oen_sel:     1;
            uint32_t func41_oen_inv_sel: 1;
            uint32_t reserved12:        20;
        };
        uint32_t val;
    } func41_out_sel_cfg;
    union {
        struct {
            uint32_t func42_out_sel:     9;
            uint32_t func42_out_inv_sel: 1;
            uint32_t func42_oen_sel:     1;
            uint32_t func42_oen_inv_sel: 1;
            uint32_t reserved12:        20;
        };
        uint32_t val;
    } func42_out_sel_cfg;
    union {
        struct {
            uint32_t func43_out_sel:     9;
            uint32_t func43_out_inv_sel: 1;
            uint32_t func43_oen_sel:     1;
            uint32_t func43_oen_inv_sel: 1;
            uint32_t reserved12:        20;
        };
        uint32_t val;
    } func43_out_sel_cfg;
    union {
        struct {
            uint32_t func44_out_sel:     9;
            uint32_t func44_out_inv_sel: 1;
            uint32_t func44_oen_sel:     1;
            uint32_t func44_oen_inv_sel: 1;
            uint32_t reserved12:        20;
        };
        uint32_t val;
    } func44_out_sel_cfg;
    union {
        struct {
            uint32_t func45_out_sel:     9;
            uint32_t func45_out_inv_sel: 1;
            uint32_t func45_oen_sel:     1;
            uint32_t func45_oen_inv_sel: 1;
            uint32_t reserved12:        20;
        };
        uint32_t val;
    } func45_out_sel_cfg;
    union {
        struct {
            uint32_t func46_out_sel:     9;
            uint32_t func46_out_inv_sel: 1;
            uint32_t func46_oen_sel:     1;
            uint32_t func46_oen_inv_sel: 1;
            uint32_t reserved12:        20;
        };
        uint32_t val;
    } func46_out_sel_cfg;
    union {
        struct {
            uint32_t func47_out_sel:     9;
            uint32_t func47_out_inv_sel: 1;
            uint32_t func47_oen_sel:     1;
            uint32_t func47_oen_inv_sel: 1;
            uint32_t reserved12:        20;
        };
        uint32_t val;
    } func47_out_sel_cfg;
    union {
        struct {
            uint32_t func48_out_sel:     9;
            uint32_t func48_out_inv_sel: 1;
            uint32_t func48_oen_sel:     1;
            uint32_t func48_oen_inv_sel: 1;
            uint32_t reserved12:        20;
        };
        uint32_t val;
    } func48_out_sel_cfg;
    union {
        struct {
            uint32_t func49_out_sel:     9;
            uint32_t func49_out_inv_sel: 1;
            uint32_t func49_oen_sel:     1;
            uint32_t func49_oen_inv_sel: 1;
            uint32_t reserved12:        20;
        };
        uint32_t val;
    } func49_out_sel_cfg;
    union {
        struct {
            uint32_t func50_out_sel:     9;
            uint32_t func50_out_inv_sel: 1;
            uint32_t func50_oen_sel:     1;
            uint32_t func50_oen_inv_sel: 1;
            uint32_t reserved12:        20;
        };
        uint32_t val;
    } func50_out_sel_cfg;
    union {
        struct {
            uint32_t func51_out_sel:     9;
            uint32_t func51_out_inv_sel: 1;
            uint32_t func51_oen_sel:     1;
            uint32_t func51_oen_inv_sel: 1;
            uint32_t reserved12:        20;
        };
        uint32_t val;
    } func51_out_sel_cfg;
    union {
        struct {
            uint32_t func52_out_sel:     9;
            uint32_t func52_out_inv_sel: 1;
            uint32_t func52_oen_sel:     1;
            uint32_t func52_oen_inv_sel: 1;
            uint32_t reserved12:        20;
        };
        uint32_t val;
    } func52_out_sel_cfg;
    union {
        struct {
            uint32_t func53_out_sel:     9;
            uint32_t func53_out_inv_sel: 1;
            uint32_t func53_oen_sel:     1;
            uint32_t func53_oen_inv_sel: 1;
            uint32_t reserved12:        20;
        };
        uint32_t val;
    } func53_out_sel_cfg;
} gpio_dev_t;
extern gpio_dev_t GPIO;
#ifdef __cplusplus
}
#endif

#endif  /* _SOC_GPIO_STRUCT_H_ */
