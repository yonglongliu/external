/*
 *******************************************************************************
 *
 * vdm_utl_persistentdata.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file    vdm_utl_persistentdata.h
 *
 * \brief   Persistent Storage API
 *******************************************************************************
 */

#ifndef _VDM_UTL_PERSISTENTDATA_H_
#define _VDM_UTL_PERSISTENTDATA_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define KEY_DELIMITER '\\'
#define VAL_DELIMITER '/'

typedef struct VDM_UTL_PersistentData_t  VDM_UTL_PersistentData_t;

/*!
 * Persistent storage data types. Used when invoking the compatibility
 * callbacks.
 *
 * When you invoke the callbacks, you invoke all callbacks registered for
 * a specific type of data. For example, all callbacks to update the DM Tree.
 */
typedef enum {
	E_VDM_PERSISTENT_UTL_DMTree = 0,    /**< DM Tree */
	E_VDM_PERSISTENT_UTL_Registry,      /**< Configuration file (not used by vDM) */
	E_VDM_PERSISTENT_UTL_InternalInfo, 	/**< Internal client storage used in downgrade*/
	E_VDM_PERSISTENT_UTL_DpCompatibility,      /**< DpCompatibility */
	E_VDM_PERSISTENT_UTL_Last = E_VDM_PERSISTENT_UTL_DpCompatibility     /**< The type of data that will be updated last. After this type of data is updated, the storage is flashed. */
} E_VDM_PERSISTENT_UTL_ItemType_t;

/*!
 * SMM persistent variable types.
 *
 * Used for converting single-instance machines data to multi-instance format.
 */
typedef enum {
	E_VDM_PERSISTENT_UTL_SMM_VAR_STATE = 0,
	E_VDM_PERSISTENT_UTL_SMM_VAR_INSTANCE,
	E_VDM_PERSISTENT_UTL_SMM_VAR_GLOBAL,
	E_VDM_PERSISTENT_UTL_SMM_VAR_DUAL,
	E_VDM_PERSISTENT_UTL_SMM_VAR_Last
} E_VDM_PERSISTENT_UTL_SMM_VarType_t;

/*!
 * Compatibility validation return options
 *
 * Used for informing the invoker if we are in upgrade or downgrade (doing nothing) mode, or error
 */
typedef enum {
    E_VDM_PERSISTENT_UTL_UPDATE_Type_notInitialized = 0,
    E_VDM_PERSISTENT_UTL_UPDATE_Type_upgrade,
    E_VDM_PERSISTENT_UTL_UPDATE_Type_downgrade,
    E_VDM_PERSISTENT_UTL_UPDATE_Type_sameVersion,
    E_VDM_PERSISTENT_UTL_UPDATE_Type_error,
} E_VDM_PERSISTENT_UTL_UPDATE_Type;

#define VERSION_ROOT "SOFTWARE\\RedBend"

/*!
 *******************************************************************************
 * Initialize persistent data.
 *
 * \param   outDataHandle   Handle to data read from a path within persistent
 *                          storage
 * \param   inRoot          The path within persistent storage where the data
 *                          is stored
 * \param   inKey           The key<br>
 *                          The key is concatenated to \a inRoot to create the
 *                          full path to the storage item.
 * \param   inType   The persisntent storage type
 *
 * \return  VDM_ERR_OK on success,
 *          VDM_ERR_MEMORY if no memory to perform action, or
 *          VDM_ERR_MO_STORAGE if error accessing persistent storage
 *******************************************************************************
 */
VDM_Error VDM_UTL_PersistentData_init(VDM_UTL_PersistentData_t **outDataHandle,
	const char *inRoot, const char *inKey, E_VDM_PERSISTENT_UTL_ItemType_t inType);

/*!
 *******************************************************************************
 * Commit data to the persistent storage.
 *
 * \param   inDataHandle     Handle to the persistent data object
 *
 * \return  VDM_ERR_OK on success, or
 *      VDM_ERR_MO_STORAGE if error creating persistent storage file
 *******************************************************************************
 */
VDM_Error VDM_UTL_PersistentData_commit(VDM_UTL_PersistentData_t *ioDataHandle);

/// @cond EXCLUDE
/*
 *******************************************************************************
 * Internal. Do not use.
 *******************************************************************************
 */
VDM_Error VDM_UTL_PersistentData_globalCommit(E_VDM_PERSISTENT_UTL_ItemType_t inType);

/// @endcond

