/*
 * lfo.h
 *
 *  Created on: Jan 8, 2023
 *      Author: chrismcdowell
 */

#ifndef LFO_H_
#define LFO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

typedef struct {
	uint16_t raw;
	float out;
	uint32_t phase_increment;
	uint32_t phase_index;
} lfo_t;

uint32_t lfo_tick(volatile lfo_t *lfo, float _frequency, int16_t _mod);
int16_t op_tick(volatile lfo_t *lfo, float _frequency, int16_t _mod);

#ifdef __cplusplus
}
#endif

#endif /* LFO_H_ */
