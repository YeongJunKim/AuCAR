/*
 * master_main.c
 *
 *  Created on: Jun 22, 2019
 *      Author: colson
 */

#include <hardware.h>
#include <stateLed.h>
#include "main.h"

#include "AuCAR_conf.h"
#include "master_main.h"
#include "frame_handler.h"
#include "stateMachine.h"

#include "usart.h"
#include "tim.h"

#if LED_TYPE == C3_LED
StateLed __led1(GPIOA, GPIO_PIN_4, 100);
StateLed __led2(GPIOA, GPIO_PIN_5, 500);
StateLed __led3(GPIOA, GPIO_PIN_6, 100);
StateLed __led4(GPIOA, GPIO_PIN_7, 500);
#else
StateLed __led1(GPIOC, GPIO_PIN_4, 100);
StateLed __led2(GPIOC, GPIO_PIN_5, 500);
StateLed __led3(GPIOB, GPIO_PIN_0, 100);
StateLed __led4(GPIOB, GPIO_PIN_1, 500);
#endif

Hardware g_hardware_uart1(&huart1);
Hardware g_hardware_uart3(&huart3);

Hardware g_hardware_uart2(&huart2);

StateMachine g_stateMachines;

uint8_t g_readData;

void init(void) {
	/* peripheral init */
	HAL_TIM_Base_Start_IT(&htim6);
	HAL_TIM_Base_Start_IT(&htim7);

	g_hardware_uart1.init();
	g_hardware_uart3.init();

	g_hardware_uart2.init();
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
		read = g_hardware_uart1.read();

		if(cnt++ >= 100) {
			break;
		}
		if(read = -1)
			break;
	}
	cnt = 0
	while (1) {
		read = g_hardware_uart3.read();

		if(cnt++ >= 100) {
			break;
		}
		if(read = -1)
			break;
	}
	cnt = 0
	while (1) {
		read = g_hardware_uart3.read();

		if(cnt++ >= 100) {
			break;
		}
		if(read = -1)
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



/*
 * motor control
 * */
__weak void timer_10ms(void)
{

}

