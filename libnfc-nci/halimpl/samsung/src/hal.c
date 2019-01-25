/*
 *    Copyright (C) 2013 SAMSUNG S.LSI
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at:
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 *   Author: Woonki Lee <woonki84.lee@samsung.com>
 *
 */
#include <errno.h>
#include <string.h>

#include "osi.h"
#include "hal.h"
#include "util.h"
#include "device.h"
#include <cutils/properties.h>
/* [201603] Single SKU */
#ifdef TN
#include <SecNativeFeature.h>
#endif
/* [201603] End */

/*************************************
 * Generic device handling.
 *************************************/
bool nfc_stack_cback(nfc_event_t event, nfc_status_t event_status)
{
    OSI_logt("!");
    if (!nfc_hal_info.stack_cback)
        return false;

    nfc_hal_info.stack_cback(event, event_status);
    return true;
}

bool nfc_data_callback(tNFC_NCI_PKT *pkt)
{
    uint8_t *data = (uint8_t*)pkt;
    size_t len = NCI_LEN(pkt) + NCI_HDR_SIZE;

    OSI_logt("!");
    if (!nfc_hal_info.data_cback)
        return false;

    nfc_hal_info.data_cback(len, data);
    return true;
}

int nfc_hal_init(void)
{
    char valueStr [PROPERTY_VALUE_MAX] = {0};
    bool data_trace = false;
    int trace_level = 0;
    int ret;
    char *csc;

    OSI_set_debug_level(2);
    OSI_init();

    OSI_logt("enter;");

/* [201603] Single SKU */
    /* Set user prefix for configuration file */
#ifndef SEC_PRODUCT_SHIP
    static char override_code[PROPERTY_VALUE_MAX] = {0};
    property_get("nfc.fw.dfl_ovrd", override_code, "");

    if(strlen(override_code) != 0)
    {
        OSI_logd("dynamicfwloading_override : %s", override_code);
        csc = override_code;
    }
    else
#endif
#ifdef TN
    csc = SecNativeFeature_getString(TAG_CSCFEATURE_NFC_CONFIGDYNAMICFIRMWARELOADING);
#endif
    set_user_prefix(csc);
/* [201603] End */

    /* don't print log at user binary */
    ret = property_get ("ro.build.type", valueStr, "");
    if (!strncmp("user", valueStr, PROPERTY_VALUE_MAX))
    {
        property_get("ro.debug_level", valueStr, "");
        if ( strncmp("0x4f4c",valueStr, PROPERTY_VALUE_MAX))
        {
            trace_level = 2;
            data_trace = true;
        }
    }
    else
    {
           if (!get_config_int(cfg_name_table[CFG_TRACE_LEVEL], &trace_level))
               trace_level = 0;

           if (get_config_int(cfg_name_table[CFG_DATA_TRACE], &ret))
        {
               if (ret > 0)
                   data_trace = true;
       }
    }

       OSI_set_debug_level(trace_level);

    memset(&nfc_hal_info, 0, sizeof(nfc_hal_info));
    // contenxt init
    nfc_hal_info.state = HAL_STATE_INIT;
    nfc_hal_info.stack_cback = NULL;
    nfc_hal_info.data_cback = NULL;
    nfc_hal_info.nci_last_pkt = (tNFC_NCI_PKT*)OSI_mem_get(NCI_CTRL_SIZE);
    nfc_hal_info.nci_fragment_pkt = NULL;
    nfc_hal_info.msg_task = OSI_task_allocate("hal_task", nfc_hal_task);
    nfc_hal_info.nci_timer = OSI_timer_allocate("nci_timer");
    nfc_hal_info.sleep_timer = OSI_timer_allocate("sleep_timer");
    nfc_hal_info.msg_q = OSI_queue_allocate("msg_q");
    nfc_hal_info.nci_q = OSI_queue_allocate("nci_q");

/* [201603] Single SKU */
// Remove code
/* [201603] End */
    setSleepTimeout(SET_SLEEP_TIME_CFG, 5000);

    if (!nfc_hal_info.msg_task || !nfc_hal_info.nci_timer || !nfc_hal_info.sleep_timer
            || !nfc_hal_info.msg_q || !nfc_hal_info.nci_q)
    {
        nfc_hal_deinit();
        return -EPERM;
    }

    if (device_init(data_trace))
    {
        nfc_hal_deinit();
        return -EPERM;
    }

    OSI_logt("succeed;");
    return 0;
}

void nfc_hal_deinit(void)
{
    OSI_logt("enter;");

    device_close();

    nfc_hal_info.state = HAL_STATE_DEINIT;
    OSI_task_kill(nfc_hal_info.msg_task);
    nfc_hal_info.stack_cback = NULL;
    nfc_hal_info.data_cback = NULL;
    OSI_mem_free((tOSI_MEM_HANDLER)nfc_hal_info.nci_last_pkt);
    nfc_hal_info.nci_last_pkt = NULL;
    OSI_mem_free((tOSI_MEM_HANDLER)nfc_hal_info.nci_fragment_pkt);
    nfc_hal_info.nci_fragment_pkt = NULL;
    OSI_timer_free(nfc_hal_info.nci_timer);
    OSI_timer_free(nfc_hal_info.sleep_timer);
    OSI_queue_free(nfc_hal_info.msg_q);
    OSI_queue_free(nfc_hal_info.nci_q);

    OSI_deinit();
    OSI_logt("exit;");
}

