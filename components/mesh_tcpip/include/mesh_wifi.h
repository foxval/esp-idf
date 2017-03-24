#ifndef __MESH_WIFI_H__
#define __MESH_WIFI_H__

#include <stdint.h>
#include <xtensa/xos_types.h>
#include "esp_wifi.h"
#include "esp_wifi_internal.h"

void mesh_rx_task(void *pvPara);
bool mesh_wifi_init();


#endif /* __MESH_WIFI_H__ */
