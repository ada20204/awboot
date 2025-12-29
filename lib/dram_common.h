/*
 * dram_common.h - Common DRAM definitions for awboot
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __DRAM_COMMON_H__
#define __DRAM_COMMON_H__

#include "types.h"
#include "io.h"

/*
 * Common delay functions
 */
static inline void sdelay(int loops)
{
	__asm__ __volatile__ ("1:\n" "subs %0, %1, #1\n"
		"bne 1b":"=r" (loops):"0"(loops));
}

static inline void dram_delay_us(u32 us)
{
	sdelay(us * 2);
}

static inline void dram_delay_ms(u32 ms)
{
	sdelay(ms * 2 * 1000);
}

/*
 * Common register access macros
 */
#define readl(addr)              read32(addr)
#define writel(val, addr)        write32((addr), (val))

#define clrsetbits_le32(addr, clear, set) \
	write32((addr), (read32(addr) & ~(clear)) | (set))

#define setbits_le32(addr, set) \
	write32((addr), read32(addr) | (set))

#define clrbits_le32(addr, clear) \
	write32((addr), read32(addr) & ~(clear))

#define DIV_ROUND_UP(a, b)       (((a) + (b) - 1) / (b))

/*
 * Common DRAM types
 */
enum dram_type {
	DRAM_TYPE_SDR   = 0,
	DRAM_TYPE_DDR   = 1,
	DRAM_TYPE_MDDR  = 2,
	DRAM_TYPE_DDR2  = 3,
	DRAM_TYPE_DDR3  = 4,
	DRAM_TYPE_LPDDR2 = 6,
	DRAM_TYPE_LPDDR3 = 7,
};

/*
 * Common timeout for DRAM operations
 */
#define DRAM_TIMEOUT_DEFAULT    0xffffff

/*
 * Wait for bit to clear with timeout
 * Returns: 1 on success, 0 on timeout
 */
static inline int dram_wait_bit_clear(u32 addr, u32 bit)
{
	u32 timeout = DRAM_TIMEOUT_DEFAULT;

	while ((read32(addr) & bit) && timeout--) {
		if (timeout == 0)
			return 0;
	}
	return 1;
}

/*
 * Wait for bit to set with timeout
 * Returns: 1 on success, 0 on timeout
 */
static inline int dram_wait_bit_set(u32 addr, u32 bit)
{
	u32 timeout = DRAM_TIMEOUT_DEFAULT;

	while (!(read32(addr) & bit) && timeout--) {
		if (timeout == 0)
			return 0;
	}
	return 1;
}

#endif /* __DRAM_COMMON_H__ */
