/*
 * Driver interaction with extended Linux CFG8021
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Alternatively, this software may be distributed under the terms of BSD
 * license.
 *
 */

#include <net/if.h>

#include "includes.h"
#include "common.h"
#include "linux_ioctl.h"
#include "driver_nl80211.h"
#include "wpa_supplicant_i.h"
#include "android_drv.h"
#include "driver_i.h"

typedef struct android_wifi_priv_cmd {
       char *buf;                //pointer to struct driver_cmd_msg
       int used_len;             //length of driver_cmd_msg including data
       int total_len;
} android_wifi_priv_cmd;

struct driver_cmd_msg
{
	uint16_t  msg_type;    //CMD_SUBTYPE_XX
	uint16_t msg_len;      //msg_data length
	char msg_data[];
};

#define CMD_SUBTYPE_MAX_NUM_STA (4)
#define CMD_SUBTYPE_MIRACAST_MODE (5)

static int drv_errors = 0;

#define SPRDWL_WNM_BTM (1 << 0)
#define SPRDWL_WNM_PARP (1 << 1)
#define SPRDWL_WNM_MIPM (1 << 2)
#define SPRDWL_WNM_DMS (1 << 3)
#define SPRDWL_WNM_SLEEP (1 << 4)
#define SPRDWL_WNM_TFS (1 << 5)

static void wpa_driver_send_hang_msg(struct wpa_driver_nl80211_data *drv)
{
       drv_errors++;
       if (drv_errors > DRV_NUMBER_SEQUENTIAL_ERRORS) {
               drv_errors = 0;
               wpa_msg(drv->ctx, MSG_INFO, WPA_EVENT_DRIVER_STATE "HANGED");
       }
}

