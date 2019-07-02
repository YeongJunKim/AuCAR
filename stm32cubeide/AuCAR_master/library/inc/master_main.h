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
