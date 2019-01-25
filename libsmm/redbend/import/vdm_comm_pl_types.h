/*
 *******************************************************************************
 *
 * vdm_comm_pl_types.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_comm_pl_types.h
 *
 * \brief	Communications Porting Layer Types and Definitions
 *******************************************************************************
 */
#ifndef _VDM_COMM_PL_TYPES_H_
#define _VDM_COMM_PL_TYPES_H_       //!< Internal

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @addtogroup pl_comm	Communication
 * @ingroup pl
 * @{
 */

/*!
 *******************************************************************************
 * Send a "Comm Initialized" notification after communication was initialized as
 * a result of \ref VDM_Comm_PL_Conn_init.
 *
 * \param	inContext	Comm Observer context.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Comm_notifyCommInitCB)(VDM_Handle_t inContext);

/*!
 *******************************************************************************
 * Send a "Comm Opened" notification after a port is opened as a result of
 * \ref VDM_Comm_PL_Conn_open. The first parameter is the Comm Observer context
 * (\a inContext). The second parameter is a unique connection id that will
 * later be used on subsequent calls to this connection.
 *
 * \param	inContext	Comm Observer context.
 * \param	inConnId	ID of new connection.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Comm_notifyCommOpenCB)(VDM_Handle_t inContext, IS32 inConnId);

/*!
 *******************************************************************************
 * Send a "Comm Transport" notification after data is received. The first
 * parameter is the Comm Observer context (\a inContext). The second parameter
 * is the unique connection id returned by the "Comm Opened" notification.
 *
 * \param	inContext	Comm Observer context.
 * \param	inConnId	ID of new connection where transport has occurred.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Comm_notifyTransportCB)(VDM_Handle_t inContext, IS32 inConnId);

/*!
 *******************************************************************************
 * Send a "Comm Broken" notification when a connection has failed or when a
 * connection has been terminated abruptly. The first parameter is the Comm
 * Observer context (\a inContext). The second parameter is the unique
 * connection id returned by the "Comm Opened" notification.
 *
 * The third parameter specifies what type of error. For a recoverable error,
 * such as VDM_ERR_COMMS_NON_FATAL, the Engine will try to reconnect.
 *
 * \param	inContext		Comm Observer context.
 * \param	inConnId		ID of the broken connection.
 * \param	inError			The error which caused the communication to break.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Comm_notifyCommBrokenExCB)(VDM_Handle_t inContext, IS32 inConnId, VDM_Error inError);

/*!
 *******************************************************************************
 * Send a "Comm Closed" notification after communication was closed as
 * a result of \ref VDM_Comm_PL_Conn_close.
 *
 * \param	inContext	Comm Observer context.
 * \param	inConnId	ID of the closed connection.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Comm_notifyCommClosedCB)(VDM_Handle_t inContext, IS32 inConnId);

/*!
 *******************************************************************************
 * Send a "Comm Termination" notification after communication was terminated as
 * a result of \ref VDM_Comm_PL_Conn_term.
 *
 * \param	inContext	Comm Observer context.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Comm_notifyCommTermCB)(VDM_Handle_t inContext);

/*!
 *******************************************************************************
 * The Comm Observer structure.
 *
 * The Comm Observer is a structure of callback pointers created by the OMA DM
 * Protocol Engine and passed to the communication component upon initialization.
 * The initialization API must make the structure available to the open,
 * send, and receive APIs. The implementation of each of these APIs should
 * invoke the corresponding notification callback, as required.
 *
 * The Comm Observer monitors the networking communication. The
 * open, send, and receive callbacks must notify the Comm Observer on success
 * or failure; the Comm Observer then notifies the Engine of the communication
 * event.
 *******************************************************************************
 */
typedef struct {
	VDM_Handle_t context;                               /**< Comm Observer context */
	VDM_Comm_notifyCommInitCB notifyCommInit;           /**< Init request callback */
	VDM_Comm_notifyCommOpenCB notifyCommOpen;           /**< Open request callback */
	VDM_Comm_notifyTransportCB notifyTransport;         /**< Transport notification */
	VDM_Comm_notifyCommBrokenExCB notifyCommBrokenEx;   /**< Communication break notification */
	VDM_Comm_notifyCommClosedCB notifyCommClosed;       /**< Close callback */
	VDM_Comm_notifyCommTermCB notifyCommTerm;           /**< Termination callback */
} VDM_CommObserver_t;

/*!
 * If using HMAC authentication, then an HMAC structure containing an
 * algorithm, username, and MAC is used by some HTTP functions. The
 * algorithm can be left empty to indicate MD5 (the default).
 */
typedef struct {
    char *algorithm;     /**< Optional; if missing, MD5 is assumed */
    char *username;      /**< Identity of the sender of the message */
    char *mac;           /**< Digest values */
} VDM_Comm_HMAC_t;

/*!
 * HTTP Authentication Levels.
 */
typedef enum {
	E_VDM_Comm_HttpAuthLevel_None,  //!< No server authentication (user name and password not needed)
	E_VDM_Comm_HttpAuthLevel_Basic, //!< Basic server authentication (user name and password needed)
	E_VDM_Comm_HttpAuthLevel_Digest //!< Not Supported
} E_VDM_Comm_HttpAuthLevel_t;

/*!
 * When initializing the raw communication component, OMA DM Protocol Engine sends
 * additional parameters, including proxy and User-Agent HTTP header,
 * using this structure.
 */
typedef struct {
	char *proxy;                                /**< Proxy server address; format is: http://{host}[:{port}] */
	const char *userAgent;                         /**< Value of User-Agent HTTP header */
	E_VDM_Comm_HttpAuthLevel_t proxyAuthLevel;  /**< Proxy server authentication level.
	                                                 A value from \ref E_VDM_Comm_HttpAuthLevel_t */
	IU8 *proxyUsernamePassword;              /**< B64 encoded User name and password for proxy authentication */
	IU32 connTimeoutMS;                         /**< Socket connection timeout, in milliseconds, or
	                                                 0 indicating no timeout */
	IBOOL isSslMandatory;                       /**< Whether only secure connections are allowed */
	IBOOL isClientCertMandatory;                /**< Whether client should provide client certificate (HTTPS session) */
	IBOOL isNonStandardDomainSupported;         /**< Whether client certificate must be provided */
} VDM_Comm_ConnParams_t;

/*!
 * When creating the system communication component, the application can send optional parameters
 * using this structure.
 */
typedef struct {
	IU32 param;                                 /**< A placeholder for future use */
} VDM_Comm_SystemParams_t;

/*! @} */

#ifdef __cplusplus
}
#endif

#endif

