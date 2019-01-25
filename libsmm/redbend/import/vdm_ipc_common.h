/*
 *******************************************************************************
 *
 * vdm_ipc_common.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file    vdm_ipc_common.h
 *
 * \brief   Inter Process Communication common functions
 *
 *
 * The SMM Engine runs first and waits for the DIL to connect using IPC.
 * SMM Engine and DIL are peers, client and server to each other.
 *
 * Android doesn't use IPC functions, but uses the package and parse functions
 * (\ref VDM_IPC_genEvent and \ref VDM_IPC_parseEvent).
 *
 *******************************************************************************
 */


#ifndef _VDM_IPC_COMMON_H_
#define _VDM_IPC_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <vdm_smm_types.h>
#include <vdm_error.h>

#define VDM_IPC_MSG_SIZE (sizeof(uint32_t))
#define VDM_SMM_SIGNATURE_MAX_SIZE_BYTES    32

/* fs list is kept as a sparsed int array, first non-zero element is used,
 * when removing fd, it is set to zero, and will be reused next time a new
 * element is added */
#define VDM_IPC_INSTANCE_MAX_FDS 8

#define VDM_IPC_EVENT_COMM_PROTOCOL_TCP 0
#define VDM_IPC_EVENT_COMM_PROTOCOL_UNIX 1
#define VDM_IPC_EVENT_COMM_PROTOCOL_ETHERNET 2

#define VDM_IPC_RAW_SOCK_ERROR_NO_INTERFACE_NAME -2
#define VDM_IPC_RAW_SOCK_ERROR_INTERFACE_NAME_NOT_VALID -3
#define VDM_IPC_RAW_SOCK_ERROR_NO_DEST_ADDR -4

#define VDM_IPC_RAW_SOCK_ERROR_PEER_SHUTDOWN 0
#define VDM_IPC_RAW_SOCK_ERROR_PEER_UNKNOWN -1
///
#define ntohll(x) (((uint64_t)(ntohl((uint32_t)(((x) << 32) >> 32))) << 32) | ntohl(((uint32_t)((x) >> 32))))
#define htonll(x) (((uint64_t)(htonl((uint32_t)(((x) << 32) >> 32))) << 32) | htonl(((uint32_t)((x) >> 32))))


#define IPC_BUFFER_SIZE 1460
#define IPC_MAX_BUFFER_SIZE 10000000 // ~ 10MB
#define MAX_CONN_BACKLOG 3

#define MAX_DIL_EVENT_RETRY 50

#define NUM_OF_BYTES_FOR_EVENT_LEN  VDM_IPC_MSG_SIZE

#ifndef UNIX_PATH_MAX
#define UNIX_PATH_MAX 108
#endif

#if defined (__linux__) && !defined (__ANDROID__) && !defined(VDM_QNX)
#define RAW_PACKETS_PROTOCOL 0x2424
#define ETH_HEADER_LEN 14
#define ETH_MAC_ADDR_LEN 6
#define ETH_FRAME_MAX_SIZE 1024
#endif


/**
 * Evaluate whether to continue processing an event after evaluating the event buffer’s signature.
 * You might continue processing certain events even after a failed signature evaluation.
 *
 * \param   inContext               The context
 * \param   inEvent                 The event
 * \param   inAuthorized        True if the event buffer was authorized, false otherwise
 *
 * \return  0 on success, -1 otherwise
 */
typedef IBOOL (*VDM_IPC_filterEventCB_t)(void *intContext,
    const VDM_SMM_Event_t *inEvent, IBOOL inIsAuthorizeEvent);

/**
 * Callback to calculate signatures for buffer.
 *
 * \param   inContext           The context
 * \param   inAuthBuffer            The buffer
 * \param   inAuthBufferSize    Size of inAuthBuffer
 * \param   outSignature        pre allocated buffer in Max size
 * \param   ioSignatureSize     In: Max size of outSignature. Out: Actual size of outSignature.
 *
 * \return  0 on success, -1 otherwise
 */
typedef int (*VDM_IPC_calculateSignatureCB_t)(void *inContext,
    const unsigned char *inAuthBuffer,
    IU32 inAuthBufferSize,
    char *outSignature,
    IU32 *ioSignatureSize);


typedef struct {
    IU8 sockType;
    IU32 eventFormat;
    int serverfd;
    int stopPipefd[2];
    int fds[VDM_IPC_INSTANCE_MAX_FDS];
#if defined (__linux__) && !defined (__ANDROID__) && !defined(VDM_QNX)
    char *ethInterfaceName;
    IU8 ethDestAddr[6];
#endif
} VDM_IPC_Instance_t;

/**
 * Parse received event from IPC channel.
 * Deprecated. Use VDM_IPC_parseSmmEvent instead.
 * This function parses only events in SMM format  - for backwards compatibility.
 *
 * An event is packaged before sending by \ref ipc_getEvent.
 *
 * \param   readArray       A packaged event
 *
 * \return  The unpackaged event
 */
