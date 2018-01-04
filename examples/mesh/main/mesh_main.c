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

#include "esp_mesh.h"
#include "esp_mesh_internal.h"
#include "mesh_log.h"
#include "mesh_cloud.h"
#include "mesh_light.h"
#include "mesh_config.h"
#include "mesh_tcpip.h"
#include "mesh_common.h"
#include "nvs.h"
#include "esp_timer.h"

/*******************************************************
 *                Macros
 *******************************************************/

/*******************************************************
 *                Constants
 *******************************************************/
#define RX_SIZE          (1500)
#define TX_SIZE          (1460)
#define TX_MCAST_SIZE    (1200)

/*******************************************************
 *                Variable Definitions
 *******************************************************/
static const char *TAG = "mesh_main";
static bool is_running = true;
static bool is_mesh_connected = false;
static bool is_voting = false;
static bool is_dhcp_stopped = false;
static uint8_t mesh_toDS_reachable = 0;
static mesh_addr_t mesh_sta_addr;
static int vote_times = 0;

/*******************************************************
 *                Function Declarations
 *******************************************************/
esp_err_t esp_mesh_comm_p2p_start(void);
esp_err_t esp_mesh_comm_server_start(void);
esp_err_t esp_mesh_print_settings(void);
void print_sta_list(const char *func);

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

bool esp_mesh_is_toDS_reachable(void)
{
    return mesh_toDS_reachable;
}

void esp_mesh_connected(int layer)
{
    if (esp_mesh_is_root()) {
        /* layer one: pink */
        mesh_gpio_set(RGB_LIGHT_PINK);
        return;
    }

    if (layer == 2) {
        /* layer two: yellow */
        mesh_gpio_set(RGB_LIGHT_YELLOW);
    } else if (layer == 3) {
        /* layer one: red */
        mesh_gpio_set(RGB_LIGHT_RED);
    } else if (layer == 4) {
        /* layer one: blue */
        mesh_gpio_set(RGB_LIGHT_BLUE);
    } else if (layer == 5) {
        /* layer one: green */
        mesh_gpio_set(RGB_LIGHT_GREEN);
    } else if (layer >= 6) {
        /* layer one: white */
        mesh_gpio_set(RGB_LIGHT_WARNING);
    } else {
        mesh_gpio_set(1);
    }
}

void esp_mesh_disconnected(void)
{
    mesh_gpio_set(RGB_LIGHT_WARNING);
}

void esp_mesh_event_cb(mesh_event_t event)
{
    int layer = 0;
    static int last_layer = 0;

    switch (event) {

    case MESH_EVENT_NO_AP_FOUND:
        /* no AP found */
        MESH_LOGE("err: no AP found after scan %d times\n",
                  MESH_SCAN_RETRIES)
        ;
        /* TODO handler for the failure */
        break;

    case MESH_EVENT_CONNECTED:
        /* wifi connected */
        layer = esp_mesh_get_layer();
        MESH_LOGI("MESH_EVENT_CONNECTED, layer:%d-->%d%s", last_layer,
                  layer,
                  esp_mesh_is_root() ? "[ROOT]" :
                  (layer == 2) ? "[Layer2]" : "")
        ;
        last_layer = layer;
        esp_mesh_connected(layer);
        is_mesh_connected = true;
        if (esp_mesh_is_root()) {
            is_voting = false;
//          esp_mesh_enable_dhcp();
        } else {
//          esp_mesh_disable_dhcp();
        }
        esp_mesh_print_settings();
        {
            wifi_vnd_mesh_assoc_t assoc;
            esp_wifi_vnd_mesh_get(&assoc);
            MESH_LOGI(
                "parent rssi:%d, router rssi:%d, layer[%d,%d], child[%d,%d], total[%d,%d], scan:%d\n",
                assoc.ap_rssi, assoc.router_rssi, assoc.layer_cap,
                assoc.layer_lvl, assoc.dev_cap, assoc.dev_assoc,
                assoc.total_cap, assoc.total_assoc, assoc.scan_ap_num);
        }

#ifdef MESH_P2P_FORWARD_TEST
        esp_mesh_comm_p2p_start();
#else /* MESH_P2P_FORWARD_TEST */
        esp_mesh_comm_server_start();
#endif /* MESH_P2P_FORWARD_TEST */
        break;

    case MESH_EVENT_DISCONNECTED:
        /* wifi disconnected */
        MESH_LOGI("MESH_EVENT_DISCONNECTED")
        ;
        is_mesh_connected = false;
        esp_mesh_disconnected();
#ifndef MESH_P2P_FORWARD_TEST
        esp_mesh_tcp_client_stop();
#endif /* MESH_P2P_FORWARD_TEST */
        break;

    case MESH_EVENT_LAYER_CHANGE:
        /* mesh device layer changes */
        layer = esp_mesh_get_layer();
        MESH_LOGI("MESH_EVENT_CONNECTED, layer:%d-->%d%s", last_layer,
                  layer,
                  esp_mesh_is_root() ? "[ROOT]" :
                  (layer == 2) ? "[Layer2]" : "")
        ;
        last_layer = layer;
        esp_mesh_connected(layer);
#ifndef MESH_P2P_FORWARD_TEST
        if (!esp_mesh_is_root()) {
            /* non-root */
            esp_mesh_tcp_client_stop();
        }
#endif /* MESH_P2P_FORWARD_TEST */
        break;

    case MESH_EVENT_ROOT_GOT_IP:
        /* root starts to connect to server */
        MESH_LOGI("MESH_EVENT_ROOT_GOT_IP")
        ;
#ifndef MESH_P2P_FORWARD_TEST
        if (esp_mesh_is_root()) {
            esp_mesh_tcp_client_start(MESH_SERVER_HOSTNAME,
                                      strlen(MESH_SERVER_HOSTNAME), MESH_SERVER_PORT);
        }
#endif /* MESH_P2P_FORWARD_TEST */
        break;

    case MESH_EVENT_VOTE_START:
        vote_times++;
        is_voting = true;
        MESH_LOGI("<MESH_EVENT_VOTE_START> vote_times:%d", vote_times)
        ;
        break;

    case MESH_EVENT_VOTE_DONE:
        MESH_LOGI("<MESH_EVENT_VOTE_DONE> vote_times:%d", vote_times)
        ;
        is_voting = false;
        break;

    case MESH_EVENT_ROOT_SWITCH_REQ:
        MESH_LOGI("<MESH_EVENT_ROOT_SWITCH_REQ>")
        ;
        break;

    case MESH_EVENT_ROOT_SWITCH_ACK:
        MESH_LOGI("<MESH_EVENT_ROOT_SWITCH_ACK>")
        ;
        break;

    case MESH_EVENT_TODS_REACHABLE:
        MESH_LOGI("MESH_EVENT_TODS_REACHABLE")
        ;
        mesh_toDS_reachable = 1;
        break;

    case MESH_EVENT_TODS_UNREACHABLE:
        MESH_LOGI("MESH_EVENT_TODS_UNREACHABLE")
        ;
        mesh_toDS_reachable = 0;
        break;

    case MESH_EVENT_FAIL:
        MESH_LOGI("MESH_EVENT_FAIL")
        ;
        break;

    default:
        MESH_LOGI("unknown mesh event")
        ;
        break;
    }
}

