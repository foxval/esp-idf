#ifndef __MESH_WIFI_H__
#define __MESH_WIFI_H__

#include "esp_err.h"

esp_err_t esp_mesh_wifi_init(uint8_t channel, uint8_t mac_connections);

#endif /* __MESH_WIFI_H__ */
