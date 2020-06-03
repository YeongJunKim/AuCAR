/*
 * master_main.cpp
 *
 *  Created on: Jun 22, 2019
 *      Author: colson
 */

#include <periphGpio.h>
#include <periphusart.h>
#include <periphMotor.h>
#include <periphDelay.h>
#include "vector"
#include "main.h"
#include "conf.h"

#include "AuCAR_conf.h"
#include "slave_main.h"
#include "pid_control_long.h"

#include "usart.h"
#include "tim.h"

#include "AuCAR.h"
#include "absoluteEncoder.h"
#include "stdlib.h"

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

void task_run(control_type type, stateMachineTask_ST task);

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
LPID angle[4] ={0,};
uint16_t g_getEncoder[4] = {0,};
uint16_t g_pastEncoder[4] = {0,};
long g_deltaEncoder[4] = {0,};
long g_targetEncoder[4] = {0,};
long g_targetEncoderSave[4] = {0,};
long g_nowAngle[4] = {0,};
long g_targetAngle[4] = {0,};
long g_deltaEncoderCnt[4] = {0,};

long g_targetAngleLimit[4] = {180,180,180,180};
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


		PID_Control_Long_Initialize(&motor[0]);
		PID_Control_Long_Initialize2(&motor[2]);
		PID_Control_Long_Initialize(&motor[1]);
		PID_Control_Long_Initialize2(&motor[3]);
	for(int i = 0; i < 4; i ++)
		PID_Control_Long_Initialize_angle(&angle[i]);
	_DEBUG("PID init OK.\r\n");
	_DEBUG("All init OK.\r\n");
	_DEBUG("Slave init end.\r\n");
	_DEBUG("wait 1sec\r\n");
	__delay.delay_ms(400);
}


uint32_t nowtick = 0;
uint32_t pasttick = 0;

uint8_t initialization = 0;

