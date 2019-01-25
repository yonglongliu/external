/**
 * sprd_get_imsi - Read IMSI from SIM/USIM card
 * @slot: Sim card slot: 1 or 2 or 3...
 * @imsi: Buffer for IMSI
 * @len: Length of imsi buffer; set to IMSI length on success
 * Returns: 0 on success, -1 on failure
 */
int sprd_get_imsi(int slot, char *imsi, int *len);

/**
 * scard_get_mnc_len - Read length of MNC in the IMSI from SIM/USIM card
 * @slot: Sim card slot: 1 or 2 or 3...
 * Returns: length (>0) on success, -1 on failure.
 */
int sprd_get_mnc_len(int slot);

/**
 * scard_gsm_auth - Run GSM authentication command on SIM card
 * @slot: Sim card slot: 1 or 2 or 3...
 * @rand: 16-byte RAND value from HLR/AuC
 * @sres: 4-byte buffer for SRES
 * @kc: 8-byte buffer for Kc
 * Returns: 0 on success, -1 on failure
 */
int sprd_gsm_auth(int slot, const unsigned char *rand, unsigned char *sres, unsigned char *kc);

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
int sprd_umts_auth(int slot, const unsigned char *rand, const unsigned char *autn, unsigned char *res, int *res_len, unsigned char *ik, unsigned char *ck, unsigned char *auts);
