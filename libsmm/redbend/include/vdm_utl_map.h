/*
 *******************************************************************************
 *
 * vdm_utl_map.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_utl_map.h
 *
 * \brief	Map (Associative Array) API
 *******************************************************************************
 */

#ifndef VDM_UTL_MAP_H
#define VDM_UTL_MAP_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct VDM_UTL_Map_t VDM_UTL_Map_t;

/*!
 *******************************************************************************
 * Callback to compare two keys.
 *
 * \param	inKey1		First key
 * \param	inKey2		Second key
 * \param	inContext	Context passed previously to \ref VDM_UTL_Map_create
 *
 * \return	<0: \a inKey1 < \a inKey2,
 *			 0: \a inKey1 == \a inKey2,
 *			>0: \a inKey1 > \a inKey2
 *
 * \see VDM_UTL_Map_compareByStrKeysCB
 *******************************************************************************
 */
typedef IS32 (*VDM_UTL_Map_Compare_CB_t) (
	const void *inKey1,
	const void *inKey2,
	void *inContext);

/*!
 *******************************************************************************
 * Callback to free map items.
 *
 * This function should call \ref VDM_UTL_Map_freeItem.
 *
 * \param	inKey		Key
 * \param	inValue		Value
 * \param	inContext	Context passed previously to \ref VDM_UTL_Map_create
 *
 * \return	None
 *******************************************************************************
 */
typedef void (*VDM_UTL_Map_Free_CB_t) (void *inKey, void *inValue,
	void *inContext);

/*!
 *******************************************************************************
 * Free and nullify map items (using \ref VDM_PL_freeAndNullify).
 *
 * \param	inKey		Key
 * \param	inValue		Value
 * \param	inContext	Context passed previously to \ref VDM_UTL_Map_create;
 *						the context is actually ignored
 *
 * \return	None
 *******************************************************************************
 */
void VDM_UTL_Map_freeItem(void *inKey, void *inValue, void *inContext);

/*!
 *******************************************************************************
 * Create a map.
 *
 * \param	inCompareFunc			Callback invoked to compare two map items,
 *									a \ref VDM_UTL_Map_Compare_CB_t structure
 * \param	inFreeFunc				Callback invoked to free items,
 *									a \ref VDM_UTL_Map_Free_CB_t structure
 * \param	inFuncContext			Handle to pass to \a callback Functions
 * \param	inAllowDuplicates		Whether duplicate keys are allowed
 *
 * \return	Handle to the map on success, NULL otherwise
 *******************************************************************************
 */
extern VDM_UTL_Map_t *VDM_UTL_Map_create(VDM_UTL_Map_Compare_CB_t inCompareFunc,
	VDM_UTL_Map_Free_CB_t inFreeFunc, VDM_Handle_t inFuncContext,
	IBOOL inAllowDuplicates);

/*!
 *******************************************************************************
 * Destroy a map.
 *
 * \param	ioMap	Handle to the map
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_UTL_Map_destroy(VDM_UTL_Map_t **ioMap);

/*!
 *******************************************************************************
 * Add a new key-value pair to a map.
 *
 * \param	inMap		Handle to the map
 * \param	inKey		New key
 * \param	inValue		New value
 *
 * \return	VDM_ERR_OK on success, or VDM_ERR_MEMORY if there is a memory
 *			problem
 *******************************************************************************
 */
extern VDM_Error VDM_UTL_Map_add(VDM_UTL_Map_t *inMap, void *inKey,
	void *inValue);

extern VDM_Error VDM_UTL_Map_addOrReplace(
	VDM_Handle_t inMap,
	void *inKey,
	void *inValue);

/*!
 *******************************************************************************
 * Find the first item that matches a key in a map.
 *
 * \note Uses \ref VDM_UTL_Map_Compare_CB_t to compare values.
 *
 * \param	inMap		Handle to the map
 * \param	inKey		The key
 * \param	outValue	The returned value of the first matching key
 *
 * \return	TRUE if there's a matching key, FALSE otherwise
 *******************************************************************************
 */
extern IBOOL VDM_UTL_Map_find(VDM_UTL_Map_t *inMap, void *inKey,
	void **outValue);

/*!
 *******************************************************************************
 * Iteratively get key/value pairs.
 *
 * \param	inMap		Handle to the map
 * \param	ioIter		Iterator. Should be initialized with NULL
 * \param	outKey		The returned key
 * \param	outValue	The returned value
 *
 * \return	VDM_ERR_OK if it exists, VDM_ERR_OUT_OF_BOUNDS if map is empty
 *******************************************************************************
 */
extern VDM_Error VDM_UTL_Map_getNext(VDM_UTL_Map_t *inMap, VDM_Handle_t *ioIter,
	void **outKey, void **outValue);

/*!
 *******************************************************************************
 * Remove an item from a map, according to its key.
 *
 * \note Uses \ref VDM_UTL_Map_Free_CB_t to free and nullify memory.
 *
 * \param	inMap		Handle to the map
 * \param	inKey		The key
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_UTL_Map_removeItem(VDM_UTL_Map_t *inMap, void *inKey);

/*!
 *******************************************************************************
 * Remove all key/value pairs.
 *
 * \note Uses \ref VDM_UTL_Map_Free_CB_t to free and nullify memory.
 *
 * \param	inMap		Handle to the map
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_UTL_Map_removeAll(VDM_UTL_Map_t *inMap);

/*!
 *******************************************************************************
 * Get the number of items in a map.
 *
 * \param	inMap	Handle to the map
 *
 * \return	Number of items in the map
 *******************************************************************************
 */
extern IU32 VDM_UTL_Map_getSize(VDM_UTL_Map_t *inMap);

/*!
 *******************************************************************************
 * A pre-made \ref VDM_UTL_Map_Compare_CB_t function.
 *
 * This function performs a case-sensitive string-key comparison.
 *
 * \param	inKey1	Key of the first item to compare.
 * \param	inKey2	Key of the second item to compare.
 * \param	inContext	context supplied by client at map creation.
 *
 * \return	0 if keys are equal;
 *          Positive if (inKey1 > inKey2);
 *          Negative if (inKey1 < inKey2).
 *******************************************************************************
 */
IS32 VDM_UTL_Map_compareByStrKeysCB(const void *inKey1, const void *inKey2, void *inContext);

/*!
 *******************************************************************************
 * A pre-made \ref VDM_UTL_Map_Compare_CB_t function.
 *
 * This function performs a case-INsensitive string-key comparison.
 *
 * \param	inKey1	Key of the first item to compare
 * \param	inKey2	Key of the second item to compare
 * \param	inContext	context supplied by client at map creation.
 *
 * \return	0 if keys are equal;
 *          Positive if (inKey1 > inKey2);
 *          Negative if (inKey1 < inKey2).
 *******************************************************************************
 */
IS32 VDM_UTL_Map_caseCompareByStrKeysCB(const void *inKey1, const void *inKey2, void *inContext);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

