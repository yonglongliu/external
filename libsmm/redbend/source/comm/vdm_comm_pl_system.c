/*
 *******************************************************************************
 *
 * vdm_comm_pl_system.c
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file vdm_comm_pl_system.c
 *
 * \brief Communication PL
 *******************************************************************************
 */

#ifdef VDM_OPENSSL
	#include <openssl/ssl.h>
	#include <openssl/err.h>
	#include <openssl/x509v3.h>
#endif

#include "vdm_comm_std.h"
#include <vdm_comm_pl_types.h>
#include "vdm_comm_pl_system.h"
#include <vdm_utl_logger.h>
#include <vdm_client_pl_log.h>
#include <vdm_comm_pl_conn.h>

VDM_Error VDM_Comm_PL_System_create(void **outSysContext,
	VDM_Comm_SystemParams_t *inSysParams)
{
	(void)outSysContext;
	(void)inSysParams;

	VDM_logInfo("%s", "Performing COMM PL global initialization");

#ifdef VDM_OPENSSL
	// Global system initialization
	SSL_library_init();
	SSL_load_error_strings();
#endif

	return VDM_ERR_OK;
}

VDM_Error VDM_Comm_PL_System_destroy(void **ioSysContext)
{
	(void)ioSysContext;

#ifdef VDM_OPENSSL
	// Global system cleanup
	ERR_free_strings();
	EVP_cleanup();
	CRYPTO_cleanup_all_ex_data();

	// Valgrind reports "still reachable" for 64 bytes.
	// This can be avoided by calling sk_SSL_COMP_free(SSL_COMP_get_compression_methods())
	// But this code can cause a crash on certain situations.
	// Since a constant size of "still reachable" isn't really an error,
	// and in order to avoid a crash, we didn't add it.
#endif

	return VDM_ERR_OK;
}
