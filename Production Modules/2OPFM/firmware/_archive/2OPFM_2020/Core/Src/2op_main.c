/*
 * 2op_main.c
 *
 *  Created on: Jun 4, 2020
 *      Author: SUPER
 */

#include "2op_main.h"
#include "big_expo.h"

uint16_t expo_lut[1024] = { 65535, 64771, 64017, 63271, 62534, 61805, 61085, 60374, 59670, 58975, 58288, 57609, 56938, 56274, 55619, 54971, 54330,
		53697, 53072, 52454, 51842, 51238, 50642, 50052, 49468, 48892, 48322, 47760, 47203, 46653, 46110, 45572, 45042, 44517, 43998, 43486, 42979,
		42478, 41983, 41494, 41011, 40533, 40061, 39594, 39133, 38677, 38226, 37781, 37341, 36906, 36476, 36051, 35631, 35216, 34805, 34400, 33999,
		33603, 33212, 32825, 32442, 32064, 31691, 31321, 30957, 30596, 30239, 29887, 29539, 29195, 28855, 28519, 28186, 27858, 27533, 27213, 26896,
		26582, 26272, 25966, 25664, 25365, 25069, 24777, 24489, 24203, 23921, 23643, 23367, 23095, 22826, 22560, 22297, 22037, 21781, 21527, 21276,
		21028, 20783, 20541, 20302, 20065, 19832, 19600, 19372, 19146, 18923, 18703, 18485, 18270, 18057, 17846, 17639, 17433, 17230, 17029, 16831,
		16635, 16441, 16249, 16060, 15873, 15688, 15505, 15325, 15146, 14970, 14795, 14623, 14452, 14284, 14118, 13953, 13791, 13630, 13471, 13314,
		13159, 13006, 12854, 12705, 12557, 12410, 12266, 12123, 11982, 11842, 11704, 11568, 11433, 11300, 11168, 11038, 10909, 10782, 10657, 10532,
		10410, 10288, 10169, 10050, 9933, 9817, 9703, 9590, 9478, 9368, 9259, 9151, 9044, 8939, 8835, 8732, 8630, 8529, 8430, 8332, 8235, 8139, 8044,
		7950, 7858, 7766, 7676, 7586, 7498, 7410, 7324, 7239, 7154, 7071, 6989, 6907, 6827, 6747, 6669, 6591, 6514, 6438, 6363, 6289, 6216, 6144,
		6072, 6001, 5931, 5862, 5794, 5726, 5660, 5594, 5529, 5464, 5400, 5338, 5275, 5214, 5153, 5093, 5034, 4975, 4917, 4860, 4803, 4747, 4692,
		4637, 4583, 4530, 4477, 4425, 4373, 4323, 4272, 4222, 4173, 4125, 4077, 4029, 3982, 3936, 3890, 3845, 3800, 3755, 3712, 3668, 3626, 3583,
		3542, 3500, 3460, 3419, 3380, 3340, 3301, 3263, 3225, 3187, 3150, 3113, 3077, 3041, 3006, 2971, 2936, 2902, 2868, 2835, 2802, 2769, 2737,
		2705, 2673, 2642, 2612, 2581, 2551, 2521, 2492, 2463, 2434, 2406, 2378, 2350, 2323, 2296, 2269, 2242, 2216, 2191, 2165, 2140, 2115, 2090,
		2066, 2042, 2018, 1995, 1971, 1948, 1926, 1903, 1881, 1859, 1837, 1816, 1795, 1774, 1753, 1733, 1713, 1693, 1673, 1654, 1634, 1615, 1596,
		1578, 1559, 1541, 1523, 1506, 1488, 1471, 1454, 1437, 1420, 1403, 1387, 1371, 1355, 1339, 1323, 1308, 1293, 1278, 1263, 1248, 1234, 1219,
		1205, 1191, 1177, 1163, 1150, 1136, 1123, 1110, 1097, 1084, 1072, 1059, 1047, 1035, 1023, 1011, 999, 987, 976, 964, 953, 942, 931, 920, 910,
		899, 889, 878, 868, 858, 848, 838, 828, 819, 809, 800, 790, 781, 772, 763, 754, 745, 737, 728, 720, 711, 703, 695, 687, 679, 671, 663, 655,
		648, 640, 633, 625, 618, 611, 604, 597, 590, 583, 576, 569, 563, 556, 550, 543, 537, 531, 524, 518, 512, 506, 500, 495, 489, 483, 477, 472,
		466, 461, 456, 450, 445, 440, 435, 430, 425, 420, 415, 410, 405, 400, 396, 391, 387, 382, 378, 373, 369, 365, 360, 356, 352, 348, 344, 340,
		336, 332, 328, 324, 321, 317, 313, 309, 306, 302, 299, 295, 292, 288, 285, 282, 278, 275, 272, 269, 266, 263, 260, 257, 254, 251, 248, 245,
		242, 239, 236, 234, 231, 228, 226, 223, 220, 218, 215, 213, 210, 208, 205, 203, 201, 198, 196, 194, 191, 189, 187, 185, 183, 181, 178, 176,
		174, 172, 170, 168, 166, 164, 162, 161, 159, 157, 155, 153, 151, 150, 148, 146, 144, 143, 141, 139, 138, 136, 135, 133, 132, 130, 129, 127,
		126, 124, 123, 121, 120, 118, 117, 116, 114, 113, 112, 110, 109, 108, 107, 105, 104, 103, 102, 100, 99, 98, 97, 96, 95, 94, 93, 91, 90, 89,
		88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 79, 78, 77, 76, 75, 74, 73, 72, 72, 71, 70, 69, 68, 67, 67, 66, 65, 64, 64, 63, 62, 61, 61, 60, 59,
		59, 58, 57, 57, 56, 55, 55, 54, 53, 53, 52, 52, 51, 50, 50, 49, 49, 48, 47, 47, 46, 46, 45, 45, 44, 44, 43, 43, 42, 42, 41, 41, 40, 40, 39,
		39, 38, 38, 38, 37, 37, 36, 36, 35, 35, 35, 34, 34, 33, 33, 33, 32, 32, 31, 31, 31, 30, 30, 30, 29, 29, 29, 28, 28, 28, 27, 27, 27, 26, 26,
		26, 26, 25, 25, 25, 24, 24, 24, 23, 23, 23, 23, 22, 22, 22, 22, 21, 21, 21, 21, 20, 20, 20, 20, 19, 19, 19, 19, 19, 18, 18, 18, 18, 18, 17,
		17, 17, 17, 17, 16, 16, 16, 16, 16, 15, 15, 15, 15, 15, 15, 14, 14, 14, 14, 14, 14, 13, 13, 13, 13, 13, 13, 12, 12, 12, 12, 12, 12, 12, 11,
		11, 11, 11, 11, 11, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4,
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0 };

