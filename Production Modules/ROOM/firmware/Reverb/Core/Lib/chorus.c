/*
 * chorus.c
 *
 *  Created on: Feb 11, 2023
 *      Author: chrismcdowell
 */

#include "chorus.h"

float chorus_tick(chorus_t *c, shared_delay_t *td, float _input) {
	shared_delay_tick(td);

	lfo_tick(&c->lfo, c->rate, 0);

	c->filtered_lfo += (c->lfo.out - c->filtered_lfo) * 0.01f;

	float bal_inverse = 1.0f - c->balance;

	float wet = shared_modulated_allpass(td, c->delay, _input, c->feedback, 0.5f + (c->filtered_lfo * c->amount));

	return (wet * c->balance) + (_input * bal_inverse);
}
