/*
 * sandbox.c
 *
 *  Created on: Nov 22, 2020
 *      Author: SUPER
 */

#include <sandbox.h>
#include "main.h"
#include "big_sine_wave.h"
#include "float_expo_table.h"
#include "shared_delays.h"
#include "noise.h"
#include "operator.h"
#include "tanh_table.h"
#include "lerp.h"
#include "tanh_lookup_table.h"

#define HP_INPUT_CUTOFF	20
#define LP_INPUT_CUTOFF 8000
#define HP_FEEDBACK_CUTOFF 250
#define LP_FEEDBACK_CUTOFF 2500

#define SIZE_POT_OFFSET 102
#define SIZE_POT_SCALE 0.9f

#define AP_GAIN 0.5

#define LIMIT_THRESHOLD 1500.0f  // Threshold for limiting
#define LIMIT_RATIO 10.0f      // Compression ratio above the threshold

float max_sig;

shared_delay_t d_mgr;
#define SHARED_BUF_SIZE 15000
int16_t shared_buf[SHARED_BUF_SIZE];

svf_typedef svf1, svf2, svf3;

float signal_input;

float max_sig = 0.0f;

svf_typedef input_highpass, input_lowpass, feedback_lowpass, feedback_highpass;
dynamic_smooth smooth_delay;

float slow_noise;
float slow_filtered_noise;

#define NUM_INPUT_APS 4
#define NUM_LOOP_APS 3

float input_times[NUM_INPUT_APS] = { 7.13f, 6.451f, 32.1f, 24.88f };
float loop_times[NUM_LOOP_APS] = { 42.0f, 128.4f, 164.0f };

float total_time;

float fast_tanh(float x) {
    const float x2 = x * x;  // x squared
    return x * (27.0f + x2) / (27.0f + 9.0f * x2);
}

RAMFUNC float sandbox_tick(float _input) {

	float hp_input, lp_input, signal_input, signal_output;
	static float feedback;

	// a lil' pad
	signal_input = _input;

	lfo_tick(&lfos[0], 2.2f, 1.0f);
	lfo_tick(&lfos[1], 1.1f, 1.0f);
	lfo_tick(&lfos[2], 5.4f, 1.0f);
	lfo_tick(&lfos[3], 4.1f, 1.0f);

	// filter the noise
	slow_filtered_noise += (slow_noise - slow_filtered_noise) * 0.01f;

	// scale modulation with size
	float lfo_modulation_amt = size_pot * 0.005f;

	shared_delay_tick(&d_mgr);

	float ap_gains = 0.5f;

	float input_aps = signal_input;
	for (uint8_t i = 0; i < NUM_INPUT_APS; i++) {
		input_aps = shared_modulated_allpass(&d_mgr, input_times[i], input_aps, ap_gains, size_pot);
	}

	float ap_loop = input_aps + feedback;

	ap_loop = shared_modulated_allpass(&d_mgr, loop_times[0], ap_loop, ap_gains, size_pot - (lfos[0].out * lfo_modulation_amt));
	ap_loop = shared_modulated_allpass(&d_mgr, loop_times[1], ap_loop, ap_gains, size_pot);
	ap_loop = shared_modulated_allpass(&d_mgr, loop_times[2], ap_loop, ap_gains, size_pot - (lfos[1].out * lfo_modulation_amt));

	float loop_out = ap_loop;
	svf_tick(&feedback_highpass, loop_out);
	loop_out = svf_get_high(&feedback_highpass);

	svf_tick(&feedback_lowpass, loop_out);
	loop_out = svf_get_low(&feedback_lowpass);

	signal_output = loop_out;

	//signal_output = fast_tanh(loop_out / 2047.0f) * 2047.0f;
	//feedback = limiter(signal_output * feedback_pot);
	//signal_output = limiter(signal_output);

	feedback = signal_output * feedback_pot;
	signal_output = signal_output;


	// clip
	if (signal_output > 2047.0f) {
		signal_output = 2047.0f;
	}
	if (signal_output < -2047.0f) {
		signal_output = -2047.0f;
	}

	//check for max
	if (signal_output > max_sig) {
		max_sig = signal_output;
	}

	return signal_output;

}

void control_tick(reverb_params_typedef *params, float _input) {
	hp_cutoff_pot += ((float_expo_table[params->hp_cutoff]) - hp_cutoff_pot) * 0.03f;
	lp_cutoff_pot += ((float_expo_table[params->lp_cutoff] * 1.05f) - lp_cutoff_pot) * 0.03f;
	size_pot += ((float_expo_table[(uint16_t) (params->size * SIZE_POT_SCALE) + SIZE_POT_OFFSET]) - size_pot) * 0.001f;
	feedback_pot += ((params->feedback / -1024.0f) - feedback_pot) * 0.03f;

	if(lp_cutoff_pot > 0.9999f) {
		lp_cutoff_pot = 0.9999f;
	}

	svf_set_a_direct(&feedback_highpass, hp_cutoff_pot * 0.7f);
	svf_set_a_direct(&feedback_lowpass, lp_cutoff_pot);
}

void sandbox_init() {
	// delays
	shared_delay_init(&d_mgr, shared_buf, SHARED_BUF_SIZE);

	// filtas
	svf_init(&input_lowpass, LP_INPUT_CUTOFF, 0.707f);
	svf_init(&input_highpass, HP_INPUT_CUTOFF, 0.707f);
	svf_init(&feedback_lowpass, LP_FEEDBACK_CUTOFF, 0.8f);
	svf_init(&feedback_highpass, HP_FEEDBACK_CUTOFF, 0.8f);

	// dithering filtas
	svf_init(&svf1, 30000.0f, 0.7f);
	svf_init(&svf2, 30000.0f, 0.7f);
	svf_init(&svf3, 8000.0f, 0.8f);

	// check for wild boy delay times
	total_time = 0;
	for (uint8_t i = 0; i < NUM_INPUT_APS; i++) {
		total_time += input_times[i];
	}
	for (uint8_t i = 0; i < NUM_LOOP_APS; i++) {
		total_time += loop_times[i];
	}

	if (total_time > MAX_MS_DELAY) {
		while (1) {
			//chill out here
		}
	}
}

float dither(float _input) {
	svf_tick(&svf1, ((noise() >> 21) - 512.0f) * 0.001f);
	float temp = svf_get_high(&svf1);
	svf_tick(&svf2, temp);
	temp = svf_get_low(&svf2);
	//return temp + _input;
	svf_tick(&svf3, temp + _input);
	return svf_get_low(&svf3);
}

float limiter(float input) {
	float abs_input = fabs(input);

	if (abs_input > LIMIT_THRESHOLD) {
		// Apply gain reduction above the threshold
		float excess = abs_input - LIMIT_THRESHOLD;
		float compressed_excess = excess / LIMIT_RATIO;
		float output = LIMIT_THRESHOLD + compressed_excess;

		// Restore the sign of the original input
		return (input > 0 ? output : -output);
	}

	// Below the threshold, no limiting
	return input;
}



