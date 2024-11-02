/*
 * lerp.c
 *
 *  Created on: Jan 6, 2023
 *      Author: chrismcdowell
 */

#include "lerp.h"

float lerp_int16(int16_t _buf[], uint16_t _bufsize, float position) {
	uint16_t integer_part;
	float float_part;
	int16_t this_sample, next_sample;

	if (position < 0.0f) {
		position += _bufsize;
	}

	if (position > (_bufsize - 1)) {
		position -= _bufsize;
	}

	integer_part = (uint16_t) (position);
	float_part = position - integer_part;
	this_sample = _buf[integer_part];
	if (integer_part < (_bufsize - 1)) {
		next_sample = _buf[integer_part + 1];
	} else {
		next_sample = _buf[(integer_part + 1) - _bufsize];
	}

	return (((next_sample - this_sample) * float_part) + this_sample);
}
