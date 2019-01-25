/*
 *******************************************************************************
 *
 * vdm_utl_bitarray.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_utl_bitarray.h
 *
 * \brief  Bit operation Utility
 *******************************************************************************
 */

#ifndef VDM_UTL_BITARRAY_H_
#define VDM_UTL_BITARRAY_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <vdm_pl_types.h>


/*!
 *******************************************************************************
 * Get value of specified bit in bitarray
 *
 * \param	inBitArray	the number to check
 * \param	inBitShift	bit number
 *
 * \return	the value of the bit
 *******************************************************************************
 */
extern IBOOL VDM_UTL_isBitOn(IU32 inBitArray, IU32 inBitShift);

/*!
 *******************************************************************************
 * Set specified bit in given bitarray to one
 *
 * \param	inBitArray	bitarray to be modified
 * \param	inBitShift	bit number to turn on
 *
 * \return	modified bitarray
 *******************************************************************************
 */
extern void VDM_UTL_setBitOn(IU32 *inBitArray, IU32 inBitShift);

/*!
 *******************************************************************************
 * Set specified bit in given bitarray to zero
 *
 * \param	inBitArray	bitarray to be modified
 * \param	inBitShift	bit number to turn off
 *
 * \return	modified bitarray
 *******************************************************************************
 */
extern void VDM_UTL_setBitOff(IU32 *inBitArray, IU32 inBitShift);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* VDM_UTL_BITARRAY_H_ */
