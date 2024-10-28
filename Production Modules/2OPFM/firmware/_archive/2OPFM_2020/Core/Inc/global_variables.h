/*
 * global_variables.h
 *
 *  Created on: Apr 2, 2020
 *      Author: SUPER
 */

#ifndef INC_GLOBAL_VARIABLES_H_
#define INC_GLOBAL_VARIABLES_H_

#include "stm32f3xx.h"

#define NUM_ADC_CHANNELS 7

uint16_t adc_data[NUM_ADC_CHANNELS];
uint16_t adc_data_10b[NUM_ADC_CHANNELS-1];
uint16_t voct_data[1];
uint16_t vdd_mv;
uint32_t vdd_cal;
float khz_correction;
uint16_t ramp;
uint16_t khz_in_mv;

#endif /* INC_GLOBAL_VARIABLES_H_ */
