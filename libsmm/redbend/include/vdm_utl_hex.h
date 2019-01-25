/*
 *******************************************************************************
 *
 * vdm_utl_hex.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_utl_hex.h
 *
 * \brief	Hex Encoding and Decoding API
 *******************************************************************************
 */

#ifndef _VDM_UTL_HEX_H
#define _VDM_UTL_HEX_H

#ifdef __cplusplus
extern "C" {
#endif

/** Array of hex digits */
extern const char CONST_hexDigits[];

/*!
 *******************************************************************************
 * Encode binary data to hexadecimal character representation.
 *
 * \param	inBinPtr	Pointer to binary data (input)
 * \param	ioHexPtr	Pointer to hex data (output)<br>
 *					    The output length is (\a length * 2) characters.
 * \param	inLength	Length of \a binPtr, in bytes
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_BAD_INPUT
 *******************************************************************************
 */
extern VDM_Error VDM_UTL_hexEncode(const IU8 *inBinPtr, char *ioHexPtr, IU32 inLength);

/*!
 *******************************************************************************
 * Decode hexadecimal string to binary data.
 *
 * There must be an even number of characters.
 *
 * \param	inHexPtr	Pointer to hex data (input)
 * \param	ioBinPtr	Pointer to binary data (output)<br>
 *					    The output length is (\a length / 2) bytes
 * \param	inLength	Length of \a hexPtr, in characters
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_UTL_hexDecode(const char *inHexPtr, IU8 *ioBinPtr, IU32 inLength);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _VDM_UTL_HEX_H */
