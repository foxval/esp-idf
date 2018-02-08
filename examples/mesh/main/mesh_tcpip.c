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
#include "mesh_log.h"
#include "mesh_tcpip.h"
#include "mesh_common.h"
#include "mesh_config.h"
#include "lwip/inet.h"
#include "lwip/netdb.h"

/**
 * Application Instructions
 *   1. Setup a TCP server listening on port MESH_SERVER_PORT.
 *   (see mesh configuration details from ../../examples/mesh/main/include/mesh_config.h)
 *
 *   2. Data format:
 *   _____________________________________________________________________________
 *   | 0           | 1             6|     ...     |          6(n+1)|      ...     |
 *   |----------------------------------------------------------------------------|
 *   |   control   |target address 0|     ...     |target address n|    control   |
 *   |target number|                |             |                |    commands  |
 *   |-----------------------------------------------------------------------------
 *
 *   3. Examples with BFC control protocol
 *      (data from server to turn off the lights)
 *      RPC:
 *      (1)unicast control:
 *      01 aa bb cc 11 22 33 2 00 bf c0 06 00
 *
 *      (2)multicast control:
 *      02 aa bb cc 11 22 33 aa bb cc 44 55 66 2 00 bf c0 06 00
 *
 *      (3)broadcast control:
 *      01 ff ff ff ff ff ff 2 00 bf c0 06 00
 *      GET:
 *      (1)get topology
 *      01 aa bb cc 11 22 33 7 00 bf c0 14
 */

/*******************************************************
 *                Macros
 *******************************************************/

/*******************************************************
 *                Constants
 *******************************************************/
//#define MESH_TCPIP_DUMP
//#define MESH_TCPIP_TOS_P2P
static const char *TAG = "mesh_tcpip";

#define MESH_CNX_STATE_IDLE                (1)
#define MESH_CNX_STATE_CONNECTING          (2)
#define MESH_CNX_STATE_CONNECTED           (3)

/* tcp task */
#define MESH_DEFAULT_TASK_PRI              (7)

#define MESH_TCPIP_RX_TASK_NAME            "MTRX"
#define MESH_TCPIP_RX_TASK_STACK           (1024*3)
#define MESH_TCPIP_RX_TASK_PRI             (MESH_DEFAULT_TASK_PRI)

#define MESH_TCPIP_TX_TASK_NAME            "MTTX"
#define MESH_TCPIP_TX_TASK_STACK           (2048+512)
#define MESH_TCPIP_TX_TASK_PRI             (MESH_DEFAULT_TASK_PRI)

#define TODS_DATA_SIZE (1500)
#define TCP_RECV_SIZE (1024)
#define MIN_RECV_SIZE (13)

/*******************************************************
 *                Variable Definitions
 *******************************************************/
static xTaskHandle mesh_tcpip_tx_task = NULL;
static xTaskHandle mesh_tcpip_rx_task = NULL;
static volatile int tcp_cli_sock = -1;
static uint32_t server_ip = 0;
static uint16_t server_port = 0;
static char server_hostname[128] = { 0, };
static volatile uint8_t mesh_cnx_state = MESH_CNX_STATE_IDLE;
static volatile bool is_running = true;
static volatile bool is_rx_stopped = false;
static bool is_inited = false;

/*******************************************************
 *                Function Declarations
 *******************************************************/
static void mesh_tcpip_tx_main(void *arg);
static void mesh_tcpip_rx_main(void *arg);
static esp_err_t mesh_tcpip_task_init(void);
static esp_err_t mesh_tcpip_connect_server(void);
static esp_err_t mesh_tcpip_disconnect_server(void);

/*******************************************************
 *                Function Definitions
 *******************************************************/
esp_err_t esp_mesh_tcp_client_start(const char *hostname, int hostname_len,
                                    int port)
{
    if (!hostname || !hostname_len || port == -1) {
        return ESP_FAIL;
    }
    if (is_inited) {
        return ESP_OK;
    }

    memset(server_hostname, 0, sizeof(server_hostname));
    memcpy(server_hostname, hostname, hostname_len);
    server_port = port;
    mesh_tcpip_task_init();
    is_inited = true;
    return ESP_OK;
}

esp_err_t esp_mesh_tcp_client_stop(void)
{
    is_running = false;
    is_inited = false;
    return ESP_OK;
}