#ifdef MESH_PRE_SCAN
bool is_router_found = false;
esp_err_t esp_mesh_scan_done_handler(void)
{
    char ssid[33];
    uint16_t num = 0;
    uint8_t i;
    wifi_ap_record_t *record;
    wifi_ap_record_t *ap;

    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&num));
    record = (wifi_ap_record_t *) malloc(num * sizeof(wifi_ap_record_t));
    if (num && !record) {
        return ESP_FAIL;
    }

    if (esp_wifi_scan_get_ap_records(&num,
                                     (wifi_ap_record_t *) record) == ESP_OK) {
        for (i = 0; i < num; i++) {
            ap = &(record[i]);
            ssid[32] = '\0';
            memcpy(ssid, ap->ssid, sizeof(ssid) - 1);
            if (!memcmp(MESH_ROUTER_SSID, ap->ssid, strlen(ssid))) {
                is_router_found = true;
            }
            printf("[%d]%s,"MACSTR",%u,%u,%d,%d,%u\n", i, ssid,
                   MAC2STR(ap->bssid), ap->authmode, ap->primary, ap->rssi, 0,
                   ap->second);
        }
    }

    free(record);
    if (!is_router_found) {
        ESP_ERROR_CHECK(esp_wifi_scan_start(NULL, 0));
    }
    return ESP_OK;
}

static esp_err_t esp_event_handler(void *ctx, system_event_t *event)
{
    MESH_LOGE("esp_event_handler:%d", event->event_id);

    switch ((int) event->event_id) {
    case SYSTEM_EVENT_STA_START:
        ESP_ERROR_CHECK(esp_wifi_scan_start(NULL, 0))
        ;
        break;

    case SYSTEM_EVENT_SCAN_DONE:
        if (event->event_info.scan_done.status == ESP_OK) {
            ESP_ERROR_CHECK(esp_mesh_scan_done_handler());
        }
        break;
    }

    return ESP_OK;
}
#else /* MESH_PRE_SCAN */
static esp_err_t esp_event_handler(void *ctx, system_event_t *event)
{
    MESH_LOGE("esp_event_handler:%d", event->event_id);
    if (event->event_id == SYSTEM_EVENT_STA_GOT_IP) {
        MESH_LOGE("SYSTEM_EVENT_STA_GOT_IP");
#ifndef MESH_P2P_FORWARD_TEST
        if (esp_mesh_is_root()) {
            esp_mesh_tcp_client_start(MESH_SERVER_HOSTNAME,
                                      strlen(MESH_SERVER_HOSTNAME), MESH_SERVER_PORT);
        }
#endif /* MESH_P2P_FORWARD_TEST */
    } else if (event->event_id == SYSTEM_EVENT_MESH_TODS_STATE) {
        mesh_toDS_reachable = 1;
    } else if (event->event_id == SYSTEM_EVENT_MESH_WEAK_RSSI) {
        MESH_LOGE("SYSTEM_EVENT_MESH_WEAK_RSSI");
    } else if (event->event_id == SYSTEM_EVENT_MESH_STOP_VOTE) {
        MESH_LOGE("SYSTEM_EVENT_MESH_STOP_VOTE");
    }
    return ESP_OK;
}
#endif /* MESH_PRE_SCAN */

esp_err_t print_routing_table(void)
{
    int i;
    int num = 0;
    int len;
    mesh_addr_t *addr;
    int size = esp_mesh_get_routing_table_size();
    if (!size) {
        return ESP_OK;
    }
    len = size * sizeof(mesh_addr_t);
    addr = (mesh_addr_t *) malloc(len);
    if (addr) {
        esp_mesh_get_routing_table(addr, len, &num);
        ets_printf("routing table[%d/%d][total:%d]\n", size, num,
                   esp_mesh_get_total_node_num());
        for (i = 0; i < size; i++) {
            ets_printf("[%2d]"MACSTR"  ", i,
                       MAC2STR(((mesh_addr_t * )addr + i)->addr));
            if (!(i % 5)) {
                ets_printf("\n");
            }
        }
        ets_printf("\n");
        free(addr);
    }

    return ESP_OK;
}

