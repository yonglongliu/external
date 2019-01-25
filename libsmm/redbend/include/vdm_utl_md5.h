/*
 *******************************************************************************
 *
 * vdm_utl_md5.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_utl_md5.h
 *
 * \brief	MD5 Message Digest Algorithm.
 *
 * RSA Data Security, Inc. MD5 Message-Digest Algorithm
 * Code derived from RFC1321.
 *
 *******************************************************************************
 */

/* Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
 * rights reserved.
 *
 * License to copy and use this software is granted provided that it
 * is identified as the "RSA Data Security, Inc. MD5 Message-Digest
 * Algorithm" in all material mentioning or referencing this software
 * or this function.
 *
 * License is also granted to make and use derivative works provided
 * that such works are identified as "derived from the RSA Data
 * Security, Inc. MD5 Message-Digest Algorithm" in all material
 * mentioning or referencing the derived work.
 *
 * RSA Data Security, Inc. makes no representations concerning either
 * the merchantability of this software or the suitability of this
 * software for any particular purpose. It is provided "as is"
 * without express or implied warranty of any kind.
 *
 * These notices must be retained in any copies of any part of this
 * documentation and/or software.
 */

#ifndef VDM_UTL_MD5_H_
#define VDM_UTL_MD5_H_          //!< Internal

#ifdef __cplusplus
extern "C" {
#endif

#include <vdm_error.h>

/*
 * Define the length for an MD5 hash, and use a typedef for
 * the actual hash data structure.
 */
#define HASHLEN 16
typedef unsigned char HASH[HASHLEN];

/*!
    MD5 context.
 */
typedef struct MD5_CTX_s {
	IU4BY state[4];                                   /*!< state (ABCD) */
	IU4BY count[2];        /*!< number of bits, modulo 2^64 (lsb first) */
	unsigned char buffer[64];                        /*!< input buffer */
} MD5_CTX_t;

/*!
 *******************************************************************************
 * MD5 initialization.
 * Begins an MD5 operation, writing a new context.
 *
 * \param	outContext  Pre-allocated context.
 *
 * \return	VDM_ERR_OK on success, or other error code
 *******************************************************************************
 */
extern VDM_Error VDM_UTL_MD5_init(MD5_CTX_t *outContext);

/*!
 *******************************************************************************
 * MD5 block update operation.
 * Continues an MD5 message-digest operation, processing another message block,
 * and updating the context.
 *
 * \param	inContext   MD5 context.
 * \param	inBlock		Input block.
 * \param	inBlockLen	Length of \a inBlock.
 *
 * \return	VDM_ERR_OK on success, or other error code
 ******************************************************************************
 */
extern VDM_Error VDM_UTL_MD5_update(MD5_CTX_t *inContext,
	const unsigned char *inBlock, IU32 inBlockLen);

/*!
 *******************************************************************************
 * MD5 finalization.
 * Ends an MD5 message-digest operation, writing the message digest and
 * zeroizing the context.
 *
 * \param	outDigest   Message digest.
 * \param	ioContext	In: Valid context.
 *						Out: zeroed context.
 *
 * \return	VDM_ERR_OK on success, or other error code
 ******************************************************************************
 */
extern VDM_Error VDM_UTL_MD5_final(unsigned char outDigest[16], MD5_CTX_t *ioContext);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* !VDM_UTL_MD5_H_ */
