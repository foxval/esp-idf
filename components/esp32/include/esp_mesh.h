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

#ifndef __ESP_MESH_H__
#define __ESP_MESH_H__

#include "esp_err.h"
#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include "esp_wifi_internal.h"

/*******************************************************
 *                Constants
 *******************************************************/

#define MESH_VERSION                  (5)    /**< mesh version */
#define MESH_ROOT_LAYER               (1)    /**< root layer */
#define MESH_SCAN_RETRIES             (32)   /**< scan retries */

/* mesh error code */
#define MESH_ERR_NOT_INIT             (-2)    /**< mesh not initialized */
#define MESH_ERR_NOT_CFG              (-3)    /**< mesh not configured */
#define MESH_ERR_NOT_START            (-4)    /**< mesh not start */
#define MESH_ERR_MEM                  (-5)    /**< no memory */
#define MESH_ERR_TIMEOUT              (-6)    /**< timeout */
#define MESH_ERR_QUEUE_FULL           (-7)    /**< queue full */
#define MESH_ERR_IF                   (-8)    /**< error interface */
#define MESH_ERR_ROUTE                (-9)    /**< error route */
#define MESH_ERR_BUF_LIMIT            (-10)   /**< buffer limited */
#define MESH_ERR_OPT_NONE             (-11)   /**< no option */
#define MESH_ERR_OPT_UNKNOWN          (-12)   /**< unknown option */
#define MESH_ERR_DISCARD              (-13)   /**< discard packet */
#define MESH_ERR_DISCONNECTED         (-14)   /**< leaves mesh network */
#define MESH_ERR_WIFI_MODE            (-15)   /**< error mode */
#define MESH_ERR_ARG                  (-16)   /**< error input argument */
#define MESH_ERR_QUEUE_FAIL           (-17)   /**< queue fail */
#define MESH_ERR_DISCARD_DUP          (-18)   /**< discard duplicate sequence number */
#define MESH_ERR_NOT_ALLOWED          (-19)   /**< not allowed */

/*******************************************************
 *                Enumerations
 *******************************************************/

/* event represents mesh network state */
typedef enum {
    MESH_EVENT_NO_AP_FOUND = 1, /**< no mesh AP found */
    MESH_EVENT_CONNECTED = 2, /**< joins the mesh network */
    MESH_EVENT_DISCONNECTED = 3, /**< leaves the mesh network */
    MESH_EVENT_LAYER_CHANGE = 4, /**< layer change */
    MESH_EVENT_ROOT_GOT_IP = 5, /**< root obtains IP address */
    MESH_EVENT_VOTE_START = 6, /**< mesh vote starts */
    MESH_EVENT_VOTE_DONE = 7,/**< mesh vote is over */
    MESH_EVENT_ROOT_SWITCH_REQ = 8,/**< root switch request */
    MESH_EVENT_ROOT_SWITCH_ACK = 9,/**< root switch acknowledgment */
    MESH_EVENT_TODS_REACHABLE = 10, /**< IP remote address is reached */
    MESH_EVENT_TODS_UNREACHABLE = 11, /**< IP remote address is unreachable */
    MESH_EVENT_FAIL,
} mesh_event_t;

/* node type over mesh network */
typedef enum {
    MESH_IDLE, /**< out of mesh network */
    MESH_ROOT, /**< the only sink of mesh network, has the ability to access to IP network */
    MESH_NODE, /**< intermediate node, has the ability to forward packets over mesh network */
    MESH_LEAF, /**< has no forward ability */
} mesh_type_t;

/* flags used with send and receive */
enum {
    MESH_DATA_ENC = (1), /**< data encrypted(not implemented yet) */
    MESH_DATA_P2P = (1 << 1), /**< point-to-point delivery over mesh network */
    MESH_DATA_FROMDS = (1 << 2), /**< receive from an IP remote address */
    MESH_DATA_TODS = (1 << 3), /**< send to an IP remote address */
};

/* protocol of transmission data */
typedef enum {
    MESH_PROTO_BIN = 0, /**< binary */
    MESH_PROTO_HTTP = 1, /**< http protocol */
    MESH_PROTO_JSON = 2, /**< json format */
    MESH_PROTO_MQTT = 3, /**< mqtt protocol */
} mesh_proto_t;

