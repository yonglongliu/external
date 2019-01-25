/*
 *******************************************************************************
 *
 * vdm_scomo.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_scomo.h
 *
 * \brief	SCOMO Plugin API
 *******************************************************************************
 */
#ifndef _VDM_SCOMO_H_
#define _VDM_SCOMO_H_

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *******************************************************************************
 * Callback invoked before an action is performed on a SCOMO node.
 * Use this to confirm whether the action should proceed.
 *
 * To proceed with the action, return TRUE. If FALSE is returned, the action is
 * aborted, and status code 403 ("Forbidden") is returned as the result code
 * to the server.
 *
 * \param	inDmcContext	DM Client context passed in during creation
 * \param   outMsg          Allocated buffer(256)
 *                          for message to send to the server
 *
 * \return	TRUE to proceed with the action,
 *          FALSE otherwise
 *******************************************************************************
 */
typedef IBOOL (*VDM_SCOMO_IsAllowActionCB)(void *inDmcContext, char *outMsg);

/*!
 *******************************************************************************
 * Callback invoked when delivery package (DP) is deleted.
 *
 * \param	inDmcContext	Context passed.
 * \param	inDPName		Name of deleted delivery package.
 *
 * \return	None
 *******************************************************************************
 */
typedef void (*VDM_SCOMO_deletedDPCB)(
	void *inDmcContext,
	const char *inDPName);

/*!
 * SCOMO callbacks
 */
typedef struct {
	VDM_SCOMO_IsAllowActionCB isAllowReplaceCB;  //!< Allow an Replace on a node to proceed
	VDM_SCOMO_IsAllowActionCB isAllowExecCB;  //!< Allow an Exec on a node to proceed
	VDM_SCOMO_deletedDPCB deletedDPCB;  //!< Invoked when DP deleted- remove DP from DPs array
} VDM_SCOMO_Callbacks_t;

/*!
 *******************************************************************************
 * Callback invoked when there is a new delivery package (DP).
 *
 * \param	inDmcContext	Context passed in during creation.
 * \param	inDPName		Name of new delivery package.
 *
 * \return	None
 *******************************************************************************
 */
typedef void (*VDM_SCOMO_newDPCB)(
	void *inDmcContext,
	const char *inDPName);

/*!
 * Extra parameters to pass when creating a delivery package, if required.
 */
typedef struct {
	IBOOL isStoreInvInTree;     /*!< Whether the inventory is stored in the
	                                 DM Tree */
} VDM_SCOMO_createParams_t;

