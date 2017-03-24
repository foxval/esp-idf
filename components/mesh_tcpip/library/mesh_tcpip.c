#include "mesh.h"
#include "mesh_wifi.h"
#include "mesh_route.h"
#include "mesh_tcpip.h"
#include "mesh_config.h"
#include "mesh_common.h"
#include "mesh_parent.h"
#include "mesh_schedule.h"
#include "mesh_log.h"
#include "lwip/inet.h"
#include "lwip/netdb.h"
#include "esp_err.h"

static const char *TAG = "mesh_tcpip";
void mesh_print_ap_info();
void mesh_print_task_info();
void mesh_connect_server();
void mesh_tcpip_tx_task(void *pvPara);
void mesh_tcpip_rx_task(void *pvPara);

static int tcp_cli_sock = -1;

#define MESH_CNX_STATE_IDLE       1
#define MESH_CNX_STATE_CONNECTING 2
#define MESH_CNX_STATE_CONNECTED  3

static volatile uint8_t mesh_cnx_state = MESH_CNX_STATE_IDLE;

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

esp_err_t esp_hostname_lookup(const char* hostname, uint32_t* address)
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
            return true;
        }
    }
    return ESP_OK;
}

void MESH_FUNC_ATTR
mesh_close_server()
{
    MESH_ENTER_CRITICAL();
    if (tcp_cli_sock != -1) {
        close(tcp_cli_sock);
        tcp_cli_sock = -1;
    } MESH_EXIT_CRITICAL();
}

void MESH_FUNC_ATTR
mesh_connect_server(void)
{
    if (mesh_cnx_state == MESH_CNX_STATE_CONNECTING) {
        return;
    }
    mesh_cnx_state = MESH_CNX_STATE_CONNECTING;

    printf("%s,%d\n", __func__, __LINE__);

    int opt = 1;
    struct sockaddr_in sock_addr;
    uint8_t op = (uint8_t) MESH_ENABLE_DONE;

    MESH_ENTER_CRITICAL();
    if (tcp_cli_sock < 0) {
        tcp_cli_sock = socket(PF_INET, SOCK_STREAM, 0);
    }MESH_EXIT_CRITICAL();

    if (tcp_cli_sock < 0) {
        /*
         * it's fail to create socket, we need to do it again.
         */
        MESH_DEBUG("sock:%d\n", tcp_cli_sock);
        goto CONNECT_SERVER_ERR;
    }

#if 0
    /*
     * non-block socket
     */
    if (fcntl(tcp_cli_sock, F_SETFL, O_NONBLOCK) < 0) {
        goto CONNECT_SERVER_ERR;
    }
#endif

    /*
     * enable keep alive option
     */
    if (setsockopt(tcp_cli_sock, SOL_SOCKET, SO_KEEPALIVE,
            (const char *)&opt, sizeof(opt)) != 0) {
        MESH_DEBUG("set sock err, keepalive\n");
        goto CONNECT_SERVER_ERR;
    }

    /*
     * set keep alive option, keep idle time
     */
    int keep_idle = 60;
    if (setsockopt(tcp_cli_sock, IPPROTO_TCP, TCP_KEEPIDLE,
            (const char *)&keep_idle, sizeof(keep_idle)) != 0) {
        MESH_DEBUG("set sock err, idle\n");
        goto CONNECT_SERVER_ERR;
    }

    /*
     * set keep alive option, keep count
     */
    int keep_cnt = 3;
    if (setsockopt(tcp_cli_sock, IPPROTO_TCP, TCP_KEEPCNT,
            (const char *)&keep_cnt, sizeof(keep_cnt)) != 0) {
        MESH_DEBUG("set sock err, cnt\n");
        goto CONNECT_SERVER_ERR;
    }

    /*
     * set keep alive option, keep interval time
     */
    int keep_interval = 5;
    if (setsockopt(tcp_cli_sock, IPPROTO_TCP, TCP_KEEPINTVL,
            (const char *)&keep_interval, sizeof(keep_interval)) != 0) {
        MESH_DEBUG("set sock err, interval\n");
        goto CONNECT_SERVER_ERR;
    }

    MESH_MEMSET(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(g_mesh_server_info.port);

#if 0
    const char MESH_SERVER_HOSTNAME[] = "iot.espressif.cn";
    uint32_t server_ip;
    esp_hostname_lookup(MESH_SERVER_HOSTNAME, &server_ip);
    sock_addr.sin_addr.s_addr = server_ip;
#else
    MESH_MEMCPY(&sock_addr.sin_addr, g_mesh_server_info.ip,
            sizeof(sock_addr.sin_addr));
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
        goto CONNECT_SERVER_ERR;
    }
    MESH_LOGI("Connect server successfully\n");
    mesh_cnx_state = MESH_CNX_STATE_CONNECTED;

    if (mesh_tcpip_task_init()) {
        xQueueSend(g_mesh_fsm_queue_handler, &op, portMAX_DELAY);
        return;
    }
    MESH_DEBUG("mesh_tcpip_task_init fail\n");

    CONNECT_SERVER_ERR: if (tcp_cli_sock >= 0) {
        close(tcp_cli_sock);
        tcp_cli_sock = -1;
    }
    op = (uint8_t) MESH_CONN_SERVER;
    xQueueSend(g_mesh_fsm_queue_handler, &op, portMAX_DELAY);
    MESH_LOGI("Connect server failed\n");
    mesh_cnx_state = MESH_CNX_STATE_IDLE;
}

