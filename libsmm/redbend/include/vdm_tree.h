/*
 *******************************************************************************
 *
 * vdm_tree.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_tree.h
 *
 * \brief	DM Tree API
 *******************************************************************************
 */
#ifndef _E_VDM_TREE_H_
#define _E_VDM_TREE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define VDM_CONST_binFormat     "bin"
#define VDM_CONST_chrFormat     "chr"
#define VDM_CONST_intFormat     "int"
#define VDM_CONST_boolFormat    "bool"

/*!
 * Tree DF properties flags. These can be passed to \ref VDM_Tree_AddFunc
 * or to \ref VDM_Tree_addChildLeafNodeEx for setting the DF properties for the
 * newly created node.
 */
typedef enum {
	E_VDM_Tree_DFProperties_accesstypeAdd = 0x01,       //!< Add access type
	E_VDM_Tree_DFProperties_accesstypeCopy = 0x02,      //!< Copy access type
	E_VDM_Tree_DFProperties_accesstypeDelete = 0x04,    //!< Delete access type
	E_VDM_Tree_DFProperties_accesstypeExec = 0x08,      //!< Exec access type
	E_VDM_Tree_DFProperties_accesstypeGet = 0x10,       //!< Get access type
	E_VDM_Tree_DFProperties_accesstypeReplace = 0x20,   //!< Replace access type
	E_VDM_Tree_DFProperties_defaultBehavior = 0x7f      //!< Default access type
} E_VDM_Tree_DFProperties_t;

/*!
 * The source that caused the tree operation. This type is used by
 * \ref VDM_Tree_ReplaceNotifyCB.
 */
typedef enum {
	E_VDM_Tree_OperationOriginator_undefined = 0x0  //!< Undefined operation source
} E_VDM_Tree_OperationOriginator_t;

/*!
 * The phase of the Add operation. This type is used by \ref VDM_Tree_AddFunc.
 */
typedef enum {
	E_VDM_Tree_AddNotifyCB_operationPhase_singleNode //!< Adding a single node
} E_VDM_Tree_AddNotifyCB_operationPhase_t;

/*!
 *******************************************************************************
 * Callback invoked before executing a command. Use this to confirm whether the
 * command should proceed.
 *
 * Returning 0 indicates to proceed with the Execute command. For any other
 * return value, if the return value is a valid status code it is returned as
 * the result of the command; otherwise, 500 (command failed) is returned.
 *
 * \param	inURI		The full pathname of the node.
 * \param	inContext	Context supplied when this callback was registered.
 * \param	outMsg		Optional. A string that will be sent to the server
 *                      in addition to the result. Should be allocated in
 *                      the observer function and will be freed by the engine.
 *
 * \return	A number in the range of [0..0x0fff]:
 *          0 to continue with the command, any other number to prevent from
 *          executing the command and notify the server that the command has
 *          failed
 *******************************************************************************
 */
typedef IU16 (*VDM_Tree_PreCmdNotify_t)(const char *inURI, void *inContext, char **outMsg);

/*!
 * DEPRECATED. Use VDM_Tree_getStringValueAcl instead.
 */
extern VDM_Error VDM_Tree_getStringValue(
	const char *inURI,
	char *outBuffer,
	IU32 *ioLength);

/*!
 *******************************************************************************
 * Get the value of a leaf node of string format ("chr"), or the value of
 * an interior node. The value of an interior is a string of all its children
 * separated by '/'.
 *
 * If the supplied string buffer is too short then as much data as will fit
 * in the buffer is returned along with the error code VDM_ERR_BUFFER_OVERFLOW.
 * The total length of the string is always returned.
 *
 * \param	isAcl		Should this call verify ACL pemissions.
 * \param	inServer	Server id for ACL verivication. Used only if isAcl is true.
 * \param	inURI		The full pathname of the node. The URI of a node is
 *						a string of all of its parents, and the node name,
 *						separated by '/'.
 * \param	outBuffer	Pre-allocated result buffer for the string value.
 * \param	ioLength	Input: Size of \a outBuffer.
 *						Output: Length of data in \a outBuffer.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			VDM_ERR_NODE_MISSING if the node could not be found,
 *			VDM_ERR_BUFFER_OVERFLOW if the supplied buffer is too small,
 *			or VDM_ERR_NODE_VALUE_NOT_READABLE if the node is registered for
 *			external storage (using \ref VDM_Tree_registerExternalStorage) and
 *			inReadFunc is NULL
 *******************************************************************************
 */
extern VDM_Error VDM_Tree_getStringValueAcl(int isAcl, char *inServer, const char *inURI,
	char *outBuffer, IU32 *ioLength);

/*!
 *******************************************************************************
 * Allocate and get the value of a leaf node of string format ("chr"), or the
 * value of an interior node. The value of an interior is a string of all its
 * children separated by '/'.
 *
 * Note: If the node doesn't contain a value, then NULL will be returned.
 *
 * \param	inURI		The full pathname of the node. The URI of a node is
 *						a string of all of its parents, and the node name,
 *						separated by '/'.
 * \param	outResult	VDM_ERR_OK on success,
 *						VDM_ERR_BAD_INPUT,
 *						VDM_ERR_MEMORY if the system is out of memory,
 *						VDM_ERR_NODE_MISSING if the node could not be found,
 *						VDM_ERR_NOT_LEAF_NODE if the node is not a leaf node,
 *						VDM_ERR_BUFFER_OVERFLOW if the supplied buffer is too
 *						small, or VDM_ERR_NODE_VALUE_NOT_READABLE if the node
 *						is registered for external storage (using \ref
 *						VDM_Tree_registerExternalStorage) and inReadFunc is NULL
 *
 * \return	Pointer to allocated buffer for the string on success, or NULL on
 *			failure; the memory for the new string is obtained using
 *			\ref VDM_PL_malloc, and can be freed using \ref VDM_PL_free or
 *			\ref VDM_PL_freeAndNullify
 *******************************************************************************
 */
extern char *VDM_Tree_getStringValueDup(const char *inURI, VDM_Error *outResult);