void print_timer_dump(void *arg)
{
    int i = 0;
    extern void heap_trace_dump(void);
    while (1) {
        i++;
        MESH_LOGI("[%d][%ds]", i, i * 15);
        vTaskDelay(5 * 1000 / portTICK_RATE_MS);
        esp_timer_dump(stdout);
        continue;

//      heap_trace_dump();
        if (esp_mesh_is_root() && !is_voting
                && esp_mesh_get_routing_table_size() >= 30) {
            MESH_LOGW("root waives itself");
            is_voting = true;
            mesh_vote_t vote = { .attempts = 15, };
            ESP_ERROR_CHECK(esp_mesh_waive_root(&vote, 0));
        }
        vTaskDelay(15 * 1000 / portTICK_RATE_MS);

    }

}

void app_main(void)
{
    mesh_cfg_t *config;
    ESP_ERROR_CHECK(mesh_light_init());
    ESP_ERROR_CHECK(nvs_flash_init());
    tcpip_adapter_init();
#if 0
    ESP_ERROR_CHECK(tcpip_adapter_dhcps_stop(TCPIP_ADAPTER_IF_AP));
#else
    ESP_ERROR_CHECK(tcpip_adapter_dhcpc_stop(TCPIP_ADAPTER_IF_STA));
    ESP_ERROR_CHECK(tcpip_adapter_dhcps_stop(TCPIP_ADAPTER_IF_AP));
    tcpip_adapter_ip_info_t sta_ip;
    sta_ip.ip.addr = ipaddr_addr("192.168.1.102");
    sta_ip.gw.addr = ipaddr_addr("192.168.1.1");
    sta_ip.netmask.addr = ipaddr_addr("255.255.255.0");
    tcpip_adapter_set_ip_info(WIFI_IF_STA, &sta_ip);

#endif
    ESP_ERROR_CHECK(esp_event_loop_init(esp_event_handler, NULL));
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT()
                             ;
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_FLASH));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_ERROR_CHECK(
        esp_wifi_get_mac(ESP_IF_WIFI_STA, (uint8_t * )&mesh_sta_addr));

#ifdef MESH_PRE_SCAN
    while (!is_router_found) {
        ;
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
#endif /* MESH_PRE_SCAN */

#if 0
    nvs_handle handle;
    nvs_open("MESH", NVS_READWRITE, &handle);
    nvs_erase_all(handle);
    nvs_close(handle);
#endif
    ESP_ERROR_CHECK(esp_mesh_init());
    ESP_ERROR_CHECK(esp_mesh_set_max_layer(MESH_MAX_LAYER));
    ESP_ERROR_CHECK(esp_mesh_set_map_authmode(MESH_MAP_AUTHMODE));
    ESP_ERROR_CHECK(esp_mesh_set_vote_percentage(0.6));
    ESP_ERROR_CHECK(esp_mesh_set_rssi_threshold(-20));
    ESP_ERROR_CHECK(esp_mesh_set_map_assoc_expire(10));
    mesh_attempts_t attempts = { .scan = 10, .vote = 1000, .fail = 20,
                                 .monitor_ie = 3
                               };
    ESP_ERROR_CHECK(esp_mesh_set_attempts(&attempts));
    /* parent switch */
    mesh_switch_parent_t paras;
    ESP_ERROR_CHECK(esp_mesh_get_switch_parent_paras(&paras));
    MESH_LOGI(
        "[default]duration:%dms, cnx_rssi:%d, select_rssi:%d, switch_rssi:%d, backoff_rssi:%d",

        paras.duration_ms, paras.cnx_rssi, paras.select_rssi,

        paras.switch_rssi, paras.backoff_rssi);

    paras.cnx_rssi = -70;
    paras.switch_rssi = -70;
    paras.select_rssi = -40;
    ESP_ERROR_CHECK(esp_mesh_set_switch_parent_paras(&paras));
    MESH_LOGI(
        "[config]duration:%dms, cnx_rssi:%d, select_rssi:%d, switch_rssi:%d, backoff_rssi:%d",

        paras.duration_ms, paras.cnx_rssi, paras.select_rssi,

        paras.switch_rssi, paras.backoff_rssi);
    int qsize = 72;
    ESP_ERROR_CHECK(esp_mesh_set_xon_qsize(qsize));
    MESH_LOGI("Q:%d", esp_mesh_get_xon_qsize());

#ifdef MESH_DISABLE_SELF_ORGANIZED
#if 1

    ESP_ERROR_CHECK(esp_mesh_set_self_organized(false));
    wifi_config_t parent = {
        .sta = {
            .ssid = MESH_PARENT_SSID,
            .password = MESH_PARENT_PASSWD,
            .channel = MESH_PARENT_CHANNEL,
        },
    };
    ESP_ERROR_CHECK(esp_mesh_set_parent(&parent, NULL));
#else
    wifi_config_t router = {
        .sta = {
            .ssid = MESH_ROUTER_SSID,
            .password = MESH_ROUTER_PASSWD,
            .channel = MESH_ROUTER_CHANNEL,
        },
    };
    ESP_ERROR_CHECK(esp_mesh_set_parent(&router, NULL));
#endif
#endif /* MESH_DISABLE_SELF_ORGANIZED */

    config = (mesh_cfg_t *) malloc(sizeof(mesh_cfg_t));
    if (config) {
        memset(config, 0, sizeof(mesh_cfg_t));
        /* mesh ID */
        memcpy((uint8_t *) &config->mesh_id, MESH_ID, 6);
        /* mesh event callback */
        config->event_cb = &esp_mesh_event_cb;
#ifdef MESH_ASSOC_ENCRYPT_ON
        /* crypto */
        mesh_crypto_config_t crypto;
        crypto.crypto_funcs = &g_wifi_default_mesh_crypto_funcs;
        config->crypto = &crypto;
#endif /* MESH_ASSOC_ENCRYPT_ON */
        /* router */
        config->router.channel = MESH_ROUTER_CHANNEL;
        config->router.ssid_len = strlen(MESH_ROUTER_SSID);
        memcpy((uint8_t *) &config->router.ssid, MESH_ROUTER_SSID,
               config->router.ssid_len);
        memcpy((uint8_t *) &config->router.bssid, MESH_ROUTER_BSSID, 6);
        memcpy((uint8_t *) &config->router.password, MESH_ROUTER_PASSWD,
               strlen(MESH_ROUTER_PASSWD));
        /* map */
        config->map.max_connection = MESH_MAP_CONNECTIONS;
        memcpy((uint8_t *) &config->map.password, MESH_MAP_PASSWD,
               strlen(MESH_MAP_PASSWD));

        ESP_ERROR_CHECK(esp_mesh_set_config(config));
        free(config);
        ESP_ERROR_CHECK(esp_mesh_start());
    }
    MESH_LOGI("mesh success\n");

//  xTaskCreate(print_timer_dump, "MSTX", 3072, NULL, 24, NULL);
}

