/*
 * H3 chip descriptor
 *
 * SPDX-License-Identifier: MIT
 */

#include "sunxi_chip.h"

static const struct sunxi_chip_desc h3_chip = {
	.name = "H3",
	.cpu_arch = SUNXI_CPU_CORTEX_A7,
	.cpu_max_freq = 1200000000,  /* 1.2 GHz */

	.memmap = {
		.sram_base = 0x00000000,
		.sram_size = 64 * 1024,     /* 64KB A1 + A2 */
		.dram_base = 0x40000000,
		.dram_max_size = 2048UL * 1024 * 1024,  /* 2GB max */
	},

	.ccu = {
		.base = 0x01c20000,
		.pll_cpu = 0x000,
		.pll_ddr = 0x020,
		.pll_periph = 0x028,
		.cpu_clk_cfg = 0x050,
		.ahb_apb_cfg = 0x054,
		.bus_gate0 = 0x060,
		.bus_gate1 = 0x064,
		.bus_gate2 = 0x068,
		.bus_reset0 = 0x2c0,
		.bus_reset1 = 0x2c4,
		.bus_reset2 = 0x2d0,
		.dram_clk = 0x020,
		.dram_gate = 0x100,
	},

	.dram = {
		.base = 0x01c62000,
		.phy_base = 0x01c63000,
		.type = SUNXI_DRAM_DDR3,
		.default_clk = 672000000,  /* 672 MHz */
	},

	.gpio = {
		.base = 0x01c20800,
		.irq_base = 0,
		.port_count = 7,
	},

	.uart = {
		[0] = {
			.base = 0x01c28000,
			.irq = 32,
			.clk_gate_bit = 16,
			.reset_bit = 16,
		},
	},
};

const struct sunxi_chip_desc *sunxi_get_chip_desc(void)
{
	return &h3_chip;
}
