/*
 * global_variables.h
 *
 *  Created on: Apr 2, 2020
 *      Author: SUPER
 */

#ifndef INC_GLOBAL_VARIABLES_H_
#define INC_GLOBAL_VARIABLES_H_

#define NUM_ADC1_CHANNELS 6
#define NUM_ADC2_CHANNELS 2

//#define VOCT

#define VOCT_SCALE 0.147299349f
#define WIDE_SCALE 0.25f

volatile uint16_t adc1_data[NUM_ADC1_CHANNELS];
volatile uint16_t adc1_data_10b[NUM_ADC1_CHANNELS-1];
volatile uint16_t adc2_data[NUM_ADC2_CHANNELS];
volatile uint16_t VREFINT_CAL;
volatile uint16_t vdd_mv;
volatile uint32_t vdd_cal;
volatile float khz_correction;
volatile uint16_t ramp;
volatile uint16_t khz_in_mv;
volatile float khz_in_scaling;

#endif /* INC_GLOBAL_VARIABLES_H_ */
