/*
 * shared_delays.c
 *
 *  Created on: Jan 8, 2023
 *      Author: chrismcdowell
 */

#include "shared_delays.h"

float shared_delay(shared_delay_t *d, float _delay, float _input, float _fb) {
	if (_delay > d->bufsize) {
		return 0.0f;
	}

	_delay *= d->ms_scale;

	uint16_t j = d->write + _delay;
	if (j > d->bufsize - 1) {
		j -= d->bufsize;
	}
	float delayed = d->buf[j];
	d->buf[d->write] = _input + delayed * _fb;
	_input = delayed;
	d->write = j;
	return _input;
}

float shared_allpass(shared_delay_t *ap, float _delay, float _input, float _fb) {

	if (_delay > ap->bufsize) {
		return 0.0f;
	}

	_delay *= ap->ms_scale;

	uint16_t j = ap->write + _delay;
	if (j > ap->bufsize - 1) {
		j -= ap->bufsize;
	}

	float delayed = ap->buf[j];
	ap->buf[ap->write] = _input -= delayed * _fb;
	ap->write = j;
	return _input * _fb + delayed;;
}

float shared_modulated_delay(shared_delay_t *d, float _delay, float _input, float _fb, float _mod) {

	_delay *= d->ms_scale;

	float fractional_delay = (_delay * _mod);
	uint16_t i_part = (uint16_t) (fractional_delay);
	float f_part = fractional_delay - i_part;

	if (fractional_delay > d->bufsize || fractional_delay < 0.0f) {
		return 0.0f;
	}

	uint16_t j = d->write + i_part;
	uint16_t k = d->write + _delay;
	if (j > d->bufsize - 1) {
		j -= d->bufsize;
	}
	if (k > d->bufsize - 1) {
		k -= d->bufsize;
	}

	int16_t this_sample, next_sample;
	this_sample = d->buf[j];
	if (j < d->bufsize - 1) {
		next_sample = d->buf[j + 1];
	} else {
		next_sample = d->buf[(j + 1) - d->bufsize];
	}

	float delayed = (this_sample + ((next_sample - this_sample) * f_part));
	d->buf[d->write] = _input + delayed * _fb;
	d->write = k;
	return delayed;
}

RAMFUNC float shared_modulated_allpass(shared_delay_t *ap, float _delay, float _input, float _fb, float _mod) {

	_delay *= ap->ms_scale;

	float fractional_delay = (_delay * _mod);
	uint16_t i_part = (uint16_t) (fractional_delay);
	float f_part = fractional_delay - i_part;

	if (fractional_delay > ap->bufsize || fractional_delay < 0.0f) {
		return 0.0f;
	}

	uint16_t j = ap->write + i_part;
	uint16_t k = ap->write + _delay;
	if (j > ap->bufsize - 1) {
		j -= ap->bufsize;
	}
	if (k > ap->bufsize - 1) {
		k -= ap->bufsize;
	}

	int16_t this_sample, next_sample;
	this_sample = ap->buf[j];
	if (j < ap->bufsize - 1) {
		next_sample = ap->buf[j + 1];
	} else {
		next_sample = ap->buf[(j + 1) - ap->bufsize];
	}

	float delayed = (this_sample + ((next_sample - this_sample) * f_part));
	ap->buf[ap->write] = _input -= delayed * _fb;
	ap->write = k;
	return _input * _fb + delayed;
}

float shared_nested_allpass(shared_delay_t *ap, float _delay, float _input, float _fb, float _delay2, float _fb2) {

	float output;

	if (_delay > ap->bufsize) {
		return 0.0f;
	}

	_delay *= ap->ms_scale;
	_delay2 *= ap->ms_scale;

	uint16_t j = ap->write + _delay;
	if (j > ap->bufsize - 1) {
		j -= ap->bufsize;
	}

	float delayed = ap->buf[j];
	output = _input * _fb + shared_allpass(ap, _delay2, delayed, _fb2);
	ap->buf[ap->write] = _input -= output * _fb;
	ap->write = j;
	return output;
}

void shared_delay_tick(shared_delay_t *d) {
	d->write = d->index;
	d->index--;
	if (d->index < 0) {
		d->index += d->bufsize;
	}
}

void shared_delay_init(shared_delay_t *d, int16_t *_buf, uint16_t _bufsize) {
	d->buf = _buf;
	d->bufsize = _bufsize;
	d->ms_scale = SAMPLE_RATE / 1000.0f;
	d->d1 = 0.0f;
}
