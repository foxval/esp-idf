/*
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_bt.h"

#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_gattc_api.h"
#include "esp_bt_defs.h"
#include "esp_bt_main.h"
#include "esp_bt_main.h"
#include "esp_gatt_common_api.h"

#include "sdkconfig.h"

//#if (BLE_50_FEATURE_SUPPORT == TRUE)

static SemaphoreHandle_t test_sem;

esp_gatt_if_t test_gattc_if;

#define TAG "BLE_5_0_TEST"

#define FUNC_SEND_WAIT_SEM(func, sem) do {\
        esp_err_t __err_rc = (func);\
        if (__err_rc != ESP_OK) { \
            ESP_LOGE(TAG, "%s, message send fail, error = %d", __func__, __err_rc); \
        } \
        xSemaphoreTake(sem, portMAX_DELAY); \
} while(0);

esp_ble_gap_ext_adv_params_t ext_adv_params = {
    .type = ESP_BLE_GAP_SET_EXT_ADV_PROP_CONNECTABLE,
    .interval_min = 0x20,
    .interval_max = 0x40,
    .channel_map = ADV_CHNL_ALL,
    .filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
    .primary_phy = ESP_BLE_GAP_PHY_1M,
    .max_skip = 5,
    .secondary_phy = ESP_BLE_GAP_PHY_1M,
    .sid = 0,
    .scan_req_notif = false,
};



static uint8_t raw_adv_data[] = {
        0x02, 0x01, 0x06,
        0x02, 0x0a, 0xeb, 0x03, 0x03, 0xab, 0xcd,
        0x11, 0x09, 'F', 'P', 'G', 'A', '_', 'Y', 'U', 'L', 'O', 'N', 'G',
        '_', 'D', 'E', 'M', 'O'
};
static uint8_t raw_scan_rsp_data[] = {
        0x10, 0xff, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b,
        0x0c, 0x0d, 0x0e, 0x0f
};

static esp_ble_gap_ext_adv_t ext_adv[10] = {
    [0] = {0, 0, 0},
};

static esp_ble_gap_periodic_adv_params_t periodic_adv_params = {
    .interval_min = 0x20,
    .interval_max = 0x40,
    .properties = 0,
};

static uint8_t periodic_adv_raw_data[] = {
        0x02, 0x01, 0x06,
        0x02, 0x0a, 0xeb, 0x03, 0x03, 0xab, 0xcd,
        0x11, 0x09, 'F', 'P', 'G', 'A', '_', 'Y', 'U', 'L', 'O', 'N', 'G',
        '_', 'D', 'E', 'M', 'O'
};

static esp_ble_ext_scan_params_t ext_scan_params = {
    .scan_type = BLE_SCAN_TYPE_ACTIVE,
    .own_addr_type = BLE_ADDR_TYPE_PUBLIC,
    .filter_policy = BLE_SCAN_FILTER_ALLOW_ALL,
    .scan_duplicate = BLE_SCAN_DUPLICATE_DISABLE,
    .cfg_mask = ESP_BLE_GAP_EXT_SCAN_CFG_UNCODE_MASK,
    .uncoded_cfg = {BLE_SCAN_TYPE_ACTIVE, 40, 40},
};

static esp_ble_gap_periodic_adv_sync_params_t periodic_adv_sync_params = {
    .filter_policy = 0,
    .sid = 0,
    .addr_type = BLE_ADDR_TYPE_RANDOM,
    .skip = 10,
    .sync_timeout = 1000,
};

bool periodic_sync;

static void test_compatibility_ext_scan(esp_ble_gap_ext_adv_reprot_t *params);
static char *test_phy_to_str(esp_ble_gap_phy_t phy);
static bool is_connect;

static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
    uint8_t *adv_name = NULL;
    uint8_t adv_name_len = 0;
    switch (event) {
    case ESP_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT:
        break;
    case ESP_GAP_BLE_SCAN_RSP_DATA_RAW_SET_COMPLETE_EVT:
        break;
    case ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT:
        break;
    case ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT:
        break;
    case ESP_GAP_BLE_ADV_START_COMPLETE_EVT:
        break;
    case ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT:
        break;
    case ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT:
        break;
    case ESP_GAP_BLE_SET_LOCAL_PRIVACY_COMPLETE_EVT:
    case ESP_GAP_BLE_SET_STATIC_RAND_ADDR_EVT:
    case ESP_GAP_BLE_UPDATE_WHITELIST_COMPLETE_EVT:
    case ESP_GAP_BLE_EXT_ADV_SET_PARAMS_COMPLETE_EVT:
    case ESP_GAP_BLE_EXT_ADV_DATA_SET_COMPLETE_EVT:
    case ESP_GAP_BLE_EXT_SCAN_RSP_DATA_SET_COMPLETE_EVT:
    case ESP_GAP_BLE_EXT_ADV_START_COMPLETE_EVT:
    case ESP_GAP_BLE_EXT_ADV_STOP_COMPLETE_EVT:
    case ESP_GAP_BLE_EXT_SCAN_STOP_COMPLETE_EVT:
    case ESP_GAP_BLE_PERIODIC_ADV_SET_PARAMS_COMPLETE_EVT:
    case ESP_GAP_BLE_PERIODIC_ADV_DATA_SET_COMPLETE_EVT:
    case ESP_GAP_BLE_PERIODIC_ADV_START_COMPLETE_EVT:
    case ESP_GAP_BLE_SET_EXT_SCAN_PARAMS_COMPLETE_EVT:
    case ESP_GAP_BLE_EXT_SCAN_START_COMPLETE_EVT:
	ESP_LOGE(TAG, "%s event = %d compelte, status = %d", __func__, event, param->ext_adv_data_set.status);
        xSemaphoreGive(test_sem);
        break;
    case ESP_GAP_BLE_EXT_ADV_REPORT_EVT:

        //esp_log_buffer_hex(TAG, param->ext_adv_report.params.addr, 6);
        //ESP_LOGI(TAG, "Data_status: %d", param->ext_adv_report.params.data_status);
	//ESP_LOGI(TAG, "Searched Adv Data Len %d", param->ext_adv_report.params.adv_data_len);
	adv_name = esp_ble_resolve_adv_data(param->ext_adv_report.params.adv_data,
                                            ESP_BLE_AD_TYPE_NAME_CMPL, &adv_name_len);
#if 0
	if ((adv_name != NULL) && (memcmp(adv_name, "FPGA_YULONG_DEMO", adv_name_len) == 0) && !periodic_sync) {
            periodic_sync = true;
	    char adv_temp_name[20] = {'0'};
	    memcpy(adv_temp_name, adv_name, adv_name_len);
	    //ESP_LOGI(TAG, "Start create sync with the peer device. %s", adv_temp_name);
            periodic_adv_sync_params.sid = param->ext_adv_report.params.sid;
	    //periodic_adv_sync_params.addr_type = param->ext_adv_report.params.addr_type;
	    memcpy(periodic_adv_sync_params.addr, param->ext_adv_report.params.addr, sizeof(esp_bd_addr_t));
            esp_ble_gap_periodic_adv_create_sync(&periodic_adv_sync_params);
	}
#endif
#if 1
        if ((adv_name != NULL) && (memcmp(adv_name, "FPGA_YULONG_DEMO", adv_name_len) == 0) && !is_connect) {
            const esp_ble_gap_conn_params_t phy_1m_conn_params = {
                .scan_interval = 0x40,
                .scan_window = 0x40,
                .interval_min = 0x40,
                .interval_max = 0x40,
                .latency = 0,
                .supervision_timeout = 600,
                .min_ce_len  = 0,
                .max_ce_len = 0,
            };
        is_connect = true;
        ESP_LOGI(TAG, "Receive the adv name is %s", adv_name);
#if 1
        //FUNC_SEND_WAIT_SEM(esp_ble_gap_ext_adv_stop(), test_sem);
        //esp_bd_addr_t addr = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
        esp_err_t error = esp_ble_gap_prefer_ext_connect_params_set(param->ext_adv_report.params.addr,
                                                ESP_BLE_GAP_PHY_NO_RX_PREF_MASK | ESP_BLE_GAP_PHY_NO_TX_PREF_MASK, &phy_1m_conn_params, &phy_1m_conn_params, NULL);
        ESP_LOGI(TAG, "The status = %d", error);
        //esp_ble_gattc_open(gl_profile_tab[PROFILE_A_APP_ID].gattc_if, scan_result->scan_rst.bda, scan_result->scan_rst.ble_addr_type, true);
        esp_ble_gattc_aux_open(test_gattc_if, 
                                param->ext_adv_report.params.addr, 
                                param->ext_adv_report.params.addr_type, true);
#endif

	}
    #endif
        //test_compatibility_ext_scan(&param->ext_adv_report.params);

        //ESP_LOGI(TAG, "sid %d", param->ext_adv_report.params.sid);
        //esp_log_buffer_char(TAG, adv_name, adv_name_len);
	break;
    case ESP_GAP_BLE_PERIODIC_ADV_CREATE_SYNC_COMPLETE_EVT:
        ESP_LOGI(TAG, "ESP_GAP_BLE_PERIODIC_ADV_CREATE_SYNC_COMPLETE_EVT: %s", (param->period_adv_create_sync.status == ESP_BT_STATUS_SUCCESS) ? "SUCESS" : "FAIL");
        break;
    case ESP_GAP_BLE_PERIODIC_ADV_REPORT_EVT:
        ESP_LOGI(TAG, "ESP_GAP_BLE_PERIODIC_ADV_REPORT_EVT.");
        break;
    default:
        break;
    }
}

static void esp_gattc_cb(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if, esp_ble_gattc_cb_param_t *param)
{

    if (event == ESP_GATTC_REG_EVT) {
        if (param->reg.status == ESP_GATT_OK) {
            test_gattc_if = gattc_if;
        } else {
            ESP_LOGI(TAG, "reg app failed, app_id %04x, status %d",
                    param->reg.app_id,
                    param->reg.status);
            return;
        }
    }
#if 0
    /* If event is register event, store the gattc_if for each profile */
    if (event == ESP_GATTC_REG_EVT) {
        if (param->reg.status == ESP_GATT_OK) {
            gl_profile_tab[param->reg.app_id].gattc_if = gattc_if;
        } else {
            ESP_LOGI(TAG, "reg app failed, app_id %04x, status %d",
                    param->reg.app_id,
                    param->reg.status);
            return;
        }
    }

    /* If the gattc_if equal to profile A, call profile A cb handler,
     * so here call each profile's callback */
    do {
        int idx;
        for (idx = 0; idx < PROFILE_NUM; idx++) {
            if (gattc_if == ESP_GATT_IF_NONE || /* ESP_GATT_IF_NONE, not specify a certain gatt_if, need to call every profile cb function */
                    gattc_if == gl_profile_tab[idx].gattc_if) {
                if (gl_profile_tab[idx].gattc_cb) {
                    gl_profile_tab[idx].gattc_cb(event, gattc_if, param);
                }
            }
        }
    } while (0);
