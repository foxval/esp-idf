#ifndef _BFC_LIGHT_H_
#define _BFC_LIGHT_H_

#include "esp_err.h"

esp_err_t mesh_bfc_gpio_set(int value);
esp_err_t mesh_bfc_gpio_get(int* value);
esp_err_t mesh_bfc_light_init(void);
esp_err_t mesh_bfc_light_set(int brightness);
esp_err_t mesh_bfc_light_get(int* brightness);

#endif /* _BFC_LIGHT_H_ */
