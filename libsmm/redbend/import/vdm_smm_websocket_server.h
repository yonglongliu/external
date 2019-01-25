/*
 *******************************************************************************
 *
 * vdm_smm_websocket_server.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file vdm_smm_websocket_server.h
 *
 * \brief Web socket manager
 *
 * Managing the SMM executable socket/web socket: open/close/read/write.
 * Using web socket for communicating with HTML5 client.
 *******************************************************************************
 */
#ifndef _VDM_SMM_WEBSOCKET_SERVER_H_
#define _VDM_SMM_WEBSOCKET_SERVER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "vdm_pl_types.h"

typedef struct VDM_SMM_WebSock_Instance VDM_SMM_WebSock_Instance_t;
#define VDM_SMM_WEBSOCK_NO_CLIENT 0xffff

/*
 * Terminates and free a web socket instance.
 *
 * \param            inInstance           Web socket instance
 *
 * \return             None
 */
void VDM_SMM_WebSock_termServer(VDM_SMM_WebSock_Instance_t **inInstance);

/*
 * Initiates a web socket instance.
 *
 * \param            inAddr           IP address of web socket
 * \param            inPort           Port of web socket
 *
 * \return             Web socket instance, a \ref VDM_SMM_WebSock_Instance_t value
 */
VDM_SMM_WebSock_Instance_t *VDM_SMM_WebSock_initServer(const char *inAddr, IU16 inPort);

/*
 * Wait for communication from a client in the client queue.
 *
 * \param            inInstance       Web socket instance
 * \param            inTimeoutMs      Time to wait, in ms
 *
 * \return           returns the client fd
 */
int VDM_SMM_WebSock_waitForClient(VDM_SMM_WebSock_Instance_t *inInstance, IS32 inTimeoutMs);

/*
 * Receive information from client
 *
 * \param            inInstance           Web socket instance
 * \param            inClient Client		 index of the client in client queue
 * \param            outBuf               Received data
 * \param            inSize               Size of \a outBuf, in bytes
 *
 * \return           Size of data in \a outBuf, in bytes
 */
IS32 VDM_SMM_WebSock_read(VDM_SMM_WebSock_Instance_t *inInstance, IS32 inClient, IU8 *outBuf, IS32 inSize);

/*
 * Broadcast received information to all queued clients.
 *
 * \param            inInstance           Web Socket instance
 * \param            inData               Data to broadcast
 * \param            inSize               Size of \a inData, in bytes
 * \param            inIsText            TRUE if text data, FALSE if binary data
 *
 * \return           0 on success (if data was sent to all clients), index of problematic client on failure
 */
IS32 VDM_SMM_WebSock_writeToAll(VDM_SMM_WebSock_Instance_t *inInstance,
	const IU8 *inData, IS32 inSize, IS32 inIsText);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // _VDM_SMM_WEBSOCKET_SERVER_H_
