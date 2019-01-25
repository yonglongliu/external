/*
 *******************************************************************************
 *
 * vdm_error.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_error.h
 *
 * \brief	Error Codes
 *
 * The error codes returned by OMA DM Protocol Engine APIs.
 *******************************************************************************
 */
#ifndef VDM_ERROR_H__
#define VDM_ERROR_H__			//!< Internal

#ifdef __cplusplus
extern "C" {
#endif

#include <vdm_pl_types.h>

/*! VDM_Error */
typedef IS32 VDM_Error;

/*! \addtogroup VDM_ERR_defs Errors
 * @{
 */

/*! Success */
#define VDM_ERR_OK                                  0x0000  /*     0 */

/*! Invalid input */
#define VDM_ERR_INVALID_INPUT_PARAM                 0x0002  /*     2 */

/*! Unspecified error */
#define VDM_ERR_UNSPECIFIC                          0x0010  /*    16 */

/*! Memory error */
#define VDM_ERR_MEMORY                              0x0011  /*    17 */

/*! Routine called when not allowed or bad parameters */
#define VDM_ERR_INVALID_CALL                        0x0012  /*    18 */

/*! \ref VDM_run called with non-resume trigger when suspended */
#define VDM_ERR_IS_SUSPENDED                        0x0013  /*    19 */

/*! SyncML message protocol or version error */
#define VDM_ERR_INVALID_PROTO_OR_VERSION            0x0020  /*	  32 */

/*! RTK workspace buffer too small */
#define VDM_ERR_RTK_BUFFER_OVERFLOW                 0x2002  /*	8194 */

/*
 * Synchronous Exec return codes range
 */

/*! Start range of synchronous Exec return code (not an error) */
#define VDM_ERR_EXEC_START_RANGE                    0x3000 /* 12288 */

/*! End range of synchronous Exec return code (not an error) */
#define VDM_ERR_EXEC_END_RANGE                      0x3FFF /* 16383 */

/*
 * Analytics error codes range
 */
/*! Start range of Analytics return code (not an error) */
#define VDM_ERR_ANALYTICS_RANGE_START               0x4000  /* 16384 */

/*! Failed to create database */
#define VDM_ERR_DATABASE_CREATE_FAILED              0x4200  /* 16896 */

/*! Failed to open database */
#define VDM_ERR_DATABASE_OPEN_FAILED                0x4201  /* 16897 */

/*! Failed to insert data to database */
#define VDM_ERR_DATABASE_INSERT_DATA_FAILED         0x4202  /* 16898 */

/*! Failed to update data to database */
#define VDM_ERR_DATABASE_UPDATE_DATA_FAILED         0x4203  /* 16899 */

/*! Failed to select data from database */
#define VDM_ERR_DATABASE_SELECT_DATA_FAILED         0x4204  /* 16900 */

/*! Failed to delete data from database */
#define VDM_ERR_DATABASE_DELETE_DATA_FAILED         0x4205  /* 16901 */

/*! Failed to purge data from database */
#define VDM_ERR_DATABASE_PURGE_DATA_FAILED          0x4206  /* 16902 */

/*! Failed to upgrade the database schema */
#define VDM_ERR_DATABASE_UPGRADE_FAILED             0x4207  /* 16903 */

/*! Bad  Message from server */
#define VDM_ERR_BAD_MSG                             0x4230  /* 16944 */

/*! End range of Analytics return code (not an error) */
#define VDM_ERR_ANALYTICS_RANGE_END                 0x4FFF  /* 20479 */

/* SWM Errors */

/*! Invalid ordinal number for installer type */
#define VDM_ERR_INVALID_ORD_NUM_FOR_INST_TYPE       0x5001  /* 20481 */

/*! No installer exists for that type */
#define VDM_ERR_NO_MATCHING_INSTALLER               0x5002  /* 20482 */

/*! Environment API failure */
#define VDM_ERR_ENV                                 0x5101  /* 20737 */

/*! Not enough privileges (ensure AEEPRIVID_PLFile, AEEPRIVID_ModInstaller) */
#define VDM_ERR_PRIVLEVEL                           0x5103  /* 20739 */

/*! Component not initialized */
#define VDM_ERR_NOT_INITILIZED                      0x5104  /* 20740 */

/*! Component already initialized */
#define VDM_ERR_ALREADY_INITILIZED                  0x5105  /* 20741 */

/*! Component not found */
#define VDM_ERR_COMP_MISSING                        0x5107  /* 20743 */

/*! Installer currently busy */
#define VDM_ERR_BUSY                                0x5108  /* 20744 */

/*! Invalid DP */
#define VDM_ERR_DP_FAILURE                          0x5109  /* 20745 */

/*! User cancelled the operation */
#define VDM_ERR_CANCELLED                           0x5110  /* 20752 */

/*! Attribute not supported */
#define VDM_ERR_ATTR_NOT_SUPPORT                    0x5111  /* 20753 */

/*! File system space not available */
#define VDM_ERR_NO_FS_SPACE_AVAILABLE               0x5112  /* 20754 */

/*! External validation of the DP failed */
#define VDM_ERR_DP_EXT_VALIDATION_FAILED            0x5113  /* 20755 */

/*! External validation of the Signature failed */
#define VDM_ERR_DP_EXT_SIGNATURE_FAILED             0x5114  /* 20756 */
/*! External validation of the CERTIFICATE FALIED */
#define VDM_ERR_DP_EXT_CERTIFICATE_FAILED           0x5115  /* 20757 */
/*! External validation of the CERTIFICATE EXPIRED */
#define VDM_ERR_DP_EXT_CERTIFICATE_EXPIRED          0x5116  /* 20758 */
/*! External UNKNOW VALIDATAION FALIED */
#define VDM_ERR_DP_EXT_VALIDATION_UNKNOWN           0x5117  /* 20759 */

/*! Uninstall failure */
#define VDM_UA_ERR_FAILED_TO_UNINSTALL_APK          0x5200  /* 20992 */

/*! Install failure */
#define VDM_UA_ERR_FAILED_TO_INSTALL_APK            0x5201  /* 20993 */

/*! Parsing error */
#define VDM_UA_ERR_PM_PARSING_ERROR                 0x5203  /* 20995 */

/*! cannot open directory */
#define VDM_ERR_DIR_OPEN                            0x5204  /* 20996 */

/*! mount failed */
#define VDM_ERR_MOUNT                               0x5205  /* 20997 */

/*! File not found*/
#define VDM_ERR_FILE_NOT_FOUND                      0x5206  /* 20998 */

/*! UA errors */
/**************/
/*! UA error */
#define VDM_UA_ERR_BASE                             0x5800  /* 22528 */

/*! UA: Illegal command */
#define VDM_UA_ERR_ILLEGAL_CMD                      VDM_UA_ERR_BASE + 0x1

/*! UA: Can't allocate memory */
#define VDM_UA_ERR_CANT_ALLOCATE_RAM                VDM_UA_ERR_BASE + 0x2

/*! Supplied buffer is too small */
#define VDM_ERR_BUFFER_OVERFLOW                     0x6000  /* 24576 */

/*! Badly formatted input */
#define VDM_ERR_BAD_INPUT                           0x6001  /* 24577 */

/*! Tree node already exists */
#define VDM_ERR_NODE_ALREADY_EXISTS                 0x6002  /* 24578 */

/*! Tree node is missing */
#define VDM_ERR_NODE_MISSING                        0x6003  /* 24579 */

/*! Parent node is missing */
#define VDM_ERR_PARENT_MISSING                      0x6004  /* 24580 */

/*! Error in leaf node */
#define VDM_ERR_LEAF_NODE                           0x6005  /* 24581 */

/*! Leaf node expected */
#define VDM_ERR_NOT_LEAF_NODE                       0x6006  /* 24582 */

/*! Unknown property */
#define VDM_ERR_UNKNOWN_PROPERTY                    0x6007  /* 24583 */

/*! Attempt made to delete a permanent node */
#define VDM_ERR_PERMANENT_NODE                      0x6008  /* 24584 */

/*! Not allowed by AccessType */
#define VDM_ERR_NOT_ALLOWED                         0x6009  /* 24585 */

/*! Client aborted */
#define VDM_ERR_ABORT                               0x600a  /* 24586 */

/*! Client access denied */
#define VDM_ERR_TREE_ACCESS_DENIED                  0x600b  /* 24587 */

/*! Partial write of external data not allowed */
#define VDM_ERR_TREE_EXT_NOT_PARTIAL                0x600c  /* 24588 */

/*! Write of external data not allowed at this time */
#define VDM_ERR_TREE_EXT_NOT_ALLOWED                0x600d  /* 24589 */

/*! May not replace */
#define VDM_ERR_TREE_MAY_NOT_REPLACE                0x600e  /* 24590 */

/*! Persistent storage read error */
#define VDM_ERR_STORAGE_READ                        0x600f  /* 24591 */

/*! Persistent storage write error */
#define VDM_ERR_STORAGE_WRITE                       0x6010  /* 24592 */

/*! Authentication failure */
#define VDM_ERR_AUTHENTICATION                      0x6011  /* 24593 */

/*! Access denied by ACL */
#define VDM_ERR_NODE_ACCESS_DENIED                  0x6012  /* 24594 */

/*! External data value is not readable */
#define VDM_ERR_NODE_VALUE_NOT_READABLE             0x6013  /* 24595 */

/*! External data value is not writable */
#define VDM_ERR_NODE_VALUE_NOT_WRITEABLE            0x6014  /* 24596 */

/*! Node not registered for execute */
#define VDM_ERR_NODE_NOT_EXECUTABLE                 0x6015  /* 24597 */

/*! Tree open error */
#define VDM_ERR_STORAGE_OPEN                        0x6016  /* 24598 */

/*! Tree commit error */
#define VDM_ERR_STORAGE_COMMIT                      0x6017  /* 24599 */

/*! General storage error */
#define VDM_ERR_STORAGE_NO_SPACE                    0x6018  /* 24600 */

/*! Register external callback failed */
#define VDM_ERR_REGISTER_EXT_CB_FAILED              0x6019  /* 24601 */

/*! No more commands<br>Used internally by the Engine. This is not really an
 * error. */
#define VDM_ERR_NO_MORE_COMMANDS                    0x6100 /* 24832 */

/*! Missing start message command */
#define VDM_ERR_MISSING_START_MESSAGE_CMD           0x6101 /* 24833 */

/*! Missing status command */
#define VDM_ERR_MISSING_STATUS_CMD                  0x6102 /* 24834 */

/*! Optional feature not implemented */
#define VDM_ERR_NOT_IMPLEMENTED                     0x6103 /* 24835 */

/*! Alert - options parsing error */
#define VDM_ERR_ALERT_PARSING_ERROR                 0x6105 /* 24837 */

/*! Alert - not enough items */
#define VDM_ERR_ALERT_MISSING_ITEMS                 0x6106 /* 24838 */

/*! Alert - not enough data */
#define VDM_ERR_ALERT_MISSING_DATA                  0x6107 /* 24839 */

/*! No data */
#define VDM_ERR_NO_DATA                             0x6108 /* 24840 */

/*! Alert - user cancelled or aborted */
#define VDM_ERR_ALERT_USER_ABORTED                  0x6109 /* 24841 */

/*! Alert - too many choices passed to implementation */
#define VDM_ERR_ALERT_TOO_MANY_CHOICES              0x610a /* 24842 */

/*! Alert - server has sent a session-abort alert */
#define VDM_ERR_ALERT_SESSION_ABORTED               0x610b /* 24843 */

/*! Large object item has been handled<br>Used internally by the Engine. This
 * is not really an error. */
#define VDM_ERR_LO_HANDLED                          0x610c /* 24844 */

/*! Data is too long to pass back as a large object */
#define VDM_ERR_TOO_BIG                             0x610d /* 24845 */

/*! Command status code is failed */
#define VDM_ERR_COMMAND_FAILED                      0x610e /* 24846 */

/*! The media type or format for the data item is not supported by the recipient */
#define VDM_ERR_UNSUPPORTED_MEDIA                   0x610f /* 24847 */

/*! Notification - message has invalid length */
#define VDM_ERR_NOTIF_BAD_LENGTH                    0x6200  /* 25088 */

/*! Notification - message has invalid digest */
#define VDM_ERR_NOTIF_BAD_DIGEST                    0x6201  /* 25089 */

/*! Boot message has invalid digest */
#define VDM_ERR_BOOT_DIGEST                         0x6202  /* 25090 */

/*! Could not get NSS for bootstrap */
#define VDM_ERR_BOOT_NSS                            0x6203  /* 25091 */

/*! Could not get PIN for bootstrap */
#define VDM_ERR_BOOT_PIN                            0x6204  /* 25092 */

/*! Bad bootstrap PIN length */
#define VDM_ERR_BOOT_PINLENGTH                      0x6205  /* 25093 */

/*! Bad bootstrap SEC value */
#define VDM_ERR_BOOT_BAD_SEC                        0x6206  /* 25094 */

/*! Bad bootstrap MAC */
#define VDM_ERR_BOOT_BAD_MAC                        0x6207  /* 25095 */

/*! Bad bootstrap message */
#define VDM_ERR_BOOT_BAD_MESSAGE                    0x6208  /* 25096 */

/*! Bad bootstrap profile */
#define VDM_ERR_BOOT_BAD_PROF                       0x6209  /* 25097 */

/*! Bad trigger reason */
#define VDM_ERR_TRG_BAD_REASON                      0x6210  /* 25104 */

/*! Notification - message contains unsupported version info */
#define VDM_ERR_NOTIF_UNSUPPORTED_VERSION           0x6211  /* 25105 */

/*! Bootstrap not currently allowed */
#define VDM_ERR_BOOT_DISABLED                       0x6212  /* 25106 */

/*! Non-DM Bootstrap message  */
#define VDM_ERR_CP_BOOSTRAP_WITHOUT_DM_PROFILE      0x6213  /* 25107 */

/*! Download object too large */
#define VDM_ERR_DL_OBJ_TOO_LARGE                    0x6214  /* 25108 */

/*! Bad Nia Format */
#define VDM_ERR_BAD_NIA_FORMAT                      0x6215  /* 25109 */

/*
 *	Communication errors
 */

/*! Unsupported protocol */
#define VDM_ERR_COMMS_BAD_PROTOCOL                  0x6300 /* 25344 */

/*! Mismatched reply: XML received when WBXML sent or vice-versa */
#define VDM_ERR_COMMS_MIME_MISMATCH                 0x6301 /* 25345 */

/*! General fatal transport error */
#define VDM_ERR_COMMS_FATAL                         0x6302 /* 25346 */

/*! Start range of non-fatal communication errors */
#define VDM_ERR_COMMS_NON_FATAL_RANGE_START         0x6303

/*! General non-fatal transport error (can be retried) */
 #define VDM_ERR_COMMS_NON_FATAL                    0x6303 /* 25347 */
/*! Socket timeout transport error */
 #define VDM_ERR_COMMS_SOCKET_TIMEOUT               0x6304 /* 25348 */
/*! General socket non-fatal (retriable) socket error */
 #define VDM_ERR_COMMS_SOCKET_ERROR                 0x6305 /* 25349 */
/*! HTTP result wasn't found */
 #define VDM_ERR_HTTP_RESULT_NOT_FOUND              0x6306 /* 25350 */
/*! HTTP result bad request*/
 #define VDM_ERR_HTTP_RESULT_BAD_REQUEST            0x6307 /* 25351 */
/*! HTTP result internal server error*/
 #define VDM_ERR_HTTP_RESULT_INTERNAL_SERVER_ERROR    0x6308 /* 25352  */
/*! HTTP result server error*/
#define VDM_ERR_HTTP_RESULT_SERVER_ERROR           0x6309 /* 25353  */
/*! HTTP too many requests  error*/
#define VDM_ERR_HTTP_TOO_MANY_REQUESTS_ERROR           0x630A /* 25354  */

/*! End range of non-fatal communication errors */
#define VDM_ERR_COMMS_NON_FATAL_RANGE_END           0x633F

/*! Start range of fatal communication errors */
 #define VDM_ERR_COMMS_FATAL_RANGE_START                0x6340
/*! HTTP error */
 #define VDM_ERR_COMMS_HTTP_ERROR                   0x6340 /* 25408 */
/*! Received forbidden response from HTTP */
#define VDM_ERR_COMMS_HTTP_FORBIDDEN                0x6341 /* 25409 */
/*! End range of fatal communication errors */
#define VDM_ERR_COMMS_FATAL_RANGE_END               0x637F

/*! Get if fatal communication error */
#define IS_VDM_COMMS_ERROR_FATAL(E)	\
	((E) == (VDM_ERR_COMMS_FATAL) || \
	((E) >= (VDM_ERR_COMMS_FATAL_RANGE_START) && (E) <= (VDM_ERR_COMMS_FATAL_RANGE_END)))

/*! Get if non-fatal communication error */
#define IS_VDM_COMMS_ERROR_NON_FATAL(E)	\
	((E) >= (VDM_ERR_COMMS_NON_FATAL_RANGE_START) && (E) <= (VDM_ERR_COMMS_FATAL_RANGE_END))

/*! Start range of vendor specified transport errors */
#define VDM_ERR_COMMS_VENDOR_SPECIFIC_RANGE_START   0x6380 /* 25472 */
/*! End range of vendor specified transport errors */
#define VDM_ERR_COMMS_VENDOR_SPECIFIC_RANGE_END     0x63FF /* 25599 */

/*! Internal error */
#define VDM_ERR_INTERNAL                            0x6401 /* 25601 */

/*! Error accessing MO external storage */
#define VDM_ERR_MO_STORAGE                          0x6402 /* 25602 */

/*! User cancelled update or download */
#define VDM_ERR_CANCEL                              0x6404 /* 25604 */

/*! Could not initiate update client */
#define VDM_ERR_UPDATE_INIT                         0x6405 /* 25605 */

/*! Download URL is malformed or bad */
#define VDM_ERR_BAD_URL                             0x6406 /* 25606 */

/*! Error while parsing Download Descriptor */
#define VDM_ERR_BAD_DD                              0x6407 /* 25607 */

/*! ETag changed, 412 returned because of If-match */
#define VDM_ERR_COMMS_OBJECT_CHANGED                0x6408 /* 25608 */

/*! Error while parsing Download Descriptor - descriptor size is 0*/
#define VDM_ERR_BAD_DD_INVALID_SIZE                 0x6409 /* 25609 */

/*! A call to a OMA DM Protocol Engine API is out of sync */
#define VDM_ERR_OUT_OF_SYNC                         0x6500 /* 25856 */

/*
 * DS error codes (for future use).
 */

/*! For future use */
#define VDM_ERR_MISSING_DATASTORE                   0x7001 /* 28673 */

/*! For future use */
#define VDM_ERR_NO_ANCHOR                           0x7002 /* 28674 */

/*! For future use */
#define VDM_ERR_SUCCESS_ADD                         0x7201 /* 29185 */

/*! For future use */
#define VDM_ERR_CLIENT_PREVAIL                      0x7208 /* 29192 */

/*! For future use */
#define VDM_ERR_DELETED_WITHOUT_ARCHIVE             0x7210 /* 29200 */

/*! For future use */
#define VDM_ERR_DATA_NOT_DELETED                    0x7211 /* 29201 */

/*! For future use */
#define VDM_ERR_PASS_AUTHENTICATION                 0x7212 /* 29202 */

/*! For future use */
#define VDM_ERR_DELIVER_LARGE_OBJ                   0x7213 /* 29203 */

/*! For future use */
#define VDM_ERR_AUTH_ERR                            0x7401 /* 29697 */

/*! For future use */
#define VDM_ERR_AUTH_ERR_ANOTHER_SYNCML             0x7403 /* 29699 */

/*! For future use */
#define VDM_ERR_DELETE_NO_DATE                      0x7404 /* 29700 */

/*! For future use */
#define VDM_ERR_AUTH_REQUESTED                      0x7407 /* 29703 */

/*! For future use */
#define VDM_ERR_REVISE_CONFLICT                     0x7409 /* 29705 */

/*! For future use */
#define VDM_ERR_UNINTEGRATED_CMD                    0x7412 /* 29714 */

/*! For future use */
#define VDM_ERR_TARGET_DATA_EXISTS                  0x7418 /* 29720 */

/*! For future use */
#define VDM_ERR_CONFLICT_SRV_PREVAIL                0x7419 /* 29721 */

/*! For future use */
#define VDM_ERR_LIMIT_CAPACITY                      0x7420 /* 29728 */

/*! For future use */
#define VDM_ERR_DEFAULT_SERVER_ERR                  0x7500 /* 29952 */

/*! For future use */
#define VDM_ERR_BUSY_SERVER                         0x7503 /* 29955 */

/*! For future use */
#define VDM_ERR_MORE_SLOW_SYNC                      0x7508 /* 29960 */

/*! For future use */
#define VDM_ERR_ACCESS_DATABASE                     0x7510 /* 29968 */

/*! For future use */
#define VDM_ERR_SERVER_ERROR                        0x7511 /* 29969 */

/*! For future use */
#define VDM_ERR_FAILED_SYNCML                       0x7512 /* 29970 */

/*! For future use */
#define VDM_ERR_UNSUPPORTED_PROT_VER                0x7513 /* 29971 */

/*
 *	OMA DM Protocol Engine errors
 */

/*! Error accessing registry */
#define VDM_ERR_REGISTRY                         0x8001 /* 32769 */

/*! Shutting down - cannot enqueue triggers or timed events */
#define VDM_ERR_SHUTTING_DOWN                    0x8002 /* 32770 */

/*! Out of Bounds - an array was accessed out of bounds */
#define VDM_ERR_OUT_OF_BOUNDS                    0x8003 /* 32771 */

/*! Download package cannot be removed */
#define VDM_ERR_STORAGE_REMOVE                   0x8004 /* 32772 */

/*! Error accessing storage */
#define VDM_ERR_STORAGE_SEEK                     0x8005 /* 32773 */

/*! One of the storage errors */
#define IS_VDM_TREE_ERROR(E)					(((E) == VDM_ERR_STORAGE_WRITE) || \
												((E) == VDM_ERR_STORAGE_READ) || \
												((E) == VDM_ERR_STORAGE_COMMIT))

