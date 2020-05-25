/*
 * master_main.c
 *
 *  Created on: Jun 22, 2019
 *      Author: colson
 */

#include <periphGpio.h>
#include <periphusart.h>
#include <periphMotor.h>
#include <periphusb.h>
#include <periphCAN.h>
#include <MW-AHRSv1.h>

#include "vector"
#include "main.h"
#include "can.h"
#include "conf.h"
#include "string.h"
#include <iostream>

#include "AuCAR_conf.h"
#include "master_main.h"
#include "stateMachine.h"

#include "usart.h"
#include "tim.h"

#include "ros/time.h"
#include "ros.h"

#include "std_msgs/Byte.h"
#include "std_msgs/ByteMultiArray.h"
#include "std_msgs/Header.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Imu.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"
#define DEBUG



#if LOCAL_DEVICE == C1
PeriphLED __led1(GPIOC, GPIO_PIN_0, 100);
PeriphLED __led2(GPIOC, GPIO_PIN_1, 500);
PeriphLED __led3(GPIOC, GPIO_PIN_2, 100);
PeriphLED __led4(GPIOC, GPIO_PIN_3, 500);
#elif LOCAL_DEVICE == C2
PeriphLED __led1(GPIOC, GPIO_PIN_0, 100);
PeriphLED __led2(GPIOC, GPIO_PIN_1, 500);
PeriphLED __led3(GPIOC, GPIO_PIN_2, 100);
PeriphLED __led4(GPIOC, GPIO_PIN_3, 500);
#elif LOCAL_DEVICE == C3

ros::NodeHandle nh;

std_msgs::String str_msg;
std_msgs::String str_dbgmsg;
std_msgs::Header str_header;
geometry_msgs::Vector3 topic_euler;

ros::Publisher pub_chat("AuCAR/chatter", &str_msg);
ros::Publisher pub_debub("AuCAR/debug", &str_dbgmsg);
ros::Publisher pub_header("AuCAR/header", &str_header);
ros::Publisher pub_euler("AuCAR/euler", &topic_euler);

char hello[] = "Hello world!";
char dbgmsg[] = "debuging";

/* mode selection callback */
void command_cb(const std_msgs::Byte& msg);

/* swarve drive mode callback */
void module0_cb(const geometry_msgs::Twist& msg);
void module1_cb(const geometry_msgs::Twist& msg);
void module2_cb(const geometry_msgs::Twist& msg);
void module3_cb(const geometry_msgs::Twist& msg);

/* c1 control callback */
void motor0_cb(const geometry_msgs::Twist& msg);
void motor1_cb(const geometry_msgs::Twist& msg);
void motor2_cb(const geometry_msgs::Twist& msg);
void motor3_cb(const geometry_msgs::Twist& msg);

/* c2 control callback */
void motor4_cb(const geometry_msgs::Twist& msg);
void motor5_cb(const geometry_msgs::Twist& msg);
void motor6_cb(const geometry_msgs::Twist& msg);
void motor7_cb(const geometry_msgs::Twist& msg);
void yaw_cb(const geometry_msgs::Vector3& msg);

ros::Subscriber<std_msgs::Byte> command_sub("AuCAR/command", &command_cb);

ros::Subscriber<geometry_msgs::Twist> module0_sub("AuCAR/module0", &module0_cb);
ros::Subscriber<geometry_msgs::Twist> module1_sub("AuCAR/module1", &module1_cb);
ros::Subscriber<geometry_msgs::Twist> module2_sub("AuCAR/module2", &module2_cb);
ros::Subscriber<geometry_msgs::Twist> module3_sub("AuCAR/module3", &module3_cb);

ros::Subscriber<geometry_msgs::Twist> motor0_sub("AuCAR/motor_0", &motor0_cb);
ros::Subscriber<geometry_msgs::Twist> motor1_sub("AuCAR/motor_1", &motor1_cb);
ros::Subscriber<geometry_msgs::Twist> motor2_sub("AuCAR/motor_2", &motor2_cb);
ros::Subscriber<geometry_msgs::Twist> motor3_sub("AuCAR/motor_3", &motor3_cb);

