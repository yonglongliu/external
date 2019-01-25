/*
 *******************************************************************************
 *
 * vdm_api.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_api.h
 *
 * \brief	OMA DM Protocol Engine SDK
 *
 * Functions to start and stop OMA DM Protocol Engine, as well as manage sessions,
 * events, and debugging.
 *******************************************************************************
 */
#ifndef _VDM_API_H_
#define _VDM_API_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <vdm_error.h>
#include <vdm_types.h>
#include <vdm_http_types.h>

//Init/term

/*!
 *******************************************************************************
 * Create and initialize the OMA DM Protocol Engine Engine.
 *
 * Once the OMA DM Protocol Engine Engine has been created and initialized it may be
 * configured using \ref vdm_config.h APIs.
 *
 * \param	inAsyncHandle	Handle to platform-specific asynchronous object,
 *							such as a handle to a thread. This may be NULL, and
 *							will be NULL for synchronous operation.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_create(void *inAsyncHandle);

/*!
 *******************************************************************************
 * Start the OMA DM Protocol Engine Engine.
 *
 * Call this function before calling any other OMA DM Protocol Engine function. If the
 * function returns an error, don't call any other OMA DM Protocol Engine function
 * except for \ref VDM_destroy.
 *
 * \note	This function requires that a valid DM Tree is available. for
 *			information on the DM Tree, see the vDM Integrator's Guide.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_start(void);

/*!
 *******************************************************************************
 * Stop the OMA DM Protocol Engine Engine.
 *
 * \return	None
 *******************************************************************************
 */
extern VDM_Error VDM_stop(void);

/*!
 *******************************************************************************
 * Destroy the OMA DM Protocol Engine Engine.
 *
 * This function releases all allocated resources.
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_destroy(void);

/*!
 *******************************************************************************
 * Run OMA DM Protocol Engine.
 *
 * Call this from from the DM client application event loop.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_run(void);

//Session

/*!
 *******************************************************************************
 * Set session-enable mode.
 *
 * Session-enable mode determines which sessions may be started by the Engine.
 * For example, you may allow only server-initiated sessions.
 *
 * The initial value is E_VDM_SessionEnable_allowAll.
 *
 * \see		VDM_getSessionEnableMode E_VDM_SessionEnable_t
 *
 * \param	inMode	An \ref E_VDM_SessionEnable_t value.
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_INVALID_CALL if OMA DM Protocol Engine is not initialized yet
 *******************************************************************************
 */
extern VDM_Error VDM_setSessionEnableMode(E_VDM_SessionEnable_t inMode);

/*!
 *******************************************************************************
 * Restore previous session-enable mode.
 *
 * Session-enable mode determines which sessions may be started by the Engine.
 * For example, you may allow only server-initiated sessions.
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_restoreSessionEnableMode(void);

/*!
 *******************************************************************************
 * Get session-enable mode.
 *
 * Session-enable mode determines which sessions may be started by the Engine.
 *
 * \see		E_VDM_SessionEnable_t VDM_getSessionEnableMode
 *
 * \return	Session-Enable mode, an \ref E_VDM_SessionEnable_t value
 *******************************************************************************
 */
extern E_VDM_SessionEnable_t VDM_getSessionEnableMode(void);

/*!
 *******************************************************************************
 * Get the current DM Account. The DM Account information was previously
 * received from a WAP bootstrap or a notification messages.
 *
 * If NULL is returned, the default DM Account in the DM Tree is used.
 *
 * \return	URI of the current DM Account node in the DM Tree or NULL.
 *******************************************************************************
 */
extern const char *VDM_getCurrentAccount(void);

/*!
 *******************************************************************************
 * Get the default DM Account. If not configured, the default DM Account is the
 * first account in the tree.
 *
 * \param	outDmAccPath		Pre-allocated buffer to store the path to the
 *								default DM Account in the DM Tree; if NULL,
 *								there is no defailt DM Account
 * \param	inMaxBufLen			Size of \a outDmAccPath
 *
 * \return	VDM_ERR_OK on success,
 *          VDM_ERR_BUFFER_OVERFLOW if \a inMaxBufLen is too small,
 *			or VDM_ERR_NODE_MISSING if there is no default DM Account
 *******************************************************************************
 */
