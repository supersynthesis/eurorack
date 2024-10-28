/*
 * dac.c
 *
 *  Created on: Apr 3, 2020
 *      Author: SUPER
 */


#include "dac.h"
#include "main.h"

inline void dac2_ch1(uint16_t _out_val) {
	LL_DAC_ConvertData12RightAligned(DAC2, LL_DAC_CHANNEL_1, _out_val);
}

inline void dac1_ch1(uint16_t _out_val) {
	LL_DAC_ConvertData12RightAligned(DAC1, LL_DAC_CHANNEL_1, _out_val);
}