void MESH_FUNC_ATTR
mesh_print_ap_info()
{
    wifi_mode_t mode;
    wifi_config_t config;
    esp_wifi_get_mode(&mode);
    esp_wifi_get_config(WIFI_IF_AP, &config);
    MESH_DEBUG("op_mode:%d\n", mode);
    MESH_DEBUG("AP info:\n");
    MESH_DEBUG("ssid:%s, passwd:%s\n", (char *) config.ap.ssid,
            (char *) config.ap.password);
    MESH_DEBUG("slen:%u, chan:%d, auth:%d, hiden:%d, max_con:%d, interval:%d\n",
            config.ap.ssid_len, config.ap.channel, config.ap.authmode,
            config.ap.ssid_hidden, config.ap.max_connection,
            config.ap.beacon_interval);
}

void MESH_FUNC_ATTR
mesh_tcpip_tx_task(void *pvPara)
{
    fd_set wrset, exset;
    struct mesh_packet_context_t *ctx = NULL;
    int cur_time, old_time = 0;

    while (1) {
        if (tcp_cli_sock == -1 || mesh_cnx_state != MESH_CNX_STATE_CONNECTED) {
            mesh_connect_server();
            vTaskDelay(3000 / portTICK_PERIOD_MS);
            continue;
        }

        FD_ZERO(&wrset);
        FD_SET(tcp_cli_sock, &wrset);
        FD_ZERO(&exset);
        FD_SET(tcp_cli_sock, &exset);

        if (select(tcp_cli_sock + 1, NULL, &wrset, &exset, NULL) > 0) {
#if 0
            MESH_DEBUG("server_sock tx:%d\n", tcp_cli_sock);
            mesh_print_ap_info();
            if (esp_mesh_is_enabled()) {
                mesh_print_task_info();
            }
#endif
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
                if (g_mesh_tcpip_queue_handler &&
                xQueueReceive(g_mesh_tcpip_queue_handler, &ctx,
                        portMAX_DELAY) == pdTRUE) {
                    if (ctx && ctx->buf) {
                        cur_time = system_get_time();
                        struct mesh_header_format *head =
                                (struct mesh_header_format *) ctx->buf;
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
    if (g_mesh_tcpip_queue_handler) {
        while (xQueueReceive(g_mesh_tcpip_queue_handler, &ctx, 0) == pdTRUE) {
            esp_mesh_free_packet_contxt(ctx);
            ctx = NULL;
        }
    }

    /*
     * Invalid global queue handler firstly, then free the packet in queue.
     */
    QueueHandle_t tcpip_queue = g_mesh_tcpip_queue_handler;
    MESH_ENTER_CRITICAL();
    g_mesh_tcpip_queue_handler = NULL;
    MESH_EXIT_CRITICAL();
    if (tcpip_queue) vQueueDelete(tcpip_queue);

    MESH_ENTER_CRITICAL();
    g_mesh_tcpip_tx_task_handle = NULL;
    MESH_EXIT_CRITICAL();

    vTaskDelete(NULL);
}

void MESH_FUNC_ATTR
mesh_tcpip_rx_task(void *pvPara)
{
    int size;
    fd_set rdset, exset;
    int cur_time, old_time = 0;
    mesh_header_t* header = NULL;
    uint8_t mac[6] = { 0, };
    esp_wifi_get_mac(ESP_IF_WIFI_STA, mac);


    while (1) {
        if (tcp_cli_sock == -1 || mesh_cnx_state != MESH_CNX_STATE_CONNECTED) {
            //sleep and wait tx task finish the connection
            vTaskDelay(3000 / portTICK_PERIOD_MS);
            continue;
        }

        FD_ZERO(&rdset);
        FD_SET(tcp_cli_sock, &rdset);
        FD_ZERO(&exset);
        FD_SET(tcp_cli_sock, &exset);

        if (select(tcp_cli_sock + 1, &rdset, NULL, &exset, NULL) > 0) {
            struct mesh_packet_context_t *ctx = NULL;
#if 0
            MESH_DEBUG("server_sock rx:%d\n", tcp_cli_sock);
            mesh_print_ap_info();
            if (esp_mesh_is_enabled()) {
                mesh_print_task_info();
            }
#endif
            if (FD_ISSET(tcp_cli_sock, &exset)) {
                /*
                 * process the socket exception
                 */
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
                /*
                 * check read set pending in LWIP, we get packet from LWIP,
                 * and send packet to mesh layer
                 */
//                MESH_LOGE("heap:%d", esp_get_free_heap_size());
                ctx = (struct mesh_packet_context_t *) MESH_ZALLOC(
                        sizeof(*ctx));
//                MESH_LOGE("ctx:%p, heap:%d", ctx, esp_get_free_heap_size());
                if (ctx) {
                    ctx->buf = MESH_ZALLOC(ESP_MESH_PKT_LEN_MAX);
                    uint8_t* buf = (uint8_t*) ctx->buf;
                    MESH_LOGE("buf:%p", buf);
                    if (ctx->buf) {
                        ctx->ifidx = WIFI_IF_STA;
                        MESH_MEMCPY(ctx->src, mac, sizeof(mac));

                        cur_time = system_get_time();
                        size = recv(tcp_cli_sock, ctx->buf,
                                ESP_MESH_PKT_LEN_MAX, MSG_DONTWAIT);
                        ctx->buf_len = size;
                        header = (mesh_header_t*)ctx->buf;
                        if (size) {
                            MESH_LOGW(
                                    "[%d]ms, Receive from server len:%d, mlen:%d, DST:%02x:%02x:%02x:%02x:%02x:%02x, socketID:%d",
                                    (cur_time - old_time) / 1000, size, header->len, buf[4],
                                    buf[5], buf[6], buf[7], buf[8], buf[9],
                                    tcp_cli_sock);
                        }
                        old_time = cur_time;
                        if(size != header->len) {
                            MESH_LOGE("!!! Be careful size:%d, mlen:%d\n", size, header->len);
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
                        /*
                         * If the mesh parser is limited to process the packet
                         * discard the packet
                         */
                        if ((size > 0)
                                && xQueueSend(g_mesh_rx_queue_handler, &ctx, 0)) {
                            /*
                             * if the count of packet pending in queue is more then half of the size,
                             * we try to yield cpu to parser task.
                             */
                            if (uxQueueSpacesAvailable(
                                    g_mesh_rx_queue_handler) < ESP_MESH_PKT_PENDING_SWITCH) {
                                taskYIELD();
                            }
                            continue;
                        }
                    }
                }
                esp_mesh_free_packet_contxt(ctx);
                ctx = NULL;
            }
        }
    }

    MESH_ENTER_CRITICAL();
    g_mesh_tcpip_rx_task_handle = NULL;
    MESH_EXIT_CRITICAL();

    vTaskDelete(NULL);
}

void MESH_FUNC_ATTR mesh_tcpip_start()
{
    MESH_DEBUG("%s\n", __func__);
}

void MESH_FUNC_ATTR mesh_tcpip_stop()
{
    MESH_DEBUG("%s\n", __func__);
    tcpip_adapter_dhcps_stop(TCPIP_ADAPTER_IF_AP);
    tcpip_adapter_dhcpc_stop(TCPIP_ADAPTER_IF_STA);
}
