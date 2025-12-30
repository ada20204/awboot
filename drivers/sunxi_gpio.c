#include "main.h"
#include "debug.h"
#include "sunxi_gpio.h"

enum {
	GPIO_CFG0 = 0x00,
	GPIO_CFG1 = 0x04,
	GPIO_CFG2 = 0x08,
	GPIO_CFG3 = 0x0c,
	GPIO_DAT  = 0x10,
	GPIO_DRV0 = 0x14,
	GPIO_DRV1 = 0x18,
	GPIO_DRV2 = 0x1c,
	GPIO_DRV3 = 0x20,
	GPIO_PUL0 = 0x24,
	GPIO_PUL1 = 0x28,
};

static inline uint32_t _port_num(gpio_t pin)
{
	return pin >> PIO_NUM_IO_BITS;
}

static uint32_t _port_base_get(gpio_t pin)
{
	uint32_t port = pin >> PIO_NUM_IO_BITS;

#if defined(CONFIG_CHIP_H3) || defined(CONFIG_CHIP_V3S)
	/* H3/V3S use 0x01C2xxxx GPIO base */
	switch (port) {
		case PORTA: return 0x01C20800;
		case PORTB: return 0x01C20824;
		case PORTC: return 0x01C20848;
		case PORTD: return 0x01C2086C;
		case PORTE: return 0x01C20890;
		case PORTF: return 0x01C208B4;
		case PORTG: return 0x01C208D8;
	}
#else
	/* T113S3/R528S3/V851S/T113S4 use 0x0200xxxx GPIO base */
	switch (port) {
#if defined(CONFIG_CHIP_T113S3) || defined(CONFIG_CHIP_R528S3)
		case PORTA: return 0x02000000;
#endif
		case PORTB: return 0x02000030;
		case PORTC: return 0x02000060;
		case PORTD: return 0x02000090;
		case PORTE: return 0x020000c0;
		case PORTF: return 0x020000f0;
		case PORTG: return 0x02000120;
#if defined(CONFIG_CHIP_T113S3) || defined(CONFIG_CHIP_R528S3)
		case PORTH: return 0x02000150;
#endif
	}
#endif

	return 0;
}

static inline uint32_t _pin_num(gpio_t pin)
{
	return (pin & ((1 << PIO_NUM_IO_BITS) - 1));
}

void sunxi_gpio_init(gpio_t pin, int cfg)
{
	uint32_t port_addr = _port_base_get(pin);
	uint32_t pin_num   = _pin_num(pin);
	uint32_t addr;
	uint32_t val;

	addr = port_addr + GPIO_CFG0 + ((pin_num >> 3) << 2);
	val	 = read32(addr);
	val &= ~(0xf << ((pin_num & 0x7) << 2));
	val |= ((cfg & 0xf) << ((pin_num & 0x7) << 2));
	write32(addr, val);
}

void sunxi_gpio_set_value(gpio_t pin, int value)
{
	uint32_t port_addr = _port_base_get(pin);
	uint32_t pin_num   = _pin_num(pin);
	uint32_t val;

	val = read32(port_addr + GPIO_DAT);
	val &= ~(1 << pin_num);
	val |= (!!value) << pin_num;
	write32(port_addr + GPIO_DAT, val);
}

int sunxi_gpio_read(gpio_t pin)
{
	uint32_t port_addr = _port_base_get(pin);
	uint32_t pin_num   = _pin_num(pin);
	uint32_t val;

	val = read32(port_addr + GPIO_DAT);
	return !!(val & (1 << pin_num));
}

void sunxi_gpio_set_pull(gpio_t pin, enum gpio_pull_t pull)
{
	uint32_t port_addr = _port_base_get(pin);
	uint32_t pin_num   = _pin_num(pin);
	uint32_t addr;
	uint32_t val, v;

	switch (pull) {
		case GPIO_PULL_UP:
			v = 0x1;
			break;

		case GPIO_PULL_DOWN:
			v = 0x2;
			break;

		case GPIO_PULL_NONE:
			v = 0x0;
			break;

		default:
			v = 0x0;
			break;
	}

	addr = port_addr + GPIO_PUL0 + ((pin_num >> 4) << 2);
	val	 = read32(addr);
	val &= ~(v << ((pin_num & 0xf) << 1));
	val |= (v << ((pin_num & 0xf) << 1));
	write32(addr, val);
}
