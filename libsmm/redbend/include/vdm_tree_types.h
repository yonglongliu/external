/*
 *******************************************************************************
 *
 * vdm_tree_types.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \internal
 * \file vdm_tree_types.h
 *
 * \brief DM Tree Types
 *******************************************************************************
 */
#ifndef VDM_TREE_TYPES_H_
#define VDM_TREE_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Slash and identifier */
#define VDM_Tree_str_seperator_X "/<x>"
/* Identifier */
#define VDM_Tree_str_X "<x>"

/*
 * Leaf node value formats
 */
typedef enum {
	E_VDM_TREE_FORMAT_bool, // Boolean
	E_VDM_TREE_FORMAT_int,  // Integer
	E_VDM_TREE_FORMAT_chr   // String
} E_VDM_TREE_FORMAT_t;

/*
 * DM Tree node
 */
typedef struct {
	const char *uri;               // URI
	IBOOL isLeaf;               // TRUE: leaf node; FALSE: interior node
	E_VDM_TREE_FORMAT_t format; // Leaf node value format, an E_VDM_TREE_FORMAT_t value
	void *getCb;                // GET callback
	void *replaceCb;            // REPLACE callback
	void *addCb;                // ADD callback
	void *deleteCb;             // DELETE callback
	void *context;              // DM Client context
} VDM_Tree_Node_t;

