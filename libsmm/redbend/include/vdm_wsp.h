/*
 *******************************************************************************
 *
 * vdm_wsp.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_wsp.h
 *
 * \brief	WSP Parser Utility Structure and API
 *******************************************************************************
 */
#ifndef VDM_WSP_H_
#define VDM_WSP_H_              //!< Internal

#ifdef __cplusplus
extern "C" {
#endif

#define VDM_WSP_contentType_NIA_1_2_1 (0x44 | 0x80) //!< NIA content (DM 1.2.1)
#define VDM_WSP_contentType_NIA_1_3 (0x58 | 0x80)   //!< NIA content (DM 1.3)
#define VDM_WSP_contentType_BootDM 0xc2             //!< Boot DM content
#define VDM_WSP_contentType_BootCP 0xb6             //!< Boot CP content
#define VDM_WSP_WAP_APP_ID 0x07                     //!< WAP app id

/*!
 * Parameters extracted from the WSP header
 */
typedef struct {
	IU32 contentType;       //!< Content-type
	IS32 security;          /*!< Security type if SEC field is present, 0
	                             otherwise */
	IU8 *mac;               //!< MAC, if MAC field is present; NULL otherwise
	IU8 *msgBody;           //!< Message body
	IU32 msgBodyLength;     //!< Message body length
	IU32 applicationId;     //!< Application id
	IU8 transactionId;      //!< Transaction id
} VDM_WSP_Info_t;

/*!
 *******************************************************************************
 * Parse a WSP message.
 *
 * \param	inMessage		The message
 * \param	inMsgLength		\a inMessage length
 * \param	outInfo			Pointer to the extracted parameters, a
 *							\ref VDM_WSP_Info_t structure
 *
 * \return	VDM_ERR_OK on success, VDM_ERR_MEMORY if there is not enough memory
 *******************************************************************************
 */
VDM_Error VDM_WSP_parse(IU8 *inMessage,
	IU32 inMsgLength,
	VDM_WSP_Info_t *outInfo);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

