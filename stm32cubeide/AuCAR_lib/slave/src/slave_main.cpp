/*
 * master_main.c
 *
 *  Created on: Jun 22, 2019
 *      Author: colson
 */

#include <periphGPIO.h>
#include <periphusart.h>
#include <periphMotor.h>
#include <periphDelay.h>
#include "vector"
#include "main.h"
#include "conf.h"

#include "AuCAR_conf.h"
#include "slave_main.h"
#include "stateMachine.h"
#include "pid_control_long.h"

#include "usart.h"
#include "tim.h"

#include "AuCAR.h"


#if LOCAL_DEVICE == C1
/* PeriphGPIO(MODULE, PIN, Period) */
StateMachine g_stateMachines;

PeriphDelay __delay;

PeriphGPIO __led1(GPIOC, GPIO_PIN_0, 100);
PeriphGPIO __led2(GPIOC, GPIO_PIN_1, 500);
PeriphGPIO __led3(GPIOC, GPIO_PIN_2, 100);
PeriphGPIO __led4(GPIOC, GPIO_PIN_3, 500);
PeriphUsart __usart2(&huart2);
PeriphUsart __usart4(&huart4);


#elif LOCAL_DEVICE == C2
PeriphGPIO __led1(GPIOC, GPIO_PIN_0, 100);
PeriphGPIO __led2(GPIOC, GPIO_PIN_1, 500);
PeriphGPIO __led3(GPIOC, GPIO_PIN_2, 100);
PeriphGPIO __led4(GPIOC, GPIO_PIN_3, 500);
PeriphUsart __usart2(&huart2);
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


/* motor control */
LPID motor[4] ={0,};
uint16_t g_getEncoder[4] = {0,};
uint16_t g_pastEncoder[4] = {0,};
long g_deltaEncoder[4] = {0,};
long g_targetEncoder[4] = {0,};

long g_sumEncoder[4] = {0,};
/* motor control end */

int __printf__io__putchar(int ch)
{
	uint8_t data = ch;
	__usart4.write(&data, 1);

	return ch;
}

void init(void) {
	/* peripheral init */
	_DEBUG("Slave init start.\r\n");
	HAL_TIM_Base_Start_IT(&htim6);
	HAL_TIM_Base_Start_IT(&htim7);
	_DEBUG("Timer init OK.\r\n");

	__usart2.init();
	__usart4.init();
	_DEBUG("Usart init OK.\r\n");


	for(int i = 0 ; i < 4; i++)
		PID_Control_Long_Initialize(&motor[i]);

	_DEBUG("PID init OK.\r\n");
	_DEBUG("All init OK.\r\n");
	_DEBUG("Slave init end.\r\n");
	_DEBUG("wait 1sec\r\n");
	__delay.delay_ms(400);
}


uint32_t nowtick = 0;
uint32_t pasttick = 0;

void run(void) {
	led_run();

	int cnt = 0;
	int read = 0;

	while(1)
	{
		read = __usart2.read();

		if(cnt++ >= 100) {
			//break;
		}
		if(read == -1)
			break;
		else
			g_stateMachines.data_push_back(0, (uint8_t)read);
	}
	cnt = 0;


	/* test sender */
	nowtick = HAL_GetTick();
	if(nowtick - pasttick > 5)
	{
		uint16_t size = 20;
		uint8_t arr[size];
		uint8_t checksum = 0;
		for(int i = 0 ; i < size; i++){
			arr[i] = i;
			checksum += arr[i];
		}
		uint8_t sendData1[8] = {0xFF, 0xFF, 0x05, 0x00, 0x04, 0x00, 0xF4, 0x01};
		sendData1[6] = (uint8_t)size;
		sendData1[7] = (uint8_t)(size >> 8);
		__usart2.write(sendData1, sizeof(sendData1));
		__usart2.write(arr, sizeof(arr));
		__usart2.write(&checksum, sizeof(checksum));

		pasttick = nowtick;

	}


	/* test sender end */

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

	g_stateMachines.run();

	/*
	 * enqueue data
	 * frame -> queue -> usart
	 * */




	/*
	 * sang uk area
	 * 1. 단위변경 -> m/s -> target encoder; 1 rev -> 1820;
	 * 2. target position -> target sum
	 * 3. > < =
	 * 4. 함수 만두르기
	 * */



	/*
	 * local functions
	 * PERIPHERAL - LED, PWM, ... , etc.
	 * */
}
void led_run(void)
{
	__led1.run();
	__led2.run();
	__led3.run();
	__led4.run();
}





/*
 *
 *
 * */
uint32_t pp = 0;
uint32_t ppp = 0;
__weak void timer_1s(void)
{
	//TODO
	if(g_stateMachines.get_vector_size(0) || g_stateMachines.get_vector_size(1) || g_stateMachines.get_vector_size(2)){
		_DEBUG("TIME SEQUENCE : %d (sec) \r\n", pp);
		_DEBUG("vector size\r\nvector0 size = %d \r\nvector1 size = %d \r\nvector2 size = %d\r\n"
				,g_stateMachines.get_vector_size(0), g_stateMachines.get_vector_size(1),g_stateMachines.get_vector_size(2));

	}
	else if(pp % 10 == 0){
		_DEBUG("10s count = %d \r\n", ppp);
		ppp++;
	}
	pp++;
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

	for (int i = 0 ; i < 4; i ++)
	{
		g_sumEncoder[i] += g_deltaEncoder[i];
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

void uart_tx_callback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
	}
	else if(huart->Instance == USART2)
	{
		__usart2.flush();
	}
	else if(huart->Instance == USART3)
	{
	}
}

void uart_rx_callback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
	}
	else if(huart->Instance == USART2)
	{
		__usart2.reset_rbuf();
	}
	else if(huart->Instance == USART3)
	{
	}
}


