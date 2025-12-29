/*
 * boot_nuttx.c - NuttX RTOS boot support for awboot
 *
 * SPDX-License-Identifier: MIT
 */

#include "main.h"
#include "arm32.h"
#include "debug.h"

/**
 * detect_image_type - Detect image type from EGON header magic
 * @addr: Image load address
 *
 * Returns: IMAGE_TYPE_NUTTX, IMAGE_TYPE_LINUX, or IMAGE_TYPE_UNKNOWN
 */
image_type_t detect_image_type(unsigned char *addr)
{
	struct egon_header_t *hdr = (struct egon_header_t *)addr;

	/* Check for NuttX magic */
	if (memcmp(hdr->magic, EGON_MAGIC_NUTTX, 8) == 0) {
		return IMAGE_TYPE_NUTTX;
	}

	/* Check for Linux magic (legacy support) */
	if (memcmp(hdr->magic, EGON_MAGIC_LINUX, 8) == 0) {
		return IMAGE_TYPE_LINUX;
	}

	return IMAGE_TYPE_UNKNOWN;
}

/**
 * boot_nuttx - Boot NuttX RTOS image
 * @image: Image info structure containing load addresses
 *
 * NuttX images have EGON header prepended. Entry point is after the header.
 * Boot parameters:
 *   r0 = 0
 *   r1 = 0 (NuttX doesn't use machine ID)
 *   r2 = DTB address (optional, may be 0)
 *
 * Returns: Should never return on success
 */
int boot_nuttx(image_info_t *image)
{
	struct egon_header_t *hdr = (struct egon_header_t *)image->dest;
	void (*entry)(int, int, unsigned int);
	unsigned int entry_addr;

	/* Verify magic */
	if (memcmp(hdr->magic, EGON_MAGIC_NUTTX, 8) != 0) {
		error("NuttX: invalid magic\r\n");
		return -1;
	}

	/* Entry point is after EGON header */
	entry_addr = (unsigned int)image->dest + EGON_HEADER_SIZE;
	entry = (void (*)(int, int, unsigned int))entry_addr;

	info("NuttX: entry=0x%08x, dtb=0x%08x\r\n",
	     entry_addr, (unsigned int)image->of_dest);

	/* Disable MMU, caches, interrupts before jumping */
	arm32_mmu_disable();
	arm32_dcache_disable();
	arm32_icache_disable();
	arm32_interrupt_disable();

	/* Jump to NuttX: r0=0, r1=0, r2=DTB */
	entry(0, 0, (unsigned int)image->of_dest);

	/* Should never reach here */
	return -1;
}
