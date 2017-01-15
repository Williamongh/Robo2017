/*!
 * @file       Robocon_TIM.c
 * @brief      Robocon����С��TIMӦ��ģ��
 * @author     HRCT
 * @version    v1.0
 * @date       2016-09-27
 */
 
 #include "TIM.h"
 
 /********************************����Ϊ��������*************************/
 /***********************************************************************/
 u16 Encode[3];				//�洢����������
 
 void Quadrature_decode_TIM1_Init(void)
 {
	 RCC->APB2ENR |= (1<<11);		//PA8,PA9
	 RCC->APB2ENR |= (1<<0);		//??��3��?1|?��?a??
	 RCC->APB2ENR |= (1<<6);
	 
	 //AFIO->MAPR |= (3<<6);			//������?��3��?
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
//	 /***TIM����ͨ�����õ� GPIO ���Ž��г�ʼ��***/
//	 TIM1_GPIO_Config();
//	 /***TIM ������г�ʼ��***/
//	 TIM1_Mode_Config();
//}
void TIM1_GPIO_Config(void)
{
	
	
	
	
			GPIO_InitTypeDef GPIO_InitStructure;
       /* PA8����Ϊ���ܽ�(PWM) */
	

			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE); 

				GPIO_AFIODeInit();  //�տ�ʼû�������䣬����һֱû����ӳ��ɹ�
			GPIO_PinRemapConfig(GPIO_FullRemap_TIM1 , ENABLE); //���������ӳ�书�ܺ���
	
       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_10;

       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

       GPIO_Init(GPIOE, &GPIO_InitStructure);

        /*PB13 ����ΪPWM�ķ��������*/

       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_11;

       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

       GPIO_Init(GPIOE, &GPIO_InitStructure);


 }

void TIM1_Mode_Config(void)
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
    /*����TIM1*/

     TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

     TIM_OCInitTypeDef  TIM_OCInitStructure;

	   TIM_BDTRInitTypeDef TIM_BDTRInitStructure;

	   	/******PWM��ƽ����ֵ**********/
		uint16_t CCR1_Val=0;
		uint16_t CCR2_Val=0;

	
 
	/******��һ���� ʱ����ʼ��**********/
       TIM_DeInit(TIM1); //����Ϊȱʡֵ
		 /*TIM1ʱ������*/
		 TIM_TimeBaseStructure.TIM_Period = 999;//װ��ֵ 
		 TIM_TimeBaseStructure.TIM_Prescaler = 4; //Ԥ��Ƶ(ʱ�ӷ�Ƶ)
		 TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���
		 TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;   //������ʱ�ӷָ�
		 TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;    //���ڼ�����ֵ
		 TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);    //��ʼ��TIMx��ʱ�������λ
		
  	/******�ڶ����� ���ģʽ��ʼ��**********/
		 /* Channel 1 Configuration in PWM mode ͨ��һ��PWM */
		 TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;     //PWMģʽ1
		 TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //����ͨ����Ч  PE8 
		 TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //����ͨ��Ҳ��Ч PE9
	  /******�������� װ������ֵ**********/
		 TIM_OCInitStructure.TIM_Pulse = CCR1_Val;        //ռ��ʱ��  
		 
		 TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   //�������
	     //���漸�������Ǹ߼���ʱ���Ż��õ���ͨ�ö�ʱ����������
		 TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;                                                                                                                                ;     //�����˵ļ��� 
		 TIM_OCInitStructure.TIM_OutputNState=TIM_OutputNState_Enable;//ʹ�ܻ�������� 
		 TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;  //����״̬�µķǹ���״̬ ����
		 TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;  //�Ȳ���
		
		 TIM_OC1Init(TIM1,&TIM_OCInitStructure);       //����ʼ������TIMxͨ��1����2.0��ΪTIM_OCInit
     TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);//ʹ��Ԥװ�ؼĴ���

		 TIM_OCInitStructure.TIM_Pulse = CCR2_Val;        //ռ��ʱ��  144 ����40��ʱ��Ϊ�ߣ���������������෴
	//	 TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   //�������
	//	 TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;  //ʹ�ܸ�ͨ�����
	     //���漸�������Ǹ߼���ʱ���Ż��õ���ͨ�ö�ʱ����������
