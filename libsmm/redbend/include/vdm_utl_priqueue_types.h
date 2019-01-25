/*
 *******************************************************************************
 *
 * vdm_utl_priqueue_types.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_utl_priqueue_types.h
 *
 * \brief	Priority Queue Types
 *******************************************************************************
 */

#ifndef VDM_UTL_PRIORITY_QUEUE_TYPES_H
#define VDM_UTL_PRIORITY_QUEUE_TYPES_H          //!< Internal

#ifdef __cplusplus
extern "C" {
#endif

//=========================
// typedefs and definitions
//=========================

/// Priority queue item
typedef struct VDM_UTL_priQItem_t {
	VDM_PRIORITY_T priority; //!< Item priority
	void *payload;  //!< Opaque data
	struct VDM_UTL_priQItem_t *next; //!< Pointer to next item
} VDM_UTL_priQItem_t;

/// Priority queue
struct VDM_UTL_PriQueue_t {
	VDM_UTL_priQItem_t *head;
	IU32 count; //!< Number of items in the queue
};

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

