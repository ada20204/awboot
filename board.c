#include "main.h"
#include "board.h"
#include "sunxi_gpio.h"
#include "sunxi_sdhci.h"
#include "sunxi_usart.h"
#include "sunxi_spi.h"
#include "sdmmc.h"

// #define ARM_V3S
// #define ARM_R528S3
// #define ARM_T113S3
#define ARM_H3
// #define ARM_F1C100S

#ifdef ARM_V3S
sunxi_usart_t usart0_dbg = {
	.base	 = 0x01C28000,
	.id		 = 0,
	.gpio_tx = {GPIO_PIN(PORTB, 8), GPIO_PERIPH_MUX3},
	.gpio_rx = {GPIO_PIN(PORTB, 9), GPIO_PERIPH_MUX3},
};
sunxi_usart_t usart1_dbg = {
	.base	 = 0x01C28400,
	.id		 = 1,
	.gpio_tx = {GPIO_PIN(PORTE, 21), GPIO_PERIPH_MUX4},
	.gpio_rx = {GPIO_PIN(PORTE, 22), GPIO_PERIPH_MUX4},
};
sunxi_usart_t usart2_dbg = {
	.base	 = 0x01C28800,
	.id		 = 2,
	.gpio_tx = {GPIO_PIN(PORTB, 0), GPIO_PERIPH_MUX2},
	.gpio_rx = {GPIO_PIN(PORTB, 1), GPIO_PERIPH_MUX2},
};
sunxi_spi_t sunxi_spi0 = {
	.base	   = 0x01C68000,
	.id		   = 0,
	.clk_rate  = 100 * 1000 * 1000,
	.gpio_miso = {GPIO_PIN(PORTC, 0), GPIO_PERIPH_MUX3},
	.gpio_sck  = {GPIO_PIN(PORTC, 1), GPIO_PERIPH_MUX3},
	.gpio_cs   = {GPIO_PIN(PORTC, 2), GPIO_PERIPH_MUX3},
	.gpio_mosi = {GPIO_PIN(PORTC, 3), GPIO_PERIPH_MUX3},
	.gpio_wp   = {0},
	.gpio_hold = {0},
};
sdhci_t sdhci0 = {
	.name	   = "sdhci0",
	.reg	   = (sdhci_reg_t *)0x01C0F000,
	.voltage   = MMC_VDD_27_36,
	.width	   = MMC_BUS_WIDTH_4,
	.clock	   = MMC_CLK_50M,
	.removable = 0,
	.isspi	   = FALSE,
	.gpio_clk  = {GPIO_PIN(PORTF, 2), GPIO_PERIPH_MUX2},
	.gpio_cmd  = {GPIO_PIN(PORTF, 3), GPIO_PERIPH_MUX2},
	.gpio_d0   = {GPIO_PIN(PORTF, 1), GPIO_PERIPH_MUX2},
	.gpio_d1   = {GPIO_PIN(PORTF, 0), GPIO_PERIPH_MUX2},
	.gpio_d2   = {GPIO_PIN(PORTF, 5), GPIO_PERIPH_MUX2},
	.gpio_d3   = {GPIO_PIN(PORTF, 4), GPIO_PERIPH_MUX2},
};
// static gpio_t led_red = GPIO_PIN(PORTG, 0);
// static gpio_t led_green = GPIO_PIN(PORTG, 1);
static gpio_t led_blue = GPIO_PIN(PORTG, 2);
#endif // ARM_V3S

#ifdef ARM_R528S3
#define _RAM_BASE 0x00020000
#define _FEL_RAM_BASE 0x00030000

sunxi_usart_t usart0_dbg = {
	.base	 = 0x02500000,
	.id		 = 0,
	.gpio_tx = {GPIO_PIN(PORTB, 0), GPIO_PERIPH_MUX6},
	.gpio_rx = {GPIO_PIN(PORTB, 1), GPIO_PERIPH_MUX6},
};

sunxi_usart_t usart1_dbg = {
	.base	 = 0x02500400,
	.id		 = 1,
	.gpio_tx = {GPIO_PIN(PORTG, 6), GPIO_PERIPH_MUX2},
	.gpio_rx = {GPIO_PIN(PORTG, 7), GPIO_PERIPH_MUX2},
};

sunxi_usart_t usart2_dbg = {
	.base	 = 0x02500800,
	.id		 = 2,
	.gpio_tx = {GPIO_PIN(PORTC, 0), GPIO_PERIPH_MUX2},
	.gpio_rx = {GPIO_PIN(PORTC, 1), GPIO_PERIPH_MUX2},
};

sunxi_spi_t sunxi_spi0 = {
	.base	   = 0x04025000,
	.id		   = 0,
	.clk_rate  = 100 * 1000 * 1000,
	.gpio_sck  = {GPIO_PIN(PORTC, 2), GPIO_PERIPH_MUX2},
	.gpio_cs   = {GPIO_PIN(PORTC, 3), GPIO_PERIPH_MUX2},
	.gpio_mosi = {GPIO_PIN(PORTC, 4), GPIO_PERIPH_MUX2},
	.gpio_miso = {GPIO_PIN(PORTC, 5), GPIO_PERIPH_MUX2},
	.gpio_wp   = {GPIO_PIN(PORTC, 6), GPIO_PERIPH_MUX2},
	.gpio_hold = {GPIO_PIN(PORTC, 7), GPIO_PERIPH_MUX2},
};

