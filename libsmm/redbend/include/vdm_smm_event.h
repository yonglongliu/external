/*
 *******************************************************************************
 *
 * vdm_smm_event.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file vdm_smm_event.h
 *
 * \brief SMM Event API
 *******************************************************************************
 */

#ifndef VDM_SMM_EVENT_H_    //!< Internal.
#define VDM_SMM_EVENT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <vdm_smm_types.h>

typedef struct VDM_SMM_CbContext_t {
	char *eventName;
	char *varName;
	E_VDM_SMM_VAR_TYPE_t varType;
} VDM_SMM_CbContext_t;

#define NO_VAR "NONE"
/*!
 ******************************************************************************
 * Create and initialize an SMM event.
 *
 * \param	inName		Event name.
 *
 * \return	Pointer to the event, a \ref VDM_SMM_Event_t structure or NULL
 *          if out of memory.
 ******************************************************************************
 */
VDM_SMM_Event_t *VDM_SMM_Event_create(const char *inName);

/*!
 *******************************************************************************
 * Destroy an SMM event. Free any memory allocated for the event.
 *
 * \param	ioEvent		Input: Pointer to the event
 *                      Output: NULL
 *
 * \return	None
 *******************************************************************************
 */
void VDM_SMM_Event_destroy(VDM_SMM_Event_t **ioEvent);

/*!
 *******************************************************************************
 * Set the name of the event.
 * If the name has already been set, the previous name is freed from memory.
 *
 * \param	inEvent		The event.
 * \param	inName		Event name.
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_MEMORY if out of memory
 *******************************************************************************
 */
VDM_Error VDM_SMM_Event_setName(VDM_SMM_Event_t *inEvent, const char *inName);

/*!
 *******************************************************************************
 * Add a value to an SMM event.
 *
 * \param	inEvent		The event.
 * \param	inValue		The value to add.
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_MEMORY if out of memory
 *******************************************************************************
 */
VDM_Error VDM_SMM_Event_addValue(VDM_SMM_Event_t *inEvent,
	VDM_SMM_Value_t *inVal);

/*!
 *******************************************************************************
 * Add an integer value to an SMM event.
 *
 * \param	inEvent		The event.
 * \param	inName		A name associated with the value.
 * \param	inValue		Integer value.
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_MEMORY if out of memory
 *******************************************************************************
 */
VDM_Error VDM_SMM_Event_addIntValue(VDM_SMM_Event_t *inEvent,
	char *inName, IS32 inValue);

/*!
 *******************************************************************************
 * Add an unsinged integer value to an SMM event.
 *
 * \param	inEvent		The event.
 * \param	inName		A name associated with the value.
 * \param	inValue		Unsigned integer value.
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_MEMORY if out of memory
 *******************************************************************************
 */
VDM_Error VDM_SMM_Event_addUintValue(VDM_SMM_Event_t *inEvent,
	char *inName, IU32 inValue);

/*!
 *******************************************************************************
 * Add an unsinged 64bit integer value to an SMM event.
 *
 * \param	inEvent		The event.
 * \param	inName		A name associated with the value.
 * \param	inValue		Unsigned 64bit integer value.
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_MEMORY if out of memory
 *******************************************************************************
 */
VDM_Error VDM_SMM_Event_addUint64Value(VDM_SMM_Event_t *inEvent,
	char *inName, IU64 inValue);

/*!
 *******************************************************************************
 * Add a string value to an SMM event.
 *
 * \param	inEvent		The event.
 * \param	inName		A name associated with the value.
 * \param	inValue		String value.
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_MEMORY if out of memory
 *******************************************************************************
 */
VDM_Error VDM_SMM_Event_addStringValue(VDM_SMM_Event_t *inEvent,
	char *inName, char *inValue);

/*!
 *******************************************************************************
 * Add a binary value to an SMM event.
 *
 * \param	inEvent		The event.
 * \param	inName		A name associated with the value.
 * \param	inValue		Binarry buffer.
 * \param	inSize		Size of \a inValue buffer.
 *
 * \return	VDM_ERR_OK on success, or
 *			VDM_ERR_MEMORY if out of memory
 *******************************************************************************
 */
VDM_Error VDM_SMM_Event_addBinValue(VDM_SMM_Event_t *inEvent,
	char *inName, void *inValue, IU32 inSize);

VDM_SMM_Value_t *VDM_SMM_Event_getValue(VDM_SMM_Event_t *inEvent, char *inName);

