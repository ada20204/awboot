/*
 * clk_common.c - Common clock functions for awboot
 *
 * SPDX-License-Identifier: MIT
 */

#include "clk_common.h"
#include "debug.h"

/*
 * Calculate PLL output frequency
 * Formula varies by SoC, this is a common approximation:
 *   freq = (24MHz * N * K) / (M * P)
 */
u32 clk_calc_pll_freq(u32 n, u32 k, u32 m, u32 p)
{
	u32 freq;

	if (m == 0) m = 1;
	if (p == 0) p = 1;
	if (k == 0) k = 1;

	freq = (24000000UL * (n + 1) * k) / (m * p);
	return freq;
}

/*
 * Find PLL factors for target frequency
 * Returns: 1 on success, 0 if no valid config found
 */
int clk_find_pll_factors(u32 target_freq, struct pll_config *cfg)
{
	u32 n, k, m;
	u32 best_diff = 0xffffffff;
	u32 freq;

	cfg->freq = 0;
	cfg->n = 0;
	cfg->k = 1;
	cfg->m = 1;
	cfg->p = 1;

	/* Simple search for N factor (24MHz * N) */
	for (n = 1; n <= 32; n++) {
		for (m = 1; m <= 4; m++) {
			for (k = 1; k <= 4; k++) {
				freq = (24000000UL * n * k) / m;
				u32 diff = (freq > target_freq) ?
				           (freq - target_freq) :
				           (target_freq - freq);

				if (diff < best_diff) {
					best_diff = diff;
					cfg->freq = freq;
					cfg->n = n - 1;
					cfg->k = k;
					cfg->m = m;
					cfg->p = 1;
				}

				if (diff == 0)
					return 1;
			}
		}
	}

	return (cfg->freq != 0);
}
