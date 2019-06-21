/*
 * interrupt_handler.c
 *
 *  Created on: Jun 21, 2019
 *      Author: colson
 */


#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM6)
	{
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1);
	}
	else if(htim->Instance == TIM7)
	{
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_4|GPIO_PIN_5);
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
}
