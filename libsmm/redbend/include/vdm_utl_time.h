/*
 *******************************************************************************
 *
 * vdm_utl_time.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_utl_time.h
 *
 * \brief	Time Utilities
 *******************************************************************************
 */
#ifndef VDM_UTL_TIME_H
#define VDM_UTL_TIME_H          //!< Internal

#ifdef __cplusplus
extern "C" {
#endif

#include <vdm_pl_time.h>

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
extern IU32 VDM_UTL_getCurrentTime(TIME_T *outSeconds);

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
extern IS32 VDM_UTL_getUtcOffset(void);

/*!
 *******************************************************************************
 * Get how long the system has been running in seconds.
 *
 * \param	outSeconds	Uptime in seconds
 *
 * \return  0 on success, positive number on failure
 *******************************************************************************
 */
extern IU32 VDM_UTL_getUptime(IU32 *outSeconds);

/*!
 *******************************************************************************
 * Convert time from TIME_T to platform-agnostic format
 *
 * \see	VDM_UTL_Time_toTimeT
 *
 * \param	outTime		The time in VDM_UTL_Time_t format.
 * \param	inTimeT		The time as TIME_T.
 *
 * \return  0 on success, positive number on failure
 *******************************************************************************
 */
extern IU32 VDM_UTL_Time_fromTimeT(VDM_PL_Time_t *outTime, TIME_T inTimeT);

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
extern IU32 VDM_UTL_Time_toTimeT(TIME_T *outTimeT, VDM_PL_Time_t *inTime);

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
extern IU32 VDM_UTL_getCurrentTimeInMillisec(IU64 *outMillis);

/*!
 *******************************************************************************
 * Get the current time + UTC offset in seconds.
 *
 * \param  outSeconds	Current local time seconds with UTC offset
 *
 * \return  0 on success, positive number on failure
 *******************************************************************************
 */
extern IU32 VDM_UTL_getTimeWithoutUTCOffset(TIME_T *outSeconds);

/*!
 *******************************************************************************
 * Convert the input string to number of seconds.
 * Supported formats:
 * 3600s (3600 seconds)
 * 60 (60 minutes)
 * 60m (60 minutes)
 * 1h (1 hour)
 *
 * \param	inString	String to convert
 *
 * \return Number of seconds
 *******************************************************************************
 */
extern IU32 VDM_UTL_Time_str2sec(const char *inString);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

