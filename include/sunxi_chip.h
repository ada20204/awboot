/*
 * sunxi_chip.h - Allwinner SoC chip descriptor framework
 *
 * This header defines the chip descriptor structure that contains
 * all hardware-specific parameters for each supported SoC.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __SUNXI_CHIP_H__
#define __SUNXI_CHIP_H__

#include "types.h"

/*
 * CPU Architecture types
 */
enum sunxi_cpu_arch {
	SUNXI_CPU_ARM926EJS,    /* F1C100S, F1C200S */
	SUNXI_CPU_CORTEX_A7,    /* V3S, H3, T113, R528 */
	SUNXI_CPU_CORTEX_A8,    /* A10 */
};

/*
 * DRAM types
 */
enum sunxi_dram_type {
	SUNXI_DRAM_SDR,
	SUNXI_DRAM_DDR,
	SUNXI_DRAM_DDR2,
	SUNXI_DRAM_DDR3,
	SUNXI_DRAM_LPDDR2,
	SUNXI_DRAM_LPDDR3,
};

/*
 * Memory map descriptor
 */
struct sunxi_memmap {
	u32 sram_base;          /* Internal SRAM base */
	u32 sram_size;          /* Internal SRAM size */
	u32 dram_base;          /* External DRAM base */
	u32 dram_max_size;      /* Maximum DRAM size */
};

/*
 * CCU (Clock Control Unit) descriptor
 */
struct sunxi_ccu_desc {
	u32 base;               /* CCU base address */

	/* PLL registers */
	u32 pll_cpu;            /* CPU PLL control */
	u32 pll_ddr;            /* DDR PLL control */
	u32 pll_periph;         /* Peripheral PLL control */

	/* Clock config registers */
	u32 cpu_clk_cfg;        /* CPU clock config */
	u32 ahb_apb_cfg;        /* AHB/APB clock config */

	/* Bus gate registers */
	u32 bus_gate0;          /* Bus clock gate 0 */
	u32 bus_gate1;          /* Bus clock gate 1 */
	u32 bus_gate2;          /* Bus clock gate 2 */

	/* Reset registers */
	u32 bus_reset0;         /* Bus reset 0 */
	u32 bus_reset1;         /* Bus reset 1 */
	u32 bus_reset2;         /* Bus reset 2 */

	/* DRAM clock */
	u32 dram_clk;           /* DRAM clock config */
	u32 dram_gate;          /* DRAM clock gate */
};

/*
 * DRAM controller descriptor
 */
struct sunxi_dram_desc {
	u32 base;               /* DRAM controller base */
	u32 phy_base;           /* DRAM PHY base (if separate) */
	enum sunxi_dram_type type;
	u32 default_clk;        /* Default DRAM clock in Hz */
};

/*
 * UART descriptor
 */
struct sunxi_uart_desc {
	u32 base;               /* UART base address */
	u32 irq;                /* IRQ number */
	u8  clk_gate_bit;       /* Clock gate bit */
	u8  reset_bit;          /* Reset bit */
	u8  tx_pin;             /* TX GPIO pin */
	u8  rx_pin;             /* RX GPIO pin */
};

/*
 * GPIO descriptor
 */
struct sunxi_gpio_desc {
	u32 base;               /* GPIO base address */
	u32 irq_base;           /* GPIO IRQ base */
	u8  port_count;         /* Number of GPIO ports */
};

/*
 * Main chip descriptor
 */
struct sunxi_chip_desc {
	const char *name;               /* Chip name (e.g., "F1C100S") */
	enum sunxi_cpu_arch cpu_arch;   /* CPU architecture */
	u32 cpu_max_freq;               /* Max CPU frequency in Hz */

	struct sunxi_memmap memmap;     /* Memory map */
	struct sunxi_ccu_desc ccu;      /* Clock control unit */
	struct sunxi_dram_desc dram;    /* DRAM controller */
	struct sunxi_gpio_desc gpio;    /* GPIO controller */
	struct sunxi_uart_desc uart[4]; /* UART controllers */
};

/*
 * Get current chip descriptor
 * Implemented in each mach-*/chip_desc.c
 */
extern const struct sunxi_chip_desc *sunxi_get_chip_desc(void);

/*
 * Convenience macros
 */
#define CHIP_DESC()         sunxi_get_chip_desc()
#define CHIP_CCU_BASE()     (CHIP_DESC()->ccu.base)
#define CHIP_DRAM_BASE()    (CHIP_DESC()->dram.base)
#define CHIP_GPIO_BASE()    (CHIP_DESC()->gpio.base)

#endif /* __SUNXI_CHIP_H__ */
