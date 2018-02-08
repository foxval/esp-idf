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

#ifndef _MESH_TCPIP_H_
#define _MESH_TCPIP_H_

#include "esp_err.h"

/*******************************************************
 *                Constants
 *******************************************************/
#define MESH_SERVER_CONNECTED                   (1)
#define MESH_SERVER_DISCONNECTED                (0)

/*******************************************************
 *                Function Definitions
 *******************************************************/

esp_err_t esp_mesh_tcp_client_start(const char *hostname, int hostname_len,
                                    int port);
esp_err_t esp_mesh_tcp_client_stop(void);

esp_err_t esp_mesh_send_to_server(void *message, uint32_t timeout_ms);

int esp_mesh_is_server_connected(void);

#endif /* _MESH_TCPIP_H_ */
