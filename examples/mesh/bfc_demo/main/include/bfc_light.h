#ifndef _BFC_LIGHT_H_
#define _BFC_LIGHT_H_

#include "esp_err.h"

esp_err_t mesh_bfc_set_gpio(int value);
esp_err_t mesh_bfc_set_light(int brightness);
esp_err_t mesh_bfc_get_light(int* brightness);

#endif /* _BFC_LIGHT_H_ */