#endif
}

static char *test_phy_to_str(esp_ble_gap_phy_t phy)
{
    switch(phy) {
        case ESP_BLE_GAP_PHY_1M:
            return "1M";
        case ESP_BLE_GAP_PHY_2M:
            return "2M";
        case ESP_BLE_GAP_PHY_CODED:
            return "1M coded";
    }

    return NULL;
}

static void test_compatibility_ext_scan(esp_ble_gap_ext_adv_reprot_t *params)
{
    uint8_t *adv_name = NULL;
    uint8_t adv_name_len = 0;
    uint8_t *manu_data = NULL;
    uint8_t manu_data_len = 0;

    if (params) {
        adv_name = esp_ble_resolve_adv_data(params->adv_data,
                                            ESP_BLE_AD_TYPE_NAME_CMPL, &adv_name_len);
        if ((adv_name != NULL) && (memcmp(adv_name, "FPGADEMO", adv_name_len) == 0)) {
            ESP_LOGI(TAG, "secondly phy is %s", test_phy_to_str(params->secondly_phy));
            ESP_LOGI(TAG, "primary phy phy is %s", test_phy_to_str(params->primary_phy));
            manu_data = esp_ble_resolve_adv_data(params->adv_data,
                                            ESP_BLE_AD_MANUFACTURER_SPECIFIC_TYPE, &manu_data_len);
            if (manu_data && manu_data_len != 0) {
                ESP_LOG_BUFFER_HEX(TAG, manu_data, manu_data_len);
            }
        }
    }
}

