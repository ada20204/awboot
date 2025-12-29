/*
 * ARM926EJ-S startup code for awboot
 * Shared by: F1C100S, F1C200S
 *
 * SPDX-License-Identifier: MIT
 */

#include <arch/arm32/include/linkage.h>

.arm
.globl reset
.text

reset:
	/* Boot head information for BROM - eGON.BT0 header */
	.long 0xea000016                                /* Jump instruction */
	.byte 'e', 'G', 'O', 'N', '.', 'B', 'T', '0'    /* Magic */
	.long 0x12345678                                /* Checksum (filled by mksunxi) */
	.long __spl_size                                /* SPL size */
	.byte 'S', 'P', 'L', 2                          /* SPL signature */
	.long 0, 0                                      /* fel_script_address, fel_uenv_length */
	.long 0, 0                                      /* dt_name_offset, reserved1 */
	.long 0                                         /* boot_media */
	.long 0, 0, 0, 0, 0, 0, 0, 0                    /* string_pool[0-7] */
	.long 0, 0, 0, 0, 0                             /* string_pool[8-12] */

_start:
	/* Enter SVC mode and disable interrupts */
	mrs r0, cpsr
	bic r0, r0, #0x1f
	orr r0, r0, #0xd3
	msr cpsr, r0

	/* Set vector to the low address */
	mrc p15, 0, r0, c1, c0, 0
	bic r0, #(1 << 13)
	mcr p15, 0, r0, c1, c0, 0

	/* Copy vector to 0x00000000 */
	adr r0, _vector
	ldr r1, =0x00000000
	ldmia r0!, {r2-r8, r10}
	stmia r1!, {r2-r8, r10}
	ldmia r0!, {r2-r8, r10}
	stmia r1!, {r2-r8, r10}

	ldr sp, =__stack_srv_end
	bl clear_bss
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

_undefined_instruction:	.word undefined_instruction
_software_interrupt:	.word software_interrupt
_prefetch_abort:	.word prefetch_abort
_data_abort:		.word data_abort
_not_used:		.word not_used
_irq:			.word irq
_fiq:			.word fiq

	.align 5
undefined_instruction:
software_interrupt:
prefetch_abort:
data_abort:
not_used:
irq:
fiq:
	b .
