#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "string.h"
#include "io.h"
#include "types.h"
#include "debug.h"

#define ARRAY_SIZE(array) (sizeof(array) / sizeof((array)[0]))

#define ALIGN(size, align) (((size) + (align)-1) & (~((align)-1)))
#define OF_ALIGN(size)	   ALIGN(size, 4)

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

#ifndef NULL
#define NULL 0
#endif

#define FALSE 0
#define TRUE  1

/* EGON Header Magic - used by BROM to identify bootable images */
#define EGON_MAGIC_LINUX  "eGON.BT0"  /* Linux zImage */
#define EGON_MAGIC_NUTTX  "eGON.NTX"  /* NuttX RTOS */

/* EGON Header Structure - prepended to NuttX images by mksunxi-nuttx */
struct egon_header_t {
	uint32_t instruction;      /* Jump instruction (0xea000016) */
	uint8_t  magic[8];         /* "eGON.BT0" or "eGON.NTX" */
	uint32_t checksum;         /* Checksum */
	uint32_t length;           /* Image length */
	uint8_t  spl_signature[4]; /* SPL signature */
	uint32_t fel_script_address;
	uint32_t fel_uenv_length;
	uint32_t dt_name_offset;
	uint32_t reserved1;
	uint32_t boot_media;
	uint32_t string_pool[13];
};

#define EGON_HEADER_SIZE sizeof(struct egon_header_t)

/* Image type enumeration */
typedef enum {
	IMAGE_TYPE_UNKNOWN = 0,
	IMAGE_TYPE_LINUX,
	IMAGE_TYPE_NUTTX,
} image_type_t;

static inline unsigned int swap_uint32(unsigned int data)
{
	volatile unsigned int a, b, c, d;

	a = ((data)&0xff000000) >> 24;
	b = ((data)&0x00ff0000) >> 8;
	c = ((data)&0x0000ff00) << 8;
	d = ((data)&0x000000ff) << 24;

	return a | b | c | d;
}

#define FILENAME_MAX_LEN 64
typedef struct {
	unsigned int   offset;
	unsigned int   length;
	unsigned char *dest;

	unsigned int   of_offset;
	unsigned char *of_dest;

	char filename[FILENAME_MAX_LEN];
	char of_filename[FILENAME_MAX_LEN];
} image_info_t;

void	 udelay(uint64_t us);
void	 mdelay(uint32_t ms);
void	 sdelay(uint32_t loops);
uint32_t time_ms(void);
uint64_t time_us(void);
uint64_t get_arch_counter(void);
void	 init_sp_irq(uint32_t addr);
void	 reset();

#endif
