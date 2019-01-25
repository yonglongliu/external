/*
 *******************************************************************************
 *
 * vdm_utl_decode.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_utl_decode.h
 *
 * \brief	Decoding & Encoding API
 *******************************************************************************
 */
#ifndef VDM_UTL_DECODE_H
#define VDM_UTL_DECODE_H

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 *********************************************************************
 * Encode data using Base64.
 *
 * The returned buffer has a NULL-terminator. This is useful if it is
 * necessary to turn the data into a string. The NULL-terminator is
 * NOT included in the returned length.
 *
 * \param	inDecData		The data to encode.
 * \param	inDecLength		Length of inDecData (in bytes).
 * \param	outEncData		A buffer to store the encoded data, or
 *							NULL on error; the caller must free this
 *							buffer.
 * \param	outEncLength	Length of data in outEncData, excluding
 *							NULL-terminator.
 *
 * \return	VDM_ERR_OK on success or a VDM_ERR_defs error code
 *********************************************************************
 */
extern VDM_Error VDM_UTL_b64Encode(const void *inDecData, IU32 inDecLength,
	void **outEncData, IU32 *outEncLength);

/*!
 *********************************************************************
 * Decode Base64 data.
 *
 * \param	inEncData		The encoded data.
 * \param	inEncLength		Length of inEncData.
 * \param	outDecData		A buffer to store the unencoded data;
 *							this can be the same buffer as inEncData.
 * \param	outDecLength	Length of data in outDecData.
 * \param	inDecMaxLength	Size of outDecData.
 *
 * \return	VDM_ERR_OK on success or a VDM_ERR_defs error code
 *********************************************************************
 */

extern VDM_Error VDM_UTL_b64Decode(const void *inEncData, IU32 inEncLength,
	void *outDecData, IU32  *outDecLength, IU32 inDecMaxLength);

/*! Encoding method */
typedef enum {
	E_VDM_ENCODE_HEX, //!< Hex
	E_VDM_ENCODE_BIN64  //!< Bin64
} E_VDM_ENCODE_METHOD_t;

/*!
 *******************************************************************************
 * Decode encoded message.
 *
 * \param	outDecodedMsg		Decoded message<br>
 *								Buffer is allocated and should be freed by the
 *								caller.
 * \param	outDecodedMsgLen	Length of \a outDecodedMsg
 * \param	inMsg				Message to decode
 * \param	inMsgLen			Length of encoded message \a inMsg, in bytes
 * \param	inEncodeMethod		Encoding method, an \ref E_VDM_ENCODE_METHOD_t
 *								value
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_MEMORY if could not allocate decoded message buffer, or
 *			VDM_ERR_BAD_INPUT if could not decode message according to input
 *			encoding method
 *******************************************************************************
 */
extern VDM_Error VDM_UTL_Decode_decodeMsg(IU8 **outDecodedMsg,
	IU32 *outDecodedMsgLen, const char *inMsg, IU32 inMsgLen,
	E_VDM_ENCODE_METHOD_t inEncodeMethod);

/*!
 *********************************************************************
 * Encode a binary message.
 *
 * \param	outEncodedMsg		Buffer to store encoded message; caller
 *								must free buffer.
 * \param	outEncodedMsgLen	Length of outEncodedMsg.
 * \param	inMsg				Message to encode.
 * \param	inMsgLen			Length of inMsg, in bytes.
 * \param	inEncodeMethod		Encoding method, an E_VDM_ENCODE_METHOD_t
 *								value.
 *
 * \return	VDM_ERR_OK on success, VDM_ERR_MEMORY if could not
 *				allocate outEncodedMsg, or VDM_ERR_BAD_INPUT if could not
 *				decode message according to inEncodeMethod
 *********************************************************************
 */

extern VDM_Error VDM_UTL_Decode_encodeMsg(char **outEncodedMsg,
	IU32 *outEncodedMsgLen, const IU8 *inMsg, IU32 inMsgLen,
	E_VDM_ENCODE_METHOD_t inEncodeMethod);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

