/*
 *******************************************************************************
 *
 * vdm_comm_pl_inet.c
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

#include <arpa/inet.h>
#include "order32.h"
#include "vdm_comm_std.h"
#include <vdm_comm_pl_inet.h>

#define BSWAP_64(x)     (((uint64_t)(x) << 56) | \
	(((uint64_t)(x) << 40) & 0xff000000000000ULL) | \
	(((uint64_t)(x) << 24) & 0xff0000000000ULL) | \
	(((uint64_t)(x) << 8)  & 0xff00000000ULL) | \
	(((uint64_t)(x) >> 8)  & 0xff000000ULL) | \
	(((uint64_t)(x) >> 24) & 0xff0000ULL) | \
	(((uint64_t)(x) >> 40) & 0xff00ULL) | \
	((uint64_t)(x)  >> 56))

IU16 VDM_Comm_PL_hton16(IU16 inHostInt)
{
	return htons(inHostInt);
}

IU32 VDM_Comm_PL_hton32(IU32 inHostInt)
{
	return htonl((uint32_t)inHostInt);
}

IU64 VDM_Comm_PL_hton64(IU64 inHostInt)
{
	IU64 netInt;

	netInt = (O32_HOST_ORDER == O32_LITTLE_ENDIAN) ?
	    BSWAP_64(inHostInt) : inHostInt;

	return netInt;
}

IU16 VDM_Comm_PL_ntoh16(IU16 inNetInt)
{
	return ntohs(inNetInt);
}

IU32 VDM_Comm_PL_ntoh32(IU32 inNetInt)
{
	return ntohl((uint32_t)inNetInt);
}

IU64 VDM_Comm_PL_ntoh64(IU64 inNetInt)
{
	IU64 hostInt;

	hostInt = (O32_HOST_ORDER == O32_LITTLE_ENDIAN) ?
	    BSWAP_64(inNetInt) : inNetInt;

	return hostInt;
}

