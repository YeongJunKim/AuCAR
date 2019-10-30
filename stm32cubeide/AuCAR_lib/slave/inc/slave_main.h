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

#include "interrupt_handler.h"
int __printf__io__putchar(int ch);

typedef uint8_t control_type;
#define TYPE_MOTOR 1

void init(void);
void run(void);
void led_run(void);

void timer_1s(void);
void timer_10ms(void);
void timer_15us(void);

void uart_tx_callback(UART_HandleTypeDef *huart);
void uart_rx_callback(UART_HandleTypeDef *huart);

#ifdef __cplusplus
}
#endif
#endif /* INC_MASTER_MAIN_H_ */
