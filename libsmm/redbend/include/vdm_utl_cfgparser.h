/*
 *******************************************************************************
 *
 * vdm_utl_cfgparser.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \internal
 *
 * \file	vdm_utl_cfgparser.h
 *
 * \brief	Configuration File Parsing
 *
 * The configuration file format is as follows:
 * \li	Each line is: "key=value" (without the quotes). No spaces are allowed,
 *		including before and after the "=" sign. No comments are allowed after
 *		the value.
 * \li	Lines can be empty.
 * \li	A comment line begins with a "#"; no spaces before the "#" are allowed.
 * \li	Keys are case insensitive.
 * \li	Values may not be empty. Boolean values are "t" or "f", or "true" or
 *		"false". All the characters after the first are ignored.
 * \li	Parsing is sequential. If the same key appears twice, the second
 *		overrides the first.
 *******************************************************************************
 */

#ifndef _VDM_UTL_CFGPARSER_H_
#define _VDM_UTL_CFGPARSER_H_           //!< Internal

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The maximum string size of the key and the value to show in the log messages.
 * This is used by \ref VDM_UTL_CfgParser_getFormattedPrintout.
 */
#define VDM_UTL_CFGPARSER_KEY_VAL_PRINTOUT_LEN 30

/*!
 *******************************************************************************
 * Configure a key.
 *
 * \param	inContext		Context passed from \ref VDM_UTL_CfgParser_parsePair
 * \param	inKey			The key
 * \param	inValue			The value
 * \param	outIsValidKey	TRUE if \a inKey is valid, FALSE otherwise
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_UTL_CfgParser_configPairCB)(
	void *inContext,
	const char *inKey,
	const char *inValue,
	IBOOL *outIsValidKey);

/*!
 *******************************************************************************
 * Parse configuration file.
 *
 * \param	inContext			Context to pass to \a inConfigurationFunc
 * \param	inFileName			Configuration file name
 * \param	inConfigurationFunc Configuration function, must be of the type
 *								\ref VDM_UTL_CfgParser_configPairCB
 *
 * \return	VDM_ERR_OK on success, VDM_ERR_STORAGE_OPEN if the file is not
 *			found, VDM_ERR_MEMORY if there is no memory to perform the action,
 *			or a \ref VDM_ERR_defs error code returned by
 *			\a inConfigurationFunc
 *******************************************************************************
 */
extern VDM_Error VDM_UTL_CfgParser_parseFile(void *inContext,
	const char *inFileName, VDM_UTL_CfgParser_configPairCB inConfigurationFunc);

/*!
 *******************************************************************************
 * Parse a configuration file line ("key=value" pair).
 *
 * \param	inPair			The "key=value" pair
 * \param	inSeparator		The character that separates the key and the value
 *							(the "="); the separator cannot be "#"
 * \param	outKey			The key from \a inPair
 * \param	outValue		The value from \a inPair
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT, or
 *			VDM_ERR_INVALID_CALL if the format is incorrect
 *******************************************************************************
 */
extern VDM_Error VDM_UTL_CfgParser_parsePair(
	char *inPair,
	char inSeparator,
	char **outKey,
	char **outValue);

/*!
 *******************************************************************************
 * Get the formatted printout of the key and the value in the log messages.
 * If \a inKey or \a inVal are longer than
 * VDM_UTL_CFGPARSER_KEY_VAL_PRINTOUT_LEN, then only their beginning will be
 * printed, appended with "...".
 *
 * \param	inKey			The string that contains the key
 * \param	outKeyPrintout	The buffer that will contain the formatted printout
 *							string for \a inKey.
 * \param	inKeySize		Size of key buffer in bytes
 * \param	inVal			The string that contains the value
 * \param	outValPrintout	The buffer that will contain the formatted printout
 *							string for \a inVal.
 * \param	inValSize		Size of value buffer in bytes
 *
 * \return	none
 *******************************************************************************
 */
extern void VDM_UTL_CfgParser_getFormattedPrintout(
	const char *inKey,
	char *outKeyPrintout,
	IU32 inKeySize,
	const char *inVal,
	char *outValPrintout,
	IU32 inValSize);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

