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
#define motor0_Pin GPIO_PIN_0
#define motor0_GPIO_Port GPIOC
#define motor1_Pin GPIO_PIN_1
#define motor1_GPIO_Port GPIOC
#define motor2_Pin GPIO_PIN_2
#define motor2_GPIO_Port GPIOC
#define motor3_Pin GPIO_PIN_3
#define motor3_GPIO_Port GPIOC
#define encoder0_ch1_Pin GPIO_PIN_0
#define encoder0_ch1_GPIO_Port GPIOA
#define encoder0_ch2_Pin GPIO_PIN_1
#define encoder0_ch2_GPIO_Port GPIOA
#define ABS0_0_Pin GPIO_PIN_4
#define ABS0_0_GPIO_Port GPIOA
#define ABS0_1_Pin GPIO_PIN_5
#define ABS0_1_GPIO_Port GPIOA
#define ABS0_2_Pin GPIO_PIN_6
#define ABS0_2_GPIO_Port GPIOA
#define ABS1_0_Pin GPIO_PIN_7
#define ABS1_0_GPIO_Port GPIOA
#define ABS1_1_Pin GPIO_PIN_4
#define ABS1_1_GPIO_Port GPIOC
#define ABS1_2_Pin GPIO_PIN_0
#define ABS1_2_GPIO_Port GPIOB
#define ABS2_0_Pin GPIO_PIN_1
#define ABS2_0_GPIO_Port GPIOB
#define ABS2_1_Pin GPIO_PIN_2
#define ABS2_1_GPIO_Port GPIOB
#define ABS2_2_Pin GPIO_PIN_12
#define ABS2_2_GPIO_Port GPIOB
#define ABS3_0_Pin GPIO_PIN_13
#define ABS3_0_GPIO_Port GPIOB
#define ABS3_1_Pin GPIO_PIN_14
#define ABS3_1_GPIO_Port GPIOB
#define ABS3_2_Pin GPIO_PIN_15
#define ABS3_2_GPIO_Port GPIOB
#define encoder1_ch1_Pin GPIO_PIN_6
#define encoder1_ch1_GPIO_Port GPIOC
#define encoder1_ch2_Pin GPIO_PIN_7
#define encoder1_ch2_GPIO_Port GPIOC
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
