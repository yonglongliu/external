/*
 *******************************************************************************
 *
 * vdm_ipc_server.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_ipc_server.h
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


#ifndef _VDM_IPC_SERVER_H_
#define _VDM_IPC_SERVER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <vdm_error.h>
#include <vdm_ipc_common.h>

#define VDM_IPC_EVENT_COMM_PROTOCOL_TCP_WEBSOCKET 3

/**
 * Waits for a server destined traffic to be available
 *
 * \param	ipc				The handler to the IPC instance
 *
 * \return	non-zero on success
 */
int VDM_IPC_serverSelect(VDM_IPC_Instance_t *ipc);

/**
 * Get an event from the server IPC channel.
 *
 * \param	ipc				The handler to the IPC instance
 * \param	event			The event
 * \param	non_blocking	Non-zero if a blocking socket, 0 otherwise
 *
 * \return	0 on success, 1 on a parser error, or an error message
 */
int VDM_IPC_serverReadEvent(VDM_IPC_Instance_t *ipc, VDM_SMM_Event_t **event,
	int non_blocking);

/**
 * Sends a "wake-up" byte to pipe that's included in the select waiting for
 * incoming events, will cause the blocking read to interrupt.
 * Returns zero on success, -errno on error case
 *
 * \param	ipc				The handler to the IPC instance
 *
 * \return	0 on success, or an negative number signing an error
 */
int VDM_IPC_serverStopRead(VDM_IPC_Instance_t *ipc);

/**
 * Send UI event over server IPC channel.
 *
 * \param	ipc			The handler to the IPC instance
 * \param	event		The event
 *
 * \return	1 on success, 0 if the transmitted event buffer allocation failed,
 * or an error number
 */
int VDM_IPC_serverPostUiEvent(VDM_IPC_Instance_t *ipc, VDM_SMM_Event_t *event);

/**
 * Start TCP IPC server.
 *
 * \deprecated	Use \ref VDM_IPC_initTcpServerEx
 *
 * \param	addr			The IPC server address
 * \param	port			The IPC server port
 *
 * \return	The handler to the IPC instance or NULL in the case of an error
 */
VDM_IPC_Instance_t *VDM_IPC_initTcpServer(const char *addr, int port);

/**
 * Start TCP IPC server.
 *
 * \param	addr			The IPC server address
 * \param	port			The IPC server port
 * \param	eventFormat		The format of the events that will be sent over this IPC
 *
 * \return	The handler to the IPC instance or NULL in the case of an error
 */
VDM_IPC_Instance_t *VDM_IPC_initTcpServerEx(const char *addr, int port,
		IU32 eventFormat);

/**
 * Start UNIX IPC server.
 *
 * * \deprecated	Use \ref VDM_IPC_initUnixServerEx
 *
 * \param	file			The file socket the server is bind to
 *
 * \return	The handler to the IPC instance or NULL in the case of an error
 */
VDM_IPC_Instance_t *VDM_IPC_initUnixServer(const char *file);

/**
 * Start UNIX IPC server.
 *
 * \param	file			The file socket the server is bind to
 * \param	eventFormat		The format of the events that will be sent over this IPC
 *
 * \return	The handler to the IPC instance or NULL in the case of an error
 */
VDM_IPC_Instance_t *VDM_IPC_initUnixServerEx(const char *file, IU32 eventFormat);

/**
 * Returns the number of connected clients over server IPC channel.
 *
 * \param	ipc				The handler to the IPC instance
 *
 * \return	Number of clients connected
 */
int VDM_IPC_getNumberOfClients(VDM_IPC_Instance_t *ipc);

/**
 * Terminate IPC server.
 *
 * \param	ipc				The handler to the IPC instance
 *
 * \return	None
 */
void VDM_IPC_termServer(VDM_IPC_Instance_t *ipc);


#if defined (__linux__) && !defined (__ANDROID__) && !defined(VDM_QNX)
/**
 * Start Ethernet IPC server.
 *
 * \param	inInterfaceName		The interface name used for Ethernet connection
 * \param	inDestAddr			The destination address to send the events over the given interface
 * \param	eventFormat			The format of the events that will be sent over this IPC
 *
 * \return	The handler to the IPC instance or NULL in the case of an error
 */
VDM_IPC_Instance_t *VDM_IPC_initEthernetServer(char *inInterfaceName,
		const char *inDestAddr, IU32 inEventFormat);

#endif



#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 

