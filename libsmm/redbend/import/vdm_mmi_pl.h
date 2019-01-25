/*
 *******************************************************************************
 *
 * vdm_mmi_pl.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_mmi_pl.h
 *
 * \brief	MMI Component APIs
 *
 * The Man-Machine Interface (MMI) component displays informational or query
 * text screens initiated by the DM Server, as well as download progress, to the
 * end user.
 *
 * The types of MMI screens are:
 *
 * \li Information message
 * \li Confirmation query
 * \li Input query
 * \li Choice list query
 * \li Progress status
 *
 * Each screen is handled by a different API.
 *
 * The Engine calls the appropriate API to display the screen, passing the MMI
 * screen context with additional information such as the minimum length of
 * time to display the screen.
 *******************************************************************************
 */

#ifndef _VDM_MMI_PL_H_
#define _VDM_MMI_PL_H_

#ifdef __cplusplus
extern "C" {
#endif

//==============================================================================
//
//
//			Types and Definitions
//
//
//==============================================================================

/*!
 * MMI result codes, indicating whether or not an MMI message has been displayed
 * successfully
 */
typedef enum {
	E_VDM_MMI_Result_OK,                /**< MMI displayed successfully */
	E_VDM_MMI_Result_TextTooLong,       /**< Text too long to fit screen */
	E_VDM_MMI_Result_TooManyOptions,    /**< Too many options to be displayed */
	E_VDM_MMI_Result_Error              /**< General failure */
} E_VDM_MMI_Result_t;

/*!
 * MMI screen context structure, indicating the text to display and the minimum
 * and maximum time to display it
 */
typedef struct {
	const char *displayText;       /**< Text to be displayed on screen */

	/** Minimum display time for a screen, in seconds; 0 indicates no limit */
	IU32 minDisplayTime;

	/** Maximum display time for a screen in, seconds; 0 indicates no limit */
	IU32 maxDisplayTime;
} VDM_MMI_ScreenContext_t;

/*!
 * MMI information message types
 */

typedef enum {
	E_VDM_MMI_InfoType_Startup,     /**< DM Client has started */
	E_VDM_MMI_InfoType_Generic,     /**< Generic information message screen;
	                                     message text is supplied by the server */
	E_VDM_MMI_InfoType_Exiting      /**< DM Client is about to exit */
} E_VDM_MMI_InfoType_t;

/*!
 * MMI confirmation default responses
 */

typedef enum {
	E_VDM_MMI_Confirm_Undefined = -1,   /**< No default response is defined */
	E_VDM_MMI_Confirm_No,               /**< Default response is no */
	E_VDM_MMI_Confirm_Yes               /**< Default response is yes */
} E_VDM_MMI_ConfirmCmd_t;

/*!
 * MMI input query field types; see \ref VDM_MMI_InputContext_t
 */

typedef enum {
	E_VDM_MMI_InputType_Undefined       = 0,    /**< Undefined input type */
	E_VDM_MMI_InputType_Alphanumeric    = 1,    /**< All alphanumeric characters are allowed */
	E_VDM_MMI_InputType_Numeric         = 2,    /**< [0-9], [+/-], and/or decimal point are allowed */
	E_VDM_MMI_InputType_Date            = 3,    /**< A date */
	E_VDM_MMI_InputType_Time            = 4,    /**< A time */
	E_VDM_MMI_InputType_Phone           = 5,    /**< A phone number: [0-9], '+', 'p', 'w', and 's' */
	E_VDM_MMI_InputType_IPAddress       = 6     /**< An IP address: [0-9] and '.' */
} E_VDM_MMI_InputType_t;

/*!
 * MMI input echo text settings; see \ref VDM_MMI_InputContext_t
 */

typedef enum {
	E_VDM_MMI_EchoType_Undefined    = 0,    /**< Undefined echo type */
	E_VDM_MMI_EchoType_Plain    = 1,        /**< Echo the input */
	E_VDM_MMI_EchoType_Masked   = 2         /**< Masked input, such as for passwords */
} E_VDM_MMI_EchoType_t;

/*!
 * The Engine sends an input query screen context to prompt the user to enter
 * text. The Engine may specify a type of text (for example, numeric or IP
 * address) and a limit to its length. The Engine can specify to mask the input
 * for a password, so that it won't be displayed. The Engine sends the input
 * query screen context together with the MMI screen context.
 */
typedef struct {
	E_VDM_MMI_InputType_t inputType;        /**< Type of input, an \ref E_VDM_MMI_InputType_t value */
	E_VDM_MMI_EchoType_t echoType;          /**< Input echo, an \ref E_VDM_MMI_EchoType_t value */
	IU32 maxLength;                         /**< Maximum number of characters allowed
	                                             for user input; 0 indicates 'not set' */
	char *defaultValue;                   /**< Default response, or NULL */
} VDM_MMI_InputContext_t;

/*!
 * The Engine sends a choice list query screen context to prompt the user to
 * choose one or more options from a list. The Engine specifies the list items,
 * the default selection, and if the user is allowed to choose only one option
 * or several options. The Engine passes a choice list query context together
 * with the MMI screen context.
 */
typedef struct {
	const char **items;                        /**< List items */
	IU32 itemsCount;                        /**< Number of items in the list */
	IBITFLAGS defaultSelection;             /**< Each bit represents a list item, and if a
	                                             bit is set, item is selected by default */
	IBOOL isMultipleSelection;              /**< Whether or not more than one item may be selected */
} VDM_MMI_ListContext_t;

//----------------------------------
//
//	Callbacks
//
//----------------------------------

/*!
 *******************************************************************************
 * Callback invoked when an information message has been closed by the user.
 *
 * \return	None
 *******************************************************************************
 */
typedef void (*VDM_MMI_infoMsgCB)(void);

/*!
 *******************************************************************************
 * Callback invoked when the user has confirmed or canceled an action.
 *
 * \param	inContinue	TRUE if user has confirmed the action,
 *						FALSE if user has canceled it
 *
 * \return	None
 *******************************************************************************
 */
typedef void (*VDM_MMI_confirmationQueryCB)(IBOOL isContinue);

/*!
 *******************************************************************************
 * Callback invoked when the user has entered input.
 *
 * \param	inUserInput		Text entered by the user
 *
 * \return	None
 *******************************************************************************
 */
typedef void (*VDM_MMI_inputQueryCB)(const char *inUserInput);

/*!
 *******************************************************************************
 * Callback invoked when the user has made a selection on a choice list.
 *
 * \param	inUserSelection		Each bit represents an item in the list<br>
 *								If set, the user has selected the item. In a
 *								single-selection list, only one bit may be set.
 *
 * \return	None
 *******************************************************************************
 */
typedef void (*VDM_MMI_choiceListQueryCB)(IBITFLAGS inUserSelection);

/*!
 *******************************************************************************
 * Callback invoked when the user has canceled the operation.
 *
 * May be called from any MMI screen, except progress status.
 *
 * \return	None
 *******************************************************************************
 */
typedef void (*VDM_MMI_cancelEventCB)(void);

/*!
 *******************************************************************************
 * Callback invoked when a timeout event has occurred (maxDisplayTime seconds
 * have passed) without any user response.
 *
 * May be called from any MMI screen, except progess status.
 *
 * \return	None
 *******************************************************************************
 */
typedef void (*VDM_MMI_timeoutEventCB)(void);

/*!
 *******************************************************************************
 * Callback invoked if MMI is not available. Invoke as a response
 * for any request to display an MMI screen, except progress status.
 *
 * MMI may be unavailable temporarily (for example, the GUI application is
 * not up yet) or permanently (for example, the DM Client is a service running
 * in the background).
 *
 * \since 4.3.0
 *
 * \return	None
 *******************************************************************************
 */
typedef void (*VDM_MMI_unavailableCB)(void);

/*!
 *******************************************************************************
 * The MMI Observer monitors the MMI component. MMI APIs must notify the MMI
 * Observer whenever a user responds to a query. The MMI Observer then notifies
 * the Engine.
 *
 * The MMI Observer is a structure of callback pointers passed to the MMI
 * component upon initialization and made available to all MMI APIs.
 *******************************************************************************
 */
typedef struct {
	VDM_MMI_infoMsgCB notifyInfoMsgClosed;                      /**< Info dialog box was closed callback */
	VDM_MMI_confirmationQueryCB notifyConfirmationResult;       /**< Confirmation dialog callback */
	VDM_MMI_inputQueryCB notifyInputResult;                     /**< Input query dialog callback */
	VDM_MMI_choiceListQueryCB notifyChoiceListResult;           /**< Choice list dialog callback */
	VDM_MMI_cancelEventCB notifyCanceled;                       /**< Call from any dialog to notify action has been cancelled */
	VDM_MMI_timeoutEventCB notifyTimeout;                       /**< Call from any dialog to notify action has timed out */
	VDM_MMI_unavailableCB notifyMmiUnavailable;                 /**< Notify that MMI is not available \since 4.3.0 */
} VDM_MMI_Observer_t;

//==============================================================================
//
//
//			Function Prototypes
//
//
//==============================================================================

/*!
 *******************************************************************************
 * Initialize the MMI component. This API is called once by the Engine
 * during initialization of the device. This API <b>MUST NOT</b> display
 * anything to the user.
 *
 * The initialization API must store the MMI Observer structure internally,
 * and make it available to all other MMI APIs.
 *
 * \param	inObserver	The MMI Observer structure, a VDM_MMI_Observer_t value
 *
 * \return	TRUE on success, FALSE on failure
 *******************************************************************************
 */
extern IBOOL VDM_MMI_PL_init(VDM_MMI_Observer_t *inObserver);

/*!
 *******************************************************************************
 * Terminate the MMI component and free all memory allocated for the MMI. This
 * function is called once when the Engine terminates.
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_MMI_PL_term(void);

/*!
 *******************************************************************************
 * Display an information message.
 *
 * The Engine sends an information message screen context to present text to the
 * user. The Engine does not expect a response. The API can present a Close
 * button to enable the user to close the screen manually. The API receives
 * the MMI screen context and the type of message to be displayed (startup,
 * exit, or generic; in actuality, startup and exit are not used).
 *
 * \note	The implementation must call the MMI Observer after a timeout or
 *          after the user closes the screen.
 *
 * \param	inScreenContext		Context of the screen to be displayed, a
 *								\ref VDM_MMI_ScreenContext_t structure
 * \param	inInfoType			An \ref E_VDM_MMI_InfoType_t value
 *
 * \return	An \ref E_VDM_MMI_Result_t code
 *******************************************************************************
 */
extern E_VDM_MMI_Result_t VDM_MMI_PL_infoMessage(
	VDM_MMI_ScreenContext_t *inScreenContext,
	E_VDM_MMI_InfoType_t inInfoType);

/*!
 *******************************************************************************
 * Prompt user to confirm or deny a session.
 *
 * The Engine sends a confirmation query screen context to prompt the user to
 * confirm or decline an action or message. The API receives the MMI screen
 * context and the default selection (Yes or No).
 *
 * \note	The implementation must call the MMI Observer after a user
 *          response, cancellation, or timeout with a confirmation result.
 *
 * \param	inScreenContext		Context of the screen to be displayed, a
 *								\ref VDM_MMI_ScreenContext_t structure
 * \param	inDefaultCommand	The default selection, an \ref
 *								E_VDM_MMI_ConfirmCmd_t value
 *
 * \return	An \ref E_VDM_MMI_Result_t code
 *******************************************************************************
 */
extern E_VDM_MMI_Result_t VDM_MMI_PL_confirmationQuery(
	VDM_MMI_ScreenContext_t *inScreenContext,
	E_VDM_MMI_ConfirmCmd_t inDefaultCommand);

/*!
 *******************************************************************************
 * Prompt user to enter text.
 *
 * The Engine sends an input query screen context to prompt the user to enter
 * text. The API may specify a type of text (for example, numeric or IP
 * address) and a limit to its length. The API can specify to mask the
 * input for a password, so that it won't be displayed. The API sends the
 * input query screen context together with the MMI screen context.
 *
 * \note	The implementation must call the MMI Observer after a user response,
 *          cancellation, or timeout.
 *
 * \param	inScreenContext		Context of the screen to be displayed, a
 *								\ref VDM_MMI_ScreenContext_t structure
 * \param	inInputContext		A \ref VDM_MMI_InputContext_t structure
 *								containing the type, maximum length of the
 *								response, and message to be displayed
 *
 * \return	An \ref E_VDM_MMI_Result_t code
 *******************************************************************************
 */
extern E_VDM_MMI_Result_t VDM_MMI_PL_inputQuery(
	VDM_MMI_ScreenContext_t *inScreenContext,
	VDM_MMI_InputContext_t *inInputContext);

/*!
 *******************************************************************************
 * Prompt user to select one or more item from a list.
 *
 * The Engine sends a choice list query screen context to prompt the user to
 * choose one or more options from a list. The Engine specifies the list items,
 * the default, selection, and if the user is allowed to choose only one option
 * or several options. The Engine passes a choice list query context together
 * with the MMI screen context.
 *
 * \note	The implementation must call the MMI Observer after a user response,
 *          cancellation, or timeout.
 *
 * \param	inScreenContext		Context of the screen to be displayed, a
 *								\ref VDM_MMI_ScreenContext_t structure
 * \param	inListContext		A \ref VDM_MMI_ListContext_t structure
 *								containing the options, whether multiple
 *								selections are allowed, and the default
 *								selection
 *
 * \return	An \ref E_VDM_MMI_Result_t code
 *******************************************************************************
 */
extern E_VDM_MMI_Result_t VDM_MMI_PL_choiceListQuery(
	VDM_MMI_ScreenContext_t *inScreenContext,
	VDM_MMI_ListContext_t *inListContext);

/*!
 *******************************************************************************
 * Display progress information of a specified session to the user.
 * The Engine sends the current and total values of the progress.
 *
 * \param	inCurrentProgress	Current progress status
 * \param	inMaxProgress		Maximum progress value
 * \param	inSessionKey		Download Instance key (DP name)
 *
 * \return	None
 *******************************************************************************
 */
extern void VDM_MMI_PL_updateProgress(
	IU64 inCurrentProgress,
	IU64 inMaxProgress,
	const char *inSessionKey);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