/*!
 *******************************************************************************
 * Create a SCOMO instance with extended parameters.
 *
 * \param	inScomoRootURI		Path to SCOMO instance root node in the DM tree.
 * \param	inNewDPCb			Callback to invoke when there is a new delivery
 *                              package (DP). See \ref VDM_SCOMO_newDPCB.
 * \param	inDmcContext		Context passed as a parameter of the callback in
 *								\a inNewDPCb.
 * \param	inParams			Extended parameters, if required.
 *
 * \return	VDM_ERR_OK on success, or VDM_ERR_MEMORY if there is no memory to
 *			perform the operation
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_createEx(const char *inScomoRootURI,
	VDM_SCOMO_newDPCB inNewDPCb,
	void *inDmcContext,
	VDM_SCOMO_createParams_t *inParams);

/**
 *******************************************************************************
 * Set SCOMO callbacks.
 *
 * \param	inCallbacks		Callbacks that may be invoked
 *
 * \return	VDM_ERR_OK on success, or VDM_ERR_OUT_OF_SYNC if SCOMO was not
 *			created yet.
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_setCallbacks(VDM_SCOMO_Callbacks_t *inCallbacks);

/*!
 *******************************************************************************
 * \note	This API is deprecated in favor of \ref VDM_SCOMO_createEx.
 *
 * Create a SCOMO instance.
 *
 * \param	inScomoRootURI		Path to SCOMO instance root node in the DM tree.
 * \param	inNewDPCb			Callback to invoke when there is a new delivery
 *                              package (DP). See \ref VDM_SCOMO_newDPCB.
 * \param	inDmcContext		Context passed as a parameter of the callback in
 *								\a inNewDPCb.
 *
 * \return	VDM_ERR_OK on success, or VDM_ERR_MEMORY if there is no memory to
 *			perform the operation
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_create(const char *inScomoRootURI,
	VDM_SCOMO_newDPCB inNewDPCb,
	void *inDmcContext);

/*!
 *******************************************************************************
 * Set whether, when a new delivery package is added to the DM Tree, its child
 * nodes should be added automatically by SCOMO. \ref VDM_SCOMO_create must be
 * called before this function.
 *
 * \param	inAutoAdd	TRUE if child nodes should be added automatically when
 *                      there is a new delivery package, FALSE otherwise.
 *
 * \return	VDM_ERR_OK on success, or
 *          VDM_ERR_OUT_OF_SYNC if \ref VDM_SCOMO_create was not yet called
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_setAutoAddDPChildNodes(IBOOL inAutoAdd);

/*!
 *******************************************************************************
 * Get whether, when a new delivery package is added to the DM Tree, its child
 * nodes should be added automatically by SCOMO. \ref VDM_SCOMO_create must be
 * called before calling this function.
 * Default is false (the server is expected to add the nodes).
 *
 * \param	outAutoAdd	TRUE if child nodes should be added automatically when
 *                      there is a new delivery package, FALSE otherwise.
 *
 * \return	VDM_ERR_OK on success,
 *          VDM_ERR_OUT_OF_SYNC if \ref VDM_SCOMO_create was not yet called
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_getAutoAddDPChildNodes(IBOOL *outAutoAdd);

/*!
 *******************************************************************************
 * Set whether, when a new DC is added to the DM Tree, its child nodes
 * should be stored in the DM Tree. By default, the nodes are stored in an
 * external inventory.
 *
 * \note	Call \ref VDM_SCOMO_create before calling this function.
 *
 * \param	inStoreInvInTree	TRUE if DC child node values should be stored
 *								in the DM Tree, FALSE otherwise.
 *
 * \return	VDM_ERR_OK on success, or
 *          VDM_ERR_OUT_OF_SYNC if \ref VDM_SCOMO_create was not yet called
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_setStoreInventoryInTree(IBOOL inStoreInvInTree);

/*!
 *******************************************************************************
 * Get whether, when a new DC is added to the DM Tree, its child nodes are
 * stored in the DM Tree.
 *
 * \note	Call \ref VDM_SCOMO_create before calling this function.
 *
 * \param	outStoreInvInTree	TRUE if DC child node values are stored
 *								in the DM Tree, FALSE otherwise.
 *
 * \return	VDM_ERR_OK on success,
 *          VDM_ERR_OUT_OF_SYNC if \ref VDM_SCOMO_create was not yet called
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_getStoreInventoryInTree(IBOOL *outStoreInvInTree);
/*!
 *******************************************************************************
 * Destroy the SCOMO instance. Free memory and destroy data members.
 *
 * \note	Destroying SCOMO will destroy all created delivery packages
 *			and deployment components.
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_SCOMO_destroy(void);

/*!
 *******************************************************************************
 * Get a dynamic array (\ref VDM_UTL_DynArray_t) of currently available
 * delivery packages.
 *
 * \return	Dynamic array of DPs on success, or NULL if
 *			\ref VDM_SCOMO_create was not yet called
 *******************************************************************************
 */
extern VDM_UTL_DynArray_t *VDM_SCOMO_getDPs(void);

/*!
 *******************************************************************************
 * Get a dynamic array (\ref VDM_UTL_DynArray_t) of currently available
 * deployment components.
 *
 * \return	Dynamic array of DCs on success, or NULL if
 *          \ref VDM_SCOMO_create was not yet called
 *******************************************************************************
 */
extern VDM_UTL_DynArray_t *VDM_SCOMO_getDCs(void);

/*!
 *******************************************************************************
 * Get which actions relevant to a SCOMO instance were performed last session.
 *
 * \see VDM_querySessionActions
 *
 * \return	A bit flag describing the session actions relevant to SCOMO.
 *******************************************************************************
 */
extern IU32 VDM_SCOMO_querySessionActions(void);

