/* @file wapi_asue.c
 * @brief This file contains functions for wapi_asue
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/time.h>

#include "common.h"
#include "drivers/driver.h"
#include "wpa_supplicant_i.h"
#include "l2_packet/l2_packet.h"
#include "wapi_interface_priv.h"
#include "../../wapi_lib/wapi_interface.h"

#include <keystore/keystore_get.h>

extern struct wpa_global *global_priv;


struct wpa_supplicant * get_wapi_iface()
{
	struct wpa_supplicant *wpa_s;
	/* hardcode wlan0 as wapi enabled interface */
	for (wpa_s = global_priv->ifaces; wpa_s; wpa_s = wpa_s->next)
		if(os_strcmp(wpa_s->ifname, "wlan0")==0)
			break;
	return wpa_s;
}

unsigned char WIFI_get_rand_byte()
{
	return (unsigned char)(rand() & 0xFF);
}

void wapi_rx_wai(void *ctx, const u8 *src_addr, const u8 *buf, size_t len)
{
	wpa_printf(MSG_DEBUG, "WAPI: %s, received %d bytes packet\n", __FUNCTION__, len);
	wpa_hexdump(MSG_DEBUG, "WAPI", buf, len);
	WAI_RX_packets_indication(buf, len);
}

unsigned long WIFI_TX_packet(const char* buf, int len)
{
	struct wpa_global *global;
	struct wpa_supplicant *wpa_s;
	int ret;

	wpa_printf(MSG_DEBUG, "WAPI: %s, sending layer2 %d bytes data\n", __FUNCTION__, len);
	wpa_hexdump(MSG_DEBUG, "WAPI", buf, len);

	wpa_s = get_wapi_iface();
	ret = l2_packet_send(wpa_s->l2_wapi, wpa_s->bssid, ETH_P_WAI, buf, len);

	if (ret < 0) return 0;
	else return ret;
}

void WIFI_Action_Deauth()
{
    struct wpa_global *global;
    struct wpa_supplicant *wpa_s;

    wpa_s = get_wapi_iface();

    wpa_msg(wpa_s, MSG_INFO, "WAPI: authentication failed");
    wpa_supplicant_deauthenticate(wpa_s, 15);
}

int wapi_drv_set_key(struct wpa_supplicant *wpa_s, enum wpa_alg alg,
				   const u8 *addr, int key_idx, int set_tx,
				   const u8 *seq, size_t seq_len,
				   const u8 *key, size_t key_len);

int WIFI_unicast_key_set(const char* pKeyValue, int keylength, int key_idx)
{
	struct wpa_global *global;
	struct wpa_supplicant *wpa_s;

	int alg, keylen, rsclen;
	u8 *key_rsc;
	u8 null_rsc[16] = { 0, 0, 0, 0, 0, 0, 0, 0 };

	wpa_printf(MSG_DEBUG, "WAPI: WIFI_unicast_key_set: Installing USK to the driver.");

	wpa_s = get_wapi_iface();

	alg = WPA_ALG_SMS4;
	keylen = 32;
	rsclen = 16;

	key_rsc = null_rsc;
	if (wapi_drv_set_key(wpa_s, alg, wpa_s->bssid, key_idx, 1, key_rsc, rsclen,
			    (u8 *) pKeyValue, keylen) < 0) {
		wpa_printf(MSG_WARNING, "WAPI: WIFI_unicast_key_set: Failed to set PTK to the driver");
		return -1;
	}

	return 0;
}

int WIFI_group_key_set(const unsigned char* pKeyValue, int keylength, int key_idx, const unsigned char* keyIV)
{
	struct wpa_global *global;
	struct wpa_supplicant *wpa_s;
	int alg;
	u8 msk_len;

	wpa_printf(MSG_DEBUG, "WAPI: WIFI_group_key_set: Installing group key to the driver.");
	wpa_hexdump(MSG_DEBUG, "WAPI: WIFI_group_key_set: KEYSC", keyIV, 16);

	wpa_s = get_wapi_iface();

	alg = WPA_ALG_SMS4;
	msk_len = 32;
	if (wapi_drv_set_key(wpa_s, alg, (u8 *) "\xff\xff\xff\xff\xff\xff",  key_idx, 1, keyIV, 16,   pKeyValue, keylength) < 0) 
	{
		wpa_printf(MSG_WARNING, "WAPI:  Failed to set MSK to the driver.");
		return -1;
	}
	else {
	    wpa_printf(MSG_DEBUG, "WAPI: succeeded to set MSK to the driver.");
	    wpa_supplicant_set_state(wpa_s, WPA_COMPLETED);
	}

	return 0;
}

