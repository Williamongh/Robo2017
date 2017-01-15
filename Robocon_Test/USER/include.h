#ifndef		__INCLUDE_H__
#define		__INCLUDE_H__


#define uint8 uint8_t
#define uint16 uint16_t
#define uint32 uint32_t

#define int8 int8_t
#define int16 int16_t
#define int32 int32_t

#if defined( DEBUG )
#define ASSERT(expr) \
    if (!(expr)) \
        assert_failed(__FILE__, __LINE__)
#else
#define ASSERT(expr)
#endif

////////////////////////ͷ�ļ�����

#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"

#include "Board.h"
#include "TIM.h"
#include "ADC.h"
#include "USART.h"
//#include "RCC_Conf.h"
#include "DAC.h"
#include "CAN.h"
#include "Key.h"
#include "NRF24L01.h"

#include "motion_control.h"
#include "motor.h"
#include "motorPID.h"
#include "Delay.h"

extern int16 var[6];    //��λ�� ����ʾ������Ҫ���ó� ������Ϊ6����������Ϊ uint8_t

extern uint16 var1,var2,var3,var4,var5,var6;
extern uint8_t startFlag, stopFlag;
/*
 * ��������ṹ��
 */
typedef struct
{
    uint16_t x;
    uint16_t y;
} Site_t;

/*
 * ������δ�С�ṹ��
 */
typedef struct
{
    uint16_t W;       //��
    uint16_t H;       //��
} Size_t;

#include "LCD.h"
#include "GUI.h"
#include "QDTFT_demo.h"

#include "Upper.h"
#include "UI_VAR.h"
//////////////////////��������������
#define V_P 0.0f
#define V_I 0.0f
#define V_D 0.0f

#define I_P 0.0f
#define I_I 0.0f
#define I_D 0.0f

#define IMAX 15.0f //�����������


typedef struct
{
		float pos_x ;
		float pos_y ;
		float zangle ;
		float xangle ;
		float yangle ;
		float w_z ;
}motion_status;	
	

extern float speed_set;
extern float direction_set;
extern motion_status motion;
extern uint32_t it_count;


#endif

