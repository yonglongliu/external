/*
 *******************************************************************************
 *
 * vdm_utl_url.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_utl_url.h
 *
 * \brief	URL parsing utilities
 *
 *******************************************************************************
 */
#ifndef VDM_UTL_URL_H
#define VDM_UTL_URL_H               //!< Internal

#ifdef __cplusplus
extern "C" {
#endif

#include <vdm_pl_types.h>
#include <vdm_error.h>

/*!
 *******************************************************************************
 * Parse a URL to get host name and port.
 *
 * For example, "ildev2.redbend.com:8080" returns host name "ildev2.redbend.com"
 * and port "8080".
 *
 * \param	inHostAndPort	The URL
 * \param	inDefaultPort	Default port to return if URL does not contain port
 *							number
 * \param	inHostSize		Size of \a inHostSize
 * \param	outHost			Pre-allocated buffer to store host name
 * \param	outPort			Port number
 *
 * \return	VDM_ERR_OK					on success,
 *			VDM_ERR_BAD_INPUT			if an argument is missing,
 *			VDM_ERR_BUFFER_OVERFLOW		if \a outHost is too small, or
 *			VDM_ERR_BAD_URL				if the URL could not be parsed
 *******************************************************************************
 */
VDM_Error VDM_UTL_Url_parseHostAndPort(char *inHostAndPort, IU16 inDefaultPort,
	IU32 inHostSize, char *outHost, IU16 *outPort);

typedef enum {
	E_VDM_UTL_URL_PROTO_HTTP = 0,
	E_VDM_UTL_URL_PROTO_HTTPS = 1,
} VDM_UTL_Url_proto_t;

typedef struct VDM_UTL_Url_t {
	VDM_UTL_Url_proto_t proto;
	char *host;
	IU16 port;
	char *path;
} VDM_UTL_Url_t;

/* Domain  http://www.10bis.co.il
 *         http://www.10bis.co.il:8080
 *         http://www.10bis.co.il/Restaurants
 *         http://www.10bis.co.il:8080/Restaurants
 * IPv4    http://192.168.71.203
 *         http://192.168.71.203/index.html
 *         http://192.168.71.203:8080
 *         http://192.168.71.203:8080/index.html
 * IPv6    http://[2001:db8:85a3:8d3:1319:8a2e:370:7348]
 *         http://[2001:db8:85a3:8d3:1319:8a2e:370:7348]:8080
 *         http://[2001:db8:85a3:8d3:1319:8a2e:370:7348]/index.html
 *         http://[2001:db8:85a3:8d3:1319:8a2e:370:7348]:8080/index.html
 */
VDM_Error VDM_UTL_Url_str2struct(const char *inUrl, VDM_UTL_Url_t **outStruct);

const char *VDM_UTL_Url_struct2str(VDM_UTL_Url_t *inStruct);

void VDM_UTL_Url_free(VDM_UTL_Url_t **ioStruct);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