extern VDM_Error VDM_getDefaultAccount(char *outDmAccPath, IU32 inMaxBufLen);

/*!
 *******************************************************************************
 * Trigger a Download session.
 *
 * To receive notification when the Download session state changes, register
 * as an observer using \ref VDM_registerSessionStateObserver. A session state
 * observer must implement the \ref VDM_SessionStateNotifyCB callback.
 *
 * To unregister as a session state observer, call \ref
 * VDM_unregisterSessionStateObserver.
 *
 * \param	inNodeURI			The URI of a node in DM Tree containing a URL
 *								from which to download. For example, the path
 *								to the PkgURL node.
 * \param	inDLPromptFunc		Callback invoked after the download
 *								descriptor has been downloaded and before the
 *								object is downloaded. The callback promts
 *								the user as to whether to proceed with
 *								the download.
 * \param	inDLDataHandlerFunc	Callback invoked after	each chunk of
 *								data is downloaded to be stored in a
 *								non-volatile storage.
 * \param	inGetFilePathFunc	Callback invoked to get the path used to store
 *								the file, matching the DD file name.
 * \param	inSessionContext	Context sent as a parameter of the
 *								session-state notification callback.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_triggerDLSession(
	const char *inNodeURI,
	VDM_DownloadPromptCB inDLPromptFunc,
	VDM_OnDdReceivedCB inOnDdReceivedFunc,
	VDM_HandleDLContentCB inDLDataHandlerFunc,
	VDM_GetPkgFilePathCB inGetFilePathFunc,
	VDM_SessionContext_t *inSessionContext);

/*!
 *******************************************************************************
 * Remove all NIAs saved in persistent storage.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			or VDM_ERR_MO_STORAGE if error accessing persistent storage
 *******************************************************************************
 */
extern VDM_Error VDM_removeAllNiasFromPs(void);

/*!
 *******************************************************************************
 * Trigger notification-initiated DM sessions previously stored in persistent
 * storage.
 *
 * The buffer of the NIA is read from persistent storage. Sessions are triggered
 * in the order in which they were saved. A session is saved in persistent
 * storage when it is triggered by \ref VDM_triggerNIADMSession and wasn't
 * already handled for some reason, such as a device crash.
 *
 * \param	inInitiatorId			A unique string that identifies the session
 *									initiator.
 * \param	inHandlerFunc			Callback invoked to parse the message.
 * \param	inHandlerFuncContext	Context passed to \a inHandlerFunc.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			or VDM_ERR_MO_STORAGE if error accessing persistent storage
 *******************************************************************************
 */
extern VDM_Error VDM_triggerPsNIADMSession(
	const char *inInitiatorId,
	VDM_NIAHandlerCB inHandlerFunc,
	void *inHandlerFuncContext);

/*!
 *******************************************************************************
 * Trigger the front notification-initiated DM session previously stored in
 * persistent storage.
 *
 * \param	inHandlerFunc		Callback invoked to parse the message.
 * \param	inSessionContext	Session context added to the trigger.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			or VDM_ERR_MO_STORAGE if error accessing persistent storage
 *******************************************************************************
 */
extern VDM_Error VDM_triggerNIAFromPS(
	VDM_NIAHandlerCB inHandlerFunc,
	VDM_SessionContext_t *inSessionContext);