//		 TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;//�����˵ļ��� 
															//���ڴ˲����ã�������������һ��
		 TIM_OC2Init(TIM1,&TIM_OCInitStructure);       //����ʼ������TIMxͨ��1����2.0��ΪTIM_OCInit
     TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable);//ʹ��Ԥװ�ؼĴ���




	/******������ɲ���������ã��߼���ʱ�����еģ�ͨ�ö�ʱ����������******/
		TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Disable;//����ģʽ�����ѡ��
		TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Disable;//����ģʽ�����ѡ�� 
		TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;    //��������
		TIM_BDTRInitStructure.TIM_DeadTime = 1;                  //����ʱ������
		TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;        //ɲ������ʹ��
		TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_Low;//ɲ�����뼫��
		TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;//�Զ����ʹ�� 
	
		TIM_BDTRConfig(TIM1,&TIM_BDTRInitStructure);

		TIM_ARRPreloadConfig(TIM1,ENABLE);	  //ʹ����װ�ؼĴ���
		 /* TIM1 counter enable����ʱ�� */
		 TIM_Cmd(TIM1,ENABLE);
		      /* TIM1 Main Output Enable ʹ��TIM1����������*/
		 TIM_CtrlPWMOutputs(TIM1, ENABLE);  //pwm���ʹ�ܣ�һ��Ҫ�ǵô�
	/*TIM_OC1PreloadConfig(),TIM_ARRPreloadConfig();�������������Ƶ���ccr1��arr��Ԥװ��ʹ�ܣ�
	ʹ�ܺ�ʧ�ܵ�������ǣ�ʹ�ܵ�ʱ���������Ĵ����Ķ�д��Ҫ�ȴ��и����¼�����ʱ���ܱ��ı�
	���������������Ǹ���ʱ�䣩��
	ʧ�ܵ�ʱ�����ֱ�ӽ��ж�д��û���ӳ١�
	 ���������е�����Ҫ�ı�pwm��Ƶ�ʺ�ռ�ձȵ��ã�TIM_SetAutoreload() 
	TIM_SetCompare1()�����������Ϳ����ˡ�*/
}

 

//���ò���Ĵ���1��Ȼ��Ϳ�������������ͨ�����̸ı�ռ�ձ�
//void SetT1Pwm1(u16 pulse)
//{
// TIM1->CCR1=pulse; //CCRxΪ�ȽϼĴ���
//}

/*�����Ĵ����ı�ռ��ʱ��*/


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
	


/********************************����ΪPWM���**************************/
/***********************************************************************/
void PWMout_TIM2_TIM3_Init(u16 CCR11, u16 CCR12, u16 CCR21, u16 CCR22, u16 CCR31, u16 CCR32)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* ����TIM2,TIM3CLK Ϊ 72MHZ */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3, ENABLE); 

  /* GPIOA clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

  /*GPIOA Configuration: TIM2 channel 1,2,3,4 and TIM3 channel 1,2 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

  /* Time base configuration */		 
  TIM_TimeBaseStructure.TIM_Period = 999;       //����ʱ����0������999����Ϊ1000�Σ�Ϊһ����ʱ����
  TIM_TimeBaseStructure.TIM_Prescaler = 4;	    //����Ԥ��Ƶ������Ƶ��36MHz, ��������1000, �����PWM����36kHz
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ(�����ò���)				��ע���ô��Ƕ��ⲿʱ�Ӳ�����ʱ�ӷ�Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = CCR11;	   //��������ֵ�������������������ֵʱ����ƽ��������
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
  TIM_OC1Init(TIM2, &TIM_OCInitStructure);	 //ʹ��ͨ��1
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR12;	  //����ͨ��2�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
  TIM_OC2Init(TIM2, &TIM_OCInitStructure);	  //ʹ��ͨ��2
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR21;	//����ͨ��3�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
  TIM_OC3Init(TIM2, &TIM_OCInitStructure);	 //ʹ��ͨ��3
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR22;	//����ͨ��4�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
  TIM_OC4Init(TIM2, &TIM_OCInitStructure);	//ʹ��ͨ��4
  TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
  TIM_ARRPreloadConfig(TIM2, ENABLE);			 // ʹ��TIM2���ؼĴ���ARR
  /* TIM2 enable counter */
  TIM_Cmd(TIM2, ENABLE);                   //ʹ�ܶ�ʱ��2
	
	/* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR31;	//����ͨ��1�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);	 //ʹ��ͨ��1
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR32;	//����ͨ��2�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);	//ʹ��ͨ��2
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
  TIM_ARRPreloadConfig(TIM3, ENABLE);			 // ʹ��TIM3���ؼĴ���ARR
  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);                   //ʹ�ܶ�ʱ��3
}

/********************************����Ϊ��ʱ�ж�*************************/
/***********************************************************************/
void Interrupt_TIM6_Init(void)
{
	RCC->APB1ENR |= (1<<4);
	
	TIM6->PSC = 71;					//�ж����ڣ�(71+1)*(999+1)/72M = 0.001s   (1ms�ж�)
	TIM6->ARR = 999;
	
	TIM6->DIER |= (1<<0);
	TIM6->CR1 |= (1<<2);
	
	TIM6->CNT = 0;
	
	TIM6->CR1 |= (1<<0);

	
}
	
void Interrupt_TIM7_Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		
		/* ����TIM2CLK Ϊ 72MHZ */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7 , ENABLE);
    //TIM_DeInit(TIM2);
	
	/* �Զ���װ�ؼĴ������ڵ�ֵ(����ֵ) */
    TIM_TimeBaseStructure.TIM_Period=9999;  //10ms
	
    /* �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж� */
	  /* ʱ��Ԥ��Ƶ��Ϊ72 */
    TIM_TimeBaseStructure.TIM_Prescaler= 71;
	
		/* ���ⲿʱ�ӽ��в�����ʱ�ӷ�Ƶ,����û���õ� */
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
    TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
	
    TIM_ClearFlag(TIM7, TIM_FLAG_Update);
	
    TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);
		
    TIM_Cmd(TIM7, ENABLE);																		
    
   // RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7 , DISABLE);		/*�ȹرյȴ�ʹ��*/ 
}
		
	
	
	

