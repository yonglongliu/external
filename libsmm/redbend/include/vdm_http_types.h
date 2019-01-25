/*
 *******************************************************************************
 *
 * vdm_http_types.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \internal
 * \file vdm_http_types.h
 *
 * \brief
 *******************************************************************************
 */

#ifndef VDM_HTTP_TYPES_H_
#define VDM_HTTP_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <vdm_utl_map.h>

/*!
 *******************************************************************************
 * Callback invoked before opening an HTTP connection. The callback is used to
 * control the URL used in opening the HTTP connection.
 *
 * \param	inContext	Context passed on registration.
 * \param	ioUrl		Pointer to the URL.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_notifyBeforeOpenCB_t)(VDM_Handle_t inContext,
	char **ioUrl);

/*!
 *******************************************************************************
 * Callback invoked before sending an HTTP message. The callback is used to
 * control HTTP headers.
 *
 * \param	inContext		Context passed on registration.
 * \param	ioHeadersMap	HTTP headers map, a \ref VDM_UTL_Map_getNext value.
 *							Each pair contains a header name key and a value.
 *							Use \ref VDM_UTL_StringMap_set to set the headers.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_notifyBeforeSendCB_t)(VDM_Handle_t inContext,
	VDM_UTL_Map_t *ioHeadersMap);

/*!
 *******************************************************************************
 * Callback invoked after Receiving HTTP Headers. The callback is used to
 * monitor HTTP headers.
 *
 * \param	inContext		Context passed on registration.
 * \param	inHttpResponseCode	HTTP response code (e.g. 200 or 404)
 * \param	ioHeadersMap	HTTP headers map, a \ref VDM_UTL_Map_getNext value.
 *							Each pair contains a header name key and a value.
 *							Use \ref VDM_UTL_StringMap_set to set the headers.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_notifyHttpResponseCB_t)(VDM_Handle_t inContext,
	IU32 inHttpResponseCode, VDM_Handle_t ioHeadersMap);

/// @cond EXCLUDE

/*
 * Structure of callback and context invoked before any send communication
 */
typedef struct {
	VDM_notifyBeforeSendCB_t notifyCB;  // Callback invoked before sending data
	void *context;  // HTTP context
} VDM_notifyHttpHeaders_t;

/*
 * Structure of callback and context invoked after receiving HTTP headers
 */
typedef struct  {
	VDM_notifyHttpResponseCB_t notifyCB; // Callback invoked
	void *context; // HTTP context
} VDM_notifyHttpResponse_t;

/// @endcond

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // VDM_HTTP_TYPES_H_

