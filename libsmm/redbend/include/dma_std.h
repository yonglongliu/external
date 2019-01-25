/*
 *******************************************************************************
 *
 * dma_std.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	dma_std.h
 *
 * \brief	DMA common includes
 *******************************************************************************
 */

#ifndef _DMA_STD_H_
#define _DMA_STD_H_

#ifdef __cplusplus
extern "C" {
#endif

/* A bunch of includes since SMM uses VDM_log(),
 * and SMM macros (vdm_smm_declare.h) use this logger as well.
 */
#include <vdm_pl_types.h>
#include <vdm_error.h>
#include <vdm_utl_logger.h>
#include <vdm_components.h>

#ifndef VDM_COMPONENT_ID
	#define VDM_COMPONENT_ID (E_VDM_COMPONENT_CLIENT)
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _DMA_STD_H_ */

