/*
 *******************************************************************************
 *
 * vdm_utl_msgqueue.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_utl_msgqueue.h
 *
 * \brief	Asynchronous Priority Queue API
 *
 * The message queue utility is based on the priority queue
 * \ref vdm_utl_priqueue.h. Added functionality includes:
 *
 * \li	An asynchronous object is signalled whenever an item
 *		is inserted to the queue.
 * \li	Access to the queue is protected with a mutex.
 *
 * Lower priority means that an item is more important.
 *******************************************************************************
 */

#ifndef _VDM_UTL_MSGQUEUE_H_
#define _VDM_UTL_MSGQUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <vdm_utl_mutex.h>

typedef struct VDM_UTL_msgQueue_t VDM_UTL_msgQueue_t;

//========================================
//	Standard priority queue Functionality
//========================================

/*!
 *******************************************************************************
 * Create a message queue.
 *
 * \param	inAsyncHandle	Handle to platform-specific asynchronous object,
 *							such as a handle to a thread.
 *
 * \return	Handle to the message queue on success, NULL on error
 *******************************************************************************
 */
extern VDM_UTL_msgQueue_t *VDM_UTL_MsgQueue_create(VDM_Handle_t inAsyncHandle);

/*!
 *******************************************************************************
 * Destroy a message queue.
 *
 * It is assumed that the queue is empty - items in the priority queue are not
 * freed.
 *
 * \param	inQueue		Handle to the message queue.
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_UTL_MsgQueue_destroy(VDM_UTL_msgQueue_t *inQueue);

/*!
 *******************************************************************************
 * Get the number of items in a message queue.
 *
 * \param	inQueue		Handle to the message queue.
 *
 * \return	Number of items in the queue
 *******************************************************************************
 */
extern IU32 VDM_UTL_MsgQueue_count(VDM_UTL_msgQueue_t *inQueue);

/*!
 *******************************************************************************
 * Get the data of a specific item in a message queue.
 *
 * \param	inQueue		Handle to the message queue.
 * \param	inIndex		Index of the item.
 *
 * \return	Handle to the data
 *******************************************************************************
 */
extern void *VDM_UTL_MsgQueue_item(VDM_UTL_msgQueue_t *inQueue, IU32 inIndex);

/*!
 *******************************************************************************
 * Enqueue data into a message queue.
 *
 * \param	inQueue		Handle to the message queue.
 * \param	inData		Data to be queued.
 * \param	inPriority	Message priority.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_UTL_MsgQueue_enqueue(VDM_UTL_msgQueue_t *inQueue,
	void *inData, VDM_PRIORITY_T inPriority);

/*!
 *******************************************************************************
 * Unlock a message queue.
 *
 * \param	inQueue		Handle to the message queue.
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_UTL_MsgQueue_unlock(VDM_UTL_msgQueue_t *inQueue);

/*!
 *******************************************************************************
 * Lock a message queue.
 *
 * \param	inQueue		Handle to the message queue.
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_UTL_MsgQueue_lock(VDM_UTL_msgQueue_t *inQueue);

/*!
 *******************************************************************************
 * Remove the first item from a message queue with priority that meets or
 * exceeds a threshold.
 *
 * \param	inQueue		Handle to the message queue.
 * \param	inThreshold	Priority threshold.
 * \param	outPriority	the priority of the message in the queue.
 *
 * \return	A pointer to the dequeued data, or NULL if no item was found
 *******************************************************************************
 */
extern void *VDM_UTL_MsgQueue_dequeue_with_piority(VDM_UTL_msgQueue_t *inQueue,
	VDM_PRIORITY_T inThreshold, VDM_PRIORITY_T *outPriority);

/*!
 *******************************************************************************
 * Remove the first item from a message queue with priority that meets or
 * exceeds a threshold.
 *
 * \param	inQueue		Handle to the message queue.
 * \param	inThreshold	Priority threshold.
 *
 * \return	A pointer to the dequeued data, or NULL if no item was found
 *******************************************************************************
 */
extern void *VDM_UTL_MsgQueue_dequeue(VDM_UTL_msgQueue_t *inQueue,
	VDM_PRIORITY_T inThreshold);

/*!
 *******************************************************************************
 * Peek at the first item in a message queue with priority that meets or exceeds
 * a threshold.
 *
 * \param	inQueue		Handle to the message queue.
 * \param	inThreshold	Priority threshold.
 *
 * \return	Pointer to data of the top item in the queue that meets or exceeds
 *			the threshold, or NULL if no item was found
 *******************************************************************************
 */
extern void *VDM_UTL_MsgQueue_peek(VDM_UTL_msgQueue_t *inQueue,
	VDM_PRIORITY_T inThreshold);

/*!
 *******************************************************************************
 * Check if a message queue is empty.
 *
 * \param	inQueue		Handle to the message queue.
 *
 * \return	TRUE if the message queue is empty, FALSE otherwise
 *******************************************************************************
 */
extern IBOOL VDM_UTL_MsgQueue_isQueueEmpty(VDM_UTL_msgQueue_t *inQueue);

/*!
 *******************************************************************************
 * Get mutex associated with a message queue.
 *
 * \param	inQueue		Handle to the message queue.
 *
 * \return	Handle to the mutex
 *******************************************************************************
 */
extern VDM_UTL_Mutex_t *VDM_UTL_MsgQueue_getMutex(VDM_UTL_msgQueue_t *inQueue);

//========================================
//	Extra functionality
//========================================

/*!
 *******************************************************************************
 * Callback invoked to free memory of queued item from a message queue according
 * to an external condition.
 *
 * The callback is invoked by \ref VDM_UTL_MsgQueue_condRemove. When the
 * condition is met, the callback must free the memory allocated for the
 * item. If this callback returns TRUE, then the item has been removed
 * from the queue.
 *
 * \param	inPayload	The payload to free.
 * \param	inParam		Additional parameters passed to the callback.
 *
 * \return	TRUE if condition was met and the item was freed, FALSE otherwise
 *******************************************************************************
 */
typedef IBOOL (*VDM_UTL_MsgQueue_conditionalDestroyCB)(void *inPayload,
	void *inParam);

/*!
 *******************************************************************************
 * Remove all items from a message queue of a specific priority that also meet
 * an external condition.
 *
 * \param	inQueue					Handle to the message queue.
 * \param	inPriority				Priority of items to be removed. The items
 *									must also match the external condition.
 * \param	inConditionalDestroyCB	Callback to conditionally destroy the
 *									payload data. See \ref
 *									VDM_UTL_MsgQueue_conditionalDestroyCB.
 * \param	inParam					Parameters passed to the callback.
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_UTL_MsgQueue_condRemove(VDM_UTL_msgQueue_t *inQueue,
	VDM_PRIORITY_T inPriority,
	VDM_UTL_MsgQueue_conditionalDestroyCB inConditionalDestroyCB,
	void *inParam);

/*!
 *******************************************************************************
 * Send a signal that a message queue is not empty.
 *
 * \param	inQueue		Handle to the message queue.
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_UTL_MsgQueue_signal(VDM_UTL_msgQueue_t *inQueue);

/// @cond EXCLUDE

/// For debug only
typedef void (*MSGQUEUE_DUMP_DATA_CB)(const void *inData, char **outDumpString);
extern void VDM_UTL_MsgQueue_DbgDump(VDM_UTL_msgQueue_t *inQueue,
	MSGQUEUE_DUMP_DATA_CB inDumpCB);

/// @endcond

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

