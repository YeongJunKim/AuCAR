/*
 * master_main.c
 *
 *  Created on: Jun 22, 2019
 *      Author: colson
 */

#include <periphGpio.h>
#include <periphusart.h>
#include <periphMotor.h>
#include "vector"
#include "main.h"

#include "AuCAR_conf.h"
#include "master_main.h"
#include "frame_handler.h"
#include "stateMachine.h"

#include "usart.h"
#include "tim.h"

#if LOCAL_DEVICE == C1

#elif LOCAL_DEVICE == C2

#elif LOCAL_DEVICE == C3
PeriphGPIO __c1nrst(nrst_c1_GPIO_Port, nrst_c1_Pin, 200);
PeriphGPIO __c2nrst(nrst_c2_GPIO_Port, nrst_c2_Pin, 200);

PeriphGPIO __c1power(power_c1_GPIO_Port, power_c1_Pin, 200);
PeriphGPIO __c2power(power_c2_GPIO_Port, power_c2_Pin, 200);

PeriphGPIO __c1boot(boot_c1_GPIO_Port, boot_c1_Pin, 200);
PeriphGPIO __c2boot(boot_c2_GPIO_Port, boot_c2_Pin, 200);

PeriphUsart __usart1(&huart1);
PeriphUsart __usart2(&huart2);
PeriphUsart __usart3(&huart3);

#if LED_TYPE == C3_LED
PeriphGPIO __led1(GPIOA, GPIO_PIN_4, 100);
PeriphGPIO __led2(GPIOA, GPIO_PIN_5, 500);
PeriphGPIO __led3(GPIOA, GPIO_PIN_6, 100);
PeriphGPIO __led4(GPIOA, GPIO_PIN_7, 500);
#else
PeriphGPIO __led1(GPIOC, GPIO_PIN_4, 100);
PeriphGPIO __led2(GPIOC, GPIO_PIN_5, 500);
PeriphGPIO __led3(GPIOB, GPIO_PIN_0, 100);
PeriphGPIO __led4(GPIOB, GPIO_PIN_1, 500);
#endif
#endif

StateMachine g_stateMachines;

uint8_t g_readData;

void init(void) {
	/* peripheral init */
	HAL_TIM_Base_Start_IT(&htim6);
	HAL_TIM_Base_Start_IT(&htim7);

	__c1boot.set();
	__c2boot.set();

	__c1nrst.set();
	__c2nrst.set();

	__c1power.set();
	__c2power.set();

	__usart1.init();
	__usart2.init();
	__usart3.init();
}

void run(void) {
	__led1.run();
	__led2.run();
	__led3.run();
	__led4.run();

	//__c1boot.run();
	//__c2boot.run();
	//__c1nrst.run();
	//__c2nrst.run();
	//__c1power.run();
	//__c2power.run();

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
		read = __usart1.read();

		if(cnt++ >= 100) {
			break;
		}
		if(read == -1)
			break;
	}
	cnt = 0;
	while (1) {
		read = __usart3.read();

		if(cnt++ >= 100) {
			break;
		}
		if(read == -1)
			break;
	}
	cnt = 0;
	while (1) {
		read = __usart3.read();

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

