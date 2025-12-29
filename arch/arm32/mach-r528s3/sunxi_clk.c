/*
 * R528S3 Clock initialization
 * Ported from xboot for awboot
 *
 * SPDX-License-Identifier: MIT
 */

#include "main.h"
#include "reg-ccu.h"

static inline void sdelay(int loops)
{
	__asm__ __volatile__ ("1:\n" "subs %0, %1, #1\n"
		"bne 1b":"=r" (loops):"0"(loops));
}

void sunxi_clk_init(void)
{
	u32 val;

	/* Set CPU clock to 1008MHz */
	/* PLL_CPU = 24MHz * N / M / P */
	val = (0x1 << 31) | (0x1 << 27) | (41 << 8) | (0 << 1) | (0 << 0);
	write32(R528S3_CCU_BASE + CCU_PLL_CPU_CTRL, val);
	while (!(read32(R528S3_CCU_BASE + CCU_PLL_CPU_CTRL) & (1 << 28)));

	/* Set CPU AXI clock */
	val = (2 << 24) | (0 << 16) | (1 << 8) | (1 << 0);
	write32(R528S3_CCU_BASE + CCU_CPU_AXI_CFG, val);
	sdelay(100);

	/* Set PLL_PERI0 to 600MHz */
	val = (0x1 << 31) | (0x1 << 27) | (24 << 8) | (0 << 1) | (0 << 0);
	write32(R528S3_CCU_BASE + CCU_PLL_PERI0_CTRL, val);
	while (!(read32(R528S3_CCU_BASE + CCU_PLL_PERI0_CTRL) & (1 << 28)));

	/* Set PSI/AHB clock */
	val = (0x3 << 24) | (0 << 8) | (2 << 0);
	write32(R528S3_CCU_BASE + CCU_PSI_CLK, val);
	sdelay(100);

	/* Set APB0 clock */
	val = (0x3 << 24) | (0 << 8) | (2 << 0);
	write32(R528S3_CCU_BASE + CCU_APB0_CLK, val);
	sdelay(100);

	/* Set APB1 clock */
	val = (0x3 << 24) | (0 << 8) | (2 << 0);
	write32(R528S3_CCU_BASE + CCU_APB1_CLK, val);
	sdelay(100);

	/* Set MBUS clock */
	val = (0x1 << 31) | (0x1 << 24) | (2 << 0);
	write32(R528S3_CCU_BASE + CCU_MBUS_CLK, val);
	sdelay(100);
}
