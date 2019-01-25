/*
 *******************************************************************************
 *
 * vdm_client_pl_storage.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_client_pl_storage.h
 *
 * \brief	Persistent Storage APIs
 *
 * OMA DM Protocol Engine does not assume that the device supports a file system. The
 * storage APIs support opening and closing a storage item, reading and
 * writing to and from an open storage item, and deleting a storage item from
 * persistent storage.
 *
 * In operating systems that use a file system, a storage item is typically
 * a file.
 *******************************************************************************
 */
#ifndef VDM_CLIENT_PL_STORAGE_H
#define VDM_CLIENT_PL_STORAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <vdm_error.h>

/*!
 * @defgroup pl_storage	Storage
 * @ingroup pl
 * @{
 */

/*!
 * Access type for storage items
 *
 * A storage item can be opened in read-only or write modes. If a non-existent
 * storage item is opened in write mode, the function must create the item.
 */
typedef enum {
	E_VDM_CLIENT_PL_Storage_Access_read,    /**< Read mode */
	E_VDM_CLIENT_PL_Storage_Access_write,   /**< Write mode, if files exists erase it */
	E_VDM_CLIENT_PL_Storage_Access_append   /**< Append mode, from start ("a+") */
} E_VDM_CLIENT_PL_Storage_Access_t;

/*!
 * OMA DM Protocol Engine defines the following types of storage items that it uses when
 * calling the storage Porting Layer APIs.
 */
typedef enum {
	E_VDM_CLIENT_PL_StorageItem_DMTree,     /**< DM Tree */
	E_VDM_CLIENT_PL_StorageItem_RecoveryDMTree, /**< Recovery DM Tree */
	E_VDM_CLIENT_PL_StorageItem_Config,     /**< Configuration file (not used by vDM)*/
	E_VDM_CLIENT_PL_StorageItem_DLResume_Name,   /**< Download resume data */
	E_VDM_CLIENT_PL_StorageItem_DLResume_Location,
	E_VDM_CLIENT_PL_StorageItem_Registry,    /** Settings and options for the various Framework components*/
	E_VDM_CLIENT_PL_StorageItem_InternalInfo,    /*Internal client storage used in downgrade */
	E_VDM_CLIENT_PL_StorageItem_DpCompatibility,      /**< DpCompatibility */
	E_VDM_CLIENT_PL_StorageItem_Last = 	E_VDM_CLIENT_PL_StorageItem_DpCompatibility
} E_VDM_CLIENT_PL_StorageItem_t;
/*!
 *******************************************************************************
 * Retrieves the name of the storage file.
 *
 * \param	inType		Type of storage item, an
 *						\ref E_VDM_CLIENT_PL_StorageItem_t value
 *
 * \return	Pointer to the name of the file, or NULL on failure
 *******************************************************************************
 */
extern const char *VDM_Client_PL_Storage_getItemFilename(E_VDM_CLIENT_PL_StorageItem_t inType);

/*!
 *******************************************************************************
 * Allocate memory for a storage item.
 *
 * \note	Free the memory using \ref VDM_PL_free or \ref VDM_PL_freeAndNullify
 *
 * \param	inType		Type of storage item, an
 *						\ref E_VDM_CLIENT_PL_StorageItem_t value
 *
 * \return	Pointer to allocated buffer, or NULL on failure
 *******************************************************************************
 */
extern const char *VDM_Client_PL_Storage_getPathDup(E_VDM_CLIENT_PL_StorageItem_t inType);

/*!
 *******************************************************************************
 * Load a file to a buffer.
 *
 * The function opens the file, reads and loads it to the preallocated buffer,
 * and then closes it.
 *
 * \param	inFileName	    The file name
 * \param	outBuffer	    The preallocated buffer to hold the file's content
 * \param   inBufSize       The size of \a outBuffer
 * \param   outReadCount    The number of bytes stored in \a outBuffer
 * \param   outFileSize     The file size in bytes
 *
 * \return	VDM_ERR_OK on success, VDM_ERR_BAD_INPUT,
 *          VDM_ERR_STORAGE_OPEN if there is a problem opening the file,
 *          VDM_ERR_STORAGE_READ if there is a problem reading the file, or
 *          VDM_ERR_BUFFER_OVERFLOW if the supplied buffer was too small to hold
 *          the file contents
 *******************************************************************************
 */
extern VDM_Error VDM_Client_PL_Storage_loadFile(const char *inFileName,
	void *outBuffer, IU32 inBufSize, IU32 *outReadCount, IU32 *outFileSize);

