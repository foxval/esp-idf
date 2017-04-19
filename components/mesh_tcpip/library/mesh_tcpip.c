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

#include "mesh.h"
#include "mesh_config.h"
#include "mesh_common.h"
#include "mesh_log.h"
#include "lwip/inet.h"
#include "lwip/netdb.h"

/*******************************************************
 *                Constants
 *******************************************************/
static const char *TAG = "mesh_tcpip";

#define MESH_CNX_STATE_IDLE          (1)
#define MESH_CNX_STATE_CONNECTING    (2)
#define MESH_CNX_STATE_CONNECTED     (3)

static xTaskHandle mesh_tcpip_tx_task = NULL;
static xTaskHandle mesh_tcpip_rx_task = NULL;
static int tcp_cli_sock = -1;
static int server_port = -1;
static char server_hostname[128] = { 0, };
static volatile uint8_t mesh_cnx_state = MESH_CNX_STATE_IDLE;
static volatile bool is_running = false;
static bool is_dhcp_stopped = false;

/*******************************************************
 *                Function Declarations
 *******************************************************/
static void mesh_tcpip_tx_task_main(void *pvPara);
static void mesh_tcpip_rx_task_main(void *pvPara);
static esp_err_t mesh_tcpip_task_init(void);
static esp_err_t mesh_tcpip_connect_server(void);
static esp_err_t mesh_tcpip_disconnect_server(void);

/*******************************************************
 *                Function Definitions
 *******************************************************/
void esp_mesh_tcpip_enable_dhcp(void)
{
    MESH_LOGI("%s\n", __func__);
    if (is_dhcp_stopped) {
        tcpip_adapter_dhcpc_start(TCPIP_ADAPTER_IF_STA);
        is_dhcp_stopped = false;
    }
}

void esp_mesh_tcpip_disable_dhcp(void)
{
    MESH_LOGI("%s\n", __func__);
    if (!is_dhcp_stopped) {
        tcpip_adapter_dhcps_stop(TCPIP_ADAPTER_IF_AP);
        tcpip_adapter_dhcpc_stop(TCPIP_ADAPTER_IF_STA);
        is_dhcp_stopped = true;
    }
}

esp_err_t esp_mesh_tcp_client_start(const char* hostname, int hostname_len,
        int port)
{
    static bool is_inited = false;
    if (!hostname || !hostname_len || port == -1) {
        return ESP_FAIL;
    }
    if (is_inited) {
        return ESP_OK;
    }

    if (strlen(server_hostname)) {
        memcpy(server_hostname, hostname, hostname_len);
    }
    if (server_port != -1) {
        server_port = port;
    }
    mesh_tcpip_task_init();
    is_inited = true;
    return ESP_OK;
}

esp_err_t esp_mesh_tcp_client_stop(void)
{
    is_running = false;
    return ESP_OK;
}

static esp_err_t mesh_tcpip_task_init(void)
{
    bool is_failed = false;
    if (!mesh_tcpip_tx_task) {
        xTaskCreate(mesh_tcpip_tx_task_main, MESH_TCPIP_TX_TASK_NAME,
                MESH_TCPIP_TX_TASK_STACK, NULL, MESH_TCPIP_TX_TASK_PRI,
                &mesh_tcpip_tx_task);
        if (!mesh_tcpip_tx_task) {
            is_failed = true;
        }
    }
    if (!mesh_tcpip_rx_task) {
        xTaskCreate(mesh_tcpip_rx_task_main, MESH_TCPIP_RX_TASK_NAME,
                MESH_TCPIP_RX_TASK_STACK, NULL, MESH_TCPIP_RX_TASK_PRI,
                &mesh_tcpip_rx_task);
        if (!mesh_tcpip_rx_task) {
            is_failed = true;
        }
    }
    if (is_failed) {
        if (mesh_tcpip_tx_task) {
            vTaskDelete(mesh_tcpip_tx_task);
            mesh_tcpip_tx_task = NULL;
        }
        if (mesh_tcpip_rx_task) {
            vTaskDelete(mesh_tcpip_rx_task);
            mesh_tcpip_rx_task = NULL;
        }
        return ESP_FAIL;
    }
    return ESP_OK;
}

static uint32_t str_to_ipv4(const char* arg)
{
    uint32_t addr = 0;
    uint8_t num = 0;
    arg--;
    do {
        addr = addr << 8;
        addr += (uint32_t) atoi(++arg);
        while ((*arg != '\x00') && (*arg != '.')) {
            arg++;
        }
        num++;
    } while ((num < 4) && (*arg != '\x00'));
    if (num < 4) {
        return 0;
    }
    return addr;
}

