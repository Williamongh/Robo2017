/*!
 * @file       Robocon_board.c
 * @brief      Robocon测试小车硬件板
 * @author     HRCT
 * @version    v1.0
 * @date       2016-09-27
 */
 
 #include "Board.h"
//中断优先级初始化
void NVIC_Config(void)
{
		NVIC_InitTypeDef NVIC_InitStructure; 
	 
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	 
	 //定时器中断优先级配置
		
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
		
		//定时中断查询按键优先级配置
		NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn; 
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

//		//按键外部中断优先级配置
//		NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn; 
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//		NVIC_Init(&NVIC_InitStructure);
   	//2401 IRQ    
		NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;  //打开 EXTI3的全局中断 
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢占优先级为 0 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;    //响应优先级为 0 
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     //使能 
		NVIC_Init(&NVIC_InitStructure);

}



void Motor_Init()
{
    delay_ms(100);
    CAN_RoboModule_DRV_Reset(0,1);                      //对0组1号驱动器进行复位
    CAN_RoboModule_DRV_Reset(0,2);                      //对0组2号驱动器进行复位
	  CAN_RoboModule_DRV_Reset(0,3);                      //对0组3号驱动器进行复位
    CAN_RoboModule_DRV_Reset(0,4);                      //对0组4号驱动器进行复位	 
    delay_ms(1000);                                     //发送复位指令后的延时必须要有，等待驱动器复位完毕。
    CAN_RoboModule_DRV_Config(0,1,100,0);               //配置为1s传回一次数据
    CAN_RoboModule_DRV_Config(0,2,100,0);               //配置为1s传回一次数据
    CAN_RoboModule_DRV_Config(0,3,100,0);               //配置为1s传回一次数据
    CAN_RoboModule_DRV_Config(0,4,100,0);               //配置为1s传回一次数据	 
    delay_ms(10);
    CAN_RoboModule_DRV_Mode_Choice(0,1,Current_Velocity_Mode);  //选择进入开环模式
    CAN_RoboModule_DRV_Mode_Choice(0,2,Current_Velocity_Mode);  //选择进入开环模式
    CAN_RoboModule_DRV_Mode_Choice(0,3,Current_Velocity_Mode);  //选择进入开环模式
    CAN_RoboModule_DRV_Mode_Choice(0,4,Current_Velocity_Mode);  //选择进入开环模式	 
    delay_ms(500);                                      //发送模式选择指令后，要等待驱动器进入模式就绪。所以延时也不可以去掉。	 

}

void Sys_Init(void)
{

		//		Quadrature_decode_TIM1_Init();			//正交解码初始化


		Quadrature_decode_TIM8_Init();
		Quadrature_decode_TIM4_Init();

		//  PWMout_TIM2_TIM3_Init(0, 0, 0, 0, 0, 0);						//PWM输出初始化

		TIM1_GPIO_Config();
		TIM1_Mode_Config();


		USART1_Init(115200);//串口初始化
		UART4_Init(115200);
		ADC_Mode_Init();						//电流采集初始化

		//  KEY_EXTI_Init();							//按键中断初始化

		Interrupt_TIM6_Init();					//定时器中断初始化
		Interrupt_TIM7_Init();					//按键定时查询中断初始化
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


 
 
