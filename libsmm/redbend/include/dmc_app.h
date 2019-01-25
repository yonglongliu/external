/*
 *******************************************************************************
 *
 * dmc_app.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file dmc_app.h
 *
 * \brief DM Client application.
 *******************************************************************************
 */

#ifndef _DM_CLIENT_APPLICAIONT_H_
#define _DM_CLIENT_APPLICAIONT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <vdm_smm.h>

#define DMCOPT_LOGFILE_DIR						((const char *)"com.redbend.dmc.logfile.dir")

#define DMCOPT_IMEI_GET_FUNCTION				((const char *)"com.redbend.dmc.imei.fun")
#define DMCOPT_IMSI_GET_FUNCTION				((const char *)"com.redbend.dmc.imsi.fun")
#define DMCOPT_CARRIER_GET_FUNCTION				((const char *)"com.redbend.dmc.carrier.fun")
#define DMCOPT_ACTIVATION_MODE_GET_FUNCTION		((const char *)"com.redbend.dmc.activation.mode.fun")
#define DMCOPT_ANDROID_VERSION_GET_FUNCTION		((const char *)"com.redbend.dmc.android.version.fun")
#define DMCOPT_BASEBAND_VERSION_GET_FUNCTION	((const char *)"com.redbend.dmc.baseband.version.fun")
#define DMCOPT_BUILD_NUMBER_GET_FUNCTION		((const char *)"com.redbend.dmc.build.number.fun")
#define DMCOPT_CELL_ID_GET_FUNCTION				((const char *)"com.redbend.dmc.cell.id.fun")
#define DMCOPT_MANUFACTURE_GET_FUNCTION			((const char *)"com.redbend.dmc.manufacture.fun")
#define DMCOPT_DEVICE_MODEL_GET_FUNCTION		((const char *)"com.redbend.dmc.model.fun")

#define DMCOPT_UIEVENT_FUNCTION					((const char *)"com.redbend.dmc.ui.event.fun")
#define DMCOPT_ALARM_SET_FUNCTION				((const char *)"com.redbend.dmc.alarm.set.fun")
#define DMCOPT_ALARM_RESET_FUNCTION				((const char *)"com.redbend.dmc.alarm.reset.fun")
#define DMCOPT_WAKELOCK_ACQUIRE_FUNCTION		((const char *)"com.redbend.dmc.wakelock.acquire.fun")
#define DMCOPT_WAKELOCK_RELEASE_FUNCTION		((const char *)"com.redbend.dmc.wakelock.release.fun")

/* callback to get IMEI by index. index=0: IMEI0 and index=1: IMEI1,
 * IMEI0 as device Id is mandatory
 * if IMEI1 absent, return VDM_ERR_NOT_IMPLEMENTED
 * else return the string of IMEI with VDM_ERR_OK
 */
typedef int (*DMC_OPT_Imei_get_fn)(int index, char *buffer, int *size);

/* callback to get IMSI by index. 
 * index=0: IMSI0 of SIM card on slot0
 * index=1: IMSI1 of SIM card on slot1
 * if SIM unavailable, return VDM_ERR_NOT_INITILIZED
 * if SIM abset, return VDM_ERR_NOT_IMPLEMENTED
 * else return the string of IMSI with VDM_ERR_OK
 */
typedef int (*DMC_OPT_Imsi_get_fn)(int index, char *buffer, int *size);

/* callback to get the details for all devices based on carrier by index.
 * index=0: Carrier of SIM0 connecting
 * index=1: Carrier of SIM1 connecting
 * if SIM unavailable, return VDM_ERR_NOT_INITILIZED
 * if SIM abset, return VDM_ERR_NOT_IMPLEMENTED
 * else return the string of the carrier with VDM_ERR_OK
 */
typedef int (*DMC_OPT_Carrier_get_fn)(int index, char *buffer, int *size);

/* callback to get the details for all devices based on activation modes (2g, 3g, 4g, Wi-Fi). 
 * return the string of the modes with VDM_ERR_OK, or error code
 */
