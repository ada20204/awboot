/*
 * error.h - Error codes and handling for awboot
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __AWBOOT_ERROR_H__
#define __AWBOOT_ERROR_H__

/*
 * Error codes
 * Convention: 0 = success, negative = error
 */
#define AWBOOT_OK               0

/* General errors */
#define AWBOOT_ERR_GENERIC      (-1)
#define AWBOOT_ERR_TIMEOUT      (-2)
#define AWBOOT_ERR_INVALID      (-3)
#define AWBOOT_ERR_NOMEM        (-4)

/* DRAM errors */
#define AWBOOT_ERR_DRAM         (-10)
#define AWBOOT_ERR_DRAM_INIT    (-11)
#define AWBOOT_ERR_DRAM_SCAN    (-12)
#define AWBOOT_ERR_DRAM_TEST    (-13)
#define AWBOOT_ERR_DRAM_SIZE    (-14)

/* Clock errors */
#define AWBOOT_ERR_CLK          (-20)
#define AWBOOT_ERR_CLK_PLL      (-21)
#define AWBOOT_ERR_CLK_LOCK     (-22)

/* Boot errors */
#define AWBOOT_ERR_BOOT         (-30)
#define AWBOOT_ERR_BOOT_MEDIA   (-31)
#define AWBOOT_ERR_BOOT_IMAGE   (-32)
#define AWBOOT_ERR_BOOT_MAGIC   (-33)
#define AWBOOT_ERR_BOOT_CHECKSUM (-34)

/* Storage errors */
#define AWBOOT_ERR_STORAGE      (-40)
#define AWBOOT_ERR_SD_INIT      (-41)
#define AWBOOT_ERR_SD_READ      (-42)
#define AWBOOT_ERR_SPI_INIT     (-43)
#define AWBOOT_ERR_SPI_READ     (-44)

/*
 * Error checking macros
 */
#define IS_ERR(x)       ((x) < 0)
#define IS_OK(x)        ((x) >= 0)

/*
 * Return on error macro
 */
#define RETURN_ON_ERR(expr) do { \
    int __ret = (expr); \
    if (IS_ERR(__ret)) return __ret; \
} while (0)

/*
 * Error to string conversion
 */
static inline const char *awboot_strerror(int err)
{
    switch (err) {
    case AWBOOT_OK:             return "OK";
    case AWBOOT_ERR_GENERIC:    return "Generic error";
    case AWBOOT_ERR_TIMEOUT:    return "Timeout";
    case AWBOOT_ERR_INVALID:    return "Invalid parameter";
    case AWBOOT_ERR_NOMEM:      return "Out of memory";
    case AWBOOT_ERR_DRAM:       return "DRAM error";
    case AWBOOT_ERR_DRAM_INIT:  return "DRAM init failed";
    case AWBOOT_ERR_DRAM_SCAN:  return "DRAM scan failed";
    case AWBOOT_ERR_DRAM_TEST:  return "DRAM test failed";
    case AWBOOT_ERR_DRAM_SIZE:  return "DRAM size detect failed";
    case AWBOOT_ERR_CLK:        return "Clock error";
    case AWBOOT_ERR_CLK_PLL:    return "PLL config failed";
    case AWBOOT_ERR_CLK_LOCK:   return "PLL lock timeout";
    case AWBOOT_ERR_BOOT:       return "Boot error";
    case AWBOOT_ERR_BOOT_MEDIA: return "No boot media";
    case AWBOOT_ERR_BOOT_IMAGE: return "Invalid image";
    case AWBOOT_ERR_BOOT_MAGIC: return "Bad magic";
    case AWBOOT_ERR_BOOT_CHECKSUM: return "Checksum error";
    case AWBOOT_ERR_STORAGE:    return "Storage error";
    case AWBOOT_ERR_SD_INIT:    return "SD init failed";
    case AWBOOT_ERR_SD_READ:    return "SD read failed";
    case AWBOOT_ERR_SPI_INIT:   return "SPI init failed";
    case AWBOOT_ERR_SPI_READ:   return "SPI read failed";
    default:                    return "Unknown error";
    }
}

#endif /* __AWBOOT_ERROR_H__ */
