/*
 *******************************************************************************
 *
 * vdm_smm_valuelist.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file vdm_smm_valuelist.h
 *
 * \brief A linked list of SMM Values API
 *******************************************************************************
 */

#ifndef VDM_SMM_VALUELIST_H_    //!< Internal.
#define VDM_SMM_VALUELIST_H_

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *******************************************************************************
 * Add an integer value to the head of a linked list of SMM values.
 *
 * \param	ioValueList		Input: A reference to the linked list or NULL
 *                          Output: A reference to the linked list with the
 *                          new value at the head of the list if the operation
 *                          was successful, or the list unchanged if there was
 *                          an error.
 * \param	inName		A name associated with the value.
 * \param	inValue		Integer value.
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_MEMORY VDM_ERR_MEMORY if out of memory
 *******************************************************************************
 */
VDM_Error VDM_SMM_ValueList_addIntValue(VDM_SMM_Value_t **ioValueList,
	char *inName, IS32 inValue);

/*!
 *******************************************************************************
 * Add an unsinged integer value to the head of a linked list of SMM values.
 *
 * \param	ioValueList		Input: A reference to the linked list or NULL
 *                          Output: A reference to the linked list with the
 *                          new value at the head of the list if the operation
 *                          was successful, or the list unchanged if there was
 *                          an error.
 * \param	inName		A name associated with the value.
 * \param	inValue		Unsigned integer value.
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_MEMORY VDM_ERR_MEMORY if out of memory
 *******************************************************************************
 */
VDM_Error VDM_SMM_ValueList_addUintValue(VDM_SMM_Value_t **ioValueList,
	char *inName, IU32 inValue);

/*!
 *******************************************************************************
 * Add an unsinged 64 bit integer value to the head of a linked list of SMM values.
 *
 * \param	ioValueList		Input: A reference to the linked list or NULL
 *                          Output: A reference to the linked list with the
 *                          new value at the head of the list if the operation
 *                          was successful, or the list unchanged if there was
 *                          an error.
 * \param	inName		A name associated with the value.
 * \param	inValue		Unsigned 64 bit integer value.
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_MEMORY VDM_ERR_MEMORY if out of memory
 *******************************************************************************
 */
VDM_Error VDM_SMM_ValueList_addUint64Value(VDM_SMM_Value_t **ioValueList,
	char *inName, IU64 inValue);

/*!
 *******************************************************************************
 * Add a string value to the head of a linked list of SMM values.
 *
 * \param	ioValueList		Input: A reference to the linked list or NULL
 *                          Output: A reference to the linked list with the
 *                          new value at the head of the list if the operation
 *                          was successful, or the list unchanged if there was
 *                          an error.
 * \param	inName		A name associated with the value.
 * \param	inValue		String value.
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_MEMORY VDM_ERR_MEMORY if out of memory
 *******************************************************************************
 */
VDM_Error VDM_SMM_ValueList_addStrValue(VDM_SMM_Value_t **ioValueList,
	char *inName, char *inValue);

/*!
 *******************************************************************************
 * Add a binary value to the head of a linked list of SMM values.
 *
 * \param	ioValueList		Input: A reference to the linked list or NULL
 *                          Output: A reference to the linked list with the
 *                          new value at the head of the list if the operation
 *                          was successful, or the list unchanged if there was
 *                          an error.
 * \param	inName		A name associated with the value.
 * \param	inValue		Binarry buffer.
 * \param	inSize		Size of \a inValue buffer.
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_MEMORY VDM_ERR_MEMORY if out of memory
 *******************************************************************************
 */
VDM_Error VDM_SMM_ValueList_addBinValue(VDM_SMM_Value_t **ioValueList,
	char *inName, void *inValue, IU32 inSize);

/*!
 *******************************************************************************
 * Destroy linked list of SMM values. Free any memory allocated for the values.
 *
 * \param	ioValueList		Input: Pointer to the linked list
 *	                        Output: NULL
 *
 *******************************************************************************
 */
void VDM_SMM_ValueList_destroy(VDM_SMM_Value_t **ioValueList);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // VDM_SMM_VALUELIST_H_
