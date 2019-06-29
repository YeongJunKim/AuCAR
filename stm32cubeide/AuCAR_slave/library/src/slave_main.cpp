/*
 * master_main.c
 *
 *  Created on: Jun 22, 2019
 *      Author: colson
 */

#include <periphLed.h>
#include <periphusart.h>
#include <periphMotor.h>
#include "vector"
#include "main.h"

#include "AuCAR_conf.h"
#include "slave_main.h"
#include "frame_handler.h"
#include "stateMachine.h"
#include "pid_control_long.h"

#include "usart.h"
#include "tim.h"

#if LED_TYPE == C1_LED
PeriphLED __led1(GPIOC, GPIO_PIN_0, 100);
PeriphLED __led2(GPIOC, GPIO_PIN_1, 500);
PeriphLED __led3(GPIOC, GPIO_PIN_2, 100);
PeriphLED __led4(GPIOC, GPIO_PIN_3, 500);
#elif LED_TYPE == C2_LED
PeriphLED __led1(GPIOC, GPIO_PIN_0, 100);
PeriphLED __led2(GPIOC, GPIO_PIN_1, 500);
PeriphLED __led3(GPIOC, GPIO_PIN_2, 100);
PeriphLED __led4(GPIOC, GPIO_PIN_3, 500);
#elif LED_TYPE == C3_LED
PeriphLED __led1(GPIOA, GPIO_PIN_4, 100);
PeriphLED __led2(GPIOA, GPIO_PIN_5, 500);
PeriphLED __led3(GPIOA, GPIO_PIN_6, 100);
PeriphLED __led4(GPIOA, GPIO_PIN_7, 500);
#elif LED_TYPE == C3_LED_ALT
PeriphLED __led1(GPIOC, GPIO_PIN_4, 100);
PeriphLED __led2(GPIOC, GPIO_PIN_5, 500);
PeriphLED __led3(GPIOB, GPIO_PIN_0, 100);
PeriphLED __led4(GPIOB, GPIO_PIN_1, 500);
#else
#error 'NO LED TYPE'
#endif

PeriphUsart g_hardware_uart2(&huart2);

LPID motor[4] ={0,};
uint16_t g_getEncoder[4] = {0,};
uint16_t g_pastEncoder[4] = {0,};
long g_deltaEncoder[4] = {0,};
long g_targetEncoder[4] = {0,};


StateMachine g_stateMachines;

uint8_t g_readData;

void init(void) {
	/* peripheral init */
	HAL_TIM_Base_Start_IT(&htim6);
	HAL_TIM_Base_Start_IT(&htim7);

	g_hardware_uart2.init();

	for(int i = 0 ; i < 4; i++)
		PID_Control_Long_Initialize(&motor[i]);
}

void run(void) {
	__led1.run();
	__led2.run();
	__led3.run();
	__led4.run();
	/*
	 * check queue (dequeue)
	 * usart -> queue -> frame
	 * USART1 - To C1 -
	 * USART2 - for ROS -
	 * USART3 - To C2 -
	 * USB_DEVICE_FS - TODO (for ROS) -
	 * */
	int read;
	uint8_t cnt = 0;
	while (1) {
		read = g_hardware_uart2.read();

		if(cnt++ >= 100) {
			break;
		}
		if(read == -1)
			break;
	}

	/*
	 * state machine
	 * */

	/*
	 * enqueue data
	 * frame -> queue -> usart
	 * */

	/*
	 * local functions
	 * PERIPHERAL - LED, PWM, ... , etc.
	 * */
}



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM6)
	{
		//timer_1s();
	}
	if(htim->Instance == TIM7)
	{
		timer_10ms();
	}
}
/*
 * motor control
 * */
__weak void timer_10ms(void)
{

	//get encoder data
	//reset encoder data
	//65535
	//30000 > - (65535 - getencoder) = delta;
	//PID
	//


	g_getEncoder[0] = TIM5->CNT;
	g_getEncoder[1] = TIM8->CNT;
	g_getEncoder[2] = TIM3->CNT;
	g_getEncoder[3] = TIM4->CNT;

	for (int i = 0 ; i < 4 ; i++)
	{
		if(g_getEncoder[i] > 30000)
			g_deltaEncoder[i] = -(65535 - g_getEncoder[i]);
		else
			g_deltaEncoder[i] = g_getEncoder[i];
	}

	TIM5->CNT = 0;
	TIM8->CNT = 0;
	TIM3->CNT = 0;
	TIM4->CNT = 0;

	//uint32_t targetTimer[4] = {TIM5,TIM8,TIM3,TIM4};
	for(int i = 0 ; i < 4; i++)
	{
		PID_Control_Long(&motor[i], g_targetEncoder[i], g_deltaEncoder[i]);
	}


	if(motor[0].nowOutput < 0)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
		TIM1->CCR1 = (uint16_t)(-motor[0].nowOutput);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
		TIM1->CCR1 = (uint16_t)(motor[0].nowOutput);
	}
	if(motor[1].nowOutput < 0)
	{

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
		TIM1->CCR2 = (uint16_t)(-motor[1].nowOutput);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
		TIM1->CCR2 = (uint16_t)(motor[1].nowOutput);
	}
	if(motor[2].nowOutput < 0)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
		TIM1->CCR3 = (uint16_t)(-motor[2].nowOutput);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
		TIM1->CCR3 = (uint16_t)(motor[2].nowOutput);
	}
	if(motor[3].nowOutput < 0)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
		TIM1->CCR4 = (uint16_t)(-motor[3].nowOutput);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
		TIM1->CCR4 = (uint16_t)(motor[3].nowOutput);
	}
}




