/*
 *******************************************************************************
 *
 * vdm_pl_memory.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_pl_memory.h
 *
 * \brief	Memory Management APIs
 *******************************************************************************
 */
#ifndef VDM_PL_MEMORY_H__
#define VDM_PL_MEMORY_H__

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @addtogroup pl_system
 * @{
 */

/*!
 *******************************************************************************
 * Compare two buffers of bytes.
 *
 * \param	inBuf1		The first memory buffer
 * \param	inBuf2		The second memory buffer
 * \param	inLen		Number of bytes to compare
 *
 * \return	< 0 if \a inBuf1 < \a inBuf2,
 *            0 if \a inBuf1 == \a inBuf2, or
 *          > 0 if \a inBuf1 > \a inBuf2
 *******************************************************************************
 */
extern IS32 VDM_PL_memcmp(const void *inBuf1, const void *inBuf2, IU32 inLen);

/*!
 *******************************************************************************
 * Copy bytes from one place to another. The source and destination bytes
 * must not overlap.
 *
 * \param	outDest		Destination pointer
 * \param	inSrc		Source pointer
 * \param	inLen		Number of bytes to copy
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_PL_memcpy(void *outDest, const void *inSrc, IU32 inLen);

/*!
 *******************************************************************************
 * Copy bytes from one place to another. The source and destination bytes
 * may overlap.
 *
 * \param	outDest		Destination pointer
 * \param	inSrc		Source pointer
 * \param	inLen		Number of bytes to copy
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_PL_memmove(void *outDest, const void *inSrc, IU32 inLen);

/*!
 *******************************************************************************
 * Set a byte sequence to a common value.
 *
 * \param	outDest		Pointer to first byte in memory to be set
 * \param	inVal		Value to which bytes will be set
 * \param	inLen		Number of bytes to set
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_PL_memset(void *outDest, IU8 inVal, IU32 inLen);

/*! @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

