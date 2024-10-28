/*
 * 2op_main.h
 *
 *  Created on: Jun 4, 2020
 *      Author: SUPER
 */


#ifndef INC_2OP_MAIN_H_
#define INC_2OP_MAIN_H_

#include "main.h"

//*****************************************************************************************

uint16_t expo_lut[1024];

typedef enum {
	ATTACK, DECAY, RELEASE, OFF, RETRIG
} envelope_stage;

typedef struct {
	volatile float output;
	volatile envelope_stage stage;
	volatile float rate;
	volatile float rate_offset;
	volatile float attack_offset;
	volatile float release_offset;
	volatile float cutoff;
	volatile float target;
	volatile float attack;
	volatile float decay;
	volatile float sustain;
	volatile float release;
	volatile char one_shot;
	volatile uint8_t gate;
	volatile uint8_t trig;
} soft_adsr;

void adsr_structinit(soft_adsr* adsr);

void run_adsr(soft_adsr* adsr);

void run_ar(soft_adsr* adsr);

//************************************************************************************************

//#define ONLY_ONE_SHOTS
#define SMOOTH_ATTACK
#define SMOOTH_ATTACK_INCREMENT 0.1f

#define ENV_INIT 1.0f
#define KHZ_PRE_FILTER

float noise_offset;


typedef struct {
	//uint is cool!
	int32_t output;
	float amplitude;
	float frequency;
	uint32_t phase_increment;
	uint32_t phase_index;
	//uint is cool!
	int32_t modulation;
	soft_adsr ADSR;
} Operator;

float filtered_decay_jack;
float decay_sum;
float ENV_AMT;
float ENV_OFFSET;
int32_t output, voice1, voice2;
float env_lowpass;
uint32_t dummy;
//int32_t freqSum;
float freqSum;
float khz_pot;
float khz_in;
float filtered_khz_in;
uint8_t note;
float fm_ratio;
uint8_t trig, last_trig;
float env_lp;
Operator OP1, OP2;

uint32_t operator_run(Operator *OP, float envelope);

void operator_structinit(Operator *OP);

void check_gate();

void check_trig();

void set_adsr_parameters(soft_adsr *adsr);

void slow_2op_parameter_loop();

int16_t tanh_table[256];

void tanh_table_init();

void main_2OP_loop();

//todo needs to run in slow loop
//		run_ar(&OP1.ADSR);

#endif /* INC_2OP_MAIN_H_ */
