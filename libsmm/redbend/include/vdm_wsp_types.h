/*
 *******************************************************************************
 *
 * vdm_wsp_types.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_wsp_types.h
 *
 * \brief	WSP Types
 *******************************************************************************
 */

/// @cond EXCLUDE

#ifndef VDM_WSP_QUEUE_TYPES_H
#define VDM_WSP_QUEUE_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

//=========================
// typedefs and definitions
//=========================
#define VDM_WSP_INVALID_SEC -1

#define VDM_WSP_FieldType_PDUTypePush 0x06

#define VDM_WSP_FieldType_SEC 0x91
#define VDM_WSP_FieldType_MAC 0x92
#define VDM_WSP_FieldLength_MAC 40
#define VDM_WSP_FieldType_WAPApplication 0xaf

#define NIA_TOTAL_HEADERS_LEN 6
#define NIA_TOTAL_HEADERS_LEN_DOCOMO 8
#define BOOT_TOTAL_HEADERS_LEN 50

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
/// @endcond

