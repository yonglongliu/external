/*
 *******************************************************************************
 *
 * vdm_utl_error.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_utl_error.h
 *
 * \brief	Error handling APIs
 *******************************************************************************
 */
#ifndef VDM_UTL_ERROR_H
#define VDM_UTL_ERROR_H

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 *******************************************************************************
 * Get whether a Comm error was fatal or non-fatal.
 *
 * \param	inError		The error
 *
 * \return	TRUE if the error is fatal, FALSE if the error is non-fatal
 *******************************************************************************
 */
extern IBOOL VDM_UTL_ERR_isCommsErrorNonFatal(VDM_Error inError);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