/*!
 *******************************************************************************
 * Get path to SCOMO instance root node in the DM Tree (set in
 * \ref VDM_SCOMO_create).
 *
 * \return	Path to SCOMO instance root node in the DM tree
 *******************************************************************************
 */
extern const char *VDM_SCOMO_getRootURI(void);

/*!
 *******************************************************************************
 * Set alert type for SCOMO generic alerts.
 *
 * Call \ref VDM_SCOMO_create before this calling this function.
 *
 * \param	inAlertType		Alert type
 *
 * \return	VDM_ERR_OK on success, or
 *          VDM_ERR_OUT_OF_SYNC if \ref VDM_SCOMO_create was not yet called
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_setAlertType(const char *inAlertType);

/*!
 *******************************************************************************
 * Get alert type used for SCOMO generic alerts.
 *
 * \return	Alert type
 *******************************************************************************
 */
extern const char *VDM_SCOMO_getAlertType(void);

/*!
 *******************************************************************************
 * Start a client-initiated SCOMO session for a DM Account.
 *
 * \param	inMessage		SCOMO message content; vendor specific data<br>
 *							CURRENTLY NOT SUPPORTED
 * \param	inMessageLen	Size of \a inMessage
 * \param	inClientType	Type of client, an \ref E_VDM_SCOMO_Client_t value
 * \param	inAccount		The DM Account for which to start a session
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_MEMORY if no memory to perform action, or
 *			VDM_ERR_TREE_ACCESS_DENIED if access denied
 *******************************************************************************
 */
extern VDM_Error VDM_SCOMO_triggerSessionForAccount(
	char *inMessage,
	IU32 inMessageLen,
	E_VDM_SCOMO_Client_t inClientType,
	const char *inAccount);

/*!
 *******************************************************************************
 * Check if session initiator is SCOMO.
 *
 * \param	inSessContext	Session Context
 *
 * \return	TRUE if the initiator is SCOMO,
 *			FALSE if the initiator is not SCOMO,
 *******************************************************************************
 */
IBOOL VDM_SCOMO_isSessionInitiator(VDM_SessionContext_t *inSessContext);
/*!
 *******************************************************************************
 * Get all components names under Inventory/Deployed from the tree,
 * separated by "/".
 *
 * \param	inRoot      Root of SCOMO sub tree.
 * \param	outBuffer	A pointer to the components string.
 * \param	ioLength	Length of the supplied buffer.(May be 0)
 *
 * If the supplied buffer is too short then as much data as will fit in the
 * buffer is returned along with the error code \ref VDM_ERR_BUFFER_OVERFLOW.
 *
 * \return	VDM_ERR_OK				- Success.
 *			VDM_ERR_BAD_INPUT		- One of the  parameters is NULL
 *			VDM_ERR_MEMORY			- No memory to perform action.
 *			VDM_ERR_TREE_ACCESS_DENIED	- Access denied.
 *			VDM_ERR_BUFFER_OVERFLOW - Supplied buffer is too short.
 ******************************************************************************
 */

VDM_Error VDM_SCOMO_getAllComponents(
		const char *inRoot,
		char *outBuffer,
		IU32 *ioLength);

/*!
 *******************************************************************************
 * Get all packages under "Download" from the tree, separated by "/".
 *
 * \param	inRoot			Root of SCOMO sub tree.
 * \param	outPkgsBuffer	Result buffer.
 * \param	ioLength		Input:  size of the result buffer.
 *							Output: length of node value in the tree.
 *
 * If the supplied buffer is too short then as much data as will fit in the
 * buffer is returned along with the error code \ref VDM_ERR_BUFFER_OVERFLOW.
 *
 * \return	VDM_ERR_OK			 - Success.
 *			VDM_ERR_MEMORY		 - No memory to perform action.
 *			VDM_ERR_TREE_ACCESS_DENIED - Access denied.
 *			VDM_ERR_BUFFER_OVERFLOW - Supplied buffer is too short.
 ******************************************************************************
 */
VDM_Error VDM_SCOMO_getDownloadPackages(
	const char *inRoot,
	char *outPkgsBuffer,
	IU32 *ioLength);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

