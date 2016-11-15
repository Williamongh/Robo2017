#ifndef		__INCLUDE_H__
#define		__INCLUDE_H__

#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "stdio.h"
#include "math.h"

#include "motion_control.h"
#include "motor.h"

#include "Robocon_board.h"
#include "Robocon_TIM.h"
#include "Robocon_ADC.h"
#include "Robocon_Debug.h"
#include "usart.h"
#include "RCC_Conf.h"
#include "DAC.h"
	
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

