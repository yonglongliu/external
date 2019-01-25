/*
 *******************************************************************************
 *
 * vdm_comm_pl_conn.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_comm_pl_conn.h
 *
 * \brief	Raw Connection API
 *
 * This API provides a means for the Engine to manage raw data connections.
 * Typically you implement this using sockets.
 *
 * OMA DM Protocol Engine uses event-driven communication, and supports both
 * synchronous and asynchronous communication. Whenever the Engine initiates a
 * communication operation, such as opening or closing a connection, or sending
 * or receiving data, it does not assume that the operation is complete
 * immediately when the function returns. Instead, the Engine waits for
 * notification of completion via a communication observer.
 *
 * The Porting Layer functions call the Comm Observer callback functions to
 * notify the Engine of a communication event (such as opened, received,
 * or broken).
 *
 * The Comm Observer monitors the networking communication components. The open,
 * send, and receive functions must notify the Comm Observer on success or
 * failure; the Comm Observer then notifies the Engine of the communication
 * event.
 *
 * The Comm Observer is a structure of callback pointers created by the OMA DM
 * Protocol Engine Framework and passed to the communication component upon
 * initialization. The initialization function must make the structure available
 * to the open, send, and receive APIs. The implementation of each of these APIs
 * should invoke the corresponding notification callback, as required.
 *******************************************************************************
 */
#ifndef _VDM_COMM_PL_CONN_H_
#define _VDM_COMM_PL_CONN_H_

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
 * Initialize the raw data connection.
 *
 * When initializing the raw communication, OMA DM Protocol Engine sends
 * additional parameters, including proxy and User-Agent HTTP header,
 * using \ref VDM_Comm_ConnParams_t.
 *
 * The Engine initializes the raw data communication before opening a
 * connection. The Engine caches the context returned and passes it to all
 * other raw data communication APIs.
 *
 * After initializing the raw communication, the API must notify the
 * Comm Observer using the "Comm Initialized" notification.
 *
 * \note	This function must make the Comm Observer structure available to
 *			all other raw data communication APIs, for example via the
 *			\a outContext parameter that is passed to all other raw data
 *			communication APIs.
 *
 * \param	outContext	The raw connection context.
 * \param	inObserver	The Comm Observer structure.
 * \param	inParams	Structure containing optional parameters.
 *                      See \ref VDM_Comm_ConnParams_t.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_Comm_PL_Conn_init(
	void **outContext,
	VDM_CommObserver_t *inObserver,
	VDM_Comm_ConnParams_t *inParams);

/*!
 *******************************************************************************
 * Open a raw data connection.
 *
 * After attempting to open a raw data connection, the API must notify the
 * Comm Observer using the "Comm Opened" notification or the "Comm Broken"
 * notification.
 *
 * \param	inContext	The context set by \ref VDM_Comm_PL_Conn_init.
 * \param	outConnId	A connection id.
 * \param	inURL		The URL to open.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_Comm_PL_Conn_open(
	void *inContext,
	IS32 *outConnId,
	const char *inURL);

/*!
 *******************************************************************************
 * Send a request using a raw connection.
 *
 * For a raw data connection, you simply open a TCP socket and write or read
 * data from the socket. You can use secure sockets, if desired.
 *
 * \param	inContext		The context set by \ref VDM_Comm_PL_Conn_init.
 * \param	inConnId		The connection id returned by
 *							\ref VDM_Comm_PL_Conn_open.
 * \param	inData			Pointer to the data to be sent.
 * \param	inDataLength	The length of \a inData, in bytes.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_Comm_PL_Conn_send(
	void *inContext,
	IS32 inConnId,
	IU8 *inData,
	IU32 inDataLength);

/*!
 *******************************************************************************
 * Read the content of the server's reply into a pre-allocated buffer of the
 * indicated length. This function can be called multiple times until all the
 * content has been read.
 *
 * After receiving data over a raw data connection, the API must notify the
 * Comm Observer using the "Comm Transport" notification or the "Comm Broken"
 * notification.
 *
 * \param	inContext	The context set by \ref VDM_Comm_PL_Conn_init.
 * \param	inConnId	The connection id returned by
 *						\ref VDM_Comm_PL_Conn_open.
 * \param	outBuf		Pointer to a pre-allocated buffer to receive the
 *						incoming data.
 * \param	inBufSize	Size of the \a outBuf, in bytes.
 * \param	outDataLen	The actual length of the data read. Set to -1
 *						if there is no more data.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_Comm_PL_Conn_receive(
	void *inContext,
	IS32 inConnId,
	IU8 *outBuf,
	IU32 inBufSize,
	IS32 *outDataLen);

/*!
 *******************************************************************************
 * Terminate any current message or response and close an open raw data
 * connection.
 *
 * After closing the raw data connection, the API must notify the
 * Comm Observer using the "Comm Closed" notification.
 *
 * \param	inContext	The context set by \ref VDM_Comm_PL_Conn_init.
 * \param	inConnId	The connection id returned by
 *						\ref VDM_Comm_PL_Conn_open.
 *
 * \return None
 *******************************************************************************
 */
extern void VDM_Comm_PL_Conn_close(
	void *inContext,
	IS32 inConnId);

/*!
 *******************************************************************************
 * Terminate the raw data communication and free any resources in use.
 *
 * After terminating the raw data connection, the API must notify the
 * Comm Observer using the "Comm Terminated" notification.
 *
 * \param	inContext	Connection context.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_Comm_PL_Conn_term(void *inContext);

/*! @} */

#ifdef __cplusplus
}
#endif

#endif

