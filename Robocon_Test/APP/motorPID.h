#ifndef __MOTORpid__H
#define __MOTORpid__H
#include "include.h"

float Vel_Read(void);			  		//��ȡ��ǰ�ٶ� ��
float V_PID(float Vel_Set, float Vel_Get);  //��
int16_t I_PID(float I_Set, float I_Get);		//��
void Speed_Output(int16_t I_Output);			  //Get��

#endif
