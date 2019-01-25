/*
 *******************************************************************************
 *
 * vdm_comm_pl_inet.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_comm_pl_inet.h
 *
 * \brief	API functions to convert between host and network byte order
 *******************************************************************************
 */

#ifndef VDM_COMM_PL_INET_H_     //!< Internal.
#define VDM_COMM_PL_INET_H_

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @addtogroup pl_comm	Communication
 * @ingroup pl
 * @{
 */

/*!
 *******************************************************************************
 * Convert unsigned 16-bit integer from host byte order to network byte order.
 *
 * \param	inHostInt	Integer in host byte order.
 *
 * \return	Integer in network byte order
 *******************************************************************************
 */
IU16 VDM_Comm_PL_hton16(IU16 inHostInt);

/*!
 *******************************************************************************
 * Convert unsigned 32-bit integer from host byte order to network byte order.
 *
 * \param	inHostInt	Integer in host byte order.
 *
 * \return	32-bit integer in network byte order
 *******************************************************************************
 */
IU32 VDM_Comm_PL_hton32(IU32 inHostInt);

/*!
 *******************************************************************************
 * Convert unsigned 64-bit integer from host byte order to network byte order.
 *
 * \param	inHostInt	Integer in host byte order.
 *
 * \return	Integer in network byte order
 *******************************************************************************
 */
IU64 VDM_Comm_PL_hton64(IU64 inHostInt);

/*!
 *******************************************************************************
 * Convert unsigned 16-bit integer from network byte order to host byte order.
 *
 * \param	inNetInt	Integer in network byte order.
 *
 * \return	Integer in host byte order
 *******************************************************************************
 */
IU16 VDM_Comm_PL_ntoh16(IU16 inNetInt);

/*!
 *******************************************************************************
 * Convert unsigned 32-bit integer from network byte order to host byte order.
 *
 * \param	inNetInt	Integer in network byte order.
 *
 * \return	Integer in host byte order
 *******************************************************************************
 */
IU32 VDM_Comm_PL_ntoh32(IU32 inNetInt);

/*!
 *******************************************************************************
 * Convert unsigned 64-bit integer from network byte order to host byte order.
 *
 * \param	inNetInt	Integer in network byte order.
 *
 * \return	Integer in host byte order
 *******************************************************************************
 */
IU64 VDM_Comm_PL_ntoh64(IU64 inNetInt);

/*! @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // VDM_COMM_PL_INET_H_
