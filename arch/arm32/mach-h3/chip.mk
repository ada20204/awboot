# Chip configuration for H3
CPU := cortex-a7
CPU_FLAGS := -mcpu=cortex-a7 -mthumb-interwork -mthumb -mno-unaligned-access -mfpu=neon-vfpv4 -mfloat-abi=hard
COUNTER_FREQ := 24000000
RAM_BASE ?= 0x00000000
FEL_RAM_BASE ?= 0x00008000
