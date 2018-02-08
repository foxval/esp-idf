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
static uint8_t mesh_toDS_state = 0;
static mesh_addr_t mesh_sta_addr;
static mesh_addr_t mesh_parent_addr;
static int mesh_layer = -1;
static int vote_times = 0;

/*******************************************************
 *                Function Declarations
 *******************************************************/
esp_err_t esp_mesh_comm_p2p_start(void);
esp_err_t esp_mesh_comm_server_start(void);

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
    return mesh_toDS_state;
}

void esp_mesh_connected_indicator(int layer)
{
    if (esp_mesh_is_root()) {
        mesh_gpio_set(RGB_LIGHT_PINK);
        return;
    }
    switch (layer) {
    case 2:
        mesh_gpio_set(RGB_LIGHT_YELLOW);
        break;
    case 3:
        mesh_gpio_set(RGB_LIGHT_RED);
        break;
    case 4:
        mesh_gpio_set(RGB_LIGHT_BLUE);
        break;
    case 5:
        mesh_gpio_set(RGB_LIGHT_GREEN);
        break;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        mesh_gpio_set(RGB_LIGHT_WARNING);
        break;
    default:
        mesh_gpio_set(0);
    }
}

void esp_mesh_disconnected_indicator(void)
{
    mesh_gpio_set(RGB_LIGHT_WARNING);
}