/*!
 *******************************************************************************
 * Add NIA to persistent storage, without triggering DM session.
 *
 * \param	inMessage			Vendor-specific message content.
 * \param	inMessageLen		Size of \a inMessage.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_NIA_PS_addNiaToPS(IU8 *inMessage, IU32 inMessageLen);

/*!
 *******************************************************************************
 * Trigger a DM session.
 *
 * To receive notification when a DM session state changes, register as an
 * observer using \ref VDM_registerSessionStateObserver. A session state
 * observer must implement the \ref VDM_SessionStateNotifyCB callback.
 *
 * To unregister as a session state observer, call \ref
 * VDM_unregisterSessionStateObserver.
 *
 * \param	inAccount			The URI of the DM Account node in the DM Tree
 *								(NULL for default DM account).
 * \param	inGenericAlertType	Generic alert type as defined by OMA.
 *								For example:
 *								org.openmobilealliance.dm.firmwareupdate.devicerequest
 *								is the generic alert type used for device
 *								initiated firmware update.
 * \param	inMessage			Vendor-specific message content. It will be sent only
 * 								if inGenericAlertType is not NULL.
 * 								The format in the alert will be determined according
 * 								to the value of the data (text\plain or b64)
 * \param	inMessageLen		Size of \a inMessage.
 * \param	inSessionContext	Context that will be sent as a parameter of the
 *								session-state notification callback.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_triggerDMSession(
	const char *inAccount,
	const char *inGenericAlertType,
	IU8 *inMessage,
	IU32 inMessageLen,
	VDM_SessionContext_t *inSessionContext);

/*!
 *******************************************************************************
 * Trigger an Abort(1223) Report session (DM Session).
 *
 * To receive notification when a DM session state changes, register as an
 * observer using \ref VDM_registerSessionStateObserver. A session state
 * observer must implement the \ref VDM_SessionStateNotifyCB callback.
 *
 * For 1223 alert the method needs to be called as follows:
 *		VDM_triggerAbortReportSession(NULL, "alert-1223", context);

 * To unregister as a session state observer, call \ref
 * VDM_unregisterSessionStateObserver.
 *
 * \param	inAccount				The URI of the DM Account node in the DM
 *									Tree (NULL for default DM account).
 * \param	inAbortSessionAlertType	Vendor specific string (can be NULL).
 * \param	inSessionContext		Context that will be sent as a parameter of
 *									the session-state notification callback.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_triggerAbortReportSession(
	const char *inAccount,
	const char *inAbortSessionAlertType,
	VDM_SessionContext_t *inSessionContext);
/*!
 *******************************************************************************
 * Trigger a Report session (DM Session).
 *
 * To receive notification when a Report session state changes, register as an
 * observer using \ref VDM_registerSessionStateObserver. A session state
 * observer must implement the \ref VDM_SessionStateNotifyCB callback.
 *
 * To unregister as a session state observer, call \ref
 * VDM_unregisterSessionStateObserver.
 *
 * \param	inNodeURI			The URI of a node in the DM Tree.
 * \param	inReasonCode		Result code. Used when the alert is an
 *								asynchronous response to an Exec command.
 * \param	inAccount			The URI of the DM Account node in the DM Tree.
 *								(NULL for default DM account).
 * \param	inGenericAlertType	Generic alert type as defined by OMA.
 *								For example:
 *								org.openmobilealliance.dm.firmwareupdate.download
 *								is the generic alert type used in response
 *								to the completion of a Download operation.
 * \param	inCorrelator		Correlator previously sent by server. Used when
 *								the alert is an asynchronous response to an
 *								Exec command.
 * \param	inSessionContext	Context that will be sent as a parameter of the
 *								session-state notification callback.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_triggerReportSession(
	const char *inNodeURI,
	IU32 inReasonCode,
	const char * inAccount,
	const char *inGenericAlertType,
	const char *inCorrelator,
	VDM_SessionContext_t *inSessionContext);

/*!
 *******************************************************************************
 * Trigger a Report session (DM Session). Accepts an extra parameter
 * \ref inTextResult
 *
 * To receive notification when a Report session state changes, register as an
 * observer using \ref VDM_registerSessionStateObserver. A session state
 * observer must implement the \ref VDM_SessionStateNotifyCB callback.
 *
 * To unregister as a session state observer, call \ref
 * VDM_unregisterSessionStateObserver.
 *
 * \param	inNodeURI			The URI of a node in the DM Tree.
 * \param	inReasonCode		Result code. Used when the alert is an
 *								asynchronous response to an Exec command.
 * \param	inAccount			The URI of the DM Account node in the DM Tree.
 *								(NULL for default DM account).
 * \param	inGenericAlertType	Generic alert type as defined by OMA.
 *								For example:
 *								org.openmobilealliance.dm.firmwareupdate.download
 *								is the generic alert type used in response
 *								to the completion of a Download operation.
 * \param	inTextResult		A textual result to report
 * \param	inCorrelator		Correlator previously sent by server. Used when
 *								the alert is an asynchronous response to an
 *								Exec command.
 * \param	inSessionContext	Context that will be sent as a parameter of the
 *								session-state notification callback.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_triggerReportSessionTxtRes(
	const char *inNodeURI,
	IU32 inReasonCode,
	const char *inAccount,
	const char *inGenericAlertType,
	const char *inTextResult,
	const char *inCorrelator,
	VDM_SessionContext_t *inSessionContext);

/*!
 *******************************************************************************
 * Trigger a Multiple Alerts session (DM Session).
 *
 * The content of the message sent to the server is constructed externally
 * to OMA DM Protocol Engine in the \a inCreateGenAlertsFunc callback. The content
 * is a list of one or more generic alerts, each of which may contain multiple
 * items. The list of generic alerts is allocated externally, but freed by
 * OMA DM Protocol Engine.
 *
 * To receive notification when a Multiple Alerts session state changes,
 * register as an observer using \ref VDM_registerSessionStateObserver. A
 * session state observer must implement the \ref VDM_SessionStateNotifyCB
 * callback.
 *
 * To unregister as a session state observer, call \ref
 * VDM_unregisterSessionStateObserver.
 *
 * \param	inAccount				URI of the DM Account node in the DM Tree.
 * \param	inCreateGenAlertsFunc	Callback that will return
 *									a linked list of generic alerts.
 * \param	inSessionContext		Context that will be sent as a parameter of
 *									session-state the notification callback.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_triggerMultipleGenericAlertsSession(
	const char *inAccount,
	VDM_CreateGenericAlertsCB inCreateGenAlertsFunc,
	VDM_SessionContext_t *inSessionContext);

/*!
 *******************************************************************************
 * Trigger a notification-initiated DM session.
 *
 * The DM client should call this function after receiving a "General
 * Notification Initiated Session Alert" (NIA).
 *
 * To receive notification when a notification-initiated (DM) session state
 * changes, register as an observer using \ref VDM_registerSessionStateObserver.
 * A session state observer must implement the \ref VDM_SessionStateNotifyCB
 * callback.
 *
 * To unregister as a session state observer, call \ref
 * VDM_unregisterSessionStateObserver.
 *
 * \param	inMessage			Notification message content.
 * \param	inMessageLen		Size of \a inMessage.
 * \param	inHandlerFunc		Callback invoked after \a inMessage is
 *								parsed and before a connection is opened.
 * \param	inSessionContext	Context that will be sent as a parameter of the
 *								session-state notification callback.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_triggerNIADMSession(
	IU8 *inMessage,
	IU32 inMessageLen,
	VDM_NIAHandlerCB inHandlerFunc,
	VDM_SessionContext_t *inSessionContext);

/*!
 *******************************************************************************
 * Count the number of enqueued notification-initiated DM session.
 *
 * \return	The number of enqueued NIAs.
 *******************************************************************************
 */
