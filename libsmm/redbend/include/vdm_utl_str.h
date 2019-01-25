/*
 *******************************************************************************
 *
 * vdm_utl_str.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_utl_str.h
 *
 * \brief	ANSI String Utilities
 *******************************************************************************
 */
#ifndef VDM_UTL_STR_H
#define VDM_UTL_STR_H           //!< Internal

#include <vdm_pl_types.h>
#include <vdm_error.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *******************************************************************************
 * Duplicate a string.
 *
 * Memory for the new string is acquired using \ref VDM_PL_malloc and should be
 * freed using \ref VDM_PL_free or \ref VDM_PL_freeAndNullify.
 *
 * \param	inString	The string to duplicate
 *
 * \return	A pointer to the duplicate string
 *******************************************************************************
 */
extern char *VDM_UTL_strdup(const char *inString);

/*!
 *******************************************************************************
 * Duplicate the first \a inLen characters of a string.
 *
 * Memory for the new string is acquired using \ref VDM_PL_malloc and should be
 * freed using \ref VDM_PL_free or \ref VDM_PL_freeAndNullify.
 *
 * \param	inString	The string to duplicate
 * \param	inLen		The number of characters to duplicate.
 *
 * \return	A pointer to the duplicate string
 *******************************************************************************
 */
extern char *VDM_UTL_strndup(const char *inString, IU32 inLen);

/*!
 *******************************************************************************
 * Macro for \ref VDM_UTL_stringPrintNull.
 *
 * \param	P	Buffer to print.
 *
 * \return	"[null]" if the buffer was null, otherwise the buffer is returned
 *			as entered
 *******************************************************************************
 */
#define VDM_UTL_strPrintNull(P) (VDM_UTL_stringPrintNull((const char *)(P)))

/*!
 *******************************************************************************
 * Print "[null]" instead of a null buffer.
 *
 * \param	inPtr	Buffer to print.
 *
 * \return	"[null]" if the buffer was null, otherwise the buffer is returned
 *			as entered
 *******************************************************************************
 */
extern char *VDM_UTL_stringPrintNull(const char *inPtr);

/*!
 *******************************************************************************
 * Get whether two strings are equal, ignoring case as required.
 *
 * \param	inString1	The first string
 * \param	inString2	The second string
 * \param	inIgnoreCase	TRUE to ignore case, FALSE otherwise
 *
 * \return	TRUE if the strings are equal, FALSE otherwise
 *******************************************************************************
 */
extern IBOOL VDM_UTL_strAreEqual(const char *inString1, const char *inString2,
	IBOOL inIgnoreCase);

/*!
 *******************************************************************************
 * Get the number of characters at the start of a string that are all from a
 * specified set of acceptable characters.
 *
 * \param	inString	The string
 * \param	inAccept	A string containing the specified set of
 *				acceptable characters
 *
 * \return	The length of the valid string
 *******************************************************************************
 */
IU32 VDM_UTL_strspn(const char *inString, const char *inAccept);

/*!
 *******************************************************************************
 * Get the number of characters at the start of a string that are all not from a
 * specified set of acceptable characters.
 *
 * \param	inString	The string
 * \param	inReject	A string containing the specified set of
 *				not acceptable characters
 *
 * \return	The length of the valid string
 *******************************************************************************
 */
IU32 VDM_UTL_strcspn(const char *inString, const char *inReject);

/*!
 *******************************************************************************
 * Split a string of tokens separated by delimiters into an array of tokens.
 *
 * Memory for the new string is acquired using \ref VDM_PL_malloc and can be
 * freed using \ref VDM_PL_free or \ref VDM_PL_freeAndNullify.
 *
 * \param   inString        The string
 * \param   inSeperator     The delimiter
 * \param   outParts        A pointer to the new allocated array of tokens
 * \param   outPartsCount   Size of \a outParts array
 *
 * \return  VDM_ERR_OK on success, VDM_ERR_INVALID_CALL if \a inString,
 *          \a inSeparator, \a outParts, or \a outPartsCount are NULL, or
 *          VDM_ERR_MEMORY if out of memory
 *******************************************************************************
 */
VDM_Error VDM_UTL_strSplit(const char *inString,
        const char *inSeperator, char ***outParts, IU32 *outPartsCount);

/*!
 *******************************************************************************
 * Get the next token in a string of tokens separated by delimiters, starting
 * from an offset.
 *
 * Similar to strtok, but without using a global variable.
 *
 * \param   inString    The string
 * \param   inSeperator The delimiter
 * \param   ioOffset    Input: Start of the token to get;
 *                      Output: Start of the next token
 * \param   outToken    Pre-allocated buffer to store the token
 * \param   inTokenSize The token size
 *
 * \return  TRUE if the end of the string has not yet been reached (indicating
 *          that there are more tokens), FALSE otherwise
 *
 *  \code
    while (isFound)
    {
        isFound = VDM_UTL_strGetNextSubstr(string, '/', &offset, token);
    }
    \endcode
 *******************************************************************************
 */
IBOOL VDM_UTL_strGetNextSubstr(const char *inString, char inSeperator,
    IU32 *ioOffset, char *outToken, IU32 inTokenSize);

/*!
 *******************************************************************************
 * Free array of tokens allocated by \ref VDM_UTL_strSplit.
 *
 * \param   inParts      A pointer to the allocated array of tokens
 * \param   inPartsCount Size of \a inParts
 *
 * \return  None
 *******************************************************************************
 */
void VDM_UTL_strSplitFree(char **inParts, IU32 inPartsCount);

/*!
 *******************************************************************************
 * Check whether a string represents a pure decimal number.
 *
 * Only digits (0-9) are allowed in \a inStr, and it cannot start with 0.
 *
 * \param   inStr   String to check
 *
 * \return  TRUE if \a inStr is a pure decimal number,
 *          FALSE otherwise
 *******************************************************************************
 */
IBOOL VDM_UTL_strIsPureDecNumber(const char *inStr);

/*!
 *******************************************************************************
 * Convert a string to a decimal number.
 *
 * Trim spaces from both ends of the string.
 *
 * \param   inStr           String to convert
 * \param   outIsSuccess    TRUE on success, FALSE otherwise
 *
 * \return  The decimal equivalent
 *******************************************************************************
 */
IU64 VDM_UTL_strGetDecNumber(const char *inStr, IBOOL *outIsSuccess);


/*!
 *******************************************************************************
 * Search for a substring within a string of specific length.
 *
 * \param   inHaystack  String within which to search
 * \param   inNeedle    String to search for within \a inHaystack
 * \param   inLen       \a inHaystack Length
 *
 * \return  Pointer to the first occurrence of \a inNeedle within \a inHaystack
 *          if it exists, or NULL if not found
 *******************************************************************************
 */
const char *VDM_UTL_strnstr(const char *inHaystack, const char *inNeedle, IU32 inLen);

/*!
 *******************************************************************************
 * Search for a substring within a string, ignoring case.
 *
 * \param   inHaystack  String within which to search
 * \param   inNeedle    String to search for within \a inHaystack
 *
 * \return  Pointer to the first occurrence of \a inNeedle within \a inHaystack
 *          if it exists, or NULL if not found
 *******************************************************************************
 */
char *VDM_UTL_strCasestr(const char *inHaystack, const char *inNeedle);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

