/*
 * chorus.h
 *
 *  Created on: Nov 22, 2020
 *      Author: SUPER
 */

#ifndef INC_SANDBOX_H_
#define INC_SANDBOX_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "dynamic_smooth.h"
#include "c_filters.h"
#include "lfo.h"

#define NUM_LFOS 4
volatile lfo_t lfos[NUM_LFOS];

typedef struct {
	uint16_t hp_cutoff;
	uint16_t lp_cutoff;
	uint16_t feedback;
	uint16_t size;
} reverb_params_typedef;

volatile float feedback_pot;
volatile float hp_cutoff_pot;
volatile float lp_cutoff_pot;
volatile float size_pot;

float sandbox_tick(float _input) RAMFUNC;
void control_tick(reverb_params_typedef *params, float _input);
void sandbox_init();

float dither(float _input);
float limiter(float input);

#ifdef __cplusplus
}
#endif

#endif /* INC_SANDBOX_H_ */
