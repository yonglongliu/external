/*
 *******************************************************************************
 *
 * vdm_utl_human_readable.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_utl_human_readable.h
 *
 * \brief	convert size integer to human readable format
 *******************************************************************************
 */

#ifndef _VDM_UTL_HUMAN_READABLE_H_
#define _VDM_UTL_HUMAN_READABLE_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 *******************************************************************************
 * Convert number that represent files sizes to human readable format.
 *
 * \param	inNum	number to convert.
 *
 * \return	Pointer to memory buffer allocated, or NULL on error
 *******************************************************************************
 */
char *VDM_UTL_intToHumanReadableDup(IU64 inNum);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

