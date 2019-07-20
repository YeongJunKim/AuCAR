/*
 * stateMachine.h
 *
 *  Created on: Jun 23, 2019
 *      Author: colson
 */
#ifndef INC_STATEMACHINE_H_
#define INC_STATEMACHINE_H_


#include "main.h"
#include "vector"
#include "stdlib.h"

#include "AuCAR_conf.h"

typedef struct _stateMachine{
	int 	state;
	uint16_t 	cmd1;
	uint16_t 	cmd2;
	uint16_t 	length;
	uint8_t 	*data;
	uint8_t 	checksum;
	uint16_t 	count;

}stateMachine_ST;


class StateMachine {
protected:
	int device;
	stateMachine_ST info[3];
	std::vector<uint8_t> data0;
	std::vector<uint8_t> data1;
	std::vector<uint8_t> data2;



public:
	StateMachine(){
		machine_init(0);
		machine_init(1);
		machine_init(2);
	};
	/*
	 * state machine
	 * */
	void run(void);

	void machine(int index, uint8_t data);

	void machine_init(int index)
	{
		info[index].state = 0;
		info[index].cmd1 = 0;
		info[index].cmd2 = 0;
		info[index].length = 0;
		if(info[index].data != NULL)
			free(info[index].data);
		else
			info[index].data = NULL;
	}

	int data_push_back(int index, uint8_t data)
	{
		if(index == 0)
			data0.push_back(data);
		else if(index == 1)
			data1.push_back(data);
		else if(index == 2)
			data2.push_back(data);
		else
			return -1;
		return 1;
	}
	int data_clear(int index)
	{
		if(index == 0)
			data0.clear();
		else if(index == 1)
			data1.clear();
		else if(index == 2)
			data2.clear();
		else
			return -1;
		return 1;
	}
};




#endif /* INC_STATEMACHINE_H_ */
