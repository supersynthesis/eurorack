/*
 * envelopes.c
 *
 *  Created on: Jan 21, 2023
 *      Author: chrismcdowell
 */

#include "envelopes.h"
#include "noise.h"

void env_init(env_t *e) {
	e->out = 0.0f;
	e->state = OFF;
	e->attack = 0.0f;
	e->decay = 0.0f;
	e->sustain = 0.0f;
	e->release = 0.0f;
	e->hold = 0.0f;
	e->hold_count = 0;
	e->target = 0.0f;
	e->last_target = 0.0f;
	e->rate = 0.0f;
	e->last_trig = 0;
}

void env_params_init(env_params_t *p) {
	p->l1 = 0.0f;
	p->l2 = 0.0f;
	p->l3 = 0.0f;
	p->l4 = 0.0f;
	p->r1 = 0.0f;
	p->r2 = 0.0f;
	p->r3 = 0.0f;
	p->r4 = 0.0f;
}

// attack - decay ***********************************************

uint8_t env_trig_ad(env_t *e, int16_t _trig) {
	uint8_t was_triggered = 0;
	if (_trig != 0 && e->last_trig == 0) {
		e->state = ATTACK;
		e->target = 2.0f;
		e->rate = e->attack;
		was_triggered = 1;
	}
	e->last_trig = _trig;
	return was_triggered;
}

float env_tick_ad(env_t *e) {
	switch (e->state) {
	case ATTACK:
		if (e->out > 1.0f) {
			e->state = DECAY;
			e->target = 0.0f;
			e->rate = e->decay;
		}
		break;
	case DECAY:
		e->rate = e->decay;
		break;
	default:
		break;
	}
	e->out += (e->target - e->out) * e->rate;

	return e->out;
}

// hold - attack - decay ****************************************

uint8_t env_trig_had(env_t *e, int16_t _trig, float _hold) {
	uint8_t was_triggered = 0;
	if (_trig != 0 && e->last_trig == 0) {
		e->state = HOLD;
		e->hold = _hold;
		e->target = 0.0f;
		was_triggered = 1;
	}
	e->last_trig = _trig;
	return was_triggered;
}

float env_tick_had(env_t *e) {
	switch (e->state) {
	case HOLD:
		e->hold_count++;
		if ((e->hold_count / SAMPLE_RATE) > e->hold) {
			e->target = 2.0f;
			e->rate = e->attack;
			e->state = ATTACK;
			e->hold_count = 0;
		}
		break;
	case ATTACK:
		if (e->out > 1.0f) {
			e->state = DECAY;
			e->target = 0.0f;
			e->rate = e->decay;
		}
		break;
	case DECAY:
		e->rate = e->decay;
		if (e->out < 0.00001f) {
			e->state = OFF;
		}
		break;
	default:
		break;
	}
	if (e->state != OFF) {
		e->out += (e->target - e->out) * e->rate;
		//e->dithered_out = e->out + ((noise() >> 22) - 512.0f) * 0.0000001f;
		return e->out;
	} else {
		return 0.0f;
	}
}

// attack - hold - decay ****************************************

float env_tick_ahd(env_t *e) {
	// not implemented
	return e->out;
}

// decay ********************************************************

uint8_t env_trig_d(env_t *e, int16_t _trig) {
	uint8_t was_triggered = 0;
	if (_trig != 0 && e->last_trig == 0) {
		e->state = DECAY;
		e->target = 0.0f;
		e->rate = e->decay;
		e->out = 1.0f;
		was_triggered = 1;
	}
	e->last_trig = _trig;
	return was_triggered;
}

float env_tick_d(env_t *e) {
	e->out += (e->target - e->out) * e->rate;
	return e->out;
}

// decay - release **********************************************

uint8_t env_trig_dr(env_t *e, int16_t _trig, float _start) {
	uint8_t was_triggered = 0;
	if (_trig != 0 && e->last_trig == 0) {
		e->state = DECAY;
		e->target = 0.0f;
		e->rate = e->decay;
		e->out = _start;
		was_triggered = 1;
	}
	e->last_trig = _trig;
	return was_triggered;
}

float env_tick_dr(env_t *e) {
	switch (e->state) {
	case DECAY:
		if (e->out < (e->sustain + 0.001f)) {
			e->state = RELEASE;
			e->rate = e->release;
			e->target = 0.0f;
		}
		break;
	case RELEASE:
		if (e->out < 0.00001f) {
			e->out = 0.0f;
			e->state = OFF;
		}
		break;
	default:
		break;
	}

	if (e->state != OFF) {
		e->out += (e->target - e->out) * e->rate;
	}
	return e->out;
}

// hold - decay *************************************************

uint8_t env_trig_hd(env_t *e, int16_t _trig, float _hold) {
	uint8_t was_triggered = 0;
	if (_trig != 0 && e->last_trig == 0) {
		e->state = HOLD;
		e->hold = _hold;
		was_triggered = 1;
	}
	e->last_trig = _trig;
	return was_triggered;
}

