/*
 * R528S3 DRAM initialization (DDR3)
 * Ported from xboot for awboot
 *
 * SPDX-License-Identifier: MIT
 *
 * Note: R528S3 uses external DDR3. Full implementation requires
 * complete DDR3 PHY initialization sequence from xboot (~1000 lines).
 * This is a framework version.
 */

#include "main.h"
#include "reg-ccu.h"
#include "reg-dram.h"

#define CONFIG_DRAM_BASE    (0x40000000)
#define CONFIG_DRAM_CLK     (792)

static inline void sdelay(int loops)
{
	__asm__ __volatile__ ("1:\n" "subs %0, %1, #1\n"
		"bne 1b":"=r" (loops):"0"(loops));
}

/*
 * R528S3 DRAM initialization
 * Returns DRAM size in MB, or 0 on failure
 *
 * Note: Full implementation requires complete DDR3 PHY init sequence.
 * This is a placeholder. R528S3 typically has 128MB-256MB external DDR3.
 */
u32 sunxi_dram_init(void)
{
	u32 val;

	/* Enable DRAM clock */
	val = read32(R528S3_CCU_BASE + CCU_DRAM_CLK);
	val |= (0x1 << 31);
	write32(R528S3_CCU_BASE + CCU_DRAM_CLK, val);
	sdelay(100);

	/* Deassert DRAM reset */
	val = read32(R528S3_CCU_BASE + CCU_DRAM_BGR);
	val |= (0x1 << 16);
	write32(R528S3_CCU_BASE + CCU_DRAM_BGR, val);
	sdelay(100);

	/* Enable DRAM clock gate */
	val = read32(R528S3_CCU_BASE + CCU_DRAM_BGR);
	val |= (0x1 << 0);
	write32(R528S3_CCU_BASE + CCU_DRAM_BGR, val);
	sdelay(100);

	/*
	 * TODO: Complete DDR3 PHY initialization
	 * For now, return 128MB as default
	 */

	return 128;
}
