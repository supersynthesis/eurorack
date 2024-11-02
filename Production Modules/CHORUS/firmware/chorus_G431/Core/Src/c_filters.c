/*
 * c_filters.c
 *
 *  Created on: Jan 6, 2023
 *      Author: chrismcdowell
 */

#include "c_filters.h"

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
