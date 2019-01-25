/*
 *******************************************************************************
 *
 * dma_log.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	dma_log.h
 *
 * \brief	DMA Logging
 *******************************************************************************
 */

#ifndef _DMA_LOG_H_
#define _DMA_LOG_H_

#ifdef __cplusplus
extern "C" {
#endif

/* A bunch of includes because SMM uses VDM_log(),
 * and SMM macros (vdm_smm_declare.h) also use this logger.
 */
#include <dma_std.h>

#ifdef DEBUG
#define DLOG(...) VDM_logDebug(__VA_ARGS__)
#else
#define DLOG(...)
#endif
#define LOG(...) VDM_log(__VA_ARGS__)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _DMA_LOG_H_ */

