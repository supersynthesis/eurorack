/*
 * super_filters.h
 *
 *  Created on: Jan 6, 2023
 *      Author: chrismcdowell
 */

#ifndef INC_SUPER_FILTERS_H_
#define INC_SUPER_FILTERS_H_

#include "main.h"

class Svf {
private:

	float low;
	float high;
	float band;
	float delay1;
	float delay2;
	float freq;
	float q;
	float sample_rate;

public:

	Svf(float _sample_rate, float _freq, float _q);
	void tick(float _input);
	float getLow() {
		return low;
	}
	float getHigh() {
		return high;
	}
	float getBand() {
		return band;
	}

};

#endif /* INC_SUPER_FILTERS_H_ */
