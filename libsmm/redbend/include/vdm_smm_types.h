/*
 *******************************************************************************
 *
 * vdm_smm_types.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file vdm_smm_types.h
 *
 * \brief State Machine Manager Types
 *******************************************************************************
 */
/// @cond EXCLUDE

#ifndef _VDM_SMM_TYPES_H_
#define _VDM_SMM_TYPES_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <vdm_pl_types.h>

#define MAX_STATE_NAME_LEN 128
#define SM_NAME_MAX_LEN 128

// State Machine flags
#define VDM_SMM_SM_FLAG_NON_PERSISTENT  0x01
#define VDM_SMM_SM_FLAG_MULTI_INSTANCES 0x02
#define VDM_SMM_SM_FLAG_SINGLE_INSTANCE 0x04

#define VDM_SMM_RESULT_ANY  (MAX_IS32)

// Variable flags
#define VDM_SMM_VAR_FLAG_SM_PERSISTENT      0x01   // a config var
#define VDM_SMM_VAR_FLAG_COPY_EVENT_VAR     0x02   // take value from event
#define VDM_SMM_VAR_FLAG_COPY_SM_VAR        0x04   // take value from variable
#define VDM_SMM_VAR_FLAG_ADD_VAL            0x08   // add this value
#define VDM_SMM_VAR_FLAG_OR_VAL             0x10   // OR this value
#define VDM_SMM_VAR_FLAG_ANDNOT_VAL         0x20   // ANDNOT this value
#define VDM_SMM_VAR_FLAG_TEMP               0x40   // is a temporary var
#define VDM_SMM_VAR_FLAG_RETVAL             0x80   // take value from the returned value
#define VDM_SMM_VAR_FLAG_CHANGED            0x100  // the variable was changed since last write to persistance
#define VDM_SMM_VAR_FLAG_INST_VAR           0x200  // on->instance variable; off->global variable
#define VDM_SMM_VAR_FLAG_COPY_INST_KEY      0x400  // take value from instance variable
#define VDM_SMM_VAR_FLAG_INST_KEY           0x800  // this variable defines:
                                                   //   - the name and id of the source variable in the event
                                                   //   - the default value for the default machine
#define VDM_SMM_VAR_FLAG_EXTERN_VAR         0x1000 // declare variable as extern - other machines have read access
                                                   // for this variable
#define VDM_SMM_VAR_FLAG_COPY_SM_EXTERN_VAR 0x2000 // take value from another machine's variable
#define VDM_SMM_VAR_FLAG_IF_EXTERN_VAR      0x4000 // compare value with another machine's variable value

#define INSTANCE_VAR            "INSTANCE_VAR"
#define INSTANCE_FINAL_STATE    "instnaceDestructor"

/* Event formats */
#define VDM_SMM_EVENT_FORMAT_SMM    0
#define VDM_SMM_EVENT_FORMAT_ASM    1

typedef enum {
	E_VDM_SMM_VAR_TYPE_UINT = 1,
	E_VDM_SMM_VAR_TYPE_STR = 2,
	E_VDM_SMM_VAR_TYPE_BIN = 3,
	E_VDM_SMM_VAR_TYPE_INT = 4,
	E_VDM_SMM_VAR_TYPE_UINT64 = 5
} E_VDM_SMM_VAR_TYPE_t;

typedef struct {
	IU32 size;
	void *data;
} VDM_SMM_Binary_t;

/* states */
typedef struct VDM_SMM_Value {
	char *varName;
	char machineName[SM_NAME_MAX_LEN];
	IU32 varId; /* valid only in SMM logic */
	E_VDM_SMM_VAR_TYPE_t type;
	union {
		IS32 i;
		IU32 ui;
		IU64 ui64;
		char *str;
		VDM_SMM_Binary_t bin;
	} val;
	IS32 flags;
	struct VDM_SMM_Value *next;
} VDM_SMM_Value_t;

/* events */
typedef struct {
	const char *name;
	VDM_SMM_Value_t *values;
	void *smmData; /* valid only in SMM logic */
} VDM_SMM_Event_t;

/* actions */
typedef IS32 (*VDM_SMM_ActionCb_t)(char *msgName, ...);

typedef struct {
	char *name;
	VDM_SMM_ActionCb_t cb;
	VDM_SMM_Value_t *params;
	IBOOL isAsync;
	IBOOL isPersistent; // used only for timeout actions
} VDM_SMM_Action_t;

/* transitions */
typedef struct VDM_SMM_NewState {
	IS32 actionResult;
	IS32 toId; /* valid only in SMM logic */
	char *toState;
	VDM_SMM_Value_t *toValues;
	VDM_SMM_Event_t *uiEvent;
	VDM_SMM_Event_t *sendEvent;
	VDM_SMM_Action_t *exec;
	char *gosubState;
	IS32 gosubId;
	IS32 isRtrn;
	struct VDM_SMM_NewState *next;
} VDM_SMM_NewState_t;

typedef struct VDM_SMM_Transition {
	IS32 id;
	VDM_SMM_Value_t *filter;
	char **eventsName;
	IU32 *eventsId; /* valid only in SMM logic */
	VDM_SMM_Action_t *action;
	VDM_SMM_NewState_t *states;
	struct VDM_SMM_Transition *next;
	VDM_SMM_Value_t *defVals;
} VDM_SMM_Transition_t;

typedef struct VDM_SMM_Observer {
	IS32 id;
	char **varsName;
	IU32 *varsId; /* valid only in SMM logic */
	VDM_SMM_Action_t *action;
	VDM_SMM_NewState_t *states;
	struct VDM_SMM_Observer *next;
} VDM_SMM_Observer_t;

#define VDM_SMM_STATE_FLAG_IGNORE_NON_IDLE_MONITOR 2

/* the first state is the initial state */
typedef struct VDM_SMM_State {
	char *name;
	VDM_SMM_Action_t *timeout; /* timeout function, returns how much to sleep */
	IS32 flags;
	VDM_SMM_Transition_t *transitions;
	struct VDM_SMM_State *next;
} VDM_SMM_State_t;

typedef struct VDM_SMM_Rtrn {
	char *stateName;
	IS32 stateId;
	struct VDM_SMM_Rtrn *next;
} VDM_SMM_Rtrn_t;

typedef struct {
	char *smName;
	IS32 flags;
	VDM_SMM_State_t *states;
	VDM_SMM_Value_t *smVars;
	VDM_SMM_Value_t *smInstKey;
	VDM_SMM_Observer_t *observers;
} VDM_SMM_StateMachine_t;

#ifdef __cplusplus
}
#endif

#endif /* _VDM_SMM_TYPES_H_ */
/// @endcond
