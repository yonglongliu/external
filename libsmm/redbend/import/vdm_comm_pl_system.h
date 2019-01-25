/*
 *******************************************************************************
 *
 * vdm_comm_pl_system.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_comm_pl_system.h
 *
 * \brief   Communication PL
 *
 *******************************************************************************
 */
#ifndef _VDM_COMM_PL_SYSTEM_H_
#define _VDM_COMM_PL_SYSTEM_H_

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @addtogroup pl_comm	Communication
 * @ingroup pl
 * @{
 */

/*!
 *******************************************************************************
 * Perform system-wise communication initialization.
 *
 * All global (system-wise) initialization needed for using the communication PL
 * should be placed here.
 *
 * This function should only be called once, before starting to use the
 * communication PL. Typically it will be at the beginning of the application.
 * When using the vDM engine, this is done for you from within \ref VDM_start.
 *
 * \note	The application must call \ref VDM_Comm_PL_System_destroy before
 *          terminating the application.
 *
 *
 * \param	outSysContext	The system communication PL context.
 * \param	inSysParams		Structure containing optional parameters.
 *                          See \ref VDM_Comm_SystemParams_t.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_Comm_PL_System_create(void **outSysContext,
	VDM_Comm_SystemParams_t *inSysParams);

/*!
 *******************************************************************************
 * Perform system-wise communication termination.
 *
 * Free all global (system-wise) resources previously allocated in
 * \ref VDM_Comm_PL_System_create.
 *
 * This function should only be called once, when finished using the
 * communication PL. Typically it will be at the end of the application.
 * When using the vDM engine, this is done for you from within \ref VDM_stop.
 *
 * \param	ioSysContext	The system communication PL context.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_Comm_PL_System_destroy(void **ioSysContext);

/*! @} */

#ifdef __cplusplus
}
#endif

#endif

