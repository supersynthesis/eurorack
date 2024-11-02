/*
 * operator.h
 *
 *  Created on: Jan 23, 2023
 *      Author: chrismcdowell
 */

#ifndef OPERATOR_H_
#define OPERATOR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "envelopes.h"

typedef struct {
	uint16_t raw;
	float output;
	float amplitude;
	float frequency;
	uint32_t phase_increment;
	uint32_t phase_index;
} osc_t;

typedef struct {
	osc_t osc;
	env_t env;
	float modulation;
} operator_t;

typedef struct {
	operator_t carrier;
	operator_t modulator;
	float ratio;
	float fm_amount;
	float modulation;
	float out;
}fm_voice_t;

float osc_tick_10b(osc_t *osc, float _frequency, int16_t _mod);
float osc_tick_16b(osc_t *osc, float _frequency, int16_t _mod);
void osc_sync(osc_t *op);

float operator_tick(operator_t *op, float _frequency, int16_t _mod);
float operator_tick_had(operator_t *op, float _frequency, int16_t _mod);
void operator_init(operator_t *op);

uint8_t fm_voice_trig(fm_voice_t *v, uint8_t _trig);
uint8_t fm_voice_trig_had(fm_voice_t *v, uint8_t _trig, float _hold);
float fm_voice_tick(fm_voice_t *v, float _frequency, float _amt, float _fb);
float fm_voice_tick_had(fm_voice_t *v, float _frequency, float _amt, float _fb);
void fm_voice_set_ratio(fm_voice_t *v, float _ratio);

// these have lazy names, sorry future me. but they are fm voice tick had with square or saw feedback applied to the modulator or carrier
float fmvthad_sq_m(fm_voice_t *v, float _frequency, float _amt, float _fb);
float fmvthad_sw_m(fm_voice_t *v, float _frequency, float _amt, float _fb);
float fmvthad_sq_c(fm_voice_t *v, float _frequency, float _amt, float _fb);
float fmvthad_sw_c(fm_voice_t *v, float _frequency, float _amt, float _fb);

#ifdef __cplusplus
}
#endif

#endif /* OPERATOR_H_ */
