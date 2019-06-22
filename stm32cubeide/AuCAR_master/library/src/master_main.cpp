/*
 * master_main.c
 *
 *  Created on: Jun 22, 2019
 *      Author: colson
 */

#include "master_main.h"
#include "frame_handler.h"
#include "hardware.h"
#include "main.h"

dataFrame_ST g_frame1;
dataFrame_ST g_frame2;
dataFrame_ST g_frame3;
dataFrame_ST g_frame4;
dataFrame_ST g_frame5;
dataFrame_ST g_frame6;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;

Hardware __uart1(&huart1);
Hardware __uart3(&huart3);

void init(void)
{
	__uart1.init();
	__uart3.init();
}

void run(void)
{
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

/*
 * state led
 *  */
void timer_1s(void)
{

}

/*
 * motor control
 * */
void timer_10ms(void)
{

}