VDM_SMM_Event_t *VDM_IPC_parseEvent(unsigned char *readArray);

/**
 * Parse received event from IPC channel.
 * This function parses only events in SMM format
 *
 * An event is packaged before sending by \ref ipc_getEvent.
 *
 * \param   readArray       A packaged event
 *
 * \return  The unpackaged event
 */
VDM_SMM_Event_t *VDM_IPC_parseSmmEvent(unsigned char *readArray);

/**
 * Parse received ASM event from IPC channel.
 * This function parses only events in ASM format
 *
 * An event is packaged before sending by \ref ipc_getEvent.
 *
 * \param   readArray       A packaged event
 *
 * \return  The unpackaged event
 */
VDM_SMM_Event_t *VDM_IPC_parseAsmEvent(unsigned char *readArray);

/**
 * Package an event for sending over IPC channel.
 * Deprecated. Use VDM_IPC_genSmmEvent instead.
 *
 * The event is unpackaged on the other side by \ref ipc_parseEvent.
 * This function generates only events in SMM format - for backwards compatibility.
 *
 * \param   event       The event
 * \param   outWriteArray  The packaged event
 * \param   arraySize   Size of \a outWriteArray
 *
 * \return  The size of the package; if the size is greater than \a arraySize,
 *          this is the required size, and the packaging was unsuccessful
 */
IU32 VDM_IPC_genEvent(VDM_SMM_Event_t *event, unsigned char *outWriteArray,
    IU32 arraySize);

/**
 * Package an event for sending over IPC channel.
 *
 * The event is unpackaged on the other side by \ref ipc_parseEvent.
 * This function generates only events in SMM format
 *
 * \param   event       The event
 * \param   outWriteArray  The packaged event
 * \param   arraySize   Size of \a outWriteArray
 *
 * \return  The size of the package; if the size is greater than \a arraySize,
 *          this is the required size, and the packaging was unsuccessful
 */
IU32 VDM_IPC_genSmmEvent(VDM_SMM_Event_t *event, unsigned char *outWriteArray,
    IU32 arraySize);

/**
 * Package an ASM event for sending over IPC channel.
 *
 * The event is unpackaged on the other side by \ref ipc_parseAsmEvent.
 * This function generates only events in ASM format
 *
 * \param   event       The ASM event
 * \param   outWriteArray  The packaged event
 * \param   arraySize   Size of \a outWriteArray
 *
 * \return  The size of the package; if the size is greater than \a arraySize,
 *          this is the required size, and the packaging was unsuccessful
 */
IU32 VDM_IPC_genAsmEvent(VDM_SMM_Event_t *event, unsigned char *outWriteArray,
    IU32 arraySize);

/**
 * Create authentication context.
 *
 * \param   inContext       The context info
 *
 * \return  None
 */
void VDM_IPC_createAuthenticationContext(void *inContext);


/**
 * Register  callback function for calculating signature
 *
 * \param   inCb            The callback.
 *
 * None
 */
void VDM_IPC_registerSignatureCalcFunc(VDM_IPC_calculateSignatureCB_t inCb);


/**
 * register callback function for events filter.
 *
 * \param   inCb            The callback.
 *
 * None
 */
void VDM_IPC_registerEventFilterFunc(VDM_IPC_filterEventCB_t inCb);


/**
 * Get the event name for the specified event id
 *
 * \param   inId            In ID number.
 * \param 	eventName		Name of the event
 *
 * \return VDM_ERR_OK on success or error code
 */
VDM_Error VDM_SMM_getEventNameById(const IU32 inId, char **eventName);


/**
 * Get the var name for the specified var id
 *
 * \param   inId            In ID number.
 * \param 	varName			Name of the variable
 *
 * \return VDM_ERR_OK on success or error code
 */
VDM_Error VDM_SMM_getVarNameById(const IU32 inId, char **varName);


/**
 * Get the event id for the specified event name
 *
 * \param   inEventName		In event name.
 * \param 	outId			Event ID
 *
 * \return VDM_ERR_OK on success or error code
 */
VDM_Error VDM_SMM_getEventIdByName(const char *inEventName, IU32 *outId);


/**
 * Get the var id for the specified var name
 *
 * \param   inVarName		In var name.
 * \param 	outId			Event ID
 *
 * \return VDM_ERR_OK on success or error code
 */
VDM_Error VDM_SMM_getVarIdByName(const char *inVarName, IU32 *outId, IU32 inEventId);


/**
 * Get the var type for the specified id
 *
 * \param   inVarId				In var ID.
 * \param 	outVarType			Type of var
 *
 * \return VDM_ERR_OK on success or error code
 */
VDM_Error VDM_SMM_getVarTypeById(IU32 inVarId, IU32 *outVarType);


#ifdef  __cplusplus
}
#endif

#endif