sdhci_t sdhci0 = {
	.name	   = "sdhci0",
	.reg	   = (sdhci_reg_t *)0x04020000,
	.voltage   = MMC_VDD_27_36,
	.width	   = MMC_BUS_WIDTH_4,
	.clock	   = MMC_CLK_50M,
	.removable = 0,
	.isspi	   = FALSE,
	.gpio_clk  = {GPIO_PIN(PORTF, 2), GPIO_PERIPH_MUX2},
	.gpio_cmd  = {GPIO_PIN(PORTF, 3), GPIO_PERIPH_MUX2},
	.gpio_d0   = {GPIO_PIN(PORTF, 1), GPIO_PERIPH_MUX2},
	.gpio_d1   = {GPIO_PIN(PORTF, 0), GPIO_PERIPH_MUX2},
	.gpio_d2   = {GPIO_PIN(PORTF, 5), GPIO_PERIPH_MUX2},
	.gpio_d3   = {GPIO_PIN(PORTF, 4), GPIO_PERIPH_MUX2},
};

static gpio_t led_blue = GPIO_PIN(PORTD, 22);
#endif // ARM_R528S3

#ifdef ARM_T113S3
#define _RAM_BASE 0x00020000
#define _FEL_RAM_BASE 0x00030000

sunxi_usart_t usart0_dbg = {
	.base	 = 0x02500000,
	.id		 = 0,
	.gpio_tx = {GPIO_PIN(PORTE, 2), GPIO_PERIPH_MUX6},
	.gpio_rx = {GPIO_PIN(PORTE, 3), GPIO_PERIPH_MUX6},
};

sunxi_usart_t usart3_dbg = {
	.base	 = 0x02500c00,
	.id		 = 3,
	.gpio_tx = {GPIO_PIN(PORTB, 6), GPIO_PERIPH_MUX7},
	.gpio_rx = {GPIO_PIN(PORTB, 7), GPIO_PERIPH_MUX7},
};

sunxi_usart_t usart5_dbg = {
	.base	 = 0x02501400,
	.id		 = 5,
	.gpio_tx = {GPIO_PIN(PORTB, 4), GPIO_PERIPH_MUX7},
	.gpio_rx = {GPIO_PIN(PORTB, 5), GPIO_PERIPH_MUX7},
};

sunxi_spi_t sunxi_spi0 = {
	.base	   = 0x04025000,
	.id		   = 0,
	.clk_rate  = 100 * 1000 * 1000,
	.gpio_sck  = {GPIO_PIN(PORTC, 2), GPIO_PERIPH_MUX2},
	.gpio_cs   = {GPIO_PIN(PORTC, 3), GPIO_PERIPH_MUX2},
	.gpio_mosi = {GPIO_PIN(PORTC, 4), GPIO_PERIPH_MUX2},
	.gpio_miso = {GPIO_PIN(PORTC, 5), GPIO_PERIPH_MUX2},
	.gpio_wp   = {GPIO_PIN(PORTC, 6), GPIO_PERIPH_MUX2},
	.gpio_hold = {GPIO_PIN(PORTC, 7), GPIO_PERIPH_MUX2},
};

sdhci_t sdhci0 = {
	.name	   = "sdhci0",
	.reg	   = (sdhci_reg_t *)0x04020000,
	.voltage   = MMC_VDD_27_36,
	.width	   = MMC_BUS_WIDTH_4,
	.clock	   = MMC_CLK_50M,
	.removable = 0,
	.isspi	   = FALSE,
	.gpio_clk  = {GPIO_PIN(PORTF, 2), GPIO_PERIPH_MUX2},
	.gpio_cmd  = {GPIO_PIN(PORTF, 3), GPIO_PERIPH_MUX2},
	.gpio_d0   = {GPIO_PIN(PORTF, 1), GPIO_PERIPH_MUX2},
	.gpio_d1   = {GPIO_PIN(PORTF, 0), GPIO_PERIPH_MUX2},
	.gpio_d2   = {GPIO_PIN(PORTF, 5), GPIO_PERIPH_MUX2},
	.gpio_d3   = {GPIO_PIN(PORTF, 4), GPIO_PERIPH_MUX2},
};

static gpio_t led_blue = GPIO_PIN(PORTD, 22);

#endif // ARM_T113S3