void test_set_extend_adv_data(uint8_t instance, esp_ble_gap_ext_adv_params_t *params,
                                             uint16_t adv_data_len, uint8_t *adv_data,
                                             uint16_t scan_rsp_len, uint8_t *scan_rsp_data)
{
    FUNC_SEND_WAIT_SEM(esp_ble_gap_ext_adv_set_params(instance, params), test_sem);
    if (adv_data_len && adv_data) {
        FUNC_SEND_WAIT_SEM(esp_ble_gap_config_ext_adv_data_raw(instance, adv_data_len, adv_data), test_sem);
    }
    if (scan_rsp_len && scan_rsp_data) {
        FUNC_SEND_WAIT_SEM(esp_ble_gap_config_ext_scan_rsp_data_raw(instance, scan_rsp_len, scan_rsp_data), test_sem);
    }
}

void test_start_extand_adv(uint8_t num_adv, esp_ble_gap_ext_adv_t *ext_adv)
{
    FUNC_SEND_WAIT_SEM(esp_ble_gap_ext_adv_start(num_adv, ext_adv), test_sem);
}

uint8_t adv_inst[1] = {0};
void test_stop_extand_adv(void)
{
   FUNC_SEND_WAIT_SEM(esp_ble_gap_ext_adv_stop(1, adv_inst), test_sem);
}

