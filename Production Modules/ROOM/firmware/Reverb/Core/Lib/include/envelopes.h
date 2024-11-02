/*
 * envelopes.h
 *
 *  Created on: Jan 21, 2023
 *      Author: chrismcdowell
 */

#ifndef INC_ENVELOPES_H_
#define INC_ENVELOPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

typedef enum {
	ATTACK, DECAY, SUSTAIN, RELEASE, HOLD, R1, R2, R3, R4, OFF
} env_state;

typedef struct {
	float out;
	float dithered_out;
	env_state state;
	float attack;
	float decay;
	float sustain;
	float release;
	float hold;
	uint32_t hold_count;
	float target;
	float last_target;
	float rate;
	int16_t last_trig;
} env_t;

typedef struct {
	float l1;
	float l2;
	float l3;
	float l4;
	float r1;
	float r2;
	float r3;
	float r4;
} env_params_t;

void env_init(env_t *e);
void env_params_init(env_params_t *p);

// processing tick
float env_tick_ad(env_t *e);
float env_tick_had(env_t *e);
float env_tick_ahd(env_t *e);
float env_tick_d(env_t *e);
float env_tick_dr(env_t *e);
float env_tick_hd(env_t *e);

uint8_t env_trig_2stage(env_t *e, env_params_t *p, int16_t _trig);
float env_tick_2stage_lin(env_t *e, env_params_t *p);
float env_tick_2stage_rc(env_t *e, env_params_t *p);

// triggers
uint8_t env_trig_ad(env_t *e, int16_t _trig);
uint8_t env_trig_had(env_t *e, int16_t _trig, float _hold);
uint8_t env_trig_d(env_t *e, int16_t _trig);
uint8_t env_trig_dr(env_t *e, int16_t _trig, float _start);
uint8_t env_trig_hd(env_t *e, int16_t _trig, float _hold);
uint8_t env_trig_hd_group(env_t *e, int16_t _trig, uint16_t _num);

// rc params
void env_set_attack(env_t *e, float _attack);
void env_set_decay(env_t *e, float _decay);
void env_set_sustain(env_t *e, float _sustain);
void env_set_release(env_t *e, float _release);
void env_set_hold(env_t *e, float _hold);
void env_set_target(env_t *e, float _target);
void env_set_state(env_t *e, env_state _state);

// multi-stage params
void env_set_l1(env_params_t *p, float _l);
void env_set_l2(env_params_t *p, float _l);
void env_set_l3(env_params_t *p, float _l);
void env_set_l4(env_params_t *p, float _l);
void env_set_r1(env_params_t *p, float _ms);
void env_set_r2(env_params_t *p, float _ms);
void env_set_r3(env_params_t *p, float _ms);
void env_set_r4(env_params_t *p, float _ms);

// helpers
float env_s_to_hz(float _s);

#ifdef __cplusplus
}
#endif

#endif /* INC_ENVELOPES_H_ */
