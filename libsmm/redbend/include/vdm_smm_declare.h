/*
 *******************************************************************************
 *
 * vdm_smm_declare.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_smm_declare.h
 *
 * \brief	vDM State Machine Structures
 *
 * Macros that implement the State Machine language. All structure allocation
 * and freeing is handled internally.
 *******************************************************************************
 */

/// @cond EXCLUDE

#ifndef _VDM_SMM_DECLARE_H_
#define _VDM_SMM_DECLARE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <vdm_smm_dump.h>
#include <vdm_smm_declare_inl.h>
#include <vdm_utl_str.h>
#include <vdm_smm.h>

#define NO_VALUES       NULL
#define NO_MORE_VALUES  NULL
#define NO_MORE_STATES  NULL
#define NO_STR_VALUE    NULL
#define NO_UI_EVENT     NULL
#ifdef STATIC_SMM_GEN

#define END() VDM_SMM_Declare_listEnd()

#define END_GOTO() VDM_SMM_Declare_goto_listEnd()

/*!
 *******************************************************************************
 * Begin a persistent-type state machine declaration.
 *
 * The state machine defined by this macro saves its state to the persistent
 * storage.
 * The state machine declaration must end with a call to \ref ADD_SM.
 *
 * \param	name		The name of the state machine. This name must be unique.
 *
 * \see ADD_SM
 * \see DEFINE_NON_PERSISTENT_SM
 *******************************************************************************
 */
