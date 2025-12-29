/*
 * V3S DRAM initialization (DDR2)
 * Ported from xboot for awboot
 *
 * SPDX-License-Identifier: MIT
 *
 * Note: This is a simplified version. Full implementation requires
 * the complete DDR2 PHY initialization sequence from xboot.
 */

#include "main.h"
#include "reg-ccu.h"
#include "reg-dram.h"

#define CONFIG_DRAM_BASE    (0x40000000)
#define CONFIG_DRAM_CLK     (360)
#define CONFIG_DRAM_ZQ      (14779)

#define clrbits_le32(addr, clear) \
	write32((addr), read32((addr)) & ~(clear))

#define setbits_le32(addr, set) \
	write32((addr), read32((addr)) | (set))

#define clrsetbits_le32(addr, clear, set) \
	write32((addr), (read32((addr)) & ~(clear)) | (set))

#define DIV_ROUND_UP(n, d)  (((n) + (d) - 1) / (d))

static inline void sdelay(int loops)
{
	__asm__ __volatile__ ("1:\n" "subs %0, %1, #1\n"
		"bne 1b":"=r" (loops):"0"(loops));
}

static inline int gfls(int x)
{
	int r = 32;

	if (!x)
		return 0;
	if (!(x & 0xffff0000u)) {
		x <<= 16;
		r -= 16;
	}
	if (!(x & 0xff000000u)) {
		x <<= 8;
		r -= 8;
	}
	if (!(x & 0xf0000000u)) {
		x <<= 4;
		r -= 4;
	}
	if (!(x & 0xc0000000u)) {
		x <<= 2;
		r -= 2;
	}
	if (!(x & 0x80000000u)) {
		x <<= 1;
		r -= 1;
	}
	return r;
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
	write32(V3S_CCU_BASE + CCU_PLL_DDR0_CTRL, val);
	sdelay(5500);
}

static void mctl_await_completion(u32 reg, u32 mask, u32 val)
{
	int timeout = 0;

	while ((read32(reg) & mask) != val) {
		if (timeout++ > 10000)
			break;
	}
}

/*
 * V3S DRAM initialization
 * Returns DRAM size in bytes, or 0 on failure
 *
 * Note: Full implementation requires complete DDR2 PHY init sequence.
 * This is a placeholder that sets up basic clocks.
 */
u32 sunxi_dram_init(void)
{
	u32 val;

	/* Disable MBUS clock */
	val = read32(V3S_CCU_BASE + CCU_MBUS_CLK);
	val &= ~(0x1 << 31);
	write32(V3S_CCU_BASE + CCU_MBUS_CLK, val);

	/* Disable MBUS reset */
	val = read32(V3S_CCU_BASE + CCU_MBUS_RST);
	val &= ~(0x1 << 31);
	write32(V3S_CCU_BASE + CCU_MBUS_RST, val);

	/* Disable DRAM clock gate */
	val = read32(V3S_CCU_BASE + CCU_BUS_CLK_GATE0);
	val &= ~(0x1 << 14);
	write32(V3S_CCU_BASE + CCU_BUS_CLK_GATE0, val);

	/* Assert DRAM reset */
	val = read32(V3S_CCU_BASE + CCU_BUS_SOFT_RST0);
	val &= ~(0x1 << 14);
	write32(V3S_CCU_BASE + CCU_BUS_SOFT_RST0, val);

	/* Disable DDR PLL */
	val = read32(V3S_CCU_BASE + CCU_PLL_DDR0_CTRL);
	val &= ~(0x1 << 31);
	write32(V3S_CCU_BASE + CCU_PLL_DDR0_CTRL, val);
	sdelay(10);

	/* Disable DRAM clock */
	val = read32(V3S_CCU_BASE + CCU_DRAM_CLK_GATE);
	val &= ~(0x1 << 31);
	write32(V3S_CCU_BASE + CCU_DRAM_CLK_GATE, val);
	sdelay(1000);

	/* Set DDR PLL */
	clock_set_pll_ddr(CONFIG_DRAM_CLK * 2 * 1000000);

	/* Configure DRAM clock */
	val = read32(V3S_CCU_BASE + CCU_DRAM_CFG);
	val &= ~(0xf << 0);
	val &= ~(0x3 << 20);
	val |= ((1 - 1) << 0);
	val |= (0x0 << 20);
	val |= (0x1 << 16);
	write32(V3S_CCU_BASE + CCU_DRAM_CFG, val);
	mctl_await_completion(V3S_CCU_BASE + CCU_DRAM_CFG, 0x1 << 16, 0);

	/* Deassert DRAM reset */
	val = read32(V3S_CCU_BASE + CCU_BUS_SOFT_RST0);
	val |= (0x1 << 14);
	write32(V3S_CCU_BASE + CCU_BUS_SOFT_RST0, val);

	/* Enable DRAM clock gate */
	val = read32(V3S_CCU_BASE + CCU_BUS_CLK_GATE0);
	val |= (0x1 << 14);
	write32(V3S_CCU_BASE + CCU_BUS_CLK_GATE0, val);

	/* Enable MBUS clock */
	val = read32(V3S_CCU_BASE + CCU_MBUS_CLK);
	val |= (0x1 << 31);
	write32(V3S_CCU_BASE + CCU_MBUS_CLK, val);

	/* Enable MBUS reset */
	val = read32(V3S_CCU_BASE + CCU_MBUS_RST);
	val |= (0x1 << 31);
	write32(V3S_CCU_BASE + CCU_MBUS_RST, val);

	/* Enable DRAM clock */
	val = read32(V3S_CCU_BASE + CCU_DRAM_CFG);
	val |= (0x1 << 31);
	write32(V3S_CCU_BASE + CCU_DRAM_CFG, val);
	sdelay(10);

	/*
	 * TODO: Complete DDR2 PHY initialization
	 * The full implementation requires:
	 * - mctl_set_cr() - Configure control register
	 * - mctl_set_timing_params() - Set timing parameters
	 * - mctl_set_master_priority() - Set master priority
	 * - mctl_zq_calibration() - ZQ calibration
	 * - mctl_phy_init() - PHY initialization
	 * - mctl_channel_init() - Channel initialization
	 * - mctl_auto_detect_dram_size() - Auto detect DRAM size
	 *
	 * For now, return 64MB as default (V3S has 64MB DDR2)
	 */

	return 64 * 1024 * 1024;
}
