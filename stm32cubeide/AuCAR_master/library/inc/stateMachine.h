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
	uint8_t 	state;
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
	std::vector<uint8_t> data1;
	std::vector<uint8_t> data2;
	std::vector<uint8_t> data3;



public:
	StateMachine(){
		for(int i = 0 ; i < 3; i ++)
		{
			info[i].state 		= 0;
			info[i].cmd1 		= 0;
			info[i].cmd2 		= 0;
			info[i].length 		= 0;
			info[i].data 		= NULL;
			info[i].checksum 	= 0;
			info[i].count 		= 0;
		}
	};
	/*
	 * state machine
	 * */
	void run(int index);

	void machine(int index, uint8_t data);

	void str_init(int index)
	{
		info[index].state = 0;
		info[index].cmd1 = 0;
		info[index].cmd2 = 0;
		info[index].length = 0;
		if(info[index].data != NULL)
			free(info[index]);
		else
			info[index].data = NULL;
	}

	int data_push_back(int index, uint8_t data)
	{
		if(index == 1)
			data1.push_back(data);
		else if(index == 2)
			data2.push_back(data);
		else if(index == 3)
			data3.push_back(data);
		else
			return -1;
		return 1;
	}
	int data_clear(int index)
	{
		if(index == 1)
			data1.clear();
		else if(index == 2)
			data2.clear();
		else if(index == 3)
			data3.clear();
		else
			return -1;
		return 1;
	}
};




#endif /* INC_STATEMACHINE_H_ */
