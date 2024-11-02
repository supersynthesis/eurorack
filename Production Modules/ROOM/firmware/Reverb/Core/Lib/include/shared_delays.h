/*
 * shared_delays.h
 *
 *  Created on: Jan 8, 2023
 *      Author: chrismcdowell
 */

#ifndef INC_SHARED_DELAYS_H_
#define INC_SHARED_DELAYS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "delay.h"

typedef struct {
	int16_t *buf;
	uint16_t bufsize;
	int16_t write;
	int16_t index;
	float ms_scale;
	float d1;
} shared_delay_t;

void shared_delay_tick(shared_delay_t *d);

float shared_delay(shared_delay_t *d, float _delay, float _input, float _fb);

float shared_allpass(shared_delay_t *ap, float _delay, float _input, float _fb);

float shared_modulated_delay(shared_delay_t *d, float _delay, float _input, float _fb, float _mod);

float shared_modulated_delay_float(shared_delay_t *d, float _delay, float _input, float _fb, float _mod);

float shared_nested_allpass(shared_delay_t *ap, float _delay, float _input, float _fb, float _delay2, float _fb2);

RAMFUNC float shared_modulated_allpass(shared_delay_t *ap, float _delay, float _input, float _fb, float _mod);

void shared_delay_init(shared_delay_t *d, int16_t *_buf, uint16_t _bufsize);

#ifdef __cplusplus
}
#endif

#endif /* INC_SHARED_DELAYS_H_ */
