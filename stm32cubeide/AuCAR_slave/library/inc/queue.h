/*
 * queue.h
 *
 *  Created on: Jun 22, 2019
 *      Author: colson
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include "main.h"
#ifdef __cplusplus
extern "C"{
#endif

#ifndef BOOL
#define BOOL int
#endif

#define UART_RX_MAX_QUEUE 256
#define UART_TX_MAX_QUEUE 256
#define CAN_RX_MAX_QUEUE 30
#define CAN_TX_MAX_QUEUE 30


#define true 1
#define false 0


typedef struct _u_queue {
	uint8_t queue[UART_RX_MAX_QUEUE];
	int front;
	int rear;
	int count;
	int max_count;
} QUEUE_ST;

typedef struct _c_queue {
	// TODO CanRxMsgTypeDef queue[CAN_RX_MAX_QUEUE];
	int front;
	int rear;
	int count;
	int max_count;
} C_QUEUE_ST;

/*
 * for uint8_t arr
 *
 */

void u8_init_queue(QUEUE_ST *str);
BOOL u8_is_empty(QUEUE_ST * str);
BOOL u8_is_full(QUEUE_ST * str);
BOOL u8_enqueue(QUEUE_ST *str, uint8_t value);
BOOL u8_dequeue(QUEUE_ST *str, uint8_t* value);
/*
 * for CanRxMsgTypeDef arr
 *
 */

void cT_init_queue(C_QUEUE_ST *str);
BOOL cT_is_empty(C_QUEUE_ST * str);
BOOL cT_is_full(C_QUEUE_ST * str);
// TODO BOOL cT_enqueue(C_Q_Struct *str, CanRxMsgTypeDef* value);
// TPDP BOOL cT_dequeue(C_Q_Struct *str, CanRxMsgTypeDef* tx_msg);

#ifdef __cplusplus
}
#endif
#endif /* QUEUE_H_ */
