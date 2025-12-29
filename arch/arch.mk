# awboot architecture configuration
# Usage: make CHIP=t113s3 (default)
#        make CHIP=h3
#        make CHIP=f1c100s

ARCH := arch
CHIP ?= t113s3
SOC := $(ARCH)/arm32/mach-$(CHIP)
CPU_DIR := $(ARCH)/arm32/cpu

# Include chip-specific configuration
-include $(SOC)/chip.mk

# CPU defaults (can be overridden by chip.mk)
CPU ?= cortex-a7
COUNTER_FREQ ?= 24000000

INCLUDE_DIRS += -I $(ARCH)/arm32/include -I $(SOC)/include -I $(SOC) -I $(SOC)/mmc

CFLAGS += -DCOUNTER_FREQUENCY=$(COUNTER_FREQ)

# Chip-specific sources (required)
SRCS += $(SOC)/dram.c
SRCS += $(SOC)/sunxi_clk.c

# Optional chip-specific sources (only if they exist)
SRCS += $(wildcard $(SOC)/sunxi_usart.c)
SRCS += $(wildcard $(SOC)/arch_timer.c)
SRCS += $(wildcard $(SOC)/sunxi_spi.c)
SRCS += $(wildcard $(SOC)/sunxi_dma.c)
SRCS += $(wildcard $(SOC)/sunxi_gpio.c)
SRCS += $(wildcard $(SOC)/sdmmc.c)
SRCS += $(wildcard $(SOC)/sunxi_sdhci.c)
SRCS += $(wildcard $(SOC)/exception.c)

# Use shared CPU start.S, fallback to chip-specific if exists
ifneq ($(wildcard $(SOC)/start.S),)
ASRCS += $(SOC)/start.S
else
ASRCS += $(CPU_DIR)/$(CPU)/start.S
endif

ASRCS += $(wildcard $(SOC)/memcpy.S)