void esp_mesh_event_handler(mesh_event_t event)
{
    static uint8_t last_layer = 0;
    MESH_LOGW("esp_event_handler:%d", event.id);

    switch (event.id) {

    case MESH_EVENT_STARTED:
        MESH_LOGW("<MESH_EVENT_STARTED>")
        ;
        break;

    case MESH_EVENT_STOPPED:
        MESH_LOGW("<MESH_EVENT_STOPPED>")
        ;
        break;
    case MESH_EVENT_CHILD_CONNECTED:
        MESH_LOGW("<MESH_EVENT_CHILD_CONNECTED>aid:%d, "MACSTR"\n",
                  event.info.child_connected.aid,
                  MAC2STR(event.info.child_connected.mac))
        ;
        break;

    case MESH_EVENT_CHILD_DISCONNECTED:
        MESH_LOGW("<MESH_EVENT_CHILD_DISCONNECTED>aid:%d, "MACSTR"\n",
                  event.info.child_disconnected.aid,
                  MAC2STR(event.info.child_disconnected.mac))
        ;
        break;

    case MESH_EVENT_ROUTING_TABLE_ADD:
        MESH_LOGW("<MESH_EVENT_ROUTING_TABLE_ADD>")
        ;
        break;

    case MESH_EVENT_ROUTING_TABLE_REMOVE:
        MESH_LOGW("<MESH_EVENT_ROUTING_TABLE_REMOVE>")
        ;
        break;

    case MESH_EVENT_NO_PARNET_FOUND:
        MESH_LOGW("<MESH_EVENT_NO_PARNET_FOUND>scan times:%d",
                  event.info.no_parent.scan_times)
        ;
        /* TODO handler for the failure */
        break;

    case MESH_EVENT_PARENT_CONNECTED:
        mesh_layer = event.info.connected.self_layer;
        memcpy(&mesh_parent_addr.addr, event.info.connected.connected.bssid, 6);
        MESH_LOGW("<MESH_EVENT_PARENT_CONNECTED>layer:%d-->%d, parent:"MACSTR"%s",
                  last_layer, mesh_layer,
                  MAC2STR(mesh_parent_addr.addr), esp_mesh_is_root() ? "<ROOT>" : (mesh_layer == 2) ? "<layer2>" : "")
        ;
        last_layer = mesh_layer;
        esp_mesh_connected_indicator(mesh_layer);
        is_mesh_connected = true;
        if (esp_mesh_is_root()) {
            is_voting = false;
            esp_mesh_enable_dhcp();
        } else {
            esp_mesh_disable_dhcp();
        }

#ifdef MESH_P2P_FORWARD_TEST
        esp_mesh_comm_p2p_start();
#else /* MESH_P2P_FORWARD_TEST */
        esp_mesh_comm_server_start();
#endif /* MESH_P2P_FORWARD_TEST */
        break;

    case MESH_EVENT_PARENT_DISCONNECTED:
        MESH_LOGW("<MESH_EVENT_PARENT_DISCONNECTED>")
        ;
        is_mesh_connected = false;
        esp_mesh_disconnected_indicator();
#ifndef MESH_P2P_FORWARD_TEST
        esp_mesh_tcp_client_stop();
#endif /* MESH_P2P_FORWARD_TEST */
        break;

    case MESH_EVENT_LAYER_CHANGE:
        mesh_layer = event.info.layer_change.new_layer;
        MESH_LOGW("<MESH_EVENT_LAYER_CHANGE>layer:%d-->%d%s", last_layer, mesh_layer,
                  esp_mesh_is_root() ? "<ROOT>" : (mesh_layer == 2) ? "<layer2>" : "")
        ;
        last_layer = mesh_layer;
        esp_mesh_connected_indicator(mesh_layer);
#ifndef MESH_P2P_FORWARD_TEST
        if (!esp_mesh_is_root()) {
            /* non-root */
            esp_mesh_tcp_client_stop();
        }
#endif /* MESH_P2P_FORWARD_TEST */
        break;

    case MESH_EVENT_ROOT_ADDRESS:
        MESH_LOGW("<MESH_EVENT_ROOT_ADDRESS>rc_addr:"MACSTR"",
                  MAC2STR(event.info.root_addr.addr))
        ;
        break;

    case MESH_EVENT_ROOT_GOT_IP:
        /* root starts to connect to server */
        MESH_LOGW(
            "<MESH_EVENT_ROOT_GOT_IP>sta ip: " IPSTR ", mask: " IPSTR ", gw: " IPSTR,
            IP2STR(&event.info.got_ip.ip_info.ip),
            IP2STR(&event.info.got_ip.ip_info.netmask),
            IP2STR(&event.info.got_ip.ip_info.gw))
        ;
#ifndef MESH_P2P_FORWARD_TEST
        if (esp_mesh_is_root()) {
            esp_mesh_tcp_client_start(MESH_SERVER_HOSTNAME,
                                      strlen(MESH_SERVER_HOSTNAME), MESH_SERVER_PORT);
        }
#endif /* MESH_P2P_FORWARD_TEST */
        break;

    case MESH_EVENT_ROOT_LOST_IP:
        MESH_LOGW("<MESH_EVENT_ROOT_LOST_IP>")
        ;
        break;

    case MESH_EVENT_VOTE_STARTED:
        vote_times++;
        is_voting = true;
        MESH_LOGW(
            "<MESH_EVENT_VOTE_STARTED>[%d]attempts:%d, reason:%d, rc_addr:"MACSTR"",
            vote_times, event.info.vote_started.attempts,
            event.info.vote_started.reason,
            MAC2STR(event.info.vote_started.rc_addr.addr))
        ;
        break;

    case MESH_EVENT_VOTE_STOPPED:
        MESH_LOGW("<MESH_EVENT_VOTE_DONE> vote_times:%d", vote_times)
        ;
        is_voting = false;
        break;

    case MESH_EVENT_ROOT_SWITCH_REQ:
        MESH_LOGW("<MESH_EVENT_ROOT_SWITCH_REQ>reason:%d, rc_addr:"MACSTR"",
                  event.info.switch_req.reason,
                  MAC2STR( event.info.switch_req.rc_addr.addr))
        ;
        break;

    case MESH_EVENT_ROOT_SWITCH_ACK:
        MESH_LOGW("<MESH_EVENT_ROOT_SWITCH_ACK>")
        ;
        break;

    case MESH_EVENT_TODS_STATE:
        MESH_LOGW("<MESH_EVENT_TODS_REACHABLE>state:%d", event.info.toDS_state)
        ;
        mesh_toDS_state = event.info.toDS_state;
        break;

    default:
        MESH_LOGW("unknown")
        ;
        break;
    }
}

