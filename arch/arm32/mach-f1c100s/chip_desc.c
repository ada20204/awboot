/*
 * F1C100S chip descriptor
 *
 * SPDX-License-Identifier: MIT
 */

#include "sunxi_chip.h"

static const struct sunxi_chip_desc f1c100s_chip = {
	.name = "F1C100S",
	.cpu_arch = SUNXI_CPU_ARM926EJS,
	.cpu_max_freq = 720000000,  /* 720 MHz */

	.memmap = {
		.sram_base = 0x00000000,
		.sram_size = 32 * 1024,     /* 32KB */
		.dram_base = 0x80000000,
		.dram_max_size = 64 * 1024 * 1024,  /* 64MB max */
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
		.dram_clk = 0x020,      /* PLL_DDR_CTRL */
		.dram_gate = 0x100,
	},

	.dram = {
		.base = 0x01c01000,
		.phy_base = 0,          /* No separate PHY */
		.type = SUNXI_DRAM_DDR,
		.default_clk = 156000000,  /* 156 MHz */
	},

	.gpio = {
		.base = 0x01c20800,
		.irq_base = 0,
		.port_count = 6,        /* PA-PF */
	},

	.uart = {
		[0] = {
			.base = 0x01c25000,
			.irq = 1,
			.clk_gate_bit = 20,
			.reset_bit = 20,
			.tx_pin = 0,        /* PE0 */
			.rx_pin = 1,        /* PE1 */
		},
		[1] = {
			.base = 0x01c25400,
			.irq = 2,
			.clk_gate_bit = 21,
			.reset_bit = 21,
			.tx_pin = 0,
			.rx_pin = 0,
		},
		[2] = {
			.base = 0x01c25800,
			.irq = 3,
			.clk_gate_bit = 22,
			.reset_bit = 22,
			.tx_pin = 0,
			.rx_pin = 0,
		},
	},
};

const struct sunxi_chip_desc *sunxi_get_chip_desc(void)
{
	return &f1c100s_chip;
}
