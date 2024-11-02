/*
 * chorus.h
 *
 *  Created on: Feb 11, 2023
 *      Author: chrismcdowell
 */

#ifndef LIB_INCLUDE_CHORUS_H_
#define LIB_INCLUDE_CHORUS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "shared_delays.h"
#include "lfo.h"

typedef struct {
	lfo_t lfo;
	float filtered_lfo;
	float rate;
	float amount;
	float delay;
	float feedback;
	float balance;
}chorus_t;

float chorus_tick(chorus_t *c, shared_delay_t *d, float _input) RAMFUNC;

#ifdef __cplusplus
}
#endif

#endif /* LIB_INCLUDE_CHORUS_H_ */
