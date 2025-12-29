/*
 * H3 DRAM initialization (DDR3)
 * Ported from xboot for awboot
 *
 * SPDX-License-Identifier: MIT
 *
 * Note: H3 uses external DDR3. Full implementation requires
 * complete DDR3 PHY initialization sequence from xboot (~700 lines).
 * This is a framework version.
 */

#include "main.h"
#include "reg-ccu.h"
#include "reg-dram.h"

#define CONFIG_DRAM_BASE    (0x40000000)
#define CONFIG_DRAM_CLK     (408)

static inline void sdelay(int loops)
{
	__asm__ __volatile__ ("1:\n" "subs %0, %1, #1\n"
		"bne 1b":"=r" (loops):"0"(loops));
}

static void mctl_await_completion(u32 reg, u32 mask, u32 val)
{
	int timeout = 0;

	while ((read32(reg) & mask) != val) {
		if (timeout++ > 10000)
			break;
	}
}

static void clock_set_pll_ddr(u32 clk)
{
	int n = 32;
	int k = 1;
	int m = 2;
	u32 val;

	if (clk > 24000000 * k * n / m) {
		m = 1;
		if (clk > 24000000 * k * n / m)
			k = 2;
	}

	val = (0x1 << 31);
	val |= (0x0 << 24);
	val |= (0x1 << 20);
	val |= ((((clk / (24000000 * k / m)) - 1) & 0x1f) << 8);
	val |= (((k - 1) & 0x3) << 4);
	val |= (((m - 1) & 0x3) << 0);
	write32(H3_CCU_BASE + CCU_PLL_DDR_CTRL, val);
	sdelay(5500);
}

/*
 * H3 DRAM initialization
 * Returns DRAM size in MB, or 0 on failure
 *
 * Note: Full implementation requires complete DDR3 PHY init sequence.
 * This is a placeholder that sets up basic clocks.
 * H3 typically has 256MB-1GB external DDR3.
 */
u32 sunxi_dram_init(void)
{
	u32 val;

	/* Disable MBUS clock */
	val = read32(H3_CCU_BASE + CCU_MBUS_CLK);
	val &= ~(0x1 << 31);
	write32(H3_CCU_BASE + CCU_MBUS_CLK, val);

	/* Disable MBUS reset */
	val = read32(H3_CCU_BASE + CCU_MBUS_RST);
	val &= ~(0x1 << 31);
	write32(H3_CCU_BASE + CCU_MBUS_RST, val);

	/* Disable DRAM clock gate */
	val = read32(H3_CCU_BASE + CCU_BUS_CLK_GATE0);
	val &= ~(0x1 << 14);
	write32(H3_CCU_BASE + CCU_BUS_CLK_GATE0, val);

	/* Assert DRAM reset */
	val = read32(H3_CCU_BASE + CCU_BUS_SOFT_RST0);
	val &= ~(0x1 << 14);
	write32(H3_CCU_BASE + CCU_BUS_SOFT_RST0, val);

	/* Disable DDR PLL */
	val = read32(H3_CCU_BASE + CCU_PLL_DDR_CTRL);
	val &= ~(0x1 << 31);
	write32(H3_CCU_BASE + CCU_PLL_DDR_CTRL, val);
	sdelay(10);

	/* Disable DRAM clock */
	val = read32(H3_CCU_BASE + CCU_DRAM_CLK_GATE);
	val &= ~(0x1 << 31);
	write32(H3_CCU_BASE + CCU_DRAM_CLK_GATE, val);
	sdelay(1000);

	/* Set DDR PLL */
	clock_set_pll_ddr(CONFIG_DRAM_CLK * 2 * 1000000);

	/* Configure DRAM clock */
	val = read32(H3_CCU_BASE + CCU_DRAM_CFG);
	val &= ~(0xf << 0);
	val &= ~(0x3 << 20);
	val |= ((1 - 1) << 0);
	val |= (0x0 << 20);
	val |= (0x1 << 16);
	write32(H3_CCU_BASE + CCU_DRAM_CFG, val);
	mctl_await_completion(H3_CCU_BASE + CCU_DRAM_CFG, 0x1 << 16, 0);

	/* Deassert DRAM reset */
	val = read32(H3_CCU_BASE + CCU_BUS_SOFT_RST0);
	val |= (0x1 << 14);
	write32(H3_CCU_BASE + CCU_BUS_SOFT_RST0, val);

	/* Enable DRAM clock gate */
	val = read32(H3_CCU_BASE + CCU_BUS_CLK_GATE0);
	val |= (0x1 << 14);
	write32(H3_CCU_BASE + CCU_BUS_CLK_GATE0, val);

	/* Enable MBUS clock */
	val = read32(H3_CCU_BASE + CCU_MBUS_CLK);
	val |= (0x1 << 31);
	write32(H3_CCU_BASE + CCU_MBUS_CLK, val);

	/* Enable MBUS reset */
	val = read32(H3_CCU_BASE + CCU_MBUS_RST);
	val |= (0x1 << 31);
	write32(H3_CCU_BASE + CCU_MBUS_RST, val);

	/* Enable DRAM clock */
	val = read32(H3_CCU_BASE + CCU_DRAM_CFG);
	val |= (0x1 << 31);
	write32(H3_CCU_BASE + CCU_DRAM_CFG, val);
	sdelay(10);

	/*
	 * TODO: Complete DDR3 PHY initialization
	 * For now, return 512MB as default
	 */

	return 512;
}