#define DEFINE_SM(name) \
	do { \
		VDM_SMM_StateMachine_t *sm; \
        \
		sm = VDM_SMM_Declare_initSM((char *)name, 0)

/*!
 *******************************************************************************
 * Begin a non-persistent-type state machine declaration.
 *
 * The state machine defined by this macro doesn't save its state to the
 * persistent storage.
 * The state machine declaration must end with a call to \ref ADD_SM.
 *
 * \param	name		The name of the state machine. This name must be unique.
 *
 * \see ADD_SM
 * \see DEFINE_SM
 *******************************************************************************
 */
#define DEFINE_NON_PERSISTENT_SM(name) \
	do { \
		VDM_SMM_StateMachine_t *sm; \
        \
		sm = VDM_SMM_Declare_initSM((char *)name, VDM_SMM_SM_FLAG_NON_PERSISTENT)

/*!
 *******************************************************************************
 * Begin a multi-instances-type state machine declaration.
 *
 * The state machine defined by this macro can manage different instances.
 * The state machine declaration must end with a call to \ref ADD_SM.
 *
 * \param	name		The name of the state machine. This name must be unique.
 *
 * \see ADD_SM
 * \see DEFINE_SM
 *******************************************************************************
 */

#define DEFINE_MULTI_INSTANCES_SM(name) \
	do { \
		VDM_SMM_StateMachine_t *sm; \
        \
		sm = VDM_SMM_Declare_initSM((char *)name, VDM_SMM_SM_FLAG_MULTI_INSTANCES)

/*!
 *******************************************************************************
 * Begin declaration of extern vars.
 * Vars in this block has read access from other machines.
 *******************************************************************************
 */
#define START_EXTERN_VARS VDM_SMM_Declare_setExternVarsNow(TRUE)

/*!
 *******************************************************************************
 * End declaration of extern vars.
 * Vars in this block has read access from other machines.
 *******************************************************************************
 */
#define END_EXTERN_VARS VDM_SMM_Declare_setExternVarsNow(FALSE)

#define TRANS(...) \
	VDM_SMM_Declare_addTransition(sm, __VA_ARGS__, END())

/*!
 *******************************************************************************
 * Register to be notified that the values of specific variables have changed.
 *
 * An OBSERV declaration should consist of one or more \ref VAR_CHANGE conditions,
 * one for each tracked variable.
 *
 * \see VAR_CHANGE
 *******************************************************************************
 */
#define OBSERV(...) \
	VDM_SMM_Declare_addObserver(sm, __VA_ARGS__, END())

#define STATE(state) \
	VDM_SMM_Declare_transState((char *)#state)

#define IF_VAR(var, value) \
	VDM_SMM_Declare_transIfVar((char *)#var, value)

/*!
 *******************************************************************************
 * Condition to check if the value of a specific variable has changed.
 *
 * The VAR_CHANGE condition is checked as a part of an \ref OBSERV declaration.
 *
 * \param	var		The variable to check.
 *
 * \see OBSERV
 *******************************************************************************
 */
#define VAR_CHANGE(var) \
	VDM_SMM_Declare_observVarChange(#var)

#define EVENT(name) \
	VDM_SMM_Declare_transEvent((char *)#name)

#ifdef VDM_VA_ARGS_EXPANDED_AS_SINGLE_TOKEN
	#define DO(action, ...) \
	VDM_SMM_Declare_transAction((VDM_SMM_ActionCb_t)action, #action, ## __VA_ARGS__, \
	VDM_SMM_Declare_gotoSetVarNone())
#else
	#define DO(...) \
	_DO(__VA_ARGS__, VDM_SMM_Declare_gotoSetVarNone())
	#define _DO(action, ...) \
	VDM_SMM_Declare_transAction((VDM_SMM_ActionCb_t)action, #action, __VA_ARGS__)
#endif

#define GOTO(ret, ...) \
	VDM_SMM_Declare_transGo(ret, __VA_ARGS__, END_GOTO())

#define TO_STATE(newState) \
	VDM_SMM_Declare_gotoState((char *)#newState)

#define GO_SUB(subState) \
	VDM_SMM_Declare_gosubState((char *)#subState)

#define RETURN \
	VDM_SMM_Declare_rtrn()

#define SET_VAR(var, value) \
	VDM_SMM_Declare_gotoVar((char *)#var, value)

#define ADD_VAR(var, value) \
	VDM_SMM_Declare_gotoAddVar((char *)#var, value)

#define OR_VAR(var, value) \
	VDM_SMM_Declare_gotoOrVar((char *)#var, value)

#define ANDNOT_VAR(var, value) \
	VDM_SMM_Declare_gotoAndNotVar((char *)#var, value)

#define EVT_VAL(evtVarName) \
	VDM_SMM_Declare_gotoSetVarEvt((char *)#evtVarName)

#define SM_VAL(smVarName) \
	VDM_SMM_Declare_gotoSetVarSm((char *)#smVarName)

#define RET_VAL() \
	VDM_SMM_Declare_gotoSetVarRet()

#define INSTANCE_VAL() \
	VDM_SMM_Declare_gotoSetVarInst()

#define INT(val) \
	VDM_SMM_Declare_gotoSetVarInt(val)

#define UINT(val) \
	VDM_SMM_Declare_gotoSetVarUint(val)

#define UINT64(val) \
	VDM_SMM_Declare_gotoSetVarUint64(val)

#define STR(val) \
	VDM_SMM_Declare_gotoSetVarStr(val)

#define BIN(size, val) \
	VDM_SMM_Declare_gotoSetVarBin(size, val)

#ifdef VDM_VA_ARGS_EXPANDED_AS_SINGLE_TOKEN
	#define UI(uiEvent, ...) \
	VDM_SMM_Declare_gotoEvent((char *)#uiEvent, 1, ## __VA_ARGS__, \
	VDM_SMM_Declare_gotoSetVarNone())
	#define SEND_EVENT(uiEvent, ...) \
	VDM_SMM_Declare_gotoEvent((char *)#uiEvent, 0, ## __VA_ARGS__, \
	VDM_SMM_Declare_gotoSetVarNone())
	#define TIMEOUT_FUNC(state, action, ...) \
	VDM_SMM_Declare_setStateTimeout(sm, #state, #action, (VDM_SMM_ActionCb_t)action, FALSE, ## __VA_ARGS__, \
	VDM_SMM_Declare_gotoSetVarNone())
	#define TIMEOUT_PERSISTENT_FUNC(state, action, ...) \
	VDM_SMM_Declare_setStateTimeout(sm, #state, #action, (VDM_SMM_ActionCb_t)action, TRUE, ## __VA_ARGS__, \
	VDM_SMM_Declare_gotoSetVarNone())
	#define EXEC(action, ...) \
	VDM_SMM_Declare_gotoExec((VDM_SMM_ActionCb_t)action, #action, FALSE, ## __VA_ARGS__, \
	VDM_SMM_Declare_gotoSetVarNone())
	#define EXEC_ASYNC(action, ...) \
	VDM_SMM_Declare_gotoExec((VDM_SMM_ActionCb_t)action, #action, TRUE, ## __VA_ARGS__, \
	VDM_SMM_Declare_gotoSetVarNone())
#else
	#define UI(...) \
	_UI(__VA_ARGS__, VDM_SMM_Declare_gotoSetVarNone())
	#define SEND_EVENT(...) \
	_SEND_EVENT(__VA_ARGS__, VDM_SMM_Declare_gotoSetVarNone())
	#define _UI(uiEvent, ...) \
	VDM_SMM_Declare_gotoEvent((char *)#uiEvent, 1, __VA_ARGS__)
	#define _SEND_EVENT(uiEvent, ...) \
	VDM_SMM_Declare_gotoEvent((char *)#uiEvent, 0, __VA_ARGS__)

	#define TIMEOUT_FUNC(state, ...) \
	_TIMEOUT_FUNC(state, __VA_ARGS__, VDM_SMM_Declare_gotoSetVarNone())
	#define _TIMEOUT_FUNC(state, action, ...) \
	VDM_SMM_Declare_setStateTimeout(sm, #state, #action, (VDM_SMM_ActionCb_t)action, FALSE, __VA_ARGS__)

	#define TIMEOUT_PERSISTENT_FUNC(state, ...) \
	_TIMEOUT_PERSISTENT_FUNC(state, __VA_ARGS__, VDM_SMM_Declare_gotoSetVarNone())
	#define _TIMEOUT_PERSISTENT_FUNC(state, action, ...) \
	VDM_SMM_Declare_setStateTimeout(sm, #state, #action, (VDM_SMM_ActionCb_t)action, TRUE, __VA_ARGS__)

	#define EXEC(...) \
	_EXEC(__VA_ARGS__, VDM_SMM_Declare_gotoSetVarNone())
	#define _EXEC(action, ...) \
	VDM_SMM_Declare_gotoExec((VDM_SMM_ActionCb_t)action, #action, FALSE, __VA_ARGS__)
	#define EXEC_ASYNC(...) \
	_EXEC_ASYNC(__VA_ARGS__, VDM_SMM_Declare_gotoSetVarNone())
	#define _EXEC_ASYNC(action, ...) \
	VDM_SMM_Declare_gotoExec((VDM_SMM_ActionCb_t)action, #action, TRUE, __VA_ARGS__)

#endif

#define TIMEOUT(state, timeout) \
	TIMEOUT_FUNC(state, VDM_SMM_Declare_defaultTimeoutFunc, INT(timeout))

#define IGNORE_NON_IDLE_MONITOR(state) \
	VDM_SMM_Declare_setStateFlag(sm, #state, VDM_SMM_STATE_FLAG_IGNORE_NON_IDLE_MONITOR)

#define DEF_VAL(varName, val) \
	VDM_SMM_Declare_transDefVal(#varName, val)

/*!
 *******************************************************************************
 * Declare a VAR-type state machine variable.
 *
 * The value of a VAR-type variable is saved to the persistent storage, and it
 * resets to default when its state machine returns to idle state.
 *
 * \param	varName		The name of the variable.
 * \param	val			The default value of the variable.
 *
 * \see CONFIG_VAR
 * \see TEMP_VAR
 *******************************************************************************
 */
#define VAR(varName, val) \
	VDM_SMM_Declare_stateVar(sm, (char *)#varName, val, 0)

/*!
 *******************************************************************************
 * Declare a CONFIG_VAR-type state machine variable.
 *
 * The value of a CONFIG_VAR-type variable is saved to the persistent storage,
 * and it doesn't reset to default when its state machine returns to idle state.
 *
 * \param	varName		The name of the variable.
 * \param	val			The default value of the variable.
 *
 * \see VAR
 * \see TEMP_VAR
 *******************************************************************************
 */
#define CONFIG_VAR(varName, val) \
	VDM_SMM_Declare_stateVar(sm, (char *)#varName, val, VDM_SMM_VAR_FLAG_SM_PERSISTENT)

/*!
 *******************************************************************************
 * Declare a TEMP_VAR-type state machine variable.
 *
 * The value of a TEMP_VAR-type variable is not saved to the persistent
 * storage, and it doesn't reset to default when its state machine returns to
 * idle state.
 *
 * \param	varName		The name of the variable.
 * \param	val			The default value of the variable.
 *
 * \see VAR
 * \see CONFIG_VAR
 *******************************************************************************
 */
#define TEMP_VAR(varName, val) \
	VDM_SMM_Declare_stateVar(sm, (char *)#varName, val, VDM_SMM_VAR_FLAG_TEMP)

/*!
 *******************************************************************************
 * Declare a INSTANCE_KEY name and type.
 *
 * The value of a INSTANCE_VAR-type variable is received from the event,
 * and used as the key of the instance machine
 * if a new value is received, a new instance is created
 * if the instance machine returns to its idle state, the inst state machine is destroyed
 *
 * \param	varName		The name of the variable.
 * \param	val			The default value of the variable.
 *
 *******************************************************************************
 */
#define INSTANCE_KEY(varName, val) \
	VDM_SMM_Declare_stateVar(sm, (char *)#varName, val, VDM_SMM_VAR_FLAG_INST_KEY)

/*!
 *******************************************************************************
 * End a state machine declaration.
 *
 * This macro must appear at the end of a state machine declaration, which was
 * declared by either \ref DEFINE_SM or \ref DEFINE_NON_PERSISTENT_SM.
 *
 * \param	initState		The name of the initial state of the state machine,
 *                          also known as "idle state".
 *
 * \see DEFINE_SM
 * \see DEFINE_NON_PERSISTENT_SM
 *******************************************************************************
 */
#define ADD_SM(initState) \
	VDM_SMM_dumpSM(sm); \
	if (VDM_SMM_addSM(sm, (char *)#initState)) \
	{ \
		VDM_logError("Error adding SM %s", VDM_UTL_strPrintNull(sm->smName)); \
		VDM_SMM_handleError(); \
	} \
	else { \
		VDM_logInfo("Added SM %s", VDM_UTL_strPrintNull(sm->smName)); } \
	VDM_SMM_Declare_freeSmDeclaration(sm); \
	} while (0)

/*!
 *******************************************************************************
 * Declare a WAIT_FLOW_END_STATE name and type.
 *
 * In all multi-instance state machines - each instance will wait for
 * DMA_MSG_SCOMO_FLOW_END/DMA_MSG_LAWMO_FLOW_END/DMA_MSG_DESCMO_FLOW_END
 * (depends on the session type) event in order to end its flow.
 * When the instance get the flow end event, it immediately will go
 * to its final state and will be destroyed.
 *
 * \param	flowEndState	The name of the state in which the
 *                          instance will wait for flow end event.
 *
 *******************************************************************************
 */
#define WAIT_FLOW_END_STATE(flowEndState)  \
	VDM_SMM_Declare_addTransition(sm, \
	VDM_SMM_Declare_transEvent((char *)"DMA_MSG_SCOMO_FLOW_END"), \
	VDM_SMM_Declare_transEvent((char *)"DMA_MSG_LAWMO_FLOW_END"), \
	VDM_SMM_Declare_transEvent((char *)"DMA_MSG_DESCMO_FLOW_END"), \
	VDM_SMM_Declare_transEvent((char *)"DMA_MSG_LOCATE_FLOW_END"), \
	VDM_SMM_Declare_transGo(0, VDM_SMM_Declare_gotoState((char *)INSTANCE_FINAL_STATE), \
	VDM_SMM_Declare_goto_listEnd()), VDM_SMM_Declare_listEnd()); \
	VDM_SMM_Declare_addTransition(sm, \
	VDM_SMM_Declare_transState(#flowEndState), \
	VDM_SMM_Declare_transEvent((char *)"DMA_MSG_INT_SMM_STARTED"), VDM_SMM_Declare_listEnd()); \
	VDM_SMM_Declare_addTransition(sm, \
	VDM_SMM_Declare_transState(INSTANCE_FINAL_STATE), VDM_SMM_Declare_listEnd());

#else
#define END()
#define END_GOTO()
#define DEFINE_SM(name) enableSm(name)
#define DEFINE_NON_PERSISTENT_SM(name) enableSm(name)
#define DEFINE_MULTI_INSTANCES_SM(name) enableSm(name)
#define START_EXTERN_VARS
#define END_EXTERN_VARS
#define TRANS(...)
#define OBSERV(...)
#define STATE(state)
#define IF_VAR(var, value)
#define VAR_CHANGE(var)
#define EVENT(name)
#ifdef VDM_VA_ARGS_EXAPNDED_AS_SINGLE_TOKEN
    #define DO(action, ...)
#else
    #define DO(...)
#endif

#define GOTO(ret, ...)
#define TO_STATE(newState)
#define SET_VAR(var, value)
#define ADD_VAR(var, value)
#define OR_VAR(var, value)
#define ANDNOT_VAR(var, value)
#define EVT_VAL(evtVarName)
#define SM_VAL(smVarName)
#define RET_VAL()
#define INT(val)
#define UINT(val)
#define STR(val)
#define BIN(size, val)
#ifdef VDM_VA_ARGS_EXAPNDED_AS_SINGLE_TOKEN
    #define UI(uiEvent, ...)
	#define SEND_EVENT(uiEvent, ...)
    #define TIMEOUT_FUNC(state, action, ...)
#define TIMEOUT_PERSISTENT_FUNC(state, ...)
#define _TIMEOUT_PERSISTENT_FUNC(state, action, ...)
    #define EXEC(action, ...)
    #define EXEC_ASYNC(action, ...)
#else
    #define UI(...)
	#define SEND_EVENT(...)
	#define _UI(uiEvent, ...)
    #define _SEND_EVENT(uiEvent, ...)
    #define TIMEOUT_FUNC(state, ...)
    #define _TIMEOUT_FUNC(state, action, ...)
#define TIMEOUT_PERSISTENT_FUNC(state, ...)
#define _TIMEOUT_PERSISTENT_FUNC(state, action, ...)
    #define EXEC(...)
    #define _EXEC(action, ...)
    #define EXEC_ASYNC(...)
    #define _EXEC_ASYNC(action, ...)
#endif

#define TIMEOUT(state, timeout)
#define EXT_TIMER(state)
#define IGNORE_NON_IDLE_MONITOR(state)
#define DEF_VAL(varName, val)
#define VAR(varName, val)
#define CONFIG_VAR(varName, val)
#define TEMP_VAR(varName, val)
#define INSTANCE_KEY(varName, val)
#define ADD_SM(initState)
#define WAIT_FLOW_END_STATE(flowEndState)
#endif

#ifdef __cplusplus
}
#endif

#endif /* _VDM_SMM_DECLARE_H_ */
/// @endcond