int nfc_hal_open(const struct nfc_nci_device *p_dev,
    nfc_stack_callback_t *p_cback, nfc_stack_data_callback_t *p_data_cback)
{
    tNFC_HAL_MSG *msg;

    OSI_logt("enter;");

    if (device_open())
        return -EPERM;

    if (OSI_OK != OSI_task_run(nfc_hal_info.msg_task))
    {
        nfc_hal_deinit();
        return -EPERM;
    }

    nfc_hal_info.stack_cback = p_cback;
    nfc_hal_info.data_cback = p_data_cback;
    nfc_hal_info.state = HAL_STATE_OPEN;

    msg = (tNFC_HAL_MSG*)OSI_mem_get(HAL_EVT_SIZE);
    if (msg != NULL)
    {
        msg->event = HAL_EVT_OPEN;
        OSI_queue_put(nfc_hal_info.msg_q, (void *)msg);
    }
    OSI_logt("exit;");
    return 0;
}

int nfc_hal_close(const struct nfc_nci_device *p_dev)
{
    tNFC_HAL_MSG *msg;

    OSI_logt("enter;");

    msg = (tNFC_HAL_MSG*)OSI_mem_get(HAL_EVT_SIZE);
    if (msg != NULL)
    {
        msg->event = HAL_EVT_TERMINATE;
        OSI_queue_put(nfc_hal_info.msg_q, (void *)msg);
    }
    OSI_logt("enter;");
    OSI_task_stop(nfc_hal_info.msg_task);
    OSI_logt("enter;");

    device_sleep();
    device_close();

    nfc_stack_cback(HAL_NFC_CLOSE_CPLT_EVT, HAL_NFC_STATUS_OK);

    OSI_logt("exit;");
    return 0;
}

int nfc_hal_write(const struct nfc_nci_device *p_dev,
    uint16_t data_len,
    const uint8_t *p_data)
{
    tNFC_HAL_MSG *msg;
    size_t size = (size_t)data_len;

    OSI_logt("enter;");

    msg = (tNFC_HAL_MSG*)OSI_mem_get(size + HAL_EVT_SIZE);
    if (msg != NULL)
    {
        msg->event = HAL_EVT_WRITE;
        memcpy((uint8_t*)&msg->nci_packet, p_data, size);

        OSI_queue_put(nfc_hal_info.msg_q, (void *)msg);
    }

    OSI_logt("exit;");
    return 0;
}

int nfc_hal_core_initialized(const struct nfc_nci_device *p_dev,
    uint8_t* p_core_init_rsp_params)
{
    tNFC_HAL_MSG *msg;
    size_t size = (size_t)p_core_init_rsp_params[2] + 3;

    OSI_logt("enter;");

    msg = (tNFC_HAL_MSG*)OSI_mem_get(size + HAL_EVT_SIZE);
    if (msg != NULL)
    {
        msg->event = HAL_EVT_CORE_INIT;
        memcpy((uint8_t*)&msg->nci_packet, p_core_init_rsp_params, size);

        OSI_queue_put(nfc_hal_info.msg_q, (void *)msg);
    }
    OSI_logt("exit;");
    return 0;
}

int nfc_hal_pre_discover(const struct nfc_nci_device *p_dev)
{
    tNFC_HAL_MSG *msg;

    OSI_logt("enter;");

    msg = (tNFC_HAL_MSG*)OSI_mem_get(HAL_EVT_SIZE);
    if (msg != NULL)
    {
        msg->event = HAL_EVT_PRE_DISCOVER;
        OSI_queue_put(nfc_hal_info.msg_q, (void *)msg);
    }
    OSI_logt("exit;");
    return 0;
}

int nfc_hal_control_granted(const struct nfc_nci_device *p_dev)
{
    tNFC_HAL_MSG *msg;

    OSI_logt("enter;");

    msg = (tNFC_HAL_MSG*)OSI_mem_get(HAL_EVT_SIZE);
    if (msg != NULL)
    {
        msg->event = HAL_EVT_CONTROL_GRANTED;
        OSI_queue_put(nfc_hal_info.msg_q, (void *)msg);
    }
    OSI_logt("exit;");
    return 0;
}

int nfc_hal_power_cycle(const struct nfc_nci_device *p_dev)
{
    OSI_logt("enter;");
    OSI_logt("exit;");
    return 0;
}

void setSleepTimeout(int option, uint32_t timeout)
{
    nfc_hal_info.flag &= ~HAL_FLAG_PROP_ONE_TIMER;
    nfc_hal_info.cfg.override_timeout = 0;

    if (option == SET_SLEEP_TIME_CFG)
    {
        if (!get_config_int(cfg_name_table[CFG_SLEEP_TIMEOUT], (int *)&nfc_hal_info.cfg.sleep_timeout))
            nfc_hal_info.cfg.sleep_timeout = timeout;
    }
    else if (option == SET_SLEEP_TIME_ONCE)
    {
        nfc_hal_info.cfg.override_timeout = timeout;
        nfc_hal_info.flag |= HAL_FLAG_PROP_ONE_TIMER;
    }
    else if (option == SET_SLEEP_TIME_FORCE)
        nfc_hal_info.cfg.sleep_timeout = timeout;
    else
        ALOGE("Unknown option: %d", option);

    if (nfc_hal_info.flag & HAL_FLAG_PROP_ONE_TIMER)
        OSI_logd("Override timeout is %d ms", nfc_hal_info.cfg.override_timeout);
    OSI_logd("Sleep timeout is %d ms", nfc_hal_info.cfg.sleep_timeout);
}