/*!
 *******************************************************************************
 * Get the checksum of a subtree.
 *
 * The checksum is calculated by applying the MD5 algorithm on the names and
 * values of the nodes contained in the subtree. Other tree properties are
 * omitted from the calculation, and do not affect the checksum result.
 * The order of sibling nodes is ignored and does not affect the checksum
 * result.
 *
 * Note: the checksum result is a 16 bytes buffer.
 *
 * \param	inURI		The full pathname of the root of the sub-tree. The
 *						URI of a node is a string of all of its parents, and
 *						the node name, separated by '/'. The node may be an
 *						interior node or a leaf node.
 * \param	outBuffer	Pre-allocated result buffer for the checksum value.
 * \param	ioLength	Input: Size of \a outBuffer.
 *						Output: Length of data in \a outBuffer.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			VDM_ERR_NODE_MISSING if the node could not be found,
 *			VDM_ERR_BUFFER_OVERFLOW if the supplied buffer is too small,
 *			or VDM_ERR_NODE_VALUE_NOT_READABLE if the node is registered for
 *			external storage (using \ref VDM_Tree_registerExternalStorage) and
 *			inReadFunc is NULL
 *******************************************************************************
 */
extern VDM_Error VDM_Tree_getSubtreeChecksum(const char *inURI, IU8 *outBuffer,
	IU32 *ioLength);

/*!
 * DEPRECATED. Use VDM_Tree_replaceStringValueAcl instead.
 */
extern VDM_Error VDM_Tree_replaceStringValue(const char *inURI, const char *inValue);

/*!
 *******************************************************************************
 * Replace the value of a leaf node of string format ("chr").
 *
 * \param	isAcl		Should this call verify ACL pemissions.
 * \param	inServer	Server id for ACL verivication. Used only if isAcl is true.
 * \param	inURI		The full pathname of the node. The URI of a node is
 *						a string of all of its parents, and the node name,
 *						separated by '/'.
 * \param	inValue		String value.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			VDM_ERR_NODE_MISSING if the node could not be found,
 *			VDM_ERR_NOT_LEAF_NODE if the node is not a leaf node,
 *			VDM_ERR_PERMANENT_NODE if the node is a permanent node,
 *			VDM_ERR_BUFFER_OVERFLOW if the supplied buffer is too small,
 *			or VDM_ERR_NODE_VALUE_NOT_WRITEABLE if the node is registered for
 *			external storage (using \ref VDM_Tree_registerExternalStorage) and
 *			inWriteFunc is NULL
 *******************************************************************************
 */
extern VDM_Error VDM_Tree_replaceStringValueAcl(int isAcl, char *inServer,
	const char *inURI, const char *inValue);

/*!
 *******************************************************************************
 * Get the value of a leaf node of integer format ("int").
 *
 * \param	inURI		The full pathname of the node. The URI of a node is
 *						a string of all of its parents, and the node name,
 *						separated by '/'.
 * \param	outValue	Integer value.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			VDM_ERR_NODE_MISSING if the node could not be found,
 *			or VDM_ERR_NODE_VALUE_NOT_READABLE if the node is registered for
 *			external storage (using \ref VDM_Tree_registerExternalStorage) and
 *			inReadFunc is NULL
 *******************************************************************************
 */
extern VDM_Error VDM_Tree_getIntValue(
	const char *inURI,
	IS32 *outValue);

/*!
 * DEPRECATED. Use VDM_Tree_replaceIntValueAcl instead.
 */
extern VDM_Error VDM_Tree_replaceIntValue(const char *inURI, IS32 inValue);

/*!
 *******************************************************************************
 * Replace the value of a leaf node of integer format ("int").
 *
 * \param	isAcl		Should this call verify ACL pemissions.
 * \param	inServer	Server id for ACL verivication. Used only if isAcl is true.
 * \param	inURI		The full pathname of the node. The URI of a node is
 *						a string of all of its parents, and the node name,
 *						separated by '/'.
 * \param	inValue		Integer value.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			VDM_ERR_NODE_MISSING if the node could not be found,
 *			VDM_ERR_NOT_LEAF_NODE if the node is not a leaf node,
 *			VDM_ERR_PERMANENT_NODE if the node is a permanent node,
 *			or VDM_ERR_NODE_VALUE_NOT_READABLE if the node is registered for
 *			external storage (using \ref VDM_Tree_registerExternalStorage) and
 *			inReadFunc is NULL
 *******************************************************************************
 */
extern VDM_Error VDM_Tree_replaceIntValueAcl(int isAcl, char *inServer,
	const char *inURI, IS32 inValue);

/*!
 * DEPRECATED. Use VDM_Tree_getUintValueAcl instead.
 */
extern VDM_Error VDM_Tree_getUintValue(const char *inURI, IU32 *outValue);

/*!
 *******************************************************************************
 * Get the value of a leaf node of integer format ("int") as an unsigned int.
 *
 * \param	isAcl		Should this call verify ACL pemissions.
 * \param	inServer	Server id for ACL verivication. Used only if isAcl is true.
 * \param	inURI		The full pathname of the node. The URI of a node is
 *						a string of all of its parents, and the node name,
 *						separated by '/'.
 * \param	outValue	Unsigned integer value.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			VDM_ERR_NODE_MISSING if the node could not be found,
 *			or VDM_ERR_NODE_VALUE_NOT_READABLE if the node is registered for
 *			external storage (using \ref VDM_Tree_registerExternalStorage) and
 *			inReadFunc is NULL
 *******************************************************************************
 */
extern VDM_Error VDM_Tree_getUintValueAcl(int isAcl, char *inServer, const char *inURI,
	IU32 *outValue);

/*!
 * DEPRECATED. Use VDM_Tree_replaceUintValueAcl instead.
 */
extern VDM_Error VDM_Tree_replaceUintValue(const char *inURI, IU32 inValue);

/*!
 *******************************************************************************
 * Replace the value of a leaf node of integer format ("int") with an unsigned
 * int.
 *
 * \param	isAcl		Should this call verify ACL pemissions.
 * \param	inServer	Server id for ACL verivication. Used only if isAcl is true.
 * \param	inURI		The full pathname of the node. The URI of a node is
 *						a string of all of its parents, and the node name,
 *						separated by '/'.
 * \param	inValue		Unsigned integer value.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			VDM_ERR_NODE_MISSING if the node could not be found,
 *			VDM_ERR_NOT_LEAF_NODE if the node is not a leaf node,
 *			VDM_ERR_PERMANENT_NODE if the node is a permanent node,
 *			or VDM_ERR_NODE_VALUE_NOT_READABLE if the node is registered for
 *			external storage (using \ref VDM_Tree_registerExternalStorage) and
 *			inReadFunc is NULL
 *******************************************************************************
 */
extern VDM_Error VDM_Tree_replaceUintValueAcl(int isAcl, char *inServer, const char *inURI,
	IU32 inValue);

