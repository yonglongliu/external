/*
 *******************************************************************************
 *
 * vdm_utl_sha1.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*! \internal
 * \file
 *		This is the header file for code which implements the Secure
 *		Hashing Algorithm 1 as defined in FIPS PUB 180-1 published
 *		April 17, 1995.
 *
 * \brief	SHA-1
 */

#ifndef _UTL_SHA1_H_
#define _UTL_SHA1_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <vdm_pl_types.h>

#define VDM_UTL_SHA1_DIGESTSIZE 20
#define VDM_UTL_SHA1_BLOCKSIZE 64

/*
 *	This structure will hold context information for the SHA-1
 *	hashing operation
 */
typedef struct VDM_UTL_SHA1_ctx_t {
	IU4BY Intermediate_Hash[VDM_UTL_SHA1_DIGESTSIZE / 4]; /* Message Digest */
	IU32 Length_Low;                    /* Message length in bits */
	IU32 Length_High;                   /* Message length in bits */
	IS16 Message_Block_Index;       /* Index into message block array */
	IU8 Message_Block[VDM_UTL_SHA1_BLOCKSIZE];  /* 512-bit message blocks */
} VDM_UTL_SHA1_ctx_t;

/*
 *	Function Prototypes
 */
void VDM_UTL_SHA1_init(VDM_UTL_SHA1_ctx_t *);
void VDM_UTL_SHA1_update(VDM_UTL_SHA1_ctx_t *, const IU8 *, unsigned int);
void VDM_UTL_SHA1_final(IU8 [VDM_UTL_SHA1_DIGESTSIZE], VDM_UTL_SHA1_ctx_t *);
void VDM_UTL_SHA1_hmac(const IU8 *inKey, IU32 inKeyLen, const IU8 *inData,
	IU32 inDataLen, IU8 outBuf[VDM_UTL_SHA1_DIGESTSIZE]);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _UTL_SHA1_H_ */

