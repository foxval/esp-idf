#ifndef __MESH_H__
#define __MESH_H__

#include <stdint.h>
#include "mesh_common.h"

/************ mesh configure information *******************************/
#define ESP_MESH_CONNECT_MAX              (4)
#define ESP_MESH_ESP32_VER                (1)
#define ESP_MESH_DEFAULT_MAX_HOP          (4)
#define ESP_MESH_PKT_PENDING_MAX          (ESP_MESH_CONNECT_MAX << 2)
#define ESP_MESH_PKT_PENDING_SWITCH       (ESP_MESH_CONNECT_MAX >> 2)
/***********************************************************************/

/************ mesh constant and check information **********************/
#define ESP_MESH_MACSTR                   "%02x:%02x:%02x:%02x:%02x:%02x"
#define ESP_MESH_MAC2STR(addr)            ((uint8_t *)addr)[0], ((uint8_t *)addr)[1],\
                                          ((uint8_t *)addr)[2], ((uint8_t *)addr)[3],\
                                          ((uint8_t *)addr)[4], ((uint8_t *)addr)[5]
#define ESP_MESH_ARRAY_ELEM_COUNT(array)  (sizeof((array))/sizeof((array)[0]))
#define ESP_MESH_IDX_NONE                 (-1)
#define ESP_MESH_VALID_CIDX(cidx)         ((cidx) >=0 && (cidx) < ESP_MESH_CONNECT_MAX)
#define ESP_MESH_HOP_ONE                  (1)
/***********************************************************************/

/************ mesh packet information **********************************/
#define ESP_MESH_PKT_LEN_MAX              (1460)
#define ESP_MESH_OPTION_MAX_LEN           (255)
#define ESP_MESH_OT_LEN_LEN               (sizeof(uint16_t))
#define ESP_MESH_HLEN                     (sizeof(struct mesh_header_format))
#define ESP_MESH_OPTION_HLEN              (sizeof(struct mesh_header_option_format))
#define ESP_MESH_OP_MAX_PER_PKT           ((ESP_MESH_PKT_LEN_MAX - ESP_MESH_HLEN) / ESP_MESH_OPTION_MAX_LEN)
#define ESP_MESH_DEV_MAX_PER_OP           ((ESP_MESH_OPTION_MAX_LEN - ESP_MESH_OPTION_HLEN) / MESH_HWADDR_LEN)
#define ESP_MESH_DEV_MAX_PER_PKT          (ESP_MESH_OP_MAX_PER_PKT * ESP_MESH_DEV_MAX_PER_OP)
/***********************************************************************/

/************* mesh error no *******************************************/
#define ESP_MESH_ERR_NOT_ENABLED          (-1)
#define ESP_MESH_ERR_NO_DATA              (-2)
#define ESP_MESH_ERR_NO_MEM               (-3)
#define ESP_MESH_ERR_TIMEOUT              (-4)
#define ESP_MESH_ERR_QUEUE                (-5)
#define ESP_MESH_ERR_NO_IF                (-6)
#define ESP_MESH_ERR_NO_CTX               (-7)
#define ESP_MESH_ERR_NOT_SUPPORT          (-7)
#define ESP_MESH_ERR_NO_PATH              (-9)
#define ESP_MESH_ERR_BUF_LIMIT            (-10)
#define ESP_MESH_ERR_NO_OP                (-11)
#define ESP_MESH_MCAST_NO_TYPE            (-12)
#define ESP_MESH_MCAST_NO_ELEM            (-13)
#define ESP_MESH_NO_CHILD                 (-14)
/***********************************************************************/

enum mesh_op_result_t
{
    MESH_OP_SUC, MESH_OP_FAIL,
};

enum mesh_type
{
    MESH_NONE = 0x00, MESH_ONLINE, MESH_LOCAL,
};

enum mesh_node_t
{
    MESH_NODE_PARENT, MESH_NODE_CHILD, MESH_NODE_ALL,
};

typedef void (*esp32_mesh_op_callback_t)(enum mesh_op_result_t result);
typedef void (*esp32_mesh_usr_callback_t)(void *para);

