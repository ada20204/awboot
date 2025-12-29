/*
 * mksunxi-nuttx.c - Generate NuttX image with eGON.NTX header
 *
 * Usage: mksunxi-nuttx <input.bin> <output.bin> <padding>
 *   padding: 512 for SD card, 8192 for SPI flash
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define __ALIGN_MASK(x, mask) (((x) + (mask)) & ~(mask))
#define ALIGN(x, a)           __ALIGN_MASK((x), (typeof(x))(a)-1)

#define EGON_MAGIC_NUTTX  "eGON.NTX"
#define BROM_PAGE_SIZE    2048

/* EGON Header - must match awboot main.h */
struct egon_header_t {
	uint32_t instruction;      /* Jump instruction */
	uint8_t  magic[8];         /* "eGON.NTX" */
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

/* ARM branch instruction: B +0x30 (skip header, jump to code) */
#define EGON_JUMP_INSTRUCTION 0xea00000b

static uint32_t calc_checksum(uint32_t *buf, uint32_t len)
{
	uint32_t sum = 0;
	uint32_t i;

	for (i = 0; i < len / 4; i++) {
		sum += buf[i];
	}
	return sum;
}

int main(int argc, char *argv[])
{
	FILE *fin, *fout;
	char *buffer;
	struct egon_header_t *hdr;
	int filelen, buflen, padding;
	uint32_t checksum;

	if (argc != 4) {
		printf("Usage: mksunxi-nuttx <input.bin> <output.bin> <padding>\n");
		printf("  padding: 512 for SD card, 8192 for SPI flash\n");
		return 1;
	}

	padding = atoi(argv[3]);
	if (padding != 512 && padding != 8192) {
		printf("Error: padding must be 512 (SD card) or 8192 (SPI flash)\n");
		return 1;
	}

	/* Open input file */
	fin = fopen(argv[1], "rb");
	if (!fin) {
		printf("Error: cannot open input file: %s\n", argv[1]);
		return 1;
	}

	/* Get input file size */
	fseek(fin, 0, SEEK_END);
	filelen = ftell(fin);
	fseek(fin, 0, SEEK_SET);

	if (filelen <= 0) {
		printf("Error: input file is empty\n");
		fclose(fin);
		return 1;
	}

	/* Calculate output buffer size (header + data, aligned) */
	buflen = ALIGN(EGON_HEADER_SIZE + filelen, padding);
	buffer = malloc(buflen);
	if (!buffer) {
		printf("Error: cannot allocate memory\n");
		fclose(fin);
		return 1;
	}
	memset(buffer, 0, buflen);

	/* Setup EGON header */
	hdr = (struct egon_header_t *)buffer;
	hdr->instruction = EGON_JUMP_INSTRUCTION;
	memcpy(hdr->magic, EGON_MAGIC_NUTTX, 8);
	hdr->length = buflen;
	hdr->checksum = 0x5F0A6C39; /* Initial checksum value */

	/* Read NuttX binary after header */
	if (fread(buffer + EGON_HEADER_SIZE, 1, filelen, fin) != filelen) {
		printf("Error: cannot read input file\n");
		free(buffer);
		fclose(fin);
		return 1;
	}
	fclose(fin);

	/* Calculate and set checksum */
	hdr->checksum = 0x5F0A6C39;
	checksum = calc_checksum((uint32_t *)buffer, buflen);
	hdr->checksum = checksum;

	/* Write output file */
	fout = fopen(argv[2], "wb");
	if (!fout) {
		printf("Error: cannot create output file: %s\n", argv[2]);
		free(buffer);
		return 1;
	}

	if (fwrite(buffer, 1, buflen, fout) != buflen) {
		printf("Error: cannot write output file\n");
		free(buffer);
		fclose(fout);
		return 1;
	}

	fclose(fout);
	free(buffer);

	printf("Created NuttX image: %s\n", argv[2]);
	printf("  Input size:  %d bytes\n", filelen);
	printf("  Output size: %d bytes (padding=%d)\n", buflen, padding);
	printf("  Header size: %lu bytes\n", (unsigned long)EGON_HEADER_SIZE);

	return 0;
}