typedef int (*DMC_OPT_ActivationMode_get_fn)(char *buffer, int *size);

/* callback to get the android version (eg. 5.1, 6.0, 6.0.1). 
 * return the string of the modes with VDM_ERR_OK
 */
typedef int (*DMC_OPT_AndroidVersion_get_fn)(char *buffer, int *size);

/* callback to get the baseband version (eg. 2.1, -8976_GEN_PACK-1.62825.1.64990.1). 
 * return the string of the modes with VDM_ERR_OK
 */
typedef int (*DMC_OPT_BasebandVersion_get_fn)(char *buffer, int *size);

/* callback to get the build number (eg. 1.2, LS-5201-S10A_LYF_L13EN_200_USERDEBUG_160811).
 * as well as firmware version for FOTA
 * return the string of the modes with VDM_ERR_OK
 */
typedef int (*DMC_OPT_BuildNumber_get_fn)(char *buffer, int *size);

/* callback to get the cell Id(Primary slot). 
 * return the string of the modes with VDM_ERR_OK
 */
typedef int (*DMC_OPT_CellId_get_fn)(char *buffer, int *size);

/* callback to get the manufacturer. 
 * return the string of the modes with VDM_ERR_OK
 */
typedef int (*DMC_OPT_Manufacturer_get_fn)(char *buffer, int *size);

/* callback to get the device model. 
 * return the string of the modes with VDM_ERR_OK
 */
typedef int (*DMC_OPT_DeviceModel_get_fn)(char *buffer, int *size);

/* callback to notify a ui event coming. 
 * extract the event name by "event->name", and handle it properly
 *
 * The details of VDM_SMM_Event_t on vdm_smm_types.h
 */
typedef void (*VDM_SMM_UiEvent_fn)(VDM_SMM_Event_t *event);

/* callback to set alarm, called from SMM PL, alarmId is used to identify if
 * the alarm is reset, or when the alarm expires, secs is relative -- in how
 * much time the alarm should expire */
typedef int (*VDM_SMM_AlarmCb_set_fn)(int alarmId, unsigned long secs);

/* callback to reset the alarm set, called from SMM PL */
typedef void (*VDM_SMM_AlarmCb_reset_fn)(int alarmId);

/* callback to acquire the wakelock, called from SMM PL */
typedef int (*VDM_SMM_WakeLock_acquire_fn)(void);

/* callback to acquire the wakelock, called from SMM PL */
typedef int (*VDM_SMM_WakeLock_release_fn)(void);

/* DM engine creating and initialization
 * workDir: The Engine’s working directory; 
 *  puts tree.xml and relevant information in this location 
 *  together with any other files that the Client needs.
 *  Note: The Client must have R/W permissions to the working directory.
 * configFile: The location of config file dma_config.txt
 * return the result of engine initialization
 */
int Java_com_redbend_client_BasicService_initEngine(const char *workDir, const char *configFile);

/* DM engine destroy */
void Java_com_redbend_client_BasicService_destroyEngine(void);

/* Start and stop all the BLs */
void Java_com_redbend_client_BasicService_startSmm(void);
void Java_com_redbend_client_BasicService_stopSmm(void);

/* Set option for configuration and callback registration
 * option: the target option to be set
 * value: the configuration value or callback function
 * return the result of option setting
 */
int Java_com_redbend_client_BasicService_setOption(const char *option, const void *value);

/* Send a event to DM engine
 * event: the event to DM engine
 */
void Java_com_redbend_client_BasicService_sendEvent(VDM_SMM_Event_t *event);

/* Alarm expiration notifing
 * alarmId: the expired alarm Id
 *  Register a callback via DMCOPT_ALARM_SET_FUNCTION for BL setting alarm,
 *  BL call the callback registered by DMCOPT_ALARM_RESET_FUNCTION when the alarm need reset, 
 *  If the alarm expired, invoke this function to notify BL
 */
void Java_com_redbend_client_BasicService_alarmExpire(int alarmId);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
