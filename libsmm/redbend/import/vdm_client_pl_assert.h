/*
 *******************************************************************************
 *
 * vdm_client_pl_assert.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_client_pl_assert.h
 *
 * \brief	Assertion Failure APIs
 *
 * \note	The OMA DM Protocol Engine framework is provided in one of two possible
 *			build modes: "Release" or "Trace". Release mode eliminates most
 *			logging messages in order to enhance performance. Trace mode
 *			includes full logging, and is recommended while developing the DM
 *			Client application.
 *
 * This macro is defined only in trace mode. While in trace mode, OMA DM Protocol Engine
 * uses assertions to capture invalid inputs.
 *******************************************************************************
 */
#ifndef VDM_CLIENT_PL_ASSERT_H
#define VDM_CLIENT_PL_ASSERT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <vdm_pl_stdlib.h>

/*!
 * @defgroup pl_assert	Assert
 * @ingroup pl
 * @{ */

/*!
 *******************************************************************************
 * Report an assertion failure.
 *
 * \param	inFile		The file name in which the assertion failure occurred
 * \param	inLine		The line number within the file in which the assertion
 *                      failure occurred
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_Client_PL_assertFail(const char *inFile, IS32 inLine);

/*!
 * Assertions
 */
#ifdef PROD
	#define VDM_Client_PL_assert(cond)      \
	do {if (!(cond)) {VDM_PL_exit(-1); }} while (0)
#else
	#define VDM_Client_PL_assert(inCond)                                    \
	do {                                                    \
		if (!(inCond)) {VDM_Client_PL_assertFail(__FILE__, __LINE__); VDM_PL_exit(-1); }  \
	} while (0)

#endif  /*PROD*/

/** Assert signed */
#define VDM_Client_PL_assertUnsignedToSigned32(var) \
	VDM_Client_PL_assert(!((IS32)var & (1 << 31)))

#define VDM_ASSERT_PREFIX "!!!!!!!!!! ASSERTION FAILED!!! "

/*! @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*VDM_CLIENT_PL_ASSERT_H*/

