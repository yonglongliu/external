/*
 *******************************************************************************
 *
 * vdm_comm_pl_conn.c
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file vdm_comm_pl_conn.c
 *
 * \brief OMA DM Protocol Engine SDK
 *******************************************************************************
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <fnmatch.h>
#ifdef VDM_OPENSSL
 #include <openssl/ssl.h>
 #include <openssl/err.h>
 #include <openssl/x509v3.h>
#endif

//all this mess - for making sure htons() is defined correctly for Android
#if (defined VDM_RUN_ON_ANDROID) && (!defined __OPTIMIZE__)
	#define __OPTIMIZE__
	#define VDM_PL_ANDROID_OPTIMIZE
#endif

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#ifdef VDM_PL_ANDROID_OPTIMIZE
	#undef __OPTIMIZE__
	#undef VDM_PL_ANDROID_OPTIMIZE
#endif
//end of mess

#include "vdm_comm_std.h"
#include <vdm_comm_pl_types.h>
#include <vdm_pl_alloc.h>
#include <vdm_pl_memory.h>
#include <vdm_utl_utf8.h>
#include <vdm_utl_str.h>
#include <vdm_utl_url.h>
#include <vdm_utl_logger.h>
#include <vdm_utl_calloc.h>
#include <vdm_utl_url.h>
#include <vdm_pl_stdlib.h>
#include <vdm_client_pl_log.h>
#include <vdm_comm_pl_conn.h>
#include <vdm_config.h>

#define MAX_BUFF_SIZE               ((IU32)1024)
#define INTERNET_DEFAULT_HTTPS_PORT 443
#define INTERNET_DEFAULT_HTTP_PORT  80
#define HTTP_CONNECTION_ESTABLISHED " 200 "

#define PROXY_AUTH_HEADER "Proxy-Authorization: "
#define BASIC_STRING "Basic "

#if DEBUG_USE_NEALS
	#include "../neals/vdm_neals_defs.h"
#endif

typedef struct {
	VDM_CommObserver_t *observer;
	VDM_Comm_ConnParams_t connParams;
	IBOOL isSecure;
	int connId;
	VDM_UTL_Url_t *server;
	VDM_UTL_Url_t *proxy;
	VDM_UTL_Url_t *toConnect; // either server or proxy
#ifdef VDM_OPENSSL
	SSL_CTX *sslCtx;
	SSL *ssl;
	BIO *sbio;
#endif
} VDM_Conn_Ctx_t;

#ifdef VDM_OPENSSL
	#define VDM_OPENSSL_ROOT            "SOFTWARE\\RedBend\\vDM\\OpenSSL"
	#define CLIENT_CERT_FILE_NAME "cert.pem"
	#define MAX_CERT_PATH           128
	#define MAX_SSL_SHUTDOWN_RETRIES    5

static int check_cert(VDM_Conn_Ctx_t *inContext);
static void log_ssl_error(void);
static SSL_CTX *init_ssl_context(VDM_Conn_Ctx_t *inContext);
#endif /* VDM_OPENSSL */

static void VDM_Comm_PL_Conn_resetContext(VDM_Conn_Ctx_t *inContext)
{
	/* reset all fields of VDM_Conn_Ctx_t except observer,connParams */
	inContext->isSecure = FALSE;
	inContext->connId = 0;

	VDM_UTL_Url_free(&inContext->server);
	VDM_UTL_Url_free(&inContext->proxy);
	inContext->toConnect = NULL;

#ifdef VDM_OPENSSL
	inContext->sslCtx = NULL;
	inContext->ssl  = NULL;
	inContext->sbio  = NULL;
#endif
}

#ifdef VDM_OPENSSL
//-----------------------------------------------------
// VDM_Comm_PL_Conn_setSocketSecure
//-----------------------------------------------------
static VDM_Error VDM_Comm_PL_Conn_setSocketSecure(VDM_Conn_Ctx_t *inContext)
{
	VDM_Error result = VDM_ERR_OK;
	int sslConnectError = 0;

	// Build our SSL context
	inContext->sslCtx = init_ssl_context(inContext);

	if (!inContext->sslCtx)
	{
		VDM_logError("%s", "Could not initialize SSL context");
		result =  VDM_ERR_COMMS_FATAL;
		goto end;
	}

	inContext->ssl = SSL_new(inContext->sslCtx);
	if (!inContext->ssl)
	{
		log_ssl_error();
		result = VDM_ERR_COMMS_NON_FATAL;
		goto end;
	}
	inContext->sbio = BIO_new_socket(inContext->connId, BIO_NOCLOSE);
	SSL_set_bio(inContext->ssl, inContext->sbio, inContext->sbio);
	/* SNI support */
	SSL_set_tlsext_host_name(inContext->ssl, inContext->server->host);
	sslConnectError = SSL_connect(inContext->ssl);
	if (sslConnectError <= 0)
	{
		log_ssl_error();
		result = VDM_ERR_COMMS_NON_FATAL;
		goto end;
	}

	if (check_cert(inContext))
	{
		VDM_logError("%s", "Certificate check failed");
		result = VDM_ERR_COMMS_NON_FATAL;
		goto end;
	}
	VDM_logDebug("%s", "Certificate verified.");

end:
	return result;
}

