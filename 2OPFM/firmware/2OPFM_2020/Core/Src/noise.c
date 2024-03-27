/*
 * noise.c
 *
 *  Created on: Apr 3, 2020
 *      Author: SUPER
 */

#include "noise.h"
#include "main.h"

uint32_t noise_m_z = 362436069;
uint32_t noise_m_w = 521288629;

uint32_t noise(void) {
	noise_m_z = 36969 * (noise_m_z & 65535) + (noise_m_z >> 16);
	noise_m_w = 18000 * (noise_m_w & 65535) + (noise_m_w >> 16);
	return (noise_m_z << 16) + noise_m_w;
}