void esp_mesh_p2p_tx_main(void *arg)
{
    esp_err_t err;
    mesh_opt_t *opt = NULL;
#if defined (MESH_P2P_FORWARD_UCAST) || defined (MESH_P2P_FORWARD_MCAST) || defined (MESH_P2P_FORWARD_BCAST)
    mesh_addr_t to;
#endif
    uint32_t send_count = 0;
#ifdef MESH_XON_TO_ROOT
    uint32_t to_root_count = 0;
#endif /* MESH_XON_TO_ROOT */

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

    MESH_LOGW("%s", __func__);
    is_running = true;
    while (is_running) {

#ifdef MESH_XON_TO_ROOT
        /* normal devices send to root */
        if (is_mesh_connected && (!esp_mesh_is_root())) {
            to_root_count++;
            tx_buf[25] = (to_root_count >> 24) & 0xff;
            tx_buf[24] = (to_root_count >> 16) & 0xff;
            tx_buf[23] = (to_root_count >> 8) & 0xff;
            tx_buf[22] = (to_root_count >> 0) & 0xff;
            err = esp_mesh_send(NULL, &data, 0, NULL, 0);
            if (err) {
                MESH_LOGE(
                    "[XON-2-ROOT:%d][layer:%d]%s%s%s[rtableSize:%d], err:%d",
                    to_root_count, mesh_layer,
                    is_mesh_connected ? "CONNECT" : "DISCONNECT",
                    esp_mesh_is_root() ? "<ROOT>" : "[NODE]",
                    is_voting ? "[VOTING]" : "NOT-VOTING",
                    esp_mesh_get_routing_table_size(), err);
                vTaskDelay(5000 / portTICK_RATE_MS);
            } else {
                if (!(to_root_count % 100)) {
                    MESH_LOGI(
                        "[XON-2-ROOT:%d][layer:%d]%s%s%s[rtableSize:%d], err:%d",
                        to_root_count, mesh_layer,
                        is_mesh_connected ? "CONNECT" : "DISCONNECT",
                        esp_mesh_is_root() ? "<ROOT>" : "[NODE]",
                        is_voting ? "[VOTING]" : "NOT-VOTING",
                        esp_mesh_get_routing_table_size(), err);
                }

            }
            if (!esp_mesh_is_root()) {
                vTaskDelay(1000 / portTICK_RATE_MS);
                continue;
            }
        }
#endif /* MESH_XON_TO_ROOT */

#if defined (MESH_ROOT_SEND_UCAST) || defined (MESH_ROOT_SEND_MCAST)
        /* root sends to normal devices */
        if (!esp_mesh_is_root() || is_voting) {
            MESH_LOGD("[layer:%d]%s%s%s[rtableSize:%d]", mesh_layer,
                      is_mesh_connected ? "CONNECT" : "DISCONNECT",
                      esp_mesh_is_root() ? "<ROOT>" : "[NODE]",
                      is_voting ? "[VOTING]" : "NOT-VOTING",
                      esp_mesh_get_routing_table_size());

            vTaskDelay(5000 / portTICK_RATE_MS);
            continue;
        }

        esp_mesh_get_routing_table((mesh_addr_t *) &route_table,
                                   MESH_ROUTE_TABLE_NUM * 6, &route_table_size);
        if (send_count && !(send_count % 100)) {
            ets_printf("size:%d/%d,send_count:%d\n", route_table_size,
                       esp_mesh_get_routing_table_size(), send_count);
        }
        send_count++;
        tx_buf[25] = (send_count >> 24) & 0xff;
        tx_buf[24] = (send_count >> 16) & 0xff;
        tx_buf[23] = (send_count >> 8) & 0xff;
        tx_buf[22] = (send_count >> 0) & 0xff;
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
                send_count, mesh_layer, MAC2STR(mesh_parent_addr.addr),
                MAC2STR(to.addr), esp_get_free_heap_size(), err, data.proto,
                data.tos);
            if (err == MESH_ERR_MEM) {
                vTaskDelay(1000 / portTICK_RATE_MS);
            }
        } else {
            MESH_LOGW(
                "[#TX:%d][L:%d]parent:"MACSTR" to "MACSTR", heap:%d[err:%d], [%d,%d]",
                send_count, mesh_layer, MAC2STR(mesh_parent_addr.addr),
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
                    "[ROOT-2-UNICAST:%d][L:%d]parent:"MACSTR" to "MACSTR", heap:%d[err:%d], [%d,%d]",
                    send_count, mesh_layer, MAC2STR(mesh_parent_addr.addr),
                    MAC2STR(route_table[i].addr), esp_get_free_heap_size(),
                    err, data.proto, data.tos);
            } else {
                if (!(send_count % 100)) {
                    MESH_LOGW(
                        "[ROOT-2-UNICAST:%d][L:%d][rtableSize:%d]parent:"MACSTR" to "MACSTR", heap:%d[err:%d], [%d,%d]",
                        send_count, mesh_layer,
                        esp_mesh_get_routing_table_size(),
                        MAC2STR(mesh_parent_addr.addr), MAC2STR(route_table[i].addr),
                        esp_get_free_heap_size(), err, data.proto, data.tos);
                }
            }
        }
