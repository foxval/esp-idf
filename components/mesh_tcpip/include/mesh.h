// Copyright 2015-2017 Espressif Systems (Shanghai) PTE LTD
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

#ifndef __MESH_H__
#define __MESH_H__

#include "mesh_common.h"

/*******************************************************
 *                Constants
 *******************************************************/

#define MESH_VERSION                  (4)
#define MESH_MAX_CONNECTIONS          (6)
#define MESH_MAX_LAYER                (5)
#define MESH_ROOT_LAYER               (1)
#define MESH_CIDX_INVALID             (-1)
#define MESH_CIDX_VALID(cidx)         ((cidx) >=0 && (cidx) < MESH_MAX_CONNECTIONS)
#define MESH_SCAN_RETRIES             (32)

#define MESH_HLEN                     (sizeof(mesh_hdr_t))  /**> fix header size (in bytes) */
#define MESH_MTU                      (1500)                /**> maximum transfer unit (in bytes) */
#define MESH_MPS                      (MESH_MTU-MESH_HLEN)  /**> maximum payload size (in bytes) */

/* mesh error code */
#define MESH_ERR_NOT_CFG              (-1)
#define MESH_ERR_NO_DATA              (-2)
#define MESH_ERR_NO_MEM               (-3)
#define MESH_ERR_TIMEOUT              (-4)
#define MESH_ERR_QUEUE                (-5)
#define MESH_ERR_NO_IF                (-6)
#define MESH_ERR_NO_CTX               (-7)
#define MESH_ERR_NOT_SUPPORT          (-8)
#define MESH_ERR_NO_PATH              (-9)
#define MESH_ERR_BUF_LIMIT            (-10)
#define MESH_ERR_NO_OP                (-11)
#define MESH_MCAST_NO_TYPE            (-12)
#define MESH_MCAST_NO_ELEM            (-13)
#define MESH_NO_CHILD                 (-14)
#define MESH_DISCARD                  (-15)

/*******************************************************
 *                Enumerations
 *******************************************************/

typedef enum
{
    MESH_EVENT_SUCCESS = 0,
    MESH_EVENT_NO_AP_FOUND = 1,
    MESH_EVENT_CONNECTED = 2,
    MESH_EVENT_DISCONNECTED = 3,
    MESH_EVENT_LAYER_CHANGE = 4,
    MESH_EVENT_ROOT_GOT_IP = 5,
    MESH_EVENT_FAIL,
} mesh_event_t;

typedef enum
{
    MESH_ROOT, MESH_NODE, MESH_LEAF,
} mesh_type_t;

/* Flags used with send and receive */
enum
{
    MESH_DATA_ENC = (1), /**< data encrypted */
    MESH_DATA_P2P = (1 << 1), /**< P2P */
    MESH_DATA_FROMDS = (1 << 2), /**< from DS */
    MESH_DATA_TODS = (1 << 3), /**< to DS */
};

typedef enum
{
    MESH_PROTO_BIN = 0, /**< binary data */
    MESH_PROTO_HTTP = 1, /**< http protocol */
    MESH_PROTO_JSON = 2, /**< json format */
    MESH_PROTO_MQTT = 3, /**< mqtt protocol */
} mesh_proto_t;

typedef enum
{
    MESH_TOS_DEF = 0, /**< default */
    MESH_TOS_P2P = 1, /**< Best effort for P2P(point 2 point) delivery */
    MESH_TOS_E2E = 2, /**< Best effort for E2E(end 2 end) delivery */
} mesh_tos_t;

/* option type */
enum
{
    MESH_OPT_MCAST_GROUP = 7, /**< multicast group */
};

/*******************************************************
 *                Type Definitions
 *******************************************************/
typedef void (*mesh_event_cb_t)(mesh_event_t event);

/*******************************************************
 *                Structures
 *******************************************************/
typedef struct
{
    uint8_t addr[6];
} mesh_addr_t;

typedef struct
{
    uint8_t type; /**< option type */
    uint8_t len; /**< option length */
    uint8_t *val; /**< option value */
} mesh_opt_t;

/* mesh header format:
 * _________________________________________________________________________
 |byte\bit|0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7|
 |------------------------------------------------------------------------|
 |   4    | ver  | flags | header length |         total length           |   
 |--------|---------------------------------------------------------------|   
 |   8    | flow |  TTL  |TOS| protocol  |         reserved               |
 |--------|---------------------------------------------------------------|
 |   12   |                  destination address                          |
 |--------|                              |--------------------------------|
 |   16   |                              |                                |
 |--------|------------------------------|                                |
 |   20   |                     source address                            |
 |--------|---------------------------------------------------------------|
 |   24   | frag |               sequence                                 |
 |--------|---------------------------------------------------------------|
 |   28   |                        ack                                    |
 |--------|---------------------------------------------------------------|
 |        |                       options                                 |
 |--------|---------------------------------------------------------------|
 
 format of flags:
 ____________________
 | 0  | 1  | 2  | 3  |
 |-------------------|
 |frDs|toDs|ENC | MF |
 |-------------------|
 
 format of flow:
 ____________________
 | 0  | 1    2    3  |
 |-------------------|
 |xreq|    xrsp      |
 |-------------------|
 
 *
 */

