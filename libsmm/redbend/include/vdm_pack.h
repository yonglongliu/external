/*
 *******************************************************************************
 *
 * vdm_pack.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_pack.h
 *
 * \brief	utilities to Pack/Unpack files
 *
 *******************************************************************************
 */

#ifndef _VDM_PACK_H_
#define _VDM_PACK_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Callback to report extract progress */
typedef void (*extractProgressCb)(IU32 currProg, IU32 maxProg);

/* Callback for USB split DP */
typedef VDM_Error (*executionCb)(IU8 *inData, IBOOL isFirstIteration ,IU32 inDataSize);

typedef struct {
	extractProgressCb progCb;
	executionCb		  execCb;
} VDM_PACK_Callbacks_t;

/**
 *	Receives the path for the compressed folder and extracts
 *	the specific file from the folder.
 *
 * \param     inPackedFilePath:   The full path of the compressed
 *                                folder.
 * \param     inInternalFilePath: The name of the internal file in
 *                                inPackedFilePath that is to be
 *                                extracted.
 * \param     inTargetFilePath:   The path to save the extracted
 *                                file to.
 * \param     inCb:			      Progress callback pointer
 *
 * \return      0:     Success
 *				Not 0: Error specific
 */
VDM_Error VDM_PACK_extractInternalFromPackedFile(
	const char *inPackedFilePath,
	const char *inInternalFilePath,
	const char *inTargetFilePath,
	VDM_PACK_Callbacks_t *inCb);

/**
 *  Receives the path for the zip file and the DP file name and returns
 *  the uncompressed size of the DP file
 *
 * \param     inPackedFilePath:     The full path of the compressed
 *                                  folder.
 * \param     inInternalFilePath:   The name of the DP file in
 *                                  inPackedFilePath
 * \param     uncompressedFileSize: IU64 Pointer to store the DP file size
 *
 * \return      0:     Success
 *              Not 0: Error specific
 */
VDM_Error VDM_PACK_getUncompressedFileSize(
	const char *inPackedFilePath,
	const char *inInternalFilePath,
	IU64 *uncompressedFileSize);


/*!
 *******************************************************************************
 * Compress directory into archive.
 *
 * \param   inArchivePath   Path of archive file.
 * \param   inArchiveName   Archive file name.
 * \param   inDirToCompress Directory from which files should be compress
 *
 * \return  VDM_ERR_OK on success.
 *
 *******************************************************************************
 */
extern VDM_Error  VDM_PACK_compress_dir(const char *inArchivePath,
	const char *inArchiveName, const char *inDirToCompress);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _VDM_PACK_H_ */
