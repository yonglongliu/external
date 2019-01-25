/*
 *******************************************************************************
 *
 * vdm_smm_value.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file vdm_smm_value.h
 *
 * \brief SMM Value API
 *******************************************************************************
 */

#ifndef VDM_SMM_VALUE_H_    //!< Internal.
#define VDM_SMM_VALUE_H_

#ifdef __cplusplus
extern "C" {
#endif

/*!
 ******************************************************************************
 *	Create and initialize an SMM integer value.
 *
 * \param	inName		A name associated with the value.
 * \param	inValue		Integer value.
 *
 * \return	Pointer to the value, a \ref VDM_SMM_Value_t structure or NULL
 *          if out of memory.
 ******************************************************************************
 */
VDM_SMM_Value_t *VDM_SMM_Value_createInt(char *inName, IS32 inValue);

/*!
 ******************************************************************************
 *	Create and initialize an SMM unsigned integer value.
 *
 * \param	inName		A name associated with the value.
 * \param	inValue		Unsigned integer value.
 *
 * \return	Pointer to the value, a \ref VDM_SMM_Value_t structure or NULL
 *          if out of memory.
 ******************************************************************************
 */
VDM_SMM_Value_t *VDM_SMM_Value_createUint(char *inName, IU32 inValue);

/*!
 ******************************************************************************
 *	Create and initialize an SMM unsigned integer value.
 *
 * \param	inName		A name associated with the value.
 * \param	inValue		Unsigned 64bit integer value.
 *
 * \return	Pointer to the value, a \ref VDM_SMM_Value_t structure or NULL
 *          if out of memory.
 ******************************************************************************
 */
VDM_SMM_Value_t *VDM_SMM_Value_createUint64(char *inName, IU64 inValue);

/*!
 ******************************************************************************
 *	Create and initialize an SMM string value.
 *
 * \param	inName		A name associated with the value.
 * \param	inValue		String value.
 *
 * \return	Pointer to the value, a \ref VDM_SMM_Value_t structure or NULL
 *          if out of memory.
 ******************************************************************************
 */
VDM_SMM_Value_t *VDM_SMM_Value_createStr(char *inName, char *inValue);

/*!
 ******************************************************************************
 *	Create and initialize an SMM binary value.
 *
 * \param	inName		A name associated with the value.
 * \param	inValue		Binarry buffer.
 * \param	inSize		Size of \a inValue buffer.
 *
 * \return	Pointer to the value, a \ref VDM_SMM_Value_t structure or NULL
 *          if out of memory.
 ******************************************************************************
 */
VDM_SMM_Value_t *VDM_SMM_Value_createBin(char *inName, void *inValue,
	IU32 inSize);

/*!
 *******************************************************************************
 * Destroy an SMM value. Free any memory allocated for the value.
 *
 * \param	ioValue		Input: Pointer to the value
 *                      Output: NULL
 *
 * \return	None
 *******************************************************************************
 */
void VDM_SMM_Value_destroy(VDM_SMM_Value_t **ioValue);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // VDM_SMM_VALUE_H_