int wpa_driver_nl80211_driver_cmd(void *priv, char *cmd, char *buf,
				  size_t buf_len )
{
	struct i802_bss *bss = priv;
	struct wpa_driver_nl80211_data *drv = bss->drv;
	struct ifreq ifr;
	android_wifi_priv_cmd priv_cmd;
	int ret = 0;
	union wpa_event_data event_data;
	struct wpa_supplicant *wpa_s = drv->ctx;

	wpa_printf(MSG_DEBUG, "%s: Driver cmd: %s\n", __func__, cmd);
	memset(&ifr, 0, sizeof(ifr));
	memset(&priv_cmd, 0, sizeof(priv_cmd));
	memset(&event_data, 0, sizeof(event_data));

	if (os_strcasecmp(cmd, "STOP") == 0) {
		linux_set_iface_flags(drv->global->ioctl_sock, bss->ifname, 0);
		wpa_msg(drv->ctx, MSG_INFO, WPA_EVENT_DRIVER_STATE "STOPPED");
	} else if (os_strcasecmp(cmd, "START") == 0) {
		linux_set_iface_flags(drv->global->ioctl_sock, bss->ifname, 1);
		wpa_msg(drv->ctx, MSG_INFO, WPA_EVENT_DRIVER_STATE "STARTED");
	} else if (os_strcasecmp(cmd, "MACADDR") == 0) {
		u8 macaddr[ETH_ALEN] = {};
		ret = linux_get_ifhwaddr(drv->global->ioctl_sock, bss->ifname, macaddr);
		if (!ret) ret = os_snprintf(buf, buf_len, "Macaddr = " MACSTR "\n", MAC2STR(macaddr));
	} else if(os_strncasecmp(cmd, "MAX_STA", 7) == 0) {
		int hdrlen = 2*sizeof(unsigned short);
		char max_sta_num = *buf;
		wpa_printf(MSG_INFO, "max_sta_num: %d, buf_len: %d.", max_sta_num, buf_len);
		memset(buf, 0, buf_len);
		*(unsigned short *)buf = CMD_SUBTYPE_MAX_NUM_STA;
		*(unsigned short *)(buf + hdrlen/2)= sizeof(max_sta_num);
		*(buf + hdrlen) = max_sta_num;
		buf_len = hdrlen + sizeof(max_sta_num);

               memset(&ifr, 0, sizeof(ifr));
               memset(&priv_cmd, 0, sizeof(priv_cmd));
               os_strncpy(ifr.ifr_name, bss->ifname, IFNAMSIZ);
	       wpa_printf(MSG_DEBUG, "buf_len:%d.", buf_len);
               priv_cmd.buf = buf;
               priv_cmd.used_len = buf_len;
               priv_cmd.total_len = buf_len;
               ifr.ifr_data = &priv_cmd;

               if ((ret = ioctl(drv->global->ioctl_sock, SIOCDEVPRIVATE + 2, &ifr)) < 0) {
                       wpa_printf(MSG_ERROR, "%s: failed to issue private commands\n", __func__);
                       //wpa_driver_send_hang_msg(drv);
               } else {
                       drv_errors = 0;
                       wpa_printf(MSG_INFO, "%s %s len = %d, %d", __func__, buf, ret, strlen(buf));
               }

	}  else if (os_strncasecmp(cmd, "MIRACAST", 8) == 0) {
		struct driver_cmd_msg *miracast;
		int value = atoi(cmd+8);

		memset(buf, 0, buf_len);
		miracast = (struct driver_cmd_msg *)buf;
		miracast->msg_type = CMD_SUBTYPE_MIRACAST_MODE;
		miracast->msg_len = sizeof(int);
		memcpy(miracast->msg_data, &value, sizeof(value));

		priv_cmd.buf = (char *)miracast;
		priv_cmd.used_len = sizeof(*miracast) + miracast->msg_len;
		priv_cmd.total_len = priv_cmd.used_len;

		os_strncpy(ifr.ifr_name, bss->ifname, IFNAMSIZ);
		ifr.ifr_data = &priv_cmd;

		if ((ret = ioctl(drv->global->ioctl_sock, SIOCDEVPRIVATE + 2, &ifr)) < 0) {
			wpa_printf(MSG_ERROR, "%s: failed to issue private commands(%s), total_len=%d, value=%d\n",
				__func__, strerror(errno), priv_cmd.total_len, value);
			//wpa_driver_send_hang_msg(drv);
		} else {
			drv_errors = 0;
		}

		memset(buf, 0, buf_len);
	} else if (os_strncasecmp(cmd, "SETSUSPENDMODE", 14) == 0) {
		os_memcpy(buf, cmd, strlen(cmd) + 1);
		memset(&ifr, 0, sizeof(ifr));
		memset(&priv_cmd, 0, sizeof(priv_cmd));
		os_strncpy(ifr.ifr_name, bss->ifname, IFNAMSIZ);
		ifr.ifr_name[IFNAMSIZ - 1] = '\0';

		priv_cmd.buf = buf;
		priv_cmd.used_len = buf_len;
		priv_cmd.total_len = buf_len;
		ifr.ifr_data = &priv_cmd;

		if ((ret = ioctl(drv->global->ioctl_sock, SIOCDEVPRIVATE + 4, &ifr)) < 0) {
			wpa_printf(MSG_ERROR, "%s: failed to issue private commands(%s)\n", __func__, strerror(errno));
			//wpa_driver_send_hang_msg(drv);
		} else {
			drv_errors = 0;
			ret = 0;

			wpa_printf(MSG_DEBUG, "%s %s len = %d, %d", __func__, buf, ret, strlen(buf));
		}
       } else if (os_strncasecmp(cmd, "COUNTRY", 7) == 0) {
           char *pos = strchr(cmd, ' ');
           int valid = 0;

           if (pos)
               valid = strlen(++pos) == 2 ? 1 : 0;

           if (valid) {
               wpa_printf(MSG_DEBUG, "SET country code: %c%c", pos[0], pos[1]);

               if ((ret = wpa_drv_set_country(wpa_s, pos)) < 0) {
                   wpa_printf(MSG_ERROR, "%s: failed to set country code\n",
                          __func__, strerror(errno));
                   ret = -1;
               } else {
                   wpa_supplicant_event(drv->ctx, EVENT_CHANNEL_LIST_CHANGED, &event_data);
                   wpa_printf(MSG_DEBUG, "NL80211 Set COUNTRY code OK!");
               }
           } else {
               wpa_printf(MSG_DEBUG, "Ivalid country code format: %s", cmd);
               ret = -1;
           }
       } else if(os_strncasecmp(cmd, "11VCFG_GET", 10) == 0) {
		os_memcpy(buf, cmd, strlen(cmd) + 1);
		os_strncpy(ifr.ifr_name, bss->ifname, IFNAMSIZ);

		priv_cmd.buf = buf;
		priv_cmd.used_len = buf_len;
		priv_cmd.total_len = buf_len;
		ifr.ifr_data = &priv_cmd;

		if ((ret = ioctl(drv->global->ioctl_sock, SIOCDEVPRIVATE + 1, &ifr)) < 0) {
			wpa_printf(MSG_ERROR, "%s: failed to issue private commands\n", __func__);
			//wpa_driver_send_hang_msg(drv);
		} else {
			drv_errors = 0;
			wpa_printf(MSG_DEBUG, "%s %s len = %d, %d", __func__, buf, ret, strlen(buf));
			wpa_printf(MSG_DEBUG, "11V_CFGGET: 0x%x ", buf[11]);
		}

	}else if(os_strncasecmp(cmd, "11VCFG_SET", 10) == 0) {
		os_memcpy(buf, cmd, 11);
		int tmp;
		tmp = atoi(&cmd[11]);
		buf[11] = tmp;
		os_strncpy(ifr.ifr_name, bss->ifname, IFNAMSIZ);

		priv_cmd.buf = buf;
		priv_cmd.used_len = buf_len;
		priv_cmd.total_len = buf_len;
		ifr.ifr_data = &priv_cmd;

		if ((ret = ioctl(drv->global->ioctl_sock, SIOCDEVPRIVATE + 1, &ifr)) < 0) {
			wpa_printf(MSG_ERROR, "%s: failed to issue private commands\n", __func__);
			//wpa_driver_send_hang_msg(drv);
		} else {
			drv_errors = 0;
			wpa_printf(MSG_DEBUG, "%s %s len = %d, %d", __func__, buf, ret, strlen(buf));
			wpa_printf(MSG_DEBUG, "11V_CFGSET: 0x%x ", buf[11]);
		}

	}
	return ret;
}