/* mesh header format:
 * |0 1 2  3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7|
 * __________________________________________________________________
 * |ver|oe|  flags  |    proto      |             len               |
 * ------------------------------------------------------------------
 * |                      dst_addr   _______________________________|
 * |_________________________________|                              |                              |
 * |                                    src_addr                    |
 * |----------------------------------------------------------------|
 * |__________ot_len_________________|      option_list             |
 * |                                                                |
 * |-----------------------------------------------------------------
 *
 * format of flags:
 * | 0 1  2 3 4|
 * -------------
 * |cp|cr| rsv |
 * -------------
 *
 * format of proto:
 * |0  1  2 3 4 5 6 7|
 * -------------------
 * |d|p2p|  protocol |
 * -------------------
 *
 * format of option element:
 * |0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 ......|
 * ------------------------------------------------------------------------
 * |     otype     |     olen      |               ovalue                 |
 * ------------------------------------------------------------------------
 */

struct mesh_header_option_format
{
    uint8_t otype;           // option type
    uint8_t olen;            // current option length
    uint8_t ovalue[0];       // option value
} __packed;

struct mesh_header_option_header_type
{
    uint16_t ot_len;        // option total length;
    struct mesh_header_option_format olist[0];   // option list
} __packed;

struct mesh_header_option_frag_format
{
    uint16_t id;            // identify of fragment
    struct
    {
        uint16_t resv :1;    // reserve for future
        uint16_t mf :1;      // more fragment
        uint16_t idx :14;    // fragment offset;
    } offset;
} __packed;

struct mesh_header_format
{
    uint8_t ver :2;          // version of mesh
    uint8_t oe :1;          // option exist flag
    uint8_t cp :1;          // piggyback local flow permit in packet
    uint8_t cr :1;          // piggyback local flow request in packet
    uint8_t ocp :1;         // piggyback online flow permit in packet
    uint8_t ocr :1;         // piggyback online flow request in packet
    uint8_t rsv :1;          // reserve for future;
    struct
    {
        uint8_t d :1;      // direction, 1:upwards, 0:downwards
        uint8_t p2p :1;      // node to node packet
        uint8_t protocol :6; // protocol used by user data;
    } proto;
    uint16_t len;           // packet total length (include mesh header)
    uint8_t dst_addr[MESH_HWADDR_LEN];  // destiny address
    uint8_t src_addr[MESH_HWADDR_LEN];  // source address
    uint32_t seq :29;
    uint32_t f :1;
    uint32_t m :1;
    uint32_t e :1;
    uint32_t ack :30;
    uint32_t a :1;
    uint32_t c :1;
    struct mesh_header_option_header_type option[0];  // mesh option
} __packed;

struct mesh_scan_para_type
{
    esp32_mesh_usr_callback_t usr_scan_cb; // scan done callback
    uint8_t grp_id[MESH_GRP_ID_LEN];  // group id
    bool grp_set;                           // group set
};

enum mesh_option_type
{
    M_O_CONGEST_REQ = 0,      // local flow request option
    M_O_CONGEST_RESP,         // flow response option
    M_O_ROUTER_SPREAD,        // router information spread option
    M_O_ROUTE_ADD,            // route table update (node joins mesh) option
    M_O_ROUTE_DEL,            // route table update (node leaves mesh) option
    M_O_TOPO_REQ,             // topology request option
    M_O_TOPO_RESP,            // topology response option
    M_O_MCAST_GRP,            // group list of mcast
    M_O_MESH_FRAG,            // mesh management fragment option
    M_O_USR_FRAG,             // user data fragment
    M_O_USR_OPTION,           // user option
    M_O_CONGEST_OREQ,         // online flow request option
    M_O_ROUTER_RS,            // router RSSI solicit
    M_O_ROUTER_RI,            // router RSSI information
    M_O_ROUTER_RA,            // router RSSI advertisement
    M_O_INVALID = 0xFFFF      // invalid option type
};