#endif //VDM_OPENSSL

VDM_Error VDM_Comm_PL_Conn_init(void **outContext, VDM_CommObserver_t *inObserver,
	VDM_Comm_ConnParams_t *inParams)
{
	VDM_Error result;
	VDM_Conn_Ctx_t *context;

	context = VDM_UTL_calloc(sizeof(VDM_Conn_Ctx_t));
	if (!context)
	{
		return VDM_ERR_MEMORY;
	}

	context->observer = VDM_PL_malloc(sizeof(VDM_CommObserver_t));
	if (!context->observer)
	{
		result = VDM_ERR_MEMORY;
		goto end;
	}
	VDM_PL_memcpy(context->observer, inObserver, sizeof(VDM_CommObserver_t));
	VDM_PL_memcpy(&context->connParams, inParams, sizeof(VDM_Comm_ConnParams_t));
	*outContext = context;

	context->observer->notifyCommInit(context->observer->context);
	result = VDM_ERR_OK;

end:
	if (result != VDM_ERR_OK)
	{
		VDM_PL_free(context);
	}
	VDM_logDebug("VDM_Comm_PL_Conn_init returns 0x%x", result);
	return result;
}

#ifndef RB_SUPPORT_IPV4_ONLY
static VDM_Error openSock(VDM_UTL_Url_t *server, int *fd)
{
	char portStr[6];
	struct addrinfo hints;
	struct addrinfo *res = NULL, *p;
	VDM_Error result = VDM_ERR_OK;
	int rc;

	/* Obtain address(es) matching host/port */
	VDM_PL_memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = 0;

	VDM_PL_snprintf(portStr, sizeof(portStr), "%d", server->port);

	*fd = -1;//initialize to default invalid value
	rc = getaddrinfo((char *)server->host, portStr, &hints, &res);
	if (rc)
	{
		VDM_logDebug("getaddrinfo() failed(%d): %s", rc, gai_strerror(rc));
		if (EAI_NONAME == rc)
		{
		    result = VDM_ERR_COMMS_FATAL;
		}
		else
		{
	        result = VDM_ERR_COMMS_NON_FATAL;
		}

		goto end;
	}
	if (!res)
	{
		VDM_logDebug("%s", "getaddrinfo(): resolution failed");
		result = VDM_ERR_COMMS_NON_FATAL;
		goto end;
	}

	/* Open socket and connection */
	/* loop through all the results and connect to the first we can */
	for (p = res; p; p = p->ai_next)
	{
		*fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (*fd == -1)
		{
			VDM_logDebug("socket() failed (%s)", strerror(errno));
			continue;
		}

		// if we get here, we must have a socket
		break;
	}

	if (!p || *fd == -1)
	{
		result = VDM_ERR_COMMS_NON_FATAL;
		goto end;
	}

	if (connect(*fd, p->ai_addr, p->ai_addrlen) == -1)
	{
		VDM_logDebug("connect() failed (%s)", strerror(errno));
		result = VDM_ERR_COMMS_NON_FATAL;
		close(*fd);
	}

end:
	if (res)
	{
		freeaddrinfo(res);
	}

	return result;
}