int wpa_driver_set_p2p_noa(void *priv, u8 count, int start, int duration)
{
	wpa_printf(MSG_DEBUG, "%s: NOT IMPLETE", __func__);

	return 0;
}

int wpa_driver_get_p2p_noa(void *priv, u8 *buf, size_t len)
{
	wpa_printf(MSG_DEBUG, "%s: NOT IMPLETE", __func__);

	/* Return 0 till we handle p2p_presence request completely in the driver */
	return 0;
}

int wpa_driver_set_p2p_ps(void *priv, int legacy_ps, int opp_ps, int ctwindow)
{
	wpa_printf(MSG_DEBUG, "%s: NOT IMPLETE", __func__);

	return 0;
}

int wpa_driver_set_ap_wps_p2p_ie(void *priv, const struct wpabuf *beacon,
				 const struct wpabuf *proberesp,
				 const struct wpabuf *assocresp)
{
	wpa_printf(MSG_DEBUG, "%s: NOT IMPLETE", __func__);

	return 0;
}

int wpa_driver_nl80211_driver_cmd_wnm(void *priv, enum wnm_oper oper, const u8 *peer,
			u8 *buf, u16 *buf_len)
{
	struct i802_bss *bss = priv;
	struct wpa_driver_nl80211_data *drv = bss->drv;
	struct ifreq ifr;
	android_wifi_priv_cmd priv_cmd;
	int ret = 0;
	char buff[MAX_DRV_CMD_SIZE];

	wpa_printf(MSG_DEBUG, "wnm_oper: %d\n", oper);
	memset(buff, 0, sizeof(buff));
	memset(&ifr, 0, sizeof(ifr));
	memset(&priv_cmd, 0, sizeof(priv_cmd));

	os_memcpy(buf, "WNM_SLEEP", 9);
	buf[9] = ' ';
	buf[10] = oper;
	os_strncpy(ifr.ifr_name, bss->ifname, IFNAMSIZ);

	priv_cmd.buf = buff;
	priv_cmd.used_len = sizeof(buff);
	priv_cmd.total_len = sizeof(buff);
	ifr.ifr_data = &priv_cmd;

	if ((ret = ioctl(drv->global->ioctl_sock, SIOCDEVPRIVATE + 1, &ifr)) < 0) {
		wpa_printf(MSG_ERROR, "%s: failed to issue private commands\n", __func__);
		wpa_driver_send_hang_msg(drv);
	} else {
		drv_errors = 0;
		wpa_printf(MSG_DEBUG, "%s %s len = %d, %d", __func__, buf, ret, strlen(buf));
	}

	return ret;
}