ros::Subscriber<geometry_msgs::Twist> motor4_sub("AuCAR/motor_4", &motor4_cb);
ros::Subscriber<geometry_msgs::Twist> motor5_sub("AuCAR/motor_5", &motor5_cb);
ros::Subscriber<geometry_msgs::Twist> motor6_sub("AuCAR/motor_6", &motor6_cb);
ros::Subscriber<geometry_msgs::Twist> motor7_sub("AuCAR/motor_7", &motor7_cb);

ros::Subscriber<geometry_msgs::Vector3> yaw_sub("AuCAR/yaw", &yaw_cb);


extern CAN_HandleTypeDef hcan1;
CAN_TxHeaderTypeDef can_tx_hedder = { 0, };
CAN_RxHeaderTypeDef can_rx_hedder = { 0, };
uint8_t can_tx_data[8] = { 0, };
uint8_t can_rx_data[8] = { 0, };
MW_AHRS ahrs_obj;



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

PeriphCAN __can1(&hcan1);

PeriphUSBCOM __usbcom();

#if LED_TYPE == C3_LED_ALT
PeriphGPIO __led1(GPIOA, GPIO_PIN_4, 1000);
PeriphGPIO __led2(GPIOA, GPIO_PIN_5, 500);
PeriphGPIO __led3(GPIOA, GPIO_PIN_6, 1000);
PeriphGPIO __led4(GPIOA, GPIO_PIN_7, 500);
#else
PeriphGPIO __led1(GPIOC, GPIO_PIN_4, 100);
PeriphGPIO __led2(GPIOC, GPIO_PIN_5, 500);
PeriphGPIO __led3(GPIOB, GPIO_PIN_0, 100);
PeriphGPIO __led4(GPIOB, GPIO_PIN_1, 500);
#endif
#endif

StateMachine g_stateMachines;



BUGCATCHER debug = {0,};

int __printf__io__putchar(int ch)
{
	uint8_t data = ch;

	//TODO change MAX485 or CAN line
	//__usart2.write(&data, 1);

	return ch;
}

void init(void) {
	/* ros init */

	nh.initNode();
	nh.advertise(pub_chat);
	nh.advertise(pub_header);
	nh.advertise(pub_debub);
	nh.advertise(pub_euler);

	nh.subscribe(module0_sub);
	nh.subscribe(module1_sub);
	nh.subscribe(module2_sub);
	nh.subscribe(module3_sub);

	nh.subscribe(motor0_sub);
	nh.subscribe(motor1_sub);
	nh.subscribe(motor2_sub);
	nh.subscribe(motor3_sub);

	nh.subscribe(motor4_sub);
	nh.subscribe(motor5_sub);
	nh.subscribe(motor6_sub);
	nh.subscribe(motor7_sub);

	nh.subscribe(yaw_sub);

	_DEBUG("ROS init OK.\r\n");

	/* Timer initilization */
	HAL_TIM_Base_Start_IT(&htim6);
	HAL_TIM_Base_Start_IT(&htim7);
	_DEBUG("Timer init OK.\r\n");

	/* IO initilization */
	__c1boot.set();
	__c2boot.set();

	__c1nrst.reset();
	__c2nrst.reset();

	__c1power.reset();
	__c2power.reset();
	_DEBUG("Default IO init OK.\r\n");

	/* USART initilization */
	__usart1.init();
	//__usart2.init();
	__usart3.init();
	_DEBUG("Usart init OK.\r\n");
	_DEBUG("All init OK.\r\n");

	/* CAN initilization */
	CAN_FilterTypeDef canFilter;
	canFilter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	canFilter.FilterMode = CAN_FILTERMODE_IDMASK;
	canFilter.FilterScale = CAN_FILTERSCALE_32BIT;
	canFilter.FilterIdHigh = 0x0000 << 5;
	canFilter.FilterIdLow = 0x0000;
	canFilter.FilterMaskIdHigh = 0x0000 << 5;
	canFilter.FilterMaskIdLow = 0x0000;
	canFilter.SlaveStartFilterBank = 0;
	canFilter.FilterBank = 0;
	canFilter.FilterActivation = CAN_FILTER_ENABLE;


	mw_ahrs_set_period(&ahrs_obj, 10);
	mw_ahrs_set_data_type(&ahrs_obj, 1, 1, 1, 1);
	can_tx_hedder.StdId = 0x01;
	can_tx_hedder.ExtId = 0x01;
	can_tx_hedder.RTR = CAN_RTR_DATA;
	can_tx_hedder.IDE = CAN_ID_STD;
	can_tx_hedder.DLC = 8;
	for(int i=0; i<8; i++)
		can_tx_data[i] = ahrs_obj.can_write_data[i];
	__can1.can_filter_init(canFilter);
	__can1.can_notification_init(CAN_IT_TX_MAILBOX_EMPTY | CAN_IT_RX_FIFO0_MSG_PENDING | CAN_IT_RX_FIFO0_FULL);
	__can1.can_start();
	__can1.can_transmit_data(&can_tx_hedder, can_tx_data);
}

