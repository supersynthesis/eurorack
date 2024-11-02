/*
 * lerp_delay.h
 *
 *  Created on: Jan 7, 2023
 *      Author: chrismcdowell
 */

#ifndef INC_DELAY_H_
#define INC_DELAY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

typedef struct {
	uint16_t buf_write_index;
} delay_typedef;

float lerp_delay_tick(delay_typedef *d, int16_t _buf[], uint16_t _bufsize,
		float _input, float _delay, float _modulation);

float delays(float x, float t);

#ifdef __cplusplus
}
#endif

#endif /* INC_DELAY_H_ */