/*!
 *******************************************************************************
 * Get the value of a leaf node of boolean format ("bool").
 *
 * \param	inURI		The full pathname of the node. The URI of a node is
 *						a string of all of its parents, and the node name,
 *						separated by '/'.
 * \param	outValue	Boolean value.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			VDM_ERR_NODE_MISSING if the node could not be found,
 *			VDM_ERR_LEAF_NODE if the leaf node value is not TRUE or FALSE (case
 *			insensitive),
 *			or VDM_ERR_NODE_VALUE_NOT_READABLE if the node is registered for
 *			external storage (using \ref VDM_Tree_registerExternalStorage) and
 *			inReadFunc is NULL
 *******************************************************************************
 */
extern VDM_Error VDM_Tree_getBoolValue(
	const char *inURI,
	IBOOL *outValue);

/*!
 * DEPRECATED. Use VDM_Tree_replaceBoolValueAcl instead.
 */
extern VDM_Error VDM_Tree_replaceBoolValue(const char *inURI, IBOOL inValue);

/*!
 *******************************************************************************
 * Replace the value of a leaf node of boolean format ("bool").
 *
 * \param	isAcl		Should this call verify ACL pemissions.
 * \param	inServer	Server id for ACL verivication. Used only if isAcl is true.
 * \param	inURI		The full pathname of the node. The URI of a node is
 *						a string of all of its parents, and the node name,
 *						separated by '/'.
 * \param	inValue		Boolean value.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			VDM_ERR_NODE_MISSING if the node could not be found,
 *			VDM_ERR_NOT_LEAF_NODE if the node is not a leaf node,
 *			VDM_ERR_PERMANENT_NODE if the node is a permanent node,
 *			or VDM_ERR_NODE_VALUE_NOT_READABLE if the node is registered for
 *			external storage (using \ref VDM_Tree_registerExternalStorage) and
 *			inReadFunc is NULL
 *******************************************************************************
 */
extern VDM_Error VDM_Tree_replaceBoolValueAcl(int isAcl, char *inServer,
	const char *inURI, IBOOL inValue);

/*!
 *******************************************************************************
 * Get the value of a leaf node of binary format ("bin").
 *
 * If the supplied string buffer is too short then as much data as will fit
 * in the buffer is returned along with the error code VDM_ERR_BUFFER_OVERFLOW.
 * The total length of the string is always returned.
 *
 * \param	inURI		The full pathname of the node. The URI of a node is
 *						a string of all of its parents, and the node name,
 *						separated by '/'.
 * \param	outBuffer	Pre-allocated result buffer for the binary value.
 * \param	ioLength	Input: Size of \a outBuffer.
 *						Output: Length of data in \a outBuffer.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			VDM_ERR_NODE_MISSING if the node could not be found,
 *			VDM_ERR_BUFFER_OVERFLOW if the supplied buffer is too small,
 *			or VDM_ERR_NODE_VALUE_NOT_READABLE if the node is registered for
 *			external storage (using \ref VDM_Tree_registerExternalStorage) and
 *			inReadFunc is NULL
 *******************************************************************************
 */
extern VDM_Error VDM_Tree_getBinValue(
	const char *inURI,
	void *outBuffer,
	IU32 *ioLength);

/*!
 * DEPRECATED. Use VDM_Tree_replaceBinValueAcl instead.
 */
extern VDM_Error VDM_Tree_replaceBinValue(const char *inURI, void *inValue, IU32 inLength);

/*!
 *******************************************************************************
 * Replace the value of a leaf node of binary format ("bin").
 *
 * \param	isAcl		Should this call verify ACL pemissions.
 * \param	inServer	Server id for ACL verivication. Used only if isAcl is true.
 * \param	inURI		The full pathname of the node. The URI of a node is
 *						a string of all of its parents, and the node name,
 *						separated by '/'.
 * \param	inValue		Binary value.
 * \param	inLength	Length of \a inValue.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			VDM_ERR_NODE_MISSING if the node could not be found,
 *			VDM_ERR_NOT_LEAF_NODE if the node is not a leaf node,
 *			VDM_ERR_PERMANENT_NODE if the node is a permanent node,
 *			or VDM_ERR_NODE_VALUE_NOT_READABLE if the node is registered for
 *			external storage (using \ref VDM_Tree_registerExternalStorage) and
 *			inReadFunc is NULL
 *******************************************************************************
 */
extern VDM_Error VDM_Tree_replaceBinValueAcl(int isAcl, char *inServer, const char *inURI,
	void *inValue, IU32 inLength);

/*!
 *******************************************************************************
 * Add a leaf node to the DM Tree, given the path to the node to add.
 *
 * \see VDM_Tree_addChildLeafNode
 *
 * \param	inNodeURI	The full pathname of the node to add. The path of
 *						a node is a string of all of its parents, and the node
 *						name, separated by '/'.
 * \param	inFormat	Node data format ("chr", "int", and so on). The default
 *						is "chr".
 * \param	inType		Node MIME type (may be NULL).
 * \param	inData		Buffer containing node's initial value.
 * \param	inSize		Size of initial value, in bytes (may be 0).
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			VDM_ERR_NODE_ALREADY_EXISTS if the node already exists,
 *			or another \ref VDM_ERR_defs error code
 *******************************************************************************
 */

VDM_Error VDM_Tree_addLeafNode(
	const char *inNodeURI,
	const char *inFormat,
	const char *inType,
	void *inData,
	IU32 inSize);

/*!
 *******************************************************************************
 * Add a leaf node to the DM Tree, given the path to the node to add.
 *
 * \see VDM_Tree_addChildLeafNodeEx
 *
 * \param	inNodeURI		The full pathname of the node to add. The path of
 *							a node is a string of all of its parents, and the node
 *							name, separated by '/'.
 * \param	inFormat		Node data format ("chr", "int", and so on). The default
 *							is "chr".
 * \param	inType			Node MIME type (may be NULL).
 * \param	inData			Buffer containing node's initial value.
 * \param	inSize			Size of initial value, in bytes (may be 0).
 *
 * \param	inAccessType	The access type flags for the newly created node,
 *							which are \ref E_VDM_Tree_DFProperties_t values. To
 *							maintain the default behavior, use \ref
 *							E_VDM_Tree_DFProperties_t#E_VDM_Tree_DFProperties_defaultBehavior.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			VDM_ERR_NODE_ALREADY_EXISTS if the node already exists,
 *			or another \ref VDM_ERR_defs error code
 *******************************************************************************
 */

