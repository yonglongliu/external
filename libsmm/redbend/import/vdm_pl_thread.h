/*
 *******************************************************************************
 *
 * vdm_pl_thread.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_pl_thread.h
 *
 * \brief	Thread API
 *
 * See the notes in the functions regarding single-threaded applications.
 *******************************************************************************
 */
#ifndef VDM_PL_THREAD_H
#define VDM_PL_THREAD_H             //!< Internal

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @addtogroup pl_system
 * @{
 */

#define VDM_PL_INVALIDTHREADID  0xFFFFFFFF  //!< Invalid thread id

/*!
 *******************************************************************************
 * Get current thread Id.
 *
 * In single-threaded environments, return \ref VDM_PL_INVALIDTHREADID.
 *
 * \return	Current thread id on success, \ref VDM_PL_INVALIDTHREADID on failure
 *			or a single-threaded environment
 *******************************************************************************
 */
extern IU32 VDM_PL_getCurrentThreadId(void);

/*! @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