/*! error in pack/unpack files */
#define VDM_ERR_UNPACK_EXTERNAL_NOT_FOUND          0x8101 /* 33025 */
#define VDM_ERR_UNPACK_NOT_VALID                   0x8102 /* 33026 */
#define VDM_ERR_UNPACK_INTERNAL_NOT_FOUND          0x8103 /* 33027 */
#define VDM_ERR_UNPACK_INTERNAL_EMPTY              0x8104 /* 33028 */
#define VDM_ERR_UNPACK_NO_SPACE                    0x8105 /* 33029 */
#define VDM_ERR_UNPACK_NOT_FOUND                   0x8106 /* 33030 */
#define VDM_ERR_UNPACK_FAILED                      0x8107 /* 33031 */


/*! json errors */
#define VDM_ERR_JSON_BUILDER					   0x8200 /* 33280 */
#define VDM_ERR_JSON_KEY_NOT_FOUND				   0x8201 /* 33281 */

/*! error reading Tool Version from dp component */
#define VDM_ERR_DATA_SCRIPT_VAL_NOT_FOUND              0x8202 /*33282*/

/*
 *  XML Parsing errors
 */
#define VDM_ERR_XML_INVALID_SYNTAX               0x84D0 /* 34000 */

/*
 *	TRUE errors
 */

/*! SED not provisioned */
#define VDM_ERR_MISSING_ENT                      0x9001 /* 36865 */

/*! SED is locked */
#define VDM_ERR_LOCKED_ENT                       0x9002 /* 36866 */
/* @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

