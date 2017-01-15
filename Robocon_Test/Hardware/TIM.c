/*!
 * @file       Robocon_TIM.c
 * @brief      Robocon测试小车TIM应用模块
 * @author     HRCT
 * @version    v1.0
 * @date       2016-09-27
 */
 
 #include "TIM.h"
 
 /********************************以下为正交解码*************************/
 /***********************************************************************/
 u16 Encode[3];				//存储编码器读数
 
 void Quadrature_decode_TIM1_Init(void)
 {
	 RCC->APB2ENR |= (1<<11);		//PA8,PA9
	 RCC->APB2ENR |= (1<<0);		//??ó3é?1|?ü?a??
	 RCC->APB2ENR |= (1<<6);
	 
	 //AFIO->MAPR |= (3<<6);			//íêè?ó3é?
	 GPIO_PinRemapConfig(GPIO_FullRemap_TIM1 ,ENABLE);
	 
	 GPIOE->CRH &= ~(1<<12);
	 GPIOE->CRH &= ~(1<<13);
	 GPIOE->CRH &= ~(1<<4);
	 GPIOE->CRH &= ~(1<<5);
	 
	 GPIOE->CRH |= (1<<14);
	 GPIOE->CRH &= ~(1<<15);
	 GPIOE->CRH |= (1<<6);
	 GPIOE->CRH &= ~(1<<7);
	 
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
 //////////////////////////////////////////////////////////////////////////////////////////////////////////


//void TM1_SPWM_Init(void)
//{
//	 /***TIM外设通道复用的 GPIO 引脚进行初始化***/
//	 TIM1_GPIO_Config();
//	 /***TIM 外设进行初始化***/
//	 TIM1_Mode_Config();
//}
void TIM1_GPIO_Config(void)
{
	
	
	
	
			GPIO_InitTypeDef GPIO_InitStructure;
       /* PA8设置为功能脚(PWM) */
	

			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE); 

				GPIO_AFIODeInit();  //刚开始没有这个语句，所以一直没有重映射成功
			GPIO_PinRemapConfig(GPIO_FullRemap_TIM1 , ENABLE); //这个就是重映射功能函数
	
       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_10;

       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

       GPIO_Init(GPIOE, &GPIO_InitStructure);

        /*PB13 设置为PWM的反极性输出*/

       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_11;

       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

       GPIO_Init(GPIOE, &GPIO_InitStructure);


 }

void TIM1_Mode_Config(void)
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
    /*配置TIM1*/

     TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

     TIM_OCInitTypeDef  TIM_OCInitStructure;

	   TIM_BDTRInitTypeDef TIM_BDTRInitStructure;

	   	/******PWM电平跳变值**********/
		uint16_t CCR1_Val=0;
		uint16_t CCR2_Val=0;

	
 
	/******第一部分 时基初始化**********/
       TIM_DeInit(TIM1); //重设为缺省值
		 /*TIM1时钟配置*/
		 TIM_TimeBaseStructure.TIM_Period = 999;//装载值 
		 TIM_TimeBaseStructure.TIM_Prescaler = 4; //预分频(时钟分频)
		 TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数
		 TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;   //设置了时钟分割
		 TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;    //周期计数器值
		 TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);    //初始化TIMx的时间基数单位
		
  	/******第二部分 输出模式初始化**********/
		 /* Channel 1 Configuration in PWM mode 通道一的PWM */
		 TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;     //PWM模式1
		 TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //正向通道有效  PE8 
		 TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //反向通道也有效 PE9
	  /******第三部分 装载跳变值**********/
		 TIM_OCInitStructure.TIM_Pulse = CCR1_Val;        //占空时间  
		 
		 TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   //输出极性
	     //下面几个参数是高级定时器才会用到，通用定时器不用配置
		 TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;                                                                                                                                ;     //互补端的极性 
		 TIM_OCInitStructure.TIM_OutputNState=TIM_OutputNState_Enable;//使能互补端输出 
		 TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;  //空闲状态下的非工作状态 不管
		 TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;  //先不管
		
		 TIM_OC1Init(TIM1,&TIM_OCInitStructure);       //数初始化外设TIMx通道1这里2.0库为TIM_OCInit
     TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);//使能预装载寄存器

		 TIM_OCInitStructure.TIM_Pulse = CCR2_Val;        //占空时间  144 中有40的时间为高，互补的输出正好相反
	//	 TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   //输出极性
	//	 TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;  //使能该通道输出
	     //下面几个参数是高级定时器才会用到，通用定时器不用配置
