#ifndef _MESH_TCPIP_H_
#define _MESH_TCPIP_H_

#include "lwip/sockets.h"


extern xTaskHandle g_mesh_tcpip_rx_task_handle;
extern xTaskHandle g_mesh_tcpip_tx_task_handle;

bool mesh_tcpip_task_init();
bool mesh_tcpip_task_deinit();

void mesh_tcpip_stop();
void mesh_tcpip_start();
void mesh_close_server();
void mesh_connect_server();
void mesh_tcpip_tx_task(void *pvPara);
void mesh_tcpip_rx_task(void *pvPara);

#endif /* _MESH_TCPIP_H_ */
