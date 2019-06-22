/*
 * master_main.c
 *
 *  Created on: Jun 22, 2019
 *      Author: colson
 */

#include "master_main.h"
#include "frame_handler.h"

QUEUE_ST g_usart1_tx_queue;
QUEUE_ST g_usart1_rx_queue;
QUEUE_ST g_usart2_tx_queue;
QUEUE_ST g_usart2_rx_queue;
QUEUE_ST g_usart3_tx_queue;
QUEUE_ST g_usart3_rx_queue;

dataFrame_ST g_frame1;
dataFrame_ST g_frame2;
dataFrame_ST g_frame3;
dataFrame_ST g_frame4;
dataFrame_ST g_frame5;
dataFrame_ST g_frame6;

void init(void)
{
	u8_init_queue(&g_usart1_tx_queue);
	u8_init_queue(&g_usart1_rx_queue);
	u8_init_queue(&g_usart2_rx_queue);
	u8_init_queue(&g_usart2_rx_queue);
	u8_init_queue(&g_usart3_rx_queue);
	u8_init_queue(&g_usart3_rx_queue);
	frame_init(&g_frame1);
	frame_init(&g_frame2);
	frame_init(&g_frame3);
	frame_init(&g_frame4);
	frame_init(&g_frame5);
	frame_init(&g_frame6);
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
