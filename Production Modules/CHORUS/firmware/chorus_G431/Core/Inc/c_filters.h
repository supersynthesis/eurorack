/*
 * c_filters.h
 *
 *  Created on: Jan 6, 2023
 *      Author: chrismcdowell
 */

#ifndef INC_C_FILTERS_H_
#define INC_C_FILTERS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

// note: SAMPLE_RATE must be defined in main.h

typedef struct {
	float low;
	float high;
	float band;
	float delay1;
	float delay2;
	float freq;
	float a;
	float q;
} svf_typedef;

void svf_init(svf_typedef *svf, float _freq, float _q);
void svf_tick(svf_typedef *svf, float _input);
void svf_set_freq(svf_typedef *svf, float _freq);
void svf_set_a_direct(svf_typedef *svf, float _a);

void svf_set_q(svf_typedef *svf, float _q);

float svf_get_low(svf_typedef *svf);

float svf_get_high(svf_typedef *svf);

float svf_get_band(svf_typedef *svf);

#ifdef __cplusplus
}
#endif

#endif /* INC_C_FILTERS_H_ */
