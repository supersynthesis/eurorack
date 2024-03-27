/*
 * stm32F334_config.h
 *
 *  Created on: Oct 22, 2016
 *      Author: SUPER
 */

#include <pin_map.h>

#include "stm32f30x.h"

#ifndef SUPER_2SLIDER_CONFIG_H_
#define SUPER_2SLIDER_CONFIG_H_

//ADC stuff
volatile uint16_t calibration_value;
volatile uint16_t ADC[2];
static void ADC_Config(void) {

	//Phew! Continuous conversion with DMA transfer

	ADC_InitTypeDef ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;

	ADC_CommonStructInit(&ADC_CommonInitStructure);
	ADC_StructInit(&ADC_InitStructure);
	DMA_StructInit(&DMA_InitStructure);

	/* Configure the ADC clock */
	RCC_ADCCLKConfig(RCC_ADC12PLLCLK_Div2);

	/* Enable ADC1 clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12, ENABLE);

	/* DMA configuration */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	DMA_InitStructure.DMA_BufferSize = 2;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t) &ADC[0];
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) &ADC1->DR;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;

	DMA_Init(DMA1_Channel1, &DMA_InitStructure);

	/* ADC Channel configuration */
	/* GPIOA Periph clock enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	/* Configure ADC Channel 1,2 & 3 as analog input */
	GPIO_InitStructure.GPIO_Pin = RATE_POT | DC_POT;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Calibration procedure */
	ADC_VoltageRegulatorCmd(ADC1, ENABLE);

	/* Insert delay equal to 10 µs */
	delay(500);

	ADC_SelectCalibrationMode(ADC1, ADC_CalibrationMode_Single);
	ADC_StartCalibration(ADC1);

	while (ADC_GetCalibrationStatus(ADC1) != RESET)
		;
	calibration_value = ADC_GetCalibrationValue(ADC1);

	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Clock = ADC_Clock_AsynClkMode;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_DMAMode = ADC_DMAMode_Circular;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = 2;
	ADC_CommonInit(ADC1, &ADC_CommonInitStructure);

	ADC_InitStructure.ADC_ContinuousConvMode = ADC_ContinuousConvMode_Enable;
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_0;
	ADC_InitStructure.ADC_ExternalTrigEventEdge =
	ADC_ExternalTrigEventEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_OverrunMode = ADC_OverrunMode_Disable;
	ADC_InitStructure.ADC_AutoInjMode = ADC_AutoInjec_Disable;
	ADC_InitStructure.ADC_NbrOfRegChannel = 2;
	ADC_Init(ADC1, &ADC_InitStructure);

	/* ADC1 regular channel 3 & 4 configuration */
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 1,
			ADC_SampleTime_601Cycles5); //PB0
	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 2,
			ADC_SampleTime_601Cycles5); //PB1
	ADC_DMAConfig(ADC1, ADC_DMAMode_Circular);

	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);
	DMA_Cmd(DMA1_Channel1, ENABLE);
	ADC_DMACmd(ADC1, ENABLE);

	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);
	ADC_GetConversionValue(ADC1);
	/* wait for ADRDY */
	while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_RDY))
		;

	/* Start ADC1 Software Conversion */
	ADC_StartConversion(ADC1);
}

void NVIC_Config() {

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

	NVIC_InitTypeDef nvicStructure;
	nvicStructure.NVIC_IRQChannel = TIM2_IRQn;
	nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
	nvicStructure.NVIC_IRQChannelSubPriority = 0;
	nvicStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicStructure);

	nvicStructure.NVIC_IRQChannel = TIM3_IRQn;
	nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
	nvicStructure.NVIC_IRQChannelSubPriority = 0;
	nvicStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicStructure);

	// Enable DMA1 channel1 IRQ Channel
	nvicStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
	nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
	nvicStructure.NVIC_IRQChannelSubPriority = 0;
	nvicStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicStructure);
}

void GPIO_Config() {
	//for example
	GPIO_InitTypeDef GPIO_InitStructure;
	//Enable GPIOB Clock
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = LEFT_BUTTON | CLOCK_IN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = RIGHT_BUTTON;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = STEPS_BUTTON;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

}

void delay(int a) {
	volatile int i, j;

	for (i = 0; i < a; i++) {
		j++;
	}

	return;
}

void DAC_Config(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitStructure;

	/* DAC Periph clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC2, ENABLE);

	/* GPIOA clock enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	/* Configure PA4 & PA6 as analog out */

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* DAC channel1 Configuration */
	DAC_StructInit(&DAC_InitStructure);
	DAC_InitStructure.DAC_Buffer_Switch =
	DAC_BufferSwitch_Enable;
	DAC_Init(DAC1, DAC_Channel_1, &DAC_InitStructure);
	DAC_Init(DAC1, DAC_Channel_2, &DAC_InitStructure);
	DAC_Init(DAC2, DAC_Channel_1, &DAC_InitStructure);
	DAC_Cmd(DAC1, DAC_Channel_1, ENABLE);
	DAC_Cmd(DAC1, DAC_Channel_2, ENABLE);
	DAC_Cmd(DAC2, DAC_Channel_1, ENABLE);
	DAC_SetChannel1Data(DAC1, DAC_Align_12b_R, 0);
	DAC_SetChannel2Data(DAC1, DAC_Align_12b_R, 0);
	DAC_SetChannel1Data(DAC2, DAC_Align_12b_R, 0);
}

void TIM_Config(void) {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	/* TIM2 Periph clock enable */
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	/* Time base configuration */
	//TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	//TIM_TimeBaseStructure.TIM_Period = 1600; // tuned for 440, bleh
	//TIM_TimeBaseStructure.TIM_Prescaler = 0;
	//TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	//TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	//TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	//TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	//TIM_Cmd(TIM2, ENABLE);
	/* TIM2 Periph clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	/* Time base configuration */
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = 45000;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV4;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_ARRPreloadConfig(TIM3, ENABLE);

	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM3, ENABLE);

}

#endif /* SUPER_2SLIDER_CONFIG_H_ */
