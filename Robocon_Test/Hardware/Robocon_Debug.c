/*!
 * @file       Robocon_Debug.c
 * @brief      Robocon测试小车调试模块
 * @author     HRCT
 * @version    v1.0
 * @date       2016-09-29
 */
 
#include "Robocon_Debug.h"

/**************************以下为普通按键*********************************/
/*************************************************************************/
void KEY_EXTI_Init(void)
{
		RCC->APB2ENR |= (1<<6);		//端口E时钟开启
		RCC->APB2ENR |= (1<<0);		//辅助功能AFIO时钟开启
	
		GPIOE->CRL &= 0xFFFF0000;		//PE0、1、2、3	//输入模式
	
		GPIOE->CRL |= (1<<3);
		GPIOE->CRL |= (1<<7);
		GPIOE->CRL |= (1<<11);
		GPIOE->CRL |= (1<<15);		//上/下拉模式			注意复位值！！！！！！！！！！！！！！！！！！！！
		
		GPIOE->ODR |= (1<<0);
		GPIOE->ODR |= (1<<1);
		GPIOE->ODR |= (1<<2);
		GPIOE->ODR |= (1<<3);		//上拉
		
		AFIO->EXTICR[0] |= (1<<2);		//EXTI线0、1、2、3由PE管脚0、1、2、3触发
		AFIO->EXTICR[0] |= (1<<6);
		AFIO->EXTICR[0] |= (1<<10);
		AFIO->EXTICR[0] |= (1<<14);
	
		EXTI->IMR |= (1<<0);			//EXTI线0
		EXTI->FTSR |= (1<<0);			//EXTI线0下降沿触发
		EXTI->IMR |= (1<<1);			//EXTI线1
		EXTI->FTSR |= (1<<1);			//EXTI线1下降沿触发
		EXTI->IMR |= (1<<2);			//EXTI线2
		EXTI->FTSR |= (1<<2);			//EXTI线2下降沿触发
		EXTI->IMR |= (1<<3);			//EXTI线3
		EXTI->FTSR |= (1<<3);			//EXTI线3下降沿触发
		
}
