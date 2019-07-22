/*
 * stateMachine.h
 *
 *  Created on: Jun 23, 2019
 *      Author: colson
 */

/* task map */
/*
 * ======================================================================================================================================
 * packet |  2bytes  |  2bytes  |  2bytes  |  2bytes  |      varing-bytes      |    1byte   |
 *        |  s-bits  |   cmd1   |   cmd2   |  length  |  depend on length bits |  checksum  |
 * ======================================================================================================================================
 * cmd1 : command 1
 * request command
 * type, set mode, set value
 * --------------------------------------------------------------------------------------------------------------------------------------
 * == 0x0001
 * request ping (every 1sec)
 * If there is no ack signal from slaves, reboot slaves. (power control)
 *
 * == 0x0002
 * request cpu rate
 *--------------------------------------------------------------------------------------------------------------------------------------
 * == 0x@000
 * request motor@ type(absolute or incremental)
 *
 * == 0x@001
 * request motor@ set mode(PWM mode PID mode)
 *
 * == 0x@002
 * request motor@ set PID(long type setting)
 *
 * == 0x@003
 * request motor@ set value of PWM
 *
 * == 0x@004
 * request motor@ set value of PID (long type)
 *
 * == 0x@005
 * request motor@ set value of wheel size (for calculate speed)
 *
 * == 0x@006
 * request motor@ ~~~~~
 *
 * == 0x@010
 * request motor@ set target PWM
 *
 * == 0x@020
 * request motor@ set target PID
 *
 *
 * --------------------------------------------------------------------------------------------------------------------------------------
 *
 *
 * ======================================================================================================================================
 * cmd2 : command 2
 * ack command
 * Command2 bytes is ack for command1 request.
 * If cmd1 bytes is 0x0001, cmd2 bytes same as cmd1(0x0001) request -> ack
 * --------------------------------------------------------------------------------------------------------------------------------------
 *
 *
 *
 *
 *
 *
 *
 *
 * ======================================================================================================================================
 * --------------------------------------------------------------------------------------------------------------------------------------
 */
/*task map end */

#ifndef INC_STATEMACHINE_H_
#define INC_STATEMACHINE_H_


#include "main.h"
#include "vector"
#include "stdlib.h"
#include "data_struct.h"
#include "AuCAR_conf.h"


#ifndef BOOL
#define BOOL int
#endif

#define true 1
#define false 0

typedef struct _stateMachineTask{
	uint16_t cmd1;
	uint16_t cmd2;
	uint16_t length;
	uint8_t *data;
}stateMachineTask_ST;

typedef struct _stateMachine{
	int 	state;
	uint16_t 	cmd1;
	uint16_t 	cmd2;
	uint16_t 	length;
	uint8_t 	*data;
	uint8_t 	checksum;
	uint16_t 	count;

	stateMachineTask_ST queue[TASK_MAX_QUEUE_SIZE];
	int qfront;
	int qrear;
	int qcount;
	int qmax_count;

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
	void machine_init(int index);
	void machine(int index, uint8_t data);

public:
	void add_task(int index);
	BOOL get_task(int index, stateMachineTask_ST *task);

public:
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
	int get_vector_size(int index)
	{
		if(index == 0)
			return data0.size();
		else if(index == 1)
			return data1.size();
		else if(index == 2)
			return data2.size();
		else
			return -1;
	}

public:
	void init_task_queue(int index);
	BOOL is_task_empty(int index);
	BOOL is_task_full(int index);
	BOOL task_enqueue(int index, stateMachineTask_ST value);
	BOOL task_dequeue(int index, stateMachineTask_ST *value);

public:



};




#endif /* INC_STATEMACHINE_H_ */
