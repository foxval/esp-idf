#include "mesh.h"
#include "mesh_wifi.h"
#include "mesh_route.h"
#include "mesh_tcpip.h"
#include "mesh_config.h"
#include "mesh_common.h"
#include "mesh_parent.h"
#include "mesh_schedule.h"

void mesh_print_ap_info();
void mesh_print_task_info();
void mesh_connect_server();
void mesh_tcpip_tx_task(void *pvPara);
void mesh_tcpip_rx_task(void *pvPara);

static int g_server_sock = MESH_TCPIP_SOCK_INVALID;

void MESH_FUNC_ATTR
mesh_close_server()
{
    MESH_ENTER_CRITICAL();
    if (g_server_sock != MESH_TCPIP_SOCK_INVALID)
        close(g_server_sock);
    g_server_sock = MESH_TCPIP_SOCK_INVALID;
    MESH_EXIT_CRITICAL();
}

void MESH_FUNC_ATTR
mesh_connect_server()
{
    int opt = 1;
    struct sockaddr_in sock_addr;
    uint8_t op = (uint8_t)MESH_ENABLE_DONE;

    MESH_ENTER_CRITICAL();
    if (g_server_sock < 0)
        g_server_sock = socket(PF_INET, SOCK_STREAM, 0);
    MESH_EXIT_CRITICAL();

    if (g_server_sock < 0) {
        /*
         * it's fail to create socket, we need to do it again.
         */
        MESH_DEBUG("sock:%d\n", g_server_sock);
        goto CONNECT_SERVER_ERR;
    }

#if 0
    /*
     * non-block socket
     */
    if (fcntl(g_server_sock, F_SETFL, O_NONBLOCK) < 0) {
        goto CONNECT_SERVER_ERR;
    }
#endif
    /*
     * enable reuse address
     */
    if (setsockopt(g_server_sock, SOL_SOCKET, SO_REUSEADDR,
            (const char *)&opt, sizeof(opt)) != 0) {
        MESH_DEBUG("set sock err, reuse\n");
        goto CONNECT_SERVER_ERR;
    }

    /*
     * enable keep alive option
     */
    if (setsockopt(g_server_sock, SOL_SOCKET, SO_KEEPALIVE,
                (const char *)&opt, sizeof(opt)) != 0) {
        MESH_DEBUG("set sock err, keepalive\n");
        goto CONNECT_SERVER_ERR;
    }

    /*
     * set keep alive option, keep idle time
     */
    int keep_idle = 60;
    if (setsockopt(g_server_sock, IPPROTO_TCP, TCP_KEEPIDLE,
                (const char *)&keep_idle, sizeof(keep_idle)) != 0) {
        MESH_DEBUG("set sock err, idle\n");
        goto CONNECT_SERVER_ERR;
    }

    /*
     * set keep alive option, keep count
     */
    int keep_cnt = 3;
    if (setsockopt(g_server_sock, IPPROTO_TCP, TCP_KEEPCNT,
                (const char *)&keep_cnt, sizeof(keep_cnt)) != 0) {
        MESH_DEBUG("set sock err, cnt\n");
        goto CONNECT_SERVER_ERR;
    }

    /*
     * set keep alive option, keep interval time
     */
    int keep_interval = 5;
    if (setsockopt(g_server_sock, IPPROTO_TCP, TCP_KEEPINTVL,
                (const char *)&keep_interval, sizeof(keep_interval)) != 0) {
        MESH_DEBUG("set sock err, interval\n");
        goto CONNECT_SERVER_ERR;
    }

    MESH_MEMSET(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    MESH_MEMCPY(&sock_addr.sin_addr, g_mesh_server_info.ip, sizeof(sock_addr.sin_addr));
    sock_addr.sin_port = htons(g_mesh_server_info.port);

    if (connect(g_server_sock, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) != ESP_OK) {
        MESH_DEBUG("conn server err, ip:%d.%d.%d.%d, port:%d\n",
                g_mesh_server_info.ip[0], g_mesh_server_info.ip[1],
                g_mesh_server_info.ip[2], g_mesh_server_info.ip[3],
                g_mesh_server_info.port);
        goto CONNECT_SERVER_ERR;
    }

    if (mesh_tcpip_task_init()) {
        xQueueSend(g_mesh_fsm_queue_handler, &op, portMAX_DELAY);
        return;
    }
    MESH_DEBUG("mesh_tcpip_task_init fail\n");

CONNECT_SERVER_ERR:
    MESH_ENTER_CRITICAL();
    if (g_server_sock >= 0)
        close(g_server_sock);
    g_server_sock = MESH_TCPIP_SOCK_INVALID;
    MESH_EXIT_CRITICAL();
    op = (uint8_t)MESH_CONN_SERVER;
    xQueueSend(g_mesh_fsm_queue_handler, &op, portMAX_DELAY);
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
    MESH_DEBUG("ssid:%s, passwd:%s\n", (char *)config.ap.ssid, (char *)config.ap.password);
    MESH_DEBUG("slen:%u, chan:%d, auth:%d, hiden:%d, max_con:%d, interval:%d\n",
            config.ap.ssid_len, config.ap.channel, config.ap.authmode, config.ap.ssid_hidden,
            config.ap.max_connection, config.ap.beacon_interval);
}

void MESH_FUNC_ATTR
mesh_tcpip_tx_task(void *pvPara)
{
    bool write = false;
    fd_set wrset, exset;
    struct mesh_packet_context_t *ctx = NULL;

    while (1) {
        FD_ZERO(&wrset);
        FD_SET(g_server_sock, &wrset);
        FD_ZERO(&exset);
        FD_SET(g_server_sock, &exset);

        if (write || g_server_sock == MESH_TCPIP_SOCK_INVALID ||
            select(g_server_sock + 1, NULL, &wrset, &exset, NULL) > 0) {
#if 0
            MESH_DEBUG("server_sock tx:%d\n", g_server_sock);
            mesh_print_ap_info();
            if (esp32_mesh_is_enabled())
                mesh_print_task_info();
#endif
            ctx = NULL;
            if (g_server_sock == MESH_TCPIP_SOCK_INVALID || FD_ISSET(g_server_sock, &exset)) {
                /*
                 * process the socket exception
                 */
                MESH_ENTER_CRITICAL();
                if (g_server_sock != MESH_TCPIP_SOCK_INVALID) {
                    close(g_server_sock);
                    g_server_sock = MESH_TCPIP_SOCK_INVALID;
                }
                MESH_EXIT_CRITICAL();
                MESH_DEBUG("tx exception\n");
                if (!esp32_mesh_is_enabled()) {
                    MESH_DEBUG("tx not enable\n");
                    break;
                }
                mesh_connect_server();
            } else if (write || FD_ISSET(g_server_sock, &wrset)) {
                /*
                 * check write set
                 * if there is packet waiting in queue, we get packet from queue,
                 * and send packet out
                 */
                write = true;
                if (g_mesh_tcpip_queue_handler &&
                    xQueueReceive(g_mesh_tcpip_queue_handler, &ctx, portMAX_DELAY) == pdTRUE) {
                    if (ctx && ctx->buf) {
                        struct mesh_header_format *head = (struct mesh_header_format *)ctx->buf;
                        send(g_server_sock, head, head->len, MSG_DONTWAIT);
                        write = false;
                    }
                    esp32_mesh_free_packet_contxt(ctx);
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
            esp32_mesh_free_packet_contxt(ctx);
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
    if (tcpip_queue)
        vQueueDelete(tcpip_queue);

    MESH_ENTER_CRITICAL();
    g_mesh_tcpip_tx_task_handle = NULL;
    MESH_EXIT_CRITICAL();

    vTaskDelete(NULL);
}

void MESH_FUNC_ATTR
mesh_tcpip_rx_task(void *pvPara)
{
    bool read = false;
    fd_set rdset, exset;

    while (1) {
        FD_ZERO(&rdset);
        FD_SET(g_server_sock, &rdset);
        FD_ZERO(&exset);
        FD_SET(g_server_sock, &exset);

        if (read || g_server_sock == MESH_TCPIP_SOCK_INVALID ||
            select(g_server_sock + 1, &rdset, NULL, &exset, NULL) > 0) {
            struct mesh_packet_context_t *ctx = NULL;
#if 0
            MESH_DEBUG("server_sock rx:%d\n", g_server_sock);
            mesh_print_ap_info();
            if (esp32_mesh_is_enabled())
                mesh_print_task_info();
#endif
            if (g_server_sock == MESH_TCPIP_SOCK_INVALID || FD_ISSET(g_server_sock, &exset)) {
                /*
                 * process the socket exception
                 */
                MESH_ENTER_CRITICAL();
                if (g_server_sock != MESH_TCPIP_SOCK_INVALID) {
                    close(g_server_sock);
                    g_server_sock = MESH_TCPIP_SOCK_INVALID;
                }
                MESH_EXIT_CRITICAL();
                MESH_DEBUG("rx exception\n");
                if (!esp32_mesh_is_enabled()) {
                    MESH_DEBUG("rx not enable\n");
                    break;
                }
                mesh_connect_server();
            } else if (read || FD_ISSET(g_server_sock, &rdset)) {
                /*
                 * check read set pending in LWIP, we get packet from LWIP,
                 * and send packet to mesh layer
                 */
                read = true;
                ctx = (struct mesh_packet_context_t *)MESH_ZALLOC(sizeof(*ctx));
                if (ctx) {
                    ctx->buf = MESH_ZALLOC(ESP_MESH_PKT_LEN_MAX);
                    if (ctx->buf) {
                        ctx->ifidx = WIFI_IF_STA;
                        esp_wifi_get_mac(WIFI_IF_STA, ctx->src);
                        recv(g_server_sock, ctx->buf, ESP_MESH_PKT_LEN_MAX, MSG_DONTWAIT);
                        read = false;
                        /*
                         * If the mesh parser is limited to process the packet
                         * discard the packet
                         */
                        if (xQueueSend(g_mesh_rx_queue_handler, &ctx, 0)) {
                            /*
                             * if the count of packet pending in queue is more then half of the size,
                             * we try to yield cpu to parser task.
                             */
                            if (uxQueueSpacesAvailable(g_mesh_rx_queue_handler) < ESP_MESH_PKT_PENDING_SWITCH)
                                taskYIELD();
                            continue;
                        }
                    }
                }
                esp32_mesh_free_packet_contxt(ctx);
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
#if 0
    esp_err_t res;
    uint8_t sta_mac[6];
    tcpip_adapter_dhcp_status_t status;
    tcpip_adapter_ip_info_t sta_ip;

    MESH_DEBUG("%s\n", __func__);
    //tcpip_adapter_init();

    res = tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_STA, &sta_ip);
    MESH_DEBUG("get ip:%d\n", res);
    res = tcpip_adapter_start(TCPIP_ADAPTER_IF_STA, sta_mac, &sta_ip);
    MESH_DEBUG("adapter start:%d\n", res);

    res = tcpip_adapter_up(TCPIP_ADAPTER_IF_STA);
    MESH_DEBUG("adapter up:%d\n", res);

    tcpip_adapter_dhcpc_get_status(TCPIP_ADAPTER_IF_STA, &status);

    if (status != TCPIP_ADAPTER_DHCP_STARTED) {
        res = tcpip_adapter_dhcpc_start(TCPIP_ADAPTER_IF_STA);
        MESH_DEBUG("dhcpc start:%d\n", res);
    }
#endif
}

void MESH_FUNC_ATTR mesh_tcpip_stop()
{
    MESH_DEBUG("%s\n", __func__);
    tcpip_adapter_dhcps_stop(TCPIP_ADAPTER_IF_AP);
    tcpip_adapter_dhcpc_stop(TCPIP_ADAPTER_IF_STA);
}
