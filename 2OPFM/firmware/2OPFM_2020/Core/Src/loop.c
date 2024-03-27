/*
 * loop.c
 *
 *  Created on: Apr 2, 2020
 *      Author: SUPER
 */

#include "loop.h"
#include "main.h"

void loop(void) {
	//dac1_ch1(ramp);
	dac2_ch1(2047);
	vdd_mv = __LL_ADC_CALC_VREFANALOG_VOLTAGE(adc_data[6],LL_ADC_RESOLUTION_12B);
	vdd_cal = (uint32_t)(*VREFINT_CAL_ADDR);
	khz_correction = vdd_mv / 3300.0f;
	khz_in_mv = voct_data[0] * 3300 >> 12;
}
