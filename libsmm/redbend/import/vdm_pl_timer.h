/*
 *******************************************************************************
 *
 * vdm_pl_timer.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_pl_timer.h
 *
 * \brief	A generic timer mechanism
 *******************************************************************************
 */

#ifndef VDM_PL_TIMER_H__
#define VDM_PL_TIMER_H__				//!< Internal

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *******************************************************************************
 * Callback invoked when a set timer expires.
 *
 * This callback is passed to \ref VDM_PL_Timer_create upon timer creation.
 *
 * \param	inContext		The context that was supplied  when timer was set in
 *                          \ref VDM_PL_Timer_set.
 *
 * \see VDM_PL_Timer_set
 *
 * \return	None
 *******************************************************************************
 */
typedef void (*VDM_PL_Timer_ExpirationCB_t) (void *inContext);

/*!
 *******************************************************************************
 * Create a timer.
 *
 * \param	inExpirationCB		Callback to invoke when the timer expires, a
 *								\ref VDM_PL_Timer_ExpirationCB_t value.
 *
 * \return	Handle to the created timer, or NULL on failure
 *******************************************************************************
 */
extern VDM_PL_Timer_ExpirationCB_t VDM_PL_Timer_create(VDM_PL_Timer_ExpirationCB_t inExpirationCB);

/*!
 *******************************************************************************
 * Set a timer.
 *
 * This function sets the timer to expire in \a inSeconds.
 * Upon expiration, the callback passed to \ref VDM_PL_Timer_create will
 * be invoked with \a inContext as the parameter.
 * If a timer was already set, it will first be canceled.
 *
 * \see VDM_PL_Timer_ExpirationCB_t
 *
 * \param	inHandle		Handle to the timer.
 * \param	inSeconds		Interval in seconds.
 * \param	inContext		Parameter for the timer expiration callback.
 *
 * \return	TRUE if the timer was successfully set, FALSE otherwise
 *******************************************************************************
 */
extern IBOOL VDM_PL_Timer_set(void *inHandle, IU32 inSeconds, void *inContext);

/*!
 *******************************************************************************
 * Cancel a timer request.
 *
 * This function cancels a timer previously set by \ref VDM_PL_Timer_set.
 *
 * \param	inHandle			Handle to the timer
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_PL_Timer_cancel(void *inHandle);

/*!
 *******************************************************************************
 * Destroy a timer.
 *
 * This function cancels the timer and frees all resources related to it.
 *
 * \param	inHandle			Handle to the timer
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_PL_Timer_destroy(void *inHandle);

/*! @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
