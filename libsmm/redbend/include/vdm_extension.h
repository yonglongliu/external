/*
 *******************************************************************************
 *
 * vdm_extension.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_extension.h
 *
 * \brief	Extension API
 *
 * The extension invokes internal Engine APIs.
 *******************************************************************************
 */

/*! \addtogroup VDM_EXTENSION
 * @{
 */

#ifndef _VDM_EXTENSION_H_
#define _VDM_EXTENSION_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 *******************************************************************************
 * Initialize the Engine.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*initCB_t)(void);

/*!
 *******************************************************************************
 * Run the Engine.
 *
 * \param	inTriggerData	The reason for the activation
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*runCB_t)(RDM_TRG_Data *inTriggerData);

/*!
 *******************************************************************************
 * Terminate the Engine.
 *
 * \return	None
 *******************************************************************************
 */
typedef void (*termCB_t)(void);

/*!
 * Extension callbacks
 */
typedef struct {
	initCB_t init;      //!< Initialize the Engine
	runCB_t run;        //!< Run the Engine
	termCB_t term;      //!< Termimate the Engine
} VDM_Ext_t;

/*!
 *******************************************************************************
 * Create table of Extension callbacks. Overwrites any previous table.
 *
 * \param	inExt	Extension callbacks, a \ref VDM_Ext_t structure
 *
 * \return	none
 *******************************************************************************
 */
extern void VDM_setExtension(VDM_Ext_t *inExt);

#ifdef __cplusplus
} /* extern "C" */
#endif

/* @} */

#endif