void print_sta_list(const char *func)
{
#ifdef MESH_XON_QSIZE_DBG
    typedef struct {
        uint8_t qnum;
        uint32_t xseqno_in;
    } upQ_t;

    int j;
    wifi_sta_list_t sta;
    upQ_t upQ[MESH_MAP_CONNECTIONS + 1];

    upQ[0].qnum = esp_mesh_available_txupQ_num(&mesh_sta_addr,
                  &upQ[0].xseqno_in);
    ets_printf("#%s[L:%d]"MACSTR"[available:%2d,xseqno_in:%u]\n", func,
               esp_mesh_get_layer(), MAC2STR(mesh_sta_addr.addr), upQ[0].qnum,
               upQ[0].xseqno_in);
    esp_wifi_ap_get_sta_list(&sta);
    for (j = 0; j < sta.num; j++) {
        upQ[j + 1].qnum = esp_mesh_available_txupQ_num(
                              (mesh_addr_t *) &sta.sta[j].mac, &upQ[j + 1].xseqno_in);
        ets_printf("#%s[L:%d]"MACSTR"[available:%2d,xseqno_in:%u]\n", func,
                   esp_mesh_get_layer() + 1, MAC2STR(sta.sta[j].mac),
                   upQ[j + 1].qnum, upQ[j + 1].xseqno_in);

    }
    esp_mesh_print_txQ_waiting();
    esp_mesh_print_rxQ_waiting();
#endif /* MESH_XON_QSIZE_DBG */
}

