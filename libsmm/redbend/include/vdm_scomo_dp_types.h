/*
 *******************************************************************************
 *
 * vdm_scomo_dp_types.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_scomo_dp_types.h
 *
 * \brief	SCOMO Delivery Package (DP) Types and Constants
 ******************************************************************************
 */
#ifndef _VDM_SCOMO_DP_TYPES_H_
#define _VDM_SCOMO_DP_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <vdm_types.h>
#include <vdm_scomo_types.h>

#define USB_DP_NAME     "USB_DP"

/*!
 *******************************************************************************
 * Callback invoked to confirm download of an available DP.
 *
 * \param	inDownloadDescriptor	Download descriptor.
 * \param	inScomoDPInstance		Handle to the SCOMO DP instance.
 * \param	inDmcContext			Context passed in during instance creation.
 *
 * \return	TRUE to start downloading the DP, FALSE to postpone
 *			until calling \ref VDM_SCOMO_DP_resumeDLSession
 *******************************************************************************
 */
typedef IBOOL (*VDM_SCOMO_DP_confirmDownloadCB)(
	VDM_Downloader_DD_t *inDownloadDescriptor,
	VDM_Handle_t inScomoDPInstance,
	void *inDmcContext);

/*!
 *******************************************************************************
 * Callback invoked to confirm installation of downloaded DP.
 *
 * \param	inScomoDPInstance	Handle to SCOMO DP instance.
 * \param	inDmcContext		Context passed in during instance creation.
 *
 * \return	TRUE to start installation, FALSE to postpone installation until
 *			calling \ref VDM_SCOMO_DP_executeInstall or after a reboot
 *******************************************************************************
 */
typedef IBOOL (*VDM_SCOMO_DP_ConfirmInstallCB)(VDM_Handle_t inScomoDPInstance,
	void *inDmcContext);

/*!
 *******************************************************************************
 * Callback invoked to start DP installation.
 *
 * \param	inScomoDPInstance	Handle to SCOMO DP instance.
 * \param	inDmcContext		Context passed in during instance creation.
 * \param	inIsActive			A flag indicating whether the DCs in this DP
 *								should be installed in Active mode.
 * \param	outResult			Used in synchronous updates only.
 *
 * \return	TRUE if synchronous installation finished, or FALSE if asynchronous
 *			installation, in which case SCOMO DP must be notified upon
 *			completion by calling \ref VDM_SCOMO_DP_triggerReportSession
 *******************************************************************************
 */
typedef IBOOL (*VDM_SCOMO_DP_InstallCB)(VDM_Handle_t inScomoDPInstance,
	void *inDmcContext,
	IBOOL inIsActive,
	E_VDM_SCOMO_RESULT_t *outResult);

/*!
 *******************************************************************************
 * Callback invoked to write chunk.
 *
 * \param	inScomoDPInstance	Handle to SCOMO DP instance.
 * \param	inOffset		    Offset of the current chunk
 * \param	inData			    The buffer where the read data resides
 * \param	inDataSize		    Size of the data buffer
 * \param	inPkgName	        Name of package
 * \param	outOffset		    The file size on disk after the write
 *
 * \return	VDM_ERR_OK on success, or:
 *			VDM_ERR_MEMORY
 *			VDM_ERR_MO_STORAGE.
 *******************************************************************************
 */
typedef VDM_Error (*VDM_SCOMO_DP_writeChunkCB)(VDM_Handle_t inScomoDPInstance,
	IU64 inOffset, IU8 *inData, IU32 inDataSize, char *inPkgName,
	IU64 *outOffset);
/*!
 * Callbacks that may be implemented externally.
 */

/*!
 *******************************************************************************
 * Callback invoked to check the update is external or internal
 *
 * \param	inDownloadDescriptor	Download descriptor.
 * \param	inScomoDPInstance		Handle to the SCOMO DP instance.
 * \param	inDmcContext			Context passed in during instance creation.
 *
 * \return	TRUE is external update, FALSE is internal update
 *******************************************************************************
 */
typedef IBOOL (*VDM_SCOMO_DP_onDdReceivedCB)(
	VDM_Downloader_DD_t *inDownloadDescriptor,
	getMaxSizeCB_t *getMaxSizeCb,
	getPkgSizeCB_t *getPkgSizeCb);

/*!
 *******************************************************************************
 * Callback invoked to delete the DP file.
 *
 * \note The porting layer (VDM_Client_PL_Dlpkg_remove) is always used to
 *  delete DP files. In addition, this callback is also used (if registered).
 *
 * \param	inScomoDPInstance	Handle to SCOMO DP instance.
 *
 * \return	None
 *******************************************************************************
 */
typedef void (*VDM_SCOMO_DP_DeletePkgCB)(VDM_Handle_t inScomoDPInstance);

typedef struct {
	VDM_SCOMO_DP_confirmDownloadCB confirmDownloadCB;           //!< Confirm DP download callback (optional, may be NULL)
	VDM_SCOMO_DP_ConfirmInstallCB confirmInstallCB;             //!< Confirm DP installation callback (optional, may be NULL)
	VDM_SCOMO_DP_InstallCB executeInstallCB;                    //!< Process DP installation callback (mandatory)
	VDM_SCOMO_DP_writeChunkCB writeExternalChunk;               //!< Write DP chunk (optional, may be NULL)
	VDM_SCOMO_DP_onDdReceivedCB onDdReceivedCB;                 //!< DD was downloaded
	VDM_SCOMO_DP_DeletePkgCB deletePkgCB;                       //!< Delete the downloaded file
} VDM_SCOMO_DP_Callbacks_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