/*!
 *******************************************************************************
 * Build a callback context to be used by VDM_SMM_Event_sendEventCB.
 *
 * \param	inEventName		Event name.
 * \param	inVarName		Var name.
 *
 * \return	Pointer to a context or NULL on error;
 *******************************************************************************
 */
void *VDM_SMM_Event_buildCbContext(char *inEventName, char *inVarName);

/*!
 *******************************************************************************
 * Free a callback context that was previously built by
 * VDM_SMM_Event_buildCbContext.
 *
 * \param	inCtx		Pointer to context.
 *******************************************************************************
 */
void VDM_SMM_Event_freeCbContext(void *inCtx);

/**
 * Allocate new SMM event variable of type integer macro
 *
 * @param name - name of the variable
 * @param value - default value of the variable
 * @return the new allocated variable
 */
#define VDM_SMM_allocVarInt(varName, value) VDM_SMM_allocVarIntEx(#varName, value)

/**
 * Allocate new SMM event variable of type integer
 *
 * @param name - name of the variable
 * @param value - default value of the variable
 * @return the new allocated variable
 */
VDM_SMM_Value_t *VDM_SMM_allocVarIntEx(const char *name, IS32 value);

/**
 * Allocate new SMM event variable of type unsigned integer macro
 *
 * @param name - name of the variable
 * @param value - default value of the variable
 * @return the new allocated variable
 */
#define VDM_SMM_allocVarUint(varName, value) VDM_SMM_allocVarUintEx(#varName, value)

/**
 * Allocate new SMM event variable of type unsigned integer
 *
 * @param name - name of the variable
 * @param value - default value of the variable
 * @return the new allocated variable
 */
VDM_SMM_Value_t *VDM_SMM_allocVarUintEx(const char *name, IU32 value);

/**
 * Allocate new SMM event global variable of type unsigned integer
 *
 * @param machineName - name of the machine that has this global variable
 * @param name - name of the variable
 * @param value - default value of the variable
 * @return the new allocated variable
 */
VDM_SMM_Value_t *VDM_SMM_allocExternVarUint(const char *machineName,
	const char *name, IU32 value);

/**
 * Allocate new SMM event variable of type unsigned 64-bit integer
 *
 * @param name - name of the variable
 * @param value - default value of the variable
 * @return the new allocated variable
 */
VDM_SMM_Value_t *VDM_SMM_allocVarUint64Ex(const char *name, IU64 value);

/**
 * Allocate new SMM event variable of type unsigned long long int macro
 *
 * @param name - name of the variable
 * @param value - default value of the variable
 * @return the new allocated variable
 */
#define VDM_SMM_allocVarUint64(varName, value) VDM_SMM_allocVarUint64Ex(#varName, value)

/**
 * Allocate new SMM event variable of type string - macro
 *
 * @param name - name of the variable
 * @param strValue - default value of the variable
 * @return the new allocated variable
 */
#define VDM_SMM_allocVarStr(varName, strValue) VDM_SMM_allocVarStrEx(#varName, strValue)

/**
 * Allocate new SMM event variable of type string
 *
 * @param name - name of the variable
 * @param strValue - default value of the variable
 * @return the new allocated variable
 */
VDM_SMM_Value_t *VDM_SMM_allocVarStrEx(const char *name, const char *strValue);

/**
 * Allocate new SMM event variable of type binary - macro
 *
 * @param name - name of the variable
 * @param binValue - default value of the variable
 * @param size - size of binary value in bytes
 * @return the new allocated variable
 */
#define VDM_SMM_allocVarBin(varName, binValue, size) VDM_SMM_allocVarBinEx(#varName, binValue, size)

/**
 * Allocate new SMM event variable of type binary
 * @param name - name of the variable
 * @param binValue - default value of the variable
 * @param size - size of binary value in bytes
 * @return the new allocated variable
 */
VDM_SMM_Value_t *VDM_SMM_allocVarBinEx(const char *name, const void *binValue,
	IU32 size);

/**
 * Display a trace of the event and its variables
 *
 * @param event - the event to display
 */
void VDM_SMM_logEventVars(VDM_SMM_Event_t *event);

IBOOL validateEventVars(IU32 inEventListIndex,  VDM_SMM_Event_t *inEvent);

IS32 locateVarIndexByName(const char *inVarName);
IS32 locateEventIndexByName(const char *inEventName);

/*!
 *******************************************************************************
 * Send an event built from the data saved in the input context.
 *
 * \param	inCtx		Context.
 * \param	inVal		Var value.
 *
 *******************************************************************************
 */
void VDM_SMM_Event_sendEventCB(void *inCtx, void *inVal);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // VDM_SMM_EVENT_H_
