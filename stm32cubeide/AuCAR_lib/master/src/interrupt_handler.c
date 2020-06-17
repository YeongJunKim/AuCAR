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
#include "master_main.h"

COUNTERS g_counters;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM6)
	{
		timer_1s();
	}
	else if(htim->Instance == TIM7)
	{
		timer_10ms();
	}
}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		g_counters.usart1TxCounter++;
		uart_tx_callback(huart);
	}
	else if(huart->Instance == USART2)
	{
		g_counters.usart2TxCounter++;
		  //nh.getHardware()->flush();
		uart_tx_callback(huart);
	}
	else if(huart->Instance == USART3)
	{
		g_counters.usart3TxCounter++;
		uart_tx_callback(huart);
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
		uart_rx_callback(huart);
	}
	else if(huart->Instance == USART2)
	{
		g_counters.usart2RxCounter++;
		//nh.getHardware()->reset_rbuf();
		uart_rx_callback(huart);
	}
	else if(huart->Instance == USART3)
	{
		g_counters.usart3RxCounter++;
		uart_rx_callback(huart);
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


void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef *hcan) {
	if (hcan->Instance == CAN1) {
		g_counters.can1TxCounter++;
		can_tx_callback(hcan);
	}
}


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
	if (hcan->Instance == CAN1) {
		g_counters.can1RxCounter++;
		can_rx_callback(hcan);

	}
}

void HAL_CAN_RxFifo0FullCallback(CAN_HandleTypeDef *hcan)
{
	if (hcan->Instance == CAN1) {
		g_counters.can1RxFullCounter++;
	}
}

void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan)
{
	if (hcan->Instance == CAN1) {
		g_counters.can1ErrorCounter++;
	}
}
