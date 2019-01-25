/*
 *******************************************************************************
 *
 * dma_compatibility.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file dma_compatibility.h
 *
 * \brief Backward compatibility code
 *******************************************************************************
 */

#ifndef _DMA_REDBEND_COMPATIBILTY_H_
#define _DMA_REDBEND_COMPATIBILTY_H_

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *******************************************************************************
 * Initialize backward compatibility
 *******************************************************************************
 */
void DMA_redbend_compatibilityInit(const char *inVersion);

/*!
 *******************************************************************************
 * Check whether client is in downgrade mode
 *******************************************************************************
 */
IBOOL DMA_redbend_compatibility_isInDowngradeMode(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _DMA_REDBEND_COMPATIBILTY_H_ */
