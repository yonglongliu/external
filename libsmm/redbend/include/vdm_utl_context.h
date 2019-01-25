/*
 *******************************************************************************
 *
 * vdm_utl_context.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_utl_context.h
 *
 * \brief	Component Context API
 *******************************************************************************
 */
#ifndef VDM_UTL_CONTEXT_H
#define VDM_UTL_CONTEXT_H

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 *******************************************************************************
 * Create context for a component.
 *
 * \param	inId	Component id
 * \param	inSize	Size of context to allocate
 *
 * \return	VDM_ERR_OK on success, VDM_ERR_MEMORY if there is not enough memory,
 *			or VDM_ERR_INVALID_CALL if a context was already allocated for this
 *			component
 *******************************************************************************
 */
extern VDM_Error VDM_UTL_Context_create(IS32 inId, IU32 inSize);

/*!
 *******************************************************************************
 * Insert a pre-allocated context for a component.
 *
 * \param	inId		Component id
 * \param	inData		The context to insert
 *
 * \return	VDM_ERR_OK on success, VDM_ERR_MEMORY if there is not enough memory,
 *			or VDM_ERR_INVALID_CALL if a context was already allocated for this
 *			component
 *******************************************************************************
 */
VDM_Error VDM_UTL_Context_set(IS32 inId, void *inData);

/*!
 *******************************************************************************
 * Get the context of a component.
 *
 * \param	inId	Component id
 *
 * \return	Component context, which may be NULL
 *******************************************************************************
 */
extern void *VDM_UTL_Context_get(IS32 inId);

/*!
 *******************************************************************************
 * Destroy the context of a component.
 * It is the responsibility of the caller to free any members of the component
 * context object.
 *
 * \param	inId	Component id
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_UTL_Context_destroy(IS32 inId);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

