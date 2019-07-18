/*
 * stateMachine.c
 *
 *  Created on: Jun 23, 2019
 *      Author: colson
 */

#include "stateMachine.h"





void StateMachine::run(int index) {
	int nsize = 0;
	if(index == 1)
	{
		nsize = this->data1.size();
		for(int i = 0; i < nsize; i++)
		{
			machine(1, data1.at(i));
		}
	}
	else if(index == 2)
	{
		nsize = this->data2.size();
		for(int i = 0; i < nsize; i++)
		{
			machine(2, data2.at(i));
		}
	}
	else if(index == 3)
	{
		nsize = this->data3.size();
		for(int i = 0; i < nsize; i++)
		{
			machine(3, data3.at(i));
		}
	}
	data1.clear();
	data2.clear();
	data3.clear();
}

void StateMachine::machine(int index, uint8_t data)
{
	stateMachine_ST *str;
	str = &this->info[index];

	if(str->state == 0x00)
	{
		str->count = 0;
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
		if(str->count == str->length)
		{
			str->state = 0x09;
		}
	}
	else if(str->state == 0x09)
	{
		//checksum//


		//add task//


	}
}

