#ifndef __MESH_PARENT_H__
#define __MESH_PARENT_H__

#include "mesh.h"
#include "mesh_common.h"
#include "mesh_config.h"

#define MESH_NODE_TYPE_ROOT    (0)
#define MESH_NODE_TYPE_IDLE    (0)
#define MESH_NODE_TYPE_NODE    (0)
#define MESH_NODE_TYPE_LEAF    (0)

enum mesh_fsm_op_t {
    MESH_SCAN_REQ = 0x01,
    MESH_SCAN_DONE,
    MESH_SAVE_ROUTER,
    MESH_SEL_PARENT,
    MESH_CONN_SERVER,
    MESH_SPREAD_ROUTE,
    MESH_ENABLE_DONE,
    MESH_FSM_OP_MAX,
    MESH_FSM_DESTROY,
};

struct mesh_conn_info_t {
    uint8_t mac[MESH_HWADDR_LEN];
    uint8_t used:1;
    uint8_t stop:1;
    uint8_t oreq:1;
    uint8_t lreq:1;
    uint8_t ocapa:2;
    uint8_t lcapa:2;
};

struct mesh_ctx_t {
    /*
     * conn_info[0 ~ ESP_MESH_CONNECT_MAX - 1] used for child nodes
     * conn_info[ESP_MESH_CONNECT_MAX] used to save the WiFi connect information for STA
     */
    struct mesh_conn_info_t conn_info[ESP_MESH_CONNECT_MAX + 1];
    uint8_t init;
};

bool esp32_mesh_ctx_init(struct mesh_ctx_t *ctx);
bool esp32_mesh_ctx_deinit(struct mesh_ctx_t *ctx);
bool es32_mesh_get_child_mac(int8_t cidx, void *mac);
uint8_t es32_mesh_get_child_count();
int8_t es32_mesh_get_child_idx(void *mac);
uint16_t es32_mesh_get_sub_dev_count();
void mesh_init_wifi(void);
bool mesh_fsm_task_init(void);
esp_err_t mesh_event_cb(void *ctx, system_event_t *event);
void esp32_mesh_event_set_cb(system_event_cb_t event_cb);

#endif
