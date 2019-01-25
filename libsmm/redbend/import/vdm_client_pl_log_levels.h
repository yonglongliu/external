/*
 *******************************************************************************
 *
 * vdm_client_pl_log_levels.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_client_pl_log_levels.h
 *
 * \brief	OMA DM Protocol Engine Logger Utility Severity Levels
 *******************************************************************************
 */
#ifndef VDM_CLIENT_PL_LOG_LEVELS_H
#define VDM_CLIENT_PL_LOG_LEVELS_H

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @addtogroup pl_log	Logging
 * @{
 */

/*!
 * Logging levels
 */
typedef enum {
	E_VDM_LOGLEVEL_None     = 0,
	E_VDM_LOGLEVEL_Error    = 1,   //!< Failure (default in rls)
	E_VDM_LOGLEVEL_Trace    = 2,   //!< TRACE
	E_VDM_LOGLEVEL_Warning  = 3,   //!< Warning
	E_VDM_LOGLEVEL_Notice   = 4,   //!< Notice (default in rls_dbgInfo)
	E_VDM_LOGLEVEL_Info     = 5,   //!< Info
	E_VDM_LOGLEVEL_Debug    = 6,   //!< Debug
	E_VDM_LOGLEVEL_Verbose  = 7    //!< Verbose
} E_VDM_LOGLEVEL_TYPE;

/*! @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

