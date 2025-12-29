/*
 * reg-dram-suniv.h - DRAM register definitions for Suniv SoCs (F1C100S/F1C200S)
 *
 * Common DRAM controller registers shared by F1C100S and F1C200S.
 * These SoCs use the same DRAM controller IP.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __REG_DRAM_SUNIV_H__
#define __REG_DRAM_SUNIV_H__

/* DRAM controller register offsets */
#define DRAM_SCONR          (0x00)  /* SDRAM Configuration Register */
#define DRAM_STMG0R         (0x04)  /* SDRAM Timing 0 Register */
#define DRAM_STMG1R         (0x08)  /* SDRAM Timing 1 Register */
#define DRAM_SCTLR          (0x0c)  /* SDRAM Control Register */
#define DRAM_SREFR          (0x10)  /* SDRAM Refresh Register */
#define DRAM_SEXTMR         (0x14)  /* SDRAM Extended Mode Register */
#define DRAM_DDLYR          (0x24)  /* SDRAM DLL Register */
#define DRAM_DADRR          (0x28)  /* SDRAM Data Address Register */
#define DRAM_DVALR          (0x2c)  /* SDRAM Data Value Register */
#define DRAM_DRPTR0         (0x30)  /* SDRAM DQS Read Pointer 0 */
#define DRAM_DRPTR1         (0x34)  /* SDRAM DQS Read Pointer 1 */
#define DRAM_DRPTR2         (0x38)  /* SDRAM DQS Read Pointer 2 */
#define DRAM_DRPTR3         (0x3c)  /* SDRAM DQS Read Pointer 3 */
#define DRAM_SEFR           (0x40)  /* SDRAM Error Flag Register */
#define DRAM_MAE            (0x44)  /* SDRAM Memory Access Error */
#define DRAM_ASPR           (0x48)  /* SDRAM Auto-Refresh Period */
#define DRAM_SDLY0          (0x4C)  /* SDRAM Delay 0 */
#define DRAM_SDLY1          (0x50)  /* SDRAM Delay 1 */
#define DRAM_SDLY2          (0x54)  /* SDRAM Delay 2 */
#define DRAM_MCR0           (0x100) /* SDRAM Mode Control 0 */
#define DRAM_MCR1           (0x104) /* SDRAM Mode Control 1 */
#define DRAM_MCR2           (0x108) /* SDRAM Mode Control 2 */
#define DRAM_MCR3           (0x10c) /* SDRAM Mode Control 3 */
#define DRAM_MCR4           (0x110) /* SDRAM Mode Control 4 */
#define DRAM_MCR5           (0x114) /* SDRAM Mode Control 5 */
#define DRAM_MCR6           (0x118) /* SDRAM Mode Control 6 */
#define DRAM_MCR7           (0x11c) /* SDRAM Mode Control 7 */
#define DRAM_MCR8           (0x120) /* SDRAM Mode Control 8 */
#define DRAM_MCR9           (0x124) /* SDRAM Mode Control 9 */
#define DRAM_MCR10          (0x128) /* SDRAM Mode Control 10 */
#define DRAM_MCR11          (0x12c) /* SDRAM Mode Control 11 */
#define DRAM_BWCR           (0x140) /* SDRAM Bandwidth Control */

/* SCTLR bits */
#define DRAM_SCTLR_INIT     (1 << 0)

/* DDLYR bits */
#define DRAM_DDLYR_SCAN     (1 << 0)

#endif /* __REG_DRAM_SUNIV_H__ */