VDM_Error VDM_Tree_addLeafNodeEx(
	const char *inNodeURI,
	const char *inFormat,
	const char *inType,
	const void *inData,
	IU32 inSize,
	IS8 inAccessType);

/*!
 *******************************************************************************
 * Add a leaf node to the DM Tree, given the path to the parent of the node
 * to add.
 *
 * \see VDM_Tree_addLeafNode
 *
 * \param	inParentPath	The full pathname of the parent node of the node to
 *							add. The path of a node is a string of all of its
 *							parents, and the node name,	separated by '/'.
 * \param	inNodeName		Name of the node to add (required, may not be NULL).
 * \param	inFormat		Node data format ("chr", "int", and so on). The
 *							default is "chr".
 * \param	inType			Node MIME type (may be NULL).
 * \param	inData			Buffer containing node's initial value.
 * \param	inSize			Size of initial value, in bytes (may be 0).
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			VDM_ERR_NODE_ALREADY_EXISTS if the node already exists,
 *			or another \ref VDM_ERR_defs error code
 *******************************************************************************
 */
VDM_Error VDM_Tree_addChildLeafNode(
	const char *inParentPath,
	const char *inNodeName,
	const char *inFormat,
	const char *inType,
	const void *inData,
	IU32 inSize);

/*!
 *******************************************************************************
 * Add a leaf node to the DM Tree, given the path to the parent of the node
 * to add.
 *
 * \see VDM_Tree_addLeafNodeEx
 *
 * \param	inParentPath	The full pathname of the parent node of the node to
 *							add. The path of a node is a string of all of its
 *							parents, and the node name,	separated by '/'.
 * \param	inNodeName		Name of the node to add (required, may not be NULL).
 * \param	inFormat		Node data format ("chr", "int", and so on). The
 *							default is "chr".
 * \param	inType			Node MIME type (may be NULL).
 * \param	inData			Buffer containing node's initial value.
 * \param	inSize			Size of initial value, in bytes (may be 0).
 * \param	inAccessType	The access type flags for the newly created node,
 *							which are \ref E_VDM_Tree_DFProperties_t values. To
 *							maintain the default behavior, use \ref
 *							E_VDM_Tree_DFProperties_t#E_VDM_Tree_DFProperties_defaultBehavior.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			VDM_ERR_NODE_ALREADY_EXISTS if the node already exists,
 *			or another \ref VDM_ERR_defs error code
 *******************************************************************************
 */
VDM_Error VDM_Tree_addChildLeafNodeEx(
	const char *inParentPath,
	const char *inNodeName,
	const char *inFormat,
	const char *inType,
	const void *inData,
	IU32 inSize,
	IS8 inAccessType);

/*!
 *******************************************************************************
 * Add an interior node to the DM Tree, given the path to the node to add.
 *
 * \see VDM_Tree_addInteriorChildNode
 *
 * \param	inNodePath	The full pathname of the node to add. The path of
 *						a node is a string of all of its parents, and the node
 *						name, separated by '/'.
 * \param	inType		A name representing the Device Description Framework
 *						document (DDF) describing the collection of nodes
 *						rooted at this node, or NULL.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			VDM_ERR_NODE_ALREADY_EXISTS if the node already exists,
 *			or another \ref VDM_ERR_defs error code
 *******************************************************************************
 */
VDM_Error VDM_Tree_addInteriorNode(
	const char *inNodePath,
	const char *inType);

/*!
 *******************************************************************************
 * Add an interior node to the DM Tree, given the path to the node to add.
 *
 * \see VDM_Tree_addInteriorChildNode
 *
 * \param	inNodePath	The full pathname of the node to add. The path of
 *						a node is a string of all of its parents, and the node
 *						name, separated by '/'.
 * \param	inType		A name representing the Device Description Framework
 *						document (DDF) describing the collection of nodes
 *						rooted at this node, or NULL.
 * \param	inACL		The new ACL.
 * \param	inAccessType	The access type flags for the newly created node,
 *							which are \ref E_VDM_Tree_DFProperties_t values. To
 *							maintain the default behavior, use \ref
 *							E_VDM_Tree_DFProperties_t#E_VDM_Tree_DFProperties_defaultBehavior.
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			VDM_ERR_NODE_ALREADY_EXISTS if the node already exists,
 *			or another \ref VDM_ERR_defs error code
 *******************************************************************************
 */
VDM_Error VDM_Tree_addInteriorNodeEx(const char *inNodePath, const char *inType,
	const char *inAcl, IS8 inAccessType);

/*!
 *******************************************************************************
 * Add an interior node to the DM Tree, given the path to the parent of the node
 * to add.
 *
 * \see VDM_Tree_addInteriorNode
 *
 * \param	inParentPath	The full pathname of the parent node of the node to
 *							add. The path of a node is a string of all of its
 *							parents, and the node name,	separated by '/'.
 * \param	inNodeName		Name of the node to add (required, may not be NULL).
 * \param	inType			A name representing the Device Description Framework
 *							document (DDF) describing the collection of nodes
 *							rooted at this node, or NULL.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			VDM_ERR_NODE_ALREADY_EXISTS if the node already exists,
 *			or another \ref VDM_ERR_defs error code
 *******************************************************************************
 */
VDM_Error VDM_Tree_addInteriorChildNode(
	const char*inParentPath,
	const char *inNodeName,
	const char *inType);

/*!
 *******************************************************************************
 * Delete a node from the DM Tree.
 *
 * \param	inNodePath	The full pathname of the node to delete. The path of
 *						a node is a string of all of its parents, and the node
 *						name, separated by '/'.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT,
 *			VDM_ERR_NODE_MISSING if the node could not be found,
 *			or VDM_ERR_PERMANENT_NODE if the node is a permanent node.
 *******************************************************************************
 */
VDM_Error VDM_Tree_deleteNode(const char *inNodePath);

