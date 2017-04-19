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

#ifndef _MESH_TCPIP_H_
#define _MESH_TCPIP_H_

#include "esp_err.h"

/*******************************************************
 *                Function Definitions
 *******************************************************/
void esp_mesh_tcpip_enable_dhcp(void);
void esp_mesh_tcpip_disable_dhcp(void);
esp_err_t esp_mesh_tcp_client_start(const char* hostname, int hostname_len,
        int port);
esp_err_t esp_mesh_tcp_client_stop(void);

#endif /* _MESH_TCPIP_H_ */
