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
#include "stateMachine.h"

#include "usart.h"
#include "tim.h"

#if LOCAL_DEVICE == C1

#elif LOCAL_DEVICE == C2

#elif LOCAL_DEVICE == C3

PeriphGPIO __c1nrst(nrst_c1_GPIO_Port, nrst_c1_Pin, 1000);
PeriphGPIO __c2nrst(nrst_c2_GPIO_Port, nrst_c2_Pin, 1000);

PeriphGPIO __c1power(power_c1_GPIO_Port, power_c1_Pin, 1000);
PeriphGPIO __c2power(power_c2_GPIO_Port, power_c2_Pin, 1000);

PeriphGPIO __c1boot(boot_c1_GPIO_Port, boot_c1_Pin, 1000);
PeriphGPIO __c2boot(boot_c2_GPIO_Port, boot_c2_Pin, 1000);

PeriphGPIO __id0(id_0_GPIO_Port, id_0_Pin, 0);
PeriphGPIO __id1(id_1_GPIO_Port, id_1_Pin, 0);
PeriphGPIO __id2(id_2_GPIO_Port, id_2_Pin, 0);
PeriphGPIO __id3(id_3_GPIO_Port, id_3_Pin, 0);


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

	__c1nrst.reset();
	__c2nrst.reset();

	__c1power.reset();
	__c2power.reset();

	__usart1.init();
	__usart2.init();
	__usart3.init();
}



void run(void) {

	io_read();
	led_run();

	// circuit_logic_test();

	int data = 0;
	uint8_t read = 0;
	while(1)
	{
		data = __usart2.read();

		if(data < 0)
			break;
		else
		{
			read = (uint8_t)data;
			//TODO
			//state machine
		}
	}

	while(1)
	{
		data = __usart1.read();
		if(data < 0)
			break;
		else
		{
			read = (uint8_t)data;
			//TODO
			//state machine
		}
	}

	while(1)
	{
		data = __usart3.read();
		if(data < 0)
			break;
		else
		{
			read = (uint8_t)data;
			//TODO
			//state machine
		}
	}

	/*
	 * check queue (dequeue)
	 * usart -> queue -> frame
	 * USART1 - To C1 -
	 * USART2 - for ROS -
	 * USART3 - To C2 -
	 * USB_DEVICE_FS - TODO (for ROS) -
	 * */


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


void io_read(void)
{
	if(__id0.read() == GPIO_PIN_SET)
		__c1power.reset();
	else
		__c1power.set();

	if(__id1.read() == GPIO_PIN_SET)
		__c2power.reset();
	else
		__c2power.set();

	if(__id2.read() == GPIO_PIN_SET)
	{}
	else
	{}
	if(__id3.read() == GPIO_PIN_SET)
	{}
	else
	{}
}

void led_run(void)
{
	__led1.run();
	__led2.run();
	__led3.run();
	__led4.run();
}


void circuit_logic_test(void)
{
	__c1boot.run();
	__c2boot.run();
	__c1nrst.run();
	__c2nrst.run();
	__c1power.run();
	__c2power.run();
}

void timer_1s(void)
{

}

void timer_10ms(void)
{

}

void uart_tx_callback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		__usart1.flush();
	}
	else if(huart->Instance == USART2)
	{
		__usart2.flush();
	}
	else if(huart->Instance == USART3)
	{
		__usart3.flush();
	}
}

void uart_rx_callback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		__usart1.reset_rbuf();
	}
	else if(huart->Instance == USART2)
	{
		__usart2.reset_rbuf();
	}
	else if(huart->Instance == USART3)
	{
		__usart3.reset_rbuf();
	}
}

