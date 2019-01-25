/*
 *******************************************************************************
 *
 * vdm_scomo_pl_inventory.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_scomo_pl_inventory.h
 *
 * \brief	SCOMO Inventory APIs
 ******************************************************************************
 */
#ifndef _VDM_SCOMO_PL_INVENTORY_H_
#define _VDM_SCOMO_PL_INVENTORY_H_

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *******************************************************************************
 * Get component id. The id is initially the same as the identification
 * string, but may have been changed.
 *
 * \param	inCompId	Component id
 * \param	outBuffer	Pre-allocated result buffer for the component id
 * \param	ioLength	Input: Size of the result buffer;
 *						Output: Length of data in the result buffer
 *
 * \note	If the supplied buffer is too short, then as much data as will fit in
 *			the buffer is returned along with the error code
 *			VDM_ERR_BUFFER_OVERFLOW.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BUFFER_OVERFLOW if the supplied buffer was too short,
 *			or a \ref VDM_ERR_defs error code
 ******************************************************************************
 */

extern VDM_Error VDM_SCOMO_PL_INV_getComponentId(
	const char *inCompId,
	char *outBuffer,
	IU32 *ioLength);

/*!
 *******************************************************************************
 * Set component id.
 *
 * \param	inComp	    Component name
 * \param	inCompID	Component id
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 ******************************************************************************
 */
extern VDM_Error VDM_SCOMO_PL_INV_setComponentId(
	const char *inComp,
	const char *inCompID);

/*!
 *******************************************************************************
 * Get component name.
 *
 * \param	inCompId	Component id
 * \param	outBuffer	Pre-allocated result buffer for the component name
 * \param	ioLength	Input: Size of the result buffer;
 *						Output: Length of data in the result buffer
 *
 * \note	If the supplied buffer is too short, then as much data as will fit in
 *			the buffer is returned along with the error code
 *			VDM_ERR_BUFFER_OVERFLOW.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BUFFER_OVERFLOW if the supplied buffer was too short,
 *			or a \ref VDM_ERR_defs error code
 ******************************************************************************
 */
extern VDM_Error VDM_SCOMO_PL_INV_getComponentName(
	const char *inCompId,
	char *outBuffer,
	IU32 *ioLength);

/*!
 *******************************************************************************
 * Set component name.
 *
 * \param	inCompID    Component id
 * \param	inCompName	Component name
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 ******************************************************************************
 */
extern VDM_Error VDM_SCOMO_PL_INV_setComponentName(
	const char *inCompID,
	const char *inCompName);

/*!
 *******************************************************************************
 * Set component version.
 *
 * \param	inCompId    Component id
 * \param	inVersion	Component version
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 ******************************************************************************
 */
extern VDM_Error VDM_SCOMO_PL_INV_setComponentVersion(
	const char *inCompId,
	const char *inVersion);

/*!
 *******************************************************************************
 * Get component tool version.
 *
 * \param	inCompId	Component id
 * \param	outBuffer	Pre-allocated result buffer for the component version
 * \param	ioLength	Input: Size of the result buffer;
 *						Output: Length of data in the result buffer
 *
 * \note	If the supplied buffer is too short then, as much data as will fit in
 *			the buffer is returned along with the error code
 *			VDM_ERR_BUFFER_OVERFLOW.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BUFFER_OVERFLOW if the supplied buffer was too short,
 *			or a \ref VDM_ERR_defs error code
 ******************************************************************************
 */
extern VDM_Error VDM_SCOMO_PL_INV_getComponentVersion(
	const char *inCompId,
	char *outBuffer,
	IU32 *ioLength);

/*!
 *******************************************************************************
 * Get component state.
 *
 * \param	inCompId	Component id
 * \param	outState	Component state: active or inactive, an
 *						\ref E_VDM_SCOMO_COMPONENT_STATE_t value
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 ******************************************************************************
 */
extern VDM_Error VDM_SCOMO_PL_INV_getComponentState(
	const char *inCompId,
	E_VDM_SCOMO_COMPONENT_STATE_t *outState);

/*!
 *******************************************************************************
 * Set component state.
 *
 * \param	inCompId    Component id
 * \param	inState		Component state: active or inactive, an
 *						\ref E_VDM_SCOMO_COMPONENT_STATE_t value
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 ******************************************************************************
 */
extern VDM_Error VDM_SCOMO_PL_INV_setComponentState(
	const char *inCompId,
	E_VDM_SCOMO_COMPONENT_STATE_t inState);

/*!
 *******************************************************************************
 * Get component environment type.
 *
 * \param	inCompId    Component id
 * \param	outBuffer	Pre-allocated result buffer for the environment type
 * \param	ioLength	Input: Size of the result buffer;
 *						Output: Length of data in the result buffer
 *
 * \note	If the supplied buffer is too short, then as much data as will fit in
 *			the buffer is returned along with the error code
 *			\ref VDM_ERR_BUFFER_OVERFLOW.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BUFFER_OVERFLOW if the supplied buffer was too short,
 *			or a \ref VDM_ERR_defs error code
 ******************************************************************************
 */
extern VDM_Error VDM_SCOMO_PL_INV_getComponentEnvType(
	const char *inCompId,
	char *outBuffer,
	IU32 *ioLength);

/*!
 *******************************************************************************
 * Set component environment type.
 *
 * \param	inCompId    Component id
 * \param	inEnvType	Component environment type
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 ******************************************************************************
 */
extern VDM_Error VDM_SCOMO_PL_INV_setComponentEnvType(
	const char *inCompId,
	const char *inEnvType);

/*!
 *******************************************************************************
 * Get component description.
 *
 * \param	inCompId    Component id
 * \param	outBuffer	Pre-allocated result buffer for the description
 * \param	ioLength	Input: Size of the result buffer;
 *						Output: Length of data in the result buffer
 *
 * \note		If the supplied buffer is too short, then as much data as will fit in
 *			the buffer is returned along with the error code
 *			\ref VDM_ERR_BUFFER_OVERFLOW.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BUFFER_OVERFLOW if the supplied buffer was too short,
 *			or a \ref VDM_ERR_defs error code
 ******************************************************************************
 */
extern VDM_Error VDM_SCOMO_PL_INV_getComponentDescription(
	const char *inCompId,
	char *outBuffer,
	IU32 *ioLength);

/*!
 *******************************************************************************
 * Set component description.
 *
 * \param	inCompId        Component id
 * \param	inDescription	Component description
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 ******************************************************************************
 */
extern VDM_Error VDM_SCOMO_PL_INV_setComponentDescription(
    const char *inCompId,
    const char *inDescription);

/*!
 *******************************************************************************
 * Add component to the inventory.
 *
 * \param	inCompId			Component id
 * \param	inCompName			Component name
 * \param	inCompVersion		Component version
 * \param	inCompEnv			Component environment type
 * \param	inCompDesc			Component description
 * \param	inCompState			Component state: active or inactive, an
 *								\ref E_VDM_SCOMO_COMPONENT_STATE_t value
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 ******************************************************************************
 */
extern VDM_Error VDM_SCOMO_PL_INV_addComponent(
        const char *inCompId,
	const char *inCompName,
	const char *inCompVersion,
	const char *inCompEnv,
	const char *inCompDesc,
	E_VDM_SCOMO_COMPONENT_STATE_t inCompState);

/*!
 *******************************************************************************
 * Delete component from the inventory.
 *
 * \param	inCompId	Component id
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 ******************************************************************************
 */
extern VDM_Error VDM_SCOMO_PL_INV_deleteComponent(
	const char *inCompId);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