/* for reliable transmission, mesh network provides three type of services */
typedef enum {
    MESH_TOS_DEF = 0, /**< default */
    MESH_TOS_P2P = 1, /**< best effort for P2P(point-to-point) delivery */
    MESH_TOS_E2E = 2, /**< best effort for E2E(end-to-end) delivery(not implemented yet)*/
} mesh_tos_t;

/* option type for send and receive */
enum {
    MESH_OPT_MCAST_GROUP = 7, /**< group communication */
    MESH_OPT_RECV_DS_ADDR = 8, /**< request an IP remote address */
};

/*******************************************************
 *                Type Definitions
 *******************************************************/
typedef void (*mesh_event_cb_t)(mesh_event_t event);

/*******************************************************
 *                Structures
 *******************************************************/
typedef struct {
    uint8_t addr[6];
} mesh_addr_t;

typedef struct {
    uint8_t type; /**< option type */
    uint16_t len; /**< option length */
    uint8_t *val; /**< option value */
} __attribute__((packed)) mesh_opt_t;

typedef struct {
    uint8_t *data; /**< data */
    uint16_t size; /**< data size */
    mesh_proto_t proto; /**< data protocol */
    mesh_tos_t tos; /**< data type of service */
} mesh_data_t;

typedef struct {
    uint8_t ssid[32]; /**< SSID */
    uint8_t bssid[6]; /**< BSSID, if router is hidden, this value is mandatory */
    uint8_t password[64]; /**< password */
    uint8_t ssid_len; /**< length of SSID */
    uint8_t channel; /**< channel of router*/
} mesh_router_t;

typedef struct {
    mesh_event_cb_t event_cb;
    mesh_addr_t mesh_id;
    mesh_router_t router;
    struct {
        uint8_t password[64]; /**< mesh AP password */
        uint8_t max_connection; /**< max number of stations allowed to connect in, max 6 */
    } map;
} mesh_cfg_t;

typedef struct {
    int attempts;
    mesh_addr_t rc_addr;
} mesh_vote_t;

/*******************************************************
 *                Function Definitions
 *******************************************************/
/**
 * @brief     mesh initialization
 *
 * @param     void
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */

esp_err_t esp_mesh_init(void);

/**
 * @brief     mesh deinitialization
 *
 * @param     void
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */

esp_err_t esp_mesh_deinit(void);

/**
 * @brief     start mesh
 *
 * @param     none
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */

esp_err_t esp_mesh_start(void);

/**
 * @brief     stop mesh
 *
 * @param     none
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */

esp_err_t esp_mesh_stop(void);

/**
 * @brief     send a packet over mesh network
 *
 * @param     to  the address of the final destination of the packet
 *            if to a IP server address, use IP address and port to represent.
 *            For example, 192.168.0.1:8080 -->C0A800011F90
 * @param     data  pointer to a sending mesh packet
 * @param     flag  currently support MESH_DATA_P2P, MESH_DATA_TODS
 *            must specify one of MESH_DATA_P2P and MESH_DATA_TODS
 * @param     opt  options
 * @param     opt_count  option count
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 *
 */
esp_err_t esp_mesh_send(const mesh_addr_t *to, const mesh_data_t *data,
                        int flag, mesh_opt_t opt[], int opt_count);

/**
 * @brief     receive a packet target to self over mesh network
 *
 * @param     from  the address of the original source of the packet
 * @param     data  pointer to the receiving mesh packet
 * @param     timeout_ms  wait time
 * @param     flag  currently support MESH_DATA_P2P
 * @param     opt  options desired to receive
 * @param     opt_count  option count desired to receive
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 *
 */
esp_err_t esp_mesh_recv(mesh_addr_t *from, mesh_data_t *data, int timeout_ms,
                        int *flag, mesh_opt_t opt[], int opt_count);

/**
 * @brief     receive a packet target to an IP remote address(only apply to root)
 *            root uses this API to receive packets destined to an IP remote address from mesh network.
 *            only root has the ability to forward packets to an IP remote address over IP network.
 *
 * @param     from  the address of the original source of the packet
 * @param     to  the IP remote address of packet is destined to
 * @param     data  pointer to the receiving packet
 * @param     timeout_ms  wait time
 * @param     flag  currently support MESH_DATA_P2P and MESH_DATA_FROMDS
 * @param     opt  options desired to receive
 * @param     opt_count  option count desired to receive
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 *
 */