enum mesh_usr_proto_type
{
    M_PROTO_NONE = 0,       // used to delivery mesh management packet
    M_PROTO_HTTP,           // user data formated with HTTP protocol
    M_PROTO_JSON,           // user data formated with JSON protocol
    M_PROTO_MQTT,           // user data formated with MQTT protocol
    M_PROTO_BIN,            // user data is binary stream
};

struct mesh_sub_node_info_t
{
    uint16_t sub_count;
    uint8_t mac[MESH_HWADDR_LEN];
} __packed;

void * esp32_mesh_create_packet(void *dst_addr, void *src_addr,
        enum mesh_usr_proto_type proto, uint16_t data_len, bool option,
        uint16_t ot_len);
void * esp32_mesh_create_option(uint8_t otype, void *ovalue, uint8_t val_len);
void * esp32_mesh_get_usr_context();
bool esp32_mesh_add_option(struct mesh_header_format *head,
        struct mesh_header_option_format *option);
bool esp32_mesh_get_option(struct mesh_header_format *head,
        enum mesh_option_type otype, uint16_t oidx,
        struct mesh_header_option_format **option);
bool esp32_mesh_get_usr_data(struct mesh_header_format *head, void **usr_data,
        uint16_t *data_len);
bool esp32_mesh_set_usr_data(struct mesh_header_format *head, void *usr_data,
        uint16_t data_len);
bool esp32_mesh_get_src_addr(struct mesh_header_format *head, void **src_addr);
bool esp32_mesh_get_dst_addr(struct mesh_header_format *head, void **dst_addr);
bool esp32_mesh_set_src_addr(struct mesh_header_format *head, void *src_addr);
bool esp32_mesh_set_dst_addr(struct mesh_header_format *head, void *dst_addr);
bool esp32_mesh_get_usr_data_proto(struct mesh_header_format *head,
        enum mesh_usr_proto_type *proto);
bool esp32_mesh_set_usr_data_proto(struct mesh_header_format *head,
        enum mesh_usr_proto_type proto);
bool esp32_mesh_is_root();
bool esp32_mesh_is_root_candidate();
bool esp32_mesh_get_node_info(enum mesh_node_t type, void **info,
        uint16_t *count);
bool esp32_mesh_get_router(wifi_sta_config_t *router);
bool esp32_mesh_set_router(wifi_sta_config_t *router);
bool esp32_mesh_encrypt_init(wifi_auth_mode_t mode, void *passwd,
        uint8_t pw_len);
bool esp32_mesh_group_id_init(void *grp_id, uint16_t gid_len);
bool esp32_mesh_regist_rebuild_fail_cb(esp32_mesh_usr_callback_t cb);
bool esp32_mesh_regist_usr_cb(esp32_mesh_usr_callback_t cb);
bool esp32_mesh_server_init(ip_addr_t *ip, uint16_t port);
bool esp32_mesh_set_max_hops(uint8_t max_hops);
bool esp32_mesh_set_scan_retries(uint8_t retries);
bool esp32_mesh_set_rssi_threshold(int8_t threshold);
bool esp32_mesh_set_policy(bool policy);
bool esp32_mesh_set_wifi_retry_delay(uint16_t time_ms);

int8_t esp32_mesh_get_status();
int esp32_mesh_send(void *buf, uint16_t len, uint32_t tick);
int esp32_mesh_recv(void *buf, uint16_t len, uint32_t tick);

uint8_t esp32_mesh_get_max_hops();
uint8_t esp32_mesh_get_hop();

uint16_t esp32_mesh_get_sub_dev_count();

bool esp32_mesh_is_enabled();
bool esp32_mesh_enable(esp32_mesh_op_callback_t enable_cb, enum mesh_type type);
bool esp32_mesh_disable(esp32_mesh_op_callback_t disable_cb);
void esp32_mesh_deauth_all();
void esp32_mesh_deauth_child(int8_t cidx);
void esp32_mesh_disp_route_table();
void esp32_mesh_get_parent_mac(void *mac);
void esp32_mesh_print_status(uint8_t qidx);
void esp32_mesh_print_ver();
void esp32_mesh_release_congest();
void esp32_mesh_scan(struct mesh_scan_para_type *para);

#endif