int wapi_drv_set_key(struct wpa_supplicant *wpa_s, enum wpa_alg alg,
				   const u8 *addr, int key_idx, int set_tx,
				   const u8 *seq, size_t seq_len,
				   const u8 *key, size_t key_len)
{
	if (wpa_s->driver->set_key) {
		return wpa_s->driver->set_key(wpa_s->ifname, wpa_s->drv_priv, alg, addr,
					      key_idx, set_tx, seq, seq_len,
					      key, key_len);
	}
	return -1;
}

static void init_sigaction(int signum, OS_timer_expired handle)
{
	signal(signum, handle);
}

void* OS_timer_setup(int deltaTimer, int repeated, OS_timer_expired pfunction, const void* pdata)
{
	struct itimerval value;
	int sec = 0, usec = 0;
	int repsec = 0, repusec = 0;

	if (deltaTimer < 0 || repeated < 0 || pfunction == NULL)
		return NULL;

	init_sigaction(SIGALRM, pfunction);

	sec  = deltaTimer/(1000);
	usec = (deltaTimer%(1000)) * 1000;

	repsec  = repeated/(1000);
	repusec = (repeated%(1000)) * 1000;

	memset(&value, 0, sizeof(value));

	value.it_interval.tv_sec   = repsec;
	value.it_interval.tv_usec = repusec;

	value.it_value.tv_sec   = sec;
	value.it_value.tv_usec = usec;

	setitimer(ITIMER_REAL, &value, NULL);

	return (void *)pfunction;
}

void OS_timer_clean(void* pTimer)
{
	struct itimerval value;

	memset(&value, 0, sizeof(value));
	setitimer(ITIMER_REAL, &value, NULL);

}

int WIFI_WAI_IE_set(const u8* pbuf, int length)
{
	struct wpa_supplicant *wpa_s;

	wpa_s = get_wapi_iface();

	memcpy(wpa_s->assoc_wapi_ie, pbuf, length);
	//Do not double add 2, the length param has added when passed
	//wpa_s->assoc_wapi_ie_len = length + 2;
	wpa_s->assoc_wapi_ie_len = length;
	return 0;
}

/* The following functions are private wapi related utils */

static const unsigned char* findmark_mem(const unsigned char* src, int lsrc, const unsigned char* mark, int lmark)
{
	const unsigned char* p = src;
	const unsigned char* pe = src+lsrc;
	if (NULL==src || NULL==mark || lsrc<0 || lmark<0 || lsrc<lmark)
	{
		return NULL;
	}
	pe -= lmark;
	for (; p<=pe; p++)
	{
		if (0 == memcmp(p, mark, lmark))
		{
			return p;
		}
	}
	return NULL;
}

static const unsigned char* findstrmark_mem(const unsigned char* src, int lsrc, const char* mark)
{
	return findmark_mem(src, lsrc, (const unsigned char*)mark, strlen(mark));
}

