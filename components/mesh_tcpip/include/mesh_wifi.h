#ifndef __MESH_WIFI_H__
#define __MESH_WIFI_H__

#include <stdint.h>
#include <xtensa/xos_types.h>
#include "esp_wifi.h"
#include "esp_wifi_internal.h"

void mesh_rx_task(void *pvPara);
bool mesh_wifi_init();

#if 0
/*
 * mac: the packet destination address
 * res: the result of status, 0:Success, the others:Failure
 */
typedef void (* esp32_wifi_mesh_rxcb_t)(uint8_t ifidx, char *pdata, uint16_t len, void *src);

/*
 * esp32_wifi_mesh_recv is the entrance of mesh stack
 * when ieee80211 receives packet with mesh type, ieee80211 should post packet to mesh
 */
void esp32_mesh_wifi_rxcb(uint8_t ifidx, char *pdata, uint16_t len, void *src);

/*
 * esp32_wifi_mesh_reg_rxcb is used to register mesh receive callback
 * when ieee80211 receives the packet with mesh type, it will trigger the callback
 */
void esp32_wifi_mesh_reg_rxcb(esp32_wifi_mesh_rxcb_t fn);
/*
 * when mesh plans to sent packet, it will use the API to post packet to ieee80211
 * ifidx: the interface index, 0:STA, 1: SoftAP
 * dst: the destination MAC address
 */
int esp32_wifi_mesh_tx(uint8_t ifidx, void *buffer, uint16_t len, uint8_t *dst);
#endif

#endif