void tester_init(void)
{
    esp_err_t ret;
    
    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    ret = esp_bt_controller_init(&bt_cfg);
    if (ret) {
        ESP_LOGE(TAG, "%s initialize controller failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    ret = esp_bt_controller_enable(ESP_BT_MODE_BLE);
    if (ret) {
        ESP_LOGE(TAG, "%s enable controller failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }
    ret = esp_bluedroid_init();
    if (ret) {
        ESP_LOGE(TAG, "%s init bluetooth failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }
    ret = esp_bluedroid_enable();
    if (ret) {
        ESP_LOGE(TAG, "%s enable bluetooth failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    ret = esp_ble_gap_register_callback(gap_event_handler);
     if (ret){
        ESP_LOGE(TAG, "gap register error, error code = %x", ret);
        return;
     }

    ret = esp_ble_gattc_register_callback(esp_gattc_cb);
    if(ret){
        ESP_LOGE(TAG, "%s gattc register failed, error code = %x\n", __func__, ret);
        return;
    }

    ret = esp_ble_gattc_app_register(0);
    if (ret){
        ESP_LOGE(TAG, "%s gattc app register failed, error code = %x\n", __func__, ret);
    }

    esp_err_t local_mtu_ret = esp_ble_gatt_set_local_mtu(500);
    if (local_mtu_ret){
        ESP_LOGE(TAG, "set local  MTU failed, error code = %x", local_mtu_ret);
    }

    test_sem = xSemaphoreCreateBinary();
    
#if 0
    uint32_t reg_addr = 0x60011064;
    uint32_t reg_before = READ_PERI_REG(reg_addr);
    uint32_t reg_mask = 0xFC;
    uint32_t reg_set = reg_before & (~reg_mask);
    reg_set = reg_set | (1 << 2);
    WRITE_PERI_REG(reg_addr, reg_set);
    uint32_t reg_after()
#endif

#if 1
    uint32_t ifs_reg_base = 0x60031000;
    WRITE_PERI_REG(ifs_reg_base+0x90, 0x200408);
    WRITE_PERI_REG(ifs_reg_base+0x94, 0x00020407);
    WRITE_PERI_REG(ifs_reg_base+0x98, 0x0F020407);
    WRITE_PERI_REG(ifs_reg_base+0x9C, 0x0A020008);
#endif

}


void ble_5_0_gap_test_task(void *args)
{
    uint8_t instance = 0;
    while(1) {
	vTaskDelay(1000 / portTICK_PERIOD_MS);
#if 1
	//ext_adv_params.type = 0; //ESP_BLE_GAP_SET_EXT_ADV_PROP_SCANNABLE;
        ext_adv_params.secondary_phy = ESP_BLE_GAP_PHY_2M;
        test_set_extend_adv_data(instance, &ext_adv_params, sizeof(raw_adv_data), &raw_adv_data[0],
                                 sizeof(raw_scan_rsp_data), &raw_scan_rsp_data[0]);
        ESP_LOGE(TAG, "set ADV data");
        test_start_extand_adv(1, &ext_adv[0]);
	    ESP_LOGE(TAG, "Start Extend adv");
	    vTaskDelay(200000000 / portTICK_PERIOD_MS);
        test_stop_extand_adv();
        ESP_LOGE(TAG, "Stop Current ADV, start DIRECTED adv test.");
#endif
#if 0
	vTaskDelay(1000 / portTICK_PERIOD_MS);
	/****************************************************************************/
        //vTaskDelay(20000 / portTICK_PERIOD_MS);
        ext_adv_params.type = ESP_BLE_GAP_SET_EXT_ADV_PROP_DIRECTED;
	ext_adv_params.peer_addr_type = BLE_ADDR_TYPE_PUBLIC;
	memset(ext_adv_params.peer_addr, 0x22, sizeof(esp_bd_addr_t));
        test_set_extend_adv_data(instance, &ext_adv_params, sizeof(raw_adv_data), &raw_adv_data[0],
                                 sizeof(raw_scan_rsp_data), &raw_scan_rsp_data[0]);

        test_start_extand_adv(1, &ext_adv[0]);
        vTaskDelay(20000 / portTICK_PERIOD_MS);
        test_stop_extand_adv();
        ESP_LOGE(TAG, "Stop Current ADV, start HD_DIRECTED adv test.");
	vTaskDelay(1000 / portTICK_PERIOD_MS);
        /******************************************************************************/
         
        ext_adv_params.type = ESP_BLE_GAP_SET_EXT_ADV_PROP_HD_DIRECTED;
        test_set_extend_adv_data(instance, &ext_adv_params, sizeof(raw_adv_data), &raw_adv_data[0],
                                 sizeof(raw_scan_rsp_data), &raw_scan_rsp_data[0]);

        test_start_extand_adv(1, &ext_adv[0]);
        vTaskDelay(20000 / portTICK_PERIOD_MS);
        test_stop_extand_adv();
        ESP_LOGE(TAG, "Stop Current ADV, start LEGACY adv test.");
	vTaskDelay(1000 / portTICK_PERIOD_MS);
	/******************************************************************************/
	ext_adv_params.peer_addr_type = 0;
        memset(ext_adv_params.peer_addr, 0, sizeof(esp_bd_addr_t));
        ext_adv_params.type = ESP_BLE_GAP_SET_EXT_ADV_PROP_LEGACY;
        test_set_extend_adv_data(instance, &ext_adv_params, sizeof(raw_adv_data), &raw_adv_data[0],
                                 sizeof(raw_scan_rsp_data), &raw_scan_rsp_data[0]);

        test_start_extand_adv(1, &ext_adv[0]);
        vTaskDelay(20000 / portTICK_PERIOD_MS);
        test_stop_extand_adv();
        ESP_LOGE(TAG, "Stop Current ADV, start ANON adv test.");
	vTaskDelay(1000 / portTICK_PERIOD_MS);
	/******************************************************************************/
	ext_adv_params.type = ESP_BLE_GAP_SET_EXT_ADV_PROP_ANON_ADV;
        test_set_extend_adv_data(instance, &ext_adv_params, sizeof(raw_adv_data), &raw_adv_data[0],
                                 sizeof(raw_scan_rsp_data), &raw_scan_rsp_data[0]);

        test_start_extand_adv(1, &ext_adv[0]);
        vTaskDelay(20000 / portTICK_PERIOD_MS);
        test_stop_extand_adv();
        ESP_LOGE(TAG, "Stop Current ADV, start LEGACY_IND adv test.");
	vTaskDelay(1000 / portTICK_PERIOD_MS);
	/******************************************************************************/
        ext_adv_params.type = ESP_BLE_GAP_SET_EXT_ADV_PROP_LEGACY_IND;
        test_set_extend_adv_data(instance, &ext_adv_params, sizeof(raw_adv_data), &raw_adv_data[0],
                                 sizeof(raw_scan_rsp_data), &raw_scan_rsp_data[0]);

        test_start_extand_adv(1, &ext_adv[0]);
        vTaskDelay(20000 / portTICK_PERIOD_MS);
        test_stop_extand_adv();
        ESP_LOGE(TAG, "Stop Current ADV, start LEGACY_LD_DIR adv test.");
	vTaskDelay(1000 / portTICK_PERIOD_MS);
	/******************************************************************************/
        ext_adv_params.type = ESP_BLE_GAP_SET_EXT_ADV_PROP_LEGACY_LD_DIR;
	ext_adv_params.peer_addr_type = BLE_ADDR_TYPE_PUBLIC;
        memset(ext_adv_params.peer_addr, 0x22, sizeof(esp_bd_addr_t));
        test_set_extend_adv_data(instance, &ext_adv_params, sizeof(raw_adv_data), &raw_adv_data[0],
                                 sizeof(raw_scan_rsp_data), &raw_scan_rsp_data[0]);

        test_start_extand_adv(1, &ext_adv[0]);
        vTaskDelay(20000 / portTICK_PERIOD_MS);
        test_stop_extand_adv();
        ESP_LOGE(TAG, "Stop Current ADV, start LEGACY_HD_DIR adv test.");
	vTaskDelay(1000 / portTICK_PERIOD_MS);
	/******************************************************************************/
        ext_adv_params.type = ESP_BLE_GAP_SET_EXT_ADV_PROP_LEGACY_HD_DIR;
        test_set_extend_adv_data(instance, &ext_adv_params, sizeof(raw_adv_data), &raw_adv_data[0],
                                 sizeof(raw_scan_rsp_data), &raw_scan_rsp_data[0]);

        test_start_extand_adv(1, &ext_adv[0]);
        vTaskDelay(20000 / portTICK_PERIOD_MS);
        test_stop_extand_adv();
        ESP_LOGE(TAG, "Stop Current ADV, start LEGACY_SCAN adv test.");
	vTaskDelay(1000 / portTICK_PERIOD_MS);
	/******************************************************************************/
	ext_adv_params.peer_addr_type = 0;
        memset(ext_adv_params.peer_addr, 0, sizeof(esp_bd_addr_t));
        ext_adv_params.type = ESP_BLE_GAP_SET_EXT_ADV_PROP_LEGACY_SCAN;
        test_set_extend_adv_data(instance, &ext_adv_params, sizeof(raw_adv_data), &raw_adv_data[0],
                                 sizeof(raw_scan_rsp_data), &raw_scan_rsp_data[0]);

        test_start_extand_adv(1, &ext_adv[0]);
        vTaskDelay(20000 / portTICK_PERIOD_MS);
        test_stop_extand_adv();
        ESP_LOGE(TAG, "Stop Current ADV, start LEGACY_NONCONN adv test.");
	vTaskDelay(1000 / portTICK_PERIOD_MS);
	/******************************************************************************/
        ext_adv_params.type = ESP_BLE_GAP_SET_EXT_ADV_PROP_LEGACY_NONCONN;
        test_set_extend_adv_data(instance, &ext_adv_params, sizeof(raw_adv_data), &raw_adv_data[0],
                                 sizeof(raw_scan_rsp_data), &raw_scan_rsp_data[0]);

        test_start_extand_adv(1, &ext_adv[0]);
        vTaskDelay(20000 / portTICK_PERIOD_MS);
        test_stop_extand_adv();
        ESP_LOGE(TAG, "Stop Current ADV, start DIRECTED adv test.");
#endif  
	/******************************************************************************/
#if 0
	ESP_LOGE(TAG, "Start test chnannel map in 37 sent ADV.");
        ext_adv_params.channel_map = ADV_CHNL_37;
        test_set_extend_adv_data(instance, &ext_adv_params, sizeof(raw_adv_data), &raw_adv_data[0],
                                 sizeof(raw_scan_rsp_data), &raw_scan_rsp_data[0]);

        test_start_extand_adv(1, &ext_adv[0]);
        vTaskDelay(20000 / portTICK_PERIOD_MS);
        test_stop_extand_adv();
        ESP_LOGE(TAG, "Start test chnannel map in 38 sent ADV.");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        /******************************************************************************/
        ext_adv_params.channel_map = ADV_CHNL_38;
        test_set_extend_adv_data(instance, &ext_adv_params, sizeof(raw_adv_data), &raw_adv_data[0],
                                 sizeof(raw_scan_rsp_data), &raw_scan_rsp_data[0]);

        test_start_extand_adv(1, &ext_adv[0]);
        vTaskDelay(20000 / portTICK_PERIOD_MS);
        test_stop_extand_adv();
        ESP_LOGE(TAG, "Start test chnannel map in 39 sent ADV.");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
	/*******************************************************************************/
	ext_adv_params.channel_map = ADV_CHNL_39;
        test_set_extend_adv_data(instance, &ext_adv_params, sizeof(raw_adv_data), &raw_adv_data[0],
                                 sizeof(raw_scan_rsp_data), &raw_scan_rsp_data[0]);

        test_start_extand_adv(1, &ext_adv[0]);
        vTaskDelay(20000 / portTICK_PERIOD_MS);
        test_stop_extand_adv();
        /*******************************************************************************/
#endif
#if 0
	ESP_LOGE(TAG, "Start test primary PHY set to 1M code to sent ADV.");
        ext_adv_params.primary_phy = ESP_BLE_GAP_PHY_CODED;
        test_set_extend_adv_data(instance, &ext_adv_params, sizeof(raw_adv_data), &raw_adv_data[0],
                                 sizeof(raw_scan_rsp_data), &raw_scan_rsp_data[0]);

        test_start_extand_adv(1, &ext_adv[0]);
        vTaskDelay(20000 / portTICK_PERIOD_MS);
        test_stop_extand_adv();
        ESP_LOGE(TAG, "Start test primary PHY set to 2M to sent ADV.");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        /******************************************************************************/
        ext_adv_params.secondary_phy = ESP_BLE_GAP_PHY_2M;
        test_set_extend_adv_data(instance, &ext_adv_params, sizeof(raw_adv_data), &raw_adv_data[0],
                                 sizeof(raw_scan_rsp_data), &raw_scan_rsp_data[0]);

        test_start_extand_adv(1, &ext_adv[0]);
        vTaskDelay(20000 / portTICK_PERIOD_MS);
        test_stop_extand_adv();
        ESP_LOGE(TAG, "Start test secondary PHY set to 1M code to sent ADV.");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        /*******************************************************************************/
        ext_adv_params.secondary_phy = ESP_BLE_GAP_PHY_CODED;
        test_set_extend_adv_data(instance, &ext_adv_params, sizeof(raw_adv_data), &raw_adv_data[0],
                                 sizeof(raw_scan_rsp_data), &raw_scan_rsp_data[0]);

        test_start_extand_adv(1, &ext_adv[0]);
        vTaskDelay(20000 / portTICK_PERIOD_MS);
        test_stop_extand_adv();
        /*******************************************************************************/
#endif
#if 0
	ESP_LOGE(TAG, "Start test set filter policy to SCAN_ANY_CON_ANY to sent ADV.");
        ext_adv_params.filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY;
        test_set_extend_adv_data(instance, &ext_adv_params, sizeof(raw_adv_data), &raw_adv_data[0],
                                 sizeof(raw_scan_rsp_data), &raw_scan_rsp_data[0]);

        test_start_extand_adv(1, &ext_adv[0]);
        vTaskDelay(20000 / portTICK_PERIOD_MS);
        test_stop_extand_adv();
        ESP_LOGE(TAG, "Start test set filter policy to SCAN_WLIT_CON_ANY to sent ADV.");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        /******************************************************************************/
        ext_adv_params.filter_policy = ADV_FILTER_ALLOW_SCAN_WLST_CON_ANY;
        test_set_extend_adv_data(instance, &ext_adv_params, sizeof(raw_adv_data), &raw_adv_data[0],
                                 sizeof(raw_scan_rsp_data), &raw_scan_rsp_data[0]);

        test_start_extand_adv(1, &ext_adv[0]);
        vTaskDelay(20000 / portTICK_PERIOD_MS);
        test_stop_extand_adv();
        ESP_LOGE(TAG, "Start test set filter policy to SCAN_ANY_CON_WLIT to sent ADV.");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        /*******************************************************************************/
        ext_adv_params.filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_WLST;
        test_set_extend_adv_data(instance, &ext_adv_params, sizeof(raw_adv_data), &raw_adv_data[0],
                                 sizeof(raw_scan_rsp_data), &raw_scan_rsp_data[0]);

        test_start_extand_adv(1, &ext_adv[0]);
        vTaskDelay(20000 / portTICK_PERIOD_MS);
        test_stop_extand_adv();
	ESP_LOGE(TAG, "Start test set filter policy to SCAN_WLIT_CON_WLIT to sent ADV.");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        /*******************************************************************************/
        ext_adv_params.filter_policy = ADV_FILTER_ALLOW_SCAN_WLST_CON_WLST;
        test_set_extend_adv_data(instance, &ext_adv_params, sizeof(raw_adv_data), &raw_adv_data[0],
                                 sizeof(raw_scan_rsp_data), &raw_scan_rsp_data[0]);

        test_start_extand_adv(1, &ext_adv[0]);
        vTaskDelay(20000 / portTICK_PERIOD_MS);
        test_stop_extand_adv();
        /*******************************************************************************/
#endif
#if 0
	ext_adv_params.type = 0;
	uint8_t raw_adv_test_data[1000] = {
            0x02, 0x01, 0x06,
            0x02, 0x0a, 0xeb, 0x03, 0x03, 0xab, 0xcd,
            0x11, 0x09, 'F', 'P', 'G', 'A', '_', 'Y', 'U', 'L', 'O', 'N', 'G',
            '_', 'D', 'E', 'M', 'O',
	    0xCA, 0xff, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b,
            0x0c, 0x0d, 0x0e, 0x0f
        };
	raw_adv_test_data[999] = 0xaa;
	test_set_extend_adv_data(instance, &ext_adv_params, sizeof(raw_adv_test_data), &raw_adv_test_data[0],
                                 0, NULL);

        test_start_extand_adv(1, &ext_adv[0]);
        vTaskDelay(40000000 / portTICK_PERIOD_MS);
        test_stop_extand_adv();
        vTaskDelay(10000000 / portTICK_PERIOD_MS);
#endif
#if 0
        ext_adv_params.type = 0;
        uint8_t raw_adv_test_data[1000] = {
            0x02, 0x01, 0x06,
            0x02, 0x0a, 0xeb, 0x03, 0x03, 0xab, 0xcd,
            0x11, 0x09, 'F', 'P', 'G', 'A', '_', 'Y', 'U', 'L', 'O', 'N', 'G',
            '_', 'D', 'E', 'M', 'O',
            0xCA, 0xff, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b,
            0x0c, 0x0d, 0x0e, 0x0f
        };
        raw_adv_test_data[999] = 0xaa;
        test_set_extend_adv_data(instance, &ext_adv_params, sizeof(raw_adv_test_data), &raw_adv_test_data[0],
                                 0, NULL);

        test_start_extand_adv(1, &ext_adv[0]);
	FUNC_SEND_WAIT_SEM(esp_ble_gap_periodic_adv_set_params(instance, &periodic_adv_params), test_sem);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_config_periodic_adv_data_raw(instance, sizeof(periodic_adv_raw_data), &periodic_adv_raw_data[0]), test_sem);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_periodic_adv_start(instance), test_sem);
        vTaskDelay(40000000 / portTICK_PERIOD_MS);
        test_stop_extand_adv();
        vTaskDelay(10000000 / portTICK_PERIOD_MS);
#endif
#if 0
	uint8_t raw_adv_test_data[231] = {
            0x02, 0x01, 0x06,
            0x02, 0x0a, 0xeb, 0x03, 0x03, 0xab, 0xcd,
            0x11, 0x09, 'F', 'P', 'G', 'A', '_', 'Y', 'U', 'L', 'O', 'N', 'G',
            '_', 'D', 'E', 'M', 'O',
            0xCA, 0xff, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b,
            0x0c, 0x0d, 0x0e, 0x0f
        };

	int k;
	
	for (k = 0; k < 5; k++) {
	    memset(&raw_adv_test_data[30], k, 231 - 30);
	    ext_adv[k].instance = k;
	    test_set_extend_adv_data(k, &ext_adv_params, sizeof(raw_adv_test_data), &raw_adv_test_data[0],
                                     0, NULL);
	}

	test_start_extand_adv(k, &ext_adv[0]);
	vTaskDelay(60000 / portTICK_PERIOD_MS);
        test_stop_extand_adv();
#endif
#if 0
	ext_adv_params.type = 0;
        test_set_extend_adv_data(instance, &ext_adv_params, sizeof(raw_adv_data), &raw_adv_data[0],
                                 sizeof(raw_scan_rsp_data), &raw_scan_rsp_data[0]);
        test_start_extand_adv(1, &ext_adv[0]);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_periodic_adv_set_params(instance, &periodic_adv_params), test_sem);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_config_periodic_adv_data_raw(instance, sizeof(periodic_adv_raw_data), &periodic_adv_raw_data[0]), test_sem);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_periodic_adv_start(instance), test_sem);
        vTaskDelay(600000000 / portTICK_PERIOD_MS);
#endif
#if 0
        ext_adv_params.type = 0;
        ext_adv_params.secondary_phy = ESP_BLE_GAP_PHY_2M;
        test_set_extend_adv_data(instance, &ext_adv_params, sizeof(raw_adv_data), &raw_adv_data[0],
                                 sizeof(raw_scan_rsp_data), &raw_scan_rsp_data[0]);
        test_start_extand_adv(1, &ext_adv[0]);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_periodic_adv_set_params(instance, &periodic_adv_params), test_sem);
	FUNC_SEND_WAIT_SEM(esp_ble_gap_config_periodic_adv_data_raw(instance, sizeof(periodic_adv_raw_data), &periodic_adv_raw_data[0]), test_sem);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_periodic_adv_start(instance), test_sem);
	vTaskDelay(60000000 / portTICK_PERIOD_MS);
#endif
#if 0

	ext_adv_params.type = 0;
        ext_adv_params.secondary_phy = ESP_BLE_GAP_PHY_CODED;
        test_set_extend_adv_data(instance, &ext_adv_params, sizeof(raw_adv_data), &raw_adv_data[0],
                                 sizeof(raw_scan_rsp_data), &raw_scan_rsp_data[0]);
        test_start_extand_adv(1, &ext_adv[0]);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_periodic_adv_set_params(instance, &periodic_adv_params), test_sem);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_config_periodic_adv_data_raw(instance, sizeof(periodic_adv_raw_data), &periodic_adv_raw_data[0]), test_sem);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_periodic_adv_start(instance), test_sem);
	vTaskDelay(60000000 / portTICK_PERIOD_MS);