extern IU32 VDM_NIADMSessionCount(void);

/*!
 *******************************************************************************
 * Check validity of NIA without triggering it.
 *
 * \param	inMessage			Notification message content (without WSP).
 * \param	inMessageLen		Size of \a inMessage.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_checkNIA(IU8 *inMessage, IU32 inMessageLen);

/*!
 *******************************************************************************
 * Get vendor specific info field from NIA.
 *
 * \param	inMessage			Notification message content (without WSP).
 * \param	inMessageLen		Size of \a inMessage.
 * \param	outVendorSpec		Vendor specific info field.
 * \param	ioVendorSpecSize	Vendor specific info field size.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */

extern VDM_Error VDM_getVendorSpecInfo(IU8 *inMessage, IU32 inMessageLen,
	char *outVendorSpec, IU16 *ioVendorSpecSize);

/*!
 *******************************************************************************
 * Trigger a Bootstrap session.
 *
 * To receive notification when a Bootstrap session state changes, register as
 * an observer using \ref VDM_registerSessionStateObserver. A session state
 * observer must implement the \ref VDM_SessionStateNotifyCB callback.
 *
 * To unregister as a session state observer, call \ref
 * VDM_unregisterSessionStateObserver.
 *
 * \param	inReserved			For future use.
 * \param	inProfile			A provisioning profile, an
 *								\ref E_VDM_Prov_Profile_t value. WAP (OMA-CP)
 *								or plain (OMA-DM).
 * \param	inSecurityMechanism	The security mechanism, an \ref
 *								E_VDM_Prov_Security_t value.
 * \param	inMAC				Message Authentication Code, in hex format.
 * \param	inBuffer			The binary bootstrap data, pre-configured or
 *								received from server.
 * \param	inBufferLen			Size of \a inBuffer.
 * \param	inCallbacks			Callbacks to notify on bootstrap events.
 *								See \ref VDM_BootCallbacks_t.
 * \param	inCallbacksContext	Context that will be sent as parameter to the
 *								callbacks in \a inCallbacks.
 * \param	inSessionContext	Context that will be sent as a parameter of the
 *								session-state notification callback.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_triggerBootstrapSession(
	const char *inReserved,
	E_VDM_Prov_Profile_t inProfile,
	E_VDM_Prov_Security_t inSecurityMechanism,
	const char *inMAC,
	IU8 *inBuffer,
	IU32 inBufferLen,
	VDM_BootCallbacks_t *inCallbacks,
	void *inCallbacksContext,
	VDM_SessionContext_t *inSessionContext);

/*!
 *******************************************************************************
 * Register as a session state observer.
 *
 * Adds a callback (observer) to the list of session state observers. A session
 * state observer is notified whenever a session state changes using the
 * callback \ref VDM_SessionStateNotifyCB. Each callback is notified once on
 * each change in the session state. If the callback has already been
 * registered, a reference counter to it will be incremented.
 *
 * \see		VDM_unregisterSessionStateObserver
 *
 * \param	inHandlerFunc	Pointer to the observer's callback.
 *
 * \return	VDM_ERR_OK on success, or VDM_ERR_MEMORY if there is no memory
 *			to perform the action.
 *******************************************************************************
 */