void adsr_structinit(soft_adsr *adsr) {
	adsr->output = ENV_INIT;
	adsr->attack = 0.0f;
	adsr->decay = 0.0f;
	adsr->sustain = 0.0f;
	adsr->release = 0.0f;
	adsr->stage = OFF;
	adsr->rate = 0.0f;
	adsr->rate_offset = 0.0f;
	adsr->cutoff = 0.0f;
	adsr->target = ENV_INIT;
	adsr->one_shot = 0;
}

void run_adsr(soft_adsr *adsr) {

	if (adsr->output < 0.01f) {
		adsr->one_shot = 0;
	}

	if (adsr->stage == ATTACK) {

		adsr->target = 1.0f;
		adsr->rate = adsr->attack;
		//attack threshold
		if (adsr->output > 0.9f) {
			adsr->stage = DECAY;
		}
	}

//sustain at decay
	if (adsr->stage == DECAY) {
		adsr->rate = adsr->decay;
		adsr->target = adsr->sustain;
		if (adsr->one_shot) {
			if (adsr->output < (adsr->sustain + 0.01f)) {
				adsr->stage = RELEASE;
			}
		}
	}
//low at release
	if (adsr->stage == RELEASE) {
		adsr->rate = adsr->release;
		adsr->target = 0.0f;
	}

	adsr->cutoff = (adsr->rate + adsr->rate_offset) * 0.1f;

	if (adsr->cutoff > 0.99) {
		adsr->cutoff = 0.99;
	}
	if (adsr->cutoff < 0.0) {
		adsr->cutoff = 0;
	}

	adsr->output += (adsr->target - adsr->output) * adsr->cutoff;
}