#else
static VDM_Error openSock(VDM_UTL_Url_t *server, int *fd)
{
	in_addr_t ip;
	struct sockaddr_in addr;

	if ((ip = inet_addr((char *)server->host)) == INADDR_NONE)
	{
		struct hostent *hostData = gethostbyname((char *)server->host);

		if (!hostData)
		{
			VDM_logError("Failed to get IP of %s", (char *)server->host);
			return VDM_ERR_COMMS_NON_FATAL;
		}
		VDM_PL_memcpy((char *)&ip, hostData->h_addr, sizeof(ip));
	}
	VDM_logDebug(" ip = %x", ip);

	// build address
	VDM_PL_memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = ip;
	addr.sin_port = htons(server->port);

	/* create the socket */
	*fd = socket(AF_INET, SOCK_STREAM, 0);
	if (*fd == -1)
	{
		VDM_logDebug("%s", "socket() failed (%m)");
		return VDM_ERR_COMMS_NON_FATAL;
	}
	/* and finally connect */
	if (connect(*fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1)
	{
		VDM_logDebug("%s", "connect() failed");
		return VDM_ERR_COMMS_NON_FATAL;
	}

	VDM_logDebug("%s", "connect() success");
	return VDM_ERR_OK;
}
#endif

//--------------------------------
//	VDM_Comm_PL_Conn_open
//--------------------------------
VDM_Error VDM_Comm_PL_Conn_open(void *inContext, IS32 *outConnId,
        const char *inURL)
{
	VDM_Error result = VDM_ERR_OK;
	VDM_Conn_Ctx_t *context = (VDM_Conn_Ctx_t *)inContext;
	VDM_CommObserver_t *observer = context->observer;
	struct timeval tv;

	/* initialize to error value, because in case of no communication,
	 * it won't be initialized later. */
	*outConnId = -1;

	VDM_logDebug("+VDM_Comm_PL_Conn_open (url=%s, proxy=%s)", VDM_UTL_strPrintNull(inURL), VDM_UTL_strPrintNull(context->connParams.proxy));

	VDM_Comm_PL_Conn_resetContext(context);

	/* Parse server address */
	result =  VDM_UTL_Url_str2struct(inURL, &context->server);
	if (result != VDM_ERR_OK)
	{
		result = VDM_ERR_COMMS_FATAL;
		goto end;
	}
	VDM_logDebug("server name = %s port = %hu",
		VDM_UTL_strPrintNull(context->server->host), context->server->port);
	context->toConnect = context->server;
	if (context->server->proto == E_VDM_UTL_URL_PROTO_HTTPS)
	{
		context->isSecure = TRUE;
	}
	
#ifndef VDM_OPENSSL
	if (TRUE == context->isSecure)
	{
		VDM_logDebug("%s", "VDM_Comm_PL_Conn_open Cannot use HTTPS address without compiling to support open SSL (use VDM_OPENSSL define)\n");
		result = VDM_ERR_COMMS_FATAL;
		goto end;
	}
#endif

	/* Parse proxy address */
	if (context->connParams.proxy)
	{
		result = VDM_UTL_Url_str2struct((const char *)context->connParams.proxy,
			&context->proxy);
		if (result != VDM_ERR_OK)
		{
			result = VDM_ERR_COMMS_FATAL;
			goto end;
		}
		VDM_logDebug("proxy name = %s port = %hu",
			VDM_UTL_strPrintNull(context->proxy->host), context->proxy->port);

		/* Connect to the proxy and not to the destination server */
		context->toConnect = context->proxy;

		if (context->proxy->proto == E_VDM_UTL_URL_PROTO_HTTPS)
		{
			VDM_logError("authenticating proxy is not supported (%s)",
				VDM_UTL_strPrintNull(context->connParams.proxy));
			result = VDM_ERR_COMMS_FATAL;
			goto end;
		}
	}

	if (context->connParams.isSslMandatory && !context->isSecure)
	{
		VDM_logError("%s", "Error: configuration requires that HTTPS will be mandatory");
		result = VDM_ERR_COMMS_BAD_PROTOCOL;
		goto end;
	}

	result = openSock(context->toConnect, &context->connId);
	*outConnId = (IS32)context->connId;
	if (result == VDM_ERR_COMMS_FATAL)
	{
		goto end;
	}
	else if (result != VDM_ERR_OK || context->connId == -1)
	{
		goto broken;
	}

	/* setting timeout, timeout duration is 30 sec */
	tv.tv_sec = 30;
	tv.tv_usec = 0;

	if (setsockopt(context->connId, SOL_SOCKET, SO_RCVTIMEO, (void *)&tv, sizeof(tv)))
	{
		VDM_logDebug("%s", "setting socket receive timeout failed (%m)");
		goto broken;
	}

	if (setsockopt(context->connId, SOL_SOCKET, SO_SNDTIMEO, (void *)&tv, sizeof(tv)))
	{
		VDM_logDebug("%s", "setting socket send timeout failed (%m)");
		goto broken;
	}

	/* if https and proxy send "CONNECT" */
	if (context->proxy && context->server->proto == E_VDM_UTL_URL_PROTO_HTTPS)
	{
		IS32 actualSent = 0;
		IS32 actualReceived = 0;
		IU32 totalRead = 0;
		char connectStr[MAX_BUFF_SIZE] = {0};
		char recvStr[MAX_BUFF_SIZE + 1] = {0};
		IU32 addedLength;
		IU32 length;
		int recvCount = 0;

		IS32 l = VDM_PL_snprintf(connectStr,
			MAX_BUFF_SIZE,
			"CONNECT %s:%d HTTP/1.1\r\nUser-Agent: %s\r\nHost: %s:%d\r\n",
			(char *)context->server->host,
			context->server->port,
			context->connParams.userAgent,
			(char *)context->server->host,
			context->server->port);
		if (l <= 0)
		{
			goto broken;
		}
		length = (IU32)l;

		//set proxy authorization header
		if (context->connParams.proxyAuthLevel == E_VDM_Comm_HttpAuthLevel_Basic)
		{
			l = VDM_PL_snprintf((char *)&connectStr[length],
				MAX_BUFF_SIZE - length,
				PROXY_AUTH_HEADER BASIC_STRING "%s\r\n",
				context->connParams.proxyUsernamePassword);
			if (l <= 0)
			{
				goto broken;
			}
			addedLength = (IU32)l;

			length += addedLength;
		}

		l = VDM_PL_snprintf((char *)&connectStr[length],
			MAX_BUFF_SIZE - length, "\r\n");
		if (l <= 0)
		{
			goto broken;
		}

		addedLength = (IU32)l;

		length += addedLength;

		actualSent = send(context->connId, connectStr, (size_t)length, 0);
		if (length != (IU32)actualSent)
		{
			VDM_logDebug("VDM_Comm_PL_Conn_open: send failed, bytes sent %d, %s.",
				actualSent, strerror(errno));
			goto broken;
		}

		while (TRUE)
		{
			/* Currently buffer is limited to size MAX_BUFF_SIZE */
			if (totalRead >= MAX_BUFF_SIZE)
			{
				VDM_logDebug("%s", "VDM_Comm_PL_Conn_open: receive buffer too small.");
				goto broken;
			}

			actualReceived = recv(context->connId, recvStr + totalRead, sizeof(recvStr) - totalRead, 0);
			if (actualReceived <= 0)
			{
				VDM_logDebug("VDM_Comm_PL_Conn_open: error on recv try %d, recvd %d, %s.",
					recvCount, actualReceived, strerror(errno));
				goto broken;
			}

			totalRead += (IU32)actualReceived;
			VDM_logDebug("VDM_Comm_PL_Conn_open: recv try %d, received %d bytes from CONNECT request",
				recvCount, actualReceived);

			if (VDM_UTL_strCasestr(recvStr, "\r\n\r\n"))
			{
				VDM_logDebug("VDM_Comm_PL_Conn_open: HTTP response: %s", VDM_UTL_strPrintNull(recvStr));
				if (!VDM_UTL_strCasestr(recvStr, HTTP_CONNECTION_ESTABLISHED))
				{
					goto broken;
				}

				break;
			}

			/* Don't have everything yet */
			VDM_logDebug("VDM_Comm_PL_Conn_open: recv try %d, have incomplete CONNECT response:", recvCount);
		}
	}

	/* recv, context->isSecure = TRUE; , handshake, notify opened/broken return */
#ifdef VDM_OPENSSL
	if (context->isSecure)
	{
		result = VDM_Comm_PL_Conn_setSocketSecure(context);
		if (result != VDM_ERR_OK)
		{
			goto broken;
		}
	}
#endif

	VDM_logDebug("connection opened to %s:%hu",
		VDM_UTL_strPrintNull(context->server->host), context->server->port);
	result = observer->notifyCommOpen(observer->context, *outConnId);
	goto end;

broken:
	if (result == VDM_ERR_OK)
	{
		result = VDM_ERR_COMMS_NON_FATAL;
	}

	VDM_logDebug("connection NOT opened to %s:%hu",
		VDM_UTL_strPrintNull(context->toConnect->host), context->toConnect->port);
	result = observer->notifyCommBrokenEx(observer->context, *outConnId, result);
	if (result != VDM_ERR_OK)
	{
		VDM_logDebug("%s", "observer->notifyCommBrokenEx Failed");
	}

end:
	VDM_logDebug("-VDM_Comm_PL_Conn_open (connId = %d) returns 0x%x", *outConnId, result);
	return result;
}

VDM_Error VDM_Comm_PL_Conn_send(void *inContext, IS32 inConnId, IU8 *inData,
	IU32 inDataLen)
{
	VDM_Error result = VDM_ERR_OK;
	int actualSent = 0;
	VDM_Conn_Ctx_t *context = (VDM_Conn_Ctx_t *)inContext;
	VDM_CommObserver_t *observer = context->observer;

	VDM_logDebug("%s", "+VDM_Comm_PL_Conn_send");

	if (context->isSecure)
	{
#ifdef VDM_OPENSSL

#if DEBUG_USE_NEALS
		actualSent = SSL_write(context->ssl, inData,
			(int)((g_limitsize && g_limitsize < inDataLen) ? g_limitsize : inDataLen));
#else
		actualSent = SSL_write(context->ssl, inData, (int)inDataLen);
#endif

		if (SSL_ERROR_NONE != SSL_get_error(context->ssl, actualSent))
#endif
		{
			goto broken;
		}
	}
	else
	{
#if DEBUG_USE_NEALS
		actualSent = (int)send((int)inConnId, inData,
			(size_t)((g_limitsize && g_limitsize < inDataLen) ? g_limitsize : inDataLen), 0);
#else
		actualSent = (int)send((int)inConnId, inData, (size_t)inDataLen, 0);
#endif
		if (inDataLen != (IU32)actualSent)
		{
			goto broken;
		}
	}

	VDM_logDebug("%s", "send succeeded");
	result = observer->notifyTransport(observer->context, inConnId);
	goto end;

broken:
	VDM_logDebug("%s", "send attempt failed");
	result = observer->notifyCommBrokenEx(observer->context, inConnId, VDM_ERR_COMMS_NON_FATAL);

end:
	VDM_logDebug("VDM_Comm_PL_Conn_send (connId = %d) returns", inConnId);
	return result;
}

VDM_Error VDM_Comm_PL_Conn_receive(void *inContext, IS32 inConnId, IU8 *inBuf,
	IU32 inBufSize, IS32 *outDataLen)
{
	VDM_Error result = VDM_ERR_OK;
	VDM_Conn_Ctx_t *context = (VDM_Conn_Ctx_t *)inContext;
	VDM_CommObserver_t *observer = context->observer;
	IS32 sslError = 0;

	VDM_logDebug("%s", "+VDM_Comm_PL_Conn_receive");

	if (context->isSecure)
	{
#ifdef VDM_OPENSSL
		*outDataLen = (IS32)SSL_read(context->ssl, inBuf, (int)inBufSize);
		sslError = SSL_get_error(context->ssl, (int)*outDataLen);
		if (*outDataLen < 0  || (sslError != SSL_ERROR_NONE && sslError != SSL_ERROR_ZERO_RETURN))
#endif
		{
		    VDM_logDebug("VDM_Comm_PL_Conn_receive: sslError=%d, outDataLen=%d",
		            sslError, *outDataLen);
			goto broken;
		}
	}
	else
	{
		*outDataLen = (IS32)recv((int)inConnId, inBuf, (size_t)inBufSize, 0);
		if (*outDataLen < 0)
		{
			VDM_logDebug("recv error: %d %s", errno, strerror(errno));
			if (EAGAIN == errno) {
			    goto connection_error;
			}
			goto broken;
		}
	}

	if (*outDataLen == 0) //peer closed connection
	{
		VDM_logDebug("%s", "recv returned 0 bytes");
		goto broken;
	}

	VDM_logDebug("recvd %d bytes", *outDataLen);
	result = observer->notifyTransport(observer->context, inConnId);
	goto end;

broken:
	VDM_logDebug("%s", "recv attempt failed");
	result = observer->notifyCommBrokenEx(observer->context, inConnId, VDM_ERR_COMMS_NON_FATAL);
	goto end;
connection_error:
    VDM_logDebug("%s", "recv attempt failed");
    result = observer->notifyCommBrokenEx(observer->context, inConnId, VDM_ERR_COMMS_FATAL);
end:
	VDM_logDebug("VDM_Comm_PL_Conn_receive (connId = %d) returns", inConnId);
	return result;
}

void VDM_Comm_PL_Conn_close(void *inContext, IS32 inConnId)
{
	VDM_Conn_Ctx_t *context = (VDM_Conn_Ctx_t *)inContext;
	VDM_Comm_notifyCommClosedCB notifyCommClosed;
	void *notificationContext;
	VDM_CommObserver_t *observer;

	VDM_logDebug("%s", "+VDM_Comm_PL_Conn_close");
#ifdef VDM_OPENSSL
	if (context->isSecure && context->ssl)
	{
		int result = 0;
		IBOOL shutdown_not_finished = TRUE;
		int shutdownRetry = 1;

		while (shutdown_not_finished && shutdownRetry <= MAX_SSL_SHUTDOWN_RETRIES)
		{
			result = SSL_shutdown(context->ssl);

			VDM_logDebug("SSL_shutdown returned %d", result);

			switch (result)
			{
			case -1:
				/* failure */
				shutdown_not_finished = FALSE;
				break;
			case 0:
				VDM_logDebug("SSL_shutdown failed - calling shutdown again retry %d", shutdownRetry);
				shutdownRetry++;
				break;
			case 1:
				VDM_logDebug("%s", "SSL_shutdown succeeded \n");
				shutdown_not_finished = FALSE;
				break;
			}
		}
		/* Thread-local cleanup */
		ERR_remove_state(0);

		SSL_free(context->ssl);

		if (context->sslCtx)
		{
			SSL_CTX_free(context->sslCtx);
		}

		// Note: global cleanup is done in VDM_Comm_PL_System_destroy
	}
#endif
	close((int)inConnId);

	if (inContext && context->observer)
	{
		observer = context->observer;
		notifyCommClosed = observer->notifyCommClosed;
		notificationContext = observer->context;
		notifyCommClosed(notificationContext, inConnId);
	}

	VDM_logDebug("VDM_Comm_PL_Conn_close (connId = %d) returns", inConnId);
}

VDM_Error VDM_Comm_PL_Conn_term(void *inContext)
{
	VDM_Error result = VDM_ERR_OK;
	VDM_Conn_Ctx_t *connContext = (VDM_Conn_Ctx_t *)inContext;
	VDM_CommObserver_t *observer;
	VDM_Comm_notifyCommTermCB notifyCommTerm;
	void *notificationContext;

	if (!connContext)
	{
		VDM_logDebug("%s", "VDM_Comm_PL_Conn_term was called with NULL context");
		goto end;
	}

	if (connContext->observer)
	{
		observer = connContext->observer;
		notifyCommTerm = observer->notifyCommTerm;
		notificationContext = observer->context;
		VDM_PL_free(connContext->observer);
		if (notifyCommTerm)
		{
			result = notifyCommTerm(notificationContext);
		}
		else
		{
			VDM_logWarning("%s", "VDM_Comm_PL_Conn_term: notifyCommTerm is NULL");
		}
	}

	VDM_Comm_PL_Conn_resetContext(connContext);

	VDM_PL_free(connContext);

end:
	VDM_logDebug("VDM_Comm_PL_Conn_term returns 0x%x", result);
	return result;
}

#ifdef VDM_OPENSSL

STATIC int cmpSubDomain(const char *inCertStr,const char *inDomainStr)
{
	int res = 0;
	char *sD, *eD, *sC, *eC, *tmp;

	char *domainStr = VDM_UTL_strdup(inDomainStr);
	char *certStr = VDM_UTL_strdup(inCertStr);

	if(!domainStr || !certStr)
	{
		res = -1;
		goto end;
	}

	sD = domainStr;
	sC = certStr;
	eD = sD + strlen(sD) - 1;
	eC = sC + strlen(sC) - 1;

	/* Scan from beginning */
	while (*sC != '*' && *sC == *sD && *sC && *sD)
	{
		sC++;
		sD++;
	}
	if (*sC != '*')
	{
		if (*sC || *sD)
		{
			res = -1;
		}
		goto end; /* Success - no wildcards */
	}

	/* Scan backwards */
	while (*eC != '*' && *eC == *eD)
	{
		eC--;
		eD--;
	}
	if (*eC != '*')
	{
		res = -1;
		goto end;
	}

	*(eD + 1) = 0; //pay attention: changing content of domain string
	while (sC < eC)
	{
		++sC;
		if (*sC == '*')
		{
			continue;
		}
		tmp = strchr(sC, '*');
		*tmp = 0;//pay attention: changing content of cert string
		sD = strstr(sD, sC);
		if (sD > eD || !sD)
		{
			res = -1;
			goto end;
		}
		sD += tmp - sC;
		sC = tmp;
	}

end:
	VDM_PL_free(domainStr);
	VDM_PL_free(certStr);

	return res;
}

/**
 * This function supports non-standard server names when checking against the certificate.
 * It was originally added to support Daimler.
 * The idea is that there are two cases:
 * - If the certificate name does not start with '*', then both inputs must match.
 * - if the certificate name starts with '*', then everything after the '*' should
 *   match to the suffix of the domain name (this includes the '.' after the '*').
 *   The prefix of the domain name is not checked at all, as this is the non-standard part.
 */
static int cmpDomainToCertPromiscuous(char *inCertName, char *inDomainName)
{
	int result = -1;

	if (!inCertName || !inDomainName)
	{
		goto end;
	}

	VDM_logDebug("Promiscuously Comparing cert: <%s> to non-standard domain: <%s>...", inCertName, inDomainName);

	if (*inCertName == '*') /* Wildcard */
	{
		IU32 domainPartLen = 0, hostPartLen = 0;

		inCertName++;
		domainPartLen = VDM_PL_strlen(inCertName);
		hostPartLen = VDM_PL_strlen(inDomainName) - domainPartLen;
		if (hostPartLen < 1)  // At least one character in place of '*'
		{
			goto end;
		}
		inDomainName += hostPartLen;
	}
	result = (int)VDM_PL_strcmp(inCertName, inDomainName);
end:
	VDM_logDebug("  <%s> %s <%s>", inCertName, !result ? "matches" : "doesn't match", inDomainName);
	return result;
}

static int cmpDomainToCertWithWildCards(unsigned char *inCertName,
	const char *inDomainName, IBOOL isNonStandardDomain)
{
	int res = 0;
	char *certName, *domainName, *tmp1, *tmp2, *str1 = NULL, *str2 = NULL;

	if (isNonStandardDomain)
	{
		VDM_logDebug("%s", "Non-standard domain is allowed");
		res = cmpDomainToCertPromiscuous((char *)inCertName, (char *)inDomainName);
		goto end;
	}
	VDM_logDebug("%s", "Expecting standard domain name");
	certName = (char *)inCertName;
	domainName = (char *)inDomainName;

	while ((tmp1 = strchr(certName, '.')))
	{
		if (!(tmp2 = strchr(domainName, '.')))
		{
			res = -1;
			goto end;
		}
		str1 = VDM_UTL_strndup(certName, PTR_DIFF(tmp1, certName));
		str2 = VDM_UTL_strndup(domainName, PTR_DIFF(tmp2, domainName));
		VDM_logDebug("Comparing cert: '%s' to dom: '%s'", str1, str2);

		if (!str1 || !str2)
		{
			res = -1;
			goto end;
		}
		if ((res = cmpSubDomain(str1, str2)) == -1)
		{
			goto end;
		}

		++tmp1;
		if ((*tmp1 == '.') || (!*tmp1))
		{
			res = -1;
			goto end;
		}
		certName = tmp1;

		++tmp2;
		if ((*tmp2 == '.') || (!*tmp2))
		{
			res = -1;
			goto end;
		}
		domainName = tmp2;

		VDM_PL_freeAndNullify(str1);
		VDM_PL_freeAndNullify(str2);
	}

	if (strchr(domainName, '.'))
	{
		res = -1;
		goto end;
	}

	res = cmpSubDomain(certName, domainName);

end:
	VDM_PL_freeAndNullify(str1);
	VDM_PL_freeAndNullify(str2);
	return res;
}

/* Verify certificate, also check that the common name matches the host name*/
static int check_cert(VDM_Conn_Ctx_t *inContext)
{
	X509 *peer = NULL;
	long ret;
	int i, lastpos, result = 0;
	unsigned char *dns;
	GENERAL_NAMES *sANs;

	ret = SSL_get_verify_result(inContext->ssl);
	VDM_logDebug("Certificate verify return code: %ld", ret);

	switch (ret)
	{
	case X509_V_OK:
		break;
	case X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT:
	case X509_V_ERR_SELF_SIGNED_CERT_IN_CHAIN:
		VDM_logError("Self Signed Certificate doesn't verify (error %d)", ret);
		result = -1;
		break;
	default:
		VDM_logError("Certificate doesn't verify (error %d)", ret);
		result = -1;
		break;
	}

	if (result)
	{
		goto end;
	}

	VDM_logDebug("serverName is '%s'",
		VDM_UTL_strPrintNull(inContext->server->host));

	/* Check if the host name is approved by the SSL certificate */
	peer = SSL_get_peer_certificate(inContext->ssl);

	result = -1;

	/* Check in the common name entries */
	lastpos = -1;
	for (;; )
	{
		X509_NAME_ENTRY *e;

		lastpos = X509_NAME_get_index_by_NID(X509_get_subject_name(peer), NID_commonName, lastpos);
		if (lastpos == -1)
		{
			break;
		}
		e = X509_NAME_get_entry(X509_get_subject_name(peer), lastpos);
		dns = ASN1_STRING_data(X509_NAME_ENTRY_get_data(e));
		VDM_logDebug("Subject common name DNS: %s\n", dns);

		if (!cmpDomainToCertWithWildCards(dns, (char *)inContext->server->host,
			inContext->connParams.isNonStandardDomainSupported))
		{
			result = 0;
			break;
		}
	}

	if (result == -1)
	{
		/* Check in the alternative names entries */
		sANs = X509_get_ext_d2i(peer, NID_subject_alt_name, NULL, NULL);
		if (sANs)
		{
			int numAN = sk_GENERAL_NAME_num(sANs);

			VDM_logDebug("Subject alternative name entries number: %d", numAN);

			for (i = 0; i < numAN; ++i)
			{
				GENERAL_NAME *sAN = sk_GENERAL_NAME_value(sANs, i);

				// We only care about DNS entries
				if (GEN_DNS != sAN->type)
				{
					continue;
				}
				ASN1_STRING_to_UTF8(&dns, sAN->d.dNSName);
				if (!dns)
				{
					/* Memory allocation error */
					break;
				}
				VDM_logDebug("Subject alternative name DNS: %s", dns);
				if (!cmpDomainToCertWithWildCards(dns, (char *)inContext->server->host,
					inContext->connParams.isNonStandardDomainSupported))
				{
					result = 0;
					OPENSSL_free(dns);
					break;
				}
				OPENSSL_free(dns);
			}
			sk_GENERAL_NAME_pop_free(sANs, GENERAL_NAME_free);
		}
		else
		{
			VDM_logDebug("%s", "No subject alternative name extension");
		}
	}

	if (result == -1)
	{
		VDM_logError("%s", "Host name does not match peer name");
	}

end:
	X509_free(peer);
	return result;
}

static void log_ssl_error(void)
{
	char errBuffer[MAX_BUFF_SIZE];
	unsigned long errorCode;

	while ((errorCode = ERR_get_error()) != 0)
	{
		ERR_error_string_n(errorCode, errBuffer, sizeof(errBuffer));
		VDM_logError("SSL error: %lu :%s ", errorCode, errBuffer);
	}
}

static int getCertPath(char *ioPath, IU32 inSize)
{
	int ret = 0;
	char *caPath = VDM_Config_getStr("ca_cert_path");

	if (!caPath)
	{
		ret = -1;
		goto end;
	}

	inSize = (inSize > VDM_PL_strlen(caPath)) ? inSize : VDM_PL_strlen(caPath);
	VDM_PL_strncpy(ioPath, caPath, inSize);

end:
	return ret;
}

static SSL_CTX *init_ssl_context(VDM_Conn_Ctx_t *inContext)
{
	int sslResult = 0;
	int left = 0;
	int ret = 0;
	SSL_CTX *ctx = NULL;
	char caPath[MAX_CERT_PATH] = {0};
	char clientCertFilePath[MAX_CERT_PATH] = {0};

	// Note: global initialization is done in VDM_Comm_PL_System_create

	ctx = SSL_CTX_new(SSLv23_method());
	if (!ctx)
	{
		log_ssl_error();
		VDM_logError("%s", "SSL ctx_new failed");
		return NULL;
	}

	SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2);

	/* Get CA path */
	ret = getCertPath(caPath, sizeof(caPath));
	if (ret < 0)
	{
		VDM_logError("SSL_CTX_load_get CA path failed, path=%s", caPath);
		goto err;
	}
	sslResult = SSL_CTX_load_verify_locations(ctx, NULL, caPath);
	if (sslResult != 1)
	{
		log_ssl_error();
		VDM_logError("SSL_CTX_load_verify_locations failed, path=%s", caPath);
		goto err;
	}

	/* Build client certificate file full path, if required */
	if (!inContext->connParams.isClientCertMandatory)
	{
		goto end;
	}

	left = (int)sizeof(clientCertFilePath) - (int)VDM_PL_strlen(clientCertFilePath);
	ret = (int)VDM_PL_snprintf(clientCertFilePath + VDM_PL_strlen(clientCertFilePath),
		(IU32)left, "/%s", CLIENT_CERT_FILE_NAME);
	if (ret < 0)
	{
		VDM_logError("SSL_Building client file path failed, ret = %d", ret);
		goto err;
	}

	sslResult = SSL_CTX_use_certificate_chain_file(ctx, clientCertFilePath);
	if (sslResult != 1)
	{
		log_ssl_error();
		VDM_logError("%s", "SSL_CTX_use_certificate_chain_file failed.");
		goto err;
	}
	VDM_logError("%s", "Using proper client certificate chain");
	sslResult = SSL_CTX_use_PrivateKey_file(ctx, clientCertFilePath, SSL_FILETYPE_PEM);
	if (sslResult != 1)
	{
		log_ssl_error();
		VDM_logError("%s", "SSL_CTX_use_PrivateKey_file failed.");
		goto err;
	}
	VDM_logError("%s", "Using proper private key.\n");
	goto end;
	// before version 9.5 there was a bug and we must restrict the length
	// of the certificate chain
err:
	SSL_CTX_free(ctx);
	return NULL;
end:
#if (OPENSSL_VERSION_NUMBER < 0x00905100L)
	SSL_CTX_set_verify_depth(ctx, 1);
#endif
	return ctx;
}
#endif

