/*==============================================================================
 *
 *   pid_control.c
 *
 *   	File Name   	: pid_control.c
 *  	Version        	: 1.0
 *    	Date           	: Apr 28, 2015
 *		Modified       	: Apr 28, 2015 By ParkSuhan
 *		Author         	: ParkSuhan  (ROBIT 8th, Kwangwoon University)
 *		MPU_Type       	: MC56F8257 (60MHz)
 *		Compiler		: Freescale CodeWarrior 10.5
 *		Copyright(c) 2015 ROBIT, Kwangwoon University.
 *    	All Rights Reserved.
 *
==============================================================================*/

#include "pid_control_long.h"

/*!
** @file pid_control_long.c
** @version 1.01
** @brief
**         Long ������ ���� ���� PID����� �ڵ� ���� \n
**         �� ����� Long���� ����ϴ� PID������� �Լ��� ����ü�� ����ֽ��ϴ�. 
*/         
  

void PID_Control_Long_Initialize(LPID* dst)
{
	dst->errorSum = 0;
	dst->errorSumLimit = 500;
	dst->kP = 18000;
	dst->kI = 700;
	dst->kD = 0;
	dst->pastError = 0;
	dst->pastOutput = 0;
	dst->pastValue = 0;
	dst->underOfPoint = 1000;
	dst->outputLimit = 500;
}
void PID_Control_Long_Initialize2(LPID* dst)
{
	dst->errorSum = 0;
	dst->errorSumLimit = 500;
	dst->kP = 18000;
	dst->kI = 700;
	dst->kD = 0;
	dst->pastError = 0;
	dst->pastOutput = 0;
	dst->pastValue = 0;
	dst->underOfPoint = 1000;
	dst->outputLimit = 999;
}
void PID_Control_Long_Initialize_angle(LPID* dst)
{
	dst->errorSum = 0;
	dst->errorSumLimit = 100;
	dst->kP = 1000;
	dst->kI = 9;
	dst->kD = 20;
	dst->pastError = 0;
	dst->pastOutput = 0;
	dst->pastValue = 0;
	dst->underOfPoint = 1000;
	dst->outputLimit = 50;
}
void PID_Control_Long(LPID* dst, long target, long input)
{
	dst->nowValue = input;
	dst->target = target;
	dst->nowError =  dst->nowValue -dst->target ;
	dst->errorSum += dst->nowError;
	dst->errorDiff = dst->nowError - dst->pastError;
	
	if(dst->errorSumLimit != 0)
	{
		if(dst->errorSum > dst->errorSumLimit)
			dst->errorSum = dst->errorSumLimit;
		else if(dst->errorSum < -dst->errorSumLimit)
			dst->errorSum = -dst->errorSumLimit;
	}
	
	
	dst->nowOutput = 
			dst->kP * dst->nowError +
			dst->kI * dst->errorSum +
			dst->kD * dst->errorDiff;
			
	if(dst->underOfPoint == 0) return;	// Escape Error
	
	dst->nowOutput /= dst->underOfPoint;
	dst->pastError = dst->nowError;
	
	if(dst->outputLimit != 0)
	{
		if(dst->nowOutput > dst->outputLimit) dst->nowOutput = dst->outputLimit;
		else if(dst->nowOutput < -dst->outputLimit) dst->nowOutput = -dst->outputLimit;
	}
}
