/*
 *******************************************************************************
 *
 * rb_pl_thread.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	rb_pl_thread.h
 *
 * \brief	Platform-specific Thread Object
 *
 * \note	A complete implementation of these APIs are provided by Red Bend
 *			Software; you do not have to implement these.
 *******************************************************************************
 */
#ifndef RB_PL_THREAD_H
#define RB_PL_THREAD_H

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *******************************************************************************
 * Wake up thread.
 *
 * \param	inThreadHandle	The thread to wake.
 *
 * \return	TRUE on success, FALSE otherwise
 ******************************************************************************
 */
IBOOL RB_PL_Thread_signal(VDM_Handle_t inThreadHandle);

/*!
 * Thread function
 */
typedef IBOOL (*THREAD_EVENT_FUNC)(void *param);

/*!
 *******************************************************************************
 * Create thread.
 *
 * \return	Thread handle
 ******************************************************************************
 */
VDM_Handle_t    RB_PL_Thread_create(void);

/*!
 *******************************************************************************
 * Create thread and assign a name to it (debug mode only).
 *
 * \note	The function uses PR_SET_NAME defined in prctl.h. If not defined,
 *			the thread name is not set.
 *
 * \param	inName	The name, limited to 16 bytes. If less than 16 bytes, it
 *					must be null-terminated.
 *
 * \return	Thread handle
 ******************************************************************************
 */
VDM_Handle_t    RB_PL_Thread_createEx(const char *inName);

/*!
 *******************************************************************************
 * Set an event handing function to run on a thread. The function can take a
 * parameter.
 *
 * \param	inThreadHandle		Thread handle.
 * \param	inHandleEventFunc	Function to run on the thread.
 * \param	inHandleEventParam	Parameter to the function.
 *
 * \return	None
 ******************************************************************************
 */
void RB_PL_Thread_setEventFunc(
	VDM_Handle_t inThreadHandle,
	THREAD_EVENT_FUNC inHandleEventFunc,
	void *inHandleEventParam);

/*!
 *******************************************************************************
 * Destroy thread.
 *
 * \param	inThreadHandle		Thread handle.
 *
 * \return	None
 ******************************************************************************
 */
void RB_PL_Thread_destroy(VDM_Handle_t inThreadHandle);

/*!
 *******************************************************************************
 * Stop currently executing thread.
 *
 * \param	inThreadHandle		Thread handle.
 *
 * \return	None
 ******************************************************************************
 */
IBOOL RB_PL_Thread_stop(VDM_Handle_t inThreadHandle);

/*!
 *******************************************************************************
 * Wait for thread to finish executing.
 *
 * \param	inThreadHandle		Thread handle.
 *
 * \return	None
 ******************************************************************************
 */
void RB_PL_Thread_wait(VDM_Handle_t inThreadHandle);

/*!
 *******************************************************************************
 * Start executing on a thread.
 *
 * \param	inThreadHandle		Thread handle.
 *
 * \return	TRUE on success, FALSE otherwise
 ******************************************************************************
 */
IBOOL RB_PL_Thread_start(VDM_Handle_t inThreadHandle);

/*!
 *******************************************************************************
 * Set current thread name (debug mode only).
 *
 * A debugging utility.
 * Use <code>ps -L </code> command line to see thread name.
 * Must be call when thread is active
 *
 * \note	The function uses PR_SET_NAME defined in prctl.h. If not defined,
 *			the thread name is not set.
 *
 * \param	inThreadHandle		Thread handle.
 *
 * \return	None
 ******************************************************************************
 */
void RB_PL_Thread_setName(char *inName);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

