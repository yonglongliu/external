/*
 *******************************************************************************
 *
 * vdm_types.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_types.h
 *
 * \brief	OMA DM Protocol Engine Types
 *******************************************************************************
 */
#ifndef _VDM_TYPES_H_
#define _VDM_TYPES_H_           //!< Internal

#ifdef __cplusplus
extern "C" {
#endif

#include "vdm_dd_fields.h"

/*!
 * The maximum length of a PIN.
 */
#define VDM_PIN_MAX_LEN             20

/*!
 * The maximum length of the Network Shared Secret.
 */
#define VDM_NSS_MAX_LEN             16

/*!
 * The maximum length of DP name.
 */
#define MAX_DP_NAME_SIZE            256

/*!
 * The maximum length of DevId.
 */
#define MAX_DEV_ID_SIZE             128

/*!
 * Dummy session key for dl session
 */
#define DUMMY_SESSION_KEY               "dummy_session_key"
#define FUMO_SESSION_KEY                "FUMO_SESSION_KEY"
#define LAWMO_SESSION_KEY               "LAWMO_SESSION_KEY"
#define LOCATE_SESSION_KEY              "LOCATE_SESSION_KEY"
#define DESCMO_SESSION_KEY              "DESCMO_SESSION_KEY"
#define SCOMO_EXTERNAL_DL_SESSION_KEY   "RB_DP"
#define USB_SESSION_KEY                 "USB_DP"

/*!
 * Session Enable Modes.
 */
typedef enum {
	E_VDM_SessionEnable_allowAll,                   //!< Allow all sessions
	E_VDM_SessionEnable_allowClientInitiatedOnly,   /*!< Allow only client
	                                                     initiated sessions */
	E_VDM_SessionEnable_allowNone                   /*!< Do not allow any
	                                                     session */
} E_VDM_SessionEnable_t;

/*!
 * User Interface Mode.
 */
typedef enum {
	E_VDM_NIA_UIMode_NotSpecified   = 0x00, //!< User interaction not specified
	E_VDM_NIA_UIMode_Background     = 0x01, //!< Perform session in background
	E_VDM_NIA_UIMode_Informative    = 0x02, //!< Announce beginning of session
	E_VDM_NIA_UIMode_UI             = 0x03  //!< Prompt before starting session
} E_VDM_NIA_UIMode_t;

/*!
 * Provisioning profiles.
 */
typedef enum {
	E_VDM_Prov_Profile_PLAIN,   //!< Plain profile; OMA-DM format message
	E_VDM_Prov_Profile_WAP      //!< WAP profile; OMA-CP format message
} E_VDM_Prov_Profile_t;

/*!
 * Bootstrap security.
 */
typedef enum {
	/*! No security is used */
	E_VDM_Prov_Security_NONE        = 0,

	/*! Shared secret - based on a network specific shared secret */
	E_VDM_Prov_Security_NETWPIN     = 1,

	/*! Shared secret - based on a user PIN */
	E_VDM_Prov_Security_USERPIN     = 2,

	/*! Shared secret - network specific shared secret appended with user PIN */
	E_VDM_Prov_Security_USERNETWPIN = 3,

	/*! Out-of-band delivery of MAC authentication information - PIN includes
	 *  MAC */
	E_VDM_Prov_Security_USERPINMAC  = 4
} E_VDM_Prov_Security_t;

/*!
 *******************************************************************************
 * Callback invoked after a bootstrap session is triggered, to get PIN from
 * user.
 *
 * The PIN must be a string of ASCII-encoded decimal digits (octets with values
 * 0x30 to 0x39).
 *
 * \param	inContext	The context previously set by
 *						\ref VDM_triggerBootstrapSession.
 *
 * \note	On success (VDM_ERR_OK), after the user has entered the PIN
 *			asynchronously, call \ref VDM_notifyUserPinSet to proceed with the
 *			bootstrap session or abort.
 *
 * \return	VDM_ERR_OK on success, VDM_ERR_BOOT_PIN if PIN is unobtainable,
 *			or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_BootGetPinCB)(void *inContext);

/*!
 *******************************************************************************
 * Callback invoked after a bootstrap session is triggered, to get Network
 * specific Shared Secret (NSS).
 *
 * The NSS is network specific. For example, for GSM, it is the IMSI, while for
 * CDMA or TDMA, it is the ESN appended with SSD or SSD_S. The value returned
 * must be in a form ready for input to the MAC calculation and must be derived
 * as described in [PROVBOOT] section 6.
 *
 * \param	outBuffer		Pre-allocated result buffer for the NSS string.
 * \param	inBufferSize	Size of \a outBuffer.
 * \param	outNssLen		Length of the NSS.
 * \param	inContext		The context previously set by
 *							\ref VDM_triggerBootstrapSession.
 *
 * \return	VDM_ERR_OK on success, or VDM_ERR_BOOT_NSS if NSS is unobtainable,
 *			or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_BootGetNssCB)(
	IU8 *outBuffer,
	IU32 inBufferLen,
	IU32 *outNssLenPtr,
	void *inContext);

/*!
 *******************************************************************************
 * Callback invoked after a bootstrap session is triggered to get the Address
 * Type.
 *
 * Invoked after receiving a WAP Profile bootstrap message to determine the
 * value of the DM account node "AddrType". The OMA specification says that the
 * 'DM Client chooses the value according to the transports it supports. The DM
 * Server may modify this in a subsequent DM session.'
 *
 * \param	inAddr		Contents of the DM Account node "Addr", as received
 *						from the WAP bootstrap.
 * \param	outAddrType	Address type. Possible values are: "1" for HTTP, "2"
 *						for WSP, and "3" for OBEX.
 * \param	inContext	The context previously set by
 *						\ref VDM_triggerBootstrapSession.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_BootGetAddrTypeCB)(const char *inAddr, const char **outAddrType, void *inContext);

/*!
 * A structure containing callbacks that may be called during
 * a bootstrap session.
 */
typedef struct {
	VDM_BootGetPinCB getPinCB;              /**< Get PIN from user */
	VDM_BootGetNssCB getNssCB;              /**< Get Network Shared Secret */
	VDM_BootGetAddrTypeCB getAddrTypeCB;    /**< Get 'AddrType' node value */
} VDM_BootCallbacks_t;

/*!
 *******************************************************************************
 * Session context that may be attached to a session triggering request.
 * The session context is attached to every notification of the state of the
 * session.
 *******************************************************************************
 */

typedef struct {
/*!
 * The session context will be sent to all observers. \a initiatorId may
 * be used by an observer to differentiate between the contexts.
 * Note: \a initiatorId is required, and may not be NULL.
 */
	const char *initiatorId;

/*! Context data */
	void *data;

	char sessionKey[MAX_DP_NAME_SIZE];
} VDM_SessionContext_t;

/*!
 * Session Types
 */
typedef enum {
	VDM_SessionType_Boot = 0,   //!< Bootstrap session
	VDM_SessionType_DM = 1,     //!< DM session
	VDM_SessionType_DL = 2      //!< Download session
} E_VDM_SessionType_t;

/*!
 * Session States
 */
typedef enum {
	VDM_SessionState_Started = 0,   //!< Session has started
	VDM_SessionState_Complete = 1,  //!< Session completed successfully
	VDM_SessionState_Aborted = 2    //!< Session aborted
} E_VDM_SessionState_t;

/*!
 *******************************************************************************
 * Notify on session state change.
 *
 * Callback invoked when a bootstrap, DM, or Download session changes its state.
 * Session is typically started and then either completed successfully or
 * aborted. A DM or Download session may also be suspended or resumed. When
 * aborted, \a inLastError indicates the reason for the failure. For all other
 * states \a inLastError is VDM_ERR_OK. \a inDataStr is currently not used.
 *
 * \note	The \a ioContext is de-allocated by the OMA DM Protocol Engine Engine after
 *			all observers have been notified on the session state change.
 *			However it is the responsibility of the creator of the session
 *			context to free the memory of ioContext->data upon a notification
 *			that the session has ended. If an observer frees the memory of the
 *			session context object, it must also set it to NULL, and should use
 *			\ref VDM_destroySessionContext for that purpose.
 *
 * \param	inType		The session type, either bootstrap, DM, or Download.
 * \param	inState		The new session state.
 * \param	inLastError	The reason that the session aborted. Relevant only when
 *						\a inState is "aborted".
 * \param	inDataStr	Currently not used, always NULL.
 * \param	ioContext	The context passed by the session initiator.
 *
 * \return None
 *******************************************************************************
 */
typedef void (*VDM_SessionStateNotifyCB)(
	E_VDM_SessionType_t inType,
	E_VDM_SessionState_t inState,
	VDM_Error inLastError,
	const char *inDataStr,
	VDM_SessionContext_t **ioContext);

/*!
 *******************************************************************************
 * Callback invoked to notify the caller that NIA message content has been
 * parsed successfully after a Notification Initiated DM session (NIDM) is
 * triggered. The parsed content is also passed.
 *
 * After handling the notification alert content, call
 * either \ref VDM_notifyNIASessionProceed to proceed with the DM session or
 * \ref VDM_cancelSession to abort the session.
 *
 * \param	inUIMode					UI Mode, an \ref E_VDM_NIA_UIMode_t
 *										value
 * \param	inDMVersion					DM version, which is always 0.
 * \param	inVendorSpecificData		Vendor-specific data.
 * \param	inVendorSpecificDataLength	Size of \a inVendorSpecificData, in
 *										bytes.
 * \param	inSessionContext			Context passed in the NIA DM session
 *										trigger (\ref VDM_triggerNIADMSession).
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_NIAHandlerCB)(
	E_VDM_NIA_UIMode_t inUIMode,
	IU16 inDMVersion,
	IU8 *inVendorSpecificData,
	IU16 inVendorSpecificDataLength,
	VDM_SessionContext_t *inSessionContext);

/*!
 * Structure used to hold pointers into a buffer for the various elements
 * of a single download object specified in XML Download Descriptor (see the OMA DLOTA specs).
 */
typedef struct {
	IU64 size;                  /*!< The number of bytes to be downloaded from the URI */
	char *strField[E_VDM_DDField_count];
	VDM_Handle_t strFieldMap;   /*!< String values (Note: redundant "size" field) */
} VDM_Downloader_Comp_t;

/*!
 * Structure used to hold pointers into a buffer for the various elements
 * of an XML Download Descriptor (see the OMA DLOTA specs).
 */

#define DC_ARRAY_SIZE 10
typedef struct {
	char *version;
	char *uiInfo;
	IU64 totalSize;                     /*!< The total number of bytes to be downloaded from all URI in dd */
	IU32 dcArrayLen;                    /*!< The number of dcs in dd */
	char *description;                  /*!< A short textual description */
	char *vendor;                       /*!< The organization that provides the media object */
	char *installNotifyURI;             /*!< URI (or URL) to which an installation status report is to be sent */
	VDM_Downloader_Comp_t dcArray[DC_ARRAY_SIZE];   /*!< dc array */
} VDM_Downloader_DD_t;

/*!
 *******************************************************************************
 * Callback invoked to notify the session initiator that a chunk of data has
 * been received after a download session is triggered. The handler should store
 * the downloaded data chunk in storage and may choose to display progress to
 * the user.
 *
 * \param	inDownloadDescriptor	Download Descriptor.
 * \param	inOffset				Offset into the data.
 * \param	inData					Data received from server.
 * \param	inDataSize				Size of \a inData.
 * \param	inContext				Context passed in \ref VDM_triggerDLSession.
 * \param	outOffset				The size of the file on disk after the write
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_HandleDLContentCB)(
	VDM_Downloader_DD_t *inDownloadDescriptor,
	IU32 inIndex,
	IU64 inOffset,
	IU8 *inData,
	IU32 inDataSize,
	VDM_SessionContext_t *inContext,
	IU64 *outOffset);

/*!
 *******************************************************************************
 * Callback invoked to determine the path of the file in which the downloaded
 * data will be stored.
 *
 * \param	inDownloadDescriptor	Download Descriptor.
 * \param	inContext				Context passed in \ref VDM_triggerDLSession.
 * \param	outDLPkgPath			Path for the file.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_GetPkgFilePathCB)(
	VDM_Downloader_DD_t     *inDownloadDescriptor,
	IU32 inIndex,
	VDM_SessionContext_t    *inContext,
	char                    **outDLPkgPath);

/*!
 *******************************************************************************
 * Callback invoked to prompt user to confirm a download. Return TRUE if the
 * prompt is synchronous, or FALSE if asynchronous.
 *
 * \param	inDownloadDescriptor	Download Descriptor.
 * \param	inContext				Context passed in \ref VDM_triggerDLSession.
 *
 * \return	TRUE if a synchronous confirmation and OMA DM Protocol Engine should start
 *			downloading the package immediately, FALSE for an asynchronous
 *			operation. If FALSE, OMA DM Protocol Engine will wait for an confirmation or
 *			cancellation of the download. The caller must later call either
 *			\ref VDM_notifyDLSessionProceed to proceed with the download or
 *			\ref VDM_cancelSession to abort the download.
 *******************************************************************************
 */
typedef IBOOL (*VDM_DownloadPromptCB)(
	VDM_Downloader_DD_t *inDownloadDescriptor,
	VDM_SessionContext_t *inContext);
/*!
 *******************************************************************************
 * Callback invoked to get the maximum free storage size, can be used to
 * get the max free space of an external storage. If the DP size is higher
 * than the max free space - the download will be aborted.
 *
 * \param	outMaxSize	return the max free storage size
 *
 * \return	VDM_ERR_OK for success, else failure
 *******************************************************************************
 */
typedef VDM_Error (*getMaxSizeCB_t)(IU64 *outMaxSize);

/*!
 *******************************************************************************
 * Callback invoked to size of the DP already downloaded to local/external
 * storage
 *
 * \param	inDlPkgHandle - context of the DP
 * \param	outMaxSize	- return the max free storage size
 *
 * \return	VDM_ERR_OK for success, else failure
 *******************************************************************************
 */
typedef VDM_Error (*getPkgSizeCB_t)(const char *inDlPkgHandle,
	IU64 *outPkgSize);

/*!
 *******************************************************************************
 * Callback invoked to check install app Type. Return TRUE is external, or
 * FALSE is internal.
 *
 * \param	inDownloadDescriptor	Download Descriptor.
 * \param	inContext				Context passed in \ref VDM_triggerDLSession.
 * \param   maxSize					maxSize
 * \param   fileSize                package size
 *
 * \return TRUE is external ,FALSE is internal
 *******************************************************************************
 */
typedef IBOOL (*VDM_OnDdReceivedCB)(
	VDM_Downloader_DD_t *inDownloadDescriptor,
	VDM_SessionContext_t *inContext,
	getMaxSizeCB_t *getMaxSizeCb,
	getPkgSizeCB_t *getPkgSizeCb
    );

/*!
 *******************************************************************************
 * Callback invoked before the Engine tries to recover a download session.
 *
 * \note	The error code is passed as the inLastError parameter of the
 *			\ref VDM_SessionStateNotifyCB callback.
 *
 * \param	inUrl		The url of the download object.
 * \param	inOffset	Current offset.
 * \param	inTotal		The size of download object.
 *
 * \return	VDM_ERR_OK to retry the session and continue the download, or
 *          an error code to abort.
 *******************************************************************************
 */
typedef VDM_Error (*VDM_DownloadRetryNotifyCB_t)(
	const char *inUrl,
	IU64 inOffset,
	IU64 inTotal);

/*!
 *******************************************************************************
 * Callback invoked before download is resumed, to compare between dl resume
 * url and dd url.
 *
 * \param	inContext		Context passed in \ref VDM_registerDLResumeCmpUrlCB.
 * \param	inDDUrl			The url which is stored in the DD.
 * \param	inResumeUrl		url stored on last paused download.
 *
 * \return	TRUE if the url is approved and download should continue,
 *			FALSE otherwise.
 *******************************************************************************
 */
typedef IBOOL (*VDM_DLResumeCmpUrlCB_t)(
	void *inContext,
	const char *inDDUrl,
	const char *inResumeUrl);

/*******************************************************************************
 *******************************************************************************
 *
 *								GENERIC	ALERTS
 *
 *******************************************************************************
 *******************************************************************************
 */

/*!
 * Item element in generic alert message.
 */
typedef struct {
	char *sourcePath;     //!< Source path
	char *data;           //!< Data
	char *type;           //!< Type
	char *format;         //!< Format
	char *mark;           //!< Mark
	char *targetPath;     //!< Target path
} VDM_GenAlertItem_t;

/*!
 * Node in a linked list of generic alert's item elements.
 */
typedef struct VDM_GenAlertItem_Node_t {
	VDM_GenAlertItem_t item;    //!< Item data
	struct VDM_GenAlertItem_Node_t *next;   //!< Pointer to the next item
} VDM_GenAlertItem_Node_t;

/*!
 * Generic alert data.
 */
typedef struct VDM_GenAlert_t {
	VDM_GenAlertItem_Node_t *itemList;  //!< List of item elements
	char                    *correlator;    //!< Correlator (or NULL)
} VDM_GenAlert_t;

/*!
 * Node in a linked list of generic alerts.
 */
typedef struct VDM_GenAlertList_Node_t {
	VDM_GenAlert_t alertList;   //!< Alert data
	struct VDM_GenAlertList_Node_t *next;       //!< Pointer to the next alert
} VDM_GenAlertList_Node_t;

/*!
 *******************************************************************************
 * Callback invoked to create the list of generic alerts before a DM session
 * of multiple generic alerts is started
 * (\ref VDM_triggerMultipleGenericAlertsSession). The list of generic alerts
 * is allocated in this API and is later released by OMA DM Protocol Engine.
 *
 * \param	inContext	Context passed by the session initiator.
 * \param	outResult	Returned Error.VDM_ERR_OK on success,
 *                      or a \ref VDM_ERR_defs error code
 *
 * \return	Pointer to a list of generic alerts, where each alert may contain
 *			multiple items. NULL in case of error.
 *******************************************************************************
 */

typedef VDM_GenAlertList_Node_t * (*VDM_CreateGenericAlertsCB)(
	VDM_SessionContext_t *inContext, VDM_Error *outResult);

/*!
 *******************************************************************************
 * Callback invoked to notify on each CP field-value pair while an OMA-CP
 * message is being parsed. The callback is called one extra time with
 * NULL-NULL pair after all parameters have been parsed.
 *
 * \param	inField				The full path of the CP parameter, including
 *								characteristic type.
 * \param	inValue				The value of the CP parameter.
 * \param	inIsAlreadyHandled	Whether the parameter was already handled by the
 *								Engine as part of the CP APPLICATION data
 *								handler.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_CPNotifyCB)(
	const char *inField,
	const char *inValue,
	IBOOL inIsAlreadyHandled);

/*!
 *******************************************************************************
 * Callback invoked when a postponed event time has arrived.
 *
 * \param	inContext	Context passed by the event initiator.
 *
 * \return	None
 *******************************************************************************
 */
typedef void (*VDM_postponedEventCB)(VDM_Handle_t inContext);

/*!
 * Engine states.
 */
typedef enum {
	VDM_EngineState_created,    //!< Engine created
	VDM_EngineState_started,    //!< Engine started
	VDM_EngineState_stopped     //!< Engine stopped
} E_VDM_EngineState_t;

/*!
 *******************************************************************************
 * Callback invoked to encrypt a buffer.
 *
 * Currently used to encrypt the DM Tree.
 *
 * \param	inContext		Context passed in \ ref VDM_registerCryptCallbacks.
 * \param	inPlainText		Buffer to be encrypted.
 * \param	inPlainTextLen	Length of the buffer to be encrypted.
 * \param	outCipherText	Pre-allocated buffer to store the encrypted data.
 * \param	ioCipherLen		The size of \a outCipherText, in bytes. This may
 *							be 0, in which case only the total length of the
 *							data is returned.
 * \param	inIsLast		A flag indicating whether this is the last
 *                          buffer to be encrypted
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BUFFER_OVERFLOW if the supplied buffer is too small,
 *			or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_encryptCB)(
	void *inContext,
	const char *inPlainText,
	IU32 inPlainTextLen,
	char *outCipherText,
	IU32 *ioCipherLen,
	IBOOL inIsLast);

/*!
 *******************************************************************************
 * Callback invoked to decrypt a buffer.
 *
 * Currently used to decrypt the DM Tree.
 *
 * \param	inContext		Context passed in \ ref VDM_registerCryptCallbacks.
 * \param	inCipherText	Buffer to be decrypted.
 * \param	inCipherTextLen	Length of the buffer to be decrypted.
 * \param	outPlainText	Pre-allocated buffer to store the decrypted data.
 * \param	ioPlainTextLen	The size of \a outPlainText, in bytes. This may
 *							be 0, in which case only the total length of the
 *							data is returned.
 * \param	inIsLast		A flag indicating whether this is the last
 *                          buffer to be encrypted
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BUFFER_OVERFLOW if the supplied buffer is too small,
 *			or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_decryptCB)(
	void *inContext,
	const char *inCipherText,
	IU32 inCipherTextLen,
	char *outPlainText,
	IU32 *ioPlainTextLen,
	IBOOL inIsLast);

/*!
 * Encryption callbacks.
 */
typedef struct {
	VDM_encryptCB encryptCB;        //!< Encrypt buffer. Must not be NULL.
	VDM_decryptCB decryptCB;        //!< Decrypt buffer. Must not be NULL.
} VDM_Crypt_Callbacks_t;

/*!
 *******************************************************************************
 * Callback invoked after communication broke, just before attempting to
 * reconnect.
 *
 * \param	inContext		Context passed on registration.
 * \param	inType			The session type: either DM or DL.
 * \param	inLastError		The error which caused communication to break.
 * \param	inRetryCount	The number of retries performed so far.
 *
 * \return	TRUE to continue with connection retries,
 *			FALSE otherwise
 *******************************************************************************
 */
typedef IBOOL (*VDM_connectionRetryNotifyCB_t)(
	void *inContext,
	E_VDM_SessionType_t inType,
	VDM_Error inLastError,
	IU32 inRetryCount);

/*!
 *******************************************************************************
 * Cancel Session Flags
 *******************************************************************************
 */
typedef enum {
	E_VDM_ACTIVE_SESS_Dl,       // Download session
	E_VDM_ACTIVE_SESS_All       // Both DM and Download sessions
} E_VDM_ACTIVE_SESS_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