void esp_mesh_p2p_tx_main(void *arg)
{
    esp_err_t err;
    mesh_opt_t *opt = NULL;
    mesh_addr_t to;
    mesh_addr_t parent;
    uint32_t send_count = 0;

#ifdef MESH_P2P_FORWARD_MCAST
    static uint8_t tx_buf[TX_MCAST_SIZE] = {0,};
#elif defined(MESH_ROOT_SEND_MCAST)
    static uint8_t tx_buf[TX_SIZE - MESH_ROUTE_TABLE_NUM * 6] = {0,};
#else /* MESH_P2P_FORWARD_MCAST */
    static uint8_t tx_buf[TX_SIZE] = { 0, };
#endif /* MESH_P2P_FORWARD_MCAST */

#if defined (MESH_ROOT_SEND_UCAST) || defined (MESH_ROOT_SEND_MCAST)
    mesh_addr_t route_table[MESH_ROUTE_TABLE_NUM];
    int route_table_size = 0;
#endif /* MESH_ROOT_SEND_UCAST */

    mesh_data_t data;
    data.data = tx_buf;
    data.size = sizeof(tx_buf);
    data.proto = MESH_PROTO_BIN;
#ifdef MESH_P2P_TOS_OFF
    data.tos = MESH_TOS_DEF;
#endif /* MESH_P2P_TOS_OFF */

    /*
     * unicast
     * broadcast
     * multicast + option
     */
#ifdef MESH_P2P_FORWARD_UCAST
    memcpy((uint8_t *) &to.addr, MESH_P2P_FORWARD_UADDR, sizeof(mesh_addr_t));
#elif defined MESH_P2P_FORWARD_BCAST
    memcpy((uint8_t *) &to.addr, MESH_P2P_FORWARD_BADDR, sizeof(mesh_addr_t));
#elif defined MESH_P2P_FORWARD_MCAST
    mesh_opt_t option;
    /* option */
    option.type = MESH_OPT_MCAST_GROUP;
    option.len = sizeof(MESH_P2P_FORWARD_MADDR_NODE);
    option.val = (uint8_t *) MESH_P2P_FORWARD_MADDR_NODE;
    opt = &option;
    memcpy((uint8_t *) &to.addr, MESH_P2P_FORWARD_MADDR, sizeof(mesh_addr_t));
#endif

    esp_mesh_get_parent_bssid(&parent);
    MESH_LOGW("%s", __func__);
    is_running = true;
    while (is_running) {

#ifdef MESH_XON_TO_ROOT
        if (!is_mesh_connected || !esp_mesh_is_root() || is_voting) {
            send_count++;
            tx_buf[25] = (send_count >> 24) & 0xff;
            tx_buf[24] = (send_count >> 16) & 0xff;
            tx_buf[23] = (send_count >> 8) & 0xff;
            tx_buf[22] = (send_count) & 0xff;
            print_sta_list(NULL);
            err = esp_mesh_send(NULL, &data, 0, NULL, 0);
            MESH_LOGI("[TX:%d][layer:%d]%s%s%s[rtableSize:%d], err:%d",
                      send_count, esp_mesh_get_layer(),
                      is_mesh_connected ? "CONNECT" : "DISCONNECT",
                      esp_mesh_is_root() ? "[ROOT]" : "[NON-ROOT]",
                      is_voting ? "[VOTING]" : "NOT-VOTING",
                      esp_mesh_get_routing_table_size(), err);
            vTaskDelay(5000 / portTICK_RATE_MS);
            continue;
        }
#endif

#if defined (MESH_ROOT_SEND_UCAST) || defined (MESH_ROOT_SEND_MCAST)
        if (!is_mesh_connected || !esp_mesh_is_root() || is_voting) {
            MESH_LOGI("[layer:%d]%s%s%s[rtableSize:%d]", esp_mesh_get_layer(),
                      is_mesh_connected ? "CONNECT" : "DISCONNECT",
                      esp_mesh_is_root() ? "[ROOT]" : "[NON-ROOT]",
                      is_voting ? "[VOTING]" : "NOT-VOTING",
                      esp_mesh_get_routing_table_size());
            esp_mesh_print_txQ_waiting();
            esp_mesh_print_rxQ_waiting();
            vTaskDelay(5000 / portTICK_RATE_MS);
            continue;
        }
        esp_mesh_get_routing_table((mesh_addr_t *) &route_table,
                                   MESH_ROUTE_TABLE_NUM * 6, &route_table_size);
        if (!(send_count % 100)) {
            ets_printf("size:%d/%d,send_count:%d\n", route_table_size,
                       esp_mesh_get_routing_table_size(), send_count);
        }

        send_count++;
        tx_buf[25] = (send_count >> 24) & 0xff;
        tx_buf[24] = (send_count >> 16) & 0xff;
        tx_buf[23] = (send_count >> 8) & 0xff;
        tx_buf[22] = (send_count) & 0xff;
        if (send_count % 2) {
            memcpy(tx_buf, MESH_BCF_LIGHT_ON, sizeof(MESH_BCF_LIGHT_ON));
        } else {
            memcpy(tx_buf, MESH_BCF_LIGHT_OFF, sizeof(MESH_BCF_LIGHT_OFF));
        }

#ifdef MESH_ROOT_SEND_MCAST
        mesh_opt_t option;
        /* option */
        option.type = MESH_OPT_MCAST_GROUP;
        option.len = route_table_size * 6;
        option.val = (uint8_t *) route_table;
        opt = &option;
        memcpy((uint8_t *) &to.addr, MESH_P2P_FORWARD_MADDR,
               sizeof(mesh_addr_t));
        err = esp_mesh_send(&to, &data, MESH_DATA_P2P, opt, opt ? 1 : 0);
        if (err) {
            MESH_LOGE(
                "[#TX:%d][L:%d]parent:"MACSTR" to "MACSTR", heap:%d[err:%d], [%d,%d]",
                send_count, esp_mesh_get_layer(), MAC2STR(parent.addr),
                MAC2STR(to.addr), esp_get_free_heap_size(), err, data.proto,
                data.tos);
            if (err == MESH_ERR_MEM) {
                vTaskDelay(1000 / portTICK_RATE_MS);
            }
        } else {
            MESH_LOGW(
                "[#TX:%d][L:%d]parent:"MACSTR" to "MACSTR", heap:%d[err:%d], [%d,%d]",
                send_count, esp_mesh_get_layer(), MAC2STR(parent.addr),
                MAC2STR(to.addr), esp_get_free_heap_size(), err, data.proto,
                data.tos);
        }

        vTaskDelay(1000 / portTICK_RATE_MS);
#else  /*MESH_ROOT_SEND_MCAST */
        int i;
        for (i = 0; i < route_table_size; i++) {
            err = esp_mesh_send(&route_table[i], &data, MESH_DATA_P2P, opt,
                                opt ? 1 : 0);

            if (err) {
                MESH_LOGE(
                    "[#TX:%d][L:%d]parent:"MACSTR" to "MACSTR", heap:%d[err:%d], [%d,%d]",
                    send_count, esp_mesh_get_layer(), MAC2STR(parent.addr),
                    MAC2STR(route_table[i].addr), esp_get_free_heap_size(),
                    err, data.proto, data.tos);
            } else {
                if (!(send_count % 10)) {
                    MESH_LOGW(
                        "[#TX:%d][L:%d][rtableSize:%d]parent:"MACSTR" to "MACSTR", heap:%d[err:%d], [%d,%d]",
                        send_count, esp_mesh_get_layer(),
                        esp_mesh_get_routing_table_size(),
                        MAC2STR(parent.addr), MAC2STR(route_table[i].addr),
                        esp_get_free_heap_size(), err, data.proto, data.tos);
                }
            }
        }
#endif /* MESH_ROOT_SEND_MCAST */

#else /* MESH_ROOT_SEND_UCAST || MESH_ROOT_SEND_MCAST */
        esp_mesh_send(&to, &data, MESH_DATA_P2P, opt, opt ? 1 : 0);
#endif /* MESH_ROOT_SEND_UCAST || MESH_ROOT_SEND_MCAST */

#ifdef MESH_ROOT_WAIVE_ITSELF
        if (esp_mesh_is_root() && !is_voting && send_count
                && !(send_count % 100)
                && esp_mesh_get_routing_table_size() >= 40) {
            MESH_LOGW("root waives itself");
            is_voting = true;
            mesh_vote_t vote = { .attempts = 15, };
            ESP_ERROR_CHECK(esp_mesh_waive_root(&vote, 0));
        }
#endif /* MESH_ROOT_WAIVE_ITSELF */
    }

    vTaskDelete(NULL);
}

