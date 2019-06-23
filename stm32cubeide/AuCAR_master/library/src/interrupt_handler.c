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

#include "interrupt_handler.h"
#include "frame_handler.h"

COUNTERS g_counters;

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
	if(huart->Instance == USART1)
	{
		g_counters.usart1TxCounter++;
	}
	else if(huart->Instance == USART2)
	{
		g_counters.usart2TxCounter++;
		  //nh.getHardware()->flush();
	}
	else if(huart->Instance == USART3)
	{
		g_counters.usart3TxCounter++;
	}
	else if(huart->Instance == UART4)
	{
		g_counters.usart4TxCounter++;
	}
	else if(huart->Instance == UART5)
	{
		g_counters.usart5TxCounter++;
	}
	else if(huart->Instance == USART6)
	{
		g_counters.usart6TxCounter++;
	}
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		g_counters.usart1RxCounter++;
	}
	else if(huart->Instance == USART2)
	{
		g_counters.usart2RxCounter++;
		//nh.getHardware()->reset_rbuf();
	}
	else if(huart->Instance == USART3)
	{
		g_counters.usart3RxCounter++;
	}
	else if(huart->Instance == UART4)
	{
		g_counters.usart4RxCounter++;
	}
	else if(huart->Instance == UART5)
	{
		g_counters.usart5RxCounter++;
	}
	else if(huart->Instance == USART6)
	{
		g_counters.usart6RxCounter++;
	}
}
