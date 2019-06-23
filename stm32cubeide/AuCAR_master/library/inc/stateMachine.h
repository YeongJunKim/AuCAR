/*
 * stateMachine.h
 *
 *  Created on: Jun 23, 2019
 *      Author: colson
 */

#ifndef INC_STATEMACHINE_H_
#define INC_STATEMACHINE_H_


#include "main.h"

#include "AuCAR_conf.h"

typedef struct _stateMachine{
	uint8_t 	state;
	uint16_t 	cmd;
	uint16_t 	length;
	uint8_t 	*data;
	uint8_t 	checksum;
}stateMachine_ST;



class StateMachine {
protected:
	stateMachine_ST info[3];


public:
	StateMachine(){};

	/*
	 * state machine
	 * */
	void c2c_state_machine(stateMachine_ST inputSource, uint8_t *data, uint16_t size);
};




#endif /* INC_STATEMACHINE_H_ */
