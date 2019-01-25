#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <cutils/log.h>
#include <cutils/properties.h>
#include "attok.h"
#include "send_at.h"
#include "sprd_atci.h"

#define ICC_OPERATOR_NUMBER "gsm.sim.operator.numeric"
#define MCC_LEN 3

static void convertBinToHex(char *bin_ptr, int length, char *hex_ptr)
{
	int i;
	unsigned char tmp;

	if (bin_ptr == NULL || hex_ptr == NULL) {
		return;
	}
	for (i=0; i<length; i++) {
		tmp = (unsigned char)((bin_ptr[i] & 0xf0)>>4);
		if (tmp <= 9) {
			*hex_ptr = (unsigned char)(tmp + '0');
		} else {
			*hex_ptr = (unsigned char)(tmp + 'A' - 10);
		}
		hex_ptr++;
		tmp = (unsigned char)(bin_ptr[i] & 0x0f);
		if (tmp <= 9) {
			*hex_ptr = (unsigned char)(tmp + '0');
		} else {
			*hex_ptr = (unsigned char)(tmp + 'A' - 10);
		}
		hex_ptr++;
	}
}

static int convertHexToBin(const char *hex_ptr, int length, char *bin_ptr)
{
	char *dest_ptr = bin_ptr;
	int i;
	char ch;

	if (hex_ptr == NULL || bin_ptr == NULL) {
		return -1;
	}

	for(i = 0; i < length; i += 2) {
		ch = hex_ptr[i];
		if(ch >= '0' && ch <= '9')
			*dest_ptr = (char)((ch - '0') << 4);
		else if(ch >= 'a' && ch <= 'f')
			*dest_ptr = (char)((ch - 'a' + 10) << 4);
		else if(ch >= 'A' && ch <= 'F')
			*dest_ptr = (char)((ch - 'A' + 10) << 4);
		else
			return -1;

		ch = hex_ptr[i+1];
		if(ch >= '0' && ch <= '9')
			*dest_ptr |= (char)(ch - '0');
		else if(ch >= 'a' && ch <= 'f')
			*dest_ptr |= (char)(ch - 'a' + 10);
		else if(ch >= 'A' && ch <= 'F')
			*dest_ptr |= (char)(ch - 'A' + 10);
		else
			return -1;

		dest_ptr++;
	}
	return 0;
}

static char *readline(char *cur)
{
	char *start = cur;
	char *end = NULL;

	while (*start == '\r' || *start == '\n') start++;

	end = start;

	while (*end != '\0' && *end != '\r' && *end != '\n') end++;

	start[end-start] = '\0';

	return *start == '\0' ? NULL : start;
}

int sprd_get_imsi(int slot,char *imsi,int *len)
{
	char at_cmd_send[32] = {0};
	char at_cmd_recv[64] = {0};
	char *line = NULL;
	const char *atrsp = NULL;

	memset(at_cmd_send, 0, sizeof(at_cmd_send));
	memset(at_cmd_recv, 0, sizeof(at_cmd_recv));
	sprintf(at_cmd_send, "%s","AT+CIMI");
	ALOGD("%s, at_cmd_send = %s, at_cmd_send_len = %d",__func__,at_cmd_send,strlen(at_cmd_send));

	atrsp = sendCmd(slot, at_cmd_send);
	strcpy(at_cmd_recv, atrsp);

	ALOGD("%s, at_cmd_recv = %s, at_cmd_recv_len = %d",__func__,at_cmd_recv,strlen(at_cmd_recv));
	if (at_cmd_recv[0] != '\0') {
		if (strstr(at_cmd_recv,"OK") != NULL) {
			line = readline(at_cmd_recv);
			if (line != NULL) {
				ALOGD("%s, line = %s",__func__,line);
				memcpy(imsi, line, strlen(line)+1);
				*len = strlen(line);
			} else {
				goto error;
			}
		} else {
			goto error;
		}
	} else {
		goto error;
	}

	return 0;

error:
	return -1;
}
/*
  dual sim card:
   1. no sim : gsm.sim.operator.numeric  ,
   2. sim1 : gsm.sim.operator.numeric  xxxxxx
   3. sim2 : gsm.sim.operator.numeric   ,xxxxxx
   4. sim1 and sim2: gsm.sim.operator.numeric  xxxxxx,xxxxxx
*/