void esp_mesh_p2p_rx_main(void *arg)
{
    int i, j = 0, k = -1;
    int recv_count = 0;
    esp_err_t err;
    mesh_addr_t from;
    mesh_addr_t parent;
    int send_count = 0;
    mesh_data_t data;
    struct timeval cur_time;
    int flag = 0;
    data.size = RX_SIZE;
    data.data = (uint8_t *) malloc(RX_SIZE);
    if (!data.data) {
        ets_printf("rx start fails\n");
        vTaskDelete(NULL);
    }
    mesh_timeval_t mesh_recv;
    /* forwarding trace */
    typedef struct {
        bool set;
        mesh_addr_t mdev;
        int recv_count;
        int send_count;
        time_t recv_time;
    } mesh_forward_t;

    mesh_forward_t mforward[MESH_P2P_FORWARD_MAX_NUM];
    memset(mforward, 0, sizeof(mesh_forward_t) * MESH_P2P_FORWARD_MAX_NUM);

    uint8_t map_mac[6];
    esp_wifi_get_mac(ESP_IF_WIFI_AP, map_mac);

    is_running = true;
    while (is_running) {
        esp_mesh_get_parent_bssid(&parent);

        memset(data.data, 0, RX_SIZE);
        data.size = RX_SIZE;
        data.proto = MESH_PROTO_BIN;
        gettimeofday(&mesh_recv.start, NULL);
        err = esp_mesh_recv(&from, &data, portMAX_DELAY, &flag, NULL, 0);
        gettimeofday(&mesh_recv.stop, NULL);
        if (err != ESP_OK || !data.size) {
            MESH_LOGE("err:%d/0x%x, size:%d", err, err, data.size);
            continue;
        }
        /* compute time taken */
        timersub(&mesh_recv.stop, &mesh_recv.start, &mesh_recv.taken);
        mesh_recv.ms = (uint32_t) (mesh_recv.taken.tv_sec * 1000
                                   + mesh_recv.taken.tv_usec / 1000);
        /* extract send count */
        if (data.size > sizeof(send_count)) {
            send_count = (data.data[25] << 24) | (data.data[24] << 16)
                         | (data.data[23] << 8) | data.data[22];
        }
        recv_count++;
        /* process bfc control */
        mesh_process_received_data(&from, data.data, data.size);
        MESH_LOGW(
            "[#RX:%d][L:%d]self:"MACSTR", parent:"MACSTR", receive from "MACSTR", size:%d, heap:%d, flag:%d[err:%d], [%d,%d]\n",
            recv_count, esp_mesh_get_layer(), MAC2STR(mesh_sta_addr.addr),
            MAC2STR(parent.addr), MAC2STR(from.addr), data.size,
            esp_get_free_heap_size(), flag, err, data.proto, data.tos);

        continue;

#ifdef MESH_P2P_FORWARD_UCAST

        MESH_LOGI(
            "[#RX:%d][%u]ms, self:"MACSTR", receive from "MACSTR", size:%d, heap:%d, [err:%d]",
            send_count, mesh_recv.ms, MAC2STR(mesh_sta_addr.addr), MAC2STR(from.addr),
            data.size, esp_get_free_heap_size(), err);

        if (!memcmp(MESH_P2P_FORWARD_UADDR, sta_mac, sizeof(sta_mac))
                || !memcmp(MESH_P2P_FORWARD_UADDR, map_mac, sizeof(map_mac))) {
            data.tos = 0;
            err = esp_mesh_send(&from, &data, MESH_DATA_P2P, NULL, 0);

            if (err) {
                MESH_LOGE(
                    "[#TX:%d][L:%d]parent:"MACSTR" to "MACSTR", heap:%d[err:%d], [%d,%d], Q[self:%d, to:%d]\n",
                    send_count, esp_mesh_get_layer(), MAC2STR(parent.addr),
                    MAC2STR(from.addr), esp_get_free_heap_size(), err,
                    data.proto, data.tos,
                    esp_mesh_available_txupQ_num(&mesh_sta_addr, NULL),
                    esp_mesh_available_txupQ_num(&from, NULL));
            }
#if 0
            else {

                MESH_LOGW(
                    "[#TX:%d][L:%d]parent:"MACSTR" to "MACSTR", heap:%d[err:%d], [%d,%d], Q[self:%d, to:%d]\n",
                    send_count, esp_mesh_get_layer(), MAC2STR(parent.addr),
                    MAC2STR(from.addr), esp_get_free_heap_size(), err,
                    data.proto, data.tos,
                    esp_mesh_available_txupQ_num(&mesh_sta_addr, NULL),
                    esp_mesh_available_txupQ_num(&from, NULL));
            }
#endif
        } else {
            MESH_LOGI(
                "[#RX:%d][%u]ms, self:"MACSTR", receive from "MACSTR", size:%d, heap:%d, [err:%d]",
                send_count, mesh_recv.ms, MAC2STR(mesh_sta_addr.addr),
                MAC2STR(from.addr), data.size, esp_get_free_heap_size(),
                err);
        }

        continue;
#endif /* MESH_P2P_FORWARD_UCAST */

        for (i = k + 1; i < MESH_P2P_FORWARD_MAX_NUM; i++) {
            if (!mforward[i].set) {

                for (j = 0; j < i; j++) {
                    if (!memcmp(&mforward[j].mdev, &from,
                                sizeof(mesh_addr_t))) {
                        break;
                    }
                }
                if (j >= i) {
                    memcpy((uint8_t *) &mforward[i].mdev, (uint8_t *) &from,
                           sizeof(mesh_addr_t));
                    mforward[i].set = true;
                    k = i;
                }
                break;
            }
        }

        for (i = 0; i < MESH_P2P_FORWARD_MAX_NUM; i++) {
            if (mforward[i].set) {
                if (!memcmp(&mforward[i].mdev, &from, sizeof(mesh_addr_t))) {
                    mforward[i].recv_count++;
                    mforward[i].send_count = send_count;
                    if (mforward[i].send_count < mforward[i].recv_count) {
                        mforward[i].recv_count = 0;
                    }
                    esp_mesh_get_parent_bssid(&parent);
                    MESH_LOGI(
                        "[#RX:%d][L:%d]self:"MACSTR", parent:"MACSTR", [%u]s receive from [#%d]"MACSTR", size:%d, heap:%d, recv/send/lost:[%d/%d/%d], flag:%d[err:%d], [%d,%d]\n",
                        mforward[i].send_count, esp_mesh_get_layer(),
                        MAC2STR(mesh_sta_addr.addr), MAC2STR(parent.addr),
                        (int )(cur_time.tv_sec - mforward[i].recv_time), i,
                        MAC2STR(from.addr), data.size,
                        esp_get_free_heap_size(), mforward[i].recv_count,
                        mforward[i].send_count,
                        mforward[i].send_count - mforward[i].recv_count,
                        flag, err, data.proto, data.tos);

                    mforward[i].recv_time = cur_time.tv_sec;
                    break;
                }
            }
        }
    }

    if (data.data) {
        free(data.data);
    }
    vTaskDelete(NULL);
}

