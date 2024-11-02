/*
 * lfo.c
 *
 *  Created on: Jan 8, 2023
 *      Author: chrismcdowell
 */

#include "lfo.h"
#include "big_sine_wave.h"

uint32_t lfo_tick(volatile lfo_t *lfo, float _frequency, int16_t _mod) {
	lfo->phase_increment = PHINC_SCALE * _frequency;
	lfo->phase_index += lfo->phase_increment;
	lfo->raw = sine_10b[((lfo->phase_index >> 22) + _mod) & 1023];
	lfo->out = (lfo->raw - 512) * 0.001953125f;
	return lfo->out;
}