//		 TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;//互补端的极性 
															//若在此不设置，则跟上面的设置一样
		 TIM_OC2Init(TIM1,&TIM_OCInitStructure);       //数初始化外设TIMx通道1这里2.0库为TIM_OCInit
     TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable);//使能预装载寄存器




	/******死区和刹车功能配置，高级定时器才有的，通用定时器不用配置******/
		TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Disable;//运行模式下输出选择
		TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Disable;//空闲模式下输出选择 
		TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;    //锁定设置
		TIM_BDTRInitStructure.TIM_DeadTime = 1;                  //死区时间设置
		TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;        //刹车功能使能
		TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_Low;//刹车输入极性
		TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;//自动输出使能 
	
		TIM_BDTRConfig(TIM1,&TIM_BDTRInitStructure);

		TIM_ARRPreloadConfig(TIM1,ENABLE);	  //使能重装载寄存器
		 /* TIM1 counter enable开定时器 */
		 TIM_Cmd(TIM1,ENABLE);
		      /* TIM1 Main Output Enable 使能TIM1外设的主输出*/
		 TIM_CtrlPWMOutputs(TIM1, ENABLE);  //pwm输出使能，一定要记得打开
	/*TIM_OC1PreloadConfig(),TIM_ARRPreloadConfig();这两个函数控制的是ccr1和arr的预装载使能，
	使能和失能的区别就是：使能的时候这两个寄存器的读写需要等待有更新事件发生时才能被改变
	（比如计数溢出就是更新时间）。
	失能的时候可以直接进行读写而没有延迟。
	 另外在运行当中想要改变pwm的频率和占空比调用：TIM_SetAutoreload() 
	TIM_SetCompare1()这两个函数就可以了。*/
}

 

//设置捕获寄存器1，然后就可以在主函数中通过键盘改变占空比
//void SetT1Pwm1(u16 pulse)
//{
// TIM1->CCR1=pulse; //CCRx为比较寄存器
//}

/*操作寄存器改变占空时间*/


/////////////////////////////////////////////////////////////////////////////////////////////////






void Quadrature_decode_TIM8_Init(void)
{
	 RCC->APB2ENR |= (1<<13);			//PC6,PC7
	 RCC->APB2ENR |= (1<<4);
	 
	 GPIOC->CRL &= ~(1<<24);
	 GPIOC->CRL &= ~(1<<25);
	 GPIOC->CRL &= ~(1<<28);
	 GPIOC->CRL &= ~(1<<29);
	 
	 GPIOC->CRL |= (1<<26);
	 GPIOC->CRL &= ~(1<<27);
	 GPIOC->CRL |= (1<<30);
	 GPIOC->CRL &= ~(1<<31);
	 
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
 }
	
void Quadrature_decode_TIM4_Init(void)
{
	 RCC->APB1ENR |= (1<<2);			//PB6,PB7
	 RCC->APB2ENR |= (1<<3);
	 
	 GPIOB->CRL &= ~(1<<24);
	 GPIOB->CRL &= ~(1<<25);
	 GPIOB->CRL &= ~(1<<28);
	 GPIOB->CRL &= ~(1<<29);
	 
	 GPIOB->CRL |= (1<<26);
	 GPIOB->CRL &= ~(1<<27);
	 GPIOB->CRL |= (1<<30);
	 GPIOB->CRL &= ~(1<<31);
	 
	 TIM4->PSC = 0x0;
	 TIM4->ARR = 0xFFFF;
	 TIM4->CR1 &= ~(3<<8);
	 TIM4->CR1 &= ~(3<<5);
	 
	 TIM4->CCMR1 &= ~(1<<1);
	 TIM4->CCMR1 &= ~(1<<9);
	 TIM4->CCMR1 |= (1<<0);
	 TIM4->CCMR1 |= (1<<8);
	 
	 TIM4->CCER &= ~(1<<1);
	 TIM4->CCER &= ~(1<<5);
	 
	 TIM4->CCMR1 |= 8<<4;
	 
	 TIM4->SMCR &= ~(1<<2);
	 TIM4->SMCR |= (1<<0);
	 TIM4->SMCR |= (1<<1);
	 
	 TIM4->CNT = 0;
	 TIM4->CR1 |= (1<<0);
}
	


