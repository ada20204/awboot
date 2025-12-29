/*
 * H3 DRAM Controller Register Definitions
 * Ported from xboot for awboot
 */

#ifndef __H3_REG_DRAM_H__
#define __H3_REG_DRAM_H__

#define H3_DRAM_COM_BASE        (0x01c62000)
#define H3_DRAM_CTL_BASE        (0x01c63000)

/* Similar to V3S DRAM registers */
#define MCTL_CR_BL8             (0x4 << 20)
#define MCTL_CR_2T              (0x0 << 19)
#define MCTL_CR_DDR3            (0x3 << 16)
#define MCTL_CR_INTERLEAVED     (0x0 << 15)
#define MCTL_CR_32BIT           (0x1 << 12)
#define MCTL_CR_16BIT           (0x0 << 12)
#define MCTL_CR_PAGE_SIZE(x)    ((gfls(x) - 4) << 8)
#define MCTL_CR_ROW_BITS(x)     (((x) - 1) << 4)
#define MCTL_CR_EIGHT_BANKS     (0x1 << 2)
#define MCTL_CR_SINGLE_RANK     (0x0 << 0)

#define PIR_CLRSR               (0x1 << 27)
#define PIR_QSGATE              (0x1 << 10)
#define PIR_DRAMINIT            (0x1 << 8)
#define PIR_DRAMRST             (0x1 << 7)
#define PIR_PHYRST              (0x1 << 6)
#define PIR_DCAL                (0x1 << 5)
#define PIR_PLLINIT             (0x1 << 4)
#define PIR_ZCAL                (0x1 << 1)
#define PIR_INIT                (0x1 << 0)
#define PGSR_INIT_DONE          (0x1 << 0)
#define ZQCR_PWRDOWN            (0x1 << 31)

#endif /* __H3_REG_DRAM_H__ */
