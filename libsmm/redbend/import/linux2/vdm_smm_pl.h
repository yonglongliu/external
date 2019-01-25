/*
 *******************************************************************************
 *
 * vdm_smm_pl.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_smm_pl.h
 *
 * \brief	SMM Porting Layer API
 *******************************************************************************
 */

#ifndef _VDM_SMM_PL_H_
#define _VDM_SMM_PL_H_

#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 * Create a thread lock.
 *
 * @param	inName	Lock name
 *
 * @return	Lock handle
 *******************************************************************************
 */
void *VDM_SMM_PL_createLock(const char *inName);

/**
 *******************************************************************************
 * Destroy a thread lock.
 *
 * @param	inHandle	Lock handle
 *******************************************************************************
 */
void VDM_SMM_PL_destroyLock(void *inHandle);

/**
 *******************************************************************************
 * Lock the current thread. Used to indicate the start of a critical section of
 * code.
 *
 * @param	inHandle	Lock handle
 *
 * @return	0 on success, non-zero on failure
 *******************************************************************************
 */
IS32 VDM_SMM_PL_lock(void *inHandle);

/**
 *******************************************************************************
 * Unlock the current thread. Used to indicate the end of a critical section of
 * code.
 *
 * @param	inHandle	Lock handle
 *
 * @return	0 on success, non-zero on failure
 *******************************************************************************
 */
IS32 VDM_SMM_PL_unlock(void *inHandle);

/**
 *******************************************************************************
 * Block a thread and wait for a signal. See VDM_SMM_PL_signal.
 *
 * @param	inHandle	Lock handle
 * @param	keepBusy	whether to be "busy" while waiting
 *
 * @return	0 on success, non-zero on failure
 *******************************************************************************
 */
IS32 VDM_SMM_PL_wait(void *inHandle, IBOOL keepBusy);

/**
 *******************************************************************************
 * Block a thread and wait for a signal or a timeout. See VDM_SMM_PL_signal.
 *
 * @param	inHandle	Lock handle
 * @param	inSecs		Timeout in seconds
 * @param	keepBusy	whether to be "busy" while waiting
 *
 * @return	0 on success, non-zero on failure
 *******************************************************************************
 */
IS32 VDM_SMM_PL_timedwait(void *inHandle, TIME_T inSecs, IBOOL keepBusy);

/**
 *******************************************************************************
 * Send a signal on a thread. See VDM_SMM_PL_wait and VDM_SMM_PL_timedwait.
 *
 * @param	inHandle	Lock handle
 *
 * @return	0 on success, non-zero on failure
 *******************************************************************************
 */
IS32 VDM_SMM_PL_signal(void *inHandle);

/**
 *******************************************************************************
 * Notify that the SMM is working with a lock. Called from within a critical
 * section of code, inside a lock. See VDM_SMM_PL_notifyIdle.
 *
 * Example use-case: The DM Client should not suspend (wake-lock) while the SMM
 * is busy. This implementation may be left empty.
 *
 * @param	inHandle	Lock handle
 *******************************************************************************
 */
void VDM_SMM_PL_notifyBusy(void *inHandle);

/**
 *******************************************************************************
 * Notify that the SMM is no longer working with a lock. See
 * VDM_SMM_PL_notifyBusy.
 *
 * @param	inHandle	Lock handle
 *
 * @return	zero on success
 *******************************************************************************
 */
IS32 VDM_SMM_PL_notifyIdle(void *inHandle);

/**
 *******************************************************************************
 * Invoke a function on a new thread, called from VDM_SMM_PL_createThread.
 *
 * @param	inArg	Variable to pass to the function
 *
 * @return	non-NULL on success, NULL on failure
 *******************************************************************************
 */
typedef void *(*VDM_SMM_PL_ThreadStartRoutine_t)(void *inArg);

/**
 *******************************************************************************
 * Create a new thread and invoke a function on it. See
 * VDM_SMM_PL_ThreadStartRoutine_t.
 *
 * @param	inStartRoutine	Function to start on the thread
 * @param	inArg			Variable to pass to the function
 *
 * @return	0 on success, non-zero on failure
 *******************************************************************************
 */
IS32 VDM_SMM_PL_createThread(VDM_SMM_PL_ThreadStartRoutine_t inStartRoutine, void *inArg);

#ifdef __cplusplus
}
#endif

#endif /* _VDM_SMM_PL_H_ */

