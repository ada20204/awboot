/*
 * boot_linux.c - Linux kernel boot support for awboot
 *
 * SPDX-License-Identifier: MIT
 */

#include "main.h"
#include "arm32.h"
#include "debug.h"

/* Linux zImage Header */
#define LINUX_ZIMAGE_MAGIC 0x016f2818

typedef struct {
	unsigned int code[9];
	unsigned int magic;
	unsigned int start;
	unsigned int end;
} linux_zimage_header_t;

/**
 * boot_image_setup - Setup Linux zImage boot parameters
 * @addr: Image load address
 * @entry: Output entry point address
 *
 * Returns: 0 on success, -1 on failure
 */
int boot_image_setup(unsigned char *addr, unsigned int *entry)
{
	linux_zimage_header_t *zimage_header = (linux_zimage_header_t *)addr;

	if (zimage_header->magic == LINUX_ZIMAGE_MAGIC) {
		*entry = ((unsigned int)addr + zimage_header->start);
		return 0;
	}

	error("unsupported kernel image\r\n");
	return -1;
}

/**
 * boot_linux - Boot Linux kernel
 * @image: Image info structure containing load addresses
 *
 * Boot parameters:
 *   r0 = 0
 *   r1 = ~0 (machine ID, -1 for device tree boot)
 *   r2 = DTB address
 *
 * Returns: Should never return on success
 */
int boot_linux(image_info_t *image)
{
	unsigned int entry_point = 0;
	void (*kernel_entry)(int zero, int arch, unsigned int params);

	if (boot_image_setup(image->dest, &entry_point)) {
		error("Linux: boot setup failed\r\n");
		return -1;
	}

	info("Linux: entry=0x%08x, dtb=0x%08x\r\n",
	     entry_point, (unsigned int)image->of_dest);

	/* Disable MMU, caches, interrupts before jumping */
	arm32_mmu_disable();
	arm32_dcache_disable();
	arm32_icache_disable();
	arm32_interrupt_disable();

	/* Jump to Linux: r0=0, r1=~0, r2=DTB */
	kernel_entry = (void (*)(int, int, unsigned int))entry_point;
	kernel_entry(0, ~0, (unsigned int)image->of_dest);

	/* Should never reach here */
	return -1;
}
