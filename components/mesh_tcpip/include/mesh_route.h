#ifndef __MESH_ROUTE_H__
#define __MESH_ROUTE_H__

#include "mesh.h"
#include "mesh_common.h"

#define ESP_MESH_ROUTE_INC_STEP   (6)

enum update_type {
    MAC_ROUTE_TABLE_ADD,  // add element
    MAC_ROUTE_TABLE_DEL,  // delete element
    MAC_ROUTE_TABLE_NEW,  // new router table
    MAC_ROUTE_TABLE_FREE  // delete router table
};

/*
 * mac[0]: represent the device type
 * mac[1~5]: represent the the last five bytes of MAC address
 */
struct mesh_mac_tab_elem_t {
    uint8_t mac[MESH_HWADDR_LEN];
} __packed;

/*
 * the MAC route table.
 */
struct mesh_mac_tab_t {
    uint16_t child_mac_cnt[ESP_MESH_CONNECT_MAX];  // present the count of MAC in the current MAC route table
    uint16_t child_mac_size[ESP_MESH_CONNECT_MAX]; // present the size of mac route table
    struct mesh_mac_tab_elem_t *child_mac_tab[ESP_MESH_CONNECT_MAX];  // MAC route table
};

extern struct mesh_mac_tab_t g_mesh_route_table;

int8_t esp32_mesh_route_init();
int8_t esp32_mesh_route_deinit();
int8_t esp32_mesh_lookup_route(void *dst);
int16_t esp32_mesh_lookup_sub_route(void *dst, int8_t cidx);
void esp32_mesh_print_route_table();
uint32_t esp32_mesh_count_sub_dev();
bool esp32_mesh_adjust_rtable(int8_t cidx, enum update_type type);
bool esp32_mesh_update_route_table(int8_t cidx, uint8_t *r_opt, enum update_type type);

#endif