#endif
#if 0 
	ext_adv_params.type = 0;
        //ext_adv_params.secondary_phy = ESP_BLE_GAP_PHY_CODED;
	uint8_t raw_periodic_adv_test_data[251] = {
            0x02, 0x01, 0x06,
            0x02, 0x0a, 0xeb, 0x03, 0x03, 0xab, 0xcd,
            0x11, 0x09, 'F', 'P', 'G', 'A', '_', 'Y', 'U', 'L', 'O', 'N', 'G',
            '_', 'D', 'E', 'M', 'O',
            0xCA, 0xff, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b,
            0x0c, 0x0d, 0x0e, 0x0f
        };
	raw_periodic_adv_test_data[250] = 0xaa;
        test_set_extend_adv_data(instance, &ext_adv_params, sizeof(raw_adv_data), &raw_adv_data[0],
                                 sizeof(raw_scan_rsp_data), &raw_scan_rsp_data[0]);
        test_start_extand_adv(1, &ext_adv[0]);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_periodic_adv_set_params(instance, &periodic_adv_params), test_sem);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_config_periodic_adv_data_raw(instance, sizeof(raw_periodic_adv_test_data), &raw_periodic_adv_test_data[0]), test_sem);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_periodic_adv_start(instance), test_sem);
#endif
#if 0
        ext_adv_params.type = 0;
        //ext_adv_params.secondary_phy = ESP_BLE_GAP_PHY_CODED;
	esp_bd_addr_t rand_addr = {0xc0, 0x22, 0x33, 0x44, 0x55, 0x66};
	ext_adv_params.own_addr_type = 1;
        FUNC_SEND_WAIT_SEM(esp_ble_gap_set_rand_addr(rand_addr), test_sem);
        //FUNC_SEND_WAIT_SEM(esp_ble_gap_config_local_privacy(true), test_sem);
        test_set_extend_adv_data(instance, &ext_adv_params, sizeof(raw_adv_data), &raw_adv_data[0],
                                 sizeof(raw_scan_rsp_data), &raw_scan_rsp_data[0]);
        test_start_extand_adv(1, &ext_adv[0]);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_periodic_adv_set_params(instance, &periodic_adv_params), test_sem);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_config_periodic_adv_data_raw(instance, sizeof(periodic_adv_raw_data), &periodic_adv_raw_data[0]), test_sem);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_periodic_adv_start(instance), test_sem);
