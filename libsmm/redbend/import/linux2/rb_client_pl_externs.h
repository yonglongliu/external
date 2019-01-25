/*
 *******************************************************************************
 *
 * rb_client_pl_externs.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file rb_client_pl_externs.h
 *
 * \brief Client porting layer external definitions
 *******************************************************************************
 */

#ifndef RB_CLIENT_PL_EXTERNS_H_
#define RB_CLIENT_PL_EXTERNS_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Full path of vDM's log file.
 * you may override the default full path of the log file.
 * you should set the value of g_VDMLogFilePath before calling VDM_create
 */
extern const char *g_VDMLogFilePath;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* RB_CLIENT_PL_EXTERNS_H_ */
