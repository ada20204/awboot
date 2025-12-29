/*
 * boot_log.h - Boot stage logging for awboot
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __BOOT_LOG_H__
#define __BOOT_LOG_H__

#include "debug.h"
#include "error.h"

/*
 * Boot stage definitions
 */
enum boot_stage {
    STAGE_INIT = 0,
    STAGE_CLK,
    STAGE_DRAM,
    STAGE_STORAGE,
    STAGE_LOAD,
    STAGE_BOOT,
};

/*
 * Boot stage names
 */
static inline const char *boot_stage_name(enum boot_stage stage)
{
    switch (stage) {
    case STAGE_INIT:    return "INIT";
    case STAGE_CLK:     return "CLK";
    case STAGE_DRAM:    return "DRAM";
    case STAGE_STORAGE: return "STORAGE";
    case STAGE_LOAD:    return "LOAD";
    case STAGE_BOOT:    return "BOOT";
    default:            return "UNKNOWN";
    }
}

/*
 * Boot stage logging macros
 */
#define BOOT_STAGE_START(stage) \
    info("[%s] Starting...\r\n", boot_stage_name(stage))

#define BOOT_STAGE_OK(stage) \
    info("[%s] OK\r\n", boot_stage_name(stage))

#define BOOT_STAGE_FAIL(stage, err) \
    error("[%s] Failed: %s (%d)\r\n", boot_stage_name(stage), awboot_strerror(err), err)

/*
 * Timed operation logging
 */
#define LOG_TIMED_START(msg) \
    do { \
        debug("%s...", msg); \
    } while (0)

#define LOG_TIMED_OK() \
    do { \
        debug("OK\r\n"); \
    } while (0)

#define LOG_TIMED_FAIL(err) \
    do { \
        debug("FAIL (%d)\r\n", err); \
    } while (0)

/*
 * Memory logging
 */
#define LOG_MEM(name, base, size) \
    info("%s: 0x%08x - 0x%08x (%dMB)\r\n", \
         name, (u32)(base), (u32)(base) + (size) - 1, (size) / (1024 * 1024))

/*
 * Boot banner
 */
#define BOOT_BANNER(chip, rev) \
    info("\r\n=== awboot %s (rev %d) ===\r\n", chip, rev)

#endif /* __BOOT_LOG_H__ */