/*
 *******************************************************************************
 * Add a node to a URI which does not contain any identifier (<X>).
 *
 * inContext		The context passed on registration
 * inNodeName		Node name
 *
 * Returns VDM_ERR_OK on success, or a VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Tree_addCb) (void *inContext,
	const char *inNodeName);

/*
 *******************************************************************************
 * Delete a node from a URI which does not contain any identifier (<X>).
 *
 * inContext		The context passed on registration
 *
 * Returns VDM_ERR_OK on success, or a VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Tree_deleteCb) (void *inContext);

/*
 *******************************************************************************
 * Get an integer format leaf node value from a URI which does not contain any
 * identifier (<X>).
 *
 * inContext	The context passed on registration
 * outData		The leaf node value
 *
 * Returns VDM_ERR_OK on success, or a VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Tree_IntData_getCb) (void *inContext,
	IU32 *outData);

/*
 *******************************************************************************
 * Replace an integer format leaf node value from a URI which does not contain
 * any identifier (<X>).
 *
 * inContext	The context passed on registration
 * inData		The leaf node value
 *
 * Returns VDM_ERR_OK on success, or a VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Tree_IntData_replaceCb) (void *inContext,
	IU32 inData);

/*
 *******************************************************************************
 * Get a char (buffer) format leaf node value from a URI which does not contain
 * any identifier (<X>).
 *
 * inContext	The context passed on registration
 * inBuffer		The data buffer
 * inBufSize	inBuffer size
 * inOffset		How many bytes were already read
 * outDataLen	inBuffer length
 *
 * Returns VDM_ERR_OK on success, or a VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Tree_BufferData_getCb) (void *inContext,
	void *inBuffer,
	IU32 inBufSize,
	IU32 inOffset,
	IU32 *outDataLen);

/*
 *******************************************************************************
 * Replace a char (buffer) format leaf node value from a URI which does not
 * contain any identifier (<X>).
 *
 * inContext	The context passed on registration
 * inData		The data buffer
 * inDataLen	inData size
 * inOffset		How many bytes were already written
 * inTotalSize	Data total size<br>
 *				If inOffset + inDataLen == inTotalSize then
 *				this is the last call to this API.
 *
 * Returns	VDM_ERR_OK on success, a VDM_ERR_defs error code, or
 *			VDM_ERR_EXT_NOT_PARTIAL if incremental storage is needed
 *			(inOffset != 0) but not supported
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Tree_BufferData_replaceCb) (void *inContext,
	const void *inData,
	IU32 inDataLen,
	IU32 inOffset,
	IU32 inTotalSize);

/*
 *******************************************************************************
 * Add a node to a URI which contains one identifier (<X>).
 *
 * inContext	The context passed on registration
 * inId1		The first <X> value in the URI
 * inNodeName	Node name
 *
 * Returns VDM_ERR_OK on success, or a VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Tree_OneX_addCb) (void *inContext,
	const char *inId1,
	const char *inNodeName);

/*
 *******************************************************************************
 * Delete a node from a URI which contains one identifier (<X>).
 *
 * inContext	The context passed on registration
 * inId1		The first <X> value in the URI
 *
 * Returns VDM_ERR_OK on success, or a VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Tree_OneX_deleteCb) (void *inContext,
	const char *inId1);

/*
 *******************************************************************************
 * Get an integer format leaf node value from a URI which contains one
 * identifier (<X>).
 *
 * inContext	The context passed on registration
 * inId1		The first <X> value in the URI
 * outData		The leaf node value
 *
 * Returns VDM_ERR_OK on success, or a VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Tree_OneXIntData_getCb) (void *inContext,
	const char *inId1,
	IU32 *outData);

/*
 *******************************************************************************
 * Replace an integer format leaf node value from a URI which contains one
 * identifier (<X>).
 *
 * inContext	The context passed on registration
 * inId1		The first <X> value in the URI
 * inData		The leaf node value
 *
 * Returns VDM_ERR_OK on success, or a VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Tree_OneXIntData_replaceCb) (void *inContext,
	const char *inId1,
	IU32 inData);

/*
 *******************************************************************************
 * Get a char (buffer) format leaf node value from a URI which contains one
 * identifier (<X>).
 *
 * inContext	The context passed on registration
 * inId1		The first <X> value in the URI
 * inBuffer		The data buffer
 * inBufSize	inBuffer size
 * inOffset		How many bytes were already read
 * outDataLen	inBuffer length
 *
 * Returns VDM_ERR_OK on success, or a VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Tree_OneXBufferData_getCb) (void *inContext,
	const char *inId1,
	void *inBuffer,
	IU32 inBufSize,
	IU32 inOffset,
	IU32 *outDataLen);

/*
 *******************************************************************************
 * Replace a char (buffer) format leaf node value from a URI which contains one
 * identifier (<X>).
 *
 * inContext	The context passed on registration
 * inId1		The first <X> value in the URI
 * inData		The data buffer
 * inDataLen	inData size
 * inOffset		How many bytes were already written
 * inTotalSize	Data total size<br>
 *				If inOffset + inDataLen == inTotalSize then
 *				this is the last call to this API.
 *
 * Returns	VDM_ERR_OK on success, a VDM_ERR_defs error code, or
 *			VDM_ERR_EXT_NOT_PARTIAL if incremental storage is needed
 *			(inOffset != 0) but not supported
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Tree_OneXBufferData_replaceCb) (void *inContext,
	const char *inId1,
	const void *inData,
	IU32 inDataLen,
	IU32 inOffset,
	IU32 inTotalSize);

/*
 *******************************************************************************
 * Add a node to a URI which contains two identifiers (<X>).
 *
 * inContext	The context passed on registration
 * inId1		The first <X> value in the URI
 * inId2		The second <X> value in the URI
 * inNodeName	Node name
 *
 * Returns VDM_ERR_OK on success, or a VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Tree_TwoX_addCb) (void *inContext,
	const char *inId1,
	const char *inId2,
	const char *inNodeName);

/*
 *******************************************************************************
 * Delete a node from a URI which contains two identifiers (<X>).
 *
 * inContext	The context passed on registration
 * inId1		The first <X> value in the URI
 * inId2		The second <X> value in the URI
 *
 * Returns VDM_ERR_OK on success, or a VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Tree_TwoX_deleteCb) (void *inContext,
	const char *inId1,
	const char *inId2);

/*
 *******************************************************************************
 * Get an integer format leaf node value from a URI which contains two
 * identifiers (<X>).
 *
 * inContext	The context passed on registration
 * inId1		The first <X> value in the URI
 * inId2		The second <X> value in the URI
 * outData		The leaf node value
 *
 * Returns VDM_ERR_OK on success, or a VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Tree_TwoXIntData_getCb) (void *inContext,
	const char *inId1,
	const char *inId2,
	IU32 *outData);

/*
 *******************************************************************************
 * Replace an integer format leaf node value from a URI which contains two
 * identifiers (<X>).
 *
 * inContext	The context passed on registration
 * inId1		The first <X> value in the URI
 * inId2		The second <X> value in the URI
 * inData		The leaf node value
 *
 * Returns VDM_ERR_OK on success, or a VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Tree_TwoXIntData_replaceCb) (void *inContext,
	const char *inId1,
	const char *inId2,
	IU32 inData);

/*
 *******************************************************************************
 * Get a char (buffer) format leaf node value from a URI which contains two
 * identifiers (<X>).
 *
 * inContext	The context passed on registration
 * inId1		The first <X> value in the URI
 * inId2		The second <X> value in the URI
 * inBuffer		The data buffer
 * inBufSize	inBuffer size
 * inOffset		How many bytes were already read
 * outDataLen	inBuffer length
 *
 * Returns VDM_ERR_OK on success, or a VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Tree_TwoXBufferData_getCb) (void *inContext,
	const char *inId1,
	const char *inId2,
	void *inBuffer,
	IU32 inBufSize,
	IU32 inOffset,
	IU32 *outDataLen);

/*
 *******************************************************************************
 * Replace a char (buffer) format leaf node value from a URI which contains two
 * identifiers (<X>).
 *
 * inContext	The context passed on registration
 * inId1		The first <X> value in the URI
 * inId2		The second <X> value in the URI
 * inData		The data buffer
 * inDataLen	inData size
 * inOffset		How many bytes were already written
 * inTotalSize	Data total size<br>
 *				If inOffset + inDataLen == inTotalSize then
 *				this is the last call to this API.
 *
 * Returns	VDM_ERR_OK on success, a VDM_ERR_defs error code, or
 *			VDM_ERR_EXT_NOT_PARTIAL if incremental storage is needed
 *			(inOffset != 0) but not supported
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Tree_TwoXBufferData_replaceCb) (void *inContext,
	const char *inId1,
	const char *inId2,
	const void *inData,
	IU32 inDataLen,
	IU32 inOffset,
	IU32 inTotalSize);

/*
 *******************************************************************************
 * Add a node to a URI which contains three identifiers (<X>).
 *
 * inContext	The context passed on registration
 * inId1		The first <X> value in the URI
 * inId2		The second <X> value in the URI
 * inId3		The third <X> value in the URI
 * inNodeName	Node name
 *
 * Returns VDM_ERR_OK on success, or a VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Tree_ThreeX_addCb) (void *inContext,
	const char *inId1,
	const char *inId2,
	const char *inId3,
	const char *inNodeName);

/*
 *******************************************************************************
 * Delete a node from a URI which contains three identifiers (<X>).
 *
 * inContext	The context passed on registration
 * inId1		The first <X> value in the URI
 * inId2		The second <X> value in the URI
 * inId3		The third <X> value in the URI
 *
 * Returns VDM_ERR_OK on success, or a VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Tree_ThreeX_deleteCb) (void *inContext,
	const char *inId1,
	const char *inId2,
	const char *inId3);

/*
 *******************************************************************************
 * Get an integer format leaf node value from a URI which contains three
 * identifiers (<X>).
 *
 * inContext	The context passed on registration
 * inId1		The first <X> value in the URI
 * inId2		The second <X> value in the URI
 * inId3		The third <X> value in the URI
 * outData		The leaf node value
 *
 * Returns VDM_ERR_OK on success, or a VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Tree_ThreeXIntData_getCb) (void *inContext,
	const char *inId1,
	const char *inId2,
	const char *inId3,
	IU32 *outData);

/*
 *******************************************************************************
 * Replace an integer format leaf node value from a URI which contains three
 * identifiers (<X>).
 *
 * inContext	The context passed on registration
 * inId1		The first <X> value in the URI
 * inId2		The second <X> value in the URI
 * inId3		The third <X> value in the URI
 * inData		The leaf node value
 *
 * Returns VDM_ERR_OK on success, or a VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Tree_ThreeXIntData_replaceCb) (void *inContext,
	const char *inId1,
	const char *inId2,
	const char *inId3,
	IU32 inData);

/*
 *******************************************************************************
 * Replace a char (buffer) format leaf node value from a URI which contains two
 * identifiers (<X>).
 *
 * inContext	The context passed on registration
 * inId1		The first <X> value in the URI
 * inId2		The second <X> value in the URI
 * inId3		The third <X> value in the URI
 * inData		The data buffer
 * inDataLen	inData size
 * inOffset		How many bytes were already written
 * inTotalSize	Data total size<br>
 *				If inOffset + inDataLen == inTotalSize then
 *				this is the last call to this API.
 *
 * Returns	VDM_ERR_OK on success, a VDM_ERR_defs error code, or
 *			VDM_ERR_EXT_NOT_PARTIAL if incremental storage is needed
 *			(inOffset != 0) but not supported
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Tree_ThreeXBufferData_getCb) (void *inContext,
	const char *inId1,
	const char *inId2,
	const char *inId3,
	void *inBuffer,
	IU32 inBufSize,
	IU32 inOffset,
	IU32 *outDataLen);

/*
 *******************************************************************************
 * Replace a char (buffer) format leaf node value from a URI which contains
 * three identifiers (<X>).
 *
 * inContext	The context passed on registration
 * inId1		The first <X> value in the URI
 * inId2		The second <X> value in the URI
 * inId3		The second <X> value in the URI
 * inData		The data buffer
 * inDataLen	inData size
 * inOffset		How many bytes were already written
 * inTotalSize	Data total size<br>
 *				If inOffset + inDataLen == inTotalSize then
 *				this is the last call to this API.
 *
 * Returns	VDM_ERR_OK on success, a VDM_ERR_defs error code, or
 *			VDM_ERR_EXT_NOT_PARTIAL if incremental storage is needed
 *			(inOffset != 0) but not supported
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Tree_ThreeXBufferData_replaceCb) (void *inContext,
	const char *inId1,
	const char *inId2,
	const char *inId3,
	const void *inData,
	IU32 inDataLen,
	IU32 inOffset,
	IU32 inTotalSize);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

