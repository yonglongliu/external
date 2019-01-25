/*
 *******************************************************************************
 *
 * vdm_smm_declare_inl.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_smm_declare_inl.h
 *
 * \brief	vSM State Machine Structures
 *
 * Macros that implement the State Machine language. All structure allocation
 * and freeing is handled internally.
 *******************************************************************************
 */

/// @cond EXCLUDE

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _VDM_SMM_DECLARE_H_
#error "vdm_smm_declare_inl.h must be included from vdm_smm_declare.h only"
#endif

#ifdef WIN32
// avoid MSVS warning C4003: "not enough actual parameters for macro 'identifier'",
// which occurs when calling foo() when macro is defined as foo(dummy)
	#pragma warning(disable: 4003)
#endif

#if (defined (AEE_SIMULATOR) || defined (WIN32) || defined (WIN64))
//see explanation in: http://stackoverflow.com/questions/9183993/msvc-variadic-macro-expansion
	#define VDM_VA_ARGS_EXPANDED_AS_SINGLE_TOKEN
#endif

/* Top Level Elements */
typedef enum {
	E_VDM_SMM_EL_NONE = 0x00,
	E_VDM_SMM_TRANS_EL_STATE,
	E_VDM_SMM_TRANS_EL_IF_VAR,
	E_VDM_SMM_TRANS_EL_IF_EXTERN_VAR,
	E_VDM_SMM_TRANS_EL_EVENT,
	E_VDM_SMM_TRANS_EL_DEF_VAL,
	E_VDM_SMM_OBSERV_EL_VAR_CHANGE,
	E_VDM_SMM_EL_DO,
	E_VDM_SMM_EL_GOTO,
	E_VDM_SMM_EL_END
} E_VDM_SMM_DECLARE_ELEMENT_t;

/* Goto Elements */
typedef enum {
	E_VDM_SMM_GOTO_EL_NONE = 0x10,
	E_VDM_SMM_GOTO_EL_STATE,
	E_VDM_SMM_GOTO_EL_SET_VAR,
	E_VDM_SMM_GOTO_EL_ADD_VAR,
	E_VDM_SMM_GOTO_EL_OR_VAR,
	E_VDM_SMM_GOTO_EL_ANDNOT_VAR,
	E_VDM_SMM_GOTO_EL_UI,
	E_VDM_SMM_GOTO_EL_SEND_EVENT,
	E_VDM_SMM_GOTO_EL_EXEC,
	E_VDM_SMM_GOTO_EL_GOSUB,
	E_VDM_SMM_GOTO_EL_RTRN,
	E_VDM_SMM_GOTO_EL_END
} E_VDM_SMM_DECLARE_GOTO_ELEMENT_t;

/* Set Var elements */
typedef enum {
	E_VDM_SMM_VAR_EL_NONE = 0x20,
	E_VDM_SMM_VAR_EL_EVT_VAL,
	E_VDM_SMM_VAR_EL_SM_VAL,
	E_VDM_SMM_VAR_EL_SM_EXTERN_VAL,
	E_VDM_SMM_VAR_EL_RET_VAL,
	E_VDM_SMM_VAR_EL_INSTANCE_VAL,
	E_VDM_SMM_VAR_EL_INT,
	E_VDM_SMM_VAR_EL_UINT,
	E_VDM_SMM_VAR_EL_UINT64,
	E_VDM_SMM_VAR_EL_STR,
	E_VDM_SMM_VAR_EL_BIN
} E_VDM_SMM_DECLARE_SETVAR_ELEMENT_t;

typedef struct {
	char *name;
} VDM_SMM_Declare_StateType_t;

typedef struct {
	char machineName[SM_NAME_MAX_LEN];
	char *varName;
	IU32 value;
} VDM_SMM_Declare_IfVarType_t;

typedef char *VDM_SMM_Declare_VarChangeType_t;

typedef char *VDM_SMM_Declare_EventType_t;

typedef union {
	IS32 i;
	IU32 ui;
	IU64 ui64;
	const char *str;
	VDM_SMM_Binary_t bin;
} VDM_SMM_Declare_Value_t;

