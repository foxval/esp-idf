/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __BTC_AVRC_H__
#define __BTC_AVRC_H__

#include <stdint.h>
#include <stdbool.h>
#include "common/bt_defs.h"
#include "stack/bt_types.h"
#include "bta/bta_av_api.h"

#if (BTC_AV_INCLUDED == TRUE)
#ifndef BTC_AVRC_TGT_INCLUDED
#define BTC_AVRC_TGT_INCLUDED      FALSE
#endif

typedef enum {
    BTC_AVRC_CTRL_API_INIT_EVT = 0,
    BTC_AVRC_CTRL_API_DEINIT_EVT,
    BTC_AVRC_CTRL_API_SND_PTCMD_EVT,
    BTC_AVRC_STATUS_API_SND_META_EVT,
    BTC_AVRC_STATUS_API_SND_PLAY_STATUS_EVT,
    BTC_AVRC_NOTIFY_API_SND_REG_NOTIFY_EVT,
    BTC_AVRC_CTRL_API_SET_PLAYER_SETTING_EVT
} btc_avrc_act_t;

typedef struct {
    uint8_t tl; /* transaction label */
    uint8_t key_code;
    uint8_t key_state;
} pt_cmd_t;

typedef struct {
    uint8_t tl;
    uint8_t attr_mask;
} md_cmd_t;

typedef struct {
    uint8_t tl;
    uint8_t event_id;
    uint32_t event_parameter;
} rn_cmd_t;

typedef struct {
    uint8_t tl;
    uint8_t attr_id;
    uint8_t value_id;
} ps_cmd_t;

/* btc_avrc_args_t */
typedef union {
    pt_cmd_t pt_cmd;
    md_cmd_t md_cmd;
    rn_cmd_t rn_cmd;
    ps_cmd_t ps_cmd;
} btc_avrc_args_t;

/*****************************************************************************
**  Constants & Macros
******************************************************************************/
/* for AVRC 1.4 need to change this */
#define MAX_RC_NOTIFICATIONS AVRC_EVT_APP_SETTING_CHANGE

#define MAX_VOLUME 128
#define MAX_LABEL 16
#define MAX_TRANSACTIONS_PER_SESSION 16
#define MAX_CMD_QUEUE_LEN 8

#define CHECK_ESP_RC_CONNECTED       do { \
        BTC_TRACE_DEBUG("## %s ##", __FUNCTION__); \
        if (btc_rc_vb.rc_connected == FALSE) { \
            BTC_TRACE_WARNING("Function %s() called when RC is not connected", __FUNCTION__); \
        return ESP_ERR_INVALID_STATE; \
        } \
    } while (0)

/*****************************************************************************
**  Local type definitions
******************************************************************************/
typedef struct {
    UINT8 bNotify;
    UINT8 label;
} btc_rc_reg_notifications_t;

typedef struct {
    UINT8   label;
    UINT8   ctype;
    BOOLEAN is_rsp_pending;
} btc_rc_cmd_ctxt_t;

/* TODO : Merge btc_rc_reg_notifications_t and btc_rc_cmd_ctxt_t to a single struct */
typedef struct {
    BOOLEAN                     rc_connected;
    UINT8                       rc_handle;
    tBTA_AV_FEAT                rc_features;
    BD_ADDR                     rc_addr;
    UINT16                      rc_pending_play;
    btc_rc_cmd_ctxt_t           rc_pdu_info[MAX_CMD_QUEUE_LEN];
    btc_rc_reg_notifications_t  rc_notif[MAX_RC_NOTIFICATIONS];
    unsigned int                rc_volume;
    uint8_t                     rc_vol_label;
} btc_rc_cb_t;

/*****************************************************************************
**  Static variables
******************************************************************************/
#if AVRC_DYNAMIC_MEMORY == TRUE
extern btc_rc_cb_t *btc_rc_vb_ptr;
#define btc_rc_vb (*btc_rc_vb_ptr)
#endif ///AVRC_DYNAMIC_MEMORY == FALSE

/** BT-RC Controller callback structure. */
typedef void (* btrc_passthrough_rsp_callback) (int id, int key_state);

typedef void (* btrc_connection_state_callback) (bool state, bt_bdaddr_t *bd_addr);

void btc_rc_handler(tBTA_AV_EVT event, tBTA_AV *p_data);

BOOLEAN btc_rc_get_connected_peer(BD_ADDR peer_addr);

/*******************************************************************************
**  BTC AVRC API
********************************************************************************/
void btc_avrc_call_handler(btc_msg_t *msg);

#endif  ///BTC_AV_INCLUDED == TRUE

#endif /* __BTC_AVRC_H__ */