/*!
 *******************************************************************************
 * Open (stream) a storage item by specifying its type.
 *
 * Use this function to open any item with a \ref E_VDM_CLIENT_PL_StorageItem_t
 * value. For other items, use \ref VDM_Client_PL_Storage_openByName.
 *
 * A storage item can be opened in read-only or write modes. If a non-existent
 * storage item is opened in write mode, this function must create the item.
 *
 * \param	outHandle	Handle to the open storage item
 * \param	inType		Type of storage item, an
 *						\ref E_VDM_CLIENT_PL_StorageItem_t value
 * \param	inMode		Type of access required, an
 *                      \ref E_VDM_CLIENT_PL_Storage_Access_t value
 *
 * \return	VDM_ERR_OK on success, VDM_ERR_MEMORY if out of memory, or
 *          VDM_ERR_STORAGE_OPEN if there is a problem opening the item
 *******************************************************************************
 */
extern VDM_Error VDM_Client_PL_Storage_open(void **outHandle,
	E_VDM_CLIENT_PL_StorageItem_t inType, E_VDM_CLIENT_PL_Storage_Access_t inMode);

/*!
 *******************************************************************************
 * Open (stream) a storage item by specifying its name.
 *
 * A storage item can be opened in read-only or write modes. If a non-existent
 * storage item is opened in write mode, this function must create the item.
 *
 * \note	Do not use this function to open any file with a
 *			\ref E_VDM_CLIENT_PL_StorageItem_t value. Instead, use
 *			\ref VDM_Client_PL_Storage_open.
 *
 * \param	outHandle	Handle to the open storage item
 * \param	inFileName	The name of the file
 * \param	inMode		Type of access required, an
 *                      \ref E_VDM_CLIENT_PL_Storage_Access_t value
 *
 * \return	VDM_ERR_OK on success, VDM_ERR_MEMORY if out of memory, or
 *          VDM_ERR_STORAGE_OPEN if there is a problem opening the item
 *******************************************************************************
 */
extern VDM_Error VDM_Client_PL_Storage_openByName(void **outHandle,
	const char *inFileName, E_VDM_CLIENT_PL_Storage_Access_t inMode);

/*!
 *******************************************************************************
 * The function obtains the current value of the file position indicator for the
 * stream pointed to by inHandle.
 *
 * \param	inHandle		Handle to the open storage item
 *
 * \return	returns the current offset.  Otherwise, -1 is returned
 *******************************************************************************
 */
extern IS64 VDM_Client_PL_Storage_tell(void *inHandle);

/*!
 *******************************************************************************
 * Read a line from an open storage item.
 *
 * Read a line from the current position and append it, with a terminating null,
 * to \a outBuffer. After the read operation is finished, the file pointer
 * must be positioned at the end of the data read.
 *
 * \param	inHandle		Handle to the open storage item
 * \param	outBuffer		Pre-allocated buffer to store the string. A maximum
 *							of ( \a inBufferSize - 1 ) characters are read,
 *							stored in the buffer, and appended with a
 *							terminating null
 * \param	inBufferSize    The size of \a outBuffer
 *
 * \return	The string, or
 *          NULL if an error occurred or if there was nothing to read
 *******************************************************************************
 */
extern char *VDM_Client_PL_Storage_fgets(void *inHandle, void *outBuffer,
	IU32 inBufferSize);

/*!
 *******************************************************************************
 * Read data from storage.
 *
 * After the read operation is finished, the file pointer must be positioned
 * at the end of the data read.
 *
 * \param	inHandle		Handle to the storage item
 * \param	outBuffer		Buffer to store the read data
 * \param	inBufSize		The size of \a outBuffer, in bytes
 * \param	outReadCount	Number of bytes actually read<br>
 *							This will be \a inBufSize unless there is
 *							no more data, in which case the value must be 0.
 *
 * \return	VDM_ERR_OK on success, VDM_ERR_MEMORY if out of
 *          memory, or VDM_ERR_STORAGE_READ if there is a problem reading
 *******************************************************************************
 */
extern VDM_Error VDM_Client_PL_Storage_read(void *inHandle, void *outBuffer,
	IU32 inBufSize, IU32 *outReadCount);

/*!
 *******************************************************************************
 * Write data to storage.
 *
 * After the write operation is finished, the file pointer must be
 * positioned at the end of the data written.
 *
 * \param	inHandle		Handle to the storage item
 * \param	inData			Data to write.
 * \param	inLength		The length of \a inData, in bytes
 *
 * \return	VDM_ERR_OK on success, VDM_ERR_MEMORY if out of
 *          memory, or VDM_ERR_STORAGE_WRITE if there is a problem writing
 *******************************************************************************
 */
extern VDM_Error VDM_Client_PL_Storage_write(void *inHandle, const void *inData,
	IU32 inLength);

