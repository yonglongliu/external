/*
 *******************************************************************************
 *
 * vdm_dl_extension.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_dl_extension.h
 *
 * \brief	Alternative Download APIs
 *******************************************************************************
 */
#ifndef _VDM_DL_EXTENSION_H_
#define _VDM_DL_EXTENSION_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 *******************************************************************************
 * Start download using an Alternative Download method.
 *
 * \param	inPkgURL	URL from which to download package
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_DL_Ext_startCB_t)(const char *inPkgURL);

/*!
 *******************************************************************************
 * Notification invoked by the Engine when an Alternative Download is first
 * opened, but before any data is downloaded.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_DL_Ext_onOpenedCB_t)(void);

/*!
 *******************************************************************************
 * Notification invoked by the Engine after data is received from an
 * Alternative Download.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_DL_Ext_onReceivedCB_t)(void);

/*!
 *******************************************************************************
 * Notification invoked by the Engine if communication is broken during an
 * Alternative Download.
 *
 * \param	inReason	Error code indicating the communication problem
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_DL_Ext_onBrokenCB_t)(VDM_Error inReason);

/*!
 *******************************************************************************
 * Notification invoked by the Engine after the user cancels an Alternative
 * Download.  If \a inUserInitiated is TRUE, implementation should cancel the
 * session. If FALSE, the session should be aborted.
 *
 * \param	inUserInitiated		TRUE if the user cancelled the download,
 *								FALSE otherwise
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef void (*VDM_DL_Ext_onAbortCB_t)(IBOOL inUserInitiated);

/*!
 *******************************************************************************
 * Notification invoked by the Engine after a user confirms proceding with an
 * Alternative Download.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
typedef VDM_Error (*VDM_DL_Ext_onContinueCB_t)(void);

/*!
 *******************************************************************************
 * Terminate Alternative Download session.
 *
 * \return	None
 *******************************************************************************
 */
typedef void (*VDM_DL_Ext_termCB_t)(void);

/*!
 * Alternative Download callbacks
 */
typedef struct {
	VDM_DL_Ext_startCB_t start;             //!< Start download
	VDM_DL_Ext_onOpenedCB_t onOpened;       //!< Communication opened notification
	VDM_DL_Ext_onReceivedCB_t onReceived;   //!< Communication received notification
	VDM_DL_Ext_onBrokenCB_t onBroken;       //!< Communication broken notification
	VDM_DL_Ext_onAbortCB_t onAbort;         //!< Download aborted/cancelled notification
	VDM_DL_Ext_onContinueCB_t onContinue;   //!< Download confirmed notification
	VDM_DL_Ext_termCB_t term;               //!< Terminate download
} VDM_DL_Ext_t;

/*!
 *******************************************************************************
 * Create table of Alternative Download callbacks. Overwrites any previous
 * table.
 *
 * \param	inExt		A \ref VDM_DL_Ext_t structure containing Alternative
 *						Download callbacks
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_setDLExtension(VDM_DL_Ext_t *inExt);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

