#ifndef __MESH_LOG_H__
#define __MESH_LOG_H__

#include "esp_log.h"

#define MESH_LOGE( format, ... ) ESP_LOGE(TAG, "[%s, %d]:" format, __func__, __LINE__, ##__VA_ARGS__)
#define MESH_LOGW( format, ... ) ESP_LOGW(TAG, "[%s, %d]:" format, __func__, __LINE__, ##__VA_ARGS__)
#define MESH_LOGI( format, ... ) ESP_LOGI(TAG, format, ##__VA_ARGS__)
#define MESH_LOGD( format, ... ) ESP_LOGD(TAG, "[%s, %d]:" format, __func__, __LINE__, ##__VA_ARGS__)
#define MESH_LOGV( format, ... ) ESP_LOGV(TAG, format, ##__VA_ARGS__)

#define MESH_ERROR_CHECK(con, err, format, ...) if(con) {MESH_LOGE(format, ##__VA_ARGS__); perror(__func__); return err;}
#define MESH_PARAM_CHECK(con) if(con) {MESH_LOGE("Parameter error, "); assert(0);}

#endif /* __MESH_LOG_H__ */
