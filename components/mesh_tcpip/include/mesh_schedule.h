#ifndef __MESH_SCHEDULE_H__
#define __MESH_SCHEDULE_H__

#include "mesh_common.h"
#include "mesh_config.h"

/***************** mesh save task **************************************/
#define MESH_SCHEDULE_TASK_NAME            "MSCH"
#define MESH_SCHEDULE_TASK_HEAP            (2048)
#define MESH_SCHEDULE_TASK_PRI             (MESH_DEFAULT_TASK_PRI + 1)
/***********************************************************************/

struct mesh_packet_context_t
{
    void *buf;
    uint8_t src[MESH_HWADDR_LEN];
    uint8_t dst[MESH_HWADDR_LEN];
    uint8_t ifidx;
    uint32_t wait;
};

extern xTaskHandle g_mesh_schedule_task_handle;

int mesh_delivery_usr(struct mesh_packet_context_t *ctx);
int mesh_process_mcast(struct mesh_packet_context_t *ctx);
int mesh_process_bcast(struct mesh_packet_context_t *ctx);
int mesh_process_ucast(struct mesh_packet_context_t *ctx);
int mesh_forward_packet(struct mesh_packet_context_t *ctx);

#endif
