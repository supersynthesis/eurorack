/*
 * opamp.c
 *
 *  Created on: Jan 21, 2023
 *      Author: chrismcdowell
 */

#include "opamp.h"

void opamp_init(opamp_typedef *o) {
	o->in_n = 0.0f;
	o->in_p = 0.0f;
	o->out = 0.0f;
}

uint8_t opamp_comparator(opamp_typedef *o, float _n, float _p,
		float _hysteresis) {
	o->in_p = _p + (o->out * _hysteresis);
	o->in_n = _n;
	o->out = (o->in_p - o->in_n) * 1000.0f;
	if (o->out > 1.0f) {
		o->out = 1.0f;
	}
	if (o->out < -1.0f) {
		o->out = -1.0f;
	}
	return o->out;
}