/*!
 *******************************************************************************
 * Callback invoked to read node value from external storage.
 *
 * \param	inContext	Context supplied when the external access
 *						callback was registered.
 * \param	inOffset	The byte offset from the start of the data to read into buffer.
 * \param	outBuffer	Pre-allocated buffer to store the data.
 *                      If NULL then set the size of data to read in outDataLen and return VDM_ERR_BUFFER_OVERFLOW
 * \param	inBufSize	The size of \a outBuffer, in bytes. if inBufSize is less then the data to read,
 *                      copy what you can and return VDM_ERR_BUFFER_OVERFLOW
 * \param	outDataLen	The total length of the entire data in bytes excluding null terminator.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Tree_ReadExternalCB) (void *inContext, IU32 inOffset,
	void *outBuffer, IU32 inBufSize,
	IU32 *outDataLen);

/*!
 *******************************************************************************
 * Write data to the DM Tree, where the data is actually stored in external
 * storage.
 *
 * Normally, the data is written in a single call to this callback. For large
 * amounts of data, the data can be written using a series of calls. If this
 * partial write mechanism isn't supported, return VDM_ERR_TREE_EXT_NOT_PARTIAL.
 *
 * If the data is not written in a single call, it will always be written in a
 * series of calls with increasing offsets starting with an offset of 0. If
 * \a inOffset + \a inDataLen = \a inTotalSize, then all the data has been
 * sent and the data should now be stored if it has not been stored
 * incrementally.
 *
 * Before attempting partial writes, this callback is called with \a inOffset
 * and \a inDataLen both set to 0 and \a inTotalSize set to the maximum length
 * of the data. This is the only time \a inDataLen of 0 is supplied, unless
 * \a inTotalSize is also 0.
 *
 * \note	In certain circumstances, \a inTotalsize supplied with the last
 *			chunk of data may be a few bytes shorter than that supplied with the
 *			preceding chunks. This is due to the way the SyncML protocol handles
 *			Base64 encoded data.
 *
 * If the write fails part way through while using the partial write mechanism,
 * then OMA DM Protocol Engine will normally try to set the length of the data to 0,
 * but it is possible that the data will simply be left unfinished. If this is
 * a problem, then partial writes should be rejected and
 * VDM_ERR_TREE_EXT_NOT_PARTIAL should be returned.
 *
 * If it is not possible to write the value for some reason (for instance, it is
 * in use by another program) then the error VDM_ERR_TREE_EXT_NOT_ALLOWED should
 * be returned.
 *
 * \param	inContext	Context supplied when the external access
 *						callback was registered.
 * \param	inOffset	The byte offset from the start of the data.
 * \param	inData		A pointer to the data.
 * \param	inDataLen	The length of the supplied chunk of data, in bytes.
 *						When using partial writes, this may be less than
 *						\a inTotalSize
 * \param	inTotalSize	The total size of the data.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_TREE_EXT_NOT_ALLOWED if writing failed,
 *			VDM_ERR_TREE_EXT_NOT_PARTIAL if partial writing is not supported,
 *			or another \ref VDM_ERR_defs error code
 ********************************************************************************
 */
typedef VDM_Error (*VDM_Tree_WriteExternalCB) (void *inContext, IU32 inOffset,
	const void *inData, IU32 inDataLen, IU32 inTotalSize);
/*!
 *******************************************************************************
 * Register external access callbacks for a node. The node must exist and must
 * be a leaf node.
 *
 * \note	To unregister external access callbacks for a node, call
 *			this API with \a inReadFunc, \a inWriteFunc, and \a inContext
 *			all set to NULL.
 *
 * \param	inURI			The full pathname of the node. The URI of a node is
 *							a string of all of its parents, and the node name,
 *							separated by '/'.
 * \param	inReadFunc		The callback for reading data. If NULL, then
 *							the value is write only and VDM_Tree_get* API
 *							will return VDM_ERR_NODE_VALUE_NOT_READABLE.
 * \param	inWriteFunc		The callback for writing data. If NULL, then
 *							the value is read only and VDM_Tree_get* API
 *							will return VDM_ERR_NODE_VALUE_NOT_WRITEABLE.
 * \param	inContext		Context passed to the \a inReadFunc and
 *							\a inWriteFunc.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT,
 *			VDM_ERR_NODE_MISSING if the node could not be found,
 *			or VDM_ERR_NOT_LEAF_NODE if the node is not a leaf node
 *******************************************************************************
 */
extern VDM_Error VDM_Tree_registerExternalStorage(
	const char *inURI,
	VDM_Tree_ReadExternalCB inReadFunc,
	VDM_Tree_WriteExternalCB inWriteFunc,
	void *inContext);

/*!
 *******************************************************************************
 * Register external access callbacks for all leaf nodes in a sub-tree.
 *
 * \note	To unregister external access callbacks for a sub-tree, call
 *			this API with \a inReadFunc, \a inWriteFunc, and \a inContext
 *			all set to NULL.
 *
 * \param	inURI			The full pathname of the root of the sub-tree. The
 *							URI of a node is a string of all of its parents, and
 *							the node name, separated by '/'. The node may be an
 *							interior node or a leaf node.
 * \param	inReadFunc		The callback for reading data. If NULL, then
 *							the value is write-only.
 * \param	inWriteFunc		The callback for writing data. If NULL, then
 *							the value is read-only.
 * \param	inContext		Context passed to \a inReadFunc and \a inWriteFunc.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			or VDM_ERR_NODE_MISSING if the node could not be found
 *******************************************************************************
 */
VDM_Error VDM_Tree_registerExternalStorageSubtree(
	const char *inURI,
	VDM_Tree_ReadExternalCB inReadFunc,
	VDM_Tree_WriteExternalCB inWriteFunc,
	void *inContext);

/*!
 *******************************************************************************
 * Get the context that was provided when registering external storage
 * callbacks.
 *
 * \param	inURI	The full pathname of the root of the sub-tree. The URI of a
 *					node is a string of all of its parents, and the node name,
 *					separated by '/'. The node may be an interior node or a leaf
 *					node.
 *
 * \return	The context if the node has external storage defined, NULL otherwise
 *******************************************************************************
 */
void *VDM_Tree_getExternalStorageContext(const char *inURI);

/*!
 *******************************************************************************
 * Get the URI for which a registered callback was just called.
 *
 * The callbacks may be any of:
 * \li	\ref VDM_Tree_registerExternalStorage
 * \li	\ref VDM_Tree_registerExternalStorageSubtree
 * \li	\ref VDM_Tree_registerAdd
 * \li	\ref VDM_Tree_registerAddSubtree
 * \li	\ref VDM_Tree_registerDelete
 * \li	\ref VDM_Tree_registerDeleteSubtree
 * \li	\ref VDM_Tree_registerExecute
 * \li	\ref VDM_Tree_registerPreExecNotify
 *
 * For example, if the callback "foo" was the inReadFunc parameter of \ref
 * VDM_Tree_registerExternalStorageSubtree, and the path "./data" was the
 * inURI parameter, then when foo is called the return value of
 * this function is "./data"
 *
 * \return	The URI, or NULL if out of memory; the memory for this value is
 *          allocated by OMA DM Protocol Engine and should be freed by the caller
 *          using \ref VDM_PL_free or \ref VDM_PL_freeAndNullify
 *******************************************************************************
 */
