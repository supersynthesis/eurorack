/*
 * super_filters.cpp
 *
 *  Created on: Jan 6, 2023
 *      Author: chrismcdowell
 */

#include "super_filters.h"

Svf::Svf(float _sample_rate, float _freq, float _q) {
	freq = (6.28f * _freq) / _sample_rate;
	q = 1.0f / _q;
}
void Svf::tick(float _input) {
	low = delay2 + freq * delay1;
	high = _input - low - (q * delay1);
	band = (freq * high) + delay1;

	delay1 = band;
	delay2 = low;
}