int sprd_get_mnc_len(int slot)
{
	char oper_num_prop[48] = {0};
	char oper_num[100] = {0};
	int oper_num_len = 0;
/*
	snprintf(oper_num_prop, sizeof(oper_num_prop),ICC_OPERATOR_NUMBER"%d",slot);
	ALOGD("%s, oper_num_prop = %s",__func__, oper_num_prop);
	property_get(oper_num_prop, oper_num, "");
	ALOGD("%s, oper_num = %s, len = %d",__func__, oper_num,strlen(oper_num));
	if (strcmp(oper_num,"") != 0) {
		oper_num_len = strlen(oper_num);
		ALOGD("%s, oper_num_len = %d",__func__, oper_num_len);
		return oper_num_len - MCC_LEN;
	} else {
		return -1;
	}
*/
	char* pos = NULL;

	//printf(oper_num_prop, sizeof(oper_num_prop),ICC_OPERATOR_NUMBER"%d",slot);
	//OGD("%s, oper_num_prop = %s",__func__, oper_num_prop);
	property_get(ICC_OPERATOR_NUMBER, oper_num, "");
	ALOGD("%s, oper_num = %s, len = %d",__func__, oper_num,strlen(oper_num));
	if (strcmp(oper_num,"") != 0) {
		ALOGD("%s, 111 oper_num = %s, len = %d",__func__, oper_num,strlen(oper_num));
		pos = strchr(oper_num,',');
		if(pos == NULL){
			ALOGD("%s, 111 slot = %d ",__func__, slot);
			if(slot == 0){
				oper_num_len = strlen(oper_num) - MCC_LEN;
			}else{
				return -1;
			}
		}else if(strlen(oper_num) == strlen(pos) && strlen(oper_num) != 1){
			ALOGD("%s, 111 slot = %d len=%d ",__func__, slot, strlen(pos));
			if(slot == 1){
				oper_num_len =  strlen(pos) - MCC_LEN -1;
			}else{
				return -1;
			}
		}else if( strlen(oper_num) > strlen(pos)){
			ALOGD("%s, 111 slot = %d len=%d ",__func__, slot, strlen(pos));
			if(slot == 0){
				oper_num_len = strlen(oper_num) - strlen(pos) - MCC_LEN;
			}else if(slot == 1){
				oper_num_len = strlen(pos) - MCC_LEN -1;
			}else{
				return -1;
			}
		}else {
			return -1;
		}
		ALOGD("%s, oper_num_len = %d",__func__, oper_num_len);
		return oper_num_len ;
	} else {
		return -1;
	}
}

int sprd_gsm_auth(int slot,const unsigned char *rand,unsigned char *sres,unsigned char *kc)
{
	char at_cmd_send[64] = {0};
	char at_cmd_recv[128] = {0};
	char *line = NULL;
	int status;
	int err;
	char bin_kc[24]={0};
	char bin_sres[24]={0};
	char hex_rand[48]={0};
	char *rsp_kc = NULL;
	char *rsp_sres = NULL;
	const char *atrsp = NULL;

	ALOGD("%s, EAP-SIM",__func__);

	memset(at_cmd_send, 0, sizeof(at_cmd_send));
	memset(at_cmd_recv, 0, sizeof(at_cmd_recv));

	convertBinToHex((char*)rand, 16, hex_rand);

	snprintf(at_cmd_send, sizeof(at_cmd_send), "AT^MBAU=\"%s\"",hex_rand);
	ALOGD("%s, at_cmd_send = %s, at_cmd_send_len = %d",__func__,at_cmd_send,strlen(at_cmd_send));

	atrsp = sendCmd(slot, at_cmd_send);
	strcpy(at_cmd_recv, atrsp);
	ALOGD("%s, at_cmd_recv = %s, at_cmd_recv_len = %d",__func__,at_cmd_recv,strlen(at_cmd_recv));

	if (at_cmd_recv[0] != '\0') {
		if (strstr(at_cmd_recv,"OK") != NULL) {
			line = readline(at_cmd_recv);
			if (line != NULL) {
				ALOGD("%s, line = %s",__func__,line);
				err = at_tok_start(&line);
				if (err < 0) goto error;

				if(*line!='\0' && *line==':') { //the return value of sendCmd could be start with "^MBAU::"or"^MBAU:", we need to handle both of them
					err = at_tok_start(&line);
					if (err < 0) goto error;
				}

				err = at_tok_nextint(&line, &status);
				if (err < 0) goto error;

				if (status == APP_MN_SIM_MBBMS_RESPONSE_SUCCESS) {
					if (at_tok_hasmore(&line)) {
						err = at_tok_nextstr(&line, &rsp_kc);
						if (err < 0) goto error;

						err = at_tok_nextstr(&line, &rsp_sres);
						if (err < 0) goto error;

						if(convertHexToBin(rsp_kc, strlen(rsp_kc), bin_kc))
							goto error;

						if(convertHexToBin(rsp_sres, strlen(rsp_sres), bin_sres))
							goto error;

						memcpy(sres, bin_sres, strlen(rsp_sres)/2);//SRES data
						memcpy(kc, bin_kc, strlen(rsp_kc)/2);//KC data
					} else {
						goto error;
					}
				} else {
					goto error;
				}
			} else {
				goto error;
			}
		} else {
			goto error;
		}
	} else {
		goto error;
	}

	return 0;

error:
	return -1;
}

