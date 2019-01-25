/*
 *******************************************************************************
 *
 * vdm_pl_async.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_pl_async.h
 *
 * \brief	Platform-specific Asynchronous Object APIs
 *
 * OMA DM Protocol Engine can operate in an asynchronous mode in which events to the
 * Engine are queued by one entity and de-queued to be processed in another
 * entity.
 *******************************************************************************
 */
#ifndef VDM_PL_ASYNC_H
#define VDM_PL_ASYNC_H

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @defgroup pl_async	Async
 * OMA DM Protocol Engine can operate in an asynchronous mode in which events to the
 * Engine are queued by one entity and de-queued to be processed in another
 * entity.
 * *
 * @ingroup pl
 * @{
 */

/*!
 *******************************************************************************
 * Wake up asynchronous object to process data.
 *
 * \note	In order for OMA DM Protocol Engine to run in asynchronous mode, a handle
 *          to an allocated asynchronous object must be passed as a parameter
 *          of \ref VDM_create when initializing the Engine. For more
 *          information, see the OMA DM Protocol Engine Framework Integrator's Guide.
 *
 * \param	inAsyncHandle   Handle to the asynchronous object
 *
 * \return	TRUE on success, indicating that a signal was successfully sent to
 *          the asynchronous object, or FALSE indicating failure to send a
 *          signal to the asynchronous object
 *******************************************************************************
 */
extern IBOOL VDM_PL_Async_signal(VDM_Handle_t inAsyncHandle);

/*! @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

