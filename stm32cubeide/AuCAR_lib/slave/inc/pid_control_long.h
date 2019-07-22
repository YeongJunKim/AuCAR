/*==============================================================================
 *
 *   pid_control_long.h
 *
 *   	File Name   	: pid_control_long.h
 *  	Version        	: 1.0
 *    	Date           	: Apr 28, 2015
 *		Modified       	: Apr 28, 2015 By ParkSuhan
 *		Author         	: ParkSuhan  (ROBIT 8th, Kwangwoon University)
 *		MPU_Type       	: MC56F8257 (60MHz)
 *		Compiler		: Freescale CodeWarrior 10.6
 *		Copyright(c) 2015 ROBIT, Kwangwoon University.
 *    	All Rights Reserved.
 *
==============================================================================*/

/*!
** @file pid_control_long.h
** @version 1.01
** @brief
**         Long ������ ���� ���� PID����� ��� \n
**         �� ����� Long���� ����ϴ� PID������� �Լ��� ����ü�� ����ֽ��ϴ�. 
*/         

#ifndef PID_CONTROL_LONG_H_
#define PID_CONTROL_LONG_H_

 
#ifdef __cplusplus
extern "C" {
#endif

/* Part of PID Struct */

/** Long ���� PID ����� ������ ����ü */
typedef struct _LONGPID{
	long nowValue;		//!< ���� ��
	long pastValue;		//!< ���� ��
	
	long nowError;		//!< ���� ������
	long pastError;		//!< ���� ������
	long target;		//!< ��ǥ��
	
	long errorSum;		//!< ���� ������
	long errorSumLimit;	//!< ���� ������ ���� (0�� ��� ���� ����)
	long errorDiff;		//!< ���� �̺а�

	long nowOutput;		//!< ���� ��°�
	long pastOutput;	//!< ���� ��°�
	long outputLimit;	//!< ��� ���Ѱ�
	
	long underOfPoint;	//!< kP, kI, kD�� �������� ���� ������ (underOfPoint=1000, kP=1�̸� P�̵氪 = 0.001)
	
	long kP;			//!< P(���)�̵氪
	long kI;			//!< I(����)�̵氪
	long kD;			//!< D(�̺�)�̵氪
}LPID;


/* Part of PID Function */

/** Long �̵氪�� ����ϴ� PID ����� �Լ� */
void PID_Control_Long(LPID* dst, 	//!< ���� ��� PID ������ ����ü
		long target, 				//!< ��ǥ ��
		long input					//!< ���� ��
		);

/** Long �̵氪�� ����ϴ� PID ����ü �ʱ�ȭ �Լ� */
void PID_Control_Long_Initialize(LPID* dst //!< ���� ��� PID ������ ����ü
		);


#ifdef __cplusplus
}
#endif

#endif /* PID_CONTROL_LONG_H_ */