extern VDM_Error VDM_registerSessionStateObserver(
	VDM_SessionStateNotifyCB inHandlerFunc);

/*!
 *******************************************************************************
 * Unregister as a session state observer.
 *
 * The callback is removed from the list of session state observers.
 * If the callback has been registered more than once, it is not removed.
 * Instead, its reference counter is decremented.
 *
 * \see		VDM_registerSessionStateObserver
 *
 * \param	inHandlerFunc	Pointer to the observer's callback to be
 *							removed.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_unregisterSessionStateObserver(
	VDM_SessionStateNotifyCB inHandlerFunc);

/*!
 *******************************************************************************
 * Remove all triggers from the queue.
 *
 * \return	None
 *******************************************************************************
 */

extern void VDM_removeAllTriggers(void);

/*!
 *******************************************************************************
 * Register to be notified of OMA-CP info as it being parsed.
 *
 * \param	inObserverFunc		Pointer to the function that will be invoked for
 *								notification while parsing the CP info.
 *
 * \return None
 *******************************************************************************
 */
extern void VDM_registerCPObserver(VDM_CPNotifyCB inObserverFunc);

/*!
 *******************************************************************************
 * Register to be notified when a connection is broken during a Download
 * session.
 *
 * \param	inFunc		Callback to invoke on a broken connection.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_registerDLRetryNotify(VDM_DownloadRetryNotifyCB_t inFunc);

/*!
 *******************************************************************************
 * Register to be notified when a connection has broken, and engine is about to
 * try to reconnect.
 *
 * \param	inConnRetryNotifyCB		Callback to invoke.
 * \param	inContext				Context that will be sent as a
 *									parameter of \a inConnRetryNotifyCB.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_registerConnectionRetryNotify(
	VDM_connectionRetryNotifyCB_t inConnRetryNotifyCB, void *inContext);

/*!
 *******************************************************************************
 * Register to be notified when a download is resumed. This is done to compare
 * the DD url and DL resume url.
 *
 * \param	inFunc		Callback to invoke when download is resumed.
 * \param	inContext	Context that will be sent as a parameter of the
 *						event callback \a inFunc.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_registerDLResumeCmpUrlCB(VDM_DLResumeCmpUrlCB_t inFunc,
	void *inContext);
/*!
 *******************************************************************************
 * Cancel the active session.
 *
 * \deprecated	Use \ref VDM_cancelActiveSession
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_cancelSession(void);

/*!
 *******************************************************************************
 * Cancel active session or sessions.
 *
 * \deprecated	Use \ref VDM_VDM_cancelActiveSessionEx
 *
 * \param	inActiveSessType	E_VDM_ACTIVE_SESS_All to cancel both active DM
 *								and Download sessions, or E_VDM_ACTIVE_SESS_Dl
 *								to cancel only the active Download session
 *
 * \return	VDM_ERR_OK on success or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_cancelActiveSession(E_VDM_ACTIVE_SESS_t inActiveSessType);

/*!
 *******************************************************************************
 * Cancel active session or sessions according to sessionKey.
 *
 * \param	inActiveSessType	E_VDM_ACTIVE_SESS_All to cancel both active DM
 *								and Download sessions, or E_VDM_ACTIVE_SESS_Dl
 *								to cancel only the active Download session
 *
 * \param	inSessionKey		dl session to cancel
 *
 * \return	VDM_ERR_OK on success or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_cancelActiveSessionEx(E_VDM_ACTIVE_SESS_t inActiveSessType, char *inSessionKey);

/*!
 *******************************************************************************
 * Cancel all active sessions and clear all inactive sessions.
 *
 * An inactive session is a triggered session that has not yet started.
 * A session state notification is invoked for each session.
 *
 * \note This feature is not yet supported.
 *
 * \return	VDM_ERR_NOT_IMPLEMENTED
 *******************************************************************************
 */
