// Copyright 2015-2017 Espressif Systems (Shanghai) PTE LTD
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

#include "tcpip_adapter.h"

/*******************************************************
 *                Variable Definitions
 *******************************************************/
static bool is_dhcp_stopped = false;

/*******************************************************
 *                Function Definitions
 *******************************************************/

void esp_mesh_enable_dhcp(void)
{
    if (is_dhcp_stopped) {
        tcpip_adapter_dhcpc_start(TCPIP_ADAPTER_IF_STA);
        is_dhcp_stopped = false;
    }
}

void esp_mesh_disable_dhcp(void)
{
    if (!is_dhcp_stopped) {
        tcpip_adapter_dhcps_stop(TCPIP_ADAPTER_IF_AP);
        tcpip_adapter_dhcpc_stop(TCPIP_ADAPTER_IF_STA);
        is_dhcp_stopped = true;
    }
}
