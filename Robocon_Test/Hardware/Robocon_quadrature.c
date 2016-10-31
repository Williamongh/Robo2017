/*!
 * @file       main.c
 * @brief      Robocon测试小车主程序
 * @author     HRCT
 * @version    v1.0
 * @date       2016-09-27
 */
 
 #include "Robocon_quadrature.h"
 
 void Quadrature_decode_TIM1_Init(void)
 {
	 RCC->APB2ENR |= (1<<11);
	 RCC->APB2ENR |= (1<<2);
	 
	 GPIOA->CRH &= ~(1<<0);
	 GPIOA->CRH &= ~(1<<1);
	 GPIOA->CRH &= ~(1<<4);
	 GPIOA->CRH &= ~(1<<5);
	 
	 GPIOA->CRH |= (1<<2);
	 GPIOA->CRH &= ~(1<<3);
	 GPIOA->CRH |= (1<<6);
	 GPIOA->CRH &= ~(1<<7);
	 
	 TIM1->PSC = 0x0;
	 TIM1->ARR = 0xFFFF;
	 TIM1->CR1 &= ~(3<<8);
	 TIM1->CR1 &= ~(3<<5);
	 
	 TIM1->CCMR1 &= ~(1<<1);
	 TIM1->CCMR1 &= ~(1<<9);
	 TIM1->CCMR1 |= (1<<0);
	 TIM1->CCMR1 |= (1<<8);
	 
	 TIM1->CCER &= ~(1<<1);
	 TIM1->CCER &= ~(1<<5);
	 
	 TIM1->CCMR1 |= 8<<4;
	 
	 TIM1->SMCR &= ~(1<<2);
	 TIM1->SMCR |= (1<<0);
	 TIM1->SMCR |= (1<<1);
	 
	 TIM1->CNT = 0;
	 TIM1->CR1 |= (1<<0);
}
 
void Quadrature_decode_TIM8_Init(void)
{
	 RCC->APB2ENR |= (1<<11);
	 RCC->APB2ENR |= (1<<2);
	 
	 GPIOA->CRH &= ~(1<<0);
	 GPIOA->CRH &= ~(1<<1);
	 GPIOA->CRH &= ~(1<<4);
	 GPIOA->CRH &= ~(1<<5);
	 
	 GPIOA->CRH |= (1<<2);
	 GPIOA->CRH &= ~(1<<3);
	 GPIOA->CRH |= (1<<6);
	 GPIOA->CRH &= ~(1<<7);
	 
	 TIM8->PSC = 0x0;
	 TIM8->ARR = 0xFFFF;
	 TIM8->CR1 &= ~(3<<8);
	 TIM8->CR1 &= ~(3<<5);
	 
	 TIM8->CCMR1 &= ~(1<<1);
	 TIM8->CCMR1 &= ~(1<<9);
	 TIM8->CCMR1 |= (1<<0);
	 TIM8->CCMR1 |= (1<<8);
	 
	 TIM8->CCER &= ~(1<<1);
	 TIM8->CCER &= ~(1<<5);
	 
	 TIM8->CCMR1 |= 8<<4;
	 
	 TIM8->SMCR &= ~(1<<2);
	 TIM8->SMCR |= (1<<0);
	 TIM8->SMCR |= (1<<1);
	 
	 TIM8->CNT = 0;
	 TIM8->CR1 |= (1<<0);
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

