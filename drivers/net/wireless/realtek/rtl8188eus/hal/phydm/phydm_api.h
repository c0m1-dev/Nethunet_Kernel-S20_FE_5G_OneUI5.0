/******************************************************************************
 *
 * Copyright(c) 2007 - 2017  Realtek Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * The full GNU General Public License is included in this distribution in the
 * file called LICENSE.
 *
 * Contact Information:
 * wlanfae <wlanfae@realtek.com>
 * Realtek Corporation, No. 2, Innovation Road II, Hsinchu Science Park,
 * Hsinchu 300, Taiwan.
 *
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 *****************************************************************************/

#ifndef __PHYDM_API_H__
#define __PHYDM_API_H__

#define PHYDM_API_VERSION "1.0" /* @2017.07.10  Dino, Add phydm_api.h*/

/* @1 ============================================================
 * 1  Definition
 * 1 ============================================================
 */
#define CN_CNT_MAX 10 /*@max condition number threshold*/

#define FUNC_ENABLE 1
#define FUNC_DISABLE 2

/*@NBI API------------------------------------*/
#define NBI_128TONE 27 /*register table size*/
#define NBI_256TONE 59 /*register table size*/

#define NUM_START_CH_80M 7
#define NUM_START_CH_40M 14

#define CH_OFFSET_40M 2
#define CH_OFFSET_80M 6

#define FFT_128_TYPE 1
#define FFT_256_TYPE 2

#define FREQ_POSITIVE 1
#define FREQ_NEGATIVE 2
/*@------------------------------------------------*/

enum phystat_rpt {
	PHY_PWDB = 0,
	PHY_EVM = 1,
	PHY_CFO = 2,
	PHY_RXSNR = 3,
	PHY_LGAIN = 4,
	PHY_HT_AAGC_GAIN = 5,
};

#ifndef PHYDM_COMMON_API_SUPPORT
#define INVALID_RF_DATA 0xffffffff
#define INVALID_TXAGC_DATA 0xff
#endif

/* @1 ============================================================
 * 1  structure
 * 1 ============================================================
 */

struct phydm_api_stuc {
	u32 rxiqc_reg1; /*N-mode: for pathA REG0xc14*/
	u32 rxiqc_reg2; /*N-mode: for pathB REG0xc1c*/
	u8 tx_queue_bitmap; /*REG0x520[23:16]*/
	u8 ccktx_path;
};

/* @1 ============================================================
 * 1  enumeration
 * 1 ============================================================
 */

/* @1 ============================================================
 * 1  function prototype
 * 1 ============================================================
 */
void phydm_reset_bb_hw_cntx(void *dm_void);

void phydm_dynamic_ant_weightingx(void *dm_void);

#ifdef DYN_ANT_WEIGHTING_SUPPORT
void phydm_ant_weight_dbg(void *dm_void, char input[][16], u32 *_used,
			  char *output, u32 *_out_len);
#endif

void phydm_trx_antenna_setting_initx(void *dm_void, u8 num_rf_path);

void phydm_config_ofdm_rx_pathx(void *dm_void, u32 path);

void phydm_config_cck_rx_pathx(void *dm_void, enum bb_path path);

void phydm_config_cck_rx_antenna_initx(void *dm_void);

void phydm_config_trx_pathx(void *dm_void, char input[][16], u32 *_used,
			   char *output, u32 *_out_len);

void phydm_tx_2pathx(void *dm_void);

void phydm_stop_3_wirex(void *dm_void, u8 set_type);

u8 phydm_stop_ic_trxx(void *dm_void, u8 set_type);

void phydm_dis_cck_trxx(void *dm_void, u8 set_type);

void phydm_set_ext_switchx(void *dm_void, u32 ext_ant_switch);

void phydm_nbi_enablex(void *dm_void, u32 enable);

u8 phydm_csi_mask_settingx(void *dm_void, u32 enable, u32 ch, u32 bw, u32 f_intf,
			  u32 sec_ch);

u8 phydm_nbi_settingx(void *dm_void, u32 enable, u32 ch, u32 bw, u32 f_intf,
		     u32 sec_ch);

void phydm_nbi_debugx(void *dm_void, char input[][16], u32 *_used,
		     char *output, u32 *_out_len);

void phydm_csi_debugx(void *dm_void, char input[][16], u32 *_used,
		     char *output, u32 *_out_len);

void phydm_stop_ck320x(void *dm_void, u8 enable);

boolean
phydm_set_bb_txagc_offsetx(void *dm_void, s8 power_offset, u8 add_half_db);
#ifdef PHYDM_IC_JGR3_SERIES_SUPPORT
u8 phydm_csi_mask_settingx_jgr3(void *dm_void, u32 enable, u32 ch, u32 bw,
			       u32 f_intf, u32 sec_ch, u8 wgt);

void phydm_set_csi_maskx_jgr3(void *dm_void, u32 tone_idx_tmp, u8 tone_direction,
			     u8 wgt);

u8 phydm_nbi_settingx_jgr3(void *dm_void, u32 enable, u32 ch, u32 bw, u32 f_intf,
			  u32 sec_ch, u8 path);

void phydm_set_nbi_regx_jgr3(void *dm_void, u32 tone_idx_tmp, u8 tone_direction,
			    u8 path);

void phydm_nbi_enablex_jgr3(void *dm_void, u32 enable, u8 path);

u8 phydm_phystat_rpt_jgr3(void *dm_void, enum phystat_rpt info,
			  enum rf_path ant_path);
void phydm_user_position_for_sniffer(void *dm_void, u8 user_position);

#endif

#ifdef PHYDM_COMMON_API_SUPPORT
boolean
phydm_api_shift_txagc(void *dm_void, u32 pwr_offset, enum rf_path path,
		      boolean is_positive);
boolean
phydm_api_set_txagc(void *dm_void, u32 power_index, enum rf_path path,
		    u8 hw_rate, boolean is_single_rate);

u8 phydm_api_get_txagc(void *dm_void, enum rf_path path, u8 hw_rate);

boolean
phydm_api_switch_bw_channel(void *dm_void, u8 central_ch, u8 primary_ch_idx,
			    enum channel_width bandwidth);

boolean
phydm_api_trx_mode(void *dm_void, enum bb_path tx_path, enum bb_path rx_path,
		   enum bb_path tx_path_ctrl);

#endif

#ifdef CONFIG_MCC_DM
#ifdef DYN_ANT_WEIGHTING_SUPPORT
void phydm_dynamic_ant_weightingx_mcc_8822b(void *dm_void);
#endif /*#ifdef DYN_ANT_WEIGHTING_SUPPORT*/
void phydm_fill_mcccmd(void *dm_void, u8 regid, u16 reg_add,
		       u8 val0,	u8 val1);
u8 phydm_check(void *dm_void);
void phydm_mcc_init(void *dm_void);
void phydm_mcc_switch(void *dm_void);
#endif /*#ifdef CONFIG_MCC_DM*/

#endif