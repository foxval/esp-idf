#ifndef _BFC_USR_CONFIG_H_
#define _BFC_USR_CONFIG_H_

#include <stdint.h>
#include "esp_wifi_types.h"

static const uint16_t MESH_SERVER_PORT = 7000; /*PORT USED BY USER IOT SERVER FOR MESH SERVICE*/
static const uint8_t MESH_SERVER_IP[4] = { 192, 168, 1, 168 }; /*USER IOT SERVER IP ADDRESS*/
static const uint32_t UART_BAUD_RATIO = 115200; /*UART BAUD RATIO*/
static const uint8_t MESH_GROUP_ID[6] = { 0x18, 0xfe, 0x34, 0x32, 0x00, 0x50 }; /*MESH_GROUP_ID REPRESENTS ONE MESH NETWORK*/
static const uint8_t MESH_ROUTER_BSSID[6] =
        { 0xF0, 0xB4, 0x29, 0x2C, 0x7C, 0x72 }; /*MAC OF ROUTER*/

/*
 * please configure MESH_ROUTER_SSID and MESH_ROUTER_PASSWD according to your router
 */
#define MESH_ROUTER_SSID     "SMART_LIGHT"     /*THE ROUTER SSID*/
#define MESH_ROUTER_PASSWD   "qwertyuiop"      /*THE ROUTER PASSWORD*/
#define MESH_SSID_PREFIX     "MESH32"          /*SET THE DEFAULT MESH SSID PREFIX;THE FINAL SSID OF SOFTAP WOULD BE "MESH_SSID_PREFIX_X_YYYYYY"*/
#define MESH_AUTH            WIFI_AUTH_WPA2_PSK/*AUTH_MODE OF SOFTAP FOR EACH MESH NODE*/
#define MESH_PASSWD          "123123123"       /*SET PASSWORD OF SOFTAP FOR EACH MESH NODE*/
#define MESH_MAX_HOP         (5)               /*MAX_HOPS OF MESH NETWORK*/

#endif /* _BFC_USR_CONFIG_H_ */
