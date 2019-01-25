/*
 *******************************************************************************
 *
 * vdm_config.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_config.h
 *
 * \brief	Configuration API
 *******************************************************************************
 */
#ifndef _VDM_CONFIG_H_
#define _VDM_CONFIG_H_

#include <vdm_utl_config.h>

#ifdef __cplusplus
extern "C"
{
#endif

/*! Notification verification modes */
typedef enum {
	/** The verification result of the notification message is ignored.
	    A session is always initiated. */
	E_VDM_NotificationVerificationMode_Disabled,

	/** After an authentication verification failure, try to authenticate
	    again using the special nonce value of 32-bit of zero ((UINT32)0).
	    If successful, initiate a session using the stored credentials. */
	E_VDM_NotificationVerificationMode_Reverify,

	/** After an authentication verification failure, try to authenticate
	    again using the special nonce value of 32-bit of zero ((UINT32)0).
	    If successful, initiate a session based on the nonce value
	    ((UINT32)0). */
	E_VDM_NotificationVerificationMode_ResetNonce,

	/** After an authentication failure, the notification message is ignored
	    and no session is initiated. No attempt is made to re-authenticate. */
	E_VDM_NotificationVerificationMode_Strict
} E_VDM_NotificationVerificationMode_t;

/*! DM versions */
typedef enum {
	E_VDM_DM_Version_1_1_2 = 1, //!< DM version 1.1.2
	E_VDM_DM_Version_1_2 = 2    //!< DM version 1.2
} E_VDM_DM_Version_t;

/*! DM Server types */
typedef enum {
	E_VDM_DM_Server_any = 0,    //!< Any DM server
	E_VDM_DM_Server_wedm = 1,   //!< WEDM DM server
	E_VDM_DM_Server_vzw = 2,    //!< Verizon Wireless DM server
	E_VDM_DM_Server_att = 3,    //!< AT&T DM server
	E_VDM_DM_Server_sbmdm = 5,  //!< Softbank DM server
	E_VDM_DM_Server_bell = 6,   //!< Bell DM server
	E_VDM_DM_Server_daimler = 7,//!< Daimler DM server
	E_VDM_DM_Server_sprint = 8  //!< Sprint DM server
} E_VDM_DM_Server_t;

/*! HTTP authentication levels */
typedef enum {
	E_VDM_HttpAuthLevel_None,   /*!< No server authentication (username and
	                                 password not used) */
	E_VDM_HttpAuthLevel_Basic,  /*!< Basic server authentication (username and
	                                 password required) */
	E_VDM_HttpAuthLevel_Digest  //!< Not supported
} E_VDM_HttpAuthLevel_t;

/*! Alternative Download mechanism */
typedef enum {
	E_VDM_AlternativeDL_DLOTA,  //!< OMA DLOTA
	E_VDM_AlternativeDL_Docomo  //!< Docomo defined download mechanism
} E_VDM_AlternativeDL_t;

typedef enum {
	E_VDM_StatusTrackingLevel_None,
	E_VDM_StatusTrackingLevel_Basic,
	E_VDM_StatusTrackingLevel_Full
} E_VDM_StatusTrackingLevel_t;

#define DESCMO_SET_UI_ENABLED "descmo_set_ui_enabled"
#define DESCMO_GET_UI_ENABLED "descmo_get_ui_enabled"
#define DESCMO_ACTION_UI_ENABLED "descmo_action_ui_enabled"
#define INVENTORY_UPDATE_TIMEOUT "inventory_update_timeout_secs"

/*!
 *******************************************************************************
 * Set the maximum size of a DM message, in bytes. The default is 3000.
 *
 * Call after \ref VDM_create and before \ref VDM_start.
 *
 * \see		VDM_Config_getMaxMsgSize
 *
 * \param	inMaxMsgSize	The maximum size of a DM message, in bytes
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
#define VDM_Config_setMaxMsgSize(inMaxMsgSize) VDM_Config_setIU32("maxmsgsize", inMaxMsgSize)

/*!
 *******************************************************************************
 * Get the maximum size of a DM message, in bytes.
 *
 * \see		VDM_Config_setMaxMsgSize
 *
 * \return	The size in bytes
 *******************************************************************************
 */
#define VDM_Config_getMaxMsgSize() VDM_Config_getIU32("maxmsgsize")

/*!
 *******************************************************************************
 * Set the maximum size of an object in a DM package, in bytes. The default is
 * 100000.
 *
 * Call after \ref VDM_create and before \ref VDM_start.
 *
 * \see		VDM_Config_getMaxObjSize
 *
 * \param	inMaxObjSize	The maximum size of an object in a DM package, in
 *							bytes
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
#define VDM_Config_setMaxObjSize(inMaxObjSize) VDM_Config_setIU32("maxobjsize", inMaxObjSize)

/*!
 *******************************************************************************
 * Get the maximum size of an object in a DM package, in bytes.
 *
 * \see		VDM_Config_setMaxObjSize
 *
 * \return	The size in bytes
 *******************************************************************************
 */
#define VDM_Config_getMaxObjSize() VDM_Config_getIU32("maxobjsize")

/*!
 *******************************************************************************
 * Set the maximum number of retry attempts that OMA DM Protocol Engine will make to
 * reconnect after non-fatal network failures before terminating the
 * connection.
 *
 * The default is 3.
 *
 * Call after \ref VDM_create and before \ref VDM_start.
 *
 * \see		VDM_Config_getMaxNetRetries
 *
 * \param	inMaxNetRetries		Maximum number of retry attempts
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
#define VDM_Config_setMaxNetRetries(inMaxNetRetries) VDM_Config_setIU32("maxnetretries", inMaxNetRetries)

/*!
 *******************************************************************************
 * Get the maximum number of retry attempts that OMA DM Protocol Engine will make to
 * reconnect after non-fatal network failures before terminating the
 * connection.
 *
 * \see		VDM_Config_setMaxNetRetries
 *
 * \return	Maximum number of retry attempts
 *******************************************************************************
 */
#define VDM_Config_getMaxNetRetries() VDM_Config_getIU32("maxnetretries")

/*!
 *******************************************************************************
 * Set DM Account configuration. The default values are:
 * \li DM version: 1.2
 * \li DM Account root: "./DMAcc"
 * \li Update inactive account: FALSE
 *
 * Call after \ref VDM_create and before \ref VDM_start.
 *
 * \see		VDM_Config_getDMAccountConfiguration
 *
 * \param	inActiveAccountDMVersion	The active account DM version, an \ref
 *										E_VDM_DM_Version_t value
 * \param	inDM12AccountRoot			The root for the DM 1.2 account, or
 *										NULL if \a inActiveAccountDMVersion is
 *										1.1.2
 * \param	inUpdateInactiveDMAccount	Deprecated
 * \return	VDM_ERR_OK on success, VDM_ERR_OUT_OF_SYNC if called after
 *			\ref VDM_start, or VDM_ERR_BAD_INPUT if
 *          \a inDM12AccountRoot is ./SyncML/DMAcc, or
 *			\a inActiveAccountDMVersion is 1 (1.1.2), or if
 *			\a inUpdateInactiveDMAccount is true and \a inDM12AccountRoot is
 *			./SyncML/DMAcc
 *******************************************************************************
 */
extern VDM_Error VDM_Config_setDMAccountConfiguration(
	E_VDM_DM_Version_t inActiveAccountDMVersion,
	const char *inDM12AccountRoot,
	IBOOL inUpdateInactiveDMAccount);

/*!
 *******************************************************************************
 * Get DM Account configuration.
 *
 * \see		VDM_Config_setDMAccountConfiguration
 *
 * \param	outActiveAccountDMVersion	Active account DM version, an \ref
 *										E_VDM_DM_Version_t value
 * \param	outDM12AccountRoot			Pointer to the DM 1.2 account root URI
 * \param	outUpdateInactiveDMAccount	Deprecated
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern void VDM_Config_getDMAccountConfiguration(
	E_VDM_DM_Version_t *outActiveAccountDMVersion,
	const char **outDM12AccountRoot,
	IBOOL *outUpdateInactiveDMAccount);

/*!
 *******************************************************************************
 * Set whether only a single DM Account is allowed. When only a single DM
 * Account is allowed, bootstrap is not allowed. The default is FALSE,
 * indicating that multiple accounts are allowed.
 *
 * Call after \ref VDM_create and before \ref VDM_start.
 *
 * \see		VDM_Config_getDMAccSingle
 *
 * \param	inIsSingle	TRUE if there must be exactly one DM Account in the DM
 *						Tree and bootstrap is not allowed, FALSE if multiple
 *						accounts are allowed and bootstrap is allowed
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
#define VDM_Config_setDMAccSingle(inIsSingle) VDM_Config_setEnum("accountsallowed", (IU32)((!inIsSingle)))

/*!
 *******************************************************************************
 * Get whether only a single DM Account is allowed, and bootstrap is not
 * allowed.
 *
 * \see		VDM_Config_setDMAccSingle
 *
 * \return	TRUE if only a single account is allowed, FALSE otherwise
 *******************************************************************************
 */
#define VDM_Config_getDMAccSingle() (!(IBOOL)VDM_Config_getEnum("accountsallowed"))

/*!
 *******************************************************************************
 * Set whether to use the AT&T specific tree structure.
 *
 * Call after \ref VDM_create and before \ref VDM_start.
 *
 * \see		VDM_Config_setUseATTTreeStructure
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
#define VDM_Config_setUseAttTreeStructure() \
	VDM_Config_setEnum("dmserver", E_VDM_DM_Server_att)

/*!
 *******************************************************************************
 * Get whether using AT&T specific tree structure.
 *
 * \see		VDM_Config_getUseAttTreeStructure
 *
 * \return	TRUE if using the AT&T specific tree structure,
 *          FALSE otherwise
 *******************************************************************************
 */
#define VDM_Config_getUseAttTreeStructure() \
	(E_VDM_DM_Server_att == VDM_Config_getEnum("dmserver"))

/*!
 *******************************************************************************
 * Set whether a bootstrap is allowed to overwrite an existing account. The
 * default is FALSE
 *
 * Call after \ref VDM_create and before \ref VDM_start.
 *
 * \see		VDM_Config_setAllowBootstrapOverwriteAccount
 *
 * \param	inIsAllowed		TRUE if a bootstrap may overwrite an existing
 *							DM Account, FALSE otherwise
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
#define VDM_Config_setAllowBootstrapOverwriteAccount(inIsAllowed) VDM_Config_setIBool("allow_bootstrap_overwrite_account", inIsAllowed)

/*!
 *******************************************************************************
 * Get whether a bootstrap is allowed to overwrite an existing account.
 *
 * \see		VDM_Config_setAllowBootstrapOverwriteAccount
 *
 * \return	TRUE if a boostrap can overwrite an existing DM Account, FALSE
 *			otherwise
 *******************************************************************************
 */
#define VDM_Config_getAllowBootstrapOverwriteAccount() VDM_Config_getIBool("allow_bootstrap_overwrite_account")

/*!
 *******************************************************************************
 * Set whether messages are encoded in WBXML format or XML format. The default
 * is TRUE, indicating WBXML format.
 *
 * Call after \ref VDM_create and before \ref VDM_start.
 *
 * \see		VDM_Config_getEncodeWBXMLMsg
 *
 * \param	inIsEncode		TRUE if messages are encoded in WBXML format, FALSE
 *							if messages are encoded in XML format
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
#define VDM_Config_setEncodeWBXMLMsg(inIsEncode) VDM_Config_setEnum("encode", (IU32)inIsEncode)

/*!
 *******************************************************************************
 * Get whether messages are encoded in WBXML or XML format.
 *
 * \see		VDM_Config_setEncodeWBXMLMsg
 *
 * \return	TRUE if messages are encoded in WBXML format,
 *			FALSE if messages are encoded in XML format.
 *******************************************************************************
 */
#define VDM_Config_getEncodeWBXMLMsg() VDM_Config_getEnum("encode")

/*!
 *******************************************************************************
 * Set whether to use 'If-Range' HTTP header - instead of
 * 'If-Match'/'If-Unmodified-Since' - in OMA download retries. The default is
 * TRUE, indicating that 'If-Range' is used.
 *
 * Call after \ref VDM_create and before \ref VDM_start.
 *
 * \see		VDM_Config_getIfRangeInsteadOfIfMatch
 *
 * \param	inIsIfRange	TRUE to use If-Range header, FALSE to use
 *          If-Match/'If-Unmodified-Since'
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
#define VDM_Config_setIfRangeInsteadOfIfMatch(inIsIfRange) VDM_Config_setIBool("if_range_instead_of_if_match", inIsIfRange)

/*!
 *******************************************************************************
 * Get whether 'If-Range' HTTP header is used - instead of
 * 'If-Match'/'If-Unmodified-Since' - in OMA DL retries.
 *
 * \see		VDM_Config_setIfRangeInsteadOfIfMatch
 *
 * \return	TRUE if using If-Range header, FALSE otherwise
 *******************************************************************************
 */
#define VDM_Config_getIfRangeInsteadOfIfMatch() VDM_Config_getIBool("if_range_instead_of_if_match")

/*!
 *******************************************************************************
 * Set Alternative download mechanism. The default is DLOTA, indicating that
 * OMA DLOTA is used.
 *
 * Call after \ref VDM_create.
 *
 * \see		VDM_Config_getAlternativeDL
 *
 * \param	inType	Alternative download mechanism, an
 *					\ref E_VDM_AlternativeDL_t value
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
#define VDM_Config_setAlternativeDL(inType) VDM_Config_setEnum("alternativeDL", (IU32)(inType))

/*!
 *******************************************************************************
 * Get Alternative download mechanism.
 *
 * \see		VDM_Config_setAlternativeDL
 *
 * \return	Alternative download mechanism, an \ref E_VDM_AlternativeDL_t value
 *******************************************************************************
 */
#define VDM_Config_getAlternativeDL() (E_VDM_AlternativeDL_t)VDM_Config_getEnum("alternativeDL")

/*!
 *******************************************************************************
 * Set verification mode for a "General Notification Initiated Session Alert"
 * (NIA) message. The default is "Reset Nonce", which is the OMA DM standard
 * behavior.
 *
 * Call after \ref VDM_create and before \ref VDM_start.
 *
 * \see		VDM_Config_getNotificationVerificationMode
 *
 * \param	inMode	Verification mode, an \ref
 *					E_VDM_NotificationVerificationMode_t value
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
#define VDM_Config_setNotificationVerificationMode(inMode) VDM_Config_setEnum("notif", (IU32)(inMode))

/*!
 *******************************************************************************
 * Get verification mode for a "General Notification Initiated Session Alert"
 * message.
 *
 * \see		VDM_Config_setNotificationVerificationMode
 *
 * \return	Verification mode, an \ref E_VDM_NotificationVerificationMode_t
 *			value
 *******************************************************************************
 */
#define VDM_Config_getNotificationVerificationMode() ((E_VDM_NotificationVerificationMode_t)VDM_Config_getEnum("notif"))

/*!
 *******************************************************************************
 * Set the 'User-Agent' HTTP header used in OMA Download messages. The default
 * is NULL.
 *
 * Call after \ref VDM_create.
 *
 * \see		VDM_Config_getOMADLUserAgentName
 *
 * \param	inOMADLuserAgentName	The 'User-Agent' HTTP header
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_MEMORY if not enough memory for the action, or
 *			VDM_ERR_UNSPECIFIC otherwise
 *******************************************************************************
 */
extern VDM_Error VDM_Config_setOMADLUserAgentName(const char *inOMADLuserAgentName);

/*!
 *******************************************************************************
 * Get the 'User-Agent' HTTP header used in OMA Download messages.
 *
 * \see		VDM_Config_setOMADLUserAgentName
 *
 * \return	The OMA DL User-Agent string, or NULL in case of error
 *******************************************************************************
 */
extern const char *VDM_Config_getOMADLUserAgentName(void);

/*!
 *******************************************************************************
 * Set the 'User-Agent' HTTP header used in OMA DM messages. The default is
 * NULL.
 *
 * Call after \ref VDM_create.
 *
 * \see		VDM_Config_getOMADMUserAgentName
 *
 * \param	inOMADMuserAgentName	The 'User-Agent' HTTP header
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_MEMORY if not enough memory for the action, or
 *			VDM_ERR_UNSPECIFIC otherwise
 *******************************************************************************
 */
extern VDM_Error VDM_Config_setOMADMUserAgentName(const char *inOMADMuserAgentName);

/*!
 *******************************************************************************
 * Get the 'User-Agent' HTTP header used in OMA DM messages.
 *
 * \see		VDM_Config_setOMADMUserAgentName
 *
 * \return	The OMA DM User-Agent string, or NULL in case of error
 *******************************************************************************
 */
extern const char *VDM_Config_getOMADMUserAgentName(void);

/*!
 *******************************************************************************
 * Set the DM Proxy Server address. If not set, a proxy server is not used.
 *
 * Call after \ref VDM_create.
 *
 * \see		VDM_Config_getDMProxy
 *
 * \param	inProxy		DM Proxy Server address
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_MEMORY if not enough memory for the action, or
 *			VDM_ERR_UNSPECIFIC otherwise
 *******************************************************************************
 */
extern VDM_Error VDM_Config_setDMProxy(const char *inProxy);

/*!
 *******************************************************************************
 * Get the DM Proxy Server address, if any.
 *
 * \see		VDM_Config_setDMProxy
 *
 * \return	DM Proxy Server address
 *******************************************************************************
 */
extern const char *VDM_Config_getDMProxy(void);

/*!
 *******************************************************************************
 * Set the DM Proxy Server authentication credentials. The default DM Proxy
 * Server authentication level is none.
 *
 * Call after \ref VDM_create.
 *
 * \note	Proxy authentication information for DM Sessions is passed to
 *			\ref VDM_HTTP_init using \ref VDM_Comm_HTTPParams_t. This
 *			information is never used by the OMA DM Protocol Engine Engine. This
 *			information must be used when using the OMA DM Protocol Engine HTTP Stack
 *			component. If not using HTTP Stack, the HTTP Communication Porting
 *			Layer can be configured directly.
 *
 * \param	inAuthLevel		HTTP authentication level, an
 *							\ref E_VDM_HttpAuthLevel_t value
 * \param	inUserName		Username for proxy authentication
 * \param	inPassword		Password for proxy authentication
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_OUT_OF_SYNC on failure,
 *			VDM_ERR_MEMORY if not enough memory for the action, or
 *			VDM_ERR_NOT_IMPLEMENTED if \a inAuthLevel is
 *			E_VDM_HttpAuthLevel_Digest
 *******************************************************************************
 */
extern VDM_Error VDM_Config_setDMProxyAuthentication(
	E_VDM_HttpAuthLevel_t inAuthLevel,
	const char *inUserName,
	const char *inPassword);

/*!
 *******************************************************************************
 * Set the Download Proxy Server address. If not set, a proxy server is not
 * used.
 *
 * Call after \ref VDM_create.
 *
 * \param	inProxy		Download Proxy Server address
 *
 * \see		VDM_Config_getDLProxy
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_MEMORY if not enough memory for the action, or
 *			VDM_ERR_UNSPECIFIC otherwise
 *******************************************************************************
 */
extern VDM_Error VDM_Config_setDLProxy(const char *inProxy);

/*!
 *******************************************************************************
 * Get the Download Proxy Server address, if any.
 *
 * \see		VDM_Config_setDLProxy
 *
 * \return	Download proxy server address
 *******************************************************************************
 */
extern const char *VDM_Config_getDLProxy(void);

/*!
 *******************************************************************************
 * Set the Download Proxy Server authentication credentials. The default level
 * is E_VDM_HttpAuthLevel_None.
 *
 * Call after \ref VDM_create.
 *
 * \param	inAuthLevel		HTTP authentication level, an
 *							\ref E_VDM_HttpAuthLevel_t value
 * \param	inUserName		Username for proxy authentication
 * \param	inPassword		Password for proxy authentication
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_OUT_OF_SYNC on failure,
 *			VDM_ERR_MEMORY if not enough memory for the action, or
 *			VDM_ERR_NOT_IMPLEMENTED if \a inAuthLevel is
 *			E_VDM_HttpAuthLevel_Digest
 *******************************************************************************
 */
extern VDM_Error VDM_Config_setDLProxyAuthentication(
	E_VDM_HttpAuthLevel_t inAuthLevel,
	const char *inUserName,
	const char *inPassword);

/*!
 *******************************************************************************
 * Set the DM Server HTTP authentication level, an \ref E_VDM_HttpAuthLevel_t
 * value. If not E_VDM_HttpAuthLevel_None, username and password are required;
 * otherwise username and password must be NULL. The default value is
 * E_VDM_HttpAuthLevel_None.
 *
 * Call after \ref VDM_create.
 *
 * \note	HTTP authentication information for DM Sessions is passed to
 *			\ref VDM_HTTP_init using \ref VDM_Comm_HTTPParams_t. This
 *			information is never used by the OMA DM Protocol Engine Engine. This
 *			information must be used when using the OMA DM Protocol Engine HTTP Stack
 *			component. If not using HTTP Stack, the HTTP Communication Porting
 *			Layer can be configured directly.
 *
 * \param	inAuthLevel		HTTP authentication level, an
 *							\ref E_VDM_HttpAuthLevel_t value
 * \param	inUserName		Username for HTTP authentication
 * \param	inPassword		Password for HTTP authentication
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC on failure, or
 *			VDM_ERR_MEMORY if not enough memory for the action, or
 *			VDM_ERR_NOT_IMPLEMENTED if \a inAuthLevel is
 *			E_VDM_HttpAuthLevel_Digest
 *******************************************************************************
 */
extern VDM_Error VDM_Config_setDMHttpAuthentication(
	E_VDM_HttpAuthLevel_t inAuthLevel,
	const char *inUserName,
	const char *inPassword);

/*!
 *******************************************************************************
 * Set the Download Server HTTP authentication level, an
 * \ref E_VDM_HttpAuthLevel_t value. If not E_VDM_HttpAuthLevel_None, username
 * and password are required; otherwise username andi password must be NULL.
 * The default value is E_VDM_HttpAuthLevel_None.
 *
 * Call after \ref VDM_create.
 *
 * \note	HTTP authentication information for Download Sessions is processed
 *			and used by the OMA DM Protocol Engine engine and is not passed to the
 *			Porting Layer.
 *
 * \param	inAuthLevel		HTTP authentication level, an
 *							\ref E_VDM_HttpAuthLevel_t value
 * \param	inUserName		Username for HTTP authentication
 * \param	inPassword		Password for HTTP authentication
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_OUT_OF_SYNC on failure,
 *			VDM_ERR_MEMORY if not enough memory for the action, or
 *			VDM_ERR_NOT_IMPLEMENTED if \a inAuthLevel is
 *			E_VDM_HttpAuthLevel_Digest
 *******************************************************************************
 */
extern VDM_Error VDM_Config_setDLHttpAuthentication(
	E_VDM_HttpAuthLevel_t inAuthLevel,
	const char *inUserName,
	const char *inPassword);

/*!
 ******************************************************************************
 * Set whether both DM and Download sessions can run concurrently.
 *
 * \see		VDM_Config_getEnableConcurrentDmDl
 *
 * \param	isEnabled	TRUE if sessions can run concurrently, FALSE
 *				otherwise
 *
 * \return	VDM_ERR_OK on success, or
 *		VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 ******************************************************************************
 */
#define VDM_Config_setEnableConcurrentDmDl(isEnabled) VDM_Config_setIBool("enable_concurrent_dm_dl", (isEnabled))

/*!
 ******************************************************************************
 * Get whether both DM and Download sessions can run concurrently.
 *
 * \see		VDM_Config_setEnableConcurrentDmDl
 *
 * \return	TRUE if sessions can run concurrently, FALSE otherwise
 ******************************************************************************
 */
#define VDM_Config_getEnableConcurrentDmDl() VDM_Config_getIBool("enable_concurrent_dm_dl")

/*!
 *******************************************************************************
 * Set whether client certificate (HTTPs DM session) is mandatory.
 *
 * Call after \ref VDM_create.
 *
 * \param	inIsMandatory	TRUE if client certificate is mandatory, FALSE otherwise
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
extern VDM_Error VDM_Config_setIsDMClientCertMandatory(IBOOL inIsMandatory);

/*!
 *******************************************************************************
 * Get whether client certificate (HTTPs DM session) is mandatory.
 *
 * \see		VDM_Config_setIsDMClientCertMandatory
 *
 * \return	TRUE if client certificate is mandatory,
 *			FALSE otherwise
 *******************************************************************************
 */
extern IBOOL VDM_Config_getIsDMClientCertMandatory(void);

/*!
 *******************************************************************************
 * Set whether client certificate (HTTPs DL session) is mandatory.
 *
 * Call after \ref VDM_create.
 *
 * \param	inIsMandatory	TRUE if client certificate is mandatory, FALSE otherwise
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
extern VDM_Error VDM_Config_setIsDLClientCertMandatory(IBOOL inIsMandatory);

/*!
 *******************************************************************************
 * Get whether client certificate (HTTPs DL session) is mandatory.
 *
 * \see		VDM_Config_setIsDLClientCertMandatory
 *
 * \return	TRUE if client certificate is mandatory,
 *			FALSE otherwise
 *******************************************************************************
 */
extern IBOOL VDM_Config_getIsDLClientCertMandatory(void);

/*
 * Non OMA-Compliant behavior configuration
 */

/*!
 *******************************************************************************
 * Set whether to abort a session with VDM_ERR_COMMAND_FAILED after receiving
 * a command status which is not 2xx (success range).
 *
 * This configuration will not affect the returned values in other abort cases,
 * even if they involve a status which is different than the above. Note that
 * in package 2, status codes of 401 (Unauthorized) and 407 (Authentication
 * required) are handled and will not cause the session to abort even if the
 * configuration is set.
 *
 * The default is FALSE, indicating not to abort after receiving a command
 * status which is different from the status codes mentioned above.
 *
 * Call after \ref VDM_create and before \ref VDM_start.
 *
 * \note	Setting this configuration to TRUE contradicts OMA DM standard
 *			behavior and can break the client-server authentication negotiation
 *			when the authentication type is other than
 *			E_VDM_HttpAuthLevel_None.
 *
 * \note	SyncHdr status codes are considered authentication status and not
 *			command status, regardless of the settings of this configuration
 *			option. Therefore, \ref VDM_ERR_AUTHENTICATION will be returned on
 *			SyncHdr status codes.
 *
 * \see		VDM_Config_getAbortIfClientCommandFailed
 *
 * \param	inIsAbort	TRUE to abort session after receiving a command status
 *						other than 2xx (success range) in Packages 2 and 4,
 *						and other than 401 (Unauthorized) or 407
 *						(Authentication required) in package 2
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
#define VDM_Config_setAbortIfClientCommandFailed(inIsAbort) VDM_Config_setIBool("abort_if_client_command_failed", inIsAbort)

/*!
 *******************************************************************************
 * Get whether OMA DM Protocol Engine is set to abort the session with
 * VDM_ERR_COMMAND_FAILED after receiving a command status which other than:
 * 2xx (success range), 401 (Unauthorized), and 407 (Authentication required).
 *
 * \see		VDM_Config_setAbortIfClientCommandFailed
 *
 * \return	TRUE if set to abort the session after receiving a command status
 *			other than 2xx in packages 2 and 4, and other than 2xx, 401, 407 in
 *			package 2.
 *******************************************************************************
 */
#define VDM_Config_getAbortIfClientCommandFailed() VDM_Config_getIBool("abort_if_client_command_failed")

/*!
 *******************************************************************************
 * Set whether the server delivers a new client nonce to be used for each new
 * message, or just once per session. This is only relevant for HMAC
 * authentication. The default is TRUE, indicating a new client nonce for each
 * new message.
 *
 * Call after \ref VDM_create and before \ref VDM_start.
 *
 * \note	Setting this configuration to FALSE contradicts OMA DM standard
 *			behavior and reduces authentication security, and is not
 *			recommended.
 *
 * \see		VDM_Config_getIsClientNoncePerMessage
 *
 * \param	inIsClientNoncePerMessage	TRUE to deliver a new client nonce for
 *										each message, FALSE if only one client
 *										nonce per session
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
#define VDM_Config_setIsClientNoncePerMessage(inIsClientNoncePerMessage) VDM_Config_setIBool("is_client_nonce_per_message", inIsClientNoncePerMessage)

/*!
 *******************************************************************************
 * Get whether the server delivers a new client nonce to be used for each new
 * message, or just once per session. This is only relevant for HMAC
 * authentication.
 *
 * \see		VDM_Config_setIsClientNoncePerMessage
 *
 * \return	TRUE if the server delivers a new client nonce for each new
 *			message, FALSE otherwise
 *******************************************************************************
 */
#define VDM_Config_getIsClientNoncePerMessage() VDM_Config_getIBool("is_client_nonce_per_message")

/*!
 *******************************************************************************
 * Set whether the client delivers a new server nonce to be used for each new
 * message, or just once per session. This is only relevant for HMAC
 * authentication. The default value is TRUE, indicating a new server nonce
 * for each new message.
 *
 * Call after \ref VDM_create and before \ref VDM_start.
 *
 * \note	Setting this configuration to FALSE contradicts OMA DM standard
 *			behavior and reduces authentication security, and is not
 *			recommended.
 *
 * \see		VDM_Config_getIsServerNoncePerMessage
 *
 * \param	inIsServerNoncePerMessage	TRUE to deliver a new server nonce for
 *										each message, FALSE if only one server
 *										nonce per session.
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
#define VDM_Config_setIsServerNoncePerMessage(inIsServerNoncePerMessage) VDM_Config_setIBool("is_server_nonce_per_message", inIsServerNoncePerMessage)

/*!
 *******************************************************************************
 * Get whether the client delivers a new server nonce to be used for each new
 * message, or just once per session. This is only relevant for HMAC
 * authentication.
 *
 * \see		VDM_Config_setIsServerNoncePerMessage
 *
 * \return	TRUE if the client delivers a new server nonce for each new
 *			message, FALSE otherwise
 *******************************************************************************
 */
#define VDM_Config_getIsServerNoncePerMessage() VDM_Config_getIBool("is_server_nonce_per_message")

/*!
 *******************************************************************************
 * Set whether to encode binary data sent over WBXML in Base64. The default
 * is FALSE, indicating not to encode binary data sent over WBXML in
 * Base64.
 *
 * Call after \ref VDM_create and before \ref VDM_start.
 *
 * \note	Setting this configuration to TRUE contradicts OMA DM standard
 *			behavior and is not recommended.
 *
 * \see		VDM_Config_getB64EncodeBinDataOverWBXML
 *
 * \param	inIsB64		TRUE to encode binary data sent over WBXML in Base64,
 *						FALSE otherwise
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
#define VDM_Config_setB64EncodeBinDataOverWBXML(inIsB64) VDM_Config_setIBool("isForceB64EncodeBinDataOverWBXML", (inIsB64))

/*!
 *******************************************************************************
 * Get whether binary data sent over WBXML is encoded in Base64.
 *
 * \see		VDM_Config_setB64EncodeBinDataOverWBXML
 *
 * \return	TRUE if binary data sent over WBXML is encoded in Base64, FALSE
 *			otherwise
 *******************************************************************************
 */
#define VDM_Config_getB64EncodeBinDataOverWBXML() VDM_Config_getIBool("isForceB64EncodeBinDataOverWBXML")

/*!
 *******************************************************************************
 * Set whether to allow a challenge with Package 1. The default is FALSE,
 * indicating not to allow a challenge with Package 1.
 *
 * Call after \ref VDM_create and before \ref VDM_start.
 *
 * \note	Setting this configuration to TRUE contradicts OMA DM standard
 *			behavior and is not recommended.
 *
 * \see		VDM_Config_getAllowChallengeWithPkg1
 *
 * \param	inIsAllowed		TRUE if a challenge with Package 1 is allowed.
 *							FALSE otherwise
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
#define VDM_Config_setAllowChallengeWithPkg1(inIsAllowed) VDM_Config_setIBool("allowchallangepkg1", inIsAllowed)

/*!
 *******************************************************************************
 * Get whether a challenge with Package 1 is allowed.
 *
 * \see		VDM_Config_setAllowChallengeWithPkg1
 *
 * \return	TRUE if a challenge with Package 1 is allowed, FALSE otherwise
 *******************************************************************************
 */
#define VDM_Config_getAllowChallengeWithPkg1() VDM_Config_getIBool("allowchallangepkg1")

/*!
 *******************************************************************************
 * Set session ID to decimal or hex. The default is FALSE, indicating hex.
 *
 * Call after \ref VDM_create and before \ref VDM_start.
 *
 * \note	Setting this configuration to TRUE (decimal) contradicts OMA DM
 *			standard behavior and is not recommended.
 *
 * \see		VDM_Config_getSessionIDAsDec
 *
 * \param	inSessionIDAsDec	TRUE if session ID is decimal, FALSE if
 *								session ID is hex
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
#define VDM_Config_setSessionIDAsDec(inSessionIDAsDec) VDM_Config_setIBool("session_id_as_dec", inSessionIDAsDec)

/*!
 *******************************************************************************
 * Get whether session ID is decimal or hex.
 *
 * \see		VDM_Config_setSessionIDAsDec
 *
 * \return	TRUE if session ID is decimal, FALSE if it is hex
 *******************************************************************************
 */
#define VDM_Config_getSessionIDAsDec() VDM_Config_getIBool("session_id_as_dec")

/*!
 *******************************************************************************
 * Set whether to verify the version and type of the parsed Download
 * Descriptor. The default is FALSE, indicating no verification.
 *
 * Call after \ref VDM_create and before \ref VDM_start.
 *
 * \note	Setting this configuration to TRUE contradicts OMA DM standard
 *			behavior and is not recommended. Verification should be used only
 *			when working with servers producing invalid Download Descriptors.
 *
 * \see		VDM_Config_getDDVersionCheck
 *
 * \param	inDDVersionCheck	TRUE to verify the version and the type of the
 *								parsed Download Descriptor, FALSE otherwise
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
#define VDM_Config_setDDVersionCheck(inDDVersionCheck) VDM_Config_setIBool("dd_version_check", inDDVersionCheck)

/*!
 *******************************************************************************
 * Get whether to verify the version and the type of the parsed Download
 * Descriptor.
 *
 * \see		VDM_Config_setDDVersionCheck
 *
 * \return	TRUE if Download Descriptor version is verified, FALSE otherwise
 *******************************************************************************
 */
#define VDM_Config_getDDVersionCheck() VDM_Config_getIBool("dd_version_check")

/*!
 *******************************************************************************
 * Set whether the SyncML PCDATA opaque content type is encoded as CDATA or as
 * a string. The default is TRUE, indicating CDATA encoding.
 *
 * Call after \ref VDM_create and before \ref VDM_start.
 *
 * \note	This configuration may produce output that contradicts OMA DM
 *			standard behavior and should be used for testing purposes only.
 *
 * \see		VDM_Config_getPCDataOpaqueAsCDATA
 *
 * \note	This configuration option has no effect on WBXML encoding.
 *
 * \param	inAsCData	TRUE if SyncML PCDATA is encoded as CDATA, FALSE if
 *						the data is encoded as a string
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
#define VDM_Config_setPCDataOpaqueAsCDATA(inAsCData) VDM_Config_setEnum("pcdataopaque", (IU32)(inAsCData))

/*!
 *******************************************************************************
 * Get whether the SyncML PCDATA opaque content type is encoded as CDATA or as
 * a string.
 *
 * \see		VDM_Config_setPCDataOpaqueAsCDATA
 *
 * \return	TRUE if SyncML PCDATA is encoded as CDATA, FALSE if the data is
 *			encoded as a string
 *******************************************************************************
 */
#define VDM_Config_getPCDataOpaqueAsCDATA() ((IBOOL)(VDM_Config_getEnum("pcdataopaque")))

/*!
 *******************************************************************************
 * Set whether a URL must be absolute, which means that the URL must include
 * the "http://" or "https://" prefix. The default is FALSE, indicating
 * that the URL may be relative.
 *
 * Call after \ref VDM_create and before \ref VDM_start.
 *
 * \see		VDM_Config_getIsOMADLAbsoluteURL
 *
 * \param	inIsAbsoulteURL		TRUE if the URL must be absolute, FALSE
 *								otherwise
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
#define VDM_Config_setIsOMADLAbsoluteURL(inIsAbsoulteURL) VDM_Config_setIBool("absurl", inIsAbsoulteURL)

/*!
 *******************************************************************************
 * Get whether URL must be absolute (include "http://" or "https://" prefix).
 *
 * \see		VDM_Config_setIsOMADLAbsoluteURL
 *
 * \return	TRUE if URL must be absolute, FALSE otherwise
 *******************************************************************************
 */
#define VDM_Config_getIsOMADLAbsoluteURL() VDM_Config_getIBool("absurl")

/*!
 *******************************************************************************
 * Enable or disable TNDS support. If disabled, OMA DM Protocol Engine responds with
 * status code 406 ("Optional feature not supported") to any TNDS command sent
 * from the server. The default is TRUE, inidicating that TNDS support is
 * enabled.
 *
 * Call after \ref VDM_create and before \ref VDM_start.
 *
 * \see		VDM_Config_getIsTndsEnabled
 *
 * \param	isEnabled	TRUE to enable TNDS support, FALSE to disable
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
#define VDM_Config_setTndsEnabled(isEnabled) VDM_Config_setIBool("enable_tnds", isEnabled)

/*!
 *******************************************************************************
 * Get whether TNDS support is enabled or disabled.
 *
 * \see		VDM_Config_setTndsEnabled
 *
 * \return	TRUE if TNDS support is enabled, FALSE if disabled
 *******************************************************************************
 */
#define VDM_Config_getTndsEnabled() VDM_Config_getIBool("enable_tnds")

/*!
 *******************************************************************************
 * Swap between client and server authentication in CP. Used for backward
 * compatibility with older versions of OMA DM Protocol Engine (before 04.05.01).
 *
 * Call after \ref VDM_create and before \ref VDM_start.
 *
 * \see		VDM_Config_getSwapCpPeers
 *
 * \param	inIsSwapped		TRUE to swap between the authentication fields,
 *							FALSE otherwise
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
#define VDM_Config_setSwapCpPeers(inIsSwapped) VDM_Config_setIBool("swap_cp_peers", inIsSwapped)

/*!
 *******************************************************************************
 * Get whether client and server authentication fields are swapped in CP.
 *
 * \see		VDM_Config_setSwapCpPeers
 *
 * \return	TRUE if the fields are swapped, FALSE otherwise
 *******************************************************************************
 */
#define VDM_Config_getSwapCpPeers() VDM_Config_getIBool("swap_cp_peers")

/*!
 *******************************************************************************
 * Set socket connection idleness timeout. The default is 0, indicating no
 * timeout.
 *
 * Call after \ref VDM_create.
 *
 * \param	inConnTimeoutMS		Socket connection timeout, in milliseconds, or
 *								0 indicating no timeout
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
extern VDM_Error VDM_Config_setConnIdleTimeout(IU32 inConnTimeoutMS);

/*!
 *******************************************************************************
 * Set whether HTTP secured socket layer (HTTPS) is mandatory.
 *
 * Call after \ref VDM_create.
 *
 * \param	inIsMandatory	TRUE if HTTPS is mandatory, FALSE otherwise
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
extern VDM_Error VDM_Config_setIsHttpsMandatory(IBOOL inIsMandatory);

/*!
 *******************************************************************************
 * Get whether HTTP secured socket layer (HTTPS) is mandatory.
 *
 * \see		VDM_Config_setIsHttpsMandatory
 *
 * \return	TRUE if HTTPS is mandatory,
 *			FALSE otherwise
 *******************************************************************************
 */
extern IBOOL VDM_Config_getIsHttpsMandatory(void);

/*!
 *******************************************************************************
 * Set whether the OMA Download status report mechanism reports all download
 * results - success or errors - or only success. Reports are sent only if the
 * InstallNotifyURI attribute exists in the download descriptor. The default is
 * FALSE, indicating all results are reported.
 *
 * \note	Setting this configuration to TRUE contradicts OMA Download
 *			standard behavior and is not recommended.
 *
 * Call after \ref VDM_create and before \ref VDM_start.
 *
 * \see		VDM_Config_getInstallNotifySuccessOnly
 *
 * \param	inIsSuccessOnly		TRUE if only success is reported, FALSE
 *								if all results are reported
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
#define VDM_Config_setInstallNotifySuccessOnly(inIsSuccessOnly) VDM_Config_setIBool("installnotifysuccessonly", inIsSuccessOnly)

/*!
 *******************************************************************************
 * Get whether the OMA Download status report mechanism reports all download
 * results - success or errors - or only success.
 *
 * \see		VDM_Config_setInstallNotifySuccessOnly
 *
 * \return	TRUE if only success is reported, FALSE if all results are reported
 *******************************************************************************
 */
#define VDM_Config_getInstallNotifySuccessOnly() VDM_Config_getIBool("installnotifysuccessonly")
/*!
 *******************************************************************************
 * Set whether the 202 ("Accepted for Processing") status code is supported by
 * the DM Server on ansynchronous operations. If not supported, 200 ("OK") is
 * used. The default is FALSE, indicating that 202 is supported.
 *
 * \note	This configuration does not affect behavior of OMA DM Protocol Engine
 *			Engine, but may be used by MO components of the framework.
 *
 * \note	Setting this configuration to TRUE contradicts OMA DM standard
 *			behavior and is not recommended.
 *
 * Call after \ref VDM_create and before \ref VDM_start.
 *
 * \see		VDM_Config_get202statusCodeNotSupportedByServer
 *
 * \param	inIsNotSupported	TRUE if the DM Server does not support "202",
 *								FALSE otherwise
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
#define VDM_Config_set202statusCodeNotSupportedByServer(inIsNotSupported) \
	VDM_Config_setIBool("server_202_unsupported", inIsNotSupported)

/*!
 *******************************************************************************
 * Get whether the 202 ("Accepted for Processing") status code is supported by
 * the DM Server on ansynchronous operations.
 *
 * \see		VDM_Config_get202statusCodeNotSupportedByServer
 *
 * \return	TRUE if the DM Server does not support "202", FALSE otherwise
 *******************************************************************************
 */
#define VDM_Config_get202statusCodeNotSupportedByServer() VDM_Config_getIBool("server_202_unsupported")

/*!
 *******************************************************************************
 * Set that a missing eTag or date should be ignored while resuming a download.
 * When set, the object URL will be used as the object identifier for resuming
 * the download.
 *
 * \note	Setting this configuration to TRUE contradicts OMA DM standard
 *			behavior and is not recommended. Use only if the server is
 *			committed to not change the content of the object file.
 *
 * \see		VDM_Config_getIgnoreMissingETag
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
#define VDM_Config_setIgnoreMissingETag() VDM_Config_setIBool("ignore_missing_etag", TRUE)

/*!
 *******************************************************************************
 * Get whether a missing eTag or date should be ignored while resuming a
 * download.
 *
 * \see		VDM_Config_setIgnoreMissingETag
 *
 * \return	TRUE if a missing eTag should be ignored while resuming a download,
 *			FALSE otherwise
 *******************************************************************************
 */
#define VDM_Config_getIgnoreMissingETag() VDM_Config_getIBool("ignore_missing_etag")

/*!
 *******************************************************************************
 * Treat the download package URL as a reference to a DD.
 *
 * \note	Setting this configuration contradicts OMA DM standard behavior and
 *			is not recommended.
 *
 * \see		VDM_Config_getPkgURLIsAlwaysDD
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
#define VDM_Config_setPkgURLIsAlwaysDD() VDM_Config_setIBool("pkgurl_is_always_dd", TRUE)

/*!
 *******************************************************************************
 * Get whether the pointer to the DD is actually the pointer to the DP.
 *
 * \see		VDM_Config_setPkgURLIsAlwaysDD
 *
 * \return	TRUE if the pointer to the DD is actually the pointer to the DP,
 *			FALSE otherwise
 *******************************************************************************
 */
#define VDM_Config_getPkgURLIsAlwaysDD() VDM_Config_getIBool("pkgurl_is_always_dd")

/*!
 *******************************************************************************
 * Set a configuration parameter. Use if you don't know the type, such as when
 * parsing the configuration file.
 *
 * \param	key		Parameter name
 * \param	value	Value
 * \param	err		Output: VDM_ERR_OK on success, or a \ref VDM_Error value
 *
 * \return	TRUE on success, FALSE otherwise
 *******************************************************************************
 */
extern IBOOL VDM_Config_setValue(const char *key, const char *value,
	VDM_Error *err);

/*!
 *******************************************************************************
 * Set a configuration string parameter.
 *
 * \param	key		Parameter name
 * \param	value	Value
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_Error value
 *******************************************************************************
 */
extern VDM_Error VDM_Config_setStr(const char *key, const char *value);

/*!
 *******************************************************************************
 * Get a configuration string parameter value.
 *
 * \param	key		Parameter name
 *
 * \return	Value
 *******************************************************************************
 */
extern char *VDM_Config_getStr(const char *key);

/*!
 *******************************************************************************
 * Set a configuration boolean parameter.
 *
 * \param	key		Parameter name
 * \param	value	Value
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_Error value
 *******************************************************************************
 */
extern VDM_Error VDM_Config_setIBool(const char *key, IBOOL value);

/*!
 *******************************************************************************
 * Get a configuration boolean parameter value.
 *
 * \param	key		Parameter name
 *
 * \return	Value
 *******************************************************************************
 */
extern IBOOL VDM_Config_getIBool(const char *key);

/*!
 *******************************************************************************
 * Set a configuration integer parameter.
 *
 * \param	key		Parameter name
 * \param	value	Value
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_Error value
 *******************************************************************************
 */
extern VDM_Error VDM_Config_setIU32(const char *key, IU32 value);

/*!
 *******************************************************************************
 * Get a configuration integer parameter value.
 *
 * \param	key		Parameter name
 *
 * \return	Value
 *******************************************************************************
 */
extern IU32 VDM_Config_getIU32(const char *key);

/*!
 *******************************************************************************
 * Set a configuration enumeration parameter value (an integer index).
 *
 * \param	key		Parameter name
 * \param	value	Value
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_Error value
 *******************************************************************************
 */
extern VDM_Error VDM_Config_setEnum(const char *key, IU32 value);

/*!
 *******************************************************************************
 * Get a configuration enumeration parameter value (an integer index).
 *
 * \param	key		Parameter name
 *
 * \return	Value
 *******************************************************************************
 */
extern IU32 VDM_Config_getEnum(const char *key);

/*!
 *******************************************************************************
 * Print usage information.
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_Config_usage(const char *inGroup, const char *inTitle,
	IBOOL inPrintGroupPrefix);

/*!
 *******************************************************************************
 * Get root node of DM Accounts in the DM Tree.
 *
 * \return	Root node
 *******************************************************************************
 */
#define VDM_Config_getDMAccRoot() (VDM_Config_getStr("12accountroot"))

/*!
 *******************************************************************************
 * Get whether server authentication is required.
 *
 * \return	TRUE if server authentication is required, FALSE otherwise
 *******************************************************************************
 */
#define VDM_Config_getIsServerAuthRequired() VDM_Config_getIBool("isServerAuthRequired")

/*!
 *******************************************************************************
 * Get whether a 212 response is permitted with HMAC authentication.
 *
 * \return	TRUE if 212 response is permitted, FALSE otherwise
 *******************************************************************************
 */
#define VDM_Config_getIsAllow212WithHMAC() VDM_Config_getIBool("isAllow212WithHMAC")

/*!
 *******************************************************************************
 * Get whether using sequential nonces.
 *
 * \return	TRUE if using sequential nonces, FALSE otherwise
 *******************************************************************************
 */
#define VDM_Config_getUseSequentialNonces() VDM_Config_getIBool("isUseSequentialNonces")

/*!
 *******************************************************************************
 * Set DM Server version.
 *
 * \param	inVersion	DM Server version, an \ref E_VDM_DM_Server_t value
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_Error value
 *******************************************************************************
 */
#define VDM_Config_setDMVersion(inVersion) VDM_Config_setEnum("dmversion", inVersion)

/*!
 *******************************************************************************
 * Get DM Server version.
 *
 * \return	DM Server version, an \ref E_VDM_DM_Server_t value
 *******************************************************************************
 */
#define VDM_Config_getDMVersion() VDM_Config_getEnum("dmversion")

/*!
 *******************************************************************************
 * Allow FUMO status codes other than OMA DM values. This allows vendors to send
 * their own FUMO error codes to the server using
 * \ref VDM_FUMO_triggerReportSession.
 *
 * \note	Setting this configuration contradicts OMA DM standard behavior and
 *			is not recommended.
 *
 * \see		VDM_Config_getIfUsingeExtendedFumoStatusCodes
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
#define VDM_Config_setUseExtendedFumoStatusCodes() VDM_Config_setIBool("use_extended_fumo_status_codes", TRUE)

/*!
 ******************************************************************************
 * Get whether FUMO status codes can include values other than OMA DM values.
 *
 * \see		VDM_Config_setUseExtendedFumoStatusCodes
 *
 * \return	TRUE if FUMO status codes can include other values,
 *			FALSE otherwise
 ******************************************************************************
 */
 #define VDM_Config_getIfUsingeExtendedFumoStatusCodes() VDM_Config_getIBool("use_extended_fumo_status_codes")

/*!
 *******************************************************************************
 * Get the max retries parameter for insert Usb.
 *
 * \return	The maximum number of retries
 *******************************************************************************
 */
#define VDM_Config_getInsertUsbMaxRetries() VDM_Config_getIU32("insert_usb_max_retries")

/*!
 *******************************************************************************
 * Get the timeout parameter for insert Usb (in seconds).
 *
 * \return	The timeout in seconds
 *******************************************************************************
 */
#define VDM_Config_getInsertUsbTimeoutSeconds() VDM_Config_getIU32("insert_usb_timeout_seconds")

/// @cond EXCLUDE

VDM_Error VDM_Config_add(const char *group, const char *key,
	configType_t configType, IU32 flags, const char *usage,
	const char *defaultValue, lookupTable_t *lookupTable, const char *altKey,
	VDM_Error (*configCB)(VDM_UTL_Config_t *context, VDM_UTL_Config_cfg_t *cfg));

/// @endcond

/*!
 *******************************************************************************
 * Declare an existing configuration key to be tree-controlled.
 * Note: \a inKey must have already been added by \ref VDM_UTL_Config_add.
 * Must be called after VDM_start
 *
 * \param	inContext		Configuration context
 * \param	inKey			Key
 * \param	inURI			The full pathname of the treeCtrl node.
 * \return	VDM_ERR_OK
 *******************************************************************************
 */
VDM_Error VDM_Config_declareTreeCtrl(const char *inKey, const char *inUri);

/*!
 *******************************************************************************
 * registering a call back to be called when the the config parameter is changed.
 *
 * \param	inFunc			The call back function
 * \param	inKey			Key
 * \param	inContext		The context to be passed to the call back when invoked.
 * \return	VDM_ERR_OK on success, or a \ref VDM_Error value
 *******************************************************************************
 */
VDM_Error VDM_Config_registerOnChange(VDM_UTL_Config_onValueChangedCB inFunc,
	const char *inKey, void *inContext);

/*!
 *******************************************************************************
 * unregistering a call back to be called when the the config parameter is
 * changed.
 *
 * \param	pContext		Configuration context
 * \param	inFunc			The call back function
 * \param	inKey			Key
 *
 * \return	The context
 *******************************************************************************
 */
void *VDM_Config_unregisterOnChange(VDM_UTL_Config_onValueChangedCB inFunc,
	const char *inKey);

/*!
 *******************************************************************************
 * Set whether non-standard domain name is supported for DM (non-strict wildcard).
 *
 * Call after \ref VDM_create.
 *
 * \param	inIsSupported	TRUE if non-standard domain name is supported,
 *                          FALSE otherwise
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
extern VDM_Error VDM_Config_setIsDMNonStandardDomainSupported(IBOOL inIsSupported);

/*!
 *******************************************************************************
 * Get non-standard domain name is supported for DM.
 *
 * \see		VDM_Config_setIsDMNonStandardDomainSupported
 *
 * \return	TRUE if non-standard domain name is supported,
 *			FALSE otherwise
 *******************************************************************************
 */
extern IBOOL VDM_Config_getIsDMNonStandardDomainSupported(void);
/*!
 *******************************************************************************
 * Set whether non-standard domain name is supported for DL (non-strict wildcard).
 *
 * Call after \ref VDM_create.
 *
 * \param	inIsSupported	TRUE if non-standard domain name is supported,
 *                          FALSE otherwise
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_OUT_OF_SYNC if called after \ref VDM_start
 *******************************************************************************
 */
extern VDM_Error VDM_Config_setIsDLNonStandardDomainSupported(IBOOL inIsSupported);

/*!
 *******************************************************************************
 * Get non-standard domain name is supported for DL.
 *
 * \see		VDM_Config_setIsDLNonStandardDomainSupported
 *
 * \return	TRUE if non-standard domain name is supported,
 *			FALSE otherwise
 *******************************************************************************
 */
extern IBOOL VDM_Config_getIsDLNonStandardDomainSupported(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