static void mesh_tcpip_task_deinit(void)
{
    if (mesh_tcpip_tx_task) {
        vTaskDelete(mesh_tcpip_tx_task);
        mesh_tcpip_tx_task = NULL;
    }
    if (mesh_tcpip_rx_task) {
        vTaskDelete(mesh_tcpip_rx_task);
        mesh_tcpip_rx_task = NULL;
    }
}

static esp_err_t mesh_tcpip_task_init(void)
{
    bool is_failed = false;
    if (!mesh_tcpip_tx_task) {
        xTaskCreate(mesh_tcpip_tx_main, MESH_TCPIP_TX_TASK_NAME,
                    MESH_TCPIP_TX_TASK_STACK, NULL, MESH_TCPIP_TX_TASK_PRI,
                    &mesh_tcpip_tx_task);
        if (!mesh_tcpip_tx_task) {
            is_failed = true;
        }
    }
    if (!mesh_tcpip_rx_task) {
        xTaskCreate(mesh_tcpip_rx_main, MESH_TCPIP_RX_TASK_NAME,
                    MESH_TCPIP_RX_TASK_STACK, NULL, MESH_TCPIP_RX_TASK_PRI,
                    &mesh_tcpip_rx_task);
        if (!mesh_tcpip_rx_task) {
            is_failed = true;
        }
    }
    if (is_failed) {
        mesh_tcpip_task_deinit();
        return ESP_FAIL;
    }
    return ESP_OK;
}

static uint32_t str_to_ipv4(const char *arg)
{
    uint32_t address = 0;
    uint8_t num = 0;
    arg--;
    do {
        address = address << 8;
        address += (uint32_t) atoi(++arg);
        while ((*arg != '\x00') && (*arg != '.')) {
            arg++;
        }
        num++;
    } while ((num < 4) && (*arg != '\x00'));
    if (num < 4) {
        return 0;
    }

    return address;
}

esp_err_t esp_mesh_hostname_lookup(const char *hostname, uint32_t *address)
{
    /* Check if address is a string representation of a IPv4 address i.e. xxx.xxx.xxx.xxx */
    if (!hostname || !address) {
        return ESP_FAIL;
    }
    *address = str_to_ipv4(hostname);
    if (*address == 0) {
        struct hostent *hp = gethostbyname(hostname);
        if (hp) {
            struct ip4_addr *ip4_addr = (struct ip4_addr *) hp->h_addr;
            char ipaddr_str[16] = {0};
            sprintf(ipaddr_str, IPSTR, IP2STR(ip4_addr));
            *address = inet_addr(ipaddr_str);
            ets_printf("%s,%d hostname:%s, ip:%s\n", __func__, __LINE__, hostname,
                       ipaddr_str);
        }
    }

    return ESP_OK;
}

static esp_err_t _tcpip_connect_fail(void)
{
    MESH_LOGI("connect server failed\n");
    mesh_cnx_state = MESH_CNX_STATE_IDLE;
    if (tcp_cli_sock != -1) {
        close(tcp_cli_sock);
        tcp_cli_sock = -1;
    }
    return ESP_FAIL;
}