esp_err_t esp_mesh_hostname_lookup(const char* hostname, uint32_t* address)
{
    /* Check if address is a string representation of a IPv4 address i.e. xxx.xxx.xxx.xxx */
    if (!hostname || !address) {
        return ESP_FAIL;
    }
    *address = str_to_ipv4(hostname);
    if (*address == 0) {
        struct hostent* hp = gethostbyname(hostname);
        if (hp) {
            struct ip4_addr *ip4_addr = (struct ip4_addr *) hp->h_addr;
            char ipaddr_str[16] = {0};
            sprintf(ipaddr_str, IPSTR, IP2STR(ip4_addr));
            *address = inet_addr(ipaddr_str);
            printf("%s,%d hostname:%s, ip:%s\n", __func__, __LINE__, hostname,
                    ipaddr_str);
        }
    }
    return ESP_OK;
}

static esp_err_t _tcpip_connect_fail(void)
{
    MESH_LOGI("Connect server failed\n");
    mesh_cnx_state = MESH_CNX_STATE_IDLE;
    if (tcp_cli_sock != -1) {
        close(tcp_cli_sock);
        tcp_cli_sock = -1;
    }
    return ESP_FAIL;
}

static esp_err_t mesh_tcpip_connect_server(void)
{
    printf("%s,%d mesh_cnx_state:%d\n", __func__, __LINE__, mesh_cnx_state);
    int opt = 1;
    int keep_idle = 60;
    int keep_cnt = 3;
    int keep_interval = 5;
    struct sockaddr_in sock_addr;
    static uint32_t server_ip = 0;

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
#if 1
    sock_addr.sin_port = htons(g_mesh_server_info.port);
    memcpy(&sock_addr.sin_addr, g_mesh_server_info.ip,
            sizeof(sock_addr.sin_addr));
#else
    sock_addr.sin_port = server_port;
    if (!server_ip) {
        esp_mesh_hostname_lookup(server_hostname, &server_ip);
    }
    sock_addr.sin_addr.s_addr = server_ip;
#endif

    MESH_LOGI("Connect server ip:%d.%d.%d.%d:%d, socket:%d",
            g_mesh_server_info.ip[0], g_mesh_server_info.ip[1],
            g_mesh_server_info.ip[2], g_mesh_server_info.ip[3],
            g_mesh_server_info.port, tcp_cli_sock);
    if (connect(tcp_cli_sock, (struct sockaddr * )&sock_addr,
            sizeof(sock_addr)) != ESP_OK) {
        MESH_LOGE("Failed, ip:%d.%d.%d.%d, port:%d, errno:%d",
                g_mesh_server_info.ip[0], g_mesh_server_info.ip[1],
                g_mesh_server_info.ip[2], g_mesh_server_info.ip[3],
                g_mesh_server_info.port, errno);
        esp_mesh_update_event(ESP_MESH_TCP_DISCONNECTED);
        return _tcpip_connect_fail();
    } else {
        MESH_LOGI("Connect server successfully\n");
        mesh_cnx_state = MESH_CNX_STATE_CONNECTED;
        esp_mesh_update_event(ESP_MESH_TCP_CONNECTED);
    }
    return ESP_OK;
}

static esp_err_t mesh_tcpip_disconnect_server(void)
{
    mesh_cnx_state = MESH_CNX_STATE_IDLE;
    if (tcp_cli_sock != -1) {
        close(tcp_cli_sock);
        tcp_cli_sock = -1;
    }
    return ESP_OK;
}

static void mesh_tcpip_tx_task_main(void *pvPara)
{
    fd_set wrset, exset;
    mesh_ctx_t *ctx = NULL;
    mesh_hdr_t *head = NULL;
    int cur_time, old_time = 0;

    if (tcp_cli_sock == -1 || mesh_cnx_state != MESH_CNX_STATE_CONNECTED) {
        mesh_tcpip_connect_server();
    }
    is_running = true;

    while (is_running) {
        if (!esp_mesh_is_root()) {
            /* non-root */
            break;
        }
        if (tcp_cli_sock == -1 || mesh_cnx_state != MESH_CNX_STATE_CONNECTED) {
            mesh_tcpip_connect_server();
            vTaskDelay(3000 / portTICK_PERIOD_MS);
            MESH_LOGE("reconnect to server ...");
            continue;
        }

        FD_ZERO(&wrset);
        FD_SET(tcp_cli_sock, &wrset);
        FD_ZERO(&exset);
        FD_SET(tcp_cli_sock, &exset);

        if (select(tcp_cli_sock + 1, NULL, &wrset, &exset, NULL) > 0) {
            ctx = NULL;
            if (FD_ISSET(tcp_cli_sock, &exset)) {
                /*
                 * process the socket exception
                 */
                if (tcp_cli_sock != -1) {
                    close(tcp_cli_sock);
                    tcp_cli_sock = -1;
                    mesh_cnx_state = MESH_CNX_STATE_IDLE;
                }
                MESH_DEBUG("tx exception\n");
                if (!esp_mesh_is_enabled()) {
                    MESH_DEBUG("tx not enable\n");
                    break;
                }
            }
            if (FD_ISSET(tcp_cli_sock, &wrset)) {
                /*
                 * check write set
                 * if there is packet waiting in queue, we get packet from queue,
                 * and send packet out
                 */
                if (esp_mesh_pop_from_tcpip_queue((mesh_ctx_t*) &ctx,
                portMAX_DELAY) == ESP_OK) {
                    if (ctx && ctx->buf) {
                        cur_time = system_get_time();
                        head = (mesh_hdr_t *) ctx->buf;
                        MESH_LOGI(
                                "[%d]ms, Send to server len:%d, SRC:"MACSTR", socketID:%d",
                                (cur_time - old_time) / 1000, head->len,
                                MAC2STR(head->src_addr), tcp_cli_sock);

                        send(tcp_cli_sock, head, head->len, MSG_DONTWAIT);
                        old_time = cur_time;
                    }
                    esp_mesh_free_packet_contxt(ctx);
                    ctx = NULL;
                }
            }
        }
    }

    /*
     * release the packet context pending in tcpip queue.
     */
    while (esp_mesh_pop_from_tcpip_queue((mesh_ctx_t*) &ctx, 0) == ESP_OK) {
        esp_mesh_free_packet_contxt(ctx);
        ctx = NULL;
    }

    mesh_tcpip_disconnect_server();
    mesh_tcpip_tx_task = NULL;
    vTaskDelete(NULL);
}