extern VDM_Error VDM_clearAllSessions(void);

/*!
 *******************************************************************************
 * Get whether there are active sessions, if the queue is empty, and if the
 * busy reference counter is 0.
 *
 * \see		VDM_incBusyRc VDM_decBusyRc
 *
 * \return	TRUE if there are no active sessions, the busy reference counter is
 *			0, and the queue is empty, FALSE otherwise
 *******************************************************************************
 */
extern IBOOL VDM_isIdle(void);

/*!
 *******************************************************************************
 * Increment the busy reference counter.
 *
 * The busy reference counter is useful when you want OMA DM Protocol Engine not to
 * sleep or exit until a particular action is done. This is useful when, for
 * example, handing an Exec node in the DM Tree.
 *
 * \see		VDM_decBusyRc
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_incBusyRc(void);

/*!
 *******************************************************************************
 * Decrement the busy reference counter.
 *
 * The busy reference counter is useful when you want OMA DM Protocol Engine not to
 * sleep or exit until a particular action is done. This is useful when, for
 * example, handing an Exec node in the DM Tree.
 *
 * \see		VDM_incBusyRc
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_decBusyRc(void);

/*!
 *******************************************************************************
 * Notify that server notification has been handled. Called by the application
 * after the engine invokes \ref VDM_NIAHandlerCB.
 *
 * \see VDM_triggerNIADMSession
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_notifyNIASessionProceed(void);

/*!
 *******************************************************************************
 * Notify that the user confirmed a download. Called by the application after
 * the Engine invokes \ref VDM_DownloadPromptCB.
 *
 * \see VDM_triggerDLSession
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_notifyDLSessionProceed(void);

extern VDM_Error VDM_notifyDLSessionProceedEx(char *inSessionKey);

/*!
 *******************************************************************************
 * Get OMA DM Protocol Engine version.
 *
 * \return	OMA DM Protocol Engine version string
 *******************************************************************************
 */

extern const char *VDM_getVersion(void);

/*!
 *******************************************************************************
 * Get OMA DM Protocol Engine chunk size.
 *
 * \return	OMA DM Protocol Engine chunk size.
 *******************************************************************************
 */
extern IU32 VDM_getChunkSize(void);

/*!
 *******************************************************************************
 * Trigger a postponed event.
 *
 * \param	inInterval	How much time should elapse before calling \a
 *						inEventCB, in seconds.
 * \param	inEventCB	Event callback.
 * \param	inContext	Context that will be sent as a parameter of
 *						\a inEventCB.
 *
 * \return	A handle to the postponed event
 *******************************************************************************
 */