int sprd_umts_auth(int slot,const unsigned char *rand,const unsigned char *autn,unsigned char *res,int *res_len,unsigned char *ik,unsigned char *ck,unsigned char *auts)
{
	char at_cmd_send[128] = {0};
	char at_cmd_recv[256] = {0};
	char *line = NULL;
	int status;
	int err;
	char bin_ck[24]={0};
	char bin_res[24]={0};
	char bin_ik[24]={0};
	char hex_rand[48]={0};
	char hex_autn[48]={0};
	char *rsp_ck = NULL;
	char *rsp_res = NULL;
	char *rsp_ik = NULL;
	const char *atrsp = NULL;

	ALOGD("%s, EAP-AKA",__func__);

	memset(at_cmd_send, 0, sizeof(at_cmd_send));
	memset(at_cmd_recv, 0, sizeof(at_cmd_recv));

	convertBinToHex((char*)rand, 16, hex_rand);
	convertBinToHex((char*)autn, 16, hex_autn);

	snprintf(at_cmd_send, sizeof(at_cmd_send), "AT^MBAU=\"%s\",\"%s\"",hex_rand,hex_autn);
	ALOGD("%s, at_cmd_send = %s, at_cmd_send_len = %d",__func__,at_cmd_send,strlen(at_cmd_send));

	atrsp = sendCmd(slot, at_cmd_send);
	strcpy(at_cmd_recv, atrsp);
	ALOGD("%s, at_cmd_recv = %s, at_cmd_recv_len = %d",__func__,at_cmd_recv,strlen(at_cmd_recv));

	if (at_cmd_recv[0] != '\0') {
		if (strstr(at_cmd_recv,"OK") != NULL) {
			line = readline(at_cmd_recv);
			if (line != NULL) {
				ALOGD("%s, line = %s",__func__,line);
				err = at_tok_start(&line);
				if (err < 0) goto error;

				if(*line!='\0' && *line==':') { //the return value of sendAt could be start with "^MBAU::"or"^MBAU:", we need to handle both of them
					err = at_tok_start(&line);
					if (err < 0) goto error;
				}

				err = at_tok_nextint(&line, &status);
				if (err < 0) goto error;

				if (status == APP_MN_SIM_MBBMS_RESPONSE_SUCCESS) {
					if (at_tok_hasmore(&line)) {
						err = at_tok_nextstr(&line, &rsp_res);
						if (err < 0) goto error;

						err = at_tok_nextstr(&line, &rsp_ck);
						if (err < 0) goto error;

						err = at_tok_nextstr(&line, &rsp_ik);
						if (err < 0) goto error;

						if(convertHexToBin(rsp_res, strlen(rsp_res), bin_res))
							goto error;

						if(convertHexToBin(rsp_ck, strlen(rsp_ck), bin_ck))
							goto error;

						if(convertHexToBin(rsp_ik, strlen(rsp_ik), bin_ik))
							goto error;

						memcpy(res, bin_res, strlen(rsp_res)/2);//RES data
						*res_len = strlen(rsp_res)/2;//Len of RES
						memcpy(ck, bin_ck, strlen(rsp_ck)/2);//CK data
						memcpy(ik, bin_ik, strlen(rsp_ik)/2);//IK data
					} else {
						goto error;
					}
				} else {
					goto error;
				}
			} else {
				goto error;
			}
		} else {
			goto error;
		}
	} else {
		goto error;
	}

	return 0;

error:
	return -1;
}