/********************************以下为PWM输出**************************/
/***********************************************************************/
void PWMout_TIM2_TIM3_Init(u16 CCR11, u16 CCR12, u16 CCR21, u16 CCR22, u16 CCR31, u16 CCR32)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* 设置TIM2,TIM3CLK 为 72MHZ */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3, ENABLE); 

  /* GPIOA clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

  /*GPIOA Configuration: TIM2 channel 1,2,3,4 and TIM3 channel 1,2 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

  /* Time base configuration */		 
  TIM_TimeBaseStructure.TIM_Period = 999;       //当定时器从0计数到999，即为1000次，为一个定时周期
  TIM_TimeBaseStructure.TIM_Prescaler = 4;	    //设置预分频：二分频，36MHz, 计数周期1000, 故输出PWM周期36kHz
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//设置时钟分频系数：不分频(这里用不到)				备注：该处是对外部时钟采样的时钟分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = CCR11;	   //设置跳变值，当计数器计数到这个值时，电平发生跳变
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //当定时器计数值小于CCR1_Val时为高电平
  TIM_OC1Init(TIM2, &TIM_OCInitStructure);	 //使能通道1
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR12;	  //设置通道2的电平跳变值，输出另外一个占空比的PWM
  TIM_OC2Init(TIM2, &TIM_OCInitStructure);	  //使能通道2
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR21;	//设置通道3的电平跳变值，输出另外一个占空比的PWM
  TIM_OC3Init(TIM2, &TIM_OCInitStructure);	 //使能通道3
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR22;	//设置通道4的电平跳变值，输出另外一个占空比的PWM
  TIM_OC4Init(TIM2, &TIM_OCInitStructure);	//使能通道4
  TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
  TIM_ARRPreloadConfig(TIM2, ENABLE);			 // 使能TIM2重载寄存器ARR
  /* TIM2 enable counter */
  TIM_Cmd(TIM2, ENABLE);                   //使能定时器2
	
	/* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR31;	//设置通道1的电平跳变值，输出另外一个占空比的PWM
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);	 //使能通道1
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR32;	//设置通道2的电平跳变值，输出另外一个占空比的PWM
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);	//使能通道2
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
  TIM_ARRPreloadConfig(TIM3, ENABLE);			 // 使能TIM3重载寄存器ARR
  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);                   //使能定时器3
}

/********************************以下为定时中断*************************/
/***********************************************************************/
void Interrupt_TIM6_Init(void)
{
	RCC->APB1ENR |= (1<<4);
	
	TIM6->PSC = 71;					//中断周期：(71+1)*(999+1)/72M = 0.001s   (1ms中断)
	TIM6->ARR = 999;
	
	TIM6->DIER |= (1<<0);
	TIM6->CR1 |= (1<<2);
	
	TIM6->CNT = 0;
	
	TIM6->CR1 |= (1<<0);

	
}
	
void Interrupt_TIM7_Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		
		/* 设置TIM2CLK 为 72MHZ */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7 , ENABLE);
    //TIM_DeInit(TIM2);
	
	/* 自动重装载寄存器周期的值(计数值) */
    TIM_TimeBaseStructure.TIM_Period=9999;  //10ms
	
    /* 累计 TIM_Period个频率后产生一个更新或者中断 */
	  /* 时钟预分频数为72 */
    TIM_TimeBaseStructure.TIM_Prescaler= 71;
	
		/* 对外部时钟进行采样的时钟分频,这里没有用到 */
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
    TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
	
    TIM_ClearFlag(TIM7, TIM_FLAG_Update);
	
    TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);
		
    TIM_Cmd(TIM7, ENABLE);																		
    
   // RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7 , DISABLE);		/*先关闭等待使用*/ 
}
		
	
	
	