/*!
 *******************************************************************************
 * Close the handle to the persistent data object, and optionally commit the
 * data to persistent storage.
 *
 * \param   i0DataHandle    Input: Handle to the persistent data object;
 *                          Output: NULL
 * \param   inCommit        True to commit changes to persistent storage, False
 *                          otherwise
 *
 * \return None
 *******************************************************************************
 */
void VDM_UTL_PersistentData_term(VDM_UTL_PersistentData_t **ioDataHandle, IBOOL inCommit);

/*!
 *******************************************************************************
 * Delete a handler that was created with \ref VDM_UTL_PersistentData_init. This
 * deletes the handler and all of its sub-keys from persistent storage.
 *
 * \param	inDataHandle	 Handle to the data object
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_MO_STORAGE if error accessing persistent storage
 *******************************************************************************
 */
VDM_Error VDM_UTL_PersistentData_deleteKey(VDM_UTL_PersistentData_t *inDataHandle);

/*!
 *******************************************************************************
 * Write string to persistent data object.
 *
 * \param   inDataHandle    Handle to the persistent data object
 * \param   inKey           The key
 * \param   inStringValue   The string to store
 *
 * \return  VDM_ERR_OK on success, or
 *          VDM_ERR_FUMO_STORAGE if error accessing persistent storage
 *******************************************************************************
 */
VDM_Error VDM_UTL_PersistentData_writeString(VDM_UTL_PersistentData_t *inDataHandle,
	const char *inKey, const char *inStringValue);

/*!
 *******************************************************************************
 * Read string from persistent data object.
 *
 * \param   inDataHandle        Handle to the persistent data object
 * \param   inKey               The key
 * \param   outValueBuffer      Pre-allocated buffer to store the string
 * \param   ioLengthValueBuffer Input: \a outValueBuffer length;
 *                              Output: Length of result string
 *
 * \return  VDM_ERR_OK on success,
 *          VDM_ERR_MO_STORAGE if error accessing persistent storage
 *          VDM_ERR_NODE_MISSING if key was not found
 *******************************************************************************
 */
VDM_Error VDM_UTL_PersistentData_readString(VDM_UTL_PersistentData_t *inDataHandle,
	const char *inKey, char *outValueBuffer, IU32 *ioLengthValueBuffer);

/*!
 *******************************************************************************
 * Write an integer to persistent data object.
 *
 * \param   inDataHandle    Handle to the persistent data object
 * \param   inKey           The key
 * \param   inIntValue      The integer to store
 *
 * \return  VDM_ERR_OK on success, or
 *          VDM_ERR_MO_STORAGE if error accessing persistent storage
 *******************************************************************************
 */
VDM_Error VDM_UTL_PersistentData_writeInt(VDM_UTL_PersistentData_t *inDataHandle,
	const char *inKey, IU32 inIntValue);

/*!
 *******************************************************************************
 * Write an 64-bit integer to persistent data object.
 *
 * \param   inDataHandle    Handle to the persistent data object
 * \param   inKey           The key
 * \param   inIntValue      The unsigned long long int to store
 *
 * \return  VDM_ERR_OK on success, or
 *          VDM_ERR_MO_STORAGE if error accessing persistent storage
 *******************************************************************************
 */
VDM_Error VDM_UTL_PersistentData_writeInt64(
	VDM_UTL_PersistentData_t *inDataHandle, const char *inKey, IU64 inIntValue);

/*!
 *******************************************************************************
 * Read an integer from persistent data object.
 *
 * \param   inDataHandle    Handle to the persistent data object
 * \param   inKey           The key
 * \param   outIntValue     The stored integer value
 *
 * \return  VDM_ERR_OK on success, or
 *          VDM_ERR_MO_STORAGE if error accessing persistent storage
 *          VDM_ERR_NODE_MISSING if key was not found
 *******************************************************************************
 */
VDM_Error VDM_UTL_PersistentData_readInt(VDM_UTL_PersistentData_t *inDataHandle,
	const char *inKey, IU32 *outIntValue);

/*!
 *******************************************************************************
 * Read an 64-bit integer from persistent data object.
 *
 * \param   inDataHandle    Handle to the persistent data object
 * \param   inKey           The key
 * \param   outIntValue     The stored long long unsigned int value
 *
 * \return  VDM_ERR_OK on success, or
 *          VDM_ERR_MO_STORAGE if error accessing persistent storage
 *          VDM_ERR_NODE_MISSING if key was not found
 *******************************************************************************
 */
VDM_Error VDM_UTL_PersistentData_readInt64(VDM_UTL_PersistentData_t *inDataHandle,
	const char *inKey, IU64 *outIntValue);

