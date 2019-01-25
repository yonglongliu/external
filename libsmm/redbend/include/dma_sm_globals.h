/*
 *******************************************************************************
 *
 * dma_sm_globals.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	dma_sm_globals.h
 *
 * \brief	DMA internal globals
 *******************************************************************************
 */

#ifndef _DMA_SM_GLOBALS_H_
#define _DMA_SM_GLOBALS_H_

#ifdef __cplusplus
extern "C" {
#endif

#define NIA_INITIATOR_ID "DMA_NIA_DM_SESSION"

/* Relevant to Roaming, RTT VDO (coverage), EMERGENCY MODE */
#define FALSE   0                               //!< False
#define TRUE    1                               //!< True

// TRUE
#define SED_ERR_NOT_PROVISIONED     1
#define SED_ERR_ALREADY_LOCKED      2
#define SED_ERR_ALREADY_UNLOCKED    3

#define LAWMO_OPERATION_TYPE_UNDEFINED 9999

#define BEFORE_DM_CONDITIONS_TIMEOUT_SEC 10
#define NETWORK_TYPE_TIMEOUT_SEC 10
#define SCOUT_TIMEOUT 60

typedef enum {
	CANCEL_SESSION_NO_CANCEL = 0,
	CANCEL_SESSION_PUSH_LAWMO = 1,
	CANCEL_SESSION_PURGE_UPDATE = 2
} CANCEL_SESSION_TYPE_t;

/* All conditions which won't be checked during DM session should be placed
 * at end of conditions_types_t enum */
typedef enum {
	CONDITIONS_BEFORE_DM,
	CONDITIONS_BEFORE_PRE_INSTALL,
	CONDITIONS_BEFORE_INSTALL,
	CONDITIONS_BEFORE_POST_INSTALL,
	CONDITIONS_BEFORE_USB,
	CONDITIONS_BEFORE_REPORT,
    CONDITIONS_BEFORE_PRE_ROLLBACK_INSTALL,
    CONDITIONS_BEFORE_ROLLBACK_INSTALL,
    CONDITIONS_BEFORE_POST_ROLLBACK_INSTALL,
	CONDITIONS_LENGTH//this must be the last literal in the enum
} conditions_types_t;

typedef enum {
	CONDITIONS_EVENT_CONDITIONS_NOT_MET,
	CONDITIONS_EVENT_CONDITIONS_MET,
	CONDITIONS_EVENT_NO_CONDITIONS, //no conditions file
	CONDITIONS_EVENT_ERROR,//error parsing conditions file
	CONDITIONS_EVENT_ERROR_VALIDATION//error during validation xml file
} conditions_met_t;

typedef enum {
	LOADING_PAGE_CHECKING,
	LOADING_PAGE_INIT
} LOADING_PAGE_MESSAGE_TYPE_t;

/*
 * Network type definitions
 */
typedef enum {
	E_NETWORK_TYPE_UNKNOWN,
	E_NETWORK_TYPE_WIFI,
	E_NETWORK_TYPE_DATA,
	E_NETWORK_TYPE_EXTERNAL
} E_NETWORK_TYPES;

typedef enum {
	E_NETWORK_PROXY_STATE_Disabled = 0,
	E_NETWORK_PROXY_STATE_Enabled
} E_NETWORK_PROXY_STATE;

typedef enum {
	E_INSTALL_TYPE_Internal = 0,
	E_INSTALL_TYPE_ExternalDlAndInstall,
	E_INSTALL_TYPE_ExternalInstallOnly
} E_INSTALL_TYPE_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _DMA_SM_GLOBALS_H_ */

