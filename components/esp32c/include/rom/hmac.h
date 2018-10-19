// Copyright 2018 Espressif Systems (Shanghai) PTE LTD
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

#ifndef _ROM_HMAC_H_
#define _ROM_HMAC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include "rom/efuse.h"

void ets_hmac_enable(void);

void ets_hmac_disable(void);

/* Use the "upstream" HMAC key (ETS_EFUSE_KEY_PURPOSE_HMAC_UP)
   to digest a message.
*/
int ets_hmac_calculate_message(ets_efuse_block_t key_block, const void *message, size_t message_len, uint8_t *hmac);

#ifdef __cplusplus
}
#endif

#endif // _ROM_HMAC_H_
