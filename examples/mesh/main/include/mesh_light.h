// Copyright 2017-2018 Espressif Systems (Shanghai) PTE LTD
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

#ifndef _MESH_LIGHT_H_
#define _MESH_LIGHT_H_

#include "esp_err.h"

/*******************************************************
 *                Constants
 *******************************************************/
#define RGB_LIGHT_RED       (0xff)
#define RGB_LIGHT_GREEN     (0xfe)
#define RGB_LIGHT_BLUE      (0xfd)
#define RGB_LIGHT_YELLOW    (0xfc)
#define RGB_LIGHT_PINK      (0xfb)
#define RGB_LIGHT_INIT      (0xfa)
#define RGB_LIGHT_WARNING   (0xf9)

/*******************************************************
 *                Function Definitions
 *******************************************************/
esp_err_t mesh_gpio_set(int value);
esp_err_t mesh_gpio_get(int *value);
esp_err_t mesh_light_init(void);

#endif /* _MESH_LIGHT_H_ */
