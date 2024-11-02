/*
 * dynamic_smooth.c
 *
 *  Created on: Sep 19, 2020
 *      Author: SUPER
 */


#include "dynamic_smooth.h"
#include "math.h"

float cm_min(float a, float b) {
	return ((a) < (b) ? a : b);
}

float cm_abs(float a) {
	if (a < 0.0f) {
		return a*-1.0;
	} else {
		return a;
	}
}

void dynamic_smooth_init(dynamic_smooth* _smooth, float _base, float _sensitivity) {
	float basefreq, wc, gc;

	//init values
	basefreq = _base;
	wc = basefreq / DYN_SMOOTH_SAMPLE_RATE;
	gc = tan(3.14f * wc);
	_smooth->g0 = 2*gc/(1+gc);
	_smooth->sense = _sensitivity * 4.0f;

	//tick values
	_smooth->low1 = 0.0f;
	_smooth->low2 = 0.0f;
	_smooth->low1z = 0.0f;
	_smooth->low2z = 0.0f;
	_smooth->bandz = 0.0f;
	_smooth->out = 0.0f;
}

float dynamic_smooth_tick(dynamic_smooth* _smooth, float in) {
	float g;
	_smooth->low1z = _smooth->low1;
	_smooth->low2z = _smooth->low2;
	_smooth->bandz = _smooth->low2z - _smooth->low1z;
	g = cm_min(_smooth->g0 + _smooth->sense*cm_abs(_smooth->bandz), 1.0f);
	_smooth->low1 = _smooth->low1z + g*(in-_smooth->low1z);
	_smooth->low2 = _smooth->low2z + g*(_smooth->low1 - _smooth->low2z);

	return _smooth->low2;
}