static esp_err_t mesh_tcpip_connect_server(void)
{
    MESH_LOGW("server state:%s\n",
              (mesh_cnx_state == MESH_CNX_STATE_IDLE) ? "idle" : (mesh_cnx_state == MESH_CNX_STATE_CONNECTING) ? "connecting" : (mesh_cnx_state == MESH_CNX_STATE_CONNECTED) ? "connected" : "wrong state");
    int opt = 1;
    int keep_idle = 60;
    int keep_cnt = 3;
    int keep_interval = 5;
    struct sockaddr_in sock_addr;

    if (mesh_cnx_state == MESH_CNX_STATE_CONNECTING) {
        return ESP_OK;
    }

    mesh_cnx_state = MESH_CNX_STATE_CONNECTING;
    if (tcp_cli_sock < 0) {
        tcp_cli_sock = socket(PF_INET, SOCK_STREAM, 0);
        if (tcp_cli_sock < 0) {
            MESH_DEBUG("sock:%d\n", tcp_cli_sock);
            return ESP_FAIL;
        }
    }
    /*
     * enable keep alive option
     */
    if (setsockopt(tcp_cli_sock, SOL_SOCKET, SO_KEEPALIVE,
                   (const char *)&opt, sizeof(opt)) != 0) {
        MESH_DEBUG("set sock err, keepalive\n");
        return _tcpip_connect_fail();
    }
    /*
     * set keep alive option, keep idle time
     */
    if (setsockopt(tcp_cli_sock, IPPROTO_TCP, TCP_KEEPIDLE,
                   (const char *)&keep_idle, sizeof(keep_idle)) != 0) {
        MESH_DEBUG("set sock err, idle\n");
        return _tcpip_connect_fail();
    }
    /*
     * set keep alive option, keep count
     */
    if (setsockopt(tcp_cli_sock, IPPROTO_TCP, TCP_KEEPCNT,
                   (const char *)&keep_cnt, sizeof(keep_cnt)) != 0) {
        MESH_DEBUG("set sock err, cnt\n");
        return _tcpip_connect_fail();
    }
    /*
     * set keep alive option, keep interval time
     */
    if (setsockopt(tcp_cli_sock, IPPROTO_TCP, TCP_KEEPINTVL,
                   (const char *)&keep_interval, sizeof(keep_interval)) != 0) {
        MESH_DEBUG("set sock err, interval\n");
        return _tcpip_connect_fail();
    }
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(server_port);
    esp_mesh_hostname_lookup(server_hostname, &server_ip);
    sock_addr.sin_addr.s_addr = htonl(server_ip);
    server_ip = htonl(server_ip);

    MESH_LOGI("connect server %s, port:%d, socket:%d", server_hostname,
              server_port, tcp_cli_sock);
    if (connect(tcp_cli_sock, (struct sockaddr * )&sock_addr,
                sizeof(sock_addr)) != ESP_OK) {
        MESH_LOGE("failed, server %s, port:%d, errno:%d", server_hostname,
                  server_port, errno);
        ESP_ERROR_CHECK(esp_mesh_post_toDS_state(0));
        return _tcpip_connect_fail();
    } else {
        MESH_LOGI("connect server successfully\n");
        mesh_cnx_state = MESH_CNX_STATE_CONNECTED;
        ESP_ERROR_CHECK(esp_mesh_post_toDS_state(1));
    }

    return ESP_OK;
}

static esp_err_t mesh_tcpip_disconnect_server(void)
{
    mesh_cnx_state = MESH_CNX_STATE_IDLE;
    if (is_rx_stopped && tcp_cli_sock != -1) {
        close(tcp_cli_sock);
        tcp_cli_sock = -1;
    }
    return ESP_OK;
}

int esp_mesh_is_server_connected(void)
{
    if (tcp_cli_sock < 0 || mesh_cnx_state != MESH_CNX_STATE_CONNECTED) {
        return MESH_SERVER_DISCONNECTED;
    } else {
        return MESH_SERVER_CONNECTED;
    }
}