static void mesh_tcpip_rx_task_main(void *pvPara)
{
    int size;
    fd_set rdset, exset;
    int cur_time, old_time = 0;
    mesh_ctx_t *ctx = NULL;
    mesh_hdr_t* header = NULL;
    uint8_t* buf = NULL;
    uint8_t mac[6] = { 0, };
    is_running = true;

    esp_wifi_get_mac(ESP_IF_WIFI_STA, mac);
    while (is_running) {
        if (esp_mesh_get_hop() != 1) {
            /* non-root */
            break;
        }
        if (tcp_cli_sock == -1 || mesh_cnx_state != MESH_CNX_STATE_CONNECTED) {
            //sleep and wait tx task to do the connection
            vTaskDelay(3000 / portTICK_PERIOD_MS);
//            MESH_LOGE("reconnect to TCP server ...");
            continue;
        }

        FD_ZERO(&rdset);
        FD_SET(tcp_cli_sock, &rdset);
        FD_ZERO(&exset);
        FD_SET(tcp_cli_sock, &exset);

        if (select(tcp_cli_sock + 1, &rdset, NULL, &exset, NULL) > 0) {
            ctx = NULL;
            if (FD_ISSET(tcp_cli_sock, &exset)) {
                /* process the socket exception */
                if (tcp_cli_sock != -1) {
                    close(tcp_cli_sock);
                    tcp_cli_sock = -1;
                    mesh_cnx_state = MESH_CNX_STATE_IDLE;
                }
                MESH_DEBUG("rx exception\n");
                if (!esp_mesh_is_enabled()) {
                    MESH_DEBUG("rx not enable\n");
                    break;
                }
            }
            if (FD_ISSET(tcp_cli_sock, &rdset)) {
//                MESH_LOGE("heap:%d", esp_get_free_heap_size());
                ctx = (mesh_ctx_t *) malloc(sizeof(*ctx));
//                MESH_LOGE("ctx:%p, heap:%d", ctx, esp_get_free_heap_size());
                if (ctx) {
                    ctx->buf = malloc(ESP_MESH_PKT_LEN_MAX);
                    buf = (uint8_t*) ctx->buf;
//                    MESH_LOGE("buf:%p", buf);
                    if (ctx->buf) {
                        memset(ctx->buf, 0, ESP_MESH_PKT_LEN_MAX);
                        ctx->ifidx = WIFI_IF_STA;
                        memcpy(ctx->src, mac, sizeof(mac));
                        cur_time = system_get_time();
                        size = recv(tcp_cli_sock, ctx->buf,
                                ESP_MESH_PKT_LEN_MAX, MSG_DONTWAIT);
                        ctx->buf_len = size;
                        header = (mesh_hdr_t*) ctx->buf;
                        if (size) {
                            MESH_LOGW(
                                    "[%d]ms, Receive from server len:%d, mlen:%d, DST:%02x:%02x:%02x:%02x:%02x:%02x, socketID:%d",
                                    (cur_time - old_time) / 1000, size,
                                    header->len, buf[4], buf[5], buf[6], buf[7],
                                    buf[8], buf[9], tcp_cli_sock);
                        }
                        old_time = cur_time;
                        if (size != header->len) {
                            MESH_LOGE("!!! Be careful size:%d, mlen:%d\n", size,
                                    header->len);
                        }
#if 0
                        if (size > 0) {
                            int i;
                            for (i = 0; i < size; i++) {
                                printf("%x ", buf[i]);
                            }
                            printf("\n");
                        }
#endif
                        if ((size > 0)
                                && esp_mesh_push_to_recv_queue((void*) &ctx, 0)
                                        == ESP_OK) {
                            continue;
                        }
                    }
                }
                esp_mesh_free_packet_contxt(ctx);
                ctx = NULL;
            }
        }
    }

    mesh_tcpip_disconnect_server();
    mesh_tcpip_rx_task = NULL;
    vTaskDelete(NULL);
}

