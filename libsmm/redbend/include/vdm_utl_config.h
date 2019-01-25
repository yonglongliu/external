/*
 *******************************************************************************
 *
 * vdm_utl_config.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 ******************************************************************************
 * \file	vdm_utl_config.h
 *
 * \brief	Configuration API
 ******************************************************************************
 */
#ifndef _VDM_UTL_CONFIG_H_
#define _VDM_UTL_CONFIG_H_

#include <vdm_pl_types.h>
#include <vdm_error.h>
#include <vdm_utl_mutex.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define HASH_SIZE ('z' - '0' + 1)

#define CFG_FLG_INTERNAL                0x0001
#define CFG_FLG_ALLOWED_AFTER_START     0x0002

// tree controlled related flags
#define CFG_FLG_TREE_CONTROLLED         0x0004

typedef enum {
	E_CFG_TYPE_str = 0,
	E_CFG_TYPE_bool = 1,
	E_CFG_TYPE_iu32 = 2,
	E_CFG_TYPE_enum = 3, // iu32 with table
	E_CFG_TYPE_file = 4 // recursive configuration file
} configType_t;

typedef struct lookupTable_t {
	const char *key;
	IU32 value;
} lookupTable_t;

typedef struct VDM_UTL_Config_t VDM_UTL_Config_t;

typedef union {
	char *str;
	IBOOL ibool;
	IU32 iu32;
} VDM_UTL_Config_value_t;

typedef void (*VDM_UTL_Config_onValueChangedCB) (
	void *inContext, void *inNewValue);

typedef struct VDM_UTL_Config_extCB_t {
	VDM_UTL_Config_onValueChangedCB func;
	void *context;
	struct VDM_UTL_Config_extCB_t *next;
} VDM_UTL_Config_extCB_t;

typedef struct VDM_UTL_Config_cfg_t {
	const char *group;
	const char *key;
	configType_t configType;
	IU32 flags;
	const char *usage;
	const char *defaultValue;
	lookupTable_t *lookupTable;
	const char *altKey;
	VDM_Error (*configCB)(VDM_UTL_Config_t *context,
		struct VDM_UTL_Config_cfg_t *cfg);
	VDM_UTL_Config_value_t value;
	VDM_UTL_Config_extCB_t *extCallBack;
} VDM_UTL_Config_cfg_t;

/*!
 ******************************************************************************
 * Allocates config context
 *
 * \return	Pointer to  VDM_UTL_Config_t , NULL otherwise
 ******************************************************************************
 */
extern VDM_UTL_Config_t *VDM_UTL_Config_create(void);

/*!
 ******************************************************************************
 * Set a configuration parameter. Use if you don't know the type, such as when
 * parsing the configuration file.
 *
 * \param	inContext	Configuration context
 * \param	key			Parameter name
 * \param	value		Value
 * \param	err			Output: VDM_ERR_OK on success, or a \ref VDM_Error value
 *
 * \return	TRUE on success, FALSE otherwise
 ******************************************************************************
 */
extern IBOOL VDM_UTL_Config_setValue(VDM_UTL_Config_t *inContext,
	const char *key, const char *value, VDM_Error *err);

/*!
 ******************************************************************************
 * Set a configuration string parameter.
 *
 * \param	inContext	Configuration context
 * \param	key			Parameter name
 * \param	value		Value
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_Error value
 ******************************************************************************
 */
extern VDM_Error VDM_UTL_Config_setStr(VDM_UTL_Config_t *inContext,
	const char *key, const char *value);

/*!
 ******************************************************************************
 * Get a configuration string parameter value.
 *
 * \param	inContext	Configuration context
 * \param	key			Parameter name
 *
 * \return	Value
 ******************************************************************************
 */
extern char *VDM_UTL_Config_getStr(VDM_UTL_Config_t *inContext,
	const char *key);

/*!
 ******************************************************************************
 * Set a configuration boolean parameter.
 *
 * \param	inContext	Configuration context
 * \param	key			Parameter name
 * \param	value		Value
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_Error value
 ******************************************************************************
 */
extern VDM_Error VDM_UTL_Config_setIBool(VDM_UTL_Config_t *inContext,
	const char *key, IBOOL value);

/*!
 ******************************************************************************
 * Get a configuration boolean parameter value.
 *
 * \param	inContext	Configuration context
 * \param	key			Parameter name
 *
 * \return	Value
 ******************************************************************************
 */
extern IBOOL VDM_UTL_Config_getIBool(VDM_UTL_Config_t *inContext,
	const char *key);

/*!
 ******************************************************************************
 * Set a configuration integer parameter.
 *
 * \param	inContext	Configuration context
 * \param	key			Parameter name
 * \param	value		Value
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_Error value
 ******************************************************************************
 */
extern VDM_Error VDM_UTL_Config_setIU32(VDM_UTL_Config_t *inContext,
	const char *key, IU32 value);

/*!
 ******************************************************************************
 * Get a configuration integer parameter value.
 *
 * \param	inContext	Configuration context
 * \param	key			Parameter name
 *
 * \return	Value
 ******************************************************************************
 */
extern IU32 VDM_UTL_Config_getIU32(VDM_UTL_Config_t *inContext,
	const char *key);

/*!
 ******************************************************************************
 * Set a configuration enumeration parameter value (an integer index).
 *
 * \param	inContext	Configuration context
 * \param	key			Parameter name
 * \param	value		Value
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_Error value
 ******************************************************************************
 */