typedef struct {
	E_VDM_SMM_DECLARE_SETVAR_ELEMENT_t setType;
	char machineName[SM_NAME_MAX_LEN];
	VDM_SMM_Declare_Value_t val;
} VDM_SMM_Declare_SetVar_Value_t;

typedef struct {
	IU32 valCount;
	VDM_SMM_Declare_SetVar_Value_t *vals;   //XXX should be VDM_SMM_Declare_Value_t. the setType of SetVar_Value_t has no meaning here
} VDM_SMM_Declare_Values_t;

typedef struct {
	VDM_SMM_ActionCb_t action;
	const char *name;
	VDM_SMM_Declare_Values_t vals;
	IBOOL isAsync;
} VDM_SMM_Declare_ActionType_t;

typedef struct {
	char *varName;
	VDM_SMM_Declare_SetVar_Value_t val;
} VDM_SMM_Declare_SetVar_t;

typedef struct {
	char *name;
	VDM_SMM_Declare_Values_t vals;
} VDM_SMM_Declare_Event_t;

typedef struct {
	char *name;
} VDM_SMM_Declare_Gosub_t;

typedef struct {
	int isRtrn;
} VDM_SMM_Declare_Rtrn_t;

typedef struct {
	char *varName;
	VDM_SMM_Declare_SetVar_Value_t value;
} VDM_SMM_Declare_DefVal_t;

typedef struct {
	E_VDM_SMM_DECLARE_GOTO_ELEMENT_t type;
	union {
		VDM_SMM_Declare_StateType_t state;
		VDM_SMM_Declare_SetVar_t var;
		VDM_SMM_Declare_Event_t event;
		VDM_SMM_Declare_ActionType_t exec;
		VDM_SMM_Declare_Gosub_t gosub;
		VDM_SMM_Declare_Rtrn_t rtrn;
	} val;
} VDM_SMM_Trans_GotoElement_t;

typedef struct {
	IS32 retVal;
	VDM_SMM_Trans_GotoElement_t *el;
	IU32 elCount;
} VDM_SMM_Declare_GotoType_t;

typedef struct {
	E_VDM_SMM_DECLARE_ELEMENT_t type;
	union {
		VDM_SMM_Declare_StateType_t state;
		VDM_SMM_Declare_IfVarType_t ifVar;
		VDM_SMM_Declare_EventType_t event;
		VDM_SMM_Declare_ActionType_t action;
		VDM_SMM_Declare_GotoType_t go;
		VDM_SMM_Declare_VarChangeType_t varChange;
		VDM_SMM_Declare_DefVal_t defVal;
	} val;
} VDM_SMM_Trans_Element_t;

VDM_SMM_StateMachine_t *VDM_SMM_Declare_initSM(char *smName, IS32 flags);

IS32 VDM_SMM_Declare_setStateTimeout(VDM_SMM_StateMachine_t *sm, const char *state,
	const char *actionName, VDM_SMM_ActionCb_t func, IBOOL isPersistent, ...);

IS32 VDM_SMM_Declare_setStateFlag(VDM_SMM_StateMachine_t *sm, char *state, IS32 flag);

IS32 VDM_SMM_Declare_freeSmDeclaration(VDM_SMM_StateMachine_t *sm);

VDM_SMM_Trans_Element_t VDM_SMM_Declare_transState(char *stateName);

VDM_SMM_Trans_Element_t VDM_SMM_Declare_transIfVar(char *varName, IU32 value);

VDM_SMM_Trans_Element_t VDM_SMM_Declare_transIfExternVar(const char *machineName, char *varName, IU32 value);

VDM_SMM_Trans_Element_t VDM_SMM_Declare_transEvent(char *name);

VDM_SMM_Trans_Element_t VDM_SMM_Declare_observVarChange(char *varName);

VDM_SMM_Trans_Element_t VDM_SMM_Declare_transAction(VDM_SMM_ActionCb_t func,
	const char *actionName, ...);

VDM_SMM_Trans_Element_t VDM_SMM_Declare_transGo(IS32 ret, ...);

