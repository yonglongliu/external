/*
 *******************************************************************************
 *
 * vdm_scomo_dc_types.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_scomo_dc_types.h
 *
 * \brief	SCOMO Deployment Component (DC) Types and Constants
 ******************************************************************************
 */
#ifndef _VDM_SCOMO_DC_TYPES_H_
#define _VDM_SCOMO_DC_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *******************************************************************************
 * Callback invoked when starting DC deployment.
 *
 * \param	inScomoDCInstance	Handle to relevant SCOMO DC object.
 * \param	inDmcContext		Context passed in during instance creation.
 * \param	outResult			Used in synchronous operations only.
 *
 * \return	TRUE if synchronous operation has finished, or FALSE if asynchronous
 *			operation, in which case notify SCOMO DC upon completion by calling
 *			\ref VDM_SCOMO_DC_setDeploymentResult
 *******************************************************************************
 */
typedef IBOOL (*VDM_SCOMO_DC_DeployCB)(
	VDM_Handle_t inScomoDCInstance,
	void *inDmcContext,
	E_VDM_SCOMO_RESULT_t *outResult);

/*!
 *******************************************************************************
 * Callback invoked to confirm DC installation.
 *
 * \param	inScomoDCInstance	Handle to relevant SCOMO DC object.
 * \param	inDmcContext		Context passed in during instance creation.
 *
 * \return	TRUE to start installation, FALSE to postpone installation until
 *			calling \ref VDM_SCOMO_DP_executeInstall or after a reboot
 *******************************************************************************
 */
typedef IBOOL (*VDM_SCOMO_DC_ConfirmCB)(
	VDM_Handle_t inScomoDCInstance,
	void *inDmcContext);

/*!
 * Callbacks that may be implemented externally.
 */
typedef struct {
	VDM_SCOMO_DC_ConfirmCB confirmRemoveCB;                     //!< Confirm removing DC callback (optional, may be NULL)
	VDM_SCOMO_DC_DeployCB executeRemoveCB;                      //!< Remove DC callback (optional, may be NULL)
	VDM_SCOMO_DC_ConfirmCB confirmActivationCB;                 //!< Confirm activating DC callback (optional, may be NULL)
	VDM_SCOMO_DC_DeployCB activateCB;                           //!< Activate DC callback (optional, may be NULL)
	VDM_SCOMO_DC_ConfirmCB confirmDeactivationCB;               //!< Confirm deactivatng DC callback (optional, may be NULL)
	VDM_SCOMO_DC_DeployCB deactivateCB;                         //!< Deactivate DC callback (optional, may be NULL)
} VDM_SCOMO_DC_Callbacks_t;

/**! SCOMO DC should be included in the report status */
typedef enum {
	E_VDM_SCOMO_DC_InReport_ShouldNotBe,    //!< The component should not be included in the report (e.g. was already reported)
	E_VDM_SCOMO_DC_InReport_ShouldBe,       //!< The component should be included in the report
	E_VDM_SCOMO_DC_InReport_InProgress      //!< The component is now reported
} E_VDM_SCOMO_DC_InReport_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