static void mesh_tcpip_tx_main(void *arg)
{
    mesh_timeval_t toDS_recv;
    mesh_timeval_t sock_send;
    fd_set wrset, exset;
    mesh_data_t data;
    mesh_addr_t from, to;
    int flag = 0;
    int send_size = 0;
    uint32_t seqno;
    data.size = TODS_DATA_SIZE;
    data.data = (uint8_t *) malloc(TODS_DATA_SIZE);
    if (!data.data) {
        ets_printf("tcpip tx fails\n");
    }

    is_running = true;

    while (is_running) {

#if 0
        data.size = TODS_DATA_SIZE;
        gettimeofday(&toDS_recv.start, NULL);
        if (esp_mesh_recv_toDS(&from, &to, &data, portMAX_DELAY, &flag,
                               NULL, 0) == ESP_OK && data.size) {
            gettimeofday(&toDS_recv.stop, NULL);
            /* compute time taken */
            timersub(&toDS_recv.stop, &toDS_recv.start, &toDS_recv.taken);
            toDS_recv.ms = (uint32_t) (toDS_recv.taken.tv_sec * 1000
                                       + toDS_recv.taken.tv_usec / 1000);

            MESH_LOGW("[%u]ms from "MACSTR" len:%d, heap:%d", toDS_recv.ms,
                      MAC2STR(from.addr), data.size, esp_get_free_heap_size());

        }
        continue;
#endif

        if (!esp_mesh_is_root()) {
            /* non-root */
            MESH_LOGE("err: not root");
            break;
        }
        if (esp_mesh_is_server_connected() == MESH_SERVER_DISCONNECTED) {
            vTaskDelay(3000 / portTICK_PERIOD_MS);
            continue;
        }

        FD_ZERO(&wrset);
        FD_SET(tcp_cli_sock, &wrset);
        FD_ZERO(&exset);
        FD_SET(tcp_cli_sock, &exset);

        if (select(tcp_cli_sock + 1, NULL, &wrset, &exset, NULL) > 0) {
            if (FD_ISSET(tcp_cli_sock, &exset)) {
                /*
                 * process the socket exception
                 */
                if (tcp_cli_sock != -1) {
                    close(tcp_cli_sock);
                    tcp_cli_sock = -1;
                    mesh_cnx_state = MESH_CNX_STATE_IDLE;
                }
                ESP_ERROR_CHECK(esp_mesh_post_toDS_state(0));
                MESH_DEBUG("tx exception\n");
            } else if (FD_ISSET(tcp_cli_sock, &wrset)) {

SOCK_SEND:
                /* initialize variables */
                data.size = TODS_DATA_SIZE;
                flag = 0;
                gettimeofday(&toDS_recv.start, NULL);
                if (esp_mesh_recv_toDS(&from, &to, &data, portMAX_DELAY, &flag,
                                       NULL, 0) == ESP_OK && data.size) {
                    gettimeofday(&toDS_recv.stop, NULL);

                    if (esp_mesh_is_server_connected() == MESH_SERVER_CONNECTED) {
#ifdef MESH_TCPIP_DUMP
                        {
                            int i = 0;
                            ets_printf(
                                "%s,%d receive from "MACSTR" to "MACSTR"[%d]:", __func__, __LINE__,
                                MAC2STR(from.addr), MAC2STR(to.addr),
                                data.size);
                            for (i = 0; i < data.size; i++) {
                                ets_printf("%x ", data.data[i]);
                            }
                            ets_printf("\n");

                        }
#endif /* MESH_TCPIP_DUMP */
                        gettimeofday(&sock_send.start, NULL);
                        send_size = send(tcp_cli_sock, data.data, data.size, 0);
                        gettimeofday(&sock_send.stop, NULL);

                        if (send_size != data.size) {
                            MESH_LOGW("socekt send:%d, size:%d", send_size,
                                      data.size);
                        } else {
                            timersub(&toDS_recv.stop, &toDS_recv.start,
                                     &toDS_recv.taken);
                            timersub(&sock_send.stop, &sock_send.start,
                                     &sock_send.taken);
                            toDS_recv.ms = (uint32_t) (toDS_recv.taken.tv_sec
                                                       * 1000 + toDS_recv.taken.tv_usec / 1000);
                            sock_send.ms = (uint32_t) (sock_send.taken.tv_sec
                                                       * 1000 + sock_send.taken.tv_usec / 1000);
                            seqno = (data.data[25] << 24)
                                    | (data.data[24] << 16)
                                    | (data.data[23] << 8) | data.data[22];
#if 1
                            MESH_LOGW(
                                "[%u/%u]ms from "MACSTR", seq:%d, len:%d, Q[%d],heap:%d",
                                toDS_recv.ms, sock_send.ms,
                                MAC2STR(from.addr), seqno, data.size,
                                esp_mesh_available_txupQ_num(&from, NULL),
                                esp_get_free_heap_size());
#endif
                            goto SOCK_SEND;
                        }

                    } else {
                        ets_printf(
                            "%s,%d TCP disconnected, tcp_cli_sock:%d, mesh_cnx_state:%d\n",
                            __func__, __LINE__, tcp_cli_sock,
                            mesh_cnx_state);
                    }
                }
            }
        }
        if (is_running == false) {
            MESH_LOGE("err: is_running false");
        }
    }

    if (data.data) {
        free(data.data);
    }
    MESH_LOGE("err: task stop");
    mesh_tcpip_disconnect_server();
    mesh_tcpip_tx_task = NULL;
    vTaskDelete(NULL);
}

