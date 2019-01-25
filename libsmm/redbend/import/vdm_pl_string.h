/*
 *******************************************************************************
 *
 * vdm_pl_string.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_pl_string.h
 *
 * \brief	External String Handling APIs
 *******************************************************************************
 */

#ifndef VDM_PL_STRING_H
#define VDM_PL_STRING_H

#ifdef __cplusplus
extern "C" {
#endif

#include <vdm_pl_types.h>

/*!
 * @addtogroup pl_system
 * @{
 */

/*!
 *******************************************************************************
 * Calculate the length of a character string (not including the terminating
 * NULL).
 *
 * \param	inString		The string
 *
 * \return	The length of the string, in bytes
 *******************************************************************************
 */
extern IU32 VDM_PL_strlen(const char *inString);

/*!
 *******************************************************************************
 * Get the position of the first occurrence of a character in a character
 * string.
 *
 * \param	inString	The string
 * \param	inChar		The character
 *
 * \return	A pointer to the first occurrence of the character in the string,
 *			or NULL if the character is not found
 *******************************************************************************
 */
extern char *VDM_PL_strchr(const char *inString, char inChar);

/*!
 *******************************************************************************
 * Get the position of the last occurrence of a character in a character string.
 *
 * \param	inString	The string
 * \param	inChar		The character
 *
 * \return	A pointer to the last occurrence of the character in the string,
 *			or NULL if the character is not found
 *******************************************************************************
 */
extern char *VDM_PL_strrchr(const char *inString, char inChar);

/*!
 *******************************************************************************
 * Compare two character strings.
 *
 * \param	inString1	The first string
 * \param	inString2	The second string
 *
 * \return	< 0 if \a inString1 is lexically less than \a inString2,
 *            0 if \a inString1 is lexically the same as \a inString2, or
 *          > 0 if \a inString1 is lexically greater than \a inString2
 *******************************************************************************
 */
extern IS32 VDM_PL_strcmp(const char *inString1, const char *inString2);

/*!
 *******************************************************************************
 * Partially compare two character strings. Characters that follow a NULL
 * character are not compared.
 *
 * \param	inString1		The first string
 * \param	inString2		The second string
 * \param	inLen			Number of characters to compare
 *
 * \return	Considering only the number of characters compared:
 *          < 0 if \a inString1 is lexically less than \a inString2,
 *            0 if \a inString1 is lexically equal to \a inString2, or
 *          > 0 if \a inString1 is lexically greater than \a inString2
 *******************************************************************************
 */
extern IS32 VDM_PL_strncmp(const char *inString1, const char *inString2, IU32 inLen);

/*!
 *******************************************************************************
 * Copy a character string to the specified destination. The source and
 * destination strings must not overlap. The destination location must be large
 * enough to receive the copy of the string.
 *
 * \param	outDest		The destination string
 * \param	inSrc		The source string
 *
 * \return	A pointer to the destination string
 *******************************************************************************
 */
extern char *VDM_PL_strcpy(char *outDest, const char *inSrc);

/*!
 *******************************************************************************
 * Copy \a inLen characters from a string to a specified destination string.
 *
 * \param	outDest		The destination string
 * \param	inSrc		The source string
 * \param	inLen		The number of characters to copy
 *
 * \return	A pointer to the destination string
 *******************************************************************************
 */
extern char *VDM_PL_strncpy(char *outDest, const char *inSrc, IU32 inLen);

/*!
 *******************************************************************************
 * Copy up to \a inSize-1 characters from \a string to a specified destination
 * string.
 *
 * \param	outDest		The destination string
 * \param	inSrc		The source string
 * \param	inSize		The size of the destination buffer
 *
 * \return	The total length of the string tried to create.
 *******************************************************************************
 */
extern IU32 VDM_PL_strlcpy(char *outDest, const char *inSrc, IU32 inSize);

/*!
 *******************************************************************************
 * Concatenate a string to the specified string.
 *
 * \param	ioDest		The destination string, on which to concatenate
 * \param	inSrc		The source string that will be appended onto \a ioDest
 *
 * \return	A pointer to the destination string
 *******************************************************************************
 */
extern char *VDM_PL_strcat(char *ioDest, const char *inSrc);

/*!
 *******************************************************************************
 * Concatenate a string to the specified string.
 * It will append at most size - strlen(dest) - 1 bytes, NUL-terminating the
 * result.
 *
 * \param	ioDest		The destination string
 * \param	inSrc		The string to concatenate onto the destination
 * \param	inSize		The size of ioDest
 *
 * \return	The total length of the string tried to create.
 *******************************************************************************
 */
extern IU32 VDM_PL_strlcat(char *ioDest, const char *inSrc, IU32 inSize);

/*!
 *******************************************************************************
 * Compare two strings, ignoring case.
 *
 * \param	inString1		The first string
 * \param	inString2		The second string
 *
 * \return	Ignoring case:
 *          < 0 if \a inString1 is lexically less than \a inString2,
 *            0 if \a inString1 is lexically equal to \a inString2, or
 *          > 0 if \a inString1 is lexically greater than \a inString2
 *******************************************************************************
 */
extern IS32 VDM_PL_strcasecmp(const char *inString1, const char *inString2);

/*!
 *******************************************************************************
 * Partially compare two character strings, ignoring case. Characters that
 * follow a NULL character are not compared.
 *
 * \param	inString1		The first string
 * \param	inString2		The second string
 * \param	inLen			Number of characters to compare
 *
 * \return	Considering only the number of characters compared, and ignoring
 *          case:
 *          < 0 if \a inString1 is lexically less than \a inString2,
 *            0 if \a inString1 is lexically equal to \a inString2, or
 *          > 0 if \a inString1 is lexically greater than \a inString2
 *******************************************************************************
 */
extern IS32 VDM_PL_strncasecmp(
	const char *inString1, const char *inString2, IU32 inLen);

/*!
 *******************************************************************************
 * Locate a substring within a character string.
 *
 * \param	inHaystack	String within which to search
 * \param	inNeedle	String to search for within \a inHaystack
 *
 * \return	Pointer to the first occurrence of \a inNeedle within \a inHaystack
 *          if it exists, or NULL if not found
 *******************************************************************************
 */
extern char *VDM_PL_strstr(const char *inHaystack, const char *inNeedle);

/*!
 *******************************************************************************
 * Convert string to lower case.
 *
 * \param	ioString		The string to convert
 *
 * \return	Pointer to the converted string
 *******************************************************************************
 */
extern char *VDM_PL_strlwr(char *ioString);

/*! @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

