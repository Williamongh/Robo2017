/*!
 * @file       Robocon_board.c
 * @brief      Robocon����С��Ӳ����
 * @author     HRCT
 * @version    v1.0
 * @date       2016-09-27
 */
 
 #include "Board.h"
//�ж����ȼ���ʼ��
void NVIC_Config(void)
{
		NVIC_InitTypeDef NVIC_InitStructure; 
	 
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	 
	 //��ʱ���ж����ȼ�����
		
		NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;	 
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	 
		NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;	  
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;	
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	 
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	 
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			   
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);		


		NVIC_InitStructure.NVIC_IRQChannel = USB_HP_CAN1_TX_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			   
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);		
		
		//��ʱ�жϲ�ѯ�������ȼ�����
		NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn; 
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

//		//�����ⲿ�ж����ȼ�����
//		NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn; 
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//		NVIC_Init(&NVIC_InitStructure);
   	//2401 IRQ    
		NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;  //�� EXTI3��ȫ���ж� 
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ�Ϊ 0 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;    //��Ӧ���ȼ�Ϊ 0 
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     //ʹ�� 
		NVIC_Init(&NVIC_InitStructure);

}



void Motor_Init()
{
    delay_ms(100);
    CAN_RoboModule_DRV_Reset(0,1);                      //��0��1�����������и�λ
    CAN_RoboModule_DRV_Reset(0,2);                      //��0��2�����������и�λ
	  CAN_RoboModule_DRV_Reset(0,3);                      //��0��3�����������и�λ
    CAN_RoboModule_DRV_Reset(0,4);                      //��0��4�����������и�λ	 
    delay_ms(1000);                                     //���͸�λָ������ʱ����Ҫ�У��ȴ���������λ��ϡ�
    CAN_RoboModule_DRV_Config(0,1,100,0);               //����Ϊ1s����һ������
    CAN_RoboModule_DRV_Config(0,2,100,0);               //����Ϊ1s����һ������
    CAN_RoboModule_DRV_Config(0,3,100,0);               //����Ϊ1s����һ������
    CAN_RoboModule_DRV_Config(0,4,100,0);               //����Ϊ1s����һ������	 
    delay_ms(10);
    CAN_RoboModule_DRV_Mode_Choice(0,1,Current_Velocity_Mode);  //ѡ����뿪��ģʽ
    CAN_RoboModule_DRV_Mode_Choice(0,2,Current_Velocity_Mode);  //ѡ����뿪��ģʽ
    CAN_RoboModule_DRV_Mode_Choice(0,3,Current_Velocity_Mode);  //ѡ����뿪��ģʽ
    CAN_RoboModule_DRV_Mode_Choice(0,4,Current_Velocity_Mode);  //ѡ����뿪��ģʽ	 
    delay_ms(500);                                      //����ģʽѡ��ָ���Ҫ�ȴ�����������ģʽ������������ʱҲ������ȥ����	 

}

void Sys_Init(void)
{

		//		Quadrature_decode_TIM1_Init();			//���������ʼ��


		Quadrature_decode_TIM8_Init();
		Quadrature_decode_TIM4_Init();

		//  PWMout_TIM2_TIM3_Init(0, 0, 0, 0, 0, 0);						//PWM�����ʼ��

		TIM1_GPIO_Config();
		TIM1_Mode_Config();


		USART1_Init(115200);//���ڳ�ʼ��
		UART4_Init(115200);
		ADC_Mode_Init();						//�����ɼ���ʼ��

		//  KEY_EXTI_Init();							//�����жϳ�ʼ��

		Interrupt_TIM6_Init();					//��ʱ���жϳ�ʼ��
		Interrupt_TIM7_Init();					//������ʱ��ѯ�жϳ�ʼ��
		CAN_Config();
		KEY_Init();

		NVIC_Config();
		
		//	 DAC1_Init();
		//	 DAC2_Init();	 		
		delay_init(72);
		Lcd_Init();
		Motor_Init();
		
		SPI_NRF_Init();
		NRF_CheckConnect();
		
		NRF_RX_Mode();		
//		
		setOrigin(0,0); 
}


 
 