char *VDM_Tree_getExternalNodeURIDup(void);

/*!
 *******************************************************************************
 * Callback invoked to Exec a node.
 *
 * According to the OMA DM standard, performing an EXEC could be done either
 * synchronously or asynchronously. The two modes are supported by vDM
 * accordingly:
 *
 * In case of asynchronous execution, the function should return VDM_ERR_OK
 * after invoking actual process, and vDM will send 202 ("Accepted for
 * processing") as a result code to the DM server.
 *
 * In case of synchronous execution, the function should return a result value
 * between 0x3000 and 0x3FFF, and vDM will calculate the result code sent to
 * the DM server as the result value minus 0x3000.
 *
 * \param	inContext		Context supplied when the callback was registered.
 * \param	inData			Pointer to the data supplied with the Exec command.
 * \param	inSize			The length of \a inData, in bytes.
 * \param	inCorrelator	The correlator to use in the report sent to the
 *							server.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Tree_ExecuteFunc) (void *inContext, void *inData,
	IU32 inSize, const char *inCorrelator);

/*!
 *******************************************************************************
 * Register an Exec callback for a node. The node must exist.
 *
 * \note	To unregister an Exec callback for a node, call
 *			this API with \a inFunc and \a inContext set to NULL.
 *
 * \param	inURI		The full pathname of the node. The URI of a node is
 *						a string of all of its parents, and the node name,
 *						separated by '/'.
 * \param	inFunc		The callback to invoke when Exec is called on the node.
 *						See \ref VDM_Tree_ExecuteFunc.
 * \param	inContext	Context passed to \a inFunc.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			or VDM_ERR_NODE_MISSING if the node could not be found
 *******************************************************************************
 */
extern VDM_Error VDM_Tree_registerExecute(
	const char *inURI,
	VDM_Tree_ExecuteFunc inFunc,
	void *inContext);

/*!
 *******************************************************************************
 * Callback invoked when a node is deleted.
 *
 * \param	inContext	The context supplied when the callback was registered.
 * \param	inURI		The full pathname of the node. The URI of a node is
 *						a string of all of its parents, and the node name,
 *						separated by '/'.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Tree_DeleteFunc) (void *inContext, const char *inURI);

/*!
 *******************************************************************************
 * Register a Delete callback for a node. The node must exist.
 *
 * \note	To unregister a Delete callback for a node, call
 *			this API with \a inFunc and \a inContext set to NULL.
 *
 * \param	inURI		The full pathname of the node. The URI of a node is
 *						a string of all of its parents, and the node name,
 *						separated by '/'.
 * \param	inFunc		The callback to invoke when the node is deleted.
 *						See \ref VDM_Tree_DeleteFunc.
 * \param	inContext	Context passed to \a inFunc.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			or VDM_ERR_NODE_MISSING if the node could not be found
 *******************************************************************************
 */
extern VDM_Error VDM_Tree_registerDelete(
	const char *inURI,
	VDM_Tree_DeleteFunc inFunc,
	void *inContext);

/*!
 *******************************************************************************
 * Register a Delete callback for all nodes in a sub-tree.
 *
 * \note	To unregister a Delete callback for a sub-tree, call
 *			this API with \a inDeleteFunc and \a inContext set to NULL.
 *
 * \param	inURI			The full pathname of the root of the sub-tree. The
 *							URI of a node is a string of all of its parents,
 *							and the node name, separated by '/'. The node may
 *							be an interior node or a leaf node.
 * \param	inDeleteFunc	The callback to invoke when the node is deleted.
 *							See \ref VDM_Tree_DeleteFunc.
 * \param	inContext		Context passed to \a inDeleteFunc.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			or VDM_ERR_NODE_MISSING if the node could not be found
 *******************************************************************************
 */
VDM_Error VDM_Tree_registerDeleteSubtree(
	const char *inURI,
	VDM_Tree_DeleteFunc inDeleteFunc,
	void *inContext);
/*!
 *******************************************************************************
 * Callback invoked when a node is added.
 *
 * \param	inContext		Context supplied when the callback was registered.
 * \param	inData			A pointer to the data.
 * \param	inOffset		The byte offset from the start of the data.
 * \param	inDataLen		The length of \a inData, in bytes.
 * \param	inTotalSize		The total length of the data. This may be different
 *							from \a inDataLen if partial writes are used.
 * \param	inFormat		Format for the added node. "node" indicates an
 *							interior node, while "chr", "int", "bin", and so on
 *							indicate the format of the value of a leaf node.
 * \param	inURI			The full pathname of the node. The URI of a node is
 *							a string of all of its parents, and the node name,
 *							separated by '/'.
 * \param   outDFFlags      The access type flags for the newly created node.
 *							These are defined in \ref E_VDM_Tree_DFProperties_t.
 *							To maintain the default behavior, use \ref
 *                          E_VDM_Tree_DFProperties_t#E_VDM_Tree_DFProperties_defaultBehavior.
 * \param   inPhase         The phase of the Add operation (currently not
 *							implemented).
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Tree_AddFunc) (void *inContext, const void *inData,
	IU32 inOffset, IU32 inDataLen, IU32 inTotalSize, const char *inFormat,
	const char *inURI, IS8 *outDFFlags, E_VDM_Tree_AddNotifyCB_operationPhase_t inPhase);

/*!
 *******************************************************************************
 * Register an Add callback for a node. The node must exist and be an interior
 * node.
 *
 * \note	To unregister an Add callback for a node, call
 *			this API with \a inFunc and \a inContext set to NULL.
 *
 * \param	inURI		The full pathname of the node. The URI of a node is
 *						a string of all of its parents, and the node name,
 *						separated by '/'.
 * \param	inFunc		The callback to invoke when the node is added.
 *						See \ref VDM_Tree_AddFunc.
 * \param	inContext	Context passed to \a inFunc.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			VDM_ERR_NODE_MISSING if the node could not be found,
 *			or VDM_ERR_LEAF_NODE if the node is a leaf node
 *******************************************************************************
 */
extern VDM_Error VDM_Tree_registerAdd(
	const char *inURI,
	VDM_Tree_AddFunc inFunc,
	void *inContext);