esp_err_t esp_mesh_recv_toDS(mesh_addr_t *from, mesh_addr_t *to,
                             mesh_data_t *data, int timeout_ms, int *flag, mesh_opt_t opt[],
                             int opt_count);

/**
 * @brief     set mesh network configuration
 *
 * @param     config  pointer to mesh network configuration
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_set_config(const mesh_cfg_t *config);

/**
 * @brief     get mesh network configuration
 *
 * @param     config  pointer to mesh network configuration
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_get_config(mesh_cfg_t *config);

/**
 * @brief     set mesh network router
 *
 * @param     router  pointer to mesh network router
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_set_router(const mesh_router_t *router);

/**
 * @brief     get mesh network router
 *
 * @param     router  pointer to mesh network router
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_get_router(mesh_router_t *router);

/**
 * @brief     set mesh network ID
 *
 * @param     id  pointer to mesh network ID
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_set_id(mesh_addr_t *id);

/**
 * @brief     get mesh network ID
 *
 * @param     id  pointer to mesh network ID
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_get_id(mesh_addr_t *id);

/**
 * @brief     set node type over mesh network(not implemented yet)
 *
 * @param     type  node type
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_set_type(mesh_type_t type);

/**
 * @brief     get node type over mesh network
 *
 * @param     void
 *
 * @return    mesh type
 *
 */
mesh_type_t esp_mesh_get_type(void);

/**
 * @brief     set max layer of mesh network
 *
 * @param     max_layer  max layer value
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_set_max_layer(int max_layer);

/**
 * @brief     get max layer of mesh network
 *
 * @param     void
 *
 * @return    max layer value
 *
 */
int esp_mesh_get_max_layer(void);

/**
 * @brief     set mesh AP password
 *
 * @param     pwd  pointer to the password
 * @param     len  password length
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_set_map_password(const uint8_t *pwd, int len);

/**
 * @brief     set mesh AP authentication mode value
 *
 * @param     mode  authentication mode
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_set_map_authmode(wifi_auth_mode_t authmode);

/**
 * @brief     get mesh AP authentication mode value
 *
 * @param     void
 *
 * @return    authentication mode
 *
 */

wifi_auth_mode_t esp_mesh_get_map_authmode(void);

/**
 * @brief     set mesh AP max connection value
 *
 * @param     connections  max connection value
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_set_map_connections(int connections);

/**
 * @brief     get mesh AP max connection value
 *
 * @param     void
 *
 * @return    max connection value
 *
 */
int esp_mesh_get_map_connections(void);

/**
 * @brief     set mesh AP beacon interval(not implemented yet)
 *
 * @param     interval  beacon interval(ms)
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_set_beacon_interval(int interval);

/**
 * @brief     get mesh AP beacon interval
 *
 * @param     void
 *
 * @return    beacon interval(ms)
 *
 */
int esp_mesh_get_beacon_interval(void);

/**
 * @brief     get current layer value
 *
 * @param     void
 *
 * @return    layer value
 *
 */
int esp_mesh_get_layer(void);

/**
 * @brief     get node parent BSSID over mesh network
 *
 * @param     bssid  pointer to parent BSSID
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_get_parent_bssid(mesh_addr_t *bssid);

/**
 * @brief     return if the node is root
 *
 * @param     void
 *
 * @return    true/false
 *
 */
bool esp_mesh_is_root(void);

/**
 * @brief     set if enable/disable mesh self-organized, self-organized by default
 *
 * @param     enable
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */

esp_err_t esp_mesh_set_self_organized(bool enable);

/**
 * @brief     return if mesh self-organized is enabled/disabled
 *
 * @param     void
 *
 * @return    true/false
 *
 */
bool esp_mesh_get_self_organized(void);

