# Chip configuration for F1C200S
CPU := arm926ejs
CPU_FLAGS := -mcpu=arm926ej-s -marm
COUNTER_FREQ := 24000000
RAM_BASE ?= 0x00000000
FEL_RAM_BASE ?= 0x00010000
