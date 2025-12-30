# drivers/drivers.mk - Common driver sources

DRIVER_SRCS := \
    drivers/sunxi_gpio.c \
    drivers/sunxi_usart.c \
    drivers/sunxi_spi.c \
    drivers/sunxi_dma.c \
    drivers/sunxi_sdhci.c \
    drivers/sdmmc.c

SRCS += $(DRIVER_SRCS)
INCLUDE_DIRS += -I drivers
