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
// **********************************************************************
// SVF
// **********************************************************************

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

// **********************************************************************
// one pole
// **********************************************************************

typedef struct {
	float d1;
	float a;
	float in;
} onepole_typedef;

void onepole_tick(onepole_typedef *f, float _input);

void onepole_set_freq(onepole_typedef *f, float _freq);

void onepole_set_a_direct(onepole_typedef *f, float _a);

float onepole_get_low(onepole_typedef *f);

float onepole_get_high(onepole_typedef *f);

// **********************************************************************
// all pass
// **********************************************************************

typedef struct {
	float out;
	float in;
	uint16_t buf_write_index;
	uint16_t bufsize;
} allpass_typedef;

float allpass_tick(allpass_typedef *ap, int16_t _buf[], uint16_t _bufsize,
		float _input, float _gain, float _delay, float _modulation);

// **********************************************************************

#ifdef __cplusplus
}
#endif

#endif /* INC_C_FILTERS_H_ */
