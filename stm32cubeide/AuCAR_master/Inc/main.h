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
#define id_0_Pin GPIO_PIN_0
#define id_0_GPIO_Port GPIOC
#define id_1_Pin GPIO_PIN_1
#define id_1_GPIO_Port GPIOC
#define id_2_Pin GPIO_PIN_2
#define id_2_GPIO_Port GPIOC
#define id_3_Pin GPIO_PIN_3
#define id_3_GPIO_Port GPIOC
#define max485_dir_Pin GPIO_PIN_2
#define max485_dir_GPIO_Port GPIOB
#define max485_dir_alt_Pin GPIO_PIN_10
#define max485_dir_alt_GPIO_Port GPIOB
#define nrst_c1_Pin GPIO_PIN_8
#define nrst_c1_GPIO_Port GPIOC
#define nrst_c2_Pin GPIO_PIN_9
#define nrst_c2_GPIO_Port GPIOC
#define power_c1_Pin GPIO_PIN_12
#define power_c1_GPIO_Port GPIOC
#define power_c2_Pin GPIO_PIN_2
#define power_c2_GPIO_Port GPIOD
#define boot_c1_Pin GPIO_PIN_3
#define boot_c1_GPIO_Port GPIOB
#define boot_c2_Pin GPIO_PIN_4
#define boot_c2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
