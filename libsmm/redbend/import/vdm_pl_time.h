/*
 *******************************************************************************
 *
 * vdm_pl_time.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_pl_time.h
 *
 * \brief	Time API
 *
 * For handling timed events, the Engine occasionally requests the system for
 * the current time. The Engine uses this API to calculate time intervals.
 *******************************************************************************
 */
#ifndef VDM_PL_TIME_H__
#define VDM_PL_TIME_H__

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @defgroup pl_time	Time
 * Time may be represented as an integer or a platform-agnostic format. <br>
 * The Engine only uses the integer format for storage, and does not require
 * any calculation of absolute "zero time". The value of "zero time" may be
 * platform-specific.
 *
 * @ingroup pl
 * @{
 */

/*!
 * A date and time object in which the individual components
 * are accessible in human-readable form.
 */
typedef struct {
	IS16 year;          ///< Gregorian calendar year
	IS16 month;         ///< Month	[1..12]
	IS16 day;           ///< Day	[1..31]
	IS16 hour;          ///< Hour	[0..23]
	IS16 minute;        ///< Minute [0..59]
	IS16 second;        ///< Second [0..59]
} VDM_PL_Time_t;

/*!
 *******************************************************************************
 * Get the current time in seconds.
 *
 * Get the local time (wall clock time).
 * There is no requirement for the value "epoch time". The value of "epoch time"
 * may be platform-specific.
 *
 * \param  outSeconds	Current local time
 *
 * \return  0 on success, positive number on failure
 *******************************************************************************
 */
extern IU32 VDM_PL_getCurrentTime(TIME_T *outSeconds);

/*!
 ******************************************************************************
 * Get UTC offset of the current time in seconds.
 *
 * For example: Kathmandu's time zone is UTC+5:45, so the offset from UTC must
 * be calculated as +((5*60)+45)*60.
 *
 * \return	UTC offset for the current time zone, in seconds
 ******************************************************************************
 */
extern IS32 VDM_PL_getUtcOffset(void);

/*!
 *******************************************************************************
 * Get how long the system has been running in seconds.
 *
 * \param	outSeconds	Uptime in seconds
 *
 * \return  0 on success, positive number on failure
 *******************************************************************************
 */
extern IU32 VDM_PL_getUptime(IU32 *outSeconds);

/*!
 *******************************************************************************
 * Convert time from TIME_T to platform-agnostic format
 *
 * \see	VDM_PL_Time_toTimeT
 *
 * \param	outTime		The time in VDM_PL_Time_t format.
 * \param	inTimeT		The time as TIME_T.
 *
 * \return  0 on success, positive number on failure
 *******************************************************************************
 */
extern IU32 VDM_PL_Time_fromTimeT(VDM_PL_Time_t *outTime, TIME_T inTimeT);

/*!
 *******************************************************************************
 * Convert time from platform-agnostic format to TIME_T
 *
 * \see	VDM_PL_Time_fromTimeT
 *
 * \param	outTimeT	The time as TIME_T.
 * \param	inTime		The time in VDM_PL_Time_t format.
 *
 * \return  0 on success, positive number on failure
 *******************************************************************************
 */
extern IU32 VDM_PL_Time_toTimeT(TIME_T *outTimeT, VDM_PL_Time_t *inTime);

/*!
 *******************************************************************************
 * Get the current time in milliseconds.
 *
 * Get the local time (wall clock time).
 * There is no requirement for the value "epoch time". The value of "epoch time"
 * may be platform-specific.
 *
 * \param  outMillis	Current local time
 *
 * \return  0 on success, positive number on failure
 *******************************************************************************
 */
extern IU32 VDM_PL_getCurrentTimeInMillisec(IU64 *outMillis);

/*! @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

