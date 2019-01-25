/*
 *******************************************************************************
 *
 * vdm_scomo_dc.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_scomo_dc.h
 *
 * \brief	SCOMO Deployment Component (DC)
 *******************************************************************************
 */
#ifndef _VDM_SCOMO_DC_H_
#define _VDM_SCOMO_DC_H_

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *******************************************************************************
 * Create a SCOMO DC instance.
 *
 * \param	inScomoDCName   DC name.
 * \param	inCallbacks		Callbacks structure.
 * \param	inContext		Context passed as a parameter of the callbacks in
 *							\a inCallbacks.
 *
 * \return	Handle to the SCOMO DC instance on success, NULL on error
 *******************************************************************************
 */
extern VDM_Handle_t VDM_SCOMO_DC_createInstance(const char *inScomoDCName,
	VDM_SCOMO_DC_Callbacks_t *inCallbacks, void *inContext);

/*!
 *******************************************************************************
 * Set the callbacks for a SCOMO DC instance.
 *
 * \param	inScomoDCInstance   Handle to the SCOMO DC instance.
 * \param	inCallbacks			Callbacks structure.
 * \param	inContext			Context passed as a parameter of the callbacks
 *								in \a inCallbacks.
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_SCOMO_DC_setCallbacks(VDM_Handle_t inScomoDCInstance,
	VDM_SCOMO_DC_Callbacks_t *inCallbacks, void *inContext);
/*!
 *******************************************************************************
 * Destroy SCOMO DC instance. Free memory and destroy data members.
 *
 * \param	ioScomoDCInstance		Input: Handle to the SCOMO DC instance.
 *									Output: NULL.
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_SCOMO_DC_destroyInstance(VDM_Handle_t *ioScomoDCInstance);

/*!
 *******************************************************************************
 * Get DC process status. Called by the client to find out if the process
 * has been postponed.
 *
 * \param	inScomoDCInstance	Handle to the SCOMO DC instance.
 * \param	outStatus			Process status.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_MEMORY if no memory to perform action, or
 *			VDM_ERR_BAD_INPUT if invalid input
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DC_getProcessStatus(VDM_Handle_t inScomoDCInstance,
	E_VDM_SCOMO_DC_Operation_Status_t *outStatus);

/*!
 *******************************************************************************
 * Notify server after a DC process (activation, deactivation, or removal) ends.
 *
 * \param	inScomoDCInstance	 Handle to the SCOMO DC instance.
 * \param	inResult			 Result of the DC process.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_MEMORY if no memory to perform action,
 *			VDM_ERR_BAD_INPUT if invalid input,
 *			VDM_ERR_UNSPECIFIC if operation on inventory failed
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DC_setDeploymentResult(VDM_Handle_t inScomoDCInstance,
	E_VDM_SCOMO_RESULT_t inResult);

/*!
 *******************************************************************************
 * Remove a DC. Called by the client.
 *
 * \param	inScomoDCInstance	Handle to the SCOMO DC instance.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_MEMORY if no memory to perform action,
 *			VDM_ERR_TREE_ACCESS_DENIED if access denied, or
 *			VDM_ERR_NODE_MISSING if data is missing
 *******************************************************************************
 */
VDM_Error VDM_SCOMO_DC_executeRemove(VDM_Handle_t inScomoDCInstance);

/*!
 *******************************************************************************
 * Activate a DC. Called by the client.
 *
 * \param	inScomoDCInstance	Handle to the SCOMO DC instance.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_MEMORY if no memory to perform action,
 *			VDM_ERR_TREE_ACCESS_DENIED if access denied, or
 *			VDM_ERR_NODE_MISSING if data is missing
 *******************************************************************************
 */
VDM_Error VDM_SCOMO_DC_executeActivate(VDM_Handle_t inScomoDCInstance);

/*!
 *******************************************************************************
 * Deactivate a DC. Called by the client.
 *
 * \param	inScomoDCInstance	Handle to the SCOMO DC instance.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_MEMORY if no memory to perform action,
 *			VDM_ERR_TREE_ACCESS_DENIED if access denied, or
 *			VDM_ERR_NODE_MISSING if data is missing
 *******************************************************************************
 */
