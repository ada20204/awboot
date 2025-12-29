/*
 * V3S startup code for awboot
 * Cortex-A7 architecture
 *
 * SPDX-License-Identifier: MIT
 */

#include <arch/arm32/include/linkage.h>

#define ARMV7_USR_MODE        0x10
#define ARMV7_FIQ_MODE        0x11
#define ARMV7_IRQ_MODE        0x12
#define ARMV7_SVC_MODE        0x13
#define ARMV7_MON_MODE        0x16
#define ARMV7_ABT_MODE        0x17
#define ARMV7_UND_MODE        0x1b
#define ARMV7_SYSTEM_MODE     0x1f
#define ARMV7_MODE_MASK       0x1f
#define ARMV7_FIQ_MASK        0x40
#define ARMV7_IRQ_MASK        0x80

.arm
.globl reset
.text

reset:
	/* Boot head information for BROM - eGON.BT0 header */
	.long 0xea000016                                /* Jump instruction */
	.byte 'e', 'G', 'O', 'N', '.', 'B', 'T', '0'    /* Magic */
	.long 0x12345678                                /* Checksum (filled by mksunxi) */
	.long __spl_size                                /* SPL size */
	.long 0x30                                      /* boot header size */
	.long 0x30303033                                /* boot header version */
	.long 0x00020000                                /* return value */
	.long 0x00028000                                /* run address */
	.long 0x0                                       /* eGON version */
	.byte 0x00, 0x00, 0x00, 0x00                    /* platform information - 8byte */
	.byte 0x34, 0x2e, 0x30, 0x00

/*
 * The actual reset code
 */
	mrs r0, cpsr
	bic r0, r0, #ARMV7_MODE_MASK
	orr r0, r0, #ARMV7_SVC_MODE
	orr r0, r0, #(ARMV7_IRQ_MASK | ARMV7_FIQ_MASK)
	bic r0, r0, #(1<<9)     @set little-endian
	msr cpsr_c, r0

/* Set vector base address register */
	ldr r0, =_vector
	mcr p15, 0, r0, c12, c0, 0
	mrc p15, 0, r0, c1, c0, 0
	bic r0, #(1 << 13)
	mcr p15, 0, r0, c1, c0, 0

	mrc p15, 0, r0, c1, c0, 0
	bic r0, r0, #0x00002000     @ clear bits 13 (--V-)
	bic r0, r0, #0x00000007     @ clear bits 2:0 (-CAM)
	orr r0, r0, #0x00000800     @ set bit 11 (Z---) BTB
	bic r0, r0, #0x00001000     @ clear bit 12 (I) I-cache
	mcr p15, 0, r0, c1, c0, 0

	/* Enable neon/vfp unit */
	mrc p15, 0, r0, c1, c0, 2
	orr r0, r0, #(0xf << 20)
	mcr p15, 0, r0, c1, c0, 2
	isb
	mov r0, #0x40000000
	vmsr fpexc, r0

	/* Set stack pointer */
	ldr sp, =__stack_srv_end

	bl clear_bss

	/* Disable interrupts, set SVC mode */
	mrs r0, cpsr
	and r1, r0, #0x1f
	teq r1, #0x1a
	bicne r0, r0, #0x1f
	orrne r0, r0, #0x13
	orr r0, r0, #0xc0
	msr cpsr, r0

	/* Set cntfrq to 24M */
	ldr r0, =24000000
	mcr p15, 0, r0, c14, c0, 0

	bl main
	b .

clear_bss:
	ldr r0, =_sbss
	ldr r1, =_ebss
	mov r2, #0
1:
	cmp r0, r1
	strlt r2, [r0], #4
	blt 1b
	mov pc, lr

_vector:
	b reset
	ldr pc, _undefined_instruction
	ldr pc, _software_interrupt
	ldr pc, _prefetch_abort
	ldr pc, _data_abort
	ldr pc, _not_used
	ldr pc, _irq
	ldr pc, _fiq

_undefined_instruction:
	.word undefined_instruction
_software_interrupt:
	.word software_interrupt
_prefetch_abort:
	.word prefetch_abort
_data_abort:
	.word data_abort
_not_used:
	.word not_used
_irq:
	.word irq
_fiq:
	.word fiq

/*
 * Exception handlers (minimal stubs)
 */
	.align 5
undefined_instruction:
	b .

	.align 5
software_interrupt:
	b .

	.align 5
prefetch_abort:
	b .

	.align 5
data_abort:
	b .

	.align 5
not_used:
	b .

	.align 5
irq:
	b .

	.align 5
fiq:
	b .
