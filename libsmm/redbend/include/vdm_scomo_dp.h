/*
 *******************************************************************************
 *
 * vdm_scomo_dp.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_scomo_dp.h
 *
 * \brief	SCOMO Delivery Package (DP)
 *******************************************************************************
 */
#ifndef _VDM_SCOMO_DP_H_
#define _VDM_SCOMO_DP_H_

#ifdef __cplusplus
extern "C" {
#endif
#include <vdm_scomo_types.h>
#include <vdm_scomo_dp_types.h>
/*!
 *******************************************************************************
 * Create a SCOMO DP instance.
 *
 * \param	inScomoDPName   Name of the DP.
 * \param	inCallbacks		Callbacks structure.
 * \param	inContext		Context passed as a parameter of the callbacks in
 *							\a inCallbacks.
 *
 * \return	Handle to the SCOMO DP instance on success, NULL on error
 *******************************************************************************
 */
extern VDM_Handle_t VDM_SCOMO_DP_createInstance(
	const char *inScomoDPName,
	VDM_SCOMO_DP_Callbacks_t *inCallbacks,
	void *inContext);

/*!
 *******************************************************************************
 * Set the callbacks for a SCOMO DP instance.
 *
 * \param	inScomoDPInstance   Handle to the SCOMO DP instance.
 * \param	inCallbacks			Callbacks structure.
 * \param	inContext			Context passed as a parameter of the callbacks
 *								in \a inCallbacks.
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_SCOMO_DP_setCallbacks(
	VDM_Handle_t inScomoDPInstance,
	VDM_SCOMO_DP_Callbacks_t *inCallbacks,
	void *inContext);

/*!
 *******************************************************************************
 * Destroy the SCOMO DP instance. Free memory and destroy data members.
 *
 * \param	ioScomoDPInstance	Input: Handle to the SCOMO DP instance.
 *								Output: NULL.
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_SCOMO_DP_destroyInstance(VDM_Handle_t *ioScomoDPInstance);

/*!
 *******************************************************************************
 * Get status of a DP installation. Called by the client to find out if the
 * DP is available on the device and ready to be updated.
 *
 * \param	inScomoDPInstance	Handle to the SCOMO DP instance.
 * \param	outStatus			Installation status.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DP_getProcessStatus(
	VDM_Handle_t inScomoDPInstance,
	E_VDM_SCOMO_Operation_Status_t *outStatus);

/*!
 *******************************************************************************
 * Install the DP. Called by the client.
 *
 * \param	inScomoDPInstance	Handle to the SCOMO DP instance.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DP_executeInstall(VDM_Handle_t inScomoDPInstance);

/*!
 *******************************************************************************
 * Get a SCOMO DP instance package id.
 *
 * \param	inScomoDPInstance	Handle to the SCOMO DP instance.
 * \param	inBuffer			Pre-allocated result buffer for the package id.
 * \param	ioLength			Input: Size of the result buffer.
 *								Output: Length of data in the result buffer.
 *
 * If the supplied buffer is too short then as much data as will fit in the
 * buffer is returned along with the error code VDM_ERR_BUFFER_OVERFLOW.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BUFFER_OVERFLOW if the buffer is too small,
 *			or another \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DP_getId(
	VDM_Handle_t inScomoDPInstance,
	char *inBuffer,
	IU32 *ioLength);

/*!
 *******************************************************************************
 * Get SCOMO DP instance package URL.
 *
 * \param	inScomoDPInstance	Handle to the SCOMO DP instance.
 * \param	inBuffer			Pre-allocated result buffer for the package URL.
 * \param	ioLength			Input: Size of the result buffer.
 *								Output: Length of data in the result buffer.
 *
 * If the supplied buffer is too short then as much data as will fit in the
 * buffer is returned along with the error code VDM_ERR_BUFFER_OVERFLOW.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BUFFER_OVERFLOW if the buffer is too small,
 *			or another \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DP_getUrl(
	VDM_Handle_t inScomoDPInstance,
	char *inBuffer,
	IU32 *ioLength);

/*!
 *******************************************************************************
 * Get SCOMO DP instance package name.
 *
 * \param	inScomoDPInstance	Handle to the SCOMO DP instance.
 * \param	inBuffer			Pre-allocated result buffer for the package
 *								name.
 * \param	ioLength			Input: Size of the result buffer.
 *								Output: Length of result data.
 *
 * If the supplied buffer is too short then as much data as will fit in the
 * buffer is returned along with the error code VDM_ERR_BUFFER_OVERFLOW.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BUFFER_OVERFLOW if the buffer is too small,
 *			or another \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DP_getName(
	VDM_Handle_t inScomoDPInstance,
	char *inBuffer,
	IU32 *ioLength);

/*!
 *******************************************************************************
 * Get SCOMO DP instance package description.
 *
 * \param	inScomoDPInstance	Handle to the SCOMO DP instance.
 * \param	inBuffer			Pre-allocated result buffer for the package
 *								description.
 * \param	ioLength			Input: Size of the result buffer.
 *								Output: Length of result data.
 *
 * If the supplied buffer is too short then as much data as will fit in the
 * buffer is returned along with the error code VDM_ERR_BUFFER_OVERFLOW.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BUFFER_OVERFLOW if the buffer is too small,
 *			or another \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DP_getDescription(
	VDM_Handle_t inScomoDPInstance,
	char *inBuffer,
	IU32 *ioLength);

/*!
 *******************************************************************************
 * Get SCOMO DP instance package environment type.
 *
 * \param	inScomoDPInstance	Handle to the SCOMO DP instance.
 * \param	inBuffer			Pre-allocated result buffer for the package
 *								environment type.
 * \param	ioLength			Input: Size of the result buffer.
 *								Output: Length of result data.
 *
 * If the supplied buffer is too short then as much data as will fit in the
 * buffer is returned along with the error code VDM_ERR_BUFFER_OVERFLOW.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BUFFER_OVERFLOW if the buffer is too small,
 *			or another \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DP_getEnvType(
	VDM_Handle_t inScomoDPInstance,
	char *inBuffer,
	IU32 *ioLength);

/*!
 *******************************************************************************
 * Get SCOMO DP instance package type.
 *
 * \param	inScomoDPInstance	Handle to the SCOMO DP instance.
 * \param	inBuffer			Pre-allocated result buffer for the package
 *								type.
 * \param	ioLength			Input: Size of the result buffer.
 *								Output: Length of result data.
 *
 * If the supplied buffer is too short then as much data as will fit in the
 * buffer is returned along with the error code VDM_ERR_BUFFER_OVERFLOW.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BUFFER_OVERFLOW if the buffer is too small,
 *			or another \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DP_getType(
	VDM_Handle_t inScomoDPInstance,
	char *inBuffer,
	IU32 *ioLength);

/*!
 *******************************************************************************
 * Get SCOMO DP instance installation parameters string.
 *
 * \param	inScomoDPInstance	Handle to the SCOMO DP instance.
 * \param	inBuffer			Pre-allocated result buffer for the installation
 *								parameters string.
 * \param	ioLength			Input: Size of the result buffer.
 *								Output: Length of result data.
 *
 * If the supplied buffer is too short then as much data as will fit in the
 * buffer is returned along with the error code VDM_ERR_BUFFER_OVERFLOW.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BUFFER_OVERFLOW if the buffer is too small,
 *			or another \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DP_getInstallParams(
	VDM_Handle_t inScomoDPInstance,
	char *inBuffer,
	IU32 *ioLength);

/*!
 *******************************************************************************
 * Get SCOMO DP instance path.
 *
 * \param	inScomoDPInstance	Handle to the SCOMO DP instance.
 * \param	inBuffer			Pre-allocated result buffer for the package
 *								path.
 * \param	ioLength			Input: Size of the result buffer.
 *								Output: Length of result data.
 *
 * If the supplied buffer is too short then as much data as will fit in the
 * buffer is returned along with the error code VDM_ERR_BUFFER_OVERFLOW.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BUFFER_OVERFLOW if the buffer is too small,
 *			or another \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DP_getDeliveryPkgPath(VDM_Handle_t inScomoDPInstance,
	char *inBuffer, IU32 *ioLength);

/*!
 *******************************************************************************
 * Resume an aborted SCOMO DP download session.
 *
 * \param	inScomoDpInstance			Handle to the SCOMO DP instance.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_OUT_OF_SYNC if SCOMO is not is in a middle of a download
 *			session,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			VDM_ERR_TREE_ACCESS_DENIED if access is denied, or
 *			VDM_ERR_NODE_MISSING if the node is missing from the DM Tree
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DP_resumeDLSession(
	VDM_Handle_t inScomoDpInstance);

/*!
 *******************************************************************************
 * Trigger a SCOMO DP report session (generic alert).
 *
 * Called by the client application after a DP installation completed, either
 * successfully or failed, such as a download failure, user abort, and so on.
 *
 * \since	vDM 4.5
 * \param	inScomoDPInstance	Handle to the SCOMO DP instance.
 * \param	inResultCode		Result code, an \ref E_VDM_SCOMO_RESULT_t value
 *								or in the vendor-specified range:
 *								1250-1299: Successful - Vendor Specific,
 *								1450-1499: Client Error - Vendor Specific,
 *								1550-1599: DL Server Error - Vendor Specific
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_MEMORY if no memory to perform action, or
 *			VDM_ERR_MO_STORAGE if persistent storage cannot be read
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DP_triggerReportSession(
	VDM_Handle_t inScomoDPInstance,
	E_VDM_SCOMO_RESULT_t inResultCode);

/*!
 *******************************************************************************
 * Remove DP related files
 *
 * \param    inScomoDPInstance       SCOMO DP Instance
 *
 *******************************************************************************
 */
void VDM_SCOMO_DP_updatePkgCleanup(VDM_Handle_t inScomoDPInstance);

/*!
 *******************************************************************************
 * Get whether a SCOMO DP instance is the session-initiator.
 *
 * Typically called from \ref VDM_SessionStateNotifyCB callback.
 *
 * \param	inSessContext		Session context.
 * \param	outScomoDPInstance	Handle to the SCOMO DP instance which triggered
 *								this session, or NULL if initiator is
 *								not a SCOMO DP object.
 *
 * \return	TRUE if  vDM SCOMO DP component is the session-initiator,
 *			FALSE otherwise.
 *******************************************************************************
 */
extern IBOOL VDM_SCOMO_DP_getSessionInitiator(
	VDM_SessionContext_t *inSessContext,
	VDM_Handle_t *outScomoDPInstance);

/*!
 *******************************************************************************
 * Get SCOMO DP <x> node.
 *
 * \param	inScomoDPInstance		SCOMO DP Instance.
 *
 * \return	URI of ./SCOMO/Download/<x> ,or, ./SCOMO/Inventory/Delivered/<x>
 *******************************************************************************
 */
extern const char *VDM_SCOMO_DP_getRoot(VDM_Handle_t inScomoDPInstance);

/*!
 *******************************************************************************
 * Perform a locally-initiated EXEC install operation on an existing SCOMO DP.
 * This function should be called after preparation was done.
 * \see VDM_SCOMO_DP_prepareLocalExec
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DP_doLocalExec(void);

/*!
 *******************************************************************************
 * Prepare the internal and persistent data structures for locally-initiated
 * EXEC install operation.
 * This function should be called before performing local installation.
 * \see VDM_SCOMO_DP_doLocalExec
 *
 * \param	inPkgName		    The name of the SCOMO DP package in the file
 *                              system.
 * \param	inCorrelator		The correlator to use in the report sent to the
 *                              server.
 * \param	inDdName			The DD file name for clean up
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DP_prepareLocalExec(const char *inPkgName,
	const char *inCorrelator, char *inDdName);

extern void *VDM_SCOMO_DP_getContext(VDM_Handle_t inScomoDPInstance);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