#endif
#if 0
	ext_adv_params.type = 0;
        //ext_adv_params.secondary_phy = ESP_BLE_GAP_PHY_CODED;
        //esp_bd_addr_t rand_addr = {0xc0, 0x22, 0x33, 0x44, 0x55, 0x66};
        ext_adv_params.own_addr_type = 1;
        //FUNC_SEND_WAIT_SEM(esp_ble_gap_set_rand_addr(rand_addr), test_sem);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_config_local_privacy(true), test_sem);
        test_set_extend_adv_data(instance, &ext_adv_params, sizeof(raw_adv_data), &raw_adv_data[0],
                                 sizeof(raw_scan_rsp_data), &raw_scan_rsp_data[0]);
        test_start_extand_adv(1, &ext_adv[0]);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_periodic_adv_set_params(instance, &periodic_adv_params), test_sem);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_config_periodic_adv_data_raw(instance, sizeof(periodic_adv_raw_data), &periodic_adv_raw_data[0]), test_sem);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_periodic_adv_start(instance), test_sem);
#endif
#if 0
        int k;
	for (k = 0; k < 5; k++) {
            ext_adv[k].instance = k;
	    ext_adv[k].duration = 1000;
	    ext_adv_params.type = 0;
	    ext_adv_params.sid = k;
            test_set_extend_adv_data(k, &ext_adv_params, sizeof(raw_adv_data), &raw_adv_data[0],
                                     0, NULL);
        }

        test_start_extand_adv(k, &ext_adv[0]);
	for (k = 0; k < 5; k++) {
	    FUNC_SEND_WAIT_SEM(esp_ble_gap_periodic_adv_set_params(k, &periodic_adv_params), test_sem);
            FUNC_SEND_WAIT_SEM(esp_ble_gap_config_periodic_adv_data_raw(k, sizeof(periodic_adv_raw_data), &periodic_adv_raw_data[0]), test_sem);
	}
	vTaskDelay(100000000 / portTICK_PERIOD_MS);
