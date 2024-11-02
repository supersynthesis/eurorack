/*
 * dynamic_smooth.h
 *
 *  Created on: Sep 19, 2020
 *      Author: SUPER
 */

#ifndef INC_DYNAMIC_SMOOTH_H_
#define INC_DYNAMIC_SMOOTH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define DYN_SMOOTH_SAMPLE_RATE 53000.0f

typedef struct {
	//init values
	float g0;
	float sense;

	//tick values
	float low1;
	float low2;
	float low1z;
	float low2z;
	float bandz;
	float out;
}dynamic_smooth;

float dynamic_smooth_tick(dynamic_smooth* _smooth, float in);
void dynamic_smooth_init(dynamic_smooth* _smooth, float _base, float _sensitivity);

#ifdef __cplusplus
}
#endif
#endif /* INC_DYNAMIC_SMOOTH_H_ */