int change_cert_format(const  char *cert_file,
						unsigned char *out_user,
						int len_user,
						unsigned char *out_asu,
						int len_asu)
{
	int ret = -1;
	int len = 0;
	unsigned char buf[1024*8] = {0};

	const char* mark_asu_s = "-----BEGIN ASU CERTIFICATE-----";
	const char* mark_asu_e = "-----END ASU CERTIFICATE-----";
	const char* mark_user_s = "-----BEGIN USER CERTIFICATE-----";
	const char* mark_user_e = "-----END USER CERTIFICATE-----";
	const char* mark_ec_s = "-----BEGIN EC PRIVATE KEY-----";
	const char* mark_ec_e = "-----END EC PRIVATE KEY-----";
	const char* mark_s = "-----BEGIN CERTIFICATE-----";
	const char* mark_e = "-----END CERTIFICATE-----";

	if (cert_file == NULL || out_user == NULL || out_asu == NULL || len_user <= 0 || len_asu <= 0)
	{
		return ret;
	}

	{
		FILE* fp = fopen((const char*)cert_file, "rb");
		if (fp == NULL)
		{
			return ret;
		}
		len = fread(buf, 1, 1024*8, fp);
		fclose(fp);
		if (len <= 0)
		{
			return ret;
		}
	}

	{
		unsigned char *p  = NULL;
		const unsigned char *ps  = NULL;
		const unsigned char *pe  = NULL;
		ps = findstrmark_mem(buf, len, mark_asu_s);
		pe = findstrmark_mem(buf, len, mark_asu_e);
		if (NULL==ps || NULL==pe || ps>=pe)
		{
			return ret;
		}
		if ((unsigned int)len_asu < strlen(mark_s)+pe-ps-strlen(mark_asu_s)+strlen(mark_e))
		{
			return ret;
		}
		p = out_asu;
		memcpy(p, mark_s, strlen(mark_s));
		p += strlen(mark_s);
		memcpy(p, ps+strlen(mark_asu_s), pe-ps-strlen(mark_asu_s));
		p += pe-ps-strlen(mark_asu_s);
		memcpy(p, mark_e, strlen(mark_e));

		ps = findstrmark_mem(buf, len, mark_user_s);
		pe = findstrmark_mem(buf, len, mark_user_e);
		if (NULL==ps || NULL==pe || ps>=pe)
		{
			return ret;
		}
		if ((unsigned int)len_user < strlen(mark_s)+pe-ps-strlen(mark_user_s)+strlen(mark_e))
		{
			return ret;
		}
		p = out_user;
		memcpy(p, mark_s, strlen(mark_s));
		p += strlen(mark_s);
		memcpy(p, ps+strlen(mark_user_s), pe-ps-strlen(mark_user_s));
		p += pe-ps-strlen(mark_user_s);
		memcpy(p, mark_e, strlen(mark_e));
		p += strlen(mark_e);

		ps = findstrmark_mem(buf, len, mark_ec_s);
		pe = findstrmark_mem(buf, len, mark_ec_e);
		if (NULL==ps || NULL==pe || ps>=pe)
		{
			return ret;
		}
		if (len_user-strlen((char*)out_user) < pe-ps+strlen(mark_ec_e))
		{
			return ret;
		}
		memcpy(p, ps, pe-ps+strlen(mark_ec_e));
	}
	ret = 0;
	return ret;
}

