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

#include "data_struct.h"

COUNTERS g_counters;


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM6)
	{
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_0|GPIO_PIN_1);
	}
	else if(htim->Instance == TIM7)
	{
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_2|GPIO_PIN_2);
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART2)
	{
		g_counters.usart2TxCounter++;
	}
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART2)
	{
		g_counters.usart2RxCounter++;

	}
}