#endif
#if 0
	FUNC_SEND_WAIT_SEM(esp_ble_gap_set_ext_scan_params(&ext_scan_params, 0), test_sem);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_start_ext_scan(0, 0), test_sem);
        vTaskDelay(100000000 / portTICK_PERIOD_MS);
#endif
#if 1
	// Set the Scan type to Passive scan
	ext_scan_params.scan_type = BLE_SCAN_TYPE_ACTIVE;
	ext_scan_params.uncoded_cfg.scan_type = BLE_SCAN_TYPE_ACTIVE;
        FUNC_SEND_WAIT_SEM(esp_ble_gap_set_ext_scan_params(&ext_scan_params, 0), test_sem);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_start_ext_scan(0, 0), test_sem);
        vTaskDelay(200000000 / portTICK_PERIOD_MS);
#endif
#if 0
	// When set the filter policy to allow only white list device, the scanner shouldn't scan the peer deivce
        ext_scan_params.filter_policy = BLE_SCAN_FILTER_ALLOW_ONLY_WLST;
        FUNC_SEND_WAIT_SEM(esp_ble_gap_set_ext_scan_params(&ext_scan_params, 0), test_sem);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_start_ext_scan(0, 0), test_sem);
#endif

//==========================================================
#if 0
       esp_bd_addr_t remote_bda = {0x11, 0x11, 0x11, 0x11, 0x11, 0x11};
       // Set the peer device to the whitelist
        FUNC_SEND_WAIT_SEM(esp_ble_gap_update_whitelist(true, remote_bda), test_sem);
        ext_scan_params.filter_policy = BLE_SCAN_FILTER_ALLOW_ONLY_WLST;
        FUNC_SEND_WAIT_SEM(esp_ble_gap_set_ext_scan_params(&ext_scan_params, 0), test_sem);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_start_ext_scan(0, 0), test_sem)
        vTaskDelay(100000000 / portTICK_PERIOD_MS);
