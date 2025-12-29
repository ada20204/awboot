/*
 * reg-ccu-suniv.h - CCU register definitions for Suniv SoCs (F1C100S/F1C200S)
 *
 * Common CCU registers shared by F1C100S and F1C200S.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __REG_CCU_SUNIV_H__
#define __REG_CCU_SUNIV_H__

/* PLL Control Registers */
#define CCU_PLL_CPU_CTRL        (0x000)
#define CCU_PLL_AUDIO_CTRL      (0x008)
#define CCU_PLL_VIDEO_CTRL      (0x010)
#define CCU_PLL_VE_CTRL         (0x018)
#define CCU_PLL_DDR_CTRL        (0x020)
#define CCU_PLL_PERIPH_CTRL     (0x028)

/* Clock Configuration Registers */
#define CCU_CPU_CFG             (0x050)
#define CCU_AHB_APB_CFG         (0x054)

/* Bus Clock Gate Registers */
#define CCU_BUS_CLK_GATE0       (0x060)
#define CCU_BUS_CLK_GATE1       (0x064)
#define CCU_BUS_CLK_GATE2       (0x068)

/* Peripheral Clock Registers */
#define CCU_SDMMC0_CLK          (0x088)
#define CCU_SDMMC1_CLK          (0x08c)
#define CCU_DAUDIO_CLK          (0x0b0)
#define CCU_SPDIF_CLK           (0x0b4)
#define CCU_I2S_CLK             (0x0b8)
#define CCU_USBPHY_CFG          (0x0cc)
#define CCU_DRAM_CLK_GATE       (0x100)
#define CCU_DEBE_CLK            (0x104)
#define CCU_DEFE_CLK            (0x10c)
#define CCU_LCD_CLK             (0x118)
#define CCU_DEINTERLACE_CLK     (0x11c)
#define CCU_TVE_CLK             (0x120)
#define CCU_TVD_CLK             (0x124)
#define CCU_CSI_CLK             (0x134)
#define CCU_VE_CLK              (0x13c)
#define CCU_ADDA_CLK            (0x140)
#define CCU_AVS_CLK             (0x144)

/* PLL Stable Time Registers */
#define CCU_PLL_STABLE_TIME0    (0x200)
#define CCU_PLL_STABLE_TIME1    (0x204)

/* PLL Bias Registers */
#define CCU_PLL_CPU_BIAS        (0x220)
#define CCU_PLL_AUDIO_BIAS      (0x224)
#define CCU_PLL_VIDEO_BIAS      (0x228)
#define CCU_PLL_VE_BIAS         (0x22c)
#define CCU_PLL_DDR0_BIAS       (0x230)
#define CCU_PLL_PERIPH_BIAS     (0x234)

/* PLL Tuning Registers */
#define CCU_PLL_CPU_TUN         (0x250)
#define CCU_PLL_DDR_TUN         (0x260)

/* PLL Pattern Registers */
#define CCU_PLL_AUDIO_PAT       (0x284)
#define CCU_PLL_VIDEO_PAT       (0x288)
#define CCU_PLL_DDR0_PAT        (0x290)

/* Bus Soft Reset Registers */
#define CCU_BUS_SOFT_RST0       (0x2c0)
#define CCU_BUS_SOFT_RST1       (0x2c4)
#define CCU_BUS_SOFT_RST3       (0x2d0)

/* PLL bits */
#define PLL_ENABLE              (1U << 31)
#define PLL_LOCK                (1 << 28)

#endif /* __REG_CCU_SUNIV_H__ */
