/*
 *******************************************************************************
 *
 * vdm_pl_stdlib.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_pl_stdlib.h
 *
 * \brief	External Stdlib APIs
 *******************************************************************************
 */

#ifndef VDM_PL_STDLIB_H__
#define VDM_PL_STDLIB_H__

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @addtogroup pl_system
 * @{
 */

/*!
 *******************************************************************************
 * Convert a NULL-terminated byte character string to an signed integer.
 * This function is only required to handle positive decimal integer or
 * hexadecimal integer strings.
 *
 *
 * \param	inString		The source string
 * \param	inRadix			The base to use for conversion<br>
 *							Possible values are "10" indicating decimal, or "16"
 *							indicating hex.
 * \param	outIsSuccess	TRUE: Success,
 *                          FALSE: Failure,
 *                          NULL: Success/failure not returned
 *
 * \return	An IS32 value
 *******************************************************************************
 */
IS32 VDM_PL_atoIS32(const char *inString, IU8 inRadix, IBOOL *outIsSuccess);

/*!
 *******************************************************************************
 * Convert a NULL-terminated byte character string to an unsigned integer.
 * This function is only required to handle positive decimal integer or
 * hexadecimal integer strings.
 *
 * \note	If the string contains a '-' sign character behavior is unexpected.
 *
 * \param	inString		The source string
 * \param	inRadix			The base to use for conversion<br>
 *							Possible values are "10" indicating decimal, or "16"
 *							indicating hex.
 * \param	outIsSuccess	TRUE: Success,
 *                          FALSE: Failure,
 *                          NULL: Success/failure not returned
 *
 * \return	An IU32 value
 *******************************************************************************
 */
extern IU32 VDM_PL_atoIU32(const char *inString, IU8 inRadix, IBOOL *outIsSuccess);

/*!
 *******************************************************************************
 * Convert a NULL-terminated byte character string to an unsigned integer.
 * This function is only required to handle positive decimal integer or
 * hexadecimal integer strings.
 *
 * \note	If the string contains a '-' sign character behavior is unexpected.
 *
 * \param	inString		The source string
 * \param	inRadix			The base to use for conversion<br>
 *							Possible values are "10" indicating decimal, or "16"
 *							indicating hex.
 * \param	outIsSuccess	TRUE: Success,
 *                          FALSE: Failure,
 *                          NULL: Success/failure not returned
 *
 * \return	An IU64 value
 *******************************************************************************
 */
extern IU64 VDM_PL_atoIU64(const char *inString, IU8 inRadix, IBOOL *outIsSuccess);

/*!
 *******************************************************************************
 * Convert an unsigned integer value into a decimal or hexadecimal string
 * representation. The supplied buffer should be large enough to receive the
 * generated string (11 bytes for decimal, 9 bytes for hexadecimal).
 *
 * \note	This function does NOT prepend the value with '0x' for hexadecimal
 *          values.
 *
 * \param	inValue		The integer value to convert
 * \param	outString	Output buffer to receive the ASCII representation
 * \param	inRadix		The base to use for conversion<br>
 *						Possible values are "10" indicating decimal, or "16"
 *						indicating hex.
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_PL_IU32toa(IU32 inValue, char *outString, IU8 inRadix);

/*!
 *******************************************************************************
 * Convert an unsigned integer value into a decimal or hexadecimal string
 * representation. The supplied buffer should be large enough to receive the
 * generated string (11 bytes for decimal, 9 bytes for hexadecimal).
 *
 * \note	This function does NOT prepend the value with '0x' for hexadecimal
 *          values.
 *
 * \param	inValue		The integer value to convert
 * \param	outString	Output buffer to receive the ASCII representation
 * \param	inRadix		The base to use for conversion<br>
 *						Possible values are "10" indicating decimal, or "16"
 *						indicating hex.
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_PL_IU64toa(IU64 inValue, char *outString, IU8 inRadix);

/*!
 *******************************************************************************
 * Check if a character is considered as whitespace.
 *
 * \param	inChar		The character to check
 *
 * \return	TRUE if \a inChar is a whitespace character,
 *			FALSE otherwise
 *******************************************************************************
 */
extern IBOOL VDM_PL_isspace(const char inChar);

/*!
 *******************************************************************************
 * Exit the application. This may be called to immediately exit the application
 * after an assertion failure.
 *
 * \param	inStatus	The exit status
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_PL_exit(IS32 inStatus);

/*!
 *******************************************************************************
 * Get a pseudo-random integer. Uses the seed set by \ref VDM_PL_srand or a
 * default seed. Each invocation returns the next number from the list of
 * pseudo-random numbers generated using the seed.
 *
 * \see		VDM_PL_srand
 *
 * \param	None
 *
 * \return	Pseudo-random integer
 *******************************************************************************
 */
extern IU32 VDM_PL_rand(void);

/*!
 *******************************************************************************
 * Set pseudo-random number generator seed. It is recommended to call this once
 * at the start of your program with a different integer each time (such as the
 * clock time); otherwise, the list of pseudo-random numbers returned by
 * \ref VDM_PL_rand will be the same each time the program is run.
 *
 * \see		VDM_PL_rand
 *
 * \param	inSeed	Seed number
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_PL_srand(IU32 inSeed);

/*! @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

