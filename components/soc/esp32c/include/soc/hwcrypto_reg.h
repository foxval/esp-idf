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
#ifndef __HWCRYPTO_REG_H__
#define __HWCRYPTO_REG_H__

#include "soc.h"

/* registers for RSA acceleration via Multiple Precision Integer ops */
#define RSA_MEM_M_BLOCK_BASE          ((DR_REG_RSA_BASE)+0x000)
/* RB & Z use the same memory block, depending on phase of operation */
#define RSA_MEM_RB_BLOCK_BASE         ((DR_REG_RSA_BASE)+0x200)
#define RSA_MEM_Z_BLOCK_BASE          ((DR_REG_RSA_BASE)+0x200)
#define RSA_MEM_Y_BLOCK_BASE          ((DR_REG_RSA_BASE)+0x400)
#define RSA_MEM_X_BLOCK_BASE          ((DR_REG_RSA_BASE)+0x600)

#define RSA_M_DASH_REG                (DR_REG_RSA_BASE + 0x800)
#define RSA_MODEXP_MODE_REG           (DR_REG_RSA_BASE + 0x804)
#define RSA_START_MODEXP_REG          (DR_REG_RSA_BASE + 0x808)
#define RSA_MULT_MODE_REG             (DR_REG_RSA_BASE + 0x80c)
#define RSA_MULT_START_REG            (DR_REG_RSA_BASE + 0x810)

#define RSA_INTERRUPT_REG             (DR_REG_RSA_BASE + 0x814)

#define RSA_CLEAN_REG                 (DR_REG_RSA_BASE + 0x818)


/* SHA acceleration registers */
#define SHA_MODE_REG                  ((DR_REG_SHA_BASE) + 0x00)

#define SHA_MODE_SHA1 0
#define SHA_MODE_SHA224 1
#define SHA_MODE_SHA256 2
#define SHA_MODE_SHA384 3
#define SHA_MODE_SHA512 4
#define SHA_MODE_SHA512_224 5
#define SHA_MODE_SHA512_256 6
#define SHA_MODE_SHA512_T 7

#define SHA_T_STRING_REG              ((DR_REG_SHA_BASE) + 0x04)
#define SHA_T_LENGTH_REG              ((DR_REG_SHA_BASE) + 0x08)
#define SHA_START_REG                 ((DR_REG_SHA_BASE) + 0x0c)
#define SHA_CONTINUE_REG              ((DR_REG_SHA_BASE) + 0x10)
#define SHA_BUSY_REG                  ((DR_REG_SHA_BASE) + 0x14)

#define SHA_H_BASE                    ((DR_REG_SHA_BASE) + 0x40)
#define SHA_M_BASE                    ((DR_REG_SHA_BASE) + 0x80)

/* AES acceleration registers */
#define AES_START_REG           ((DR_REG_AES_BASE) + 0x00)
#define AES_IDLE_REG            ((DR_REG_AES_BASE) + 0x04)
#define AES_MODE_REG            ((DR_REG_AES_BASE) + 0x08)
#define AES_KEY_BASE            ((DR_REG_AES_BASE) + 0x10)
#define AES_TEXT_BASE           ((DR_REG_AES_BASE) + 0x30)
#define AES_ENDIAN              ((DR_REG_AES_BASE) + 0x40)

#endif
