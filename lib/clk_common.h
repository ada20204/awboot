/*
 * clk_common.h - Common clock definitions for awboot
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __CLK_COMMON_H__
#define __CLK_COMMON_H__

#include "types.h"
#include "io.h"

/*
 * Common PLL lock bit position
 */
#define PLL_LOCK_BIT        28
#define PLL_ENABLE_BIT      31

/*
 * Common timeout for PLL operations
 */
#define PLL_TIMEOUT_DEFAULT 0xfff

/*
 * Wait for PLL to lock
 * Returns: 1 on success, 0 on timeout
 */
static inline int clk_wait_pll_lock(u32 pll_reg)
{
	u32 timeout = PLL_TIMEOUT_DEFAULT;

	while (timeout--) {
		if (read32(pll_reg) & (1 << PLL_LOCK_BIT))
			return 1;
	}
	return 0;
}

/*
 * Enable PLL
 */
static inline void clk_pll_enable(u32 pll_reg)
{
	u32 val = read32(pll_reg);
	val |= (1U << PLL_ENABLE_BIT);
	write32(pll_reg, val);
}

/*
 * Disable PLL
 */
static inline void clk_pll_disable(u32 pll_reg)
{
	u32 val = read32(pll_reg);
	val &= ~(1U << PLL_ENABLE_BIT);
	write32(pll_reg, val);
}

/*
 * Clock gate operations
 */
static inline void clk_gate_enable(u32 gate_reg, u32 bit)
{
	u32 val = read32(gate_reg);
	val |= (1 << bit);
	write32(gate_reg, val);
}

static inline void clk_gate_disable(u32 gate_reg, u32 bit)
{
	u32 val = read32(gate_reg);
	val &= ~(1 << bit);
	write32(gate_reg, val);
}

/*
 * Reset operations
 */
static inline void clk_reset_assert(u32 reset_reg, u32 bit)
{
	u32 val = read32(reset_reg);
	val &= ~(1 << bit);
	write32(reset_reg, val);
}

static inline void clk_reset_deassert(u32 reset_reg, u32 bit)
{
	u32 val = read32(reset_reg);
	val |= (1 << bit);
	write32(reset_reg, val);
}

/*
 * Common clock source selection
 */
enum clk_source {
	CLK_SRC_LOSC    = 0,  /* 32.768 kHz */
	CLK_SRC_OSC24M  = 1,  /* 24 MHz */
	CLK_SRC_PLL     = 2,  /* PLL output */
};

/*
 * PLL configuration structure
 */
struct pll_config {
	u32 freq;       /* Target frequency in Hz */
	u8  n;          /* N factor */
	u8  k;          /* K factor (if applicable) */
	u8  m;          /* M divider */
	u8  p;          /* P divider (if applicable) */
};

#endif /* __CLK_COMMON_H__ */
