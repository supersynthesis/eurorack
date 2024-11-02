/*
 * operator.c
 *
 *  Created on: Jan 8, 2023
 *      Author: chrismcdowell
 */

#include "operator.h"
#include "big_sine_wave.h"
#include "main.h"
#include "noise.h"

float osc_tick_10b(osc_t *osc, float _frequency, int16_t _mod) {
	osc->phase_increment = PHINC_SCALE * _frequency;
	osc->phase_index += osc->phase_increment;
	osc->output = sine_10b[((osc->phase_index >> 22) + _mod) & 1023] - 511;
	return osc->output;
}

float osc_tick_16b(osc_t *osc, float _frequency, int16_t _mod) {
	osc->phase_increment = PHINC_SCALE * _frequency;
	osc->phase_index += osc->phase_increment;
	osc->output = sine_16b[((osc->phase_index >> 22) + _mod) & 1023] - 32767;
	return osc->output;
}

void osc_sync(osc_t *osc) {
	osc->phase_index = 0;
}

float operator_tick(operator_t *op, float _frequency, int16_t _mod) {
	return osc_tick_16b(&op->osc, _frequency, _mod) * env_tick_ad(&op->env);
}

float operator_tick_had(operator_t *op, float _frequency, int16_t _mod) {
	return osc_tick_16b(&op->osc, _frequency, _mod) * env_tick_had(&op->env);
}

void operator_init(operator_t *op) {
	env_init(&op->env);
}

uint8_t fm_voice_trig(fm_voice_t *v, uint8_t _trig) {
	uint8_t was_triggered = 0;
	was_triggered = env_trig_ad(&v->carrier.env, _trig);
	was_triggered &= env_trig_ad(&v->modulator.env, _trig);
	return was_triggered;
}

uint8_t fm_voice_trig_had(fm_voice_t *v, uint8_t _trig, float _hold) {
	uint8_t was_triggered = 0;
	was_triggered = env_trig_had(&v->carrier.env, _trig, _hold);
	was_triggered &= env_trig_had(&v->modulator.env, _trig, _hold);
	return was_triggered;
}

float fm_voice_tick(fm_voice_t *v, float _frequency, float _amt, float _fb) {
	float modulation = operator_tick(&v->modulator, _frequency * v->ratio, 0);
	v->out = operator_tick(&v->carrier, _frequency, (modulation * _amt) + (_fb * v->out));
	return v->out;
}

float fm_voice_tick_had(fm_voice_t *v, float _frequency, float _amt, float _fb) {
	float modulation = operator_tick_had(&v->modulator, _frequency * v->ratio, 0);
	v->out = operator_tick_had(&v->carrier, _frequency, (modulation * _amt) + (_fb * v->out));
	return v->out;
}

float fmvthad_sq_m(fm_voice_t *v, float _frequency, float _amt, float _fb) {
	v->modulation = operator_tick_had(&v->modulator, _frequency * v->ratio, (_fb * v->out * v->out * -0.000013f));
	v->out = operator_tick_had(&v->carrier, _frequency, (v->modulation * _amt));
	return v->out;
}

float fmvthad_sw_m(fm_voice_t *v, float _frequency, float _amt, float _fb) {
	v->modulation = operator_tick_had(&v->modulator, _frequency * v->ratio, (_fb * v->out * 0.45f));
	v->out = operator_tick_had(&v->carrier, _frequency, (v->modulation * _amt));
	return v->out;
}

float fmvthad_sq_c(fm_voice_t *v, float _frequency, float _amt, float _fb) {
	v->modulation = operator_tick(&v->modulator, _frequency * v->ratio, 0);
	v->out = operator_tick(&v->carrier, _frequency, (v->modulation * _amt) + (_fb * v->out * v->out * -0.000026f));
	return v->out;
}

float fmvthad_sw_c(fm_voice_t *v, float _frequency, float _amt, float _fb) {
	v->modulation = operator_tick(&v->modulator, _frequency * v->ratio, 0);
	v->out = operator_tick(&v->carrier, _frequency, (v->modulation * _amt) + (_fb * v->out * 0.9f));
	return v->out;
}

void fm_voice_set_ratio(fm_voice_t *v, float _ratio) {
	v->ratio = _ratio;
}

