/*
 *******************************************************************************
 *
 * vdm_client_pl_dlpkg.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_client_pl_dlpkg.h
 *
 * \brief	Download Package APIs
 *
 * The Download Package ensures that there is sufficient space before
 * downloading, incrementally appends downloaded chunks of a package, and
 * removes the package from non-volatile storage when it is no longer required.
 * In a typical file system, the downloaded package is stored in a file or in
 * flash memory.
 *
 * The OMA DM Protocol Engine framework requires that the download package be uniquely
 * identified by a string. Since the framework may have to access the downloaded
 * package after restarting, the download package handle cannot be a pointer,
 * but must be a string.
 *******************************************************************************
 */
#ifndef VDM_CLIENT_PL_DLPKG_H
#define VDM_CLIENT_PL_DLPKG_H

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @defgroup pl_dlpkg	Download Package
 * @ingroup pl
 * @{ */

/*!
 *******************************************************************************
 * Set the full path to the directory that contains the DP file. Use on
 * platforms that support a file system.
 *
 * \param	inPkgPath		Full path to the directory
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_Client_PL_Dlpkg_setFullPath(const char *inPkgPath);

/*!
 *******************************************************************************
 * Clear the full path to the directory that contains the DP file.
 *
 * \see	VDM_Client_PL_Dlpkg_setFullPath
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_Client_PL_Dlpkg_clearFullPath(void);

/*!
 *******************************************************************************
 * Create a download package handler.
 *
 * OMA DM Protocol Engine passes the URI node in the DM Tree of the download package as
 * an optional parameter, which can be used to create a string handle for the
 * package, such as a filename.
 *
 * \param	inURI			A URI string set by the caller; use this string to
 *                          create a file name, if desired
 * \param	outDlpkgHandle	The handle to a new download package<br>
 *							The handle can be the full path and file name
 *							of the file, or any other string id if not using
 *							a file system. This string will later be used
 *							to identify the file.
 *
 * \note	The caller must free the allocated string.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_Client_PL_Dlpkg_create(const char *inURI,
	char **outDlpkgHandle);

/*!
 *******************************************************************************
 * Write the next chunk of bytes from a current Download session.
 *
 * A package is normally downloaded in chunks. For each chunk, OMA DM Protocol Engine
 * passes the data, the chunk size, and its offset.
 *
 * \param	inDlpkgHandle	The download package handle returned in \ref
 *							VDM_Client_PL_Dlpkg_create
 * \param	inOffset		The offset within the download to write
 *							the data chunk
 * \param	inData			The data to write
 * \param	inDataSize		The size of \a inData, in bytes
 * \param	outOffset		The actual size of file that was written to the
 *                          disk (in bytes).
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_Client_PL_Dlpkg_writeChunk(
	const char *inDlpkgHandle,
	IU64 inOffset,
	IU8 *inData,
	IU32 inDataSize,
	IU64 *outOffset);

/*!
 *******************************************************************************
 * Get the size of the current package in storage.
 *
 * Before resuming a package download OMA DM Protocol Engine synchronizes between the
 * information stored in dlresume.dat and the actual downloaded upadate package
 * (DP) size.
 *
 * \param	inURI			The download package uri sent to
 *							VDM_Client_PL_Dlpkg_create
 * \param	outSize			The size of the package part downloaded so far, in
 *                          bytes count.
 *                          This value will be 0 if the package is not found.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_Client_PL_Dlpkg_getPkgSize(
	const char *inURI,
	IU64        *outSize);

/*!
 *******************************************************************************
 * Delete a download package from device.
 *
 * When the package is fully downloaded, OMA DM Protocol Engine notifies the DM Client
 * application for processing. Once the update is complete, the DM Client
 * application can remove the package. OMA DM Protocol Engine will always try to remove
 * the package when it receives notification that processing is finished by
 * calling this API. Therefore, if the package doesn't exist, the API
 * must assume that the DM Client application removed it and return success
 * (VDM_ERR_OK).
 *
 * \note 	There is an additional callback function (VDM_SCOMO_DP_DeletePkgCB)
 *  		that can be use to delete files	at clean up.
 *
 * \param	inDlpkgHandle	The download package handle returned in \ref
 *							VDM_Client_PL_Dlpkg_create
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_Client_PL_Dlpkg_remove(const char *inDlpkgHandle);

/*!
 *******************************************************************************
 * Get the maximum size available for a download package. Before downloading a
 * package, OMA DM Protocol Engine verifies that there is enough storage space for it.
 *
 * \param	outDlpkgMaxSize		The maximum size available for a download
 *                              package
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_Client_PL_Dlpkg_getMaxSize(IU64 *outDlpkgMaxSize);

/*! @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