#endif /* MESH_ROOT_SEND_MCAST */

#else /* MESH_ROOT_SEND_UCAST || MESH_ROOT_SEND_MCAST */
        esp_mesh_send(&to, &data, MESH_DATA_P2P, opt, opt ? 1 : 0);
#endif /* MESH_ROOT_SEND_UCAST || MESH_ROOT_SEND_MCAST */
    }
    vTaskDelete(NULL);
}

void esp_mesh_p2p_rx_main(void *arg)
{
    int i, j = 0, k = -1;
    int recv_count = 0;
    esp_err_t err;
    mesh_addr_t from;
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
        if (!(recv_count % 100)) {
            MESH_LOGI(
                "[#RX:%d][L:%d]self:"MACSTR", parent:"MACSTR", receive from "MACSTR", size:%d, heap:%d, flag:%d[err:%d], [%d,%d]\n",
                send_count, mesh_layer, MAC2STR(mesh_sta_addr.addr),
                MAC2STR(mesh_parent_addr.addr), MAC2STR(from.addr), data.size,
                esp_get_free_heap_size(), flag, err, data.proto, data.tos);
        }
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
                    send_count, mesh_layer, MAC2STR(mesh_parent_addr.addr),
                    MAC2STR(from.addr), esp_get_free_heap_size(), err,
                    data.proto, data.tos,
                    esp_mesh_available_txupQ_num(&mesh_sta_addr, NULL),
                    esp_mesh_available_txupQ_num(&from, NULL));
            }