/*!
 *******************************************************************************
 * Close a storage item.
 *
 * \param	inHandle		Handle to the storage item
 * \param	inCommit		TRUE if written data should be committed;
 *							FALSE if storage was opened for reading
 *
 * \return	VDM_ERR_OK on success, VDM_ERR_MEMORY if out of memory,
 *          or VDM_ERR_STORAGE_COMMIT if there is a problem committing
 *******************************************************************************
 */
extern VDM_Error VDM_Client_PL_Storage_close(void *inHandle, IBOOL inCommit);

/*!
 *******************************************************************************
 * Delete a storage item, given its type.
 *
 * \param	inType		Type of storage item, an
 *						\ref E_VDM_CLIENT_PL_StorageItem_t value
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_Client_PL_Storage_delete(E_VDM_CLIENT_PL_StorageItem_t inType);

/*!
 *******************************************************************************
 * Delete a storage item, given its file name.
 *
 * \param	inFileName	The name of the file to delete.
 *
 * \return	None
 *******************************************************************************
 */
extern VDM_Error VDM_Client_PL_Storage_deleteByName(const char *inFileName);

/*!
 * File relative seek starting point
 */
typedef enum {
	E_VDM_CLIENT_PL_FSeek_START,	///< Seek from the beginning of the file
	E_VDM_CLIENT_PL_FSeek_CURRENT,	///< Seek from the current file pointer
	E_VDM_CLIENT_PL_FSeek_END		///< Seek back from the end of the file
} E_VDM_CLIENT_PL_FSeek_t;

/*!
 *******************************************************************************
 * Seek to an offset in a file relative to a starting point:
 * - Forward from the start of the file
 * - Forward from the current file pointer
 * - Backwards from the end of the file
 *
 * After the operation is finished, the file pointer must be positioned at the
 * offset on success, the beginning of the file if searching backwards, or the
 * end of the file if searching forward.
 *
 * \param	inHandle	Handle to the storage item
 * \param	inOffset	Offset to seek
 * \param	inSeekType  Seek starting point, an \ref E_VDM_CLIENT_PL_FSeek_t
 *						value
 *
 * \return	VDM_ERR_OK on success, or VDM_ERR_STORAGE_SEEK otherwise
 *******************************************************************************
 */
extern VDM_Error VDM_Client_PL_Storage_fileSeek(void *inHandle, IU64 inOffset,
	E_VDM_CLIENT_PL_FSeek_t inSeekType);

/*!
 *******************************************************************************
 * Sync a storage item with external storage (write all changes to file).
 *
 * \param	inHandle	Handle to the storage item
 *
 * \return	VDM_ERR_OK on success, or VDM_ERR_UNSPECIFIC otherwise
 *******************************************************************************
 */
extern VDM_Error VDM_Client_PL_Storage_sync(void *inHandle);

/*!
 * VDM storage porting layer stat structure
 */
typedef struct VDM_Client_PL_Storage_stat_t {
	IBOOL isExist; /**< File exist*/
	IBOOL isDirectory; /**< File is a directory */
	IBOOL isExecutable; /**< File is executable */
	IBOOL isWritable; /**< File is writable */
	IBOOL isReadable; /**< File is readable */
	IU64 availableSpace;  /**< disk free space */
	IU64 size;  /**< File size */
} VDM_Client_PL_Storage_stat_t;

/*!
 *******************************************************************************
 * Retrieve file statistics
 *
 * \param	inFileName	Full path of file
 * \param	outStat		statistics struct (VDM_Client_PL_Storage_stat_t)
 *
 * \return	VDM_ERR_OK even if file does not exist
 *******************************************************************************
 */
extern VDM_Error VDM_Client_PL_Storage_statByName(const char *inFileName,
	VDM_Client_PL_Storage_stat_t *outStat);

/*!
 * VDM storage porting layer permissions flags.
 */
#define VDM_PL_STORAGE_ADD_EXEC 0x1 /**< Add execute permission */
#define VDM_PL_STORAGE_ADD_WRITE 0x2 /**< Add write permission */
#define VDM_PL_STORAGE_ADD_READ 0x4 /**< Add read permission */
#define VDM_PL_STORAGE_REMOVE_EXEC 0x8 /**< Remove execute permission */
#define VDM_PL_STORAGE_REMOVE_WRITE 0x10 /**< Remove write permission */
#define VDM_PL_STORAGE_REMOVE_READ 0x20 /**< Remove read permission */

/*!
 *******************************************************************************
 * Set permissions
 *
 * \param	inFileName	Full path of file
 * \param	inFlags bitwise combination of VDM_PL_STORAGE_XXX flags
 *
 * \return	VDM_ERR_OK on success, or VDM_ERR_STORAGE_WRITE/VDM_ERR_STORAGE_READ
 *  otherwise
 *******************************************************************************
 */
