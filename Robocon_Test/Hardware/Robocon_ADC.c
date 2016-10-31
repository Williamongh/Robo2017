/*!
 * @file       Robocon_ADC.c
 * @brief      Robocon测试小车ADC模块
 * @author     HRCT
 * @version    v1.0
 * @date       2016-09-29
 */
 
 #include "Robocon_ADC.h"
 
volatile uint32_t Motor_Cur[3];
 
 static void ADC_Channel_Init(void)
 {
		RCC->APB2ENR |= (1<<9);					//ADC时钟使能
		RCC->APB2ENR |= (1<<3);					//GPIOB、C时钟使能
		RCC->APB2ENR |= (1<<4);
	 
		GPIOB->CRL &= 0xFFFFFF00;				//模拟输入模式   B0 B1 C4
		GPIOC->CRL &= 0xFFF0FFFF;
	 
		RCC->APB2RSTR |= (1<<9);				//ADC1复位
		RCC->APB2RSTR &= ~(1<<9);
		RCC->CFGR |= (3<<14);							//8分频	9MHz
	 
		ADC1->CR1 &= ~(0xF<<16);				//独立工作模式
		//ADC1->CR1 &= ~(1<<8);
		ADC1->CR1 |= (1<<8);						//扫描模式
		ADC1->CR2 |= (1<<1);						//连续转换模式
		ADC1->CR2 |= (7<<17);						//软件触发转换
		ADC1->CR2 |= (1<<8);						//使用DMA
	 
		ADC1->SMPR1 |= (5<<18);					//设置采样周期
		ADC1->SMPR1 &= ~(1<<19);
		/*
		ADC1->SMPR2 |= (5<<24);
		ADC1->SMPR2 &= ~(1<<25);
		ADC1->SMPR2 |= (5<<27);
		ADC1->SMPR2 &= ~(1<<28);
		ADC1->SMPR1 |= (5<<12);
		ADC1->SMPR1 &= ~(1<<13);					//只有我和上帝知道这段寄存器是怎么配的(*^_^*)		
		*/																//好了，现在只有上帝知道了(′д｀ )…彡…彡
	 
		ADC1->CR2 |= ((1<<23)+1);
		ADC1->CR2 |= (1<<3);							//开启复位校准寄存器
		while(ADC1->CR2&(1<<3));
		ADC1->CR2 |= (1<<2);							//开启AD校准
		while(ADC1->CR2&(1<<2));
	 
	 
		ADC1->SQR1 &= ~(0xF<<20);
		ADC1->SQR3 |= (1<<4);							//通道16
		/*
		ADC1->SQR1 &= ~(0xF<<20);
		ADC1->SQR1 |= (2<<20);
		ADC1->SQR3 |= (1<<3);							//通道8
		ADC1->SQR3 |= ((1<<3)+1)<<5);			//通道9
		ADC1->SQR3 |= (0xE<<10);					//通道14
		*/

		ADC1->CR2 |= (1<<22);							//开启软件触发  
		ADC1->CR2 |= (1<<0);							//重新写1，开始转换
 }
 
 
 static void DMA_Channel_Init(void)
 {
		RCC->AHBENR |= (1<<0);
	 
		DMA1_Channel1->CPAR = ((u32)0x40012400+0x4c);			//ADC数据地址
		DMA1_Channel1->CMAR = (u32)Motor_Cur;
		DMA1_Channel1->CNDTR = 1;
		//DMA1_Channel1->CNDTR = 3;
		DMA1_Channel1->CCR |= (1<<12);			//通道优先级：中
		DMA1_Channel1->CCR &= ~(1<<0);			//外设到存储器
		DMA1_Channel1->CCR |= (1<<5);				//循环模式
		DMA1_Channel1->CCR &= ~(1<<7);			//存储器地址固定
		//DMA1_Channel1->CCR |= (1<<7);				//存储器地址增量
		DMA1_Channel1->CCR &= ~(1<<6);			//外设地址固定
		DMA1_Channel1->CCR |= (1<<10);			//存储器数据宽度：半字
		DMA1_Channel1->CCR |= (1<<8);				//外设数据宽度：半字
		
		DMA1_Channel1->CCR |= (1<<0);				//通道1使能
 }
 
 void Current_ADGet_Init(void)
 {
		ADC_Channel_Init();
		DMA_Channel_Init();
 }

 
 