void run_ar(soft_adsr *adsr) {

	if (adsr->output < 0.01f) {
		adsr->one_shot = 0;
	}

	if (adsr->stage == ATTACK) {

		adsr->target = 1.0f;
		adsr->rate = adsr->attack + adsr->attack_offset;
		//attack threshold
		if (adsr->one_shot) {
			if (adsr->output > 0.9f) {
				adsr->stage = RELEASE;
			}
		}
	}

//low at release
	if (adsr->stage == RELEASE) {
		adsr->rate = adsr->release + adsr->release_offset;
		adsr->target = 0.0f;
	}

	adsr->cutoff = (adsr->rate + adsr->rate_offset) * 0.1f;
	//adsr->cutoff = adsr->rate;

	if (adsr->cutoff > 0.99) {
		adsr->cutoff = 0.99;
	}
	if (adsr->cutoff < 0.0) {
		adsr->cutoff = 0;
	}

	adsr->output += (adsr->target - adsr->output) * adsr->cutoff;
}

void run_linear_a_expo_r(soft_adsr *adsr) {
	//one shot style smooth attack

	if (adsr->output < 0.01f) {
		adsr->one_shot = 0;
	}

	if (adsr->stage == ATTACK) {

		adsr->output += SMOOTH_ATTACK_INCREMENT;
		adsr->rate = adsr->attack + adsr->attack_offset;
		//attack threshold
		if (adsr->output > 0.95f) {
			adsr->stage = RELEASE;
		}
	} else {

		//low at release
		if (adsr->stage == RELEASE) {
			adsr->rate = adsr->release + adsr->release_offset;
			adsr->target = 0.0f;
		}

		adsr->cutoff = (adsr->rate + adsr->rate_offset) * 0.1f;
		//adsr->cutoff = adsr->rate;

		if (adsr->cutoff > 0.99) {
			adsr->cutoff = 0.99;
		}
		if (adsr->cutoff < 0.0) {
			adsr->cutoff = 0;
		}

		adsr->output += (adsr->target - adsr->output) * adsr->cutoff;
	}
}

//*****************************************************************************************************

uint32_t operator_run(Operator *OP, float envelope) {
	OP->phase_index += OP->phase_increment;
	OP->output = (big_sine_wave[((OP->phase_index >> 22) + (int32_t) (OP->modulation * ENV_AMT)) & 1023] - 32768) * envelope;
	return OP->phase_index;
}

void operator_structinit(Operator *OP) {
	OP->output = 0;
	OP->amplitude = 1.0f;
	OP->frequency = 440.0f;
	OP->phase_increment = ((4294967295) * (OP->frequency)) / 44100.0f;
}

void check_gate() {
	//read gate
	gate = !HAL_GPIO_ReadPin(GATE_PORT, GATE_PIN);

	//if low to high transition occurs
	if (gate) {
		if (!last_gate) {
			//set stage to attack
#ifdef ONLY_ONE_SHOTS
			OP1.phase_index = 0;
			OP2.phase_index = 0;
			OP1.ADSR.output = 1.0f;
			OP1.ADSR.stage = RELEASE;
			OP1.ADSR.one_shot = 0;
#else
			//OP1.phase_index = 0;
			//OP2.phase_index = 0;
			OP1.ADSR.stage = ATTACK;
			//OP1.ADSR.output = 1.0f;
			OP1.ADSR.one_shot = 0;
#endif

		}
	}

	last_gate = gate;

}

