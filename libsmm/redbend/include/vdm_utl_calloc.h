/*
 *******************************************************************************
 *
 * vdm_utl_calloc.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_utl_calloc.h
 *
 * \brief	Calloc Utility API
 *******************************************************************************
 */

#ifndef VDM_UTL_CALLOC_H
#define VDM_UTL_CALLOC_H

#include <vdm_pl_alloc.h>

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 *******************************************************************************
 * Allocate a memory buffer and set all bytes in the buffer to 0.
 *
 * \param	inSize	Size of memory buffer to allocate, in bytes.
 *
 * \return	Pointer to memory buffer allocated, or NULL on error
 *******************************************************************************
 */
void *VDM_UTL_calloc(IU32 inSize);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

