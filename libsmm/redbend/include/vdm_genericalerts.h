/*
 *******************************************************************************
 *
 * vdm_genericalerts.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_genericalerts.h
 *
 * \brief	Generic Alerts object API
 *
 * Multiple Generic Alerts are returned via \ref VDM_CreateGenericAlertsCB.
 * This callback is invoked after \ref VDM_triggerMultipleGenericAlertsSession
 * is called.
 *******************************************************************************
 */

#ifndef _VDM_GENERICALERTS_H_
#define _VDM_GENERICALERTS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *******************************************************************************
 * Create a Generic Alerts list.
 *
 * \param	inCorrelator		Correlator previously sent by server.
 *
 * \return	Generic Alerts list (a \ref VDM_GenAlertList_Node_t item) on
 *			success, NULL otherwise
 *******************************************************************************
 */
VDM_GenAlertList_Node_t *VDM_GenericAlerts_create(const char *inCorrelator);

/*!
 *******************************************************************************
 * Add a generic alert to a Generic Alerts list.
 *
 * \param	inGenericAlerts		Generic Alerts list, a
 *								\ref VDM_GenAlertList_Node_t item
 * \param	inItemStrings		The generic alert to add, a
 *								\ref VDM_GenAlertItem_t item.
 *
 * \return	VDM_ERR_OK on success, or a \ref VDM_ERR_defs error code
 *******************************************************************************
 */
VDM_Error VDM_GenericAlerts_addItem(
	VDM_GenAlertList_Node_t *inGenericAlerts,
	VDM_GenAlertItem_t *inItemStrings);

/*!
 *******************************************************************************
 * Destroy a Generic Alerts list.
 *
 * \param	inGenericAlerts		Generic Alerts list, a
 *								\ref VDM_GenAlertList_Node_t item
 *
 * \return	None
 *******************************************************************************
 */
void VDM_GenericAlerts_destroy(VDM_GenAlertList_Node_t *inGenericAlerts);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