/*!
 *******************************************************************************
 * Register an Add callback for all nodes in a sub-tree. The root of the
 * sub-tree must be an interior node.
 *
 * \note	To unregister an Add callback for a sub-tree, call
 *			this API with \a inAddFunc and \a inContext set to NULL.
 *
 * \param	inURI		The full pathname of the root of the sub-tree. The URI
 *						of a node is a string of all of its parents, and the
 *						node name, separated by '/'.
 * \param	inAddFunc	The callback to invoke when a node is added.
 *						See \ref VDM_Tree_AddFunc.
 * \param	inContext	Context passed to \a inAddFunc.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			VDM_ERR_NODE_MISSING if the node could not be found,
 *			or VDM_ERR_LEAF_NODE if the node is a leaf node
 *******************************************************************************
 */
VDM_Error VDM_Tree_registerAddSubtree(
	const char *inURI,
	VDM_Tree_AddFunc inAddFunc,
	void *inContext);

/*!
 *******************************************************************************
 * Replace the ACL (Access Control List) of a node. The node must exist. If
 * replacing the ACL of the root node, the new ACL must allow "Add".
 *
 * \param	inURI	The full pathname of the node. The URI of a node is
 *					a string of all of its parents, and the node name,
 *					separated by '/'.
 * \param	inACL	The new ACL.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			VDM_ERR_NODE_MISSING if the node could not be found,
 *			or VDM_ERR_NOT_ALLOWED if the node is the root node and the new ACL
 *			does not allow "Add"
 *******************************************************************************
 */
extern VDM_Error VDM_Tree_replaceACL(
	const char *inURI,
	const char *inACL);

/*!
 *******************************************************************************
 * Get the ACL (Access Control List) of a node. The node must exist.
 *
 * \param	inURI		The full pathname of the node. The URI of a node is
 *						a string of all of its parents, and the node name,
 *						separated by '/'.
 * \param	outBuffer	Pre-allocated result buffer.
 * \param	ioLength	Input: Size of \a outBuffer, in bytes.
 *						Output: Length of the ACL string, in bytes.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			VDM_ERR_NODE_MISSING if the node could not be found,
 *			VDM_ERR_BUFFER_OVERFLOW if the supplied buffer is too small,
 *			or VDM_ERR_UNSPECIFIC for an unspecified error
 *******************************************************************************
 */
extern VDM_Error VDM_Tree_getACL(
	const char *inURI,
	char *outBuffer,
	IU32 *ioLength);

/*!
 * DEPRECATED. Use VDM_Tree_getPropertyAcl instead.
 */
extern VDM_Error VDM_Tree_getProperty(const char *inURI, const char *inPropertyName,
	void *outBuffer, IU32 *ioLength);

/*!
 *******************************************************************************
 * Get a property of a node. The node must exist.
 *
 * \param	isAcl		Should this call verify ACL pemissions.
 * \param	inServer	Server id for ACL verivication. Used only if isAcl is true.
 * \param	inURI			The full pathname of the node. The URI of a node is
 *							a string of all of its parents, and the node name,
 *							separated by '/'.
 * \param	inPropertyName	The name of the property. Supported properties
 *							include: "ACL", "Format", "Name", "Size", "Title",
 *							and "Type".
 * \param	outBuffer		Pre-allocated result buffer.
 * \param	ioLength		Input: Size of \a outBuffer, in bytes.
 *							Output: Length of the returned output, in bytes.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			VDM_ERR_NODE_MISSING if the node could not be found,
 *			VDM_ERR_BUFFER_OVERFLOW if the supplied buffer is too small,
 *			or VDM_ERR_UNKNOWN_PROPERTY if an unsupported property was supplied
 *******************************************************************************
 */
extern VDM_Error VDM_Tree_getPropertyAcl(int isAcl, char *inServer, const char *inURI,
	const char *inPropertyName, void *outBuffer, IU32 *ioLength);

/*!
 *******************************************************************************
 * Replace a property of a node. The node must exist.
 *
 * \param	inURI			The full pathname of the node. The URI of a node is
 *							a string of all of its parents, and the node name,
 *							separated by '/'.
 * \param	inPropertyName	The name of the property. Supported properties
 *							include: "ACL", "Format", "Name", "Size", "Title",
 *							and "Type".
 * \param	inValue			The new value.
 * \param	inSize			The size of \a inValue, in bytes.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_BAD_INPUT,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			VDM_ERR_NODE_MISSING if the node could not be found,
 *			VDM_ERR_TREE_MAY_NOT_REPLACE if the property may not be replaced,
 *			VDM_ERR_UNKNOWN_PROPERTY if an unsupported property was supplied,
 *			VDM_ERR_PERMANENT_NODE if the node is a permanent node,
 *			VDM_ERR_ALREADY_EXISTS if  the property is "Name" and a node with
 *			the same name already exists at this path,
 *			or VDM_ERR_NOT_ALLOWED if the node is the root node, the property is
 *			"ACL", and the new ACL doesn't allow "Add"
 *******************************************************************************
 */
extern VDM_Error VDM_Tree_replaceProperty(
	const char *inURI,
	const char *inPropertyName,
	void *inValue,
	IU32 inSize);

/*!
 *******************************************************************************
 * Force a write of the DM Tree to persistent storage.
 *
 * Note that the DM Tree is automatically written to persistent storage when
 * OMA DM Protocol Engine is destroyed.
 *
 * \return	VDM_ERR_OK on success,
 *			VDM_ERR_MEMORY if there is no memory to perform the action,
 *			VDM_ERR_STORAGE_OPEN if persistent storage can't be opened,
 *			or VDM_ERR_STORAGE_COMMIT if the data can't be committed
 *******************************************************************************
 */
extern VDM_Error VDM_Tree_writeToPersistentStorage(void);

/*!
 *******************************************************************************
 * Check if a node exists in the DM Tree.
 *
 * \param	inUri	The full pathname of the node. The URI of a node is
 *					a string of all of its parents, and the node name,
 *					separated by '/'.
 *
 * \return	TRUE is the node exists in the DM Tree, FALSE otherwise
 *******************************************************************************
 */
extern IBOOL VDM_Tree_nodeExists(const char *inUri);

/*!
 *******************************************************************************
 * Callback invoked when the ACL of the node has changed.
 * \param	inURI		The full pathname of the node.
 * \param	inNewAcl	The new ACL for the node.
 *
 * \return	None
 *******************************************************************************
 */
typedef void (*VDM_Tree_ReplaceAclNotifyCB) (const char *inURI, const char *inNewAcl);

