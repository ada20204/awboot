/*
 * dram_common.c - Common DRAM functions for awboot
 *
 * SPDX-License-Identifier: MIT
 */

#include "dram_common.h"
#include "debug.h"

/*
 * Simple DRAM memory test
 * Returns: 1 on success, 0 on failure
 */
int dram_memory_test(u32 base, u32 size_mb)
{
	u32 i;
	u32 test_size = 128; /* Test first 128 words */
	volatile u32 *mem = (volatile u32 *)base;

	/* Write pattern */
	for (i = 0; i < test_size; i++) {
		mem[i] = base + (i * 4);
	}

	/* Verify pattern */
	for (i = 0; i < test_size; i++) {
		if (mem[i] != (base + (i * 4))) {
			error("DRAM test failed at 0x%08x: expected 0x%08x, got 0x%08x\r\n",
			      base + (i * 4), base + (i * 4), mem[i]);
			return 0;
		}
	}

	debug("DRAM test passed: %dMB at 0x%08x\r\n", size_mb, base);
	return 1;
}

/*
 * Detect DRAM size by probing
 * Returns: size in MB
 */
u32 dram_detect_size(u32 base, u32 max_size_mb)
{
	u32 size = max_size_mb;
	volatile u32 *mem = (volatile u32 *)base;
	u32 pattern = 0xaa55aa55;

	/* Write pattern at base */
	mem[0] = pattern;

	/* Check for aliasing at power-of-2 boundaries */
	while (size > 1) {
		u32 offset = (size / 2) * (1024 * 1024 / 4); /* Words */
		mem[offset] = ~pattern;

		if (mem[0] != pattern) {
			/* Aliasing detected, reduce size */
			size /= 2;
			mem[0] = pattern;
		} else {
			break;
		}
	}

	return size;
}