void check_trig() {
	//read trig
	trig = !HAL_GPIO_ReadPin(TRIG_PORT, TRIG_PIN);

	//if low to high transition occurs
	if (trig) {
		if (!last_trig) {
			if (OP1.ADSR.output < 0.3f) {
				//set stage to attack
				OP1.phase_index = 0;
				OP2.phase_index = 0;
				OP1.ADSR.output = 1.0f;
				OP1.ADSR.stage = RELEASE;
				OP1.ADSR.one_shot = 0;
			}
		}
	}

	//if high to low transistion occurs
	if (!trig) {
		if (last_trig) {
			//set stage to release
		}
	}
	last_trig = trig;
}

void set_adsr_parameters(soft_adsr *adsr) {
	adsr->rate_offset = 0.0005f;
	adsr->attack = 7.0f;

	filtered_decay_jack += (expo_lut[adc_data_10b[DECAY_JACK]] - filtered_decay_jack) * 0.02f;

	int16_t jin_offset;
	jin_offset = adc_data_10b[DECAY_SLIDER] - (adc_data_10b[DECAY_JACK] - 495);
	if (jin_offset < 0) {
		jin_offset = 0;
	}
	if (jin_offset > 1023) {
		jin_offset = 1023;
	}
	decay_sum = expo_lut[jin_offset] + 100.0f;
	adsr->release = (decay_sum) / 100000.0f;

}

void slow_2op_parameter_loop() {
	//loop
	check_gate();
	check_trig();
	set_adsr_parameters(&OP1.ADSR);
}


//fast interrupt for audio
void main_2OP_loop() {

	ENV_OFFSET += (((((960 - adc_data_10b[FM_JACK]) - 512)) / 512.0f) - ENV_OFFSET) * 0.01f;

	ENV_AMT = (adc_data_10b[FM_SLIDER] / 1600.0f) + ENV_OFFSET;

	if (ENV_AMT < 0.0f) {
		ENV_AMT = 0.0f;
	}

	//khz pot, 1p filter
	khz_pot += ((1023 - adc_data_10b[KHZ_POT]) - khz_pot) * 0.05f;

#ifdef KHZ_PRE_FILTER

	//khz input, 1p filter
	filtered_khz_in += ((voct_data[0] - 2048) - filtered_khz_in) * 0.05f;
	//khz input, 2p adaptive filter
	khz_in = dynamic_smooth_tick(&dynamic_smooth_a, (filtered_khz_in)) * KHZ_IN_SCALING * khz_correction;

#else
	//khz input, 2p adaptive filter
	khz_in = dynamic_smooth_tick(&dynamic_smooth_a, (voct_data[0] - 2048)) * KHZ_IN_SCALING;
#endif

	freqSum += ((khz_in + khz_pot) - freqSum) * 0.08f;

	//filtered fm ratio
	fm_ratio += ((adc_data_10b[RATIO_POT] / 2047.0f) - fm_ratio) * 0.01f;

	OP1.frequency = expo_lut[(uint16_t) (freqSum) & 1023];
	OP1.phase_increment = ((42949.6710f) * (OP1.frequency));
	OP2.frequency = OP1.frequency * (fm_ratio * 32.0f);
	OP2.phase_increment = ((42949.6710f) * (OP2.frequency));

	if (adc_data_10b[DECAY_SLIDER] > 1000) {
		OP1.ADSR.output = 1.0f;
	}

	operator_run(&OP1, OP1.ADSR.output);
	operator_run(&OP2, OP1.ADSR.output * OP1.ADSR.output);

	OP1.modulation = (OP2.output) >> 3;

	//original
	voice1 = (OP1.output) >> 5;
	output = voice1;


	//hard clipping
	if (output > 2047) {
		output = 2047;
	}
	if (output < -2047) {
		output = -2047;
	}

	//DAC output
	dac1_ch1((output) + 2048);
}