extern VDM_Error VDM_Client_PL_Storage_setPermissions(const char *inFileName,
	IU32 inFlags);

/*!
 *******************************************************************************
 * Check if a file exists.
 *
 * \param	inFileName	File name to find
 *
 * \return	TRUE if file exists, or otherwise FALSE
 *******************************************************************************
 */
extern IBOOL VDM_Client_PL_Storage_isFileExists(const char *inFileName);

/*!
 *******************************************************************************
 * isFileExists
 *
 * \param	inDirName	Directory name to create
 *
 * \return	VDM_ERR_OK on success, or VDM_ERR_STORAGE_WRITE otherwise
 *******************************************************************************
 */
extern VDM_Error VDM_Client_PL_Storage_createDir(const char *inDirName);

/*!
 *******************************************************************************
 * Get the specified file size information from extracted file, without extracting the file.
 *
 * \return	The future uncompressed file size, (outSize)
 *******************************************************************************
 */
extern VDM_Error VDM_Client_PL_Storage_getSpecifiedFileSizeFromExtractedFile(
	char *inExtractedFileName, char *inFileName, IU64 *outSize);

/*!
 *******************************************************************************
 * Remove dir file.
 * Removing dir/files in recursive mode using rm -rf dommand*
 * \return	VDM_ERR_OK upon a successful call,
 *
 *******************************************************************************
 */
extern VDM_Error VDM_Client_PL_Storage_removeDir(const char *inFileName);

/*!
 *******************************************************************************
 * Copy file from source to destination.
 *
 * \param	inSrc	Path of file to copy.
 * \param	inDst	Destination path.
 *
 * \return	VDM_ERR_OK on success.
 *
 *******************************************************************************
 */
extern VDM_Error VDM_Client_PL_Storage_copyFile(char *inSrc, char *inDst);

/*!
 *******************************************************************************
 * Create link file to destination.
 *
 * \param	inDst	Destination path.
 *
 * \return	VDM_ERR_OK on success.
 *
 *******************************************************************************
 */
extern VDM_Error VDM_Client_PL_Storage_createLinkFile(char *inDst);

/**
 * Open directory in given path
 *
 * \param	inPath		Full path of the directory to open
 *          outHandle   pointer to return handler to the opened directory
 *
 * \return	0 - success, other value on failure.
 */
extern VDM_Error VDM_Client_PL_Storage_openDir(char *inPath, VDM_Handle_t *outHandle);

/**
 * Returns next file by name in the directory until all files were read.
 *
 * \param	outHandle       handler to the open directory
 *			ioFileName      Buffer to the file name found
 *			fileNameLength  Size of the buffer ioFileName
 *			outIsHasNext    Indicates if there are more files in directory
 *
 * \return	0 - success, other value on failure.
 */
extern VDM_Error VDM_Client_PL_Storage_getNextFileInDir(VDM_Handle_t *inHandle, char *ioFileName, IU32 fileNameLength, IBOOL *outIsHasNext);

/**
 * Closes a directory that was opened with given VDM_Client_PL_Storage_openDir function.
 *
 * \param	inHandle  handler to the directory
 *
 * \return	0 - success, other value on failure.
 */
extern VDM_Error VDM_Client_PL_Storage_closeDir(VDM_Handle_t *inHandle);

/**
 * Returns URL to the given file path.
 *
 * \param	inFilePath		the file path
 * \param	outUrl			the requested URL
 * \param	inUrlSize		The max size of the requested URL, in bytes
 *
 * \return	0 - success, other value on failure.
 */
extern VDM_Error VDM_Client_PL_Storage_createsUrlFromFile(const char *inFilePath,
	char *outUrl, IU32 inUrlSize);

/**
 * Returns file path from a given URL.
 *
 * \param	inUrl		    the URL
 * \param	outFilePath	    the requested file path
 * \param	inUrlSize		The max size of the requested file path, in bytes
 *
 * \return	0 - success, other value on failure.
 */
extern VDM_Error VDM_Client_PL_Storage_filePathFromUrl(const char *inUrl,
	char *outFilePath, IU32 inFilePathSize);


/**
 * Deletes files from a specific directory
 *
 * \param  const char *inFilePath (input): specified the directory from which the files should be deleted
 * \param  IU32 inFilePathSize (input): indicates the length (in bytes) of inPath
 *
 *  \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 */
extern VDM_Error VDM_Client_PL_Storage_deleteFilesInDir(char *inFilePath,	IU32 inFilePathSize);

/**
 * Checks the error indicator for the stream pointed to by inHandle.
 *
 * \param	inHandle		Handle to the open storage item
 *
 * \return	FALSE if no error is set, TRUE otherwise.
 */
extern IBOOL VDM_Client_PL_Storage_checkError(void *inHandle);

/*! @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

