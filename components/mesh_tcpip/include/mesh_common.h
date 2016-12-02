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
#include "esp_err.h"
#include "esp_event.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_wifi_types.h"
#include "esp_wifi_internal.h"

/***************** mesh constant *****************/
#define MESH_GRP_ID_LEN                   (6)
#define MESH_HWADDR_LEN                   (6)
#define MESH_SSID_LEN_MAX                 (32)
#define MESH_IP_ADDR_LEN                  (4)
#define MESH_PASSWD_LEN_MAX               (64)
#define MESH_INVALID_NVS_HANDLE           ((uint32_t)-1)
#define MESH_DESTROY_CTX                  ((void *)-1)
/*************************************************/

#define MESH_FREE    free
#define MESH_ZALLOC  zalloc
#define MESH_MALLOC  malloc
#define MESH_MEMCPY  memcpy
#define MESH_MEMCMP  memcmp
#define MESH_MEMSET  memset
#define MESH_DEBUG   printf
#define MESH_PRINT   printf
#define MESH_STRLEN  strlen
#define MESH_SPRINTF sprintf
#define MESH_OTA_DBG

#define MESH_ENTER_CRITICAL()
#define MESH_EXIT_CRITICAL()

//#define MESH_FUNC_ATTR ICACHE_FLASH_ATTR
#define MESH_FUNC_ATTR 

typedef struct {
  u32_t addr;
} esp_ip_addr_t;

typedef wifi_sta_config_t mesh_wifi_stat_t;
typedef wifi_vnd_mesh_assoc_t mesh_ie_t;
//typedef esp_ip_addr_t ip_addr_t;

typedef struct {
    uint8_t bssid[MESH_HWADDR_LEN];
    uint8_t ssid[MESH_SSID_LEN_MAX];
    uint8_t primary;
    wifi_second_chan_t second;
    int8_t rssi;
    wifi_auth_mode_t authmode;
    void *mesh_ie;
} mesh_ap_info_t;

struct mesh_ap_elem_t {
    mesh_ap_info_t ap;
    struct mesh_ap_elem_t *next;
};

struct mesh_grp_id_t {
    uint8_t grp_id[MESH_GRP_ID_LEN];
    uint8_t gid_len;
    uint8_t set;
};

struct mesh_router_rssi_info_type {
    int8_t rssi;
    uint16_t count;
};

struct mesh_encrypt_t {
    uint8_t passwd[MESH_PASSWD_LEN_MAX];
    uint8_t pwlen;    // password length
    wifi_auth_mode_t mode;  // algorithm of encryption
    bool set;
};

struct mesh_server_info_t {
    uint8_t ip[MESH_IP_ADDR_LEN];
    uint16_t port;
};

typedef struct mesh_router_info {
    mesh_wifi_stat_t router;
    uint8_t set;
} mesh_router_info_t;

struct mesh_parent_info_t {
    uint8_t bssid[MESH_HWADDR_LEN];
    uint8_t ssid[MESH_SSID_LEN_MAX];
    uint8_t ssid_len;
    uint8_t channel;
    int8_t rssi;
    wifi_auth_mode_t authmode;
};

struct mesh_ap_list_head_t {
    struct mesh_ap_elem_t *ap_list;
    uint8_t count;
};

extern bool g_fix_channel;
extern bool g_mesh_as_root;
extern uint8_t g_mesh_max_hop;
extern uint8_t g_mesh_last_hop;
extern uint8_t g_mesh_scan_retries;
extern int8_t g_mesh_rssi_threshold;
extern struct mesh_ctx_t g_mesh_ctx;
extern nvs_handle g_mesh_nvs_handler;
extern wifi_vnd_mesh_assoc_t g_mesh_ie;
extern xTaskHandle g_mesh_rx_task_handle;
extern struct mesh_grp_id_t g_mesh_grp_id;
extern struct mesh_encrypt_t g_mesh_encrypt;
extern mesh_router_info_t g_mesh_router_info;
extern QueueHandle_t g_mesh_rx_queue_handler;
extern QueueHandle_t g_mesh_fsm_queue_handler;
extern QueueHandle_t g_mesh_nvs_queue_handler;
extern QueueHandle_t g_schedule_queue_handler;
extern QueueHandle_t g_mesh_usr_queue_handler;
extern QueueHandle_t g_mesh_tcpip_queue_handler;
extern struct mesh_server_info_t g_mesh_server_info;
extern struct mesh_parent_info_t g_mesh_parent_info;
extern struct mesh_router_rssi_info_type g_mesh_router_rssi;

void *zalloc(size_t len);
void esp32_mesh_free_packet_contxt(void *ctx);
void esp32_mesh_clear_ap_list(struct mesh_ap_list_head_t *ap_list_head);
bool esp32_mesh_ap_list_find(struct mesh_ap_list_head_t *ap_list_head,
                             mesh_ap_info_t *ap, bool update);
void esp32_mesh_ap_enqueue(struct mesh_ap_list_head_t *ap_list_head,
                           mesh_ap_info_t *ap);
void mesh_print_task_info();
#endif
