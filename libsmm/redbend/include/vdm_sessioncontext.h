/*
 *******************************************************************************
 *
 * vdm_sessioncontext.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_sessioncontext.h
 *
 * \brief	Session Context API
 *
 * A session context object is used as a parameter to all session triggering
 * APIs. The session context is later passed as a parameter of all session
 * state observers via the callback \ref VDM_SessionStateNotifyCB.
 *******************************************************************************
 */

#ifndef _VDM_SESSIONCONTEXT_H_
#define _VDM_SESSIONCONTEXT_H_

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *******************************************************************************
 * Create a session context object. This is a utility API that allocates a
 * session context object that is used as a parameter to all session triggering
 * APIs.
 *
 * The caller owns \a inData and is responsible to free it when the session
 * completes successfully or aborts. The allocated memory will be de-allocated
 * by OMA DM Protocol Engine after all observers have been notified that a session has
 * completed or aborted.
 *
 * \note	The session initiator can free the memory allocated for the session
 *			context when there is a session state notification, when other
 *			observers have not yet been notified. In this case, the session
 *			context must be set to NULL so that OMA DM Protocol Engine does not try to
 *			free the memory. It is recommended to use
 *			\ref VDM_destroySessionContext to destroy the session context.
 *
 * \param	inInitiatorId	A unique string that identifies the session
 *							initiator. This id may be later used for a session
 *							state notification, so that a session state
 *							observer can identify itself from other initiators.
 *							In order to avoid ambuguity in names, it is
 *							recommended that you name use
 *							{Prod}_{Comp}_{Instance} where: {Prod} is the
 *							product name, {Comp} is the component name, and
 *							{Instance} is a unique identifier of the component
 *							instance. For example, for FUMO component where the
 *							FUMO root node is "./FwUpdate/Flash", the
 *							corresponding initiator id string should be:
 *							"VDM_FUMO_./FwUpdate/Flash".
 * \param	inData			Opaque context that can be used by the session
 *							state observer.
 *
 * \return	The session context, or NULL on error
 *******************************************************************************
 */
extern VDM_SessionContext_t *VDM_createSessionContext(const char *inInitiatorId,
	void *inData);

/*!
 *******************************************************************************
 * Create a session context object. This is a utility API that allocates a
 * session context object that is used as a parameter to all session triggering
 * APIs.
 *
 * The caller owns \a inData and is responsible to free it when the session
 * completes successfully or aborts. The allocated memory will be de-allocated
 * by OMA DM Protocol Engine after all observers have been notified that a session has
 * completed or aborted.
 *
 * \note	The session initiator can free the memory allocated for the session
 *			context when there is a session state notification, when other
 *			observers have not yet been notified. In this case, the session
 *			context must be set to NULL so that OMA DM Protocol Engine does not try to
 *			free the memory. It is recommended to use
 *			\ref VDM_destroySessionContext to destroy the session context.
 *
 * \param	inInitiatorId	A unique string that identifies the session
 *							initiator. This id may be later used for a session
 *							state notification, so that a session state
 *							observer can identify itself from other initiators.
 *							In order to avoid ambiguity in names, it is
 *							recommended that you name use
 *							{Prod}_{Comp}_{Instance} where: {Prod} is the
 *							product name, {Comp} is the component name, and
 *							{Instance} is a unique identifier of the component
 *							instance. For example, for FUMO component where the
 *							FUMO root node is "./FwUpdate/Flash", the
 *							corresponding initiator id string should be:
 *							"VDM_FUMO_./FwUpdate/Flash".
 * \param	inData			Opaque context that can be used by the session
 *							state observer.
 * \param	inSessionKey	Unique identifier for session (DP NAME)
 *
 * \return	The session context, or NULL on error
 *******************************************************************************
 */
extern VDM_SessionContext_t *VDM_createSessionContextEx(const char *inInitiatorId,
	void *inData,
	const char *inSessionKey);

/*!
 *******************************************************************************
 * Destroy a session context object.
 *
 * De-allocate a session context object and set it to NULL. The function does
 * not free memory of the object's opaque data context. It is the responsibility
 * of the caller to free the memory of that member prior to calling this API.
 *
 * \param	ioSessionContext	Input: The object to destroy.
 *								Output: NULL.
 *
 * \return	None
 ******************************************************************************
 */
extern void VDM_destroySessionContext(VDM_SessionContext_t **ioSessionContext);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  //!_VDM_SESSIONCONTEXT_H_

