/*
 *******************************************************************************
 *
 * vdm_utl_logger_inl.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/// @cond EXCLUDE

#ifndef VDM_UTL_LOGGER_INL_H__
#define VDM_UTL_LOGGER_INL_H__

#ifdef __cplusplus
extern "C" {
#endif

/*
 *******************************************************************************
 * \file vdm_utl_logger_inl.h
 *
 * \brief	This file hides macros that are of no interest
 *			to the logger user, leaving vdm_utl_logger.h with only the API
 *
 * !!! This file should not appear in the doxygen documentation !!!
 *******************************************************************************
 */
#ifndef VDM_UTL_LOGGER_H__
#error "vdm_utl_logger_inl.h must be included from vdm_utl_logger only"
#endif

#include <vdm_client_pl_log.h>
#include <vdm_pl_string.h>

#define MAX_HEX_PRINT_LEN 100

// Logger's "local" functions
IBOOL VDM_UTL_Logger_isAboveThreshold(IU32 inComponentId,
	E_VDM_LOGLEVEL_TYPE inLevel);

void VDM_UTL_Logger_lock(void);
void VDM_UTL_Logger_unlock(void);
void VDM_UTL_Logger_dumpHex(char *inBufName, IU8 *inBuf, IU32 inBufLen);
void VDM_UTL_Logger_dumpFormattedHex(const void *inData, IU32 inLength);
void VDM_UTL_Logger_dumpFormattedHex2(const char *inMsg, const void *inData,
	IU32 inLength);

extern const char *VDM_UTL_Logger_getComponentString(IU32 id);

// Used to limit the size of some printouts
#define VDM_LOG_ITEM_PRINTOUT_LEN 100

/* If file name is longer than 20, use only last 20 chars. */
const char *__vdmfile__(const char *fName);

//This is for an overloading Macros trick
#define GET_LOG_MACRO_NAME(_11, _10, _9, _8, _7, _6, _5, _4, _3, _2, _1, NAME, ...) NAME

#define  VDM_logError_noArgs(msg)  \
	VDM_logError_Func(__vdmfile__(__FILE__), __LINE__, VDM_COMPONENT_ID, msg)
#define  VDM_logError_args(format, ...)  \
	VDM_logError_Func(__vdmfile__(__FILE__), __LINE__, VDM_COMPONENT_ID, format, __VA_ARGS__)

#define  VDM_logTRACE_noArgs(msg)  \
	VDM_logTRACE_Func(__vdmfile__(__FILE__), __LINE__, VDM_COMPONENT_ID, msg)
#define  VDM_logTRACE_args(format, ...)  \
	VDM_logTRACE_Func(__vdmfile__(__FILE__), __LINE__, VDM_COMPONENT_ID, format, __VA_ARGS__)

#define  VDM_logWarning_noArgs(msg)  \
	VDM_logWarning_Func(__vdmfile__(__FILE__), __LINE__, VDM_COMPONENT_ID, msg)
#define  VDM_logWarning_args(format, ...)  \
	VDM_logWarning_Func(__vdmfile__(__FILE__), __LINE__, VDM_COMPONENT_ID, format, __VA_ARGS__)

#define  VDM_logNotice_noArgs(msg)  \
	VDM_logNotice_Func(__vdmfile__(__FILE__), __LINE__, VDM_COMPONENT_ID, msg)
#define  VDM_logNotice_args(format, ...)  \
	VDM_logNotice_Func(__vdmfile__(__FILE__), __LINE__, VDM_COMPONENT_ID, format, __VA_ARGS__)

#define  VDM_logInfo_noArgs(msg)  \
	VDM_logInfo_Func(__vdmfile__(__FILE__), __LINE__, VDM_COMPONENT_ID, msg)
#define  VDM_logInfo_args(format, ...)  \
	VDM_logInfo_Func(__vdmfile__(__FILE__), __LINE__, VDM_COMPONENT_ID, format, __VA_ARGS__)

#define  VDM_logDebug_noArgs(msg)  \
	VDM_logDebug_Func(__vdmfile__(__FILE__), __LINE__, VDM_COMPONENT_ID, msg)
#define  VDM_logDebug_args(format, ...)  \
	VDM_logDebug_Func(__vdmfile__(__FILE__), __LINE__, VDM_COMPONENT_ID, format, __VA_ARGS__)

#define  VDM_logVerbose_noArgs(msg)  \
	VDM_logVerbose_Func(__vdmfile__(__FILE__), __LINE__, VDM_COMPONENT_ID, msg)
#define  VDM_logVerbose_args(format, ...)  \
	VDM_logVerbose_Func(__vdmfile__(__FILE__), __LINE__, VDM_COMPONENT_ID, format, __VA_ARGS__)

#define  VDM_logResult_noArgs(result, msg)  \
	VDM_logResult_Func(__vdmfile__(__FILE__), __LINE__, VDM_COMPONENT_ID, result, msg)
#define  VDM_logResult_args(result, format, ...)  \
	VDM_logResult_Func(__vdmfile__(__FILE__), __LINE__, VDM_COMPONENT_ID, result, format, __VA_ARGS__)

