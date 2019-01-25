/*
 *******************************************************************************
 *
 * vdm_pl_string_utils.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_pl_string_utils.h
 *
 * \brief	Additional External String Handling Utilities APIs
 *
 * String print formatting and join.
 *******************************************************************************
 */

#ifndef VDM_PL_STRING_UTILS_H__
#define VDM_PL_STRING_UTILS_H__

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @addtogroup pl_system
 * @{
 */

/*!
 *******************************************************************************
 * Write formatted data to a string.
 *
 * \note If \a inCount is too short, the result string must be truncated.
 *
 * \param	outBuffer	Buffer containing the formatted output string
 * \param	inCount		Maximum number of characters to produce
 * \param	inFormat	Format-control string
 * \param	...			printf argument list
 *
 * \return	The number of characters, not including a terminating NULL if one
 *			is written; or -1 if the number of characters that could have been
 *			written was greater than \a inCount, indicating that the output has
 *			been truncated
 *******************************************************************************
 */
IS32 VDM_PL_snprintf(char *outBuffer, IU32 inCount, const char *inFormat, ...);

/*!
 *******************************************************************************
 * Concatenate a number of strings. The last string must be a NULL character.
 * An optional separator can be inserted between the strings.
 *
 * It is the caller's responsibility to free the allocated string, using \ref
 * VDM_PL_freeAndNullify, for example.
 *
 * \param	inSeparator	A string to insert between each string in the list;
 *						this can be NULL and treated as empty string.
 * \param	...			A NULL-terminated list of strings to join together; the
 *                      last entry must be NULL
 *
 * \return	The new string containing all of the strings concatenated together
 *          with the separator between each one, or NULL on an error
 *
 * \code
    char *str = VDM_PL_strjoin(",", "Hello", " world!", (char *)NULL);
    VDM_PL_freeAndNullify(str);
   \endcode
 *******************************************************************************
 */
char *VDM_PL_strjoin(const char *inSeparator, ...);

/*!
 *******************************************************************************
 * Allocate a large enough string and write formatted data to it.
 *
 * \param	inFormat	Format-control string
 * \param	...			printf argument list
 *
 * \return	The new allocated formatted string, or NULL on an error
 *******************************************************************************
 */
char *VDM_PL_strprintf(const char *inFormat, ...);

/*! @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

