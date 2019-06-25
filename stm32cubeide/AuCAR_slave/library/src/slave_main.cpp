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



StateMachine g_stateMachines;

uint8_t g_readData;

void init(void) {
	/* peripheral init */
	HAL_TIM_Base_Start_IT(&htim6);
	HAL_TIM_Base_Start_IT(&htim7);

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



/*
 * motor control
 * */
__weak void timer_10ms(void)
{

}

