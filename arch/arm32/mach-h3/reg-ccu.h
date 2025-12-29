/*
 * H3 CCU (Clock Control Unit) Register Definitions
 * Ported from xboot for awboot
 */

#ifndef __H3_REG_CCU_H__
#define __H3_REG_CCU_H__

#define H3_CCU_BASE             (0x01c20000)

#define CCU_PLL_CPUX_CTRL       (0x000)
#define CCU_PLL_AUDIO_CTRL      (0x008)
#define CCU_PLL_VIDEO_CTRL      (0x010)
#define CCU_PLL_VE_CTRL         (0x018)
#define CCU_PLL_DDR_CTRL        (0x020)
#define CCU_PLL_PERIPH0_CTRL    (0x028)
#define CCU_PLL_GPU_CTRL        (0x038)
#define CCU_PLL_PERIPH1_CTRL    (0x044)
#define CCU_PLL_DE_CTRL         (0x048)

#define CCU_CPUX_AXI_CFG        (0x050)
#define CCU_AHB1_APB1_CFG       (0x054)
#define CCU_APB1_CFG            (0x058)
#define CCU_AHB2_CFG            (0x05c)

#define CCU_BUS_CLK_GATE0       (0x060)
#define CCU_BUS_CLK_GATE1       (0x064)
#define CCU_BUS_CLK_GATE2       (0x068)
#define CCU_BUS_CLK_GATE3       (0x06c)
#define CCU_BUS_CLK_GATE4       (0x070)

#define CCU_THS_CLK             (0x074)
#define CCU_NAND_CLK            (0x080)
#define CCU_SDMMC0_CLK          (0x088)
#define CCU_SDMMC1_CLK          (0x08c)
#define CCU_SDMMC2_CLK          (0x090)
#define CCU_CE_CLK              (0x09c)
#define CCU_SPI0_CLK            (0x0a0)
#define CCU_SPI1_CLK            (0x0a4)
#define CCU_USBPHY_CFG          (0x0cc)
#define CCU_DRAM_CFG            (0x0f4)
#define CCU_MBUS_RST            (0x0fc)
#define CCU_DRAM_CLK_GATE       (0x100)
#define CCU_MBUS_CLK            (0x15c)

#define CCU_PLL_STABLE_TIME0    (0x200)
#define CCU_PLL_STABLE_TIME1    (0x204)
#define CCU_PLL_DDR_BIAS        (0x230)
#define CCU_PLL_DDR_TUN         (0x260)
#define CCU_PLL_DDR_PAT         (0x290)

#define CCU_BUS_SOFT_RST0       (0x2c0)
#define CCU_BUS_SOFT_RST1       (0x2c4)
#define CCU_BUS_SOFT_RST2       (0x2c8)
#define CCU_BUS_SOFT_RST3       (0x2d0)
#define CCU_BUS_SOFT_RST4       (0x2d8)

#endif /* __H3_REG_CCU_H__ */
