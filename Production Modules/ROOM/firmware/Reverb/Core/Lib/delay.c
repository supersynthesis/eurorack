/*
 * lerp_delay.c
 *
 *  Created on: Jan 7, 2023
 *      Author: chrismcdowell
 */

#include "delay.h"
#include "lerp.h"

float lerp_delay_tick(delay_typedef *d, int16_t _buf[], uint16_t _bufsize,
		float _input, float _delay, float _modulation) {
	float buf_read_position;

	d->buf_write_index++;
	if (d->buf_write_index > (_bufsize - 1)) {
		d->buf_write_index -= _bufsize;
	}

	_buf[d->buf_write_index] = _input;

	buf_read_position = d->buf_write_index - (_modulation * (1.0f - _delay))
			- ((_delay) * (_bufsize - 1));

	return lerp_int16(_buf, _bufsize, buf_read_position);
}

/*
#define BUF_SIZE 15000
int16_t buf[BUF_SIZE];
int16_t delaypos;
const static float mu = 0.5f;
#define delay(N) {if(N > BUF_SIZE) {return 0.0f;} uint16_t j=(i+N);if(j > BUF_SIZE-1) {j -= BUF_SIZE;}float delayed=buf[j];buf[i]=x+delayed*mu;x=delayed; i=j; }
#define ap(N) {if(N > BUF_SIZE) {return 0.0f;} uint16_t j=(i+N);if(j > BUF_SIZE-1) {j -= BUF_SIZE;}float delayed=buf[j];buf[i]=x -= delayed*mu;x=x*mu+delayed; i=j; }

float delays(float x, float t) {
	int16_t i = delaypos--;
	if (delaypos < 0) {
		delaypos += BUF_SIZE;
	}
	ap(149);
	ap(251);
	x *= t;
	ap(367);
	ap(479);
	x *= t;
	ap(607);
	ap(733);
	x *= t;
	ap(859);
	ap(1291);
	x *= t;
	ap(1447);
	ap(1483);
	x *= t;
	return x;
}
*/

