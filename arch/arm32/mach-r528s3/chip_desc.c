/*
 * R528S3 chip descriptor
 *
 * SPDX-License-Identifier: MIT
 */

#include "sunxi_chip.h"

static const struct sunxi_chip_desc r528s3_chip = {
	.name = "R528S3",
	.cpu_arch = SUNXI_CPU_CORTEX_A7,
	.cpu_max_freq = 1200000000,  /* 1.2 GHz */

	.memmap = {
		.sram_base = 0x00020000,
		.sram_size = 160 * 1024,    /* 160KB */
		.dram_base = 0x40000000,
		.dram_max_size = 256 * 1024 * 1024,  /* 256MB max */
	},

	.ccu = {
		.base = 0x02001000,
		.pll_cpu = 0x000,
		.pll_ddr = 0x010,
		.pll_periph = 0x020,
		.cpu_clk_cfg = 0x500,
		.ahb_apb_cfg = 0x510,
		.bus_gate0 = 0x800,
		.bus_gate1 = 0x804,
		.bus_gate2 = 0x808,
		.bus_reset0 = 0x80c,
		.bus_reset1 = 0x810,
		.bus_reset2 = 0x814,
		.dram_clk = 0x800,
		.dram_gate = 0x80c,
	},

	.dram = {
		.base = 0x03000000,
		.phy_base = 0x03000000,
		.type = SUNXI_DRAM_DDR3,
		.default_clk = 792000000,
	},

	.gpio = {
		.base = 0x02000000,
		.irq_base = 0,
		.port_count = 7,
	},

	.uart = {
		[0] = {
			.base = 0x02500000,
			.irq = 34,
			.clk_gate_bit = 0,
			.reset_bit = 0,
		},
	},
};

const struct sunxi_chip_desc *sunxi_get_chip_desc(void)
{
	return &r528s3_chip;
}
