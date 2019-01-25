/*
 *******************************************************************************
 *
 * vdm_utl_dynarray.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_utl_dynarray.h
 *
 * \brief	Dynamic Array Manipulation API
 *******************************************************************************
 */

#ifndef VDM_UTL_DYNARRAY_H
#define VDM_UTL_DYNARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <vdm_error.h>

/*!
 * Dynamic array
 */
typedef struct {
	IU32 capacity;      //!< "Private" member - for internal use
	IU32 size;          /*!< Number of items in the array; actually, the highest
	                       index containing a value + 1 */
	void **items;       //!< Items buffer
} VDM_UTL_DynArray_t;

/*!
 *******************************************************************************
 * Create a dynamic array of default size and set all items to NULL.
 *
 * \return	Pointer to the dynamic array, a \ref VDM_UTL_DynArray_t structure
 *******************************************************************************
 */
extern VDM_UTL_DynArray_t *VDM_UTL_DynArray_create(void);

/*!
 *******************************************************************************
 * Destroy a dynamic array. Free any memory allocated for the array.
 *
 * \param	inArray		Pointer to the dynamic array, a \ref VDM_UTL_DynArray_t
 *						structure
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_UTL_DynArray_destroy(VDM_UTL_DynArray_t *inArray);

/*!
 *******************************************************************************
 * Set a dynamic array item. If necessary, the array buffer is allocated or
 * re-allocated so that it can accommodate the item.
 *
 * \param	inArray		Pointer to the dynamic array, a \ref VDM_UTL_DynArray_t
 *						structure
 * \param	inIndex		Item index
 * \param	inData		Item data
 *
 * \return	VDM_ERR_OK on success, or VDM_ERR_MEMORY if the system is out of
 *			memory
 *******************************************************************************
 */
extern VDM_Error VDM_UTL_DynArray_setItem(
	VDM_UTL_DynArray_t *inArray,
	IU32 inIndex,
	void *inData);

/*!
 *******************************************************************************
 * Get a dynamic array item.
 *
 * \param	inArray		Pointer to the dynamic array, a \ref VDM_UTL_DynArray_t
 *						structure
 * \param	inIndex		Item index
 *
 * \return	A pointer to the item data, or NULL if not found
 *******************************************************************************
 */
extern void *VDM_UTL_DynArray_getItem(
	VDM_UTL_DynArray_t *inArray,
	IU32 inIndex);

/*!
 *******************************************************************************
 * Remove a dynamic array item. The value of the item is set to NULL.  The size
 * of the array is decremented, if required.
 *
 * \note	The item's data is not freed from memory.
 *
 * \param	inArray		Pointer to the dynamic array, a \ref VDM_UTL_DynArray_t
 *						structure
 * \param	inIndex		Item index
 *
 * \return	A pointer to the item data, or NULL if not found
 *******************************************************************************
 */
extern void *VDM_UTL_DynArray_removeItem(
	VDM_UTL_DynArray_t *inArray,
	IU32 inIndex);

/*!
 *******************************************************************************
 * Append an item to the end of a dynamic array.
 *
 * \note	The item is added to the index numbered one greater than the highest
 *			index containing a value. Empty indices are skipped.
 *
 * \param	inArray		Pointer to the dynamic array, a \ref VDM_UTL_DynArray_t
 *						structure
 * \param	inData		Item data
 *
 * \return	Item index, or -1 on error
 *******************************************************************************
 */
extern IS32 VDM_UTL_DynArray_appendItem(
	VDM_UTL_DynArray_t *inArray,
	void *inData);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

