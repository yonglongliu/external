/** @file wapi_interface_priv.h
 *  @brief This header file contains data structures and function declarations of wapi asue
 *
 */

void wapi_rx_wai(void *ctx, const u8 *src_addr, const u8 *buf, size_t len);
int wapi_merge_cert_files(char *wapi_as_cert, char *wapi_user_cert, char *cert_name);
int change_cert_format(const  char *cert_file, unsigned char *out_user, int len_user, unsigned char *out_asu, int len_asu);