typedef struct
{
    uint8_t ver :4; /**< version */
    uint8_t frDS :1; /**< from DS */
    uint8_t toDS :1; /**< to DS */
    uint8_t ENC :1; /**< encrypt */
    uint8_t MF :1; /**< more fragment */
    uint8_t hlen; /**< header length */
    uint16_t tolen; /**< total length */
    uint8_t xreq :1; /**< flow control request */
    uint8_t xrsp :3; /**< flow control response */
    uint8_t ttl :4; /**< time to live */
    uint8_t tos :2; /**< type of service */
    uint8_t proto :6; /**< data protocol */
    uint16_t reserved; /**< reserved */
    mesh_addr_t dst; /**< destination address, final recipient */
    mesh_addr_t src; /**< source address */
    uint32_t frag :4; /**< fragment number */
    uint32_t seq :28; /**< sequence number */
    uint32_t ack :32; /**< acknowledgment number */
    mesh_opt_t option[0]; /**< mesh options */
} mesh_hdr_t;

typedef struct
{
    uint8_t* buf;
    uint16_t len;
    mesh_addr_t ra;
    mesh_addr_t ta;
    uint8_t ifidx;
    uint32_t lifetime;
    uint32_t wait;
} mesh_ctx_t;

typedef struct
{
    uint8_t* data; /**< data */
    uint16_t size; /**< data size */
    uint8_t proto; /**< data protocol */
    uint8_t tos; /**< data type of service */
} mesh_data_t;

typedef struct
{
    uint8_t ssid[32]; /**< SSID */
    uint8_t password[64]; /**< password */
    uint8_t ssid_len; /**< length of SSID */
    uint8_t channel; /**< channel of router*/
} mesh_router_t;

typedef struct
{
    mesh_event_cb_t event_cb;
    mesh_addr_t mesh_id;
    mesh_router_t router;
    struct
    {
        uint8_t password[64]; /**< mesh AP password */
        uint8_t max_connection; /**< max number of stations allowed to connect in, default 4, max 10 */
    } map;
} mesh_cfg_t;

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
 * @brief     send a mesh packet
 *
 * @param     to  the address of the final destination of the packet
 * @param     data  pointer to a sending mesh packet
 * @param     flag  currently, support MESH_DATA_ENC,  MESH_DATA_P2P,
 *                  MESH_DATA_FROMDS, MESH_DATA_TODS
 * @param     option  pointer to options
 * @param     opt_count  option count
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 *
 */
esp_err_t esp_mesh_send(const mesh_addr_t* to, const mesh_data_t* data,
        int flag, mesh_opt_t* option[], int opt_count);

/**
 * @brief     receive a mesh packet
 *
 * @param     from  the address of the original source of the packet
 * @param     data  pointer to the receiving mesh packet
 * @param     timeout_ms  wait time
 * @param     flag  currently, support MESH_DATA_ENC,  MESH_DATA_P2P,
 *                  MESH_DATA_FROMDS, MESH_DATA_TODS
 * @param     mcnx  reserved
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 *
 */
esp_err_t esp_mesh_recv(mesh_addr_t* from, mesh_data_t* data, int timeout_ms,
        int *flag, void* mcnx);

/**
 * @brief     set mesh configuration
 *
 * @param     config  pointer to mesh configuration
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_set_config(const mesh_cfg_t* config);

/**
 * @brief     get mesh configuration
 *
 * @param     config  pointer to mesh configuration
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_get_config(mesh_cfg_t* config);

/**
 * @brief     set mesh router
 *
 * @param     router  pointer to mesh router
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_set_router(const mesh_router_t* router);

/**
 * @brief     get mesh router
 *
 * @param     router  pointer to mesh router
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_get_router(mesh_router_t* router);

/**
 * @brief     set mesh ID
 *
 * @param     id  pointer to mesh ID
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_set_id(mesh_addr_t* id);

/**
 * @brief     get mesh ID
 *
 * @param     id  pointer to mesh ID
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_get_id(mesh_addr_t* id);

/**
 * @brief     set mesh type(not supported now)
 *
 * @param     type  mesh type
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_set_type(mesh_type_t type);

/**
 * @brief     get mesh type
 *
 * @param     void
 *
 * @return    mesh type
 *
 */
mesh_type_t esp_mesh_get_type(void);

/**
 * @brief     set max layer value
 *
 * @param     type  max layer value
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_set_max_layer(int max_layer);

/**
 * @brief     get mesh type
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
esp_err_t esp_mesh_set_map_password(const uint8_t* pwd, int len);

/**
 * @brief     set mesh AP max connections value
 *
 * @param     connections  max connections value
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_set_map_connections(int connections);

/**
 * @brief     get mesh AP max connections value
 *
 * @param     void
 *
 * @return    max connections value
 *
 */
int esp_mesh_get_map_connections(void);

/**
 * @brief     set mesh AP beacon interval(not support now)
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
 * @brief     get parent BSSID
 *
 * @param     bssid  pointer to BSSID
 *
 * @return
 *    - ESP_OK: succeed
 *    - ESP_FAIL: failed
 */
esp_err_t esp_mesh_get_parent_bssid(mesh_addr_t* bssid);

/**
 * @brief     if is root
 *
 * @param     void
 *
 * @return    true/false
 *
 */
bool esp_mesh_is_root(void);

#endif /* __MESH_H__ */
