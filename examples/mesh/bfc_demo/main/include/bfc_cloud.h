#ifndef _BFC_CLOUD_H_
#define _BFC_CLOUD_H_

enum
{
    BFC_SEND, BFC_ACK = 128,
};

enum BFC_CMD
{
    BFC_CMD_PING = 1,
    BFC_CMD_RPC,
    BFC_CMD_TRIGGER,
    BFC_CMD_UPGRADE,
    BFC_CMD_CONFIG,
    BFC_CMD_SET,
    BFC_CMD_GET,
};

enum OTA_ACTION
{
    BFC_OTA_START = 1,
    BFC_OTA_OK,
    BFC_AREA_OTA,
    BFC_OTA_REBOOT,
    BFC_OTA_FAIL = 255,
};

enum BFC_PROTO_VALUE
{
    BFC_VALUE_TOKEN,
    BFC_VALUE_REBOOT_CNT,
    BFC_VALUE_BSSID,
    BFC_VALUE_VERSION,
    BFC_VALUE_P_BSSID,
    BFC_VALUE_RSSI,			    //5
    BFC_VALUE_BRIGHTNESS,
    BFC_VALUE_FIX_BRIGHTNESS,
    BFC_VALUE_DELAY,			//0 means bright permanently
    BFC_VALUE_OTA,
    BFC_VALUE_OTA_ACTION,       // 10
    BFC_VALUE_MODE = 12,
    BFC_VALUE_PING_TIME = 14,   //unit second
    BFC_VALUE_PUSH_TRIGGER,

    BFC_VALUE_PING_EN = 28,		//enable ping or not
    BFC_VALUE_WIFI,
    BFC_VALUE_GROUP_ID,
    BFC_VALUE_SSID,
    BFC_VALUE_PASSWORD,
    BFC_VALUE_REBOOT,
    BFC_VALUE_STA_AP,
    BFC_VALUE_HEAP,
    BFC_VALUE_NODE_INFO,
    BFC_VALUE_IP,
    BFC_VALUE_WIFI_INFO,
    BFC_VALUE_EXCEPTION,
    BFC_VALUE_OTA_STATUS,       // 40
    BFC_VALUE_RESPONSE = 127
};

typedef struct
{
    uint16_t delay;           //change color duration accordingly
    uint8_t brightness;       //light brightness
    uint8_t fix_brightness; //after delay time the light should be set as fix_britness
    uint8_t ping_ack;         //flag to indicate receiving ack from ping request
    uint8_t trigger_send_en;  //if send info when trigger
    uint16_t ping_time;       //ping interval
    uint8_t bfc_set_color;    //if set the color
} bfc_t;

typedef struct
{
    uint8_t token_id;
    uint16_t token_val;
} bfc_token_t;

void mesh_bfc_process_received_data(uint8_t* buf, uint16_t len);
void mesh_bfc_pack_ping(uint8_t* ping_buf, uint8_t len);

#endif /* _BFC_CLOUD_H_ */
