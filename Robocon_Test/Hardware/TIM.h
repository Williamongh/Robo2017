#ifndef 	__TIM_H__
#define 	__TIM_H__

#include "include.h"

void Quadrature_decode_TIM1_Init(void);
void Quadrature_decode_TIM8_Init(void);
void Quadrature_decode_TIM4_Init(void);


#define 	Motor1_Z(DUTY)		TIM2->CCR3 = DUTY;
#define		Motor1_F(DUTY)		TIM2->CCR4 = DUTY;
#define		Motor2_Z(DUTY)		TIM2->CCR1 = DUTY;
#define		Motor2_F(DUTY)		TIM2->CCR2 = DUTY;
#define		Motor3_Z(DUTY)		TIM3->CCR1 = DUTY;
#define		Motor3_F(DUTY)		TIM3->CCR2 = DUTY;

void PWMout_TIM2_TIM3_Init(u16 CCR11, u16 CCR12, u16 CCR21, u16 CCR22, u16 CCR31, u16 CCR32);

void Interrupt_TIM6_Init(void);
void TIM1_GPIO_Config(void);
void TIM1_Mode_Config(void);
void Interrupt_TIM7_Init(void);
extern  u16 Encode[3];

#endif