extern VDM_Handle_t VDM_triggerPostponedEvent(
	IU32 inInterval,
	VDM_postponedEventCB inEventCB,
	VDM_Handle_t inContext);

/*!
 *******************************************************************************
 * Cancel a postponed event.
 *
 * \param	ioEvent		The event handle. The handle is de-allocated
 *						and set to NULL.
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_cancelPostponedEvent(VDM_Handle_t *ioEvent);

/*!
 *******************************************************************************
 * Get the next postponed event trigger time.
 *
 * \return	Trigger time in seconds, or MAX_UINT if there is an error
 *			or there is no postponed event.
 *******************************************************************************
 */
extern TIME_T VDM_getNextPostponedEventTime(void);

/*!
 *******************************************************************************
 * Notify that the user has entered a PIN code. Called by the application UI.
 * If \a inUserPin is NULL, this is the same as if \a inIsAccepted is FALSE.
 *
 * \param	inUserPin		PIN code.
 * \param	inIsAccepted	TRUE if PIN code is valid, FALSE otherwise.
 *
 * \return	VDM_ERR_OK, or VDM_ERR_BOOT_PIN if PIN is unobtainable
 *******************************************************************************
 */
extern VDM_Error VDM_notifyUserPinSet(
	const char *inUserPin,
	IBOOL inIsAccepted);

/*!
 *******************************************************************************
 * Add a session action for a component.
 *
 * \param	inKey			A key identifying a specific component's instance.
 *							The key could be a pointer to a component instance,
 *							for example.
 * \param	inBitFlags		A bit flag describing the action to be added. Each
 *							component defines its own sets of bit-flags for the
 *							operations it registers on.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_addSessionAction(
	VDM_Handle_t inKey,
	IU32 inBitFlags);

/*!
 *******************************************************************************
 * Get a component's actions performed during the last session.
 *
 * \param	inKey	A key identifying a specific component's instance.
 *					The key could be a pointer to the instance, for example.
 *
 * \return	A bit flag describing the session actions matching \a inKey.
 *			Each component defines its own bitflags.
 *******************************************************************************
 */
extern IU32 VDM_querySessionActions(VDM_Handle_t inKey);

#if 1
/*!
 *******************************************************************************
 * Lock vDM framework mutex.
 *
 * \return	TRUE if the mutex was successfully locked, FALSE otherwise
 *******************************************************************************
 */
IBOOL VDM_lockMutex(void);

/*!
 *******************************************************************************
 * Unlock vDM framework mutex.
 *
 * \return	TRUE if the mutex was successfully unlocked, FALSE otherwise - such
 *			as when attempting to release an unlocked mutex
 *******************************************************************************
 */
IBOOL VDM_releaseMutex(void);

#else
/// @cond EXCLUDE

 #define DBG_MUTEX
IBOOL VDM_lockMutexDbg(const char *inFunc, IS32 inLine);
IBOOL VDM_releaseMutexDbg(const char *inFunc, IS32 inLine);
 #define VDM_lockMutex()    VDM_lockMutexDbg(__FUNCTION__, __LINE__)
 #define VDM_releaseMutex() VDM_releaseMutexDbg(__FUNCTION__, __LINE__)
/// @endcond
#endif

/*!
 *******************************************************************************
 * Get the Engine state.
 *
 * \return	The Engine state, an \ref E_VDM_EngineState_t value
 *******************************************************************************
 */
E_VDM_EngineState_t VDM_getEngineState(void);

