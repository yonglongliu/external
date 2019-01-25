/*
 *******************************************************************************
 *
 * dma_sm_dil_globals.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	dma_sm_dil_globals.h
 *
 * \brief	Common code between DMA and DIL
 *******************************************************************************
 */

#ifndef _DMA_SM_DIL_GLOBALS_H_
#define _DMA_SM_DIL_GLOBALS_H_

#include "vdm_pl_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* IPL TYPES */
#define IPL_TYPE_BOOTSTRAP_GET_NSS     3        //!< Get bootstrap NSS - 3 was kept as legacy

// The following is a list of the values of DMA_VDM_ERR sent from BL to DIL
#define ERR_TYPE_NONE 0                             //!< No error
#define ERR_TYPE_DL_GENERAL                 0x6380  //!< Download general error /* 25472 */
#define ERR_TYPE_DL_NETWORK                 0x6381  //!< Download network error
#define ERR_TYPE_DM_GENERAL                 0x6382  //!< DM general error
#define ERR_TYPE_DM_NETWORK                 0x6383  //!< DM network error
#define ERR_TYPE_DM_NO_PKG                  0x6384  //!< No new update
#define ERR_TYPE_DM_SESSION_IN_PROGRESS     0x6385  //!< DM session in progress -- 25477
#define ERR_TYPE_ROAMING_OR_EMERGENCY       0x6386  //!< Device roaming or in emergency mode
#define ERR_TYPE_WIFI_NOT_AVAILABLE         0x6387  //!< WI-FI not available while WifiOnly is enabled
#define ERR_TYPE_FLOW_IN_PROGRESS           0x6388  //!< A DM flow scenario is in progress -- 25480
#define ERR_TYPE_USER_INTERACTION_TIMEOUT   0x6389  //!< Timeout on user response to GUI choice screen
#define ERR_TYPE_INSTALLATION_COND_TIMEOUT   0x638A //!< Timeout on getting installation conditions
#define ERR_TYPE_INSTALLATION_COND_XML_ERROR 0x638B //!< Bad installation conditions XML file
#define ERR_TYPE_INSTALLATION_COND_VALIDATION_ERROR 0x6398  //!< installation conditions validation error

#define ERR_TYPE_PURGE_INVALIID_DP          0x638C  //!< invalid DP because of purge update
#define ERR_TYPE_EXTERNAL_DL_TIMEOUT        0x638D  //!< Timeout of external download (exp. ACP Download)
#define ERR_TYPE_CONDITIONS_BEFORE_DM       0x638E  //!< Before DM conditions failed
#define ERR_TYPE_INITIALIZE_IN_PROGRESS     0x638F  //!< Initialize in Progress Error
#define ERR_TYPE_DL_WINDOW                  0x6390  //!< DL canceled (suspended) because of window reached
#define ERR_TYPE_DL_CANCELED_BY_USER        0x6391  //!< DL rejected by user
#define ERR_TYPE_DL_RESTARTED_BY_USER       0x6392  //!< DL restarted by user
#define ERR_TYPE_DL_CANCELED_BY_SERVER      0x6393  //!< DL canceled by server
#define ERR_TYPE_DL_CANCELED_EXTERNAL_TO    0x6394  //!< DL canceled due to external TO expiration
#define ERR_TYPE_DL_CANCELED_GOING_EXTERNAL 0x6395  //!< DL is canceled in terms of internal download (WI-FI, 3G etc.) due to moving to external download
#define ERR_TYPE_DL_CANCELED_MAX_RETRY_REACHED  0x6396 //!< DL canceled due to max retries to resume is reached
#define ERR_TYPE_REGISTER_EXT_CB_FAILED     0x6397  //!< Register external callback failed
#define ERR_TYPE_DL_CANCELED_DUE_TO_POLICY  0x639A //!< DL canceled due to device update policy

#define ERR_TYPE_COND_XML_EMPTY             0x639B  //!< Condition xml file is empty
#define ERR_TYPE_COND_XML_LARGE             0x639C  //!< Condition xml file is too large
#define ERR_TYPE_COND_XML_SYNTAX            0x639D  //!< Condition xml file has syntax error

#define ERR_TYPE_DL_SWITCHED_TO_USB         0x6403 //!< DL canceled due to switch to USB update flow
#define ERR_TYPE_DL_CANCEL                  0x6404  //!< DL canceled
#define ERR_TYPE_DM_ACCOUNT_DOES_NOT_EXIST  0x9003  //!< DM account, its nodes or values do not exist
/*! Error while parsing Download Descriptor - descriptor size is 0*/
#define ERR_TYPE_BAD_DD_INVALID_SIZE        0x6409 /* 25609 */
#define ERR_TYPE_INSTALL_SETUP_FAILED       0x640A /* 25610 */
#define ERR_TYPE_SYSTEM_RESOURCE_FAILURE    0x640D /* 25613 */

#define ERR_TYPE_DIL_RESPONCE_TIMEOUT    	0x640B /* 25611 */ //Timeout on DIL response to bl


/* DMA_VAR_PRODUCT_TYPE */
#define PRODUCT_SWMC_SYSTEM     0           //!< system swm client
#define PRODUCT_SWMC_DOWNLOADABLE_TRUE  1           //!< downloadable for TRUE swm client
#define PRODUCT_SWMC_DOWNLOADABLE   2           //!< downloadable swm client non TRUE

/* Since D2B_SCOMO_ACCEPT serves different purposes, we want to know
 * the specific purpose that the event was sent. */
typedef enum {
	E_SCOMO_ConfirmationPurpose_DOWNLOAD = 1,
	E_SCOMO_ConfirmationPurpose_INSTALL = 2,
	E_SCOMO_ConfirmationPurpose_REBOOT = 3
} E_SCOMO_ConfirmationPurpose_t;

/*
 * The time the DMA will wait for response from the DIL.
 */
IU32 getDilResponseTimeout(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _DMA_SM_DIL_GLOBALS_H_ */