static void mesh_tcpip_rx_main(void *arg)
{
    typedef struct {
        uint8_t count;
        mesh_addr_t *addr;
    } mesh_ctl_t;
    mesh_ctl_t mesh_ctl;

    struct timeval cur_time;
    time_t old_time = 0;
    uint8_t mcast_addr[6] = { 0x01, 0x00, 0x5e, 0x00, 0x00, 0x00 };
    fd_set rdset, exset;
    esp_err_t err;
    mesh_addr_t to;
    mesh_opt_t opt;
    mesh_data_t data;
    mesh_data_t ctl_data;
    int ctl_data_offset = 0;
    int recv_size = 0;
    data.size = TCP_RECV_SIZE;
    data.data = (uint8_t *) malloc(TCP_RECV_SIZE);
    if (!data.data) {
        ets_printf("tcpip rx fails\n");
        vTaskDelete(NULL);
        return;
    }

    is_rx_stopped = false;
    is_running = true;
    while (is_running) {
        if (!esp_mesh_is_root()) {
            /* non-root */
            break;
        }
        if (esp_mesh_is_server_connected() == MESH_SERVER_DISCONNECTED) {
            if (mesh_tcpip_connect_server() != ESP_OK) {
                vTaskDelay(3000 / portTICK_PERIOD_MS);
                continue;
            }
        }

        FD_ZERO(&rdset);
        FD_SET(tcp_cli_sock, &rdset);
        FD_ZERO(&exset);
        FD_SET(tcp_cli_sock, &exset);
        if (select(tcp_cli_sock + 1, &rdset, NULL, &exset, NULL) > 0) {
            if (FD_ISSET(tcp_cli_sock, &exset)) {
                /* process the socket exception */
                if (tcp_cli_sock != -1) {
                    close(tcp_cli_sock);
                    tcp_cli_sock = -1;
                    mesh_cnx_state = MESH_CNX_STATE_IDLE;
                }
                ESP_ERROR_CHECK(esp_mesh_post_toDS_state(0));
                MESH_DEBUG("rx exception\n");
            }
            if (FD_ISSET(tcp_cli_sock, &rdset)) {

                gettimeofday(&cur_time, NULL);
                if (esp_mesh_is_server_connected() == MESH_SERVER_CONNECTED) {
                    ctl_data_offset = 0;
                    memset(data.data, 0, TCP_RECV_SIZE);
                    recv_size = recv(tcp_cli_sock, data.data, TCP_RECV_SIZE, 0);
                    if (recv_size <= 0) {
                        MESH_LOGE("[ROOT]err:%d, size:%d", errno, data.size);
                        if (errno == ENOTCONN) {
                            /* Socket is not connected */
                            close(tcp_cli_sock);
                            tcp_cli_sock = -1;
                            mesh_cnx_state = MESH_CNX_STATE_IDLE;
                            ESP_ERROR_CHECK(esp_mesh_post_toDS_state(0));
                        }
                        continue;
                    }
                    MESH_LOGW("recv:%d", recv_size);
                    data.size = recv_size;
#ifdef MESH_TCPIP_DUMP
                    {
                        int i = 0;
                        ets_printf(
                            "[ROOT]receive from server[%d], address count[%d]\n",
                            data.size, data.data[0]);
                        for (i = 0; i < data.size; i++) {
                            ets_printf("%x ", data.data[i]);
                        }
                        ets_printf("\n");
                    }
#endif /* MESH_TCPIP_DUMP */

                } else {
                    ets_printf(
                        "%s,%d TCP disconnected, tcp_cli_sock:%d, mesh_cnx_state:%d\n",
                        __func__, __LINE__, tcp_cli_sock, mesh_cnx_state);
                    continue;
                }

#ifdef MESH_TCPIP_OPT_RECV_DS
                mesh_opt_t optDS;
                uint8_t ds_addr[6];
                memcpy(ds_addr, &server_ip, sizeof(server_ip));
                memcpy(&ds_addr[4], &server_port, sizeof(server_port));
                optDS.type = MESH_OPT_RECV_DS_ADDR;
                optDS.len = sizeof(mesh_addr_t);
                optDS.val = ds_addr;
#endif /* MESH_TCPIP_OPT_RECV_DS */
                /* address format: len(1byte) + address
                 * ex: 1 30 ae a4 03 69 a8
                 */
                mesh_ctl.count = data.data[0];
                mesh_ctl.addr = (mesh_addr_t *) &data.data[1];
                ctl_data_offset = (1 + mesh_ctl.count * sizeof(mesh_addr_t));

                if (mesh_ctl.count == 1) {
                    memcpy(&to, mesh_ctl.addr, sizeof(mesh_addr_t));
                    memset(&ctl_data, 0, sizeof(mesh_data_t));
                    ctl_data.size = data.size - ctl_data_offset;
                    ctl_data.data = (uint8_t *) malloc(ctl_data.size);
                    if (!ctl_data.data) {
                        continue;
                    }
                    memcpy(ctl_data.data, data.data + ctl_data_offset,
                           ctl_data.size);
                    ctl_data.proto = MESH_PROTO_BIN;
#ifdef MESH_TCPIP_TOS_P2P
                    ctl_data.tos = MESH_TOS_P2P;
#endif /* MESH_TCPIP_TOS_P2P */
#ifdef MESH_TCPIP_OPT_RECV_DS
                    /* send to mesh */
                    err = esp_mesh_send(&to, &ctl_data, MESH_DATA_FROMDS,
                                        &optDS, 1);
#else /* MESH_TCPIP_OPT_RECV_DS*/
                    /* send to mesh */
                    err = esp_mesh_send(&to, &ctl_data, MESH_DATA_FROMDS, NULL,
                                        0);
#endif /* MESH_TCPIP_OPT_RECV_DS */
                    free(ctl_data.data);
                } else {
                    /* option */
                    opt.type = MESH_OPT_MCAST_GROUP;
                    opt.len = mesh_ctl.count * sizeof(mesh_addr_t);
                    opt.val = (uint8_t *) malloc(opt.len);
                    if (!opt.val) {
                        continue;
                    }
                    memcpy((uint8_t *) opt.val, (uint8_t *) mesh_ctl.addr,
                           opt.len);
                    memcpy((uint8_t *) &to, mcast_addr, sizeof(mcast_addr));

                    /* payload */
                    memset(&ctl_data, 0, sizeof(mesh_data_t));
                    ctl_data.size = data.size - ctl_data_offset;
                    ctl_data.data = (uint8_t *) malloc(ctl_data.size);
                    if (!ctl_data.data) {
                        continue;
                    }
                    ctl_data.proto = MESH_PROTO_BIN;
#ifdef MESH_TCPIP_TOS_P2P
                    ctl_data.tos = MESH_TOS_P2P;
#endif /* MESH_TCPIP_TOS_P2P */
                    memcpy(ctl_data.data, data.data + ctl_data_offset,
                           ctl_data.size);

#ifdef MESH_TCPIP_OPT_RECV_DS
                    mesh_opt_t option[2];
                    memcpy(&option[0], &opt, sizeof(mesh_opt_t));
                    memcpy(&option[1], &optDS, sizeof(mesh_opt_t));
                    /* send to mesh */
                    err = esp_mesh_send(&to, &ctl_data, MESH_DATA_FROMDS,
                                        option, sizeof(option) / sizeof(mesh_opt_t));
#else /* MESH_TCPIP_OPT_RECV_DS*/
                    /* send to mesh */
                    err = esp_mesh_send(&to, &ctl_data, MESH_DATA_FROMDS, &opt,
                                        1);
#endif /* MESH_TCPIP_OPT_RECV_DS */
                    free(ctl_data.data);
                    free(opt.val);
                }
#if 1
                MESH_LOGW(
                    "[%u]s receive from server len:%d to "MACSTR", socketID:%d[%d]",
                    (int )(cur_time.tv_sec - old_time), data.size,
                    MAC2STR(to.addr), tcp_cli_sock, err);
#endif

                old_time = cur_time.tv_sec;
            }
        }
        if (is_running == false) {
            MESH_LOGE("err: is_running false");
            while (recv(tcp_cli_sock, data.data, TCP_RECV_SIZE, 0))
                ;
            is_rx_stopped = true;
        }
    }

    if (data.data) {
        free(data.data);
    }
    mesh_tcpip_disconnect_server();
    mesh_tcpip_rx_task = NULL;
    vTaskDelete(NULL);
}

