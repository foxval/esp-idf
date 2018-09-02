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

#ifdef __cplusplus
extern "C" {
#endif

#include"extmem_reg.h"
#include"interrupt_reg.h"
#include"system_reg.h"
#include "sensitive_reg.h"
#include "soc.h"

#define PROCACHE_IMMU_ADDR_BASE 0x3FEC5000
#define PROCACHE_IMMU_SIZE      0x400
#define PROCACHE_DMMU_ADDR_BASE 0x3FEC5400
#define PROCACHE_DMMU_SIZE      0x200
/* Flash MMU table for PRO CPU */
#define DPORT_PRO_FLASH_MMU_TABLE ((volatile uint32_t*) 0x3FEC5000)

#define DPORT_FLASH_MMU_TABLE_SIZE 0x100

#define DPORT_FLASH_MMU_TABLE_INVALID_VAL 0x4000

#define DPORT_DATE_REG SYSTEM_DATE_REG

#ifndef __ASSEMBLER__
#include "dport_access.h"
#endif

#ifdef __cplusplus
}
#endif

#endif /*_SOC_DPORT_REG_H_ */