void esp_mesh_comm_tx_main(void *arg)
{
    esp_err_t err;
    mesh_addr_t to;
    mesh_addr_t parent;
    uint32_t xseqno_in = 0;
    struct timeval time_start;
    struct timeval time_stop;
    struct timeval time_taken;
    int send_count = 0;
    int fail_count = 0;
    mesh_data_t data;
    memset(&data, 0, sizeof(mesh_data_t));
#define PING_SIZE (26)
    data.data = (uint8_t *) malloc(TX_SIZE);
    if (!data.data) {
        ets_printf("tx start fails\n");
        vTaskDelete(NULL);
    }
    memset(data.data, 0, TX_SIZE);
    memcpy((uint8_t *) &to.addr, MESH_SERVER_IP, sizeof(MESH_SERVER_IP));
    to.addr[5] = MESH_SERVER_PORT & 0xff;
    to.addr[4] = (MESH_SERVER_PORT >> 8) & 0xff;
    /* pack data.data */
    data.data[0] = BFC_SEND | BFC_CMD_PING;
    data.data[1] = BFC_VALUE_TOKEN;
    data.data[2] = 0xbf;
    data.data[3] = 0xc0;
    data.data[4] = BFC_VALUE_BSSID;
    esp_wifi_get_mac(ESP_IF_WIFI_STA, &data.data[5]);
    data.data[11] = BFC_VALUE_P_BSSID;
    esp_mesh_get_parent_bssid((mesh_addr_t *) &data.data[12]);
    data.data[17] -= 1;
    data.data[18] = BFC_VALUE_BRIGHTNESS;
    mesh_gpio_get((int *) &data.data[19]);
    data.data[20] = BFC_VALUE_RSSI;
    esp_wifi_get_rssi((int *) &data.data[21]);
    data.data[21] = 0 - data.data[21];

    data.size = TX_SIZE;
    data.proto = MESH_PROTO_BIN;
#ifdef MESH_P2P_TOS_OFF
    data.tos = MESH_TOS_DEF;
#endif /* MESH_P2P_TOS_OFF */
    MESH_LOGW();
    is_running = true;
    memset(data.data, 0, TX_SIZE);
    while (is_running) {

        while (is_running && !esp_mesh_is_toDS_reachable()) {
            /*
             * wait for DS reachable
             */
            vTaskDelay(100 / portTICK_RATE_MS);
        }

        send_count++;
        esp_mesh_get_parent_bssid(&parent);
        data.data[25] = (send_count >> 24) & 0xff;
        data.data[24] = (send_count >> 16) & 0xff;
        data.data[23] = (send_count >> 8) & 0xff;
        data.data[22] = (send_count) & 0xff;
#ifdef MESH_DUMP
        {
            int i = 0;
            ets_printf("Ping to server[%d]\n", data.size);
            for (i = 0; i < data.size; i++) {
                ets_printf("%x ", data.data[i]);
            }
            ets_printf("\n");
        }
#endif /* MESH_DUMP */

        gettimeofday(&time_start, NULL);
        err = esp_mesh_send(&to, &data, MESH_DATA_TODS, NULL, 0);
        gettimeofday(&time_stop, NULL);
        /* compute time taken */
        timersub(&time_stop, &time_start, &time_taken);
        if (!(send_count % 10)) {
            if (err) {
                fail_count++;
                MESH_LOGE(
                    "[L:%d][send:%d][%u]ms,"MACSTR", heap:%d,[fail:%d][err:%d][%d,%d][Q:%d][xseqno_in:%d]",
                    esp_mesh_get_layer(), send_count,
                    (uint32_t ) (time_taken.tv_sec * 1000
                                 + time_taken.tv_usec / 1000),
                    MAC2STR(mesh_sta_addr.addr), esp_get_free_heap_size(),
                    fail_count, err, data.proto, data.tos,
                    esp_mesh_available_txupQ_num(&mesh_sta_addr,
                                                 &xseqno_in), xseqno_in);
                print_sta_list(__func__);
                vTaskDelay(1000 / portTICK_RATE_MS);
            } else {
                MESH_LOGW(
                    "[L:%d][send:%d][%u]ms,"MACSTR", parent:"MACSTR" heap:%d,[err:%d][proto:%d,tos:%d][Q:%d][xseqno_in:%d]",
                    esp_mesh_get_layer(), send_count,
                    (uint32_t ) (time_taken.tv_sec * 1000
                                 + time_taken.tv_usec / 1000),
                    MAC2STR(mesh_sta_addr.addr), MAC2STR(parent.addr),
                    esp_get_free_heap_size(), err, data.proto, data.tos,
                    esp_mesh_available_txupQ_num(&mesh_sta_addr,
                                                 &xseqno_in), xseqno_in);
                print_sta_list(__func__);
            }
        }

        vTaskDelay(100 / portTICK_RATE_MS);

#ifdef MESH_ROOT_WAIVE_ITSELF
        if (esp_mesh_is_root() && !is_voting && send_count
                && !(send_count % 3)) {
            MESH_LOGW("root waives itself");
            is_voting = true;
            mesh_vote_t vote = { .attempts = 10, };
            ESP_ERROR_CHECK(esp_mesh_waive_root(&vote, 0));
        }
#endif /* MESH_ROOT_WAIVE_ITSELF */

    }
    vTaskDelete(NULL);
}

