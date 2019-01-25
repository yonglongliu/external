/*
 *******************************************************************************
 *
 * vdm_utl_priqueue.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_utl_priqueue.h
 *
 * \brief	Priority Queue API
 *
 * Lower priority means that an item is more important; 0 is the highest
 * priority.
 *******************************************************************************
 */

#ifndef VDM_UTL_PRIORITY_QUEUE_H
#define VDM_UTL_PRIORITY_QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

//========================================
//
//	Standard priority queue Functionality
//
//========================================

typedef struct VDM_UTL_PriQueue_t VDM_UTL_PriQueue_t;

/*!
 *******************************************************************************
 * Create a priority queue.
 *
 * \return	Handle to the priority queue on success, NULL on error
 *******************************************************************************
 */
extern VDM_UTL_PriQueue_t *VDM_UTL_PriQueue_create(void);

/*!
 *******************************************************************************
 * Destroy a priority queue.
 *
 * \note	The queue should be empty; items in the queue are not freed.
 *
 * \param	ioQueue		Input: Handle to the priority queue;
 *						Output: NULL
 *
 * \return  Nothing
 *******************************************************************************
 */
extern void VDM_UTL_PriQueue_destroy(VDM_UTL_PriQueue_t **ioQueue);

/*!
 *******************************************************************************
 * Enqueue data onto a priority queue.
 *
 * \param	inQueue		Handle to the priority queue
 * \param	inData		Data to be queued
 * \param	inPriority	Item priority
 *
 * \return	VDM_ERR_OK on success, VDM_ERR_INVALID_CALL if \a inQueue is NULL,
 *			or VDM_ERR_MEMORY if the system is out of memory
 *******************************************************************************
 */
extern VDM_Error VDM_UTL_PriQueue_enqueue(VDM_UTL_PriQueue_t *inQueue,
	void *inData, VDM_PRIORITY_T inPriority);

/*!
 *******************************************************************************
 * Remove the first item from a priority queue with priority that meets or
 * exceeds a threshold.
 *
 * \param	inQueue		Handle to the priority queue
 * \param	inThreshold	Priority threshold
 * \param	outItem		Dequeued data
 *
 * \return	VDM_ERR_OK on success, or VDM_ERR_INVALID_CALL if \a inQueue or
 *			\a outItem is NULL
 *******************************************************************************
 */
extern VDM_Error VDM_UTL_PriQueue_dequeue(
	VDM_UTL_PriQueue_t *inQueue,
	VDM_PRIORITY_T inThreshold,
	void **outItem,
	VDM_PRIORITY_T *outPriority);

/*!
 *******************************************************************************
 * Peek at the first item in a priority queue with priority that meets or
 * exceeds a threshold.
 *
 * \param	inQueue		Handle to the priority queue
 * \param	inThreshold	Priority threshold
 * \param	outItem		Pointer to matching data
 *
 * \return	VDM_ERR_OK on success, or VDM_ERR_INVALID_CALL if \a inQueue is NULL
 *******************************************************************************
 */
extern VDM_Error VDM_UTL_PriQueue_peek(
	VDM_UTL_PriQueue_t *inQueue,
	VDM_PRIORITY_T inThreshold,
	void **outItem);
/*!
 *******************************************************************************
 * Check if a priority queue is empty.
 *
 * \param	inQueue		Handle to the priority queue
 * \param	outIsEmpty	TRUE if priority queue is empty, FALSE otherwise
 *
 * \return	VDM_ERR_OK on success, or VDM_ERR_INVALID_CALL if \a inQueue is NULL
 *******************************************************************************
 */
extern VDM_Error VDM_UTL_PriQueue_isQueueEmpty(
	VDM_UTL_PriQueue_t *inQueue,
	IBOOL *outIsEmpty);

//========================================
//
//	Extra functionality
//
//========================================

/*!
 *******************************************************************************
 * Callback invoked to destroy a queued item in a priority queue if it matches a
 * condition. The function should free the memory of the destroyed item.
 *
 * Invoked by \ref VDM_UTL_PriQueue_condRemove.
 *
 * \param	inPayload	A pointer to the item
 * \param	inParam		A pointer to any additional parameters
 *
 * \return	TRUE if the condition was met and the item was destroyed, FALSE
 *			otherwise
 *******************************************************************************
 */
typedef IBOOL (*VDM_UTL_PriQueue_conditionalDestroyCB)(void *inPayload, void *inParam);

/*!
 *******************************************************************************
 * Remove all items from a priority queue of a specific priority that also meet
 * an external condition.
 *
 * \param	inQueue					Handle to the priority queue
 * \param	inPriority				Priority of items to be removed
 * \param	inConditionalDestroyCB	A \ref VDM_UTL_PriQueue_conditionalDestroyCB
 *									callback invoked on each item to check if
 *									the item matches a condition and to destroy
 *									the item if it does
 * \param	inParam					Parameters passed to
 *									\a inConditionalDestroyCB, including a
 *									pointer to the item and a pointer to any
 *									additional parameters
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_UTL_PriQueue_condRemove(
	VDM_UTL_PriQueue_t *inQueue,
	VDM_PRIORITY_T inPriority,
	VDM_UTL_PriQueue_conditionalDestroyCB inConditionalDestroyCB,
	void *inParam);

/*!
 *******************************************************************************
 * Get the number of enqueued triggers in a priority queue.
 *
 * \param	inQueue		Handle to the priority queue
 *
 * \return	The number of enqueued triggers
 *******************************************************************************
 */
extern IU32 VDM_UTL_PriQueue_count(VDM_UTL_PriQueue_t *inQueue);

/*!
 *******************************************************************************
 * Get the data of a specific trigger in a priority queue.
 *
 * \param	inQueue		Handle to the priority queue
 * \param	inIndex		Index of the trigger
 *
 * \return	Handle to the data
 *******************************************************************************
 */
extern void *VDM_UTL_PriQueue_item(VDM_UTL_PriQueue_t *inQueue, IU32 inIndex);

/// @cond EXCLUDE

/// For debug only
typedef void (*UT_PRIORITY_QUEUE_DUMP_DATA_CB)(
	const void *inData,
	char **outDumpString);

/// For debug only
extern void VDM_UTL_PriQueue_dbgDump(
	VDM_UTL_PriQueue_t *inQueue,
	UT_PRIORITY_QUEUE_DUMP_DATA_CB inDumpCB);

/// @endcond

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

