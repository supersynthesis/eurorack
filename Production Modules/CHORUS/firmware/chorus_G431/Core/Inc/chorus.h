/*
 * chorus.h
 *
 *  Created on: Nov 22, 2020
 *      Author: SUPER
 */

#ifndef INC_CHORUS_H_
#define INC_CHORUS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "dynamic_smooth.h"
#include "c_filters.h"

#define CHORUS_BUFFER_LENGTH 15000

float chorus_signal_input;
float chorus_hp_input;
float chorus_lp_input;
float chorus_signal_output;
float feedback;
int16_t chorus_buffer[CHORUS_BUFFER_LENGTH];
uint32_t chorus_buffer_accumulator;
uint16_t chorus_buffer_index_in;
uint16_t chorus_buffer_index_out;
float buffer_signal_input;
float buffer_modulation;
float max_sig;

typedef struct {
	float output;
	float amplitude;
	float frequency;
	uint32_t phase_increment;
	uint32_t phase_index;
} lfo_typedef;

uint32_t lfo_tick(volatile lfo_typedef *lfo, float _frequency, float _amplitude);
uint32_t lfo_tri_tick(volatile lfo_typedef *lfo, float _frequency, float _amplitude);

volatile lfo_typedef chorus_lfo;

typedef struct {
	uint16_t delay;
	uint16_t delay_cv;
	uint16_t lfo_amount;
	uint16_t lfo_rate;
	uint16_t feedback;
} chorus_params_typedef;

volatile float rate_pot;
volatile float feedback_pot;
volatile float lfo_amt_pot;
volatile float delay_pot;
volatile float delay_pot_filter;
volatile float delay_cv;
#define magic_cv_offset 1900

volatile float lfo_rate_pot;

dynamic_smooth smooth_delay;

float chorus_tick(float _input);
void chorus_control_tick(chorus_params_typedef *chorus);
void chorus_init();

svf_typedef input_lowpass;
svf_typedef input_highpass;
svf_typedef feedback_svf;

#ifdef __cplusplus
}
#endif


#endif /* INC_CHORUS_H_ */
