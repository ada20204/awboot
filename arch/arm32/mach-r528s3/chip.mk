# Chip configuration for R528S3
CPU := cortex-a7
CPU_FLAGS := -mcpu=cortex-a7 -mthumb-interwork -mthumb -mno-unaligned-access -mfpu=neon-vfpv4 -mfloat-abi=hard
COUNTER_FREQ := 24000000
RAM_BASE ?= 0x00020000
FEL_RAM_BASE ?= 0x00030000
