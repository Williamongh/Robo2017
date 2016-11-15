#include "include.h"

void RCC_Init()
{
		RCC_DeInit(); /*将外设RCC寄存器重设为缺省值 */
		RCC_HSICmd(ENABLE);
		while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY)== RESET);//等待HSI就绪
		RCC_HCLKConfig(RCC_SYSCLK_Div1);   /*设置AHB时钟（HCLK） RCC_SYSCLK_Div1——AHB时钟 = 系统时*/ 
		RCC_PCLK2Config(RCC_HCLK_Div1);   /* 设置高速AHB时钟（PCLK2)RCC_HCLK_Div1——APB2时钟 = HCLK*/    
		RCC_PCLK1Config(RCC_HCLK_Div2); /*设置低速AHB时钟（PCLK1）RCC_HCLK_Div2——APB1时钟 = HCLK / 2*/
	
		FLASH_SetLatency(FLASH_Latency_2);   /*设置FLASH存储器延时时钟周期数FLASH_Latency_2  2延时周期*/  
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);  /*选择FLASH预取指缓存的模,预取指缓存使能*/
	
		RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_16);/*设置PLL时钟源及倍频系数，频率为8/2*8=16Mhz*/   
		RCC_PLLCmd(ENABLE);   /*使能PLL */
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) ; /*检查指定的RCC标志位(PLL准备好标志)设置与否*/   
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);  /*设置系统时钟（SYSCLK） */ 
		while(RCC_GetSYSCLKSource() != 0x08);     /*0x08：PLL作为系统时钟 */     
}

