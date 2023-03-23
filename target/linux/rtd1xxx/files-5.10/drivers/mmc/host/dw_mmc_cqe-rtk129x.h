/*
 *  Copyright (C) 2013 Realtek Semiconductors, All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __DW_RTK_MMC_CQE_RTK129X_H
#define __DW_RTK_MMC_CQE_RTK129X_H

//1295 emmc ip register
#define SDMMC_CTRL                            ( 0x000)
#define SDMMC_PWREN                           ( 0x004)
#define SDMMC_CLKDIV                          ( 0x008)
#define SDMMC_CLKSRC                          ( 0x00C)
#define SDMMC_CLKENA                          ( 0x010)
#define SDMMC_TMOUT                           ( 0x014)
#define SDMMC_CTYPE                           ( 0x018)
#define SDMMC_BLKSIZE                         ( 0x01C)
#define SDMMC_BYTCNT                          ( 0x020)
#define SDMMC_INTMASK                         ( 0x024)
#define SDMMC_CMDARG                          ( 0x028)
#define SDMMC_CMD                             ( 0x02C)
#define SDMMC_RESP0                           ( 0x030)
#define SDMMC_RESP1                           ( 0x034)
#define SDMMC_RESP2                           ( 0x038)
#define SDMMC_RESP3                           ( 0x03C)
#define SDMMC_MINTSTS                         ( 0x040)
#define SDMMC_RINTSTS                         ( 0x044)
#define SDMMC_STATUS                          ( 0x048)
#define SDMMC_FIFOTH                          ( 0x04C)
#define SDMMC_TBBCNT                          ( 0x060)
#define SDMMC_UHSREG                          ( 0x074)
#define SDMMC_BMOD                            ( 0x080)
#define SDMMC_DBADDR                          ( 0x088)
#define SDMMC_IDINTEN                         ( 0x090)
#define SDMMC_IDSTS			     			 ( 0x08C)
#define SDMMC_CARD_THR_CTL			         ( 0x100)
#define SDMMC_DDR_REG			     		 ( 0x10c)

#define SDMMC_muxpad0				(0x600)	//mux for nand and emmc
#define SDMMC_muxpad1				(0x604)	//mux for sdio and sd card
#define SDMMC_PFUNC_NF1				(0x60c)	
#define SDMMC_PFUNC_CR				(0x610)	
#define SDMMC_muxpad2				(0x61c)
#define SDMMC_PDRIVE_NF0        ( 0x620 )
#define SDMMC_PDRIVE_NF1        ( 0x624 )
#define SDMMC_PDRIVE_NF2        ( 0x628 )
#define SDMMC_PDRIVE_NF3        ( 0x62c )
#define SDMMC_PDRIVE_NF4        ( 0x630 )

#define SDMMC_PDRIVE_CR0        ( 0x634 )
#define SDMMC_PDRIVE_CR1        ( 0x638 )
#define SDMMC_PDRIVE_SDIO           ( 0x63c )
#define SDMMC_PDRIVE_SDIO1          ( 0x640 )

struct backupRegs {
	u32			emmc_mux_pad0;
	u32			emmc_mux_pad1;
	u32			emmc_pfunc_nf1;
	u32			emmc_pfunc_cr;
	u32			emmc_pdrive_nf1;
	u32			emmc_pdrive_nf2;
	u32			emmc_pdrive_nf3;
	u32			emmc_pdrive_nf4;

//129x emmc reset will have impact on SD & SDIO
	u32			emmc_pdrive_cr0;
	u32			emmc_pdrive_cr1;
	u32			emmc_pdrive_sdio;
	u32			emmc_pdrive_sdio1;

	u32			emmc_ctype;
	u32			emmc_uhsreg;
	u32			emmc_ddr_reg;
	u32			emmc_card_thr_ctl;
	u32			emmc_clk_div;
	u32			emmc_ckgen_ctl;
	u32			dqs_ctrl1;
	u32			emmc_clken;
};

#endif