/*!
 *******************************************************************************
 * Write binary data to persistent data object.
 *
 * \param   inDataHandle    Handle to the persistent data object
 * \param   inKey           The key
 * \param   inBinValue      The binary data to store
 * \param   inLen           inBinValue length
 *
 * \return  VDM_ERR_OK on success, or
 *          VDM_ERR_FUMO_STORAGE if error accessing persistent storage
 *******************************************************************************
 */
VDM_Error VDM_UTL_PersistentData_writeBin(VDM_UTL_PersistentData_t *inDataHandle,
	const char *inKey, IU8 *inBinValue, IU32 inLen);

/*!
 *******************************************************************************
 * Read binary data from persistent data object.
 *
 * \param   inDataHandle        Handle to the persistent data object
 * \param   inKey               The key
 * \param   outValueBuffer      Pre-allocated buffer to store the binary data
 * \param   ioLengthValueBuffer Input: \a outValueBuffer length;
 *                              Output: Length of result binary data
 *
 * \return  VDM_ERR_OK on success,
 *          VDM_ERR_MO_STORAGE if error accessing persistent storage
 *          VDM_ERR_NODE_MISSING if key was not found
 *******************************************************************************
 */
VDM_Error VDM_UTL_PersistentData_readBin(VDM_UTL_PersistentData_t *inDataHandle,
	const char *inKey, IU8 *outValueBuffer, IU32 *ioLengthValueBuffer);

/**
 *******************************************************************************
 * Delete an item from persistent storage.
 *
 * \param	inDataHandle	Handle to the data in persistent storage
 * \param	inKey			The key of the item to delete
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_MO_STORAGE if error accessing persistent storage
 *******************************************************************************
 */
VDM_Error VDM_UTL_PersistentData_deleteItem(VDM_UTL_PersistentData_t *inDataHandle,
	const char *inKey);

/// @cond EXCLUDE

/*
 *******************************************************************************
 * Destroy all persistent data objects. Internal.
 *******************************************************************************
 */
void VDM_UTL_PersistentData_destroy(void);

/// @endcond

/*!
 *******************************************************************************
 * Set the current version of OMA DM Protocol Engine. Call this at startup, after
 * registering the callback using \ref VDM_UTL_PersistentData_compatRegister and
 * before calling \ref VDM_UTL_PersistentData_init.
 *
 * \param   inCurrentVersion        Current OMA DM Protocol Engine version.
 *******************************************************************************
 */
void VDM_UTL_PersistentData_compatInit(char *inCurrentVersion);

/*!
 *******************************************************************************
 * Callback invoked to convert the old persistent storage items to the new
 * format, as required. Each will be invoked only once, the first time that the
 * new version of OMA DM Protocol Engine is run. Each callback is associated with a
 * specific type of data.
 *
 * \param	inType				The data type, an
 *								\ref E_VDM_PERSISTENT_UTL_ItemType_t value
 *******************************************************************************
 */
typedef void (*VDM_UTL_PersistentData_compatCodeCB_t)(E_VDM_PERSISTENT_UTL_ItemType_t inType);

#define COMMIT_PS "RedBend-vdm-99.99"

/*!
 *******************************************************************************
 * Register the above callback. You can register multiple callbacks for
 * different versions.
 *
 * \param   inOlderThanVersion      Version number. The callback will be invoked
 *                                  if the old version of OMA DM Protocol Engine is this
 *                                  number or earlier.
 *                                  Pass COMMIT_PS to commit to persistent
 *                                  storage (last callback)
 * \param   inCb                    Callback to invoke.
 *
 * \return  VDM_ERR_OK on success,
 *          VDM_ERR_MEMORY on memory allocation errors,
 *          VDM_ERR_INVALID_CALL on invalid arguments
 *******************************************************************************
 */
VDM_Error VDM_UTL_PersistentData_compatRegister(const char *inOlderThanVersion,
	VDM_UTL_PersistentData_compatCodeCB_t inCb);

/*!
 *******************************************************************************
 * Invoke all callbacks registered for the specified type of data. Called in
 * \ref VDM_create (for registry data) and at the end of \ref VDM_start (for DM
 * Tree data).
 *
 * \return  VDM_ERR_OK on success,
 *          VDM_ERR_MEMORY on memory allocation errors,
 *          VDM_ERR_BAD_INPUT_on invalid arguments
 *******************************************************************************
 */
VDM_Error VDM_UTL_PersistentData_runCb(E_VDM_PERSISTENT_UTL_ItemType_t inType);

typedef struct VDM_UTL_PersistentData_subKey_t {
	struct VDM_UTL_PersistentData_subKey_t *next;
	char *subKeyVal;
} VDM_UTL_PersistentData_subKey_t;

/*!
 *******************************************************************************
 * Release memory of subkey.
 *
 * \param	inSubKey		subkey to release
 *
 * \return  None
 *
 *******************************************************************************
 */
void VDM_UTL_PersistentData_freeSubKeys(VDM_UTL_PersistentData_subKey_t **inSubKey);

/*!
 *******************************************************************************
 * Find all sub keys under main key.
 *
 * \param	inDataHandle	Handle to the data in persistent storage
 * \param	inKeyPrefix		The main key
 *
 * \return  list of all sub keys (names only, no values)
 *
 * Note: Returned list is allocated by this function, and should be freed by
 * the calling function using VDM_UTL_PersistentData_freeSubKeys.
 *******************************************************************************
 */
VDM_UTL_PersistentData_subKey_t *VDM_UTL_PersistentData_getSubKeys(
	VDM_UTL_PersistentData_t *inDataHandle, const char *inKeyPrefix);

/*!
 *******************************************************************************
 * Find all names in name-value-pair values under given key.
 *
 * \param	inDataHandle	Handle to the data in persistent storage
 * \param	inKeyPrefix		The main key
 *
 * \return  list of all names in name-value-pair values under given key.
 *
 * Note: Returned list is allocated by this function, and should be freed by
 * the calling function using VDM_UTL_PersistentData_freeSubKeys.
 *******************************************************************************
 */
VDM_UTL_PersistentData_subKey_t *VDM_UTL_PersistentData_getValueNames(
	VDM_UTL_PersistentData_t *inDataHandle, const char *inKeyPrefix);

/*!
 *******************************************************************************
 * build PS key by concatenating the value to the key using given delimiter.
 *
 * \param	outBuf		The out buffer into which the generated key is saved.
 * \param	inSize		The outBuf size
 * \param	inKey		The key
 * \param	inValue		The value to concatenate to the key
 * \param   inDelimiter	Delimiter to separate between key and value
 *
 * \return  VDM_ERR_OK on success,
 *          VDM_ERR_REGISTRY otherwise,
 *******************************************************************************
 */
VDM_Error VDM_UTL_PersistentData_buildKey(char *outBuf, IU32 inSize, const char *inKey,
	const char *inValue, const char inDelimiter);

/**
 * After this call reg.conf will not be store in PS until restart
 * or /ref enableSavingToPs is called.
 */
void disableSavingToPs(void);

/**
 * Enable saving to PS (After /ref disableSavingToPs was called)
 */
void enableSavingToPs(void);

/**
 * Returns if client is in upgrade or downgrade or nothing to do mode.
*/

E_VDM_PERSISTENT_UTL_UPDATE_Type VDM_UTL_PersistentData_getUpdateType(void);

/*!
 *******************************************************************************
 * Check whether client is in downgrade mode
 *******************************************************************************
 */
IBOOL VDM_UTL_PersistentData_isInDowngradeMode(void);

/**
 * Update client version saved in ps
 *
 * \return  VDM_ERR_OK on success,
*/
VDM_Error VDM_UTL_PersistentData_updateClientVersion(void);

/*!
 *******************************************************************************
 * register crypt info to specific persistent data type
 *
 * \param   inType             In persistent storage type
 * \param   inEncryptFunc      In encryption function
 * \param   inDecryptFunc      In decryption function
 * \param   inCtx          	   In encryption context
 *
 * \return  VDM_ERR_OK on success,
              otherwise, VDM_ERR_BAD_INPUT, VDM_ERR_MEMORY
 *******************************************************************************
 */
VDM_Error VDM_UTL_PersistentData_registerCryptInfo(
		E_VDM_PERSISTENT_UTL_ItemType_t inType,
        VDM_encryptCB inEncryptFunc,
        VDM_decryptCB inDecryptFunc,
        void *inCtx);

/*!
 *******************************************************************************
 * un register crypt info to specific persistent data type
 *
 * \param   inType             In persistent storage type
 *
 * None
 *******************************************************************************
 */

void VDM_UTL_PersistentData_unRegisterCryptInfo(
        E_VDM_PERSISTENT_UTL_ItemType_t inType);

/*!
 *******************************************************************************
 * check whether the persistent data type is using crypt
 *
 * \param   inType             In persistent storage type
 *
 * TRUE or FALSE
 *******************************************************************************
 */

IBOOL VDM_UTL_PersistentData_isCryptExists(
        E_VDM_PERSISTENT_UTL_ItemType_t inType);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  //_VDM_UTL_PERSISTENTDATA_H_
