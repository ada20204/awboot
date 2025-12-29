/*
 * R528S3 CCU (Clock Control Unit) Register Definitions
 * Ported from xboot for awboot
 */

#ifndef __R528S3_REG_CCU_H__
#define __R528S3_REG_CCU_H__

#define R528S3_CCU_BASE             (0x02001000)

#define CCU_PLL_CPU_CTRL            (0x000)
#define CCU_PLL_DDR_CTRL            (0x010)
#define CCU_PLL_PERI0_CTRL          (0x020)
#define CCU_PLL_PERI1_CTRL          (0x028)
#define CCU_PLL_GPU_CTRL            (0x030)
#define CCU_PLL_VIDEO0_CTRL         (0x040)
#define CCU_PLL_VIDEO1_CTRL         (0x048)
#define CCU_PLL_VE_CTRL             (0x058)
#define CCU_PLL_DE_CTRL             (0x060)
#define CCU_PLL_AUDIO0_CTRL         (0x078)
#define CCU_PLL_AUDIO1_CTRL         (0x080)

#define CCU_PLL_DDR_PAT0_CTRL       (0x110)
#define CCU_PLL_DDR_PAT1_CTRL       (0x114)
#define CCU_PLL_PERI0_PAT0_CTRL     (0x120)
#define CCU_PLL_PERI0_PAT1_CTRL     (0x124)

#define CCU_PLL_CPU_BIAS            (0x300)
#define CCU_PLL_DDR_BIAS            (0x310)
#define CCU_PLL_PERI0_BIAS          (0x320)

#define CCU_CPU_AXI_CFG             (0x500)
#define CCU_CPU_GATING              (0x504)
#define CCU_PSI_CLK                 (0x510)
#define CCU_AHB3_CLK                (0x51c)
#define CCU_APB0_CLK                (0x520)
#define CCU_APB1_CLK                (0x524)
#define CCU_MBUS_CLK                (0x540)

#define CCU_DMA_BGR                 (0x70c)
#define CCU_DRAM_CLK                (0x800)
#define CCU_MBUS_MAT_CLK_GATING     (0x804)
#define CCU_DRAM_BGR                (0x80c)

#endif /* __R528S3_REG_CCU_H__ */