#endif
#if 0
	// When set the filter policy to allow whitelist and privacy diretly, the scanner shouldn't scan the peer deivce
        ext_scan_params.filter_policy = BLE_SCAN_FILTER_ALLOW_WLIST_PRA_DIR;
        FUNC_SEND_WAIT_SEM(esp_ble_gap_set_ext_scan_params(&ext_scan_params, 0), test_sem);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_start_ext_scan(0, 0), test_sem);
#endif
#if 0
        esp_bd_addr_t rand_addr = {0xF0, 0x01, 0x02, 0x03, 0x04, 0x05}
        FUNC_SEND_WAIT_SEM(esp_ble_gap_set_rand_addr(rand_addr), test_sem);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_set_ext_scan_params(&ext_scan_params, 0), test_sem);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_start_ext_scan(0, 0), test_sem);
#endif
#if 0
        ext_scan_params.cfg_mask = ESP_BLE_GAP_EXT_SCAN_CFG_CODE_MASK;
        ext_scan_params.coded_cfg.scan_type = BLE_SCAN_TYPE_ACTIVE;
        ext_scan_params.coded_cfg.scan_interval = 0x40;
        ext_scan_params.coded_cfg.scan_window = 0x40;
        FUNC_SEND_WAIT_SEM(esp_ble_gap_set_ext_scan_params(&ext_scan_params, 0), test_sem);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_start_ext_scan(0, 0), test_sem);
	vTaskDelay(100000000 / portTICK_PERIOD_MS);
#endif
#if 0
        ext_scan_params.cfg_mask = ESP_BLE_GAP_EXT_SCAN_CFG_UNCODE_MASK | ESP_BLE_GAP_EXT_SCAN_CFG_CODE_MASK;
        ext_scan_params.coded_cfg.scan_type = BLE_SCAN_TYPE_ACTIVE;
        ext_scan_params.coded_cfg.scan_interval = 0x40;
        ext_scan_params.coded_cfg.scan_window = 0x40;
        FUNC_SEND_WAIT_SEM(esp_ble_gap_set_ext_scan_params(&ext_scan_params, 0), test_sem);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_start_ext_scan(0, 0), test_sem);
        vTaskDelay(100000000 / portTICK_PERIOD_MS);
#endif
#if 0
        ext_scan_params.filter_policy = BLE_SCAN_FILTER_ALLOW_UND_RPA_DIR;
        FUNC_SEND_WAIT_SEM(esp_ble_gap_set_ext_scan_params(&ext_scan_params, 0), test_sem);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_start_ext_scan(0, 0), test_sem);

        //ESP_LOGE(TAG, "Start Extend scan.");
	//vTaskDelay(100 / portTICK_PERIOD_MS);
        //FUNC_SEND_WAIT_SEM(esp_ble_gap_stop_ext_scan(), test_sem);
	//ESP_LOGE(TAG, "Stop Extend scan.");
        vTaskDelay(10000000 / portTICK_PERIOD_MS);
#endif
#if 0
        esp_bd_addr_t rand_addr = {0xc0, 0x22, 0x33, 0x44, 0x55, 0x66};
        FUNC_SEND_WAIT_SEM(esp_ble_gap_set_rand_addr(rand_addr), test_sem);
        ext_scan_params.own_addr_type = BLE_ADDR_TYPE_RANDOM;
        FUNC_SEND_WAIT_SEM(esp_ble_gap_set_ext_scan_params(&ext_scan_params, 0), test_sem);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_start_ext_scan(0, 0), test_sem);
        vTaskDelay(10000000 / portTICK_PERIOD_MS);
#endif
#if 0
        ext_scan_params.own_addr_type = BLE_ADDR_TYPE_RPA_RANDOM;
        FUNC_SEND_WAIT_SEM(esp_ble_gap_config_local_privacy(true), test_sem);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_set_ext_scan_params(&ext_scan_params, 0), test_sem);
        FUNC_SEND_WAIT_SEM(esp_ble_gap_start_ext_scan(0, 0), test_sem);
        vTaskDelay(10000000 / portTICK_PERIOD_MS);
#endif

    }
}

void app_main()
{
    esp_err_t ret;

    // Initialize NVS.
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );


    tester_init();
    xTaskCreate(ble_5_0_gap_test_task, "ble_5_0_gap_test", 2048, NULL, 10, NULL);

    return;
}

