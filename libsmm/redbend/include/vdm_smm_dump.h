/*
 *******************************************************************************
 *
 * vdm_smm_dump.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file vdm_smm_dump.h
 *
 * \brief OMA DM Protocol Engine DM Application State Machine Declaration Utils
 *******************************************************************************
 */

#ifndef __VDM_SMM_DUMP_H__
#define __VDM_SMM_DUMP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <vdm_error.h>

  #ifndef VDM_SMM_dumpSM

VDM_Error VDM_SMM_dumpSM_init(char *inFilename);
void VDM_SMM_dumpSM_term(void);

  #else
	#define VDM_SMM_dumpSM_init(inFilename)
	#define VDM_SMM_dumpSM_term(dump)
  #endif /* !VDM_SMM_dumpSM */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __VDM_SMM_DUMP_H__ */