uint32_t ntic=0;
uint32_t ptic=0;

uint32_t nowtick = 0;
uint32_t pasttick = 0;

uint32_t cannowtick = 0;
uint32_t canpasttick = 0;

uint32_t rosnowtick = 0;
uint32_t rospasttick = 0;

uint8_t abc = 0;
uint8_t cba = 0;

void run(void) {

	io_read();
	led_run();

	// circuit_logic_test();

	int cnt = 0;
	int read = 0;




	// usb test
	uint8_t mystring[] = "Hello?\n";
	ntic = HAL_GetTick();

	if(ntic - ptic > 100)
	{
		  CDC_Transmit_FS(mystring, strlen((const char*)mystring));
		  ptic = ntic;
	}



	while(1)
	{
		read = __usart1.read();

		if(cnt++ >= 100) {
			//break;
		}
		if(read == -1)
			break;
		else
			g_stateMachines.data_push_back(0, (uint8_t)read);
	}
	cnt = 0;
	while(1)
	{
		read = __usart3.read();

		if(cnt++ >= 100) {
			//break;
		}
		if(read == -1)
			break;
		else
			g_stateMachines.data_push_back(1, (uint8_t)read);
	}
	cnt = 0;
	/* test sender */
	nowtick = HAL_GetTick();
	if(nowtick - pasttick > 1000)
	{
//		uint8_t arr[50];
//		uint8_t checksum = 0;
//		for(int i = 0 ; i < 50; i++){
//			arr[i] = i;
//			checksum += arr[i];
//		}

//		uint8_t sendData1[8] = {0xFF, 0xFF, 0x05, 0x00, 0x04, 0x00, 0xF4, 0x01};
//		sendData1[6] = (uint8_t)50;
//		sendData1[7] = (uint8_t)50 >> 8;
//		__usart1.write(sendData1, sizeof(sendData1));
//		__usart3.write(sendData1, sizeof(sendData1));
//		__usart1.write(arr, sizeof(arr));
//		__usart3.write(arr, sizeof(arr));
//		__usart1.write(&checksum, sizeof(checksum));
//		__usart3.write(&checksum, sizeof(checksum));




		pasttick = nowtick;
	}

	cannowtick = HAL_GetTick();
	if(cannowtick - canpasttick > 50)
	{
		uint8_t debugyaw[100] = {0,};
		int yaw = (int)(ahrs_obj.e_yaw * 100.0);
		uint16_t cmd1 = 0x0030;
		uint16_t cmd2 = 0x0000;
		uint16_t len = 5;
		uint8_t sendData[14];
		sendData[0] = 0xFF;
		sendData[1] = 0xFF;
		sendData[2] = cmd1;
		sendData[3] = cmd1 >> 8;
		sendData[4] = cmd2;
		sendData[5] = cmd2 >> 8;
		sendData[6] = len;
		sendData[7] = len >> 8;
		sendData[8] = yaw;
		sendData[9] = yaw >> 8;
		sendData[10] = yaw >> 16;
		sendData[11] = yaw >> 24;
		sendData[12] = 0;
		for(int i = 0; i < len; i++)
			sendData[13]+= sendData[8+i];

//		__usart1.write(sendData, (2+2+2+2+len+1));
		canpasttick = cannowtick;
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
	stateMachineTask_ST get = { 0, };
	g_stateMachines.run();
	BOOL state = g_stateMachines.get_task(0, &get);
	if (state == true) {
#ifdef DEBUG
		char dbgmsg[] = "get angle from slave C1";
		char c_tick[10];
		itoa(nowtick, c_tick, 10);
		str_dbgmsg.data = strcat(c_tick, dbgmsg);
		pub_debub.publish(&str_dbgmsg);
#endif
		int getAngle1 = get.data[0];
		getAngle1 |= get.data[1] << 8;
		getAngle1 |= get.data[2] << 16;
		getAngle1 |= get.data[3] << 24;
		int getAngle3 = get.data[4];
		getAngle3 |= get.data[5];
		getAngle3 |= get.data[6];
		getAngle3 |= get.data[7];
		free(get.data);
	}

	state = g_stateMachines.get_task(1, &get);
	if (state == true) {
#ifdef DEBUG
		char dbgmsg[] = "get angle from slave C2";
		char c_tick[10];
		itoa(nowtick, c_tick, 10);
		str_dbgmsg.data = strcat(c_tick, dbgmsg);
		pub_debub.publish(&str_dbgmsg);
#endif
		int getAngle1 = get.data[0];
		getAngle1 |= get.data[1] << 8;
		getAngle1 |= get.data[2] << 16;
		getAngle1 |= get.data[3] << 24;
		int getAngle3 = get.data[4];
		getAngle3 |= get.data[5];
		getAngle3 |= get.data[6];
		getAngle3 |= get.data[7];
		free(get.data);
	}

	/*
	 * local functions
	 * PERIPHERAL - LED, PWM, ... , etc.
	 * */

	/*
	 * ROS task
	 * */
	rosnowtick = HAL_GetTick();
	if(rosnowtick - rospasttick > 100)
	{
		str_msg.data = hello;
		str_header.seq++;
		topic_euler.x = ahrs_obj.e_roll;
		topic_euler.y = ahrs_obj.e_pitch;
		topic_euler.z = ahrs_obj.e_yaw;
		pub_header.publish(&str_header);
		pub_chat.publish(&str_msg);
		pub_euler.publish(&topic_euler);
		rospasttick = rosnowtick;
	}
	nh.spinOnce();
	/*
	 * ROS task end
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
	{							}
	else
	{							}
	if(__id3.read() == GPIO_PIN_SET)
	{							}
	else
	{							}
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

int pp = 0;
void timer_1s(void)
{
	//TODO
	pp++;
	_DEBUG("hello world%d\r\n", pp);
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
		//__usart2.flush();
		nh.getHardware()->flush();
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
		//__usart2.reset_rbuf();
		nh.getHardware()->reset_rbuf();
	}
	else if(huart->Instance == USART3)
	{
		__usart3.reset_rbuf();
	}
}

//to C1 chip
void module0_cb(const geometry_msgs::Twist& msg){
#ifdef DEBUG
	char dbgmsg[] = "module0_cb";
	str_dbgmsg.data = dbgmsg;
	pub_debub.publish(&str_dbgmsg);
#endif
	__led1.setPeriod(50);
	int x = (int)(msg.linear.x * 100);
	int z = (int)(msg.angular.z * 100);
	static uint8_t seq = 0;
	uint8_t sendData[18] = {0,};
	uint8_t checksum = 0;
	uint8_t id = 0x10;
	uint16_t cmd1 = 0x1234;
	uint16_t cmd2 = 0x5678;
	uint16_t len = 9;
	sendData[0] = 0xFF;
	sendData[1] = 0xFF;
	sendData[2] = id;
	sendData[3] = cmd1 >> 8;
	sendData[4] = cmd2;
	sendData[5] = cmd2 >> 8;
	sendData[6] = len;
	sendData[7] = len >> 8;
	sendData[8] = x;
	sendData[9] = x >> 8;
	sendData[10] = x >> 16;
	sendData[11] = x >> 24;
	sendData[12] = z;
	sendData[13] = z >> 8;
	sendData[14] = z >> 16;
	sendData[15] = z >> 24;
	sendData[16] = seq++;
	for(int i = 8 ; i < 17; i++)
		checksum += sendData[i];
	sendData[17] = checksum;
	__usart1.write(sendData, sizeof(sendData));
}
void module1_cb(const geometry_msgs::Twist& msg){
#ifdef DEBUG
	char dbgmsg[] = "module1_cb";
	str_dbgmsg.data = dbgmsg;
	pub_debub.publish(&str_dbgmsg);
#endif
	__led2.setPeriod(50);
	int x = (int)(msg.linear.x * 100);
	int z = (int)(msg.angular.z * 100);
	static uint8_t seq = 0;
	uint8_t sendData[18] = {0,};
	uint8_t checksum = 0;
	uint8_t id = 0x20;
	uint16_t cmd1 = 0x1234;
	uint16_t cmd2 = 0x5678;
	uint16_t len = 9;
	sendData[0] = 0xFF;
	sendData[1] = 0xFF;
	sendData[2] = id;
	sendData[3] = cmd1 >> 8;
	sendData[4] = cmd2;
	sendData[5] = cmd2 >> 8;
	sendData[6] = len;
	sendData[7] = len >> 8;
	sendData[8] = x;
	sendData[9] = x >> 8;
	sendData[10] = x >> 16;
	sendData[11] = x >> 24;
	sendData[12] = z;
	sendData[13] = z >> 8;
	sendData[14] = z >> 16;
	sendData[15] = z >> 24;
	sendData[16] = seq++;
	for(int i = 8 ; i < 17; i++)
		checksum += sendData[i];
	sendData[17] = checksum;
	__usart1.write(sendData, sizeof(sendData));
}

//to c2 chip
void module2_cb(const geometry_msgs::Twist& msg){
#ifdef DEBUG
	char dbgmsg[] = "module2_cb";
	str_dbgmsg.data = dbgmsg;
	pub_debub.publish(&str_dbgmsg);
#endif
	__led3.setPeriod(50);
	int x = (int)(msg.linear.x * 100);
	int z = (int)(msg.angular.z * 100);
	static uint8_t seq = 0;
	uint8_t sendData[18] = {0,};
	uint8_t checksum = 0;
	uint8_t id = 0x10;
	uint16_t cmd1 = 0x1234;
	uint16_t cmd2 = 0x5678;
	uint16_t len = 9;
	sendData[0] = 0xFF;
	sendData[1] = 0xFF;
	sendData[2] = id;
	sendData[3] = cmd1 >> 8;
	sendData[4] = cmd2;
	sendData[5] = cmd2 >> 8;
	sendData[6] = len;
	sendData[7] = len >> 8;
	sendData[8] = x;
	sendData[9] = x >> 8;
	sendData[10] = x >> 16;
	sendData[11] = x >> 24;
	sendData[12] = z;
	sendData[13] = z >> 8;
	sendData[14] = z >> 16;
	sendData[15] = z >> 24;
	sendData[16] = seq++;
	for(int i = 8 ; i < 17; i++)
		checksum += sendData[i];
	sendData[17] = checksum;
	__usart3.write(sendData, sizeof(sendData));
}
void module3_cb(const geometry_msgs::Twist& msg){
#ifdef DEBUG
	char dbgmsg[] = "module3_cb";
	str_dbgmsg.data = dbgmsg;
	pub_debub.publish(&str_dbgmsg);
#endif
	__led4.setPeriod(50);
	int x = (int)(msg.linear.x * 100);
	int z = (int)(msg.angular.z * 100);
	static uint8_t seq = 0;
	uint8_t sendData[18] = {0,};
	uint8_t checksum = 0;
	uint8_t id = 0x20;
	uint16_t cmd1 = 0x1234;
	uint16_t cmd2 = 0x5678;
	uint16_t len = 9;
	sendData[0] = 0xFF;
	sendData[1] = 0xFF;
	sendData[2] = id;
	sendData[3] = cmd1 >> 8;
	sendData[4] = cmd2;
	sendData[5] = cmd2 >> 8;
	sendData[6] = len;
	sendData[7] = len >> 8;
	sendData[8] = x;
	sendData[9] = x >> 8;
	sendData[10] = x >> 16;
	sendData[11] = x >> 24;
	sendData[12] = z;
	sendData[13] = z >> 8;
	sendData[14] = z >> 16;
	sendData[15] = z >> 24;
	sendData[16] = seq++;
	for(int i = 8 ; i < 17; i++)
		checksum += sendData[i];
	sendData[17] = checksum;
	__usart3.write(sendData, sizeof(sendData));
}


/* mode selection callback */
void command_cb(const std_msgs::Byte& msg)
{

}

/* c1 control callback */
void motor0_cb(const geometry_msgs::Twist& msg)
{
#ifdef DEBUG
	char dbgmsg[] = "motor0_cb";
	str_dbgmsg.data = dbgmsg;
	pub_debub.publish(&str_dbgmsg);
#endif



}
void motor1_cb(const geometry_msgs::Twist& msg)
{
#ifdef DEBUG
	char dbgmsg[] = "motor1_cb";
	str_dbgmsg.data = dbgmsg;
	pub_debub.publish(&str_dbgmsg);
#endif

}
void motor2_cb(const geometry_msgs::Twist& msg)
{
#ifdef DEBUG
	char dbgmsg[] = "motor2_cb";
	str_dbgmsg.data = dbgmsg;
	pub_debub.publish(&str_dbgmsg);
#endif

}
void motor3_cb(const geometry_msgs::Twist& msg)
{
#ifdef DEBUG
	char dbgmsg[] = "motor3_cb";
	str_dbgmsg.data = dbgmsg;
	pub_debub.publish(&str_dbgmsg);
#endif

}

/* c2 control callback */
void motor4_cb(const geometry_msgs::Twist& msg)
{
#ifdef DEBUG
	char dbgmsg[] = "motor4_cb";
	str_dbgmsg.data = dbgmsg;
	pub_debub.publish(&str_dbgmsg);
#endif

}
void motor5_cb(const geometry_msgs::Twist& msg)
{
#ifdef DEBUG
	char dbgmsg[] = "motor5_cb";
	str_dbgmsg.data = dbgmsg;
	pub_debub.publish(&str_dbgmsg);
#endif

}
void motor6_cb(const geometry_msgs::Twist& msg)
{
#ifdef DEBUG
	char dbgmsg[] = "motor6_cb";
	str_dbgmsg.data = dbgmsg;
	pub_debub.publish(&str_dbgmsg);
#endif

}
void motor7_cb(const geometry_msgs::Twist& msg)
{
#ifdef DEBUG
	char dbgmsg[] = "motor7_cb";
	str_dbgmsg.data = dbgmsg;
	pub_debub.publish(&str_dbgmsg);
#endif

}

void yaw_cb(const geometry_msgs::Vector3& msg)
{
#ifdef DEBUG
	char dbgmsg[] = "yaw_cb";
	str_dbgmsg.data = dbgmsg;
	pub_debub.publish(&str_dbgmsg);
#endif
}

void can_tx_callback(CAN_HandleTypeDef *huart)
{

}
void can_rx_callback(CAN_HandleTypeDef *huart)
{

	HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &can_rx_hedder, can_rx_data);
	for (int i = 0; i < 8; i++) {
		ahrs_obj.can_read_data[i] = can_rx_data[i];
	}
	mw_ahrs_input_data(&ahrs_obj);
}
int make_packet(uint16_t cmd1, uint16_t cmd2, uint16_t len, uint8_t *data, uint8_t *dst)
{
	int length = 2 + 2 + 2 + len + 1;
	uint8_t checksum = 0;
	dst = (uint8_t *)malloc(sizeof(uint8_t) * length);

	dst[0] = 0xFF;
	dst[1] = 0xFF;
	dst[2] = cmd1;
	dst[3] = cmd1 >> 8;
	dst[4] = cmd2;
	dst[5] = cmd2 >> 8;
	dst[6] = length;
	dst[7] = length >> 8;
	for(int i = 0; i < len; i++)
	{
		dst[8+i] = data[i];
		checksum+= data[i];
	}
	dst[8+len] = checksum;
	return length;
}
