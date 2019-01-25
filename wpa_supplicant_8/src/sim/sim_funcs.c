#include "includes.h"
#include "common.h"
#include "send_at.h"

int scard_get_imsi_dummy(int slot, char *imsi, int *len)
{
	sprintf(imsi, "460001884124022");
	*len=15;
	return 0;
}

int scard_get_mnc_len_dummy(int slot)
{
	return 2;
}

int scard_gsm_auth_dummy(int slot, const unsigned char *rand, unsigned char *sres, unsigned char *kc)
{
	os_memset(sres, 1, 4);
	os_memset(kc, 2, 8);
	return 0;
}

int scard_umts_auth_dummy(int slot, const unsigned char *rand, const unsigned char *autn, unsigned char *res, int *res_len, unsigned char *ik, unsigned char *ck, unsigned char *auts)
{
	*res_len = 16;
	os_memset(res, 1, *res_len);
	os_memset(ik, 2, 16);
	os_memset(ck, 3, 16);
	os_memset(auts, 4, 14);
	return 0;
}

/**
 * scard_get_imsi - Read IMSI from SIM/USIM card
 * @slot: Sim card slot: 1 or 2 or 3...
 * @imsi: Buffer for IMSI
 * @len: Length of imsi buffer; set to IMSI length on success
 * Returns: 0 on success, -1 on failure
 */
int scard_get_imsi(int slot, char *imsi, int *len)
{
	int ret = -1;
	
	//ret = scard_get_imsi_dummy(slot, imsi, len);
	ret = sprd_get_imsi(slot, imsi, len);
	
	wpa_printf(MSG_DEBUG, "EAP-SIM: scard_get_imsi: imsi from sim slot%d is %s", slot, imsi);
	wpa_printf(MSG_DEBUG, "EAP-SIM: scard_get_imsi: imsi len from sim slot%d is %d", slot, *len);
	return ret;
}

/**
 * scard_get_mnc_len - Read length of MNC in the IMSI from SIM/USIM card
 * @slot: Sim card slot: 1 or 2 or 3...
 * Returns: length (>0) on success, -1 on failure.
 */
int scard_get_mnc_len(int slot)
{
	int ret = -1;
	
	//ret = scard_get_mnc_len_dummy(slot);
	ret = sprd_get_mnc_len(slot);
	
	wpa_printf(MSG_DEBUG, "EAP-SIM: scard_get_mnc_len: mnc length from sim slot%d is %d", slot, ret);
	//return 2;
	return ret;
}

/**
 * scard_gsm_auth - Run GSM authentication command on SIM card
 * @slot: Sim card slot: 1 or 2 or 3...
 * @rand: 16-byte RAND value from HLR/AuC
 * @sres: 4-byte buffer for SRES
 * @kc: 8-byte buffer for Kc
 * Returns: 0 on success, -1 on failure
 */
int scard_gsm_auth(int slot, const unsigned char *rand, unsigned char *sres, unsigned char *kc)
{
	int ret = -1;

	//ret = scard_gsm_auth_dummy(slot, rand, sres, kc);
	ret = sprd_gsm_auth(slot, rand, sres, kc);

	wpa_hexdump(MSG_DEBUG, "EAP-SIM: scard_gsm_auth: rand is", rand, 16);
	wpa_hexdump(MSG_DEBUG, "EAP-SIM: scard_gsm_auth: sres is", sres, 4);
	wpa_hexdump(MSG_DEBUG, "EAP-SIM: scard_gsm_auth: kc is", kc, 8);
	wpa_printf(MSG_DEBUG, "EAP-SIM: scard_gsm_auth: ret is %d", ret);
	return ret;
}

/**
 * scard_umts_auth - Run UMTS authentication command on USIM card
 * @slot: Sim card slot: 1 or 2 or 3...
 * @rand: 16-byte RAND value from HLR/AuC
 * @autn: 16-byte AUTN value from HLR/AuC
 * @res: 16-byte buffer for RES
 * @res_len: Variable that will be set to RES length
 * @ik: 16-byte buffer for IK
 * @ck: 16-byte buffer for CK
 * @auts: 14-byte buffer for AUTS
 * Returns: 0 on success, -1 on failure
 */
int scard_umts_auth(int slot, const unsigned char *rand, const unsigned char *autn, unsigned char *res, int *res_len, unsigned char *ik, unsigned char *ck, unsigned char *auts)
{
	int ret = -1;

	//ret = scard_umts_auth_dummy(slot, rand, autn, res, res_len, ik, ck, auts);
	ret = sprd_umts_auth(slot, rand, autn, res, res_len, ik, ck, auts);

	wpa_hexdump(MSG_DEBUG, "EAP-SIM: scard_gsm_auth: rand is", rand, 16);
	wpa_hexdump(MSG_DEBUG, "EAP-SIM: scard_gsm_auth: autn is", autn, 16);
	wpa_hexdump(MSG_DEBUG, "EAP-SIM: scard_gsm_auth: res is", res, *res_len);
	wpa_hexdump(MSG_DEBUG, "EAP-SIM: scard_gsm_auth: ik is", ik, 16);
	wpa_hexdump(MSG_DEBUG, "EAP-SIM: scard_gsm_auth: ck is", ck, 16);
	wpa_hexdump(MSG_DEBUG, "EAP-SIM: scard_gsm_auth: auts is", auts, 16);
	return ret;
}
