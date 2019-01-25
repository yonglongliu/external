/*
 *******************************************************************************
 *
 * vdm_utl_utf8.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_utl_utf8.h
 *
 * \brief	Unsigned Char String API
 *
 * The UTF8Str type is based on unsigned char. OMA DM Protocol Engine casts UTF8 string
 * pointers to use the VDM_PL_str* APIs without producing warnings; these macros
 * avoid those explicit casts.
 *******************************************************************************
 */
#ifndef VDM_UTL_UTF8_H
#define VDM_UTL_UTF8_H              //!< Internal

#include "vdm_pl_string.h"
#include "vdm_utl_str.h"
#include "vdm_pl_string_utils.h"
#ifdef __cplusplus
extern "C" {
#endif

/*!
 *******************************************************************************
 * Get the length of a string.
 *
 * \param	inString	The string
 *
 * \return	The length of the string, in bytes
 *******************************************************************************
 */
#define VDM_UTL_utf8len(inString)                                       \
	VDM_PL_strlen((const char *)(inString))

/*!
 *******************************************************************************
 * Search for a character in a string.
 *
 * \param	inString	The string
 * \param	inChar		The character
 *
 * \return	A pointer to the first occurrence of the character in the string, or
 *			NULL if the character is not found
 *******************************************************************************
 */
#define VDM_UTL_utf8chr(inString, inChar)                               \
	((UTF8Str)VDM_PL_strchr((const char *)(inString), (char)(inChar)))

/*!
 *******************************************************************************
 * Reverse search for a character in a string.
 *
 * \param	inString	The string
 * \param	inChar		The character
 *
 * \return	A pointer to the last occurrence of the character in the string, or
 *			NULL if the character is not found
 *******************************************************************************
 */
#define VDM_UTL_utf8rchr(inString, inChar)                              \
	((UTF8Str)VDM_PL_strrchr((const char *)(inString), (inChar)))

/*!
 *******************************************************************************
 * Compare two strings.
 *
 * \param	inString1	The first string
 * \param	inString2	The second string
 *
 * \return	< 0: \a inString1 is lexically less than \a inString2,
 *			  0: \a inString1 == \a inString2,
 *			> 0: \a inString1 is lexically greater than \a inString2
 *******************************************************************************
 */
#define VDM_UTL_utf8cmp(inString1, inString2)                           \
	VDM_PL_strcmp((const char *)(inString1), (const char *)(inString2))

/*!
 *******************************************************************************
 * Compare up to \a inLen characters of two strings.
 *
 * Characters that follow a null character are not compared.
 *
 * \param	inString1	The first string
 * \param	inString2	The second string
 * \param	inLen		The maximum number of characters to compare
 *
 * \return	< 0: \a inString1 is lexically less than \a inString2,
 *			  0: \a inString1 == \a inString2,
 *			> 0: \a inString1 is lexically greater than \a inString2
 *******************************************************************************
 */
#define VDM_UTL_utf8ncmp(inString1, inString2, inLen)                       \
	VDM_PL_strncmp((const char *)(inString1), (const char *)(inString2), (inLen))

/*!
 *******************************************************************************
 * Copy a string to the specified destination.
 *
 * \param	outDest		The destination string
 * \param	inSrc		The source string
 *
 * \return	A pointer to the destination string
 *******************************************************************************
 */
#define VDM_UTL_utf8cpy(outDest, inSrc)                                 \
	(VDM_PL_strcpy((char *)(outDest), (const char *)(inSrc)))

/*!
 *******************************************************************************
 * Copy up to \a inLen characters from a string to the specified destination.
 *
 * Characters that follow a null character are not copied.
 *
 * \param	outDest		The destination string
 * \param	inSrc		The source string
 * \param	inLen		The maximum number of characters to copy
 *
 * \return	A pointer to the destination string
 *******************************************************************************
 */
#define VDM_UTL_utf8ncpy(outDest, inSrc, inLen)                             \
	(VDM_PL_strncpy((char *)(outDest), (const char *)(inSrc), (inLen)))

/*!
 *******************************************************************************
 * Copy up to \a inLen-1 characters from a string to the specified destination.
 *
 * Characters that follow a null character are not copied.
 *
 * \param	outDest		The destination string
 * \param	inSrc		The source string
 * \param	inSize		Size of destination buffer.
 *
 * \return	The total length of the string tried to create
 *******************************************************************************
 */
#define VDM_UTL_utf8lcpy(outDest, inSrc, inSize)                                \
	(VDM_PL_strlcpy((char *)(outDest), (const char *)(inSrc), (inSize)))

/*!
 *******************************************************************************
 * Concatenate a string to the specified string.
 *
 * \param	ioDest		The destination string
 * \param	inSrc		The string to concatenate onto the destination
 *
 * \return	A pointer to the destination string
 *******************************************************************************
 */
#define VDM_UTL_utf8cat(ioDest, inSrc)                                  \
	(VDM_PL_strcat((char *)(ioDest), (const char *)(inSrc)))
/*!
 *******************************************************************************
 * Concatenate a string to the specified string.
 * It will append at most size - strlen(dest) - 1 bytes, NUL-terminating the
 * result.
 *
 * \param	ioDest		The destination string
 * \param	inSrc		The string to concatenate onto the destination
 * \param	inSize		Size of destination buffer.
 *
 * \return	The total length of the string tried to create
 *******************************************************************************
 */
#define VDM_UTL_utf8lcat(ioDest, inSrc, inSize)                                 \
	(VDM_PL_strlcat((char *)(ioDest), (const char *)(inSrc), (inSize)))

/*!
 *******************************************************************************
 * Duplicate a string.
 *
 * Memory for the new string is acquired using \ref VDM_PL_malloc and can be
 * freed using \ref VDM_PL_free or \ref VDM_PL_freeAndNullify.
 *
 * \param	inString	The string to duplicate
 *
 * \return	A pointer to the duplicated string
 *******************************************************************************
 */
#define VDM_UTL_utf8dup(inString) \
	((UTF8Str)VDM_UTL_strdup((const char *)(inString)))

/*!
 *******************************************************************************
 * Duplicate the first \a inLen characters of a string.
 *
 * Memory for the new string is acquired using \ref VDM_PL_malloc and can be
 * freed using \ref VDM_PL_free or \ref VDM_PL_freeAndNullify.
 *
 * \param	inString	The string
 * \param	inLen		The number of characters to duplicate
 *
 * \return	A pointer to the duplicated string
 *******************************************************************************
 */
#define VDM_UTL_utf8ndup(inString, inLen) \
	((UTF8Str)VDM_UTL_strndup((const char *)(inString), (inLen)))

/*!
 *******************************************************************************
 * Compare up to \a inLen characters of two strings, ignoring case.
 *
 * Characters that follow a null character are not compared.
 *
 * \param	inString1	The first string
 * \param	inString2	The second string
 * \param	inLen		The maximum number of characters to compare
 *
 * \return	< 0: \a inString1 is lexically less than \a inString2,
 *			  0: \a inString1 == \a inString2,
 *			> 0: \a inString1 is lexically greater than \a inString2
 *******************************************************************************
 */
#define VDM_UTL_utf8ncasecmp(inString1, inString2, inLen) \
	VDM_PL_strncasecmp((const char *)(inString1), (const char *)(inString2), \
	(inLen))

/*!
 *******************************************************************************
 * Compare two strings, ignoring case.
 *
 * \param	inString1	The first string
 * \param	inString2	The second string
 *
 * \return	< 0: \a inString1 is lexically less than \a inString2,
 *			  0: \a inString1 == \a inString2,
 *			> 0: \a inString1 is lexically greater than \a inString2
 *******************************************************************************
 */
#define VDM_UTL_utf8casecmp(inString1, inString2) \
	VDM_PL_strcasecmp((const char *)(inString1), (const char *)(inString2))

/*!
 *******************************************************************************
 * Get whether two strings are equal, ignoring case as required.
 *
 * \param	inString1		The first string
 * \param	inString2		The second string
 * \param	inIgnoreCase	TRUE to ignore case, FALSE otherwise
 *
 * \return	TRUE if the strings are equal, FALSE otherwise
 *******************************************************************************
 */
#define VDM_UTL_utf8AreEqual(inString1, inString2, inIgnoreCase)            \
	VDM_UTL_strAreEqual((const char *)(inString1), (const char *)(inString2), (inIgnoreCase))

/*!
 *******************************************************************************
 * Get the next token in a string of tokens separated by delimiters, starting
 * from an offset.
 *
 * Similar to strtok, but without using a global variable.
 *
 * \param	inString	The string
 * \param	inSeperator	The delimiter
 * \param	ioOffset	Input: Start of the token to get;
 *						Output: Start of the next token
 * \param	outToken	Pre-allocated buffer to store the token
 * \param	inTokenSize	The token size
 *
 * \return	TRUE if the end of the string has not yet been reached (indicating
 *			that there are more tokens), FALSE otherwise
 *
 *	\code
    while (isFound)
    {
        isFound = VDM_UTL_utf8getNextSubstr(string, '/', &offset, token);
    }
    \endcode
 *******************************************************************************
 */
extern IBOOL VDM_UTL_utf8getNextSubstr(UTF8CStr inString, IU8 inSeperator,
	IU32 *ioOffset, UTF8Str outToken, IU32 inTokenSize);

/*!
 *******************************************************************************
 * Split a string of tokens separated by delimiters into an array of tokens.
 *
 * Memory for the new string is acquired using \ref VDM_PL_malloc and can be
 * freed using \ref VDM_PL_free or \ref VDM_PL_freeAndNullify.
 *
 * \param	inString		The string
 * \param	inSeperator		The delimiter
 * \param	outParts		A pointer to the new allocated array of tokens
 * \param	outPartsCount	Size of \a outParts array
 *
 * \return	VDM_ERR_OK on success, VDM_ERR_INVALID_CALL if \a inString,
 *			\a inSeparator, \a outParts, or \a outPartsCount are NULL, or
 *			VDM_ERR_MEMORY if out of memory
 *******************************************************************************
 */
extern VDM_Error VDM_UTL_utf8split(UTF8CStr inString, UTF8CStr inSeperator,
	UTF8Str **outParts, IU32 *outPartsCount);

/*!
 *******************************************************************************
 * Free array of tokens allocated by \ref VDM_UTL_utf8split.
 *
 * \param	inParts		 A pointer to the allocated array of tokens
 * \param	inPartsCount Size of \a inParts
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_UTL_utf8splitFree(UTF8Str *inParts, IU32 inPartsCount);

/*!
 *******************************************************************************
 * Search for a substring within a string.
 *
 * \param	inHaystack	String within which to search
 * \param	inNeedle	String to search for within \a inHaystack
 *
 * \return	Pointer to the first occurrence of \a inNeedle within \a inHaystack
 *          if it exists, or NULL if not found
 *******************************************************************************
 */
#define VDM_UTL_utf8str(inHaystack, inNeedle)                               \
	((UTF8Str)VDM_PL_strstr((const char *)(inHaystack), (const char *)(inNeedle)))

/*!
 *******************************************************************************
 * Search for a substring within a string, ignoring case.
 *
 * \param	inHaystack	String within which to search
 * \param	inNeedle	String to search for within \a inHaystack
 *
 * \return	Pointer to the first occurrence of \a inNeedle within \a inHaystack
 *          if it exists, or NULL if not found
 *******************************************************************************
 */
extern UTF8Str VDM_UTL_utf8casestr(UTF8CStr inHaystack, const char *inNeedle);

/*!
 *******************************************************************************
 * Search for a substring within a string of specific length.
 *
 * \param	inHaystack	String within which to search
 * \param	inNeedle	String to search for within \a inHaystack
 * \param	inLen		\a inHaystack Length
 *
 * \return	Pointer to the first occurrence of \a inNeedle within \a inHaystack
 *          if it exists, or NULL if not found
 *******************************************************************************
 */
extern UTF8CStr VDM_UTL_utf8nstr(UTF8CStr inHaystack, UTF8CStr inNeedle, IU32 inLen);

/*!
 *******************************************************************************
 * Convert a string to a decimal number.
 *
 * Trim spaces from both ends of the string.
 *
 * \param	inStr			String to convert
 * \param	outIsSuccess	TRUE on success, FALSE otherwise
 *
 * \return	The decimal equivalent
 *******************************************************************************
 */
extern IU64 VDM_UTL_getDecNumber(UTF8CStr inStr, IBOOL *outIsSuccess);

/*!
 *******************************************************************************
 * Check whether a string represents a pure decimal number.
 *
 * Only digits (0-9) are allowed in \a inStr, and it cannot start with 0.
 *
 * \param	inStr	String to check
 *
 * \return	TRUE if \a inStr is a pure decimal number,
 *          FALSE otherwise
 *******************************************************************************
 */
extern IBOOL VDM_UTL_isPureDecNumber(UTF8CStr inStr);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