void run(void) {
	led_run();

	int cnt = 0;
	int read = 0;

	if(initialization == 0)
	{
		while(1)
		{
			//TODO add limit switch
			//TODO until tact limit switch turn CCW (target -10)
			//if limit switch is tackted, stop and reset deltacount = 0, abs = 0
			initialization = 1;
			break;
		}
	}

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
//	nowtick = HAL_GetTick();
//	if(nowtick - pasttick > 5)
//	{
//		uint16_t size = 20;
//		uint8_t arr[size];
//		uint8_t checksum = 0;
//		for(int i = 0 ; i < size; i++){
//			arr[i] = i;
//			checksum += arr[i];
//		}
//		uint8_t sendData1[8] = {0xFF, 0xFF, 0x05, 0x00, 0x04, 0x00, 0xF4, 0x01};
//		sendData1[6] = (uint8_t)size;
//		sendData1[7] = (uint8_t)(size >> 8);
//		__usart2.write(sendData1, sizeof(sendData1));
//		__usart2.write(arr, sizeof(arr));
//		__usart2.write(&checksum, sizeof(checksum));
//
//		pasttick = nowtick;
//
//	}

	nowtick = HAL_GetTick();
	if(nowtick - pasttick > 100)
	{
		uint16_t cmd1 = 0x3000;
		uint16_t cmd2 = 0x0000;
		uint16_t len = 8;

		uint8_t arr[2+2+2+2+8+1] = {0,};
		arr[0] = 0xFF;
		arr[1] = 0xFF;
		arr[2] = cmd1;
		arr[3] = cmd1 >> 8;
		arr[4] = cmd2;
		arr[5] = cmd2 >> 8;
		arr[6] = len;
		arr[7] = len >> 8;
//		g_nowAngle[1] = 10;
//		g_nowAngle[3] = 250;
		arr[8] = ((int)g_nowAngle[1]);
		arr[9] = ((int)g_nowAngle[1]) >> 8;
		arr[10] = ((int)g_nowAngle[1]) >> 16;
		arr[11] = ((int)g_nowAngle[1]) >> 24;
		arr[12] = ((int)g_nowAngle[3]);
		arr[13] = ((int)g_nowAngle[3]) >> 8;
		arr[14] = ((int)g_nowAngle[3]) >> 16;
		arr[15] = ((int)g_nowAngle[3]) >> 24;
		for(int i =0; i < 8 ; i++)
			arr[16] += arr[8+i];
//		__usart2.write(arr, 17);




		uint8_t deb[20] = {0,};
		stateMachineTask_ST send = {0,};
		send.cmd1 = 0x3000;
		send.cmd2 = 0x0000;
		send.length = 8;
		send.data = (uint8_t*)malloc(sizeof(uint8_t) * send.length);
		send.checksum = 0;
		for(int i = 0; i < send.length; i ++)
		{
			send.data[i] = i;
			send.checksum += send.data[i];
		}
		uint8_t *psend;
		psend = (uint8_t *)malloc(sizeof(uint8_t) * 100);

		int size = g_stateMachines.send_task(0, send, psend);
		__usart2.write(psend, size);
		free(send.data);
		free(psend);
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

	stateMachineTask_ST get = {0,};
	g_stateMachines.run();
	BOOL state = g_stateMachines.get_task(0, &get);
	if(state == true)
	{
		task_run(TYPE_MOTOR, get);

		free(get.data);
	}


	/*
	 * enqueue data
	 * frame -> queue -> usart
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

void task_run(control_type type, stateMachineTask_ST task)
{
	if(type == TYPE_MOTOR)
	{
		//motor1 setting
		uint16_t cmd2 = task.cmd2;
		uint16_t len = task.length;
		uint16_t seq = task.data[len-1];
		int x = 0;
		x = x | (task.data[0]);
		x = x | (task.data[1] << 8);
		x = x | (task.data[2] << 16);
		x = x | (task.data[3] << 24);
		int z = 0;
		z = z | (task.data[4]);
		z = z | (task.data[5] << 8);
		z = z | (task.data[6] << 16);
		z = z | (task.data[7] << 24);

		x = x/100;
		z = z/100;

		if((task.cmd1 & 0x00FF) == 0x0010)
		{
			//motor 1
			__led1.setPeriod(50);
			__led2.setPeriod(50);
			g_targetEncoder[0] = (long)x;
			//g_targetEncoder[1] = (long)z;
			g_targetAngle[1] = (long)z;
			_DEBUG("targetEncoder[0] : %d \r\ntargetEncoder[1] : %d\r\n",x,z);
			target_angle_filter();
		}
		else if((task.cmd1 & 0x00FF) == 0x0020)
		{
			//motor 2
			__led3.setPeriod(50);
			__led4.setPeriod(50);
			g_targetEncoder[2] = (long)x;
			//g_targetEncoder[3] = (long)z;
			g_targetAngle[3] = (long)z;
			_DEBUG("targetEncoder[2] : %d \r\ntargetEncoder[3] : %d\r\n",x,z);
			target_angle_filter();
		}

	}
}

void target_angle_filter(void)
{
//	if(g_targetAngle[1] < 0 || g_targetAngle[1] > 360)
//	{
//		g_targetAngle[1] = 0;
//	}
//	if(g_targetAngle[1] > 180 && g_targetAngle[1] <= 360)
//	{
//		g_targetAngle[1] = g_targetAngle[1] - 180;
//		g_targetEncoder[0] = -g_targetEncoder[0];
//	}
//	if(g_targetAngle[3] < 0 || g_targetAngle[3] > 360)
//	{
//		g_targetAngle[3] = 0;
//	}
//	if(g_targetAngle[3] > 180 && g_targetAngle[3] <= 360)
//	{
//		g_targetAngle[3] = g_targetAngle[3] - 180;
//		g_targetEncoder[2] = -g_targetEncoder[2];
//	}
//	g_targetEncoderSave[0] = g_targetEncoder[0];
//	g_targetEncoderSave[2] = g_targetEncoder[2];
	if(g_targetAngle[1] < -180)
		g_targetAngle[1] = -180;
	if(g_targetAngle[1] > 180)
		g_targetAngle[1] = 180;
	if(g_targetAngle[3] < -180)
		g_targetAngle[3] = -180;
	if(g_targetAngle[3] > 180)
		g_targetAngle[3] = 180;
	g_targetEncoderSave[0] = g_targetEncoder[0];
	g_targetEncoderSave[2] = g_targetEncoder[2];
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
//	if(g_stateMachines.get_vector_size(0) || g_stateMachines.get_vector_size(1) || g_stateMachines.get_vector_size(2)){
//		_DEBUG("TIME SEQUENCE : %d (sec) \r\n", pp);
//		_DEBUG("vector size\r\nvector0 size = %d \r\nvector1 size = %d \r\nvector2 size = %d\r\n"
//				,g_stateMachines.get_vector_size(0), g_stateMachines.get_vector_size(1),g_stateMachines.get_vector_size(2));
//
//	}
//	else if(pp % 10 == 0){
//		_DEBUG("10s count = %d \r\n", ppp);
//		ppp++;
//	}
//	pp++;
	//_DEBUG("timer 1s \r\n");
}
/*
 * motor control
 * */
__weak void timer_15us(void)
{
	abs_encoder_step_calculator();
}
__weak void timer_10ms(void)
{

	//get encoder data
	//reset encoder data
	//65535
	//30000 > - (65535 - getencoder) = delta;
	//PID
	//
	// 1820 * 3 = 1바퀴
	// 1404 * 4 = 1바퀴
	g_nowAngle[1] = (long)((float)g_deltaEncoderCnt[1] / (1820.0 * 3.0) * 360.0);
	g_nowAngle[3] = (long)((float)g_deltaEncoderCnt[3] / (1820.0 * 3.0) * 360.0);



	if(abs(g_targetAngle[1] - g_nowAngle[1]) > 5)
	{
		motor[0].errorSum = 0;
		g_targetEncoder[0] = 0;
	}
	else
	{
		g_targetEncoder[0] = g_targetEncoderSave[0];
	}
	if(abs(g_targetAngle[3] - g_nowAngle[3]) > 5)
	{
		motor[2].errorSum = 0;
		g_targetEncoder[2] = 0;
	}
	else
	{
		g_targetEncoder[2] = g_targetEncoderSave[2];
	}

	g_getEncoder[0] = TIM5->CNT;
	g_getEncoder[1] = TIM8->CNT;
	g_getEncoder[2] = TIM3->CNT;
	g_getEncoder[3] = TIM4->CNT;


	PID_Control_Long(&angle[1], g_targetAngle[1], g_nowAngle[1]);
	PID_Control_Long(&angle[3], g_targetAngle[3], g_nowAngle[3]);

	g_targetEncoder[1] = -angle[1].nowOutput;
	g_targetEncoder[3] = -angle[3].nowOutput;


	for (int i = 0 ; i < 4 ; i++)
	{
		if(g_getEncoder[i] > 30000)
			g_deltaEncoder[i] = -(65536 - g_getEncoder[i]);
		else
			g_deltaEncoder[i] = g_getEncoder[i];
		g_deltaEncoderCnt[i] += g_deltaEncoder[i];
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

void reset_encoder(uint8_t ch)
{
	g_deltaEncoder[ch] = 0;
	g_deltaEncoderCnt[ch] = 0;
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