int wapi_merge_cert_files(char *wapi_as_cert, char *wapi_user_cert, char *cert_name)
{
	char strBeginCert[] = "-----BEGIN CERTIFICATE-----";
	char strEndCert[] = "-----END CERTIFICATE-----";
	char strBeginASCert[] = "-----BEGIN ASU CERTIFICATE-----";
	char strEndASCert[] = "-----END ASU CERTIFICATE-----";
	char strBeginUserCert[] = "-----BEGIN USER CERTIFICATE-----";
	char strEndUserCert[] = "-----END USER CERTIFICATE-----";
	FILE *fpSrc;
	FILE *fpDesc;
	char line[512];
	int iSearchBegin = 1;
#ifdef ANDROID
	int keystore = 0, length;
	uint8_t *value = NULL;
	char *pCert, *pBegin, *pEnd;
	struct wpa_supplicant *wpa_s;
	wpa_s = get_wapi_iface();
#endif
	wpa_printf(MSG_INFO, "WAPI: %s", __FUNCTION__);
#ifdef ANDROID
	if (wapi_as_cert && strncmp("keystore://", wapi_as_cert, 11) == 0) {
		if ((length = keystore_get(&wapi_as_cert[11], strlen(wapi_as_cert)-11, &value)) <= 0) {
			wpa_printf(MSG_ERROR, "%s: Could not open %s\n", __FUNCTION__, wapi_as_cert);
			wpa_msg(wpa_s, MSG_INFO, "WAPI: certificate lost");
			return -1;
		}
		keystore = 1;
	} else
#endif
	if (wapi_as_cert && (fpSrc = fopen(wapi_as_cert, "r")) == NULL) {
		wpa_printf(MSG_ERROR, "WAPI: %s: Could not open %s\n", __FUNCTION__, wapi_as_cert);
		return -1;
	}

	if ((fpDesc = fopen(cert_name, "w")) == NULL) {
		wpa_printf(MSG_ERROR, "WAPI: %s: Could not open %s\n", __FUNCTION__, cert_name);
#ifdef ANDROID
		free(value);
		if (!keystore)
#endif
		fclose(fpSrc);
		return -1;
	}

#ifdef ANDROID
	if (keystore) {
		pCert = value;
		pBegin = strstr(pCert, strBeginCert);
		if (pBegin) {
			if (pBegin > pCert) {
				fwrite(pCert, 1, pBegin - pCert, fpDesc);
				length -= (pBegin - pCert);
				pCert = pBegin;
			}
			fwrite(strBeginASCert, 1, strlen(strBeginASCert), fpDesc);
			pCert += strlen(strBeginCert);
			length -= strlen(strBeginCert);
		} else {
			wpa_printf(MSG_ERROR, "WAPI: %s: Could not find begin in %s\n", __FUNCTION__, wapi_as_cert);
		}
		pEnd = strstr(pCert, strEndCert);
		if (pEnd) {
			if (pEnd > pCert) {
				fwrite(pCert, 1, pEnd - pCert, fpDesc);
				length -= (pEnd - pCert);
				pCert = pEnd;
			}
			fwrite(strEndASCert, 1, strlen(strEndASCert), fpDesc);
			pCert += strlen(strEndCert);
			length -= strlen(strEndCert);
		} else {
			wpa_printf(MSG_ERROR, "WAPI: %s: Could not find end in %s\n", __FUNCTION__, wapi_as_cert);
		}
		if (length > 0) {
			fwrite(pCert, 1, length, fpDesc);
		}
	} else
#endif
	/* copy the AS file */
	while ((fgets(line, sizeof(line), fpSrc)) != NULL) {
		if (iSearchBegin == 1) {
			if (strstr(line, strBeginCert) != 0){
				fputs(strBeginASCert, fpDesc);
				iSearchBegin = 0;
			}
		} else {
			if (strstr(line, strEndCert) != 0) {
				fputs(strEndASCert, fpDesc);
			} else {
				fputs(line, fpDesc);
			}
		}
	}

#ifdef ANDROID
	free(value);
	if (!keystore)
#endif
	fclose(fpSrc);

	/* open the user file */
	iSearchBegin = 1;

#ifdef ANDROID
	keystore = 0;

	if (wapi_user_cert && strncmp("keystore://", wapi_user_cert, 11) == 0) {
		if ((length = keystore_get(&wapi_user_cert[11], strlen(wapi_user_cert)-11, &value)) <= 0) {
			wpa_printf(MSG_ERROR, "WAPI: %s: Could not open %s\n", __FUNCTION__, wapi_user_cert);
			wpa_msg(wpa_s, MSG_INFO, "WAPI: certificate lost");
			fclose(fpDesc);
			return -1;
		}
		keystore = 1;
	} else
#endif
	if (wapi_user_cert && (fpSrc = fopen(wapi_user_cert, "r")) == NULL) {
		wpa_printf(MSG_ERROR, "WAPI: %s: Could not open %s\n", __FUNCTION__, wapi_user_cert);
		fclose(fpDesc);
		return -1;
	}

#ifdef ANDROID
	if (keystore) {
		pCert = value;
		pBegin = strstr(pCert, strBeginCert);
		if (pBegin) {
			if (pBegin > pCert) {
				fwrite(pCert, 1, pBegin - pCert, fpDesc);
				length -= (pBegin - pCert);
				pCert = pBegin;
			}
			fwrite(strBeginUserCert, 1, strlen(strBeginUserCert), fpDesc);
			pCert += strlen(strBeginCert);
			length -= strlen(strBeginCert);
		} else {
			wpa_printf(MSG_ERROR, "WAPI: %s: Could not find begin in %s\n", __FUNCTION__, wapi_user_cert);
		}
		pEnd = strstr(pCert, strEndCert);
		if (pEnd) {
			if (pEnd > pCert) {
				fwrite(pCert, 1, pEnd - pCert, fpDesc);
				length -= (pEnd - pCert);
				pCert = pEnd;
			}
			fwrite(strEndUserCert, 1, strlen(strEndUserCert), fpDesc);
			pCert += strlen(strEndCert);
			length -= strlen(strEndCert);
		} else {
			wpa_printf(MSG_ERROR, "WAPI: %s: Could not find end in %s\n", __FUNCTION__, wapi_user_cert);
		}
		if (length > 0) {
			fwrite(pCert, 1, length, fpDesc);
		}
	} else
#endif
	/* copy the user file */
	while ((fgets(line, sizeof(line), fpSrc)) != NULL) {
		if (iSearchBegin == 1) {
			if (strstr(line, strBeginCert) != 0){
				fputs(strBeginUserCert, fpDesc);
				iSearchBegin = 0;
			}
		} else {
			if (strstr(line, strEndCert) != 0){
				fputs(strEndUserCert, fpDesc);
			} else {
				fputs(line, fpDesc);
			}
		}
	}

	fflush(fpDesc);

#ifdef ANDROID
	free(value);
	if (!keystore)
#endif
	fclose(fpSrc);
	fclose(fpDesc);
	return 0;
}