/*!
 *******************************************************************************
 * Register to be notified when the ACL of a node has changed.
 *
 * \param	inNotifyFunc	Callback for notifying of the ACL change.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_Tree_registerAclNotify(VDM_Tree_ReplaceAclNotifyCB inNotifyFunc);

/*!
 *******************************************************************************
 * Callback invoked when the node has changed.
 *
 * \param	inURI			The full pathname of the changed node. The URI of a
 *							node is a string of all of its parents, and the node
 *							name, separated by '/'.
 * \param	inContext		Context supplied when the callback was registered.
 * \param	inOffset	    The byte offset from the start of the data.
 * \param	inData		    A pointer to the data.
 * \param	inDataLen	    The length of the current chunk of data, in bytes.
 * \param	inTotalSize	    The total size of the data.
 * \param	inFormat	    Node data format ("chr", "int", and so on). The
 *							default is "chr".
 * \param	inType		    Node MIME type (may be NULL).
 * \param   inOriginator    The source that caused the tree operation, defined
 *                          by \ref E_VDM_Tree_OperationOriginator_t type.
 * \param	inResult		Operation result.
 *
 * \return	VDM_ERR_OK
 *******************************************************************************
 */
typedef VDM_Error (*VDM_Tree_ReplaceNotifyCB) (
	const char *inURI,
	void *inContext,
	IU32 inOffset,
	const void *inData,
	IU32 inDataLen,
	IU32 inTotalSize,
	const char *inFormat,
	const char *inType,
	E_VDM_Tree_OperationOriginator_t inOriginator,
	IU32 inResult);

/*!
 *******************************************************************************
 * Register to be notified when any node has changed.
 *
 * \note	To unregister, call this API with \a inNotifyFunc and \a inContext
 *          set to NULL.
 *
 * \param	inNotifyFunc    The callback to invoke when a node has changed.
 *						    See \ref VDM_Tree_ReplaceNotifyCB.
 * \param	inContext	    Context passed to \a inNotifyFunc.
 *
 * \return  VDM_ERR_OK on success,
 *          or VDM_ERR_INVALID_CALL if this API was called before the tree was
 *          initialized.
 *******************************************************************************
 */
extern VDM_Error VDM_Tree_registerReplaceNotify(
	VDM_Tree_ReplaceNotifyCB inNotifyFunc,
	void *inContext);

/*!
 *******************************************************************************
 * Register to be notified when a specific node has changed.
 *
 * \note	To unregister, call this API with \a inNotifyFunc and \a inContext
 *          set to NULL.
 *
 * \param   inURI			Node's path
 * \param	inNotifyFunc    The callback to invoke when a node has changed.
 *						    See \ref VDM_Tree_ReplaceNotifyCB.
 * \param	inContext	    Context passed to \a inNotifyFunc.
 *
 * \return  VDM_ERR_OK on success,
 *          or VDM_ERR_INVALID_CALL if this API was called before the tree was
 *          initialized.
 *******************************************************************************
 */
VDM_Error VDM_Tree_registerReplace(const char *inURI,
	VDM_Tree_ReplaceNotifyCB inFunc, void *inContext);

/*!
 *******************************************************************************
 * Register to be notified before an EXEC callback is invoked. This notification
 * may be used to prevent the EXEC callback from being invoked.
 *
 * \see		VDM_Tree_registerExecute
 *
 * \deprecated  Use \ref VDM_Tree_registerPreExecObserver and
 *              \ref VDM_Tree_registerPreExecObserver instead.
 *
 * \param	inNotifyFunc	Callback for notifying before EXEC.
 * \param	inContext		Context passed to the \a inNotifyFunc.
 *
 * \return	VDM_ERR_OK on success or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_Tree_registerPreExecNotify(
	VDM_Tree_PreCmdNotify_t inNotifyFunc, void *inContext);

/*!
 *******************************************************************************
 * Register to be notified before an EXEC callback is invoked. This notification
 * may be used to prevent the EXEC callback from being invoked.
 *
 * \note    More than one observer may be registered.
 *
 * \see		VDM_Tree_unregisterPreExecObserver
 *
 * \param	inObserverFunc	Callback for notifying before EXEC.
 * \param	inContext		Context passed to the \a inObserverFunc.
 * \param	outMsg			Optional. A string that will be sent to the server
 *                          in addition to the result. Should be allocated in
 *                          the observer function and will be freed by the engine.
 *
 * \return	VDM_ERR_OK on success VDM_ERR_INVALID_CALL if \a inObserverFunc
 *          is NULL, VDM_ERR_MEMORY, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_Tree_registerPreExecObserver(
	VDM_Tree_PreCmdNotify_t inObserverFunc, void *inContext);

/*!
 *******************************************************************************
 * Unregister a pre-EXEC observer.
 *
 * \see		VDM_Tree_registerPreExecObserver
 *
 * \param	inObserverFunc	Registered observer's callback
 * \param	inContext		Context passed to the \a inObserverFunc.
 *
 * \return	VDM_ERR_OK on success or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_Tree_unregisterPreExecObserver(
	VDM_Tree_PreCmdNotify_t inObserverFunc, void *inContext);

/*!
 *******************************************************************************
 * Register to be notified before a REPLACE command is executed. This
 * notification may be used to prevent the REPLACE command from being executed.
 *
 * \note    More than one observer may be registered.
 *
 * \see		VDM_Tree_unregisterPreReplaceObserver
 *
 * \param	inObserverFunc	Callback for notifying before REPLACE.
 * \param	inContext		Context passed to the \a inObserverFunc.
 * \param	outMsg			Optional. A string that will be sent to the server
 *	                        in addition to the result. Should be allocated in
 *                          the observer function and will be freed by the engine.
 *
 * \return	VDM_ERR_OK on success VDM_ERR_INVALID_CALL if \a inObserverFunc
 *          is NULL, VDM_ERR_MEMORY, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_Tree_registerPreReplaceObserver(
	VDM_Tree_PreCmdNotify_t inObserverFunc, void *inContext);

/*!
 *******************************************************************************
 * Unregister a pre-REPLACE observer.
 *
 * \see		VDM_Tree_registerPreReplaceObserver
 *
 * \param	inObserverFunc	Registered observer's callback
 * \param	inContext		Context passed to the \a inObserverFunc.
 *
 * \return	VDM_ERR_OK on success or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
extern VDM_Error VDM_Tree_unregisterPreReplaceObserver(
	VDM_Tree_PreCmdNotify_t inObserverFunc, void *inContext);

/*!
 *******************************************************************************
 * Check if the DM Tree exists.
 *
 * \return	TRUE if the DM Tree exists, FALSE otherwise
 *******************************************************************************
 */
IBOOL VDM_Tree_isTreeExist(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