extern VDM_Error VDM_UTL_Config_setEnum(VDM_UTL_Config_t *inContext,
	const char *key, IU32 value);

/*!
 ******************************************************************************
 * Get a configuration enumeration parameter value (an integer index).
 *
 * \param	inContext	Configuration context
 * \param	key			Parameter name
 *
 * \return	Value
 ******************************************************************************
 */
extern IU32 VDM_UTL_Config_getEnum(VDM_UTL_Config_t *inContext,
	const char *key);

/*!
 ******************************************************************************
 * Print usage information.
 *
 * \param	inContext			Configuration context
 * \param	inGroup				Configuration group
 * \param	inTitle				YEHUDA
 * \param	inPrintGroupPrefix	YEHUDA
 *
 * \return	None
 ******************************************************************************
 */
extern void VDM_UTL_Config_usage(VDM_UTL_Config_t *inContext,
	const char *inGroup, const char *inTitle, IBOOL inPrintGroupPrefix);

/*!
 ******************************************************************************
 * Dump configuration.
 *
 * \param	pContext	Configuration context
 *
 * \return	None
 ******************************************************************************
 */
extern void VDM_UTL_Config_dumpConfiguration(VDM_UTL_Config_t *pContext);

/*!
 ******************************************************************************
 * Print configuration to file.
 *
 * \param	pContext	Configuration context
 * \param	inPath		Path to file
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_Error value
 ******************************************************************************
 */
extern VDM_Error VDM_UTL_Config_printToFile(VDM_UTL_Config_t *pContext,
	const char *inPath);

/*!
 ******************************************************************************
 * Initialize configuration instance.
 *
 * \param	inMutex				Mutex.
 * \param	inIsEngineStartedCb	Indicate whether engine has been started.
 *
 * \return	None
 ******************************************************************************
 */
extern VDM_UTL_Config_t *VDM_UTL_Config_init(
	IBOOL (*inIsEngineStartedCb)(void));

IBOOL VDM_UTL_Config_isConfigLocked(VDM_UTL_Config_t *pContext);

/*!
 ******************************************************************************
 * Free content and terminate configuration instance.
 *
 * \param	pContext	Configuration context
 *
 * \return	None
 ******************************************************************************
 */
extern void VDM_UTL_Config_term(VDM_UTL_Config_t *pContext);

/*!
 ******************************************************************************
 * Add configuration.
 *
 * \param	inContext		Configuration context
 * \param	inGroup			Configuration group
 * \param	inKey			Key
 * \param	inConfigType	Configuration type
 * \param	inFlags			Configuration flags
 * \param	inUsage			Usage information
 * \param	inDefaultValue	Default value
 * \param	inLookupTable	Lookup table
 * \param	inAltKey		Alternative key
 * \param	inConfigCB		Callback to invoke
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_Error value
 ******************************************************************************
 */
extern VDM_Error VDM_UTL_Config_add(VDM_UTL_Config_t *inContext,
	const char *inGroup, const char *inKey, configType_t inConfigType,
	IU32 inFlags, const char *inUsage, const char *inDefaultValue,
	lookupTable_t *inLookupTable, const char *inAltKey,
	VDM_Error (*inConfigCB)(VDM_UTL_Config_t *context, VDM_UTL_Config_cfg_t *cfg));

/*!
 *******************************************************************************
 * Register a callback to be called when the the config parameter has changed.
 *
 * Note: Currently, the callback is triggered only for configuration settings
 * made via \ref VDM_UTL_Config_valueChanged.
 *
 * \param	pContext		Configuration context
 * \param	inFunc			The callback function
 * \param	inKey			Key
 * \param	inContext		The context to be passed to the call back when invoked.
 * \return	VDM_ERR_OK on success, or a \ref VDM_Error value
 *******************************************************************************
 */
extern VDM_Error VDM_UTL_Config_registerOnChange(VDM_UTL_Config_t *pContext,
	VDM_UTL_Config_onValueChangedCB inFunc, const char *inKey, void *inContext);

/*!
 *******************************************************************************
 * Unegister a callback to be called when the the config parameter has changed.
 *
 * Note: Currently, the callback is triggered only for configuration settings
 * made via \ref VDM_UTL_Config_valueChanged.
 *
 * \param	pContext		Configuration context
 * \param	inFunc			The callback function
 * \param	inKey			Key
 *
 * \return	The callback context
 *******************************************************************************
 */
void *VDM_UTL_Config_unregisterOnChange(VDM_UTL_Config_t *pContext,
	VDM_UTL_Config_onValueChangedCB inFunc, const char *inKey);

/*!
 *******************************************************************************
 * Request and notify about a configuration change.
 *
 * \see \ref VDM_UTL_Config_registerOnChange
 *
 * \param	pContext		Configuration context
 * \param	inCfg			The configuration to change,
 *                          a \ref VDM_UTL_Config_cfg_t type.
 * \param	inNewValue		The new value to set,
 *                          a \ref VDM_UTL_Config_value_t type.
 * \return	VDM_ERR_OK on success, or a \ref VDM_Error value
 *******************************************************************************
 */
extern VDM_Error VDM_UTL_Config_valueChanged(VDM_UTL_Config_t *pContext,
	VDM_UTL_Config_cfg_t *inCfg, VDM_UTL_Config_value_t inNewValue);

extern VDM_Error VDM_UTL_Config_getCfg(VDM_UTL_Config_t *pContext,
	const char *inKey, VDM_UTL_Config_cfg_t **cfg);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