float env_tick_hd(env_t *e) {

	if (e->state == HOLD) {
		e->hold_count++;
		if ((e->hold_count / SAMPLE_RATE) > e->hold) {
			e->target = 0.0f;
			e->rate = e->decay;
			e->out = 1.0f;
			e->state = DECAY;
			e->hold_count = 0;
		}
	}
	e->out += (e->target - e->out) * e->rate;
	return e->out;
}

// 2-stage ******************************************************

uint8_t env_trig_2stage(env_t *e, env_params_t *p, int16_t _trig) {
	uint8_t was_triggered = 0;
	if (_trig != 0 && e->last_trig == 0) {
		e->state = R1;
		e->out = p->l1;
		was_triggered = 1;
	}
	e->last_trig = _trig;
	return was_triggered;
}

float env_tick_2stage_lin(env_t *e, env_params_t *p) {
	switch (e->state) {
	case R1:
		e->rate = p->r1;
		e->target = p->l2;
		if (p->l1 < p->l2) {
			if (e->out >= p->l2) {
				e->state = R2;
			}
		} else {
			if (e->out <= p->l2) {
				e->state = R2;
			}
		}
		break;
	case R2:
		e->rate = p->r2;
		e->target = p->l3;
		if (p->l2 < p->l3) {
			if (e->out >= p->l3) {
				e->state = OFF;
			}
		} else {
			if (e->out <= p->l3) {
				e->state = OFF;
			}
		}
		break;
	default:
		break;
	}
	if (e->state != OFF) {
		e->out += (e->last_target - e->target) / e->rate;
	}
	return e->out;
}

float env_tick_2stage_rc(env_t *e, env_params_t *p) {
	switch (e->state) {
	case R1:
		e->rate = p->r1;
		if (p->l1 < p->l2) {
			e->target = 1.0f;
			if (e->out >= p->l2) {
				e->state = R2;
			}
		} else {
			e->target = 0.0f;
			if (e->out <= p->l2) {
				e->state = R2;
			}
		}
		break;
	case R2:
		e->rate = p->r2;
		if (p->l2 < p->l3) {
			e->target = 1.0f;
			if (e->out >= p->l3) {
				e->state = OFF;
			}
		} else {
			e->target = 0.0f;
			if (e->out <= p->l3) {
				e->state = OFF;
			}
		}
		break;
	default:
		break;
	}
	if (e->state != OFF) {
		e->out += (e->target - e->out) * e->rate;
	}
	return e->out;
}

uint8_t env_trig_hd_group(env_t *e, int16_t _trig, uint16_t _num) {
	uint8_t was_triggered = 0;
	for (uint16_t i = 0; i < _num; i++) {
		if (_trig != 0 && e[i].last_trig == 0) {
			e[i].state = HOLD;
			e[i].hold = (noise() >> 22) / 1024.0f;
			was_triggered = 1;
		}
		e[i].last_trig = _trig;
	}
	return was_triggered;
}

// rc style param setters

void env_set_attack(env_t *e, float _attack) {
	e->attack = env_s_to_hz(_attack);
}

void env_set_decay(env_t *e, float _decay) {
	e->decay = env_s_to_hz(_decay);
}

void env_set_sustain(env_t *e, float _sustain) {
	e->sustain = _sustain;
}

void env_set_release(env_t *e, float _release) {
	e->release = env_s_to_hz(_release);
}

void env_set_hold(env_t *e, float _hold) {
	e->hold = _hold;
}

void env_set_target(env_t *e, float _target) {
	e->target = _target;
}

void env_set_state(env_t *e, env_state _state) {
	e->state = _state;
}

float env_s_to_hz(float _s) {
	if (_s < 0.0001f) {
		_s = 0.0001f;
	}
	// this 0.2 is trying to make this a 5RC kind of thing
	float hz = (6.28f * (0.2f / _s)) / SAMPLE_RATE;
	return hz;
}

// multi-stage param setters

void env_set_l1(env_params_t *p, float _l) {
	p->l1 = _l;
}

void env_set_l2(env_params_t *p, float _l) {
	p->l2 = _l;
}

void env_set_l3(env_params_t *p, float _l) {
	p->l3 = _l;
}

void env_set_l4(env_params_t *p, float _l) {
	p->l4 = _l;
}

void env_set_r1(env_params_t *p, float _s) {
	p->r1 = _s * SAMPLE_RATE;
}

void env_set_r2(env_params_t *p, float _s) {
	p->r2 = _s * SAMPLE_RATE;
}

void env_set_r3(env_params_t *p, float _s) {
	p->r3 = _s * SAMPLE_RATE;
}

void env_set_r4(env_params_t *p, float _s) {
	p->r4 = _s * SAMPLE_RATE;
}