/* This macro is used to extract the component id implicitly.
 * VDM_COMPONENT_ID should be defined in each component's standard header,
 * assigning it the enum value of the component (see \ref E_VDM_COMPONENT_TYPE in
 * vdm_components.h).
 *
 * For example, for FUMO component:
 * in file vdm_fumo_std.h:
 * #define VDM_COMPONENT_ID	(E_VDM_COMPONENT_FUMO)
 */

void VDM_logResult_Func(const char *fName, int LineNum, IU32 componentId, VDM_Error result, const char *format, ...);
void VDM_logError_Func(const char *fName, int LineNum, IU32 componentId, const char *format, ...);
void VDM_logWarning_Func(const char *fName, int LineNum, IU32 componentId, const char *format, ...);
void VDM_logNotice_Func(const char *fName, int LineNum, IU32 componentId, const char *format, ...);
void VDM_logInfo_Func(const char *fName, int LineNum, IU32 componentId, const char *format, ...);
void VDM_logDebug_Func(const char *fName, int LineNum, IU32 componentId, const char *format, ...);
void VDM_logVerbose_Func(const char *fName, int LineNum, IU32 componentId, const char *format, ...);
void VDM_log_Func(const char *fName, int LineNum, IU32 componentId, const char *format, ...);
void VDM_logTRACE_Func(const char *fName, int LineNum, IU32 componentId, const char *format, ...);

/* VDM_logDumpHex */
#define VDM_logDumpHex(inLevel, inBufName, inBuf, inLen)                    \
	do {                                                                    \
		VDM_UTL_Logger_lock();                                              \
		if (VDM_UTL_Logger_isAboveThreshold((VDM_COMPONENT_ID), (inLevel)))  \
		{                                                               \
			VDM_Client_PL_logPrefix(E_VDM_LOGLEVEL_Debug, "%s.%5u: [%s] ",  \
				__vdmfile__(__FILE__), __LINE__, VDM_UTL_Logger_getComponentString(VDM_COMPONENT_ID)); \
			VDM_UTL_Logger_dumpHex(inBufName, inBuf, inLen);            \
		}                                                               \
		VDM_UTL_Logger_unlock();                                            \
	} while (0)

/* VDM_logDumpFormattedHex */
#define VDM_logDumpFormattedHex(inBuf, inLen)                               \
	do {                                                                    \
		VDM_UTL_Logger_lock();                                              \
		if (VDM_UTL_Logger_isAboveThreshold((VDM_COMPONENT_ID), (E_VDM_LOGLEVEL_Debug))) \
		{                                                               \
			VDM_Client_PL_logPrefix(E_VDM_LOGLEVEL_Debug, "%s.%5u: [%s]",   \
				__vdmfile__(__FILE__), __LINE__, VDM_UTL_Logger_getComponentString(VDM_COMPONENT_ID)); \
			VDM_UTL_Logger_dumpFormattedHex(inBuf, inLen);              \
		}                                                               \
		VDM_UTL_Logger_unlock();                                            \
	} while (0)

#define VDM_logDumpFormattedHex2(inLevel, inMsg, inBuf, inLen)              \
	do {                                                                    \
		VDM_UTL_Logger_lock();                                              \
		if (VDM_UTL_Logger_isAboveThreshold((VDM_COMPONENT_ID), (inLevel)))  \
		{                                                               \
			VDM_Client_PL_logPrefix(E_VDM_LOGLEVEL_Debug, "%s.%5u: [%s]",   \
				__vdmfile__(__FILE__), __LINE__, VDM_UTL_Logger_getComponentString(VDM_COMPONENT_ID)); \
			VDM_UTL_Logger_dumpFormattedHex2(inMsg, inBuf, inLen);      \
		}                                                               \
		VDM_UTL_Logger_unlock();                                            \
	} while (0)

#ifdef __ANDROID__
//Used for Java code (no preprocessor for file, line, and component ID)
//note: must #include <vdm_client_pl_log_android.h>
// used currently only in vsm

#define VDM_logJavaMsgComponent(level, component, tag, msg)                 \
	do {                                                                    \
		VDM_UTL_Logger_lock();                                              \
		if (VDM_UTL_Logger_isAboveThreshold((component), (level)))           \
		{                                                               \
			VDM_Client_PL_Android_logPrefix((level), "%s: [%s] ",         \
				(tag), VDM_UTL_Logger_getComponentString(component));     \
			VDM_Client_PL_Log_Android_logMsg((tag), (msg));                 \
		}                                                               \
		VDM_UTL_Logger_unlock();                                            \
	} while (0)

#define VDM_logJavaMsg(level, tag, msg)                                     \
	do {                                                                    \
		VDM_UTL_Logger_lock();                                              \
		VDM_Client_PL_Android_logPrefix((level), "%s: ", (tag));                \
		VDM_Client_PL_Log_Android_logMsg((tag), (msg));                     \
		VDM_UTL_Logger_unlock();                                            \
	} while (0)

#endif  //__ANDROID__

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

/// @endcond

