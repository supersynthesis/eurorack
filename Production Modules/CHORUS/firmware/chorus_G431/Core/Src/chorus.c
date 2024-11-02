/*
 * chorus.c
 *
 *  Created on: Nov 22, 2020
 *      Author: SUPER
 */

#include "main.h"
#include "chorus.h"
#include "big_sine_wave.h"
#include "float_expo_table.h"
#include "lerp.h"

#define SINE

//#define FB_LP
//#define BP_LP
#define NO_FB_FILTER

#define HP_INPUT_CUTOFF	150
#define LP_INPUT_CUTOFF 8000
#define FB_SVF_CUTOFF	5000

uint32_t lfo_tick(volatile lfo_typedef *lfo, float _frequency, float _amplitude) {
	lfo->phase_increment = ((42949.6710f) * (_frequency));
	lfo->phase_index += lfo->phase_increment;
	lfo->output = ((((sine_10b[lfo->phase_index >> 22] - 512) * 0.001953125f) * 0.5f) + 0.5f) * _amplitude;
	//lfo->output = (big_sine_wave[lfo->phase_index >> 22]) >> 5;
	return lfo->phase_index;
}

float chorus_tick(float _input) {

	//input highpass
	svf_tick(&input_highpass, _input);
	chorus_hp_input = svf_get_high(&input_highpass);

	// input lowpass
	svf_tick(&input_lowpass, chorus_hp_input);
	chorus_lp_input = svf_get_low(&input_lowpass);

	// a lil' pad
	chorus_signal_input = chorus_lp_input * 0.7f;

	// increment buffer index and wrap
	chorus_buffer_index_in++;
	if (chorus_buffer_index_in > (CHORUS_BUFFER_LENGTH - 1)) {
		chorus_buffer_index_in -= CHORUS_BUFFER_LENGTH;
	}

	// add feedback
	buffer_signal_input = chorus_signal_input + (feedback);

	// store in the buffer
	chorus_buffer[chorus_buffer_index_in] = buffer_signal_input;

	lfo_tick(&chorus_lfo, lfo_rate_pot, lfo_amt_pot);

	// 1p low pass filter the lfo modulation
	buffer_modulation += ((chorus_lfo.output) - buffer_modulation) * 0.03f;

	// dynamic smooth the delay pot and cv input (summed in control tick)
	delay_pot_filter = dynamic_smooth_tick(&smooth_delay, delay_pot);

	// use the lerp to calculate our buffer output sample
	chorus_signal_output = lerp_int16(chorus_buffer, CHORUS_BUFFER_LENGTH,
			chorus_buffer_index_in - (buffer_modulation * (1.0f - delay_pot_filter)) - ((delay_pot_filter) * (CHORUS_BUFFER_LENGTH - 1)));

	// clip
	if (chorus_signal_output > 2047.0f) {
		chorus_signal_output = 2047.0f;
	}
	if (chorus_signal_output < -2047.0f) {
		chorus_signal_output = -2047.0f;
	}

	// calculate feedback with a filter or not

#ifdef BP_LP
	svf_tick(&feedback_svf, chorus_signal_output);
	feedback = svf_get_band(&feedback_svf) * (feedback_pot * -1.0f);
#endif

#ifdef FB_LP
	svf_tick(&feedback_svf, chorus_signal_output);
	feedback = svf_get_low(&feedback_svf) * (feedback_pot * -1.0f);
#endif

#ifdef NO_FB_FILTER
	feedback = chorus_signal_output * (feedback_pot * -1.0f);
#endif

	//check for max
	if (chorus_signal_output > max_sig) {
		max_sig = chorus_signal_output;
	}

	return chorus_signal_output;
}

void chorus_control_tick(chorus_params_typedef *chorus) {

	lfo_rate_pot += ((float_expo_table[chorus->lfo_rate] * 75.0f) - lfo_rate_pot) * 0.03f;

	lfo_amt_pot += ((float_expo_table[chorus->lfo_amount] * (CHORUS_BUFFER_LENGTH - 1)) - lfo_amt_pot) * 0.03f;

	feedback_pot += ((chorus->feedback / 1024.0f) - feedback_pot) * 0.03f;

	float delay_input = chorus->delay + ((chorus->delay_cv - magic_cv_offset) * 0.75f);
	if (delay_input > 1023.0f) {
		delay_input = 1023.0f;
	}
	if (delay_input < 0.0f) {
		delay_input = 0.0f;
	}

	delay_pot += (((delay_input) / 1024.0f) - delay_pot) * 0.5f;

}

void chorus_init() {
	dynamic_smooth_init(&smooth_delay, 0.05f, 0.5f);

	svf_init(&input_lowpass, LP_INPUT_CUTOFF, 0.707f);
	svf_init(&input_highpass, HP_INPUT_CUTOFF, 1.5f);
	svf_init(&feedback_svf, FB_SVF_CUTOFF, 1.0f);
}
