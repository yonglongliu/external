#ifndef __EAP_SIM_AKA_H__
#define __EAP_SIM_AKA_H__

typedef enum {
	APP_MN_SIM_MBBMS_RESPONSE_SUCCESS				= 0x00,
	APP_MN_SIM_MBBMS_RESPONSE_CONTEXT_NOT_SUPPORT	= 0x01,
	APP_MN_SIM_MBBMS_RESPONSE_MAC_FAILURE			= 0x02,
	APP_MN_SIM_MBBMS_RESPONSE_SYNC_FAILURE			= 0x03,
	APP_MN_SIM_MBBMS_RESPONSE_OTHER_FAILURE			= 0x04,
} APP_MN_SIM_MBBMS_RESPONSE_TYPE_E;

int sprd_get_imsi(int slot,char *imsi,int *len);
int sprd_get_mnc_len(int slot);
int sprd_gsm_auth(int slot,const unsigned char *rand,unsigned char *sres,unsigned char *kc);
int sprd_umts_auth(int slot,const unsigned char *rand,const unsigned char *autn,unsigned char *res,int *res_len,unsigned char *ik,unsigned char *ck,unsigned char *auts);

#endif
