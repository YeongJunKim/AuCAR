/*
 * stateMachine.c
 *
 *  Created on: Jun 23, 2019
 *      Author: colson
 */

#include "stateMachine.h"



extern COUNTERS g_counters;


void StateMachine::machine_init(int index)
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
void StateMachine::run(void) {
	int nsize = 0;
	nsize = this->data0.size();
	for (int i = 0; i < nsize; i++) {
		machine(0, data0.at(i));
	}

	nsize = this->data1.size();
	for (int i = 0; i < nsize; i++) {
		machine(1, data1.at(i));
	}

	nsize = this->data2.size();
	for (int i = 0; i < nsize; i++) {
		machine(2, data2.at(i));
	}

	data0.clear();
	data1.clear();
	data2.clear();

	//get task//

}

void StateMachine::machine(int index, uint8_t data)
{
	stateMachine_ST *str;
	str = &this->info[index];

	if(str->state == 0x00)
	{
		str->count = 0;
		str->checksum = 0;
		if(data == 0xFF)
			str->state = 0x01;
		else
			str->state = 0x00;
	}
	else if(str->state == 0x01)
	{
		if(data == 0xFF)
			str->state = 0x02;
		else
			str->state = 0x00;
	}
	else if(str->state == 0x02)
	{
		str->cmd1 = data;
		str->state = 0x03;
	}
	else if(str->state == 0x03)
	{
		str->cmd1 |= (uint16_t)data << 8;
		str->state = 0x04;
	}
	else if(str->state == 0x04)
	{
		str->cmd2 = data;
		str->state = 0x05;
	}
	else if(str->state == 0x05)
	{
		str->cmd2 |= (uint16_t)data << 8;
		str->state = 0x06;
	}
	else if(str->state == 0x06)
	{
		str->length = data;
		str->state = 0x07;
	}
	else if(str->state == 0x07)
	{
		str->length |= (uint16_t)data << 8;
		str->state = 0x08;
		str->data = (uint8_t*)malloc(sizeof(uint8_t)*str->length);
	}
	else if(str->state == 0x08)
	{
		str->data[str->count++] = data;
		str->checksum += data;
		if(str->count == str->length)
		{
			str->state = 0x09;
		}
	}
	else if(str->state == 0x09)
	{
		//checksum//
		if(str->checksum == data)
		{
			//correct//
			g_counters.stateMachineCpltCounter[index]++;

		}
		//add task//
		add_task(str);

		//end task//
		free(str->data);
		str->checksum = 0x00;
		str->state = 0x00;
	}
}



void StateMachine::add_task(stateMachine_ST *str)
{
	stateMachineTask_ST task;
	task.cmd1 = str->cmd1;
	task.cmd2 = str->cmd2;
	task.length = str->length;
	//TODO
	//is queue empty?
	//and then add task
	if(is_task_empty(info))
	{
		task.data = (uint8_t*)malloc(sizeof(uint8_t)*task.length);

		task_enqueue(str, task);
	}
}
void StateMachine::get_task(void)
{

}










void StateMachine::init_task_queue(stateMachine_ST *str)
{
	str->qfront 		= 0;
	str->qrear 			= 0;
	str->qcount 		= 0;
	str->qmax_count 	= 0;
}
BOOL StateMachine::is_task_empty(stateMachine_ST *str)
{
	return str->qfront == str->qrear ? true : false;
}
BOOL StateMachine::is_task_full(stateMachine_ST *str)
{
	return (str->qrear + 1) % TASK_MAX_QUEUE_SIZE == str->qfront ? true : false;
}
BOOL StateMachine::task_enqueue(stateMachine_ST *str, stateMachineTask_ST value)
{
	if(!is_task_full(str))
	{
		int preIndex = str->qrear;
		str->qrear = (str->qrear + 1) % TASK_MAX_QUEUE_SIZE;
		str->queue[preIndex] = value;
		str->qcount++;
		if(str->qcount > str->qmax_count)
			str->qmax_count = str->qcount;
		return true;
	}
	return false;
}
BOOL StateMachine::task_dequeue(stateMachine_ST *str, stateMachineTask_ST *value)
{
	if (!str || !value)
		return false;
	if (!is_task_empty(str))
	{
		int preIndex = str->qfront;
		str->qfront = (str->qfront + 1) % TASK_MAX_QUEUE_SIZE;
		str->qcount--;

		*value = str->queue[preIndex];

		free(str->queue[preIndex].data);

		return true;
	}
	return false;
}
