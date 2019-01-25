/*
 *******************************************************************************
 *
 * vdm_ipc_client.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_ipc_client.h
 *
 * \brief	Inter Process Communication
 *
 * The SMM Engine runs first and waits for the DIL to connect using IPC.
 * SMM Engine and DIL are peers, client and server to each other.
 *
 * Android doesn't use IPC functions, but uses the package and parse functions
 * (\ref VDM_IPC_genEvent and \ref VDM_IPC_parseEvent).
 *******************************************************************************
 */

#ifndef _VDM_IPC_H_
#define _VDM_IPC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <vdm_ipc_common.h>

/**
 * Get an UI event from client IPC channel.
 *
 * \param	sockfd			The socket id
 * \param	event			The event -- The event is allocated inside the func
 * \param	non_blocking	Non-zero if a blocking socket, 0 otherwise
 * \param	writeToLogFunc	Log function
 *
 * \return	0 on connection closing or parser error, 1 on successfully returned event,
 *              2 in non_blocking case, when there's nothing to read, negative value on error
 */
int VDM_IPC_clientReadUiEvent(int sockfd, VDM_SMM_Event_t **event, int non_blocking, void (*writeToLogFunc)(const char *format, ...));

/**
 * Send a client event over IPC channel.
 *
 * \param	sockfd		The socket id
 * \param	event		The event
 *
 * \return	1 on success, 0 if the transmitted event buffer allocation failed,
 * or an error number
 */
int VDM_IPC_clientPostEvent(int sockfd, VDM_SMM_Event_t *event);


int VDM_IPC_initTcpClient(const char *addr, int port);

/**
 * Start UNIX IPC client.
 *
 * \param	file			The file socket client will connect
 * \param	port			The IPC server port
 * \param	eventFormat		The format of the events that will be sent over this IPC
 *
 * \return	The socket id, or an error number
 */
int VDM_IPC_initTcpClientEx(const char *addr, int port, IU32 eventFormat);

/**
 * Start UNIX IPC client.
 *
 * \deprecated	Use \ref VDM_IPC_initUnixClientEx
 *
 * \param	file			The file socket client will connect
 *
 * \return	The socket id, or an error number
 */
int VDM_IPC_initUnixClient(const char *file);

/**
 * Start UNIX IPC client.
 *
 * \param	file			The file socket client will connect
 * \param	eventFormat		The format of the events that will be sent over this IPC
 *
 * \return	The socket id, or an error number
 */
int VDM_IPC_initUnixClientEx(const char *file, IU32 eventFormat);

/**
 * Terminate IPC client.
 *
 * \param	sockfd		The socket to the server
 *
 * \return	None
 */
void VDM_IPC_termClient(int sockfd);


#if defined (__linux__) && !defined (__ANDROID__) && !defined(VDM_QNX)
/**
 * Start Ethernet IPC client.
 *
 * \param	inInterfaceName		The interface name used for Ethernet connection
 * \param	inDestAddr			The destination address to send the events over the given interface
 * \param	eventFormat			The format of the events that will be sent over this IPC
 *
 * \return	The socket id, or an error number
 */
int VDM_IPC_initEthernetClient(char *inInterfaceName,
		const char *inDestAddr, IU32 eventFormat);

#endif



#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _VDM_IPC_H_ */

