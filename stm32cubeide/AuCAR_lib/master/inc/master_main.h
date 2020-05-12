/*
 * master_main.h
 *
 *  Created on: Jun 22, 2019
 *      Author: colson
 */

#ifndef INC_MASTER_MAIN_H_
#define INC_MASTER_MAIN_H_

#ifdef __cplusplus
extern "C" {
#endif
#define APP_RX_DATA_SIZE  128
#define APP_TX_DATA_SIZE  128

#include "interrupt_handler.h"
#include "usbd_cdc_if.h"
#include "string.h"


typedef struct _debug{
	int data[100];
	uint8_t read[100];
	int count1;
	int count2;
}BUGCATCHER;


int __printf__io__putchar(int ch);

void init(void);
void run(void);


void io_read(void);
void led_run(void);
void circuit_logic_test(void);
void timer_1s(void);
void timer_10ms(void);

void uart_tx_callback(UART_HandleTypeDef *huart);
void uart_rx_callback(UART_HandleTypeDef *huart);

#ifdef __cplusplus
}
#endif
#endif /* INC_MASTER_MAIN_H_ */