void esp_mesh_comm_rx_main(void *arg)
{
    esp_err_t err;
    mesh_addr_t from;
    mesh_data_t data;
    int recv_count = 0;
    struct timeval cur_time;
    time_t old_time = 0;
    int flag = 0;
    data.size = RX_SIZE;
    data.data = (uint8_t *) malloc(RX_SIZE);
    if (!data.data) {
        ets_printf("rx start fails\n");
    }
#ifdef MESH_OPT_RECV_DS
    uint8_t ds_addr[6] = {0,};
    mesh_opt_t optDS;
    optDS.type = MESH_OPT_RECV_DS_ADDR;
    optDS.len = sizeof(mesh_addr_t);
    optDS.val = ds_addr;
#endif /* MESH_OPT_RECV_DS */

    is_running = true;
    while (is_running) {
        if (esp_mesh_is_root() && esp_mesh_is_server_connected() != MESH_SERVER_CONNECTED) {
            vTaskDelay(100 / portTICK_RATE_MS);
            continue;
        }
        /* initialize variables */
        memset(data.data, 0, RX_SIZE);
        data.size = RX_SIZE;
        flag = 0;
#ifdef MESH_OPT_RECV_DS
        err = esp_mesh_recv(&from, &data, portMAX_DELAY, &flag, &optDS, 1);
        {
            int i;
            printf("%s,%d received server address:\n", __func__, __LINE__);
            for (i = 0; i < optDS.len; i++) {
                printf("%x ", optDS.val[i]);
            }
            printf("\n");
        }
#else /* MESH_OPT_RECV_DS */
        err = esp_mesh_recv(&from, &data, portMAX_DELAY, &flag, NULL, 0);
#endif /* MESH_OPT_RECV_DS */
        gettimeofday(&cur_time, NULL);
        if (err != ESP_OK || !data.size) {
            MESH_LOGE("err:%d, size:%d", err, data.size);
            continue;
        }
#ifdef MESH_DUMP
        {
            int i = 0;
            ets_printf("%s,%d receive from "MACSTR"[%d]:", __func__, __LINE__,
                       MAC2STR(from.addr), data.size);
            for (i = 0; i < data.size; i++) {
                ets_printf("%x ", data.data[i]);
            }
            ets_printf("\n");

        }
#endif /* MESH_DUMP */
        recv_count++;
        if (flag & MESH_DATA_TODS) {

        } else if (flag & MESH_DATA_FROMDS) {
#ifdef MESH_REPORT_TOPO
            mesh_process_received_data((mesh_addr_t *) &ds_addr, data.data,
                                       data.size);
#else /* MESH_REPORT_TOPO */
            mesh_process_received_data(&from, data.data, data.size);
#endif /* MESH_REPORT_TOPO */
        }
        if (!(recv_count % 10)) {
            print_sta_list(__func__);
            MESH_LOGI(
                "[%d][%u]s receive from "MACSTR", len:%d, flag:%s%s, heap:%d[err:%d], [%d,%d]",
                recv_count, (int )(cur_time.tv_sec - old_time),
                MAC2STR(from.addr), data.size,
                (flag & MESH_DATA_TODS) ? "toDS" : "",
                (flag & MESH_DATA_FROMDS) ? "fromDS" : "",
                esp_get_free_heap_size(), err, data.proto, data.tos);

            old_time = cur_time.tv_sec;
        }
    }

    if (data.data) {
        free(data.data);
    }
    vTaskDelete(NULL);
}

esp_err_t esp_mesh_comm_p2p_start(void)
{

    static bool is_comm_p2p_started = false;

    if (!is_comm_p2p_started) {
        is_comm_p2p_started = true;
        xTaskCreate(esp_mesh_p2p_tx_main, "MPTX", 3072, NULL, 5, NULL);
        xTaskCreate(esp_mesh_p2p_rx_main, "MPRX", 3072, NULL, 7, NULL);
    }

    return ESP_OK;
}

esp_err_t esp_mesh_comm_server_start(void)
{

    static bool is_comm_server_started = false;

    if (!is_comm_server_started) {
        is_comm_server_started = true;
#ifndef MESH_OPT_RECV_DS
        xTaskCreate(esp_mesh_comm_tx_main, "MSTX", 3072, NULL, 5, NULL);
#endif /* MESH_OPT_RECV_DS */
        xTaskCreate(esp_mesh_comm_rx_main, "MSRX", 3072, NULL, 5, NULL);
    }

    return ESP_OK;
}

esp_err_t esp_mesh_print_settings(void)
{
    mesh_cfg_t mesh_config;
    mesh_router_t mesh_router;
    mesh_addr_t mesh_id;
    mesh_attempts_t attempts;

    ESP_ERROR_CHECK(esp_mesh_get_config(&mesh_config));
    ESP_ERROR_CHECK(esp_mesh_get_router(&mesh_router));
    ESP_ERROR_CHECK(esp_mesh_get_id(&mesh_id));
    ESP_ERROR_CHECK(esp_mesh_get_attempts(&attempts));
    MESH_LOGI("mesh type:%s",
              (esp_mesh_get_type() == MESH_ROOT) ?
              "root" :
              ((esp_mesh_get_type() == MESH_LEAF) ? "leaf" : "node"));
    MESH_LOGI("mesh max layer:%d", esp_mesh_get_max_layer());
    MESH_LOGI("mesh map max connections:%d", esp_mesh_get_map_connections());
    MESH_LOGI("mesh map authmode:%d", esp_mesh_get_map_authmode());
    MESH_LOGI("mesh map vote percentage:%.2f", esp_mesh_get_vote_percentage());
    MESH_LOGI("mesh map attempts scan/vote/fail/monitorIE:%d/%d/%d/%d",
              attempts.scan, attempts.vote, attempts.fail, attempts.monitor_ie);
    MESH_LOGI("mesh map associate expire(seconds):%d",
              esp_mesh_get_map_assoc_expire());
    MESH_LOGI("mesh map rssi threshold:%d", esp_mesh_get_rssi_threshold());

    return ESP_OK;
}
