/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f4xx_hal.h"

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
#define LED_0_Pin GPIO_PIN_0
#define LED_0_GPIO_Port GPIOC
#define LED_1_Pin GPIO_PIN_1
#define LED_1_GPIO_Port GPIOC
#define LED_2_Pin GPIO_PIN_2
#define LED_2_GPIO_Port GPIOC
#define LED_3_Pin GPIO_PIN_3
#define LED_3_GPIO_Port GPIOC
#define encoder0_ch1_Pin GPIO_PIN_0
#define encoder0_ch1_GPIO_Port GPIOA
#define encoder0_ch2_Pin GPIO_PIN_1
#define encoder0_ch2_GPIO_Port GPIOA
#define dir0_Pin GPIO_PIN_14
#define dir0_GPIO_Port GPIOB
#define dir1_Pin GPIO_PIN_15
#define dir1_GPIO_Port GPIOB
#define encoder1_ch1_Pin GPIO_PIN_6
#define encoder1_ch1_GPIO_Port GPIOC
#define encoder1_ch2_Pin GPIO_PIN_7
#define encoder1_ch2_GPIO_Port GPIOC
#define dir2_Pin GPIO_PIN_8
#define dir2_GPIO_Port GPIOC
#define dir3_Pin GPIO_PIN_9
#define dir3_GPIO_Port GPIOC
#define pwm0_Pin GPIO_PIN_8
#define pwm0_GPIO_Port GPIOA
#define pwm1_Pin GPIO_PIN_9
#define pwm1_GPIO_Port GPIOA
#define pwm2_Pin GPIO_PIN_10
#define pwm2_GPIO_Port GPIOA
#define pwm3_Pin GPIO_PIN_11
#define pwm3_GPIO_Port GPIOA
#define encoder2_ch1_Pin GPIO_PIN_4
#define encoder2_ch1_GPIO_Port GPIOB
#define encoder2_ch2_Pin GPIO_PIN_5
#define encoder2_ch2_GPIO_Port GPIOB
#define encoder3_ch1_Pin GPIO_PIN_6
#define encoder3_ch1_GPIO_Port GPIOB
#define encoder3_ch2_Pin GPIO_PIN_7
#define encoder3_ch2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
