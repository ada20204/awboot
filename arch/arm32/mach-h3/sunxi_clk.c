/*
 * H3 Clock initialization
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

static void clock_set_pll_cpu(u32 clk)
{
	int p = 0;
	int k = 1;
	int m = 1;
	u32 val;

	if (clk > 1152000000)
		k = 2;
	else if (clk > 768000000) {
		k = 3;
		m = 2;
	}

	/* Switch to 24MHz clock while changing cpu pll */
	val = (2 << 0) | (1 << 8) | (1 << 16);
	write32(H3_CCU_BASE + CCU_CPUX_AXI_CFG, val);

	/* cpu pll rate = ((24000000 * n * k) >> p) / m */
	val = (0x1 << 31);
	val |= ((p & 0x3) << 16);
	val |= ((((clk / (24000000 * k / m)) - 1) & 0x1f) << 8);
	val |= (((k - 1) & 0x3) << 4);
	val |= (((m - 1) & 0x3) << 0);
	write32(H3_CCU_BASE + CCU_PLL_CPUX_CTRL, val);
	sdelay(200);

	/* Switch clock source */
	val = (2 << 0) | (1 << 8) | (2 << 16);
	write32(H3_CCU_BASE + CCU_CPUX_AXI_CFG, val);
}

void sunxi_clk_init(void)
{
	clock_set_pll_cpu(1008000000);

	/* pll video - 297MHZ */
	write32(H3_CCU_BASE + CCU_PLL_VIDEO_CTRL, 0x91004107);

	/* pll periph0 - 600MHZ */
	write32(H3_CCU_BASE + CCU_PLL_PERIPH0_CTRL, 0x90041811);
	while (!(read32(H3_CCU_BASE + CCU_PLL_PERIPH0_CTRL) & (1 << 28)));

	/* ahb1 = pll periph0 / 3, apb1 = ahb1 / 2 */
	write32(H3_CCU_BASE + CCU_AHB1_APB1_CFG, 0x00003180);

	/* mbus = pll periph0 / 4 */
	write32(H3_CCU_BASE + CCU_MBUS_CLK, 0x81000003);
}
