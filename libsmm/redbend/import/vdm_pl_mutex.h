/*
 *******************************************************************************
 *
 * vdm_pl_mutex.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_pl_mutex.h
 *
 * \brief	OS Mutex APIs
 *
 * A mutex is a synchronization object that is used by threads to control access
 * to a shared resource. A mutex can be locked to indicate a resource is in use.
 * Other threads can then block on the mutex to wait for the resource.
 *
 * "Mutex" is short for "mutual exclusion".
 *
 * \note	When using a single thread, these functions can be left empty.
 *			However, an empty \ref VDM_PL_Mutex_create should not return NULL,
 *			as this is interpreted as an error.
 *******************************************************************************
 */
#ifndef VDM_PL_MUTEX_H
#define VDM_PL_MUTEX_H

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @addtogroup pl_system
 * @{
 */

/*!
 *******************************************************************************
 * Create and open a mutex.
 *
 * \note	If you leave this implementation empty, do not return NULL, as this
 *			is interpreted as an error.
 *
 * \return	Handle to the mutex
 *******************************************************************************
 */
VDM_Handle_t    VDM_PL_Mutex_create(void);

/*!
 *******************************************************************************
 * Lock a mutex.
 *
 * \param	inMutex		Mutex handle to lock
 *
 * \return	None
 *******************************************************************************
 */
void    VDM_PL_Mutex_lock(VDM_Handle_t inMutex);

/*!
 *******************************************************************************
 * Unlock a mutex.
 *
 * \param	inMutex		Mutex handle to unlock
 *
 * \return	None
 *******************************************************************************
 */
void    VDM_PL_Mutex_unlock(VDM_Handle_t inMutex);

/*!
 *******************************************************************************
 * Close a mutex.
 *
 * \param	inMutex		Mutex handle to close
 *
 * \return	None
 *******************************************************************************
 */
void    VDM_PL_Mutex_close(VDM_Handle_t inMutex);

/*! @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

