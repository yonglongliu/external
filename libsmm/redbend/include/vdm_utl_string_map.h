/*
 *******************************************************************************
 *
 * vdm_utl_string_map.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_utl_string_map.h
 *
 * \brief	String Map (Associative Array) API
 *******************************************************************************
 */

#ifndef VDM_UTL_STRING_MAP_H
#define VDM_UTL_STRING_MAP_H

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *******************************************************************************
 * Set a key-value pair to a map.
 * If the key already exists the value will be replaced.
 *
 * \param	inMap		Handle to the map
 * \param	inKey		Key
 * \param	inValue		Value
 *
 * \return	VDM_ERR_OK on success, or VDM_ERR_MEMORY if there is a memory
 *			problem
 *******************************************************************************
 */
extern VDM_Error VDM_UTL_StringMap_set(VDM_UTL_Map_t *inMap, const char *inKey,
    const char *inValue);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