VDM_SMM_Trans_GotoElement_t VDM_SMM_Declare_goto_listEnd(void);

VDM_SMM_Trans_Element_t VDM_SMM_Declare_listEnd(void);

VDM_SMM_Trans_GotoElement_t VDM_SMM_Declare_gotoState(char *newState);

VDM_SMM_Trans_GotoElement_t VDM_SMM_Declare_gotoVar(char *varName,
	VDM_SMM_Declare_SetVar_Value_t val);

VDM_SMM_Trans_GotoElement_t VDM_SMM_Declare_gotoGlobalVar(const char *varName,
	VDM_SMM_Declare_SetVar_Value_t val);

VDM_SMM_Trans_GotoElement_t VDM_SMM_Declare_gotoAddVar(char *varName,
	VDM_SMM_Declare_SetVar_Value_t val);

VDM_SMM_Trans_GotoElement_t VDM_SMM_Declare_gotoOrVar(char *varName,
	VDM_SMM_Declare_SetVar_Value_t val);

VDM_SMM_Trans_GotoElement_t VDM_SMM_Declare_gotoAndNotVar(char *varName,
	VDM_SMM_Declare_SetVar_Value_t val);

VDM_SMM_Trans_GotoElement_t VDM_SMM_Declare_gotoEvent(char *name, IS32 isUI, ...);

VDM_SMM_Trans_GotoElement_t VDM_SMM_Declare_gotoExec(VDM_SMM_ActionCb_t func,
	const char *actionName, IBOOL isAsync, ...);

VDM_SMM_Trans_GotoElement_t VDM_SMM_Declare_gosubState(char *subState);

VDM_SMM_Trans_GotoElement_t VDM_SMM_Declare_rtrn(void);

VDM_SMM_Declare_SetVar_Value_t VDM_SMM_Declare_gotoSetVarEvt(char *eventVarName);

VDM_SMM_Declare_SetVar_Value_t VDM_SMM_Declare_gotoSetVarSm(char *smVarName);

VDM_SMM_Declare_SetVar_Value_t VDM_SMM_Declare_gotoSetExternVar(char *machineName, char *externVarName);

VDM_SMM_Declare_SetVar_Value_t VDM_SMM_Declare_gotoSetVarRet(void);

VDM_SMM_Declare_SetVar_Value_t VDM_SMM_Declare_gotoSetVarInst(void);

VDM_SMM_Declare_SetVar_Value_t VDM_SMM_Declare_gotoSetVarInt(IS32 value);

VDM_SMM_Declare_SetVar_Value_t VDM_SMM_Declare_gotoSetVarUint(IU32 value);

VDM_SMM_Declare_SetVar_Value_t VDM_SMM_Declare_gotoSetVarUint64(IU64 value);

VDM_SMM_Declare_SetVar_Value_t VDM_SMM_Declare_gotoSetVarStr(const char *strValue);

VDM_SMM_Declare_SetVar_Value_t VDM_SMM_Declare_gotoSetVarBin(IU32 size, void *data);

VDM_SMM_Declare_SetVar_Value_t VDM_SMM_Declare_gotoSetVarNone(void);

IS32 VDM_SMM_Declare_addTransition(VDM_SMM_StateMachine_t *sm, ...);

IS32 VDM_SMM_Declare_addObserver(VDM_SMM_StateMachine_t *sm, ...);

IS32 VDM_SMM_Declare_stateVar(VDM_SMM_StateMachine_t *sm, char *varName,
	VDM_SMM_Declare_SetVar_Value_t value, IS32 flag);

int VDM_SMM_Declare_defaultTimeoutFunc(const char *msgId, IU32 timeout);

void VDM_SMM_Declare_setExternVarsNow(IU32 value);

VDM_SMM_Trans_Element_t VDM_SMM_Declare_transDefVal(const char *varName,
	VDM_SMM_Declare_SetVar_Value_t value);

extern IS32 VDM_SMM_dumpSM(VDM_SMM_StateMachine_t *sm);

#ifdef __cplusplus
} /* extern "C" */
#endif

/// @endcond
