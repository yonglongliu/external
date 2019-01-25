/*
 *******************************************************************************
 *
 * vdm_smm_websocket.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file vdm_smm_websocket.h
 *
 * \brief Web socket protocol implementation
 *******************************************************************************
 */
#ifndef _VDM_SMM_WEBSOCKET_H_
#define _VDM_SMM_WEBSOCKET_H_

#include <vdm_pl_types.h>

typedef enum {
	E_VDM_SMM_WebSock_FrameType_ERROR = 0xF1,
	E_VDM_SMM_WebSock_FrameType_TOO_LARGE = 0xF2,
	E_VDM_SMM_WebSock_FrameType_INCOMPLETE = 0xF3,

	E_VDM_SMM_WebSock_FrameType_CONTINUATION = 0x00, // not supported
	E_VDM_SMM_WebSock_FrameType_TEXT = 0x01,
	E_VDM_SMM_WebSock_FrameType_BINARY = 0x02,
	E_VDM_SMM_WebSock_FrameType_PING = 0x09,
	E_VDM_SMM_WebSock_FrameType_PONG = 0x0A,

	E_VDM_SMM_WebSock_FrameType_CLOSING = 0x08,
	E_VDM_SMM_WebSock_FrameType_OPENING = 0x0F7,
} E_VDM_SMM_WebSock_FrameType_t;

#define VDM_SMM_WEBSOCK_SEC_KEY_LEN 24
#define VDM_SMM_WEBSOCK_MAX_FRAME_HEADER_LEN 10

#ifdef __cplusplus
extern "C" {
#endif
#define VDM_SMM_WEBSOCK_SECRET_LEN 36

typedef int (*VDM_SMM_WebSock_parseHandshakeCb)(void *cbParam, const char *field, IS32 fieldLen, const char *val, IS32 valLen);

/*
 * Parse a web socket handshake buffer and get if it is legal. Also get the
 * client key.
 *
 * \param            inData              Handshake buffer
 * \param            outKey              The client key
 * \param            inCb                Callback to parse the handshake
 * \param            inCbParam           Parameters to pass to \a inCb
 *
 * \return             Handshake buffer status, an \ref E_VDM_SMM_WebSock_FrameType_t value
 */
E_VDM_SMM_WebSock_FrameType_t VDM_SMM_WebSock_parseHandshake(const IU8 *inData, IU8 outKey[VDM_SMM_WEBSOCK_SEC_KEY_LEN],
	VDM_SMM_WebSock_parseHandshakeCb inCb, void *inCbParam);

/*
 * Generate a handshake buffer in response to the client.
 *
 * \param            inKey               Server key length
 * \param            outBuf              Handshake buffer, including server key
 * \param            inBufLen            Size of \outBuf, in bytes
 *
 * \return           Size of data in \a outBuf, in bytes,  on success, or a negative value on failure
 */
int VDM_SMM_WebSock_makeHandshakeAnswer(IU8 inKey[VDM_SMM_WEBSOCK_SEC_KEY_LEN], IU8 *outBuf, IS32 inBufLen);

/*
 * Generate a web socket frame header.
 *
 * \param            inPayloadLen       Length of communication payload data
 * \param            outBuf             Web socket frame header
 * \param            inFrameType        Web socket frame type
 *
 * \return           Size of \a outBuf, in bytes
 */
int VDM_SMM_WebSock_makeFrameHeader(IS32 inPayloadLen, IU8 outBuf[VDM_SMM_WEBSOCK_MAX_FRAME_HEADER_LEN],
	E_VDM_SMM_WebSock_FrameType_t inFrameType);

/*
 * Parse the web socket frame header and get the header length,
 * payload length, and mask.
 *
 * \param            inData             Web socket frame header
 * \param            inDataLen          Size of \a inData, in bytes
 * \param            outHeaderLen       Header length, in bytes
 * \param            outPayloadLen      Payload length, in bytes
 * \param            outMask            Mask
 *
 * \return             Web socket frame header status, an \ref E_VDM_SMM_WebSock_FrameType_t value
 */
E_VDM_SMM_WebSock_FrameType_t VDM_SMM_WebSock_parseFrameHeader(const IU8 *inData, IS32 inDataLen, IS32 *outHeaderLen,
	IS32 *outPayloadLen, IU8 outMask[4]);

/*
 * Serialize the payload.
 *
 * \param            ioPayload          Input: A payload; Output: Unmasked payload
 * \param            inPayLoadOffset    Offset of payload in the web socket frame header
 * \param            inPayloadLen       Len of \a ioPayload input, in bytes
 * \param            inMask             Mask
 *
 * \return             None
 */
void VDM_SMM_WebSock_unmaskFramePayload(IU8 *ioPayload, IS32 inPayLoadOffset,
	IS32 inPayloadLen, IU8 inMask[4]);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /* _VDM_SMM_WEBSOCKET_H_ */
