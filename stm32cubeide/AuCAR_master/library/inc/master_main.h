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

#define C1 0x01
#define C2 0x02
#define C3 0x03




void init(void);
void run(void);


void timer_10ms(void);


#ifdef __cplusplus
}
#endif
#endif /* INC_MASTER_MAIN_H_ */