#if 0
            else {

                MESH_LOGW(
                    "[#TX:%d][L:%d]parent:"MACSTR" to "MACSTR", heap:%d[err:%d], [%d,%d], Q[self:%d, to:%d]\n",
                    send_count, mesh_layer, MAC2STR(mesh_parent_addr.addr),
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
                    MESH_LOGI(
                        "[#RX:%d][L:%d]self:"MACSTR", parent:"MACSTR", [%u]s receive from [#%d]"MACSTR", size:%d, heap:%d, recv/send/lost:[%d/%d/%d], flag:%d[err:%d], [%d,%d]\n",
                        mforward[i].send_count, mesh_layer,
                        MAC2STR(mesh_sta_addr.addr), MAC2STR(mesh_parent_addr.addr),
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
    data.data[4] = BFC_VALUE_ADDRESS;
    esp_wifi_get_mac(ESP_IF_WIFI_STA, &data.data[5]);
    data.data[11] = BFC_VALUE_PARENT;
    memcpy((mesh_addr_t *) &data.data[12], mesh_parent_addr.addr, 6);
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

        printf("esp_mesh_get_routing_table_size:%d\n\n",
               esp_mesh_get_routing_table_size());
        vTaskDelay(1000 / portTICK_RATE_MS);
        continue;

        while (is_running && !esp_mesh_is_toDS_reachable()) {
            /*
             * wait for DS reachable
             */
            vTaskDelay(100 / portTICK_RATE_MS);
        }

        send_count++;
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
                    mesh_layer, send_count,
                    (uint32_t ) (time_taken.tv_sec * 1000
                                 + time_taken.tv_usec / 1000),
                    MAC2STR(mesh_sta_addr.addr), esp_get_free_heap_size(),
                    fail_count, err, data.proto, data.tos,
                    esp_mesh_available_txupQ_num(&mesh_sta_addr,
                                                 &xseqno_in), xseqno_in);
                vTaskDelay(1000 / portTICK_RATE_MS);
            } else {
                MESH_LOGW(
                    "[L:%d][send:%d][%u]ms,"MACSTR", parent:"MACSTR" heap:%d,[err:%d][proto:%d,tos:%d][Q:%d][xseqno_in:%d]",
                    mesh_layer, send_count,
                    (uint32_t ) (time_taken.tv_sec * 1000
                                 + time_taken.tv_usec / 1000),
                    MAC2STR(mesh_sta_addr.addr), MAC2STR(mesh_parent_addr.addr),
                    esp_get_free_heap_size(), err, data.proto, data.tos,
                    esp_mesh_available_txupQ_num(&mesh_sta_addr,
                                                 &xseqno_in), xseqno_in);
            }
        }
        vTaskDelay(100 / portTICK_RATE_MS);
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
            ;
        } else if (flag & MESH_DATA_FROMDS) {
#ifdef MESH_REPORT_TOPO
            mesh_process_received_data((mesh_addr_t *) &ds_addr, data.data,
                                       data.size);
#else /* MESH_REPORT_TOPO */
            mesh_process_received_data(&from, data.data, data.size);
#endif /* MESH_REPORT_TOPO */
        }

        MESH_LOGI(
            "[%d][%u]s receive from "MACSTR", len:%d, flag:%s%s, heap:%d[err:%d], [%d,%d]",
            recv_count, (int )(cur_time.tv_sec - old_time),
            MAC2STR(from.addr), data.size,
            (flag & MESH_DATA_TODS) ? "toDS" : "",
            (flag & MESH_DATA_FROMDS) ? "fromDS" : "",
            esp_get_free_heap_size(), err, data.proto, data.tos);
        old_time = cur_time.tv_sec;
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

void app_main(void)
{
    mesh_cfg_t *config;
    ESP_ERROR_CHECK(mesh_light_init());
    ESP_ERROR_CHECK(nvs_flash_init());
    /*  tcpip initialization */
    tcpip_adapter_init();
#if 1
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
    /*  wifi initialization */
    ESP_ERROR_CHECK(esp_event_loop_init(NULL, NULL));
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT()
                             ;
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_FLASH));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_ERROR_CHECK(
        esp_wifi_get_mac(ESP_IF_WIFI_STA, (uint8_t * )&mesh_sta_addr));
    /*  mesh initialization */
    ESP_ERROR_CHECK(esp_mesh_init());
    ESP_ERROR_CHECK(esp_mesh_set_max_layer(MESH_MAX_LAYER));
    ESP_ERROR_CHECK(esp_mesh_set_map_authmode(MESH_MAP_AUTHMODE));
    ESP_ERROR_CHECK(esp_mesh_set_vote_percentage(1));
    ESP_ERROR_CHECK(esp_mesh_set_map_assoc_expire(10));
    /* mesh configuration */
    config = (mesh_cfg_t *) malloc(sizeof(mesh_cfg_t));
    if (config) {
        memset(config, 0, sizeof(mesh_cfg_t));
        /* mesh ID */
        memcpy((uint8_t *) &config->mesh_id, MESH_ID, 6);
        /* mesh event callback */
        config->event_cb = &esp_mesh_event_handler;
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
        /* mesh start */
        ESP_ERROR_CHECK(esp_mesh_start());

    }
    MESH_LOGI("mesh start, mheap:%d\n", esp_get_free_heap_size());
}
