/*
 * opamp.h
 *
 *  Created on: Jan 21, 2023
 *      Author: chrismcdowell
 */

#ifndef INC_OPAMP_H_
#define INC_OPAMP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

typedef struct {
	float in_p;
	float in_n;
	float out;
} opamp_typedef;

void opamp_init(opamp_typedef *o);
uint8_t opamp_comparator(opamp_typedef *o, float _n, float _p, float _hysteresis);




#ifdef __cplusplus
}
#endif


#endif /* INC_OPAMP_H_ */
