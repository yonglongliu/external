/*
 *******************************************************************************
 *
 * vdm_dd_fields.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_dd_fields.h
 *
 * \brief	OMA DM Protocol Engine download descriptor fields
 *******************************************************************************
 */

#ifndef _VDM_DD_FIELDS_H_
#define _VDM_DD_FIELDS_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum E_VDM_DDField_t {
	E_VDM_DDField_size,                 	//!< Number of bytes to be downloaded from the URI
	E_VDM_DDField_objectURI,                //!< URI (usually a URL) from which the media object can be loaded
	E_VDM_DDField_type,                     //!< MIME type of the media object
	E_VDM_DDField_name,                     //!< A user readable name of the media object that identifies the object to the user
	E_VDM_DDField_DDVersion,                //!< Version of the Download Descriptor technology
	E_VDM_DDField_vendor,                   //!< The organisation that provides the media object
	E_VDM_DDField_description,              //!< A short textual description of the media object
	E_VDM_DDField_installNotifyURI,         //!< URI (or URL) to which an installation status report is to be sent
	E_VDM_DDField_nextURL,                  //!< URL to which the client should navigate in case the user selects to invoke a browsing action after the download transaction has completed
	E_VDM_DDField_infoURL,                  //!< A URL for further describing the media object
	E_VDM_DDField_iconURI,                  //!< The URI of an icon
	E_VDM_DDField_installParam,             //!< An installation parameter associated with the downloaded media object
	E_VDM_DDField_PreDownloadMessage,       //!< Verizon-specific
	E_VDM_DDField_PostDownloadMessage,      //!< Verizon-specific
	E_VDM_DDField_PostUpdateMessage,        //!< Verizon-specific
	E_VDM_DDField_PreDownloadURL,           //!< Verizon-specific
	E_VDM_DDField_PostDownloadURL,          //!< Verizon-specific
	E_VDM_DDField_PostUpdateURL,            //!< Verizon-specific
	E_VDM_DDField_RequiredInstallParameter, //!< Verizon-specific
	E_VDM_DDField_objectVersion,            //!< DLOTA 2.0
	E_VDM_DDField_objectID,                 //!< DLOTA 2.0
	E_VDM_DDField_envType,                  //!< Daimler-specific
	E_VDM_DDField_metaUri,                  //!< Daimler-specific
	E_VDM_DDField_count                   	//!< Must be last
} E_VDM_DDField_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

