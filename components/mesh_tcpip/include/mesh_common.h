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

#ifndef __MESH_COMMON_H__
#define __MESH_COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "malloc.h"
#include "string.h"
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_err.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include "esp_wifi_internal.h"

/*******************************************************
 *                Constants
 *******************************************************/
#define MESH_GRP_ID_LEN                   (6)
#define MESH_HWADDR_LEN                   (6)
#define MESH_SSID_LEN_MAX                 (32)
#define MESH_IP_ADDR_LEN                  (4)
#define MESH_PASSWD_LEN_MAX               (64)

#define MESH_DEBUG ets_printf
#define MESH_PRINT ets_printf

#define MESH_ENTER_CRITICAL()
#define MESH_EXIT_CRITICAL()

/*******************************************************
 *                Type Definitions
 *******************************************************/
typedef wifi_vnd_mesh_assoc_t mesh_ie_t;

/*******************************************************
 *                Structures
 *******************************************************/
typedef struct
{
    uint8_t bssid[MESH_HWADDR_LEN];
    uint8_t ssid[MESH_SSID_LEN_MAX];
    uint8_t primary;
    wifi_second_chan_t second;
    int8_t rssi;
    wifi_auth_mode_t authmode;
    void *mesh_ie;
} mesh_ap_info_t;

struct mesh_ap_elem_t
{
    mesh_ap_info_t ap;
    struct mesh_ap_elem_t *next;
};

struct mesh_grp_id_t
{
    uint8_t grp_id[MESH_GRP_ID_LEN];
    uint8_t gid_len;
    uint8_t set;
};

struct mesh_router_rssi_info_type
{
    int8_t rssi;
    uint16_t count;
};

struct mesh_encrypt_t
{
    uint8_t passwd[MESH_PASSWD_LEN_MAX];
    uint8_t pwlen;    // password length
    wifi_auth_mode_t mode;  // algorithm of encryption
    bool set;
};

struct mesh_server_info_t
{
    uint8_t ip[MESH_IP_ADDR_LEN];
    uint16_t port;
};

typedef struct mesh_router_info
{
    wifi_sta_config_t router;
    uint8_t set;
} mesh_router_info_t;

/*******************************************************
 *                Variables Declarations
 *******************************************************/
extern struct mesh_server_info_t g_mesh_server_info;

/*******************************************************
 *                Function Definitions
 *******************************************************/
void esp_mesh_free_packet_contxt(void *ctx);

#endif
