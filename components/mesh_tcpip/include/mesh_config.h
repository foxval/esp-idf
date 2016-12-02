#ifndef __MESH_CONFIG_H__
#define __MESH_CONFIG_H__

#include "mesh_parent.h"
#include "mesh_common.h"

/***************** mesh configure **************************************/
#define MESH_DEFAULT_TASK_PRI              (3)
#define MESH_DEFAULT_SCAN_RETRIES          (3)
#define MESH_DEFAULT_NO_AP_RETRIES         (3)
#define MESH_DEFAULT_MAX_HOP               (10)
#define MESH_PARENT_FACTOR                 (10)
#define MESH_ASSOC_FACTOR                  (3)
/***********************************************************************/

/***************** namespace and key used in mesh **********************/
#define MESH_NVS_NAMESPACE                 "MESH"
#define MESH_NVS_KEY_ROUTER_NAME           "ROUTER"
#define MESH_NVS_KEY_VER_NAME              "VERSION"
#define MESH_NVS_KEY_ROOT_NAME             "ROOT"
#define MESH_NVS_KEY_GRP_ID_NAME           "GRPID"
#define MESH_NVS_KEY_ROUTER_RSSI_NAME      "RSSI"
#define MESH_NVS_KEY_LHOP_NAME             "LHOP"
#define MESH_NVS_KEY_MHOP_NAME             "MHOP"
#define MESH_NVS_KEY_ENCRYPT_NAME          "ENCRYPT"
#define MESH_NVS_KEY_RSSI_TH_NAME          "RSSITH"
#define MESH_NVS_KEY_SERVER_INFO_NAME      "SERVER"
/***********************************************************************/

/***************** MESH SAVE TASK **************************************/
#define MESH_SAVE_TASK_NAME                "MNVS"
#define MESH_SAVE_TASK_HEAP                (1024)
#define MESH_SAVE_TASK_PRI                 (MESH_DEFAULT_TASK_PRI)
/***********************************************************************/

/***************** MESH FSM TASK***********************************/
#define MESH_FSM_TASK_NAME                 "MFSM"
#define MESH_FSM_TASK_HEAP                 (1024)
#define MESH_FSM_TASK_PRI                  (MESH_DEFAULT_TASK_PRI + 1)
/***********************************************************************/

/***************** mesh save task **************************************/
#define MESH_RX_TASK_NAME                  "MRX"
#define MESH_RX_TASK_HEAP                  (4096)
#define MESH_RX_TASK_PRI                   (MESH_DEFAULT_TASK_PRI + 1)
/***********************************************************************/

/***************** MESH TCPIP RX TASK***********************************/
#define MESH_TCPIP_RX_TASK_NAME            "MTRX"
#define MESH_TCPIP_RX_TASK_HEAP            (1024)
#define MESH_TCPIP_RX_TASK_PRI             (MESH_DEFAULT_TASK_PRI + 1)
/***********************************************************************/

/***************** MESH TCPIP TX TASK***********************************/
#define MESH_TCPIP_TX_TASK_NAME            "MTTX"
#define MESH_TCPIP_TX_TASK_HEAP            (1024)
#define MESH_TCPIP_TX_TASK_PRI             (MESH_DEFAULT_TASK_PRI + 1)
/***********************************************************************/

/***************** mesh version ****************************************/
#define MESH_VER_LEN                       (8)
extern char g_mesh_version[MESH_VER_LEN];
/***********************************************************************/

/***************** mesh save task operation*****************************/
enum MESH_NVS_OPERATE {
    MESH_WRITE_ROUTER = 0x01,      // router AP information
    MESH_READ_ROUTER,
    MESH_WRITE_VERSION,            // mesh version
    MESH_READ_VERSION,
    MESH_WRITE_ROOT,               // as root flag
    MESH_READ_ROOT,
    MESH_WRITE_ROOT_ROUTER,        // router AP & as root flag (WR)
    MESH_WRITE_GRP_ID,             // mesh group id
    MESH_READ_GRP_ID,
    MESH_WRITE_ROUTER_RSSI,        // RSSI of router
    MESH_READ_ROUTER_RSSI,
    MESH_WRITE_LAST_HOP,           // the last hop
    MESH_READ_LAST_HOP,
    MESH_WRITE_MAX_HOP,            // max hop
    MESH_READ_MAX_HOP,
    MESH_WRITE_ENCRYPT,            // encrypt information
    MESH_READ_ENCRYPT,
    MESH_WRITE_RSSI_THRESHOLD,     // RSSI threshold to select parent
    MESH_READ_RSSI_THRESHOLD,
    MESH_WRITE_SERVER_INFO,        // server information
    MESH_READ_SERVER_INFO,
    MESH_NVS_ERASE_ALL,
    MESH_OPERATE_IDX_MAX,
    MESH_NVS_DESTROY,
};
/***********************************************************************/

extern uint8_t g_mesh_last_hop;
extern nvs_handle g_mesh_nvs_handler;
extern xTaskHandle g_mesh_save_task_handle;
extern mesh_router_info_t g_mesh_router_info;
extern QueueHandle_t g_mesh_nvs_queue_handler;
extern struct mesh_router_rssi_info_type g_mesh_router_rssi;

extern bool mesh_save_task_init();

#endif
