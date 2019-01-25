/*
 *******************************************************************************
 *
 * vdm_scomo_types.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_scomo_types.h
 *
 * \brief	SCOMO Constants
 *******************************************************************************
 */
#ifndef _VDM_SCOMO_TYPES_H_
#define _VDM_SCOMO_TYPES_H_         //!< Internal

#ifdef __cplusplus
extern "C" {
#endif

#define COMPONENTS_SEPARATOR 	{0x1F, 0}

/*!
 * SCOMO download status (Download/\<X\>/Status)
 */
typedef enum {
	/** Invalid status */
	E_VDM_SCOMO_DOWNLOAD_STATUS_invalid                     = 0,

	/** There is no data available and download is about to start */
	E_VDM_SCOMO_DOWNLOAD_STATUS_idle                        = 10,

	/** Download failed and no data was received */
	E_VDM_SCOMO_DOWNLOAD_STATUS_download_failed             = 20,

	/** Download has started; 0 or more bytes of data have been downloaded */
	E_VDM_SCOMO_DOWNLOAD_STATUS_download_progressing        = 30,

	/** Have data after download has been completed successfully */
	E_VDM_SCOMO_DOWNLOAD_STATUS_download_complete           = 40,

	/** Installation has started */
	E_VDM_SCOMO_DOWNLOAD_STATUS_install_progressing         = 50,

	/** Installation failed and the downloaded package is still in the device */
	E_VDM_SCOMO_DOWNLOAD_STATUS_install_failed_with_data    = 60,

	/** Installation failed and the downloaded package is deleted */
	E_VDM_SCOMO_DOWNLOAD_STATUS_install_failed_without_data = 70
} E_VDM_SCOMO_DOWNLOAD_STATUS_t;

/*!
 * Delivery Package (DP) status (Inventory/Delivered/\<X\>/Status)
 */
typedef enum {
	/** Invalid status */
	E_VDM_SCOMO_DELIVERED_STATUS_invalid                        = 0,

	/** The device hasn't started to remove or install */
	E_VDM_SCOMO_DELIVERED_STATUS_idle                           = 10,

	/** Remove failed and DP is still in the device */
	E_VDM_SCOMO_DELIVERED_STATUS_remove_failed                  = 20,

	/** Remove has started */
	E_VDM_SCOMO_DELIVERED_STATUS_remove_progressing             = 30,

	/** Installation has started */
	E_VDM_SCOMO_DELIVERED_STATUS_install_progressing            = 40,

	/** Installation failed and the downloaded package is still in the device */
	E_VDM_SCOMO_DELIVERED_STATUS_install_failed_with_data       = 50,

	/** Installation failed and the downloaded package has been deleted */
	E_VDM_SCOMO_DELIVERED_STATUS_install_failed_without_data    = 60
} E_VDM_SCOMO_DELIVERED_STATUS_t;

/*!
 * Delivery Package (DP) state (Inventory/Delivered/\<X\>/State)
 */
typedef enum {
	/** Invalid status */
	E_VDM_SCOMO_DELIVERED_STATE_invalid                     = 0,

	/** DP is delivered */
	E_VDM_SCOMO_DELIVERED_STATE_delivered                       = 10,

	/** DP is installed */
	E_VDM_SCOMO_DELIVERED_STATE_installed                       = 20
} E_VDM_SCOMO_DELIVERED_STATE_t;

/*!
 * Deployment Component (DC) status (Inventory/Deployed/\<X\>/Status)
 */
typedef enum {
	/** Invalid status */
	E_VDM_SCOMO_DEPLOYED_STATUS_invalid                     = 0,

	/** The device hasn't started to remove */
	E_VDM_SCOMO_DEPLOYED_STATUS_idle                        = 10,

	/** Remove failed and DC is still in the device */
	E_VDM_SCOMO_DEPLOYED_STATUS_remove_failed               = 20,

	/** Remove started */
	E_VDM_SCOMO_DEPLOYED_STATUS_remove_progressing          = 30,

	/** Activate failed DC is still inactive */
	E_VDM_SCOMO_DEPLOYED_STATUS_activate_failed             = 40,

	/** Activate operation started */
	E_VDM_SCOMO_DEPLOYED_STATUS_activate_progressing        = 50,

	/** Deactivate failed DC is still active */
	E_VDM_SCOMO_DEPLOYED_STATUS_deactivate_failed           = 60,

	/** Deactivate operation started */
	E_VDM_SCOMO_DEPLOYED_STATUS_deactivate_progressing      = 70
} E_VDM_SCOMO_DEPLOYED_STATUS_t;

/*!
 * SCOMO result codes
 *
 * Result codes sent in Alert 1226:
 *
 * 1250-1299:	Successful operation with vendor specified result code.
 * 1450-1499:	Client Error encountered for operation with vendor-specified
 *				result code.
 * 1550-1599:	Alternate Download Server Error encountered for operation with
 *				vendor specified result code.
 */
typedef enum {
	/** Success */
	E_VDM_SCOMO_RESULT_successful                           = 1200,

	/** Success & post update status success */
	E_VDM_SCOMO_RESULT_install_successful_postUpdateStatus_successful = 1251,

	/** Client error based on user or device behavior */
	E_VDM_SCOMO_RESULT_client_error                         = 1400,

	/** User chose not to accept the operation when prompted */
	E_VDM_SCOMO_RESULT_download_cancelled                   = 1401,

	/** Software component download failed */
	E_VDM_SCOMO_RESULT_download_failed                      = 1402,

	/** Authentication required but authentication failure occurred when
	 * downloading */
	E_VDM_SCOMO_RESULT_dl_authentication_failure            = 1403,

	/** Download failed due to insufficient memory to save the DP */
	E_VDM_SCOMO_RESULT_dl_failed_device_out_of_memory       = 1404,

	/** Installation failed */
	E_VDM_SCOMO_RESULT_install_failed                       = 1405,

	/** Install failed due to insufficient memory to install the component */
	E_VDM_SCOMO_RESULT_install_failed_device_out_of_memory  = 1406,

	/** Failed to positively validate digital signature of the DP */
	E_VDM_SCOMO_RESULT_failed_package_validation            = 1407,

	/** Remove operation failed */
	E_VDM_SCOMO_RESULT_remove_failed                        = 1408,

	/** Activate operation failed */
	E_VDM_SCOMO_RESULT_activate_failed                      = 1409,

	/** Deactivate operation failed */
	E_VDM_SCOMO_RESULT_deactivate_failed                    = 1410,

	/** Device does not support the requested operation */
	E_VDM_SCOMO_RESULT_not_implemented                      = 1411,

	/** Failure not defined by any other error code */
	E_VDM_SCOMO_RESULT_undefined_error                      = 1412,

	/** Device does not support the target environment type */
	E_VDM_SCOMO_RESULT_unsupported_env                      = 1413,

	/** Alternate Download server error encountered */
	/** Client Error encountered for Operation with
	        Vendor Specified Result Code */
	E_VDM_SCOMO_RESULT_specific_client_error_range_start                = 1450,
	E_VDM_SCOMO_RESULT_specific_client_user_timeout_reached =
	        E_VDM_SCOMO_RESULT_specific_client_error_range_start,

	E_VDM_SCOMO_RESULT_swm_component_not_attempted                      = 1451,

	E_VDM_SCOMO_RESULT_swm_partially_successful                         = 1452,

	E_VDM_SCOMO_RESULT_specific_client_error_installation_timeout       = 1453,

	E_VDM_SCOMO_RESULT_purge_invalid_dp                                 = 1454,

	/** Device ID mismatch or software version mismatch */
	E_VDM_SCOMO_RESULT_update_mismatch                                  = 1455,

	/** Timestamp validation failure */
	E_VDM_SCOMO_RESULT_update_expired                                   = 1456,

	/** Update file cannot be read from the USB */
	E_VDM_SCOMO_RESULT_update_inaccessible                              = 1457,

	/** Update format is invalid */
	E_VDM_SCOMO_RESULT_invalid_update_format                            = 1458,

	/** PreInstall phase failed due to condition file */
	E_VDM_SCOMO_RESULT_condition_validation_failed_pre_install_phase    = 1459,

	/** Install phase failed due to condition file */
	E_VDM_SCOMO_RESULT_condition_validation_failed_install_phase        = 1460,

	/** PostInstall phase failed due to condition file */
	E_VDM_SCOMO_RESULT_condition_validation_failed_post_install_phase   = 1461,

	/** DL phase failed due to condition file */
	E_VDM_SCOMO_RESULT_condition_validation_failed_download_phase       = 1462,

	/** Extract file from USB timeout	 */
	E_VDM_SCOMO_RESULT_usb_extract_timedout                             = 1464,

	/** VIN response from DIL timeout	 */
	E_VDM_SCOMO_RESULT_usb_vin_response_timedout                        = 1465,

	/** PreInstall phase failed due to missing update file */
	E_VDM_SCOMO_RESULT_missing_update_file_pre_install_phase            = 1467,

	/** Failed to positively validate certificate of the DP */
	E_VDM_SCOMO_RESULT_failed_package_certificate_validation            = 1470,

	/** Failed to positively validate certificate date */
	E_VDM_SCOMO_RESULT_failed_package_certificate_expired               = 1471,

	/** Installation and rollback success */
	E_VDM_SCOMO_RESULT_install_successful_rollback_successful           = 1472,

	/** Installation failed and rollback success */
	E_VDM_SCOMO_RESULT_install_failed_rollback_successful               = 1473,

	/** Installation success and rollback failed */
	E_VDM_SCOMO_RESULT_install_successful_rollback_failed               = 1474,

	/** Installation and rollback failed */
	E_VDM_SCOMO_RESULT_install_failed_rollback_failed                   = 1475,

	/** Installation and rollback failed */
	E_VDM_SCOMO_RESULT_install_successful_postUpdateStatus_failed_rollback_successful = 1476,

	/** Installation and rollback failed */
	E_VDM_SCOMO_RESULT_install_successful_postUpdateStatus_failed_rollback_failed     = 1477,

	/** Installation success, post update status failed, rollback failed-source file wasn't found on the hw*/
	E_VDM_SCOMO_RESULT_install_successful_postUpdateStatus_failed_rollback_file_not_found       = 1478,

	/** Installation and rollback failed-source file wasn't found on the hw*/
	E_VDM_SCOMO_RESULT_install_failed_rollback_file_not_found           = 1479,

	/** Installation success, rollback failed-source file wasn't found on the hw*/
	E_VDM_SCOMO_RESULT_install_successful_rollback_file_not_found       = 1480,

	E_VDM_SCOMO_RESULT_enough_disk_space_only_for_dd                    = 1481,

	E_VDM_SCOMO_RESULT_scout_failed                                     = 1482,

	E_VDM_SCOMO_RESULT_specific_client_error_range_end                  = 1499,

	E_VDM_SCOMO_RESULT_dl_server_error                      = 1500,

	/** Alternate Download server is unavailable or does not respond */
	E_VDM_SCOMO_RESULT_dl_server_unavailable                = 1501,

	/** The download failed due to DP URL expiration */
	E_VDM_SCOMO_RESULT_error_DP_URL_expired                 = 1551,

	E_VDM_SCOMO_RESULT_vndspecific_successful_range_start       = 1250, /**< */
	E_VDM_SCOMO_RESULT_vndspecific_successful_range_end         = 1299, /**< */
	E_VDM_SCOMO_RESULT_vndspecific_client_error_range_start     = 1450, /**< */
	E_VDM_SCOMO_RESULT_vndspecific_client_error_range_end       = 1499, /**< */
	E_VDM_SCOMO_RESULT_vndspecific_dl_server_error_range_start  = 1550, /**< */
	E_VDM_SCOMO_RESULT_vndspecific_dl_server_error_range_end    = 1599  /**< */
} E_VDM_SCOMO_RESULT_t;

/*!
 * Deployment Component (DC) state
 */
typedef enum {
	/** Invalid state */
	E_VDM_SCOMO_COMPONENT_STATE_invalid         = 0,

	/** DC is inactive */
	E_VDM_SCOMO_COMPONENT_STATE_Inactive        = 10,

	/** DC is active */
	E_VDM_SCOMO_COMPONENT_STATE_Active          = 20
} E_VDM_SCOMO_COMPONENT_STATE_t;

/*!
 * Operation status
 */
typedef enum {
	E_VDM_SCOMO_Operation_Status_done               = 0,    /**< Operation complete */
	E_VDM_SCOMO_Operation_Status_startPostponed     = 1,    /**< Operation postponed */
	E_VDM_SCOMO_Operation_Status_started            = 2     /**< Operation started */
} E_VDM_SCOMO_Operation_Status_t;

/*!
 * DC Operation status
 */
typedef enum {
	/** DC removal complete */
	E_VDM_SCOMO_DC_Operation_Status_Remove_done                 = 0,
	/** DC removal  postponed */
	E_VDM_SCOMO_DC_Operation_Status_Remove_startPostponed       = 1,
	/** DC removal started */
	E_VDM_SCOMO_DC_Operation_Status_Remove_started              = 2,
	/** DC activation complete */
	E_VDM_SCOMO_DC_Operation_Status_Activation_done             = 3,
	/** DC activation postponed */
	E_VDM_SCOMO_DC_Operation_Status_Activation_startPostponed   = 4,
	/** DC activation started */
	E_VDM_SCOMO_DC_Operation_Status_Activation_started          = 5,
	/** DC deactivation complete */
	E_VDM_SCOMO_DC_Operation_Status_Deactivation_done           = 6,
	/** DC deactivation postponed */
	E_VDM_SCOMO_DC_Operation_Status_Deactivation_startPostponed = 7,
	/** DC deactivation started */
	E_VDM_SCOMO_DC_Operation_Status_Deactivation_started        = 8
} E_VDM_SCOMO_DC_Operation_Status_t;

/*! \defgroup VDM_SCOMO_Action_defs SCOMO actions
 * @{
 */
#define VDM_SCOMO_Action_None                               0x0000  //!< None
#define VDM_SCOMO_DP_Action_ExecDownload                    0x0001  //!< Download DP
#define VDM_SCOMO_DP_Action_ExecDownloadInstall             0x0002  //!< Download and install DP
#define VDM_SCOMO_DP_Action_ExecDownloadInstallInactive     0x0004  //!< Download and install inactive DP
#define VDM_SCOMO_DP_Action_ExecInstall                     0x0008  //!< Install DP
#define VDM_SCOMO_DP_Action_ExecInstallInactive             0x0010  //!< Install inactive DP
#define VDM_SCOMO_DP_Action_ExecRemove                      0x0020  //!< Remove DP
#define VDM_SCOMO_DP_Action_ReplaceData                     0x0040  //!< Replace data DP
#define VDM_SCOMO_DC_Action_ExecActivate                    0x0080  //!< Activate DC
#define VDM_SCOMO_DC_Action_ExecDeactivate                  0x0100  //!< Deactivate DC
#define VDM_SCOMO_DC_Action_ExecRemove                      0x0200  //!< Remove DC
/* @} */

/// Initiator type of a client-initiated SCOMO session
typedef enum {
	E_VDM_SCOMO_Client_user,        //!< SCOMO session initiated by user
	E_VDM_SCOMO_Client_device       //!< SCOMO session initiated by device
} E_VDM_SCOMO_Client_t;

#ifdef __cplusplus
} /* C */
#endif

#endif