#ifdef ARM_H3
// #define _RAM_BASE 0x00000000
// #define _FEL_RAM_BASE 0x00008000
// #define _FEL_RAM_BASE 0x00010000
// #define _FEL_RAM_BASE 0x00044000
sunxi_usart_t usart0_dbg = {
	.base	 = 0x01C28000,
	.id		 = 0,
	.gpio_tx = {GPIO_PIN(PORTA, 4), GPIO_PERIPH_MUX2},
	.gpio_rx = {GPIO_PIN(PORTA, 5), GPIO_PERIPH_MUX2},
};
sunxi_spi_t sunxi_spi0 = {
	.base	   = 0x01C68000,
	.id		   = 0,
	.clk_rate  = 100 * 1000 * 1000,
	.gpio_miso = {GPIO_PIN(PORTC, 0), GPIO_PERIPH_MUX3},
	.gpio_sck  = {GPIO_PIN(PORTC, 1), GPIO_PERIPH_MUX3},
	.gpio_cs   = {GPIO_PIN(PORTC, 2), GPIO_PERIPH_MUX3},
	.gpio_mosi = {GPIO_PIN(PORTC, 3), GPIO_PERIPH_MUX3},
	.gpio_wp   = {0},
	.gpio_hold = {0},
};
sdhci_t sdhci0 = {
	.name	   = "sdhci0",
	.reg	   = (sdhci_reg_t *)0x01C0F000,
	.voltage   = MMC_VDD_27_36,
	.width	   = MMC_BUS_WIDTH_4,
	.clock	   = MMC_CLK_50M,
	.removable = 0,
	.isspi	   = FALSE,
	.gpio_clk  = {GPIO_PIN(PORTF, 2), GPIO_PERIPH_MUX2},
	.gpio_cmd  = {GPIO_PIN(PORTF, 3), GPIO_PERIPH_MUX2},
	.gpio_d0   = {GPIO_PIN(PORTF, 1), GPIO_PERIPH_MUX2},
	.gpio_d1   = {GPIO_PIN(PORTF, 0), GPIO_PERIPH_MUX2},
	.gpio_d2   = {GPIO_PIN(PORTF, 5), GPIO_PERIPH_MUX2},
	.gpio_d3   = {GPIO_PIN(PORTF, 4), GPIO_PERIPH_MUX2},
};
// static gpio_t led_red = GPIO_PIN(PORTA, 17);
// static gpio_t led_green = GPIO_PIN(PORTL, 10);
static gpio_t led_blue = GPIO_PIN(PORTA, 10);
#endif // ARM_H3

#ifdef ARM_F1C100S
#define _RAM_BASE 0x00000000
#define _FEL_RAM_BASE 0x00010000

sunxi_usart_t usart0_dbg = {
	.base	 = 0x01C28000,
	.id		 = 0,
	.gpio_tx = {GPIO_PIN(PORTE, 1), GPIO_PERIPH_MUX5},
	.gpio_rx = {GPIO_PIN(PORTE, 0), GPIO_PERIPH_MUX5},
};
sunxi_spi_t sunxi_spi0 = {
	.base	   = 0x01C68000,
	.id		   = 0,
	.clk_rate  = 100 * 1000 * 1000,
	.gpio_miso = {GPIO_PIN(PORTC, 0), GPIO_PERIPH_MUX3},
	.gpio_sck  = {GPIO_PIN(PORTC, 1), GPIO_PERIPH_MUX3},
	.gpio_cs   = {GPIO_PIN(PORTC, 2), GPIO_PERIPH_MUX3},
	.gpio_mosi = {GPIO_PIN(PORTC, 3), GPIO_PERIPH_MUX3},
	.gpio_wp   = {0},
	.gpio_hold = {0},
};
sdhci_t sdhci0 = {
	.name	   = "sdhci0",
	.reg	   = (sdhci_reg_t *)0x01C0F000,
	.voltage   = MMC_VDD_27_36,
	.width	   = MMC_BUS_WIDTH_4,
	.clock	   = MMC_CLK_50M,
	.removable = 0,
	.isspi	   = FALSE,
	.gpio_clk  = {GPIO_PIN(PORTF, 2), GPIO_PERIPH_MUX2},
	.gpio_cmd  = {GPIO_PIN(PORTF, 3), GPIO_PERIPH_MUX2},
	.gpio_d0   = {GPIO_PIN(PORTF, 1), GPIO_PERIPH_MUX2},
	.gpio_d1   = {GPIO_PIN(PORTF, 0), GPIO_PERIPH_MUX2},
	.gpio_d2   = {GPIO_PIN(PORTF, 5), GPIO_PERIPH_MUX2},
	.gpio_d3   = {GPIO_PIN(PORTF, 4), GPIO_PERIPH_MUX2},
};
// static gpio_t led_red = GPIO_PIN(PORTA, 17);
// static gpio_t led_green = GPIO_PIN(PORTL, 10);
static gpio_t led_blue = GPIO_PIN(PORTG, 2);
#endif // ARM_F1C100S


void board_init_led(gpio_t led)
{
	sunxi_gpio_init(led, GPIO_OUTPUT);
	sunxi_gpio_set_value(led, 0);
}

int board_sdhci_init()
{
	sunxi_sdhci_init(&sdhci0);
	return sdmmc_init(&card0, &sdhci0);
}

void board_init()
{
	board_init_led(led_blue);
	sunxi_usart_init(&USART_DBG);
}
