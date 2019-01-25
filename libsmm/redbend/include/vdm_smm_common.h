/*
 *******************************************************************************
 *
 * vdm_smm_common.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file vdm_smm_common.h
 *
 * \brief
 *******************************************************************************
 */

#ifndef VDM_SMM_COMMON_H_
#define VDM_SMM_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

IS32 VDM_SMM_setVarInt(VDM_SMM_Value_t *var, IS32 value);

IS32 VDM_SMM_setVarUint(VDM_SMM_Value_t *var, IU32 value);

IS32 VDM_SMM_setVarUint64(VDM_SMM_Value_t *var, IU64 value);

IS32 VDM_SMM_setVarStr(VDM_SMM_Value_t *var, const char *strValue);

IS32 VDM_SMM_setVarBin(VDM_SMM_Value_t *var, const void *binValue, IU32 size);

IS32 VDM_SMM_setVarRet(VDM_SMM_Value_t *var);

void VDM_SMM_freeValue(VDM_SMM_Value_t *value);

void VDM_SMM_freeValues(VDM_SMM_Value_t *values);

void VDM_SMM_freeEvent(VDM_SMM_Event_t *ev);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // VDM_SMM_COMMON_H_