/**
 * @brief     set a specified parent for node over mesh network(not fully implemented yet)
 *
 * @param     config  parent configuration
 * @param     mesh_ie  parent mesh ie
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_set_parent(wifi_config_t *config,
                              wifi_vnd_mesh_assoc_t *mesh_ie);

/**
 * @brief     root waive itself
 *
 * @param     vote  vote configuration
 * @param     reason (not fully implemented yet, default:0 initialized by root)
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_waive_root(mesh_vote_t *vote, int reason);

/**
 * @brief     set vote percentage threshold for approval of being a root
 *
 * @param     percentage  vote percentage threshold
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_set_vote_percentage(float percentage);

/**
 * @brief     get vote percentage threshold for approval of being a root
 *
 * @param     void
 *
 * @return    percentage threshold
 */
float esp_mesh_get_vote_percentage(void);

typedef struct {
    int scan;
    int vote;
    int fail;
    int monitor_ie;
} mesh_attempts_t;

/**
 * @brief    set attempts for mesh self-organized networking
 *
 * @param    attempts
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_set_attempts(mesh_attempts_t *attempts);

/**
 * @brief    get attempts for mesh self-organized networking
 *
 * @param    attempts
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_get_attempts(mesh_attempts_t *attempts);

/**
 * @brief     set mesh AP associate expired time
 *
 * @param     seconds
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_set_map_assoc_expire(int seconds);

/**
 * @brief     get mesh AP associate expired time
 *
 * @param     void
 *
 * @return    seconds
 */
int esp_mesh_get_map_assoc_expire(void);

/**
 * @brief     get total number of nodes over mesh network(including root)
 *
 * @param     void
 *
 * @return    total number of nodes(including root)
 */
int esp_mesh_get_total_node_num(void);

/**
 * @brief     get the number of nodes in routing table(including self)
 *
 * @param     void
 *
 * @return    the number of nodes in routing table(including self)
 */
int esp_mesh_get_routing_table_size(void);

/**
 * @brief     get routing table(including itself)
 *
 * @param     mac  pointer to routing table
 * @param     len  routing table size(in bytes)
 * @param     num  pointer to the number of nodes in routing table(including itself)
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_get_routing_table(mesh_addr_t *mac, int len, int *size);

/**
 * @brief     post the toDS state to mesh network(only apply to root)
 *            this state represents if root has reached an IP remote address.
 *
 * @param     reachable
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_post_toDS_state(bool reachable);

/**
 * @brief     set rssi threshold
 *
 * @param     rssi  rssi threshold
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_set_rssi_threshold(int rssi);

/**
 * @brief     get rssi threshold
 *
 * @param     void
 *
 * @return    rssi threshold
 */
int esp_mesh_get_rssi_threshold(void);

typedef struct {
    int duration_ms; /* parent monitor duration */
    int cnx_rssi; /* threshold for keeping a good connection */
    int select_rssi; /* threshold for parent selection, should be a value greater than switch_rssi*/
    int switch_rssi; /* threshold for action to reselect a better parent */
    int backoff_rssi; /* threshold for connecting to the root */
} mesh_switch_parent_t;

/**
 * @brief     set parameters for parent switch
 *
 * @param     paras
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_set_switch_parent_paras(mesh_switch_parent_t *paras);

/**
 * @brief     get parameters for parent switch
 *
 * @param     paras
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_get_switch_parent_paras(mesh_switch_parent_t *paras);

typedef struct {
    int recv; /** queue size for esp_mesh_recv(), default:36(max:60) */
    int send; /** queue size for mesh send, default:72(max:100) */
    int toDS; /** queue size for esp_mesh_recv_toDS(), default:72(max:100) */
} mesh_cfg_qsize_t;

/**
 * @brief     set queue size(must be called before esp_mesh_start())
 *
 * @param     qsize
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_set_qsize(mesh_cfg_qsize_t *qsize);

/**
 * @brief     get queue size
 *
 * @param     qsize
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_get_qsize(mesh_cfg_qsize_t *qsize);

/**
 * @brief     return the number of upQ for a specified address
 *
 * @param     addr
 * @param     xseqno_in
 *
 * @return    the number of upQ for a specified address
 */
int esp_mesh_available_txupQ_num(mesh_addr_t *addr, uint32_t *xseqno_in);

/**
 * @brief     print the number of txQ waiting
 *
 * @param     void
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_print_txQ_waiting(void);

/**
 * @brief     print the number of rxQ waiting
 *
 * @param     void
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_print_rxQ_waiting(void);

#endif /* __ESP_MESH_H__ */
