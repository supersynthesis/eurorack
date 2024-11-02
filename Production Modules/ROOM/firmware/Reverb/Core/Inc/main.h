/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MUX_C_Pin GPIO_PIN_6
#define MUX_C_GPIO_Port GPIOA
#define MUX_B_Pin GPIO_PIN_7
#define MUX_B_GPIO_Port GPIOA
#define MUX_A_Pin GPIO_PIN_0
#define MUX_A_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define HP_POT_INDEX 		0
#define SIZE_POT_INDEX 		1
#define LP_POT_INDEX		2
#define FB_POT_INDEX		3

#define SAMPLE_RATE			32000.0f
//#define SAMPLE_RATE			44444.0f
// #define SAMPLE_RATE			53333.0f

#define MAX_MS_DELAY		15000.0f / SAMPLE_RATE * 1000.0f

#define RAMFUNC __attribute__ ((section (".ccmram")))

//uncomment one PHINC_SCALE for the given sample rate
// 48k sample rate
//#define PHINC_SCALE 89478.4853f

// 44.1k sample rate
//#define PHINC_SCALE 97391.5486f

// 53.33k sample rate
#define PHINC_SCALE 80531.1401f

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
