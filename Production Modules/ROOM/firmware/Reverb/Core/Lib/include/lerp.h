/*
 * lerp.h
 *
 *  Created on: Jan 6, 2023
 *      Author: chrismcdowell
 */

#ifndef INC_LERP_H_
#define INC_LERP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

float lerp_int16(int16_t _buf[], uint16_t _bufsize, float position);
float lerp_const_float(const float *_buf, uint16_t _bufsize, float position);

#ifdef __cplusplus
}
#endif

#endif /* INC_LERP_H_ */
