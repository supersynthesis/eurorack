/*
 * c_filters.c
 *
 *  Created on: Jan 6, 2023
 *      Author: chrismcdowell
 */

#include "c_filters.h"
#include "lerp.h"

// **********************************************************************
// SVF
// **********************************************************************

void svf_init(svf_typedef *svf, float _freq, float _q) {
	svf->freq = _freq;

	svf->a = (6.28f * _freq) / SAMPLE_RATE;
	if (svf->a > 1.0f) {
		svf->a = 1.0f;
	}

	if (_q < 0.500f) {
		_q = 0.500f;
	}
	svf->q = 1.0f / _q;
}

void svf_tick(svf_typedef *svf, float _input) {
	svf->low = svf->delay2 + svf->a * svf->delay1;
	svf->high = _input - svf->low - (svf->q * svf->delay1);
	svf->band = (svf->a * svf->high) + svf->delay1;

	svf->delay1 = svf->band;
	svf->delay2 = svf->low;
}

void svf_set_freq(svf_typedef *svf, float _freq) {
	svf->freq = _freq;
	svf->a = (6.28f * _freq) / SAMPLE_RATE;
	if (svf->a > 1.0f) {
		svf->a = 1.0f;
	}
}

void svf_set_a_direct(svf_typedef *svf, float _a) {
	svf->a = _a;
}

void svf_set_q(svf_typedef *svf, float _q) {
	if (_q < 0.500f) {
		_q = 0.500f;
	}
	svf->q = 1.0f / _q;
}

float svf_get_low(svf_typedef *svf) {
	return svf->low;
}

float svf_get_high(svf_typedef *svf) {
	return svf->high;
}

float svf_get_band(svf_typedef *svf) {
	return svf->band;
}

// **********************************************************************
// one pole
// **********************************************************************

void onepole_tick(onepole_typedef *f, float _input) {
	f->in = _input;
	f->d1 += (f->in - f->d1) * f->a;
}

void onepole_set_freq(onepole_typedef *f, float _freq) {
	f->a = (6.28f * _freq) / SAMPLE_RATE;
}

void onepole_set_a_direct(onepole_typedef *f, float _a) {
	f->a = _a;
}

float onepole_get_low(onepole_typedef *f) {
	return f->d1;
}

float onepole_get_high(onepole_typedef *f) {
	return f->in - f->d1;
}

// **********************************************************************
// all pass
// **********************************************************************

float allpass_tick(allpass_typedef *ap, int16_t _buf[], uint16_t _bufsize,
		float _input, float _gain, float _delay, float _modulation) {
	float buf_read_position;
	float delay_out;

	ap->buf_write_index++;
	if (ap->buf_write_index > (_bufsize - 1)) {
		ap->buf_write_index -= _bufsize;
	}

	_buf[ap->buf_write_index] = _input + ap->out * (-1.0f * _gain);

	buf_read_position = ap->buf_write_index - (_modulation * (1.0f - _delay))
			- ((_delay) * (_bufsize - 1));

	delay_out = lerp_int16(_buf, _bufsize, buf_read_position);
	ap->out = (_input * _gain) + delay_out;
	return ap->out;
}

// **********************************************************************

