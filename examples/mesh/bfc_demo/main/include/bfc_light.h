#ifndef _BFC_LIGHT_H_
#define _BFC_LIGHT_H_

#include "esp_err.h"

#define RGB_LIGHT_RED       (0xff)
#define RGB_LIGHT_GREEN     (0xfe)
#define RGB_LIGHT_BLUE      (0xfd)
#define RGB_LIGHT_YELLOW    (0xfc)
#define RGB_LIGHT_PINK      (0xfb)
#define RGB_LIGHT_INIT      (0xfa)
#define RGB_LIGHT_WARNING   (0xf9)

esp_err_t mesh_bfc_gpio_set(int value);
esp_err_t mesh_bfc_gpio_get(int* value);
esp_err_t mesh_bfc_light_init(void);
esp_err_t mesh_bfc_light_set(int brightness);
esp_err_t mesh_bfc_light_get(int* brightness);

#endif /* _BFC_LIGHT_H_ */
