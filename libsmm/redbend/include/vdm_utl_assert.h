/*
 *******************************************************************************
 *
 * vdm_utl_assert.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_utl_assert.h
 *
 * \brief	Assertions Utility
 *******************************************************************************
 */

#ifndef VDM_UTL_ASSERT_H_
#define VDM_UTL_ASSERT_H_           //!< Internal

#ifdef __cplusplus
extern "C"
{
#endif

#include <vdm_client_pl_assert.h>

/*!
 * Log a message on assertion failure.
 *
 * \param	inCond		Assertion condition to validate
 * \param	inMsg		Message to log on assertion failure
 *
 * \return	None
 */
#ifdef PROD
	#define VDM_UTL_assert(inCond, inMsg)
#else
	#define VDM_UTL_assert(inCond, inMsg)                       \
	do {                                                    \
		if (!(inCond)) {                                    \
			VDM_Client_PL_assertFail(__FILE__, __LINE__);   \
			VDM_logResult(E_VDM_LOGLEVEL_Error, "%s", inMsg);  \
		}                                                   \
	} while (0)

#endif  /*PROD*/

#ifdef __cplusplus
}
#endif

#endif