/*!
 *******************************************************************************
 * Pause the current session.
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_pause(void);

/*!
 *******************************************************************************
 * Resume a paused session.
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_resume(void);

/*!
 *******************************************************************************
 * Register to handle encryption events. Currently, encryption events refer to
 * encrypting or decrypting the DM Tree.
 *
 * \param	inCryptCBs	Callbacks invoked to or encrypt or decrypt.
 * \param	inContext	Context that will be passed as a parameter of the
 *						callbacks in \a inCryptCBs.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_registerCryptCallbacks(VDM_Crypt_Callbacks_t *inCryptCBs,
	void *inContext);

/*!
 *******************************************************************************
 * Register to be notified before an HTTP send. This is done to control the
 * HTTP headers.
 *
 * \see		VDM_unregisterHttpHeadersObserver
 *
 * \param	inNotifyBeforeSendCB	Callback invoked before an HTTP send.
 * \param	inContext				Context that will be passed as a parameter
 *									of the callback in \a inNotifyBeforeSendCB.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_registerHttpHeadersObserver(
	VDM_notifyBeforeSendCB_t inNotifyBeforeSendCB, void *inContext);

/*!
 *******************************************************************************
 * Unregister to be notified before an HTTP send.
 *
 * The callback is removed from the list of observers for this event.
 *
 * \see		VDM_registerHttpHeadersObserver
 *
 * \param	inNotifyBeforeSendCB	Callback to be removed.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_unregisterHttpHeadersObserver(
	VDM_notifyBeforeSendCB_t inNotifyBeforeSendCB);

/*!
 *******************************************************************************
 * Register to be notified of incoming HTTP headers
 *
 * \see		VDM_unregisterHttpResponseObserver
 *
 * \param	inCB	Callback invoked for incoming HTTP headers
 * \param	inContext				Context that will be passed as a parameter
 *									of the callback in \a inCB.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
VDM_Error VDM_registerHttpResponseObserver(VDM_notifyHttpResponseCB_t inCB,
	void *inContext);

/*!
 *******************************************************************************
 * Unregister to be notified of incoming HTTP headers
 *
 * The callback is removed from the list of observers for this event.
 *
 * \see		VDM_registerHttpHeadersObserver
 *
 * \param	inCB	Callback to be removed.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
VDM_Error VDM_unregisterHttpResponseObserver(VDM_notifyHttpResponseCB_t inCB);

/*!
 *******************************************************************************
 * Register to be notified before an HTTP connection is opened. This is done to
 * control the URL used in opening the connection.
 *
 * \see		VDM_unregisterConnUrlObserver
 *
 * \param	inNotifyBeforeOpenCB	Callback invoked before an HTTP connection
 *                                  is opend.
 * \param	inContext				Context that will be passed as a parameter
 *									of the callback in \a inNotifyBeforeOpenCB.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_registerConnUrlObserver(
	VDM_notifyBeforeOpenCB_t inNotifyBeforeOpenCB, void *inContext);

/*!
 *******************************************************************************
 * Unregister to be notified before an HTTP connection is opened.
 * The callback (and context) for this event are replaced with a NULL value.
 *
 * \see		VDM_registerConnUrlObserver
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_unregisterConnUrlObserver(void);

/// @cond EXCLUDE

//--------------------------
// !!!		DEBUG		!!!
//--------------------------

/*!
 *******************************************************************************
 * Dump internal data of OMA DM Protocol Engine Core (trigger queue, threshold, etc).
 *
 * For debug purposes only.
 *
 * \return None
 *******************************************************************************
 */
extern void VDM_DbgDump(void);

/*!
 *******************************************************************************
 * Define specific settings for testing.
 * For debug purposes only.
 * Should be called on startup.
 *
 * This function is only required on debug builds which have enabled the
 * internal OMA DM Protocol Engine memory debug features.
 *
 * \param	inMemFailureData:
 *				Pointer to a string containing the memory debug requirements
 *				specified via a command-line or other suitable method. The
 *				current configuration for this string is "single,all,heap",
 *				where:
 *				-	\c single -	Gives a specific allocation number to fail.
 *									(The first call would be number 1, the
 *									second call would be 2, etc).
 *				-	\c all		-	Specifies an allocation number which will
 *									fail, and all subsequent calls will also
 *									fail.
 *				-	\c heap		-	Creates an artificial limit on the memory
 *									which can be allocated. A running total of
 *									the amount of memory allocated is kept, and
 *									any allocation which would cause the total
 *									to exceed this value will fail. Any
 *									calls to free memory will reduce this
 *									running total, so subsequent calls to
 *									allocate memory 'may' succeed.
 *				A value of 0 for any of these items disables that item.
 *
 * \return	TRUE if \a inMemFailureData was valid, FALSE otherwise
 *******************************************************************************
 */
IBOOL VDM_debugMemory(char *inMemFailureData);

/// @endcond

#ifdef __cplusplus
} /* extern "C" */
#endif

//end of file

#endif