VDM_Error VDM_SCOMO_DC_executeDeactivate(VDM_Handle_t inScomoDCInstance);

//Inventory API

/*!
 *******************************************************************************
 * Get DC instance component id.
 *
 * \param	inScomoDCInstance	Handle to the SCOMO DC instance.
 * \param	ioBuffer			Pre-allocated result buffer for the component
 *								id.
 * \param	ioLength			Input: Size of the result buffer.
 *								Output: Length of data in the result buffer.
 *
 * If the supplied buffer is too small then as much data as will fit in the
 * buffer is returned along with the error code VDM_ERR_BUFFER_OVERFLOW.
 *
 * \return	VDM_ERR_OK on success,  or
 *			VDM_ERR_BUFFER_OVERFLOW if the buffer is too small, or
 *			a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DC_getId(VDM_Handle_t inScomoDCInstance, char *ioBuffer,
	IU32 *ioLength);

/*!
 *******************************************************************************
 * Get DC instance component package id.
 *
 * \param	inScomoDCInstance	Handle to the SCOMO DC instance.
 * \param	inBuffer			Pre-allocated result buffer for the package id.
 * \param	ioLength			Input: Size of the result buffer.
 *								Output: Length of data in the result buffer.
 *
 * If the supplied buffer is too small then as much data as will fit in the
 * buffer is returned along with the error code VDM_ERR_BUFFER_OVERFLOW.
 *
 * \return	VDM_ERR_OK on success,  or
 *			VDM_ERR_BUFFER_OVERFLOW if the buffer is too small, or
 *			a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DC_getPkgId(VDM_Handle_t inScomoDCInstance, char *outBuffer,
	IU32 *ioLength);

/*!
 *******************************************************************************
 * Get DC instance component name (Inventory/Deployed/\<X\>/Name).
 *
 * \param	inScomoDCInstance	Handle to the SCOMO DC instance.
 * \param	inBuffer			Pre-allocated result buffer for the component
 *								name.
 * \param	ioLength			Input: Size of the result buffer.
 *								Output: Length of data in the result buffer.
 *
 * If the supplied buffer is too small then as much data as will fit in the
 * buffer is returned along with the error code VDM_ERR_BUFFER_OVERFLOW.
 *
 * \return	VDM_ERR_OK on success,  or
 *			VDM_ERR_BUFFER_OVERFLOW if the buffer is too small, or
 *			a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DC_getName(VDM_Handle_t inScomoDCInstance, char *inBuffer,
	IU32 *ioLength);

/*!
 *******************************************************************************
 * Get DC instance component description (Inventory/Deployed/\<X\>/Description).
 *
 * \param	inScomoDCInstance	Handle to the SCOMO DC instance.
 * \param	inBuffer			Pre-allocated result buffer for the component
 *								description.
 * \param	ioLength			Input: Size of the result buffer.
 *								Output: Length of data in the result buffer.
 *
 * If the supplied buffer is too small then as much data as will fit in the
 * buffer is returned along with the error code VDM_ERR_BUFFER_OVERFLOW.
 *
 * \return	VDM_ERR_OK on success,  or
 *			VDM_ERR_BUFFER_OVERFLOW if the buffer is too small, or
 *			a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DC_getDescription(VDM_Handle_t inScomoDCInstance, char *outBuffer,
	IU32 *ioLength);

/*!
 *******************************************************************************
 * Get DC instance component version (Inventory/Deployed/\<X\>/Version).
 *
 * \param	inScomoDCInstance	Handle to the SCOMO DC instance.
 * \param	inBuffer			Pre-allocated result buffer for the component
 *								version.
 * \param	ioLength			Input: Size of the result buffer.
 *								Output: Length of result data.
 *
 * If the supplied buffer is too small then as much data as will fit in the
 * buffer is returned along with the error code VDM_ERR_BUFFER_OVERFLOW.
 *
 * \return	VDM_ERR_OK on success,  or
 *			VDM_ERR_BUFFER_OVERFLOW if the buffer is too small, or
 *			a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DC_getVersion(VDM_Handle_t inScomoDCInstance, char *inBuffer,
	IU32 *ioLength);

/*!
 *******************************************************************************
 * Set DC instance component version (Inventory/Deployed/\<X\>/Version).
 *
 * \param	inScomoDCInstance	Handle to the SCOMO DC instance.
 * \param	inVersion			The component version.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DC_setVersion(VDM_Handle_t inScomoDCInstance, const char *inVersion);


/*!
 *******************************************************************************
 * Get DC instance component tool version (Inventory/Deployed/\<X\>/ToolVersion).
 *
 * \param	inScomoDCInstance	Handle to the SCOMO DC instance.
 * \param	inBuffer			Pre-allocated result buffer for the component
 *								tool version.
 * \param	ioLength			Input: Size of the result buffer.
 *								Output: Length of result data.
 *
 * If the supplied buffer is too small then as much data as will fit in the
 * buffer is returned along with the error code VDM_ERR_BUFFER_OVERFLOW.
 *
 * \return	VDM_ERR_OK on success,  or
 *			VDM_ERR_BUFFER_OVERFLOW if the buffer is too small, or
 *			a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DC_getToolVersion(VDM_Handle_t inScomoDCInstance, char *inBuffer,
	IU32 *ioLength);

/*!
 *******************************************************************************
 * Set DC instance component tool version (Inventory/Deployed/\<X\>/ToolVersion).
 *
 * \param	inScomoDCInstance	Handle to the SCOMO DC instance.
 * \param	inToolVersion			The component tool version.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DC_setToolVersion(VDM_Handle_t inScomoDCInstance,
		const char *inToolVersion);

/*!
 *******************************************************************************
 * Get DC instance component state (Inventory/Deployed/\<X\>/State).
 *
 * \param	inScomoDCInstance	Handle to the SCOMO DC instance.
 * \param	outState			State of component: active or inactive.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DC_getState(VDM_Handle_t inScomoDCInstance,
	E_VDM_SCOMO_COMPONENT_STATE_t *outState);

/*!
 *******************************************************************************
 * Get a DC component environment type (Inventory/Deployed/\<X\>/EnvType).
 *
 * \param	inScomoDCInstance	Handle to the SCOMO DC instance.
 * \param	inBuffer			Pre-allocated result buffer for the environment
 *								type.
 * \param	ioLength			Input: Size of the result buffer.
 *								Output: Length of data in the result buffer.
 *
 * If the supplied buffer is too small then as much data as will fit in the
 * buffer is returned along with the error code VDM_ERR_BUFFER_OVERFLOW.
 *
 * \return	VDM_ERR_OK on success,  or
 *			VDM_ERR_BUFFER_OVERFLOW if the buffer is too small, or
 *			a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DC_getEnvType(VDM_Handle_t inScomoDCInstance, char *inBuffer,
	IU32 *ioLength);

/*!
 *******************************************************************************
 * Get DC instance deployed status.
 *
 * \param	inScomoDCInstance	Handle to the SCOMO DC instance.
 * \param	outStatus			Deployed status.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DC_getDeployedStatus(VDM_Handle_t inScomoDCInstance,
	E_VDM_SCOMO_DEPLOYED_STATUS_t *outStatus);

/*!
 *******************************************************************************
 * Add a DC.
 *
 * \param	inScomoDCInstance		Handle to the SCOMO DC instance.
 * \param	inCompId                Component id.
 * \param	inCompName              Component name (may be NULL).
 * \param	inPkgId	                Package id. If NULL, set the DC PkgIdRef to
 *									-1.
 * \param	inCompVersion			Component version.
 * \param	inCompDesc				Component description (may be NULL).
 * \param	inCompEnv				Component environment (may be NULL).
 * \param	inIsActive				DC state: TRUE for active, FALSE otherwise.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_MEMORY if no memory to perform action,
 *			VDM_ERR_BAD_INPUT if invalid input, or
 *			VDM_ERR_UNSPECIFIC if operation on inventory failed
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DC_addToInventory(VDM_Handle_t inScomoDCInstance, const char *inCompId,
	const char *inCompName, const char *inPkgId, const char *inCompVersion, const char *inCompDesc,
	const char *inCompEnv, IBOOL inIsActive);

/*!
 *******************************************************************************
 * Add leaf attribute to DC.
 *
 * \param   inScomoDCInstance       Handle to the SCOMO DC instance.
 * \param   inCompId                Component id.
 * \param   inAttribute             Attribute name
 * \param   inAttributeValue        Attribute data
 *
 * \return  VDM_ERR_OK on success,
 *          VDM_ERR_MEMORY if no memory to perform action,
 *          VDM_ERR_BAD_INPUT if invalid input, or
 *          VDM_ERR_UNSPECIFIC if operation on inventory failed
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DC_addAttribute(VDM_Handle_t inScomoDCInstance,
	const char *inCompId,
	const char *inAttribute,
	const char *inAttributeValue);

/*!
 *******************************************************************************
 * Add leaf attribute to DC or replace its value if already exist
 *
 * \param   inScomoDCInstance       Handle to the SCOMO DC instance.
 * \param   inCompId                Component id.
 * \param   inAttribute             Attribute name
 * \param   inAttributeValue        Attribute data
 *
 * \return  VDM_ERR_OK on success,
 *          VDM_ERR_MEMORY if no memory to perform action,
 *          VDM_ERR_BAD_INPUT if invalid input, or
 *          VDM_ERR_UNSPECIFIC if operation on inventory failed
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DC_addOrReplaceAttribute(VDM_Handle_t inScomoDCInstance,
	const char *inCompId,
	const char *inAttribute,
	const char *inAttributeValue);
/*!
 *******************************************************************************
 * Delete a DC.
 *
 * \param	inScomoDCInstance	Handle to the SCOMO DC instance.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DC_deleteFromInventory(VDM_Handle_t inScomoDCInstance);

/*!
 *******************************************************************************
 * Trigger a SCOMO DC report session (generic alert).
 *
 * Called by the client application after a DC activation, deactivation, or
 * installation completed, either successfully or failed, such as a user abort,
 * and so on.
 *
 * The SCOMO DC result must be up to date (see
 * \ref VDM_SCOMO_DC_setDeploymentResult).
 *
 * \since	vDM 4.5
 * \param	inScomoDCInstance	Handle to the SCOMO DC instance.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_MEMORY if no memory to perform action, or
 *			VDM_ERR_MO_STORAGE if persistent storage cannot be read
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DC_triggerReportSession(VDM_Handle_t inScomoDCInstance);

/*!
 *******************************************************************************
 * Set whether, when a new DC is added to the DM Tree, its child nodes should be
 * stored in the DM Tree. By default, the nodes are stored in external
 * inventory.
 *
 * \note	Call \ref VDM_SCOMO_DC_createInstance before calling this function.
 *
 * \param	inScomoDCInstance	Handle to the SCOMO DC instance.
 * \param	inStoreInvInTree	TRUE if DC child node values should be stored
 *								in the DM Tree, FALSE otherwise.
 *
 * \return	VDM_ERR_OK on success, or
 *          VDM_ERR_BAD_INPUT if \ref VDM_SCOMO_DC_createInstance was not yet
 *          called
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DC_setStoreInventoryInTree(VDM_Handle_t inScomoDCInstance, IBOOL inStoreInvInTree);

/*!
 *******************************************************************************
 * Get whether, when a new DC is added to the DM Tree, its child nodes are
 * stored in the DM Tree.
 *
 * \note	Call \ref VDM_SCOMO_DC_createInstance before calling this function.
 *
 * \param	inScomoDCInstance	Handle to the SCOMO DC instance.
 * \param	outStoreInvInTree	TRUE if DC child node values are stored
 *								in the DM Tree, FALSE otherwise.
 *
 * \return	VDM_ERR_OK on success,
 *          VDM_ERR_BAD_INPUT if \ref VDM_SCOMO_DC_createInstance was not yet
 *          called
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DC_getStoreInventoryInTree(VDM_Handle_t inScomoDCInstance, IBOOL *outStoreInvInTree);

/*!
 *******************************************************************************
 * Get DC error code from reg.coonf.
 *
 * \param	inScomoDCInstance	Handle to the SCOMO DC instance.
 * \param	inId			    Component id.
 * \param	outPrevError	    DC error code.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_DC_getErrorCode(VDM_Handle_t inScomoDCInstance, const char *inId, IU32 *outPrevError);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

