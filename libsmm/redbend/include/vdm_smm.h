/*
 *******************************************************************************
 *
 * vdm_smm.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file vdm_smm.h
 *
 * \brief State Machine Manager
 *******************************************************************************
 */

#ifndef _VDM_SMM_H_
#define _VDM_SMM_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <vdm_smm_types.h>
#include <vdm_smm_declare.h>
#include <vdm_client_pl_assert.h>

#define DEFAULT_INSTANCE_NAME "DEFAULT"

/**
 * A callback which is invoked once the SMM sends a UI event to the DIL
 * @param event - the UI event sent to the DIL
 */
typedef void (*VDM_SMM_sendUIEventFunc)(VDM_SMM_Event_t *event);

typedef struct VDM_SMM_syncBlock VDM_SMM_syncBlock_t;

/**
 * Initialize the SMM
 *
 * @param sendFunc             - a callback which is invoked when the SMM
 * @return 0 on success -1 on fail
 */
IS32 VDM_SMM_init(VDM_SMM_sendUIEventFunc sendFunc);

void VDM_SMM_setResetMode(IBOOL mode);

/**
 * Stop SMM
 */
void VDM_SMM_stop(void);

/**
 * Terminate SMM - clear all its data.
 *
 * @return - 0 on success, -1 on fail
 */
IS32 VDM_SMM_term(void);

#ifdef PROD
	#define VDM_SMM_handleError(dummy)
#else
	#define VDM_SMM_handleError(dummy) VDM_Client_PL_assert(FALSE)
#endif

IS32 VDM_SMM_addSM(VDM_SMM_StateMachine_t *sm, char *initialState);

/**
 * Post a pre-allocated event from to the BLs
 *
 * @param event - the event to post
 * @param origin - logcal name of the source which sent the event
 * @return 0 on success, -1 on fail
 */
IS32 VDM_SMM_postEvent(VDM_SMM_Event_t *event, const char *origin);

IS32 VDM_SMM_postBlockingEvent(VDM_SMM_syncBlock_t *sync, VDM_SMM_Event_t *event,
	char *origin);

/**
 * Allocate an event and post it to the BL - macro
 *
 * @param event - event name to be posted
 * @return 0 on success, -1 on fail
 */
#define VDM_SMM_postEventValues(event, ...) VDM_SMM_postEventValuesEx(#event, __VA_ARGS__)

/**
 * Allocate an event and post it to the BL, hold a sync lock - macro
 *
 * @param event - event name to be posted
 * @return 0 on success, -1 on fail
 */
#define VDM_SMM_postBlockingEventValues(sync, event, ...) VDM_SMM_postBlockingEventValuesEx(sync, #event, __VA_ARGS__)

/**
 * Allocate an event and post it to the BL - macro
 *
 * @param event - event name to be posted
 * @return 0 on success, -1 on fail
 */
#define VDM_SMM_postEventValuesEx(event, ...) VDM_SMM_postBlockingEventValuesEx(NULL, event, __VA_ARGS__)

/**
 * Allocate an event and post it to the BL, hold a sync lock
 *
 * @param event - event name to be posted
 * @return 0 on success, -1 on fail
 */
IS32 VDM_SMM_postBlockingEventValuesEx(VDM_SMM_syncBlock_t *sync,
	const char *name, ...);

void VDM_SMM_runQueue(IBOOL isMultiThread);

/**
 * Allocate a sync lock
 *
 * @param name - Name for the sync lock, used for debug
 * @param timeout - Timeout for the lock, zero for default timeout
 * @return pointer to the allocated lock
 */
VDM_SMM_syncBlock_t *VDM_SMM_initSync(const char *name, IU32 timeout);

/**
 * Destroy a sync lock
 *
 * @param sync - pointer the the sync lock
 */
void VDM_SMM_destroySync(VDM_SMM_syncBlock_t *sync);

/**
 * Release the sync lock
 *
 * @param sync - pointer the the sync lock
 * @return 0, in case of success
 */
IS32 VDM_SMM_releaseSync(VDM_SMM_syncBlock_t *sync);

/**
 * Release all the sync locks
 *
 * @return 0, in case of success
 */
IS32 VDM_SMM_releaseAllSync(void);

/**
 * Chaeck all SMs in Idle.
 *
 * @return True if all SMs are in the initial state.
 * Or in a state with the flag VDM_SMM_STATE_FLAG_IGNORE_NON_IDLE_MONITOR enabled.
 */
IBOOL isAllSmIdle(void);

/*!
 *******************************************************************************
 * Save state machines status to persistent data
 *******************************************************************************
 */
void VDM_SMM_saveToPs(void);

void enableSm(char* smId);

#ifdef __cplusplus
}
#endif

#endif /* _VDM_SMM_H_ */

