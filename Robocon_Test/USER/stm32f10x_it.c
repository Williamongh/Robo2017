/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "stm32f10x_it.h"
volatile u8 count = 0;
//u32 count1;
//wheel_speed speed_get = {0};
uint8_t receive_flag=0;
uint8_t rxbuf2401[4];
uint8_t stopFlag=0, startFlag=0;
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */

motion_status motion; 

uint32_t it_count=0;

float adc=0;

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles TIM2 interrupt request.
  * @param  None
  * @retval None
  */
void TIM6_IRQHandler(void)
{
		if ( TIM_GetITStatus(TIM6 , TIM_IT_Update) != RESET ) 
		{	
				TIM_ClearITPendingBit(TIM6 , TIM_FLAG_Update);			
				it_count++;
				count++;
		//	adc=ADC_Get();
			
	//		if(it_count%100==0)
	//			{
	//					GPIOB->ODR ^= GPIO_Pin_0;
	//			}	 
			
			if(it_count>=5000)
			{
					//5ms执行一次
					if(!(count%5))						
					{
//						speed_get.v1=2000;
//						speed_get.v2=2000;
//						speed_get.v3=2000;
//						speed_get.v4=2000;
//						CAN_RoboModule_DRV_Current_Velocity_Mode(0,1,10000,speed_get.v1);
//						CAN_RoboModule_DRV_Current_Velocity_Mode(0,2,10000,speed_get.v2);
//						CAN_RoboModule_DRV_Current_Velocity_Mode(0,3,10000,speed_get.v3);
//						CAN_RoboModule_DRV_Current_Velocity_Mode(0,4,10000,speed_get.v4);			
							if(it_count > 10000 && receive_flag)
							{

									Motor_Cal();
									Motor_Run();

							}						
					}
					
					//10ms执行一次
					//PWM速度控制
					if(!(count%10))						
					{
			//			Motor1_Z(0);
			//			Motor1_F(0);
			//			
			//			Motor2_Z(0);
			//			Motor2_F(0);
			//			
			//			Motor3_Z(0);
			//			Motor3_F(0);
						//speed_set=3;
			//			motion_mode = 1;
						if(it_count > 10000 && receive_flag && startFlag)
						{
								
			//					Motor_Cal();
			//					Motor_Run();

						}
						else
						{
								Motor_Stop();
						}
					}
					
					//50ms执行一次
					//编码器测速 位置发送
					if(!(count%50))						
					{
			//				Encode[0] = TIM1->CNT;
			//				Encode[1] = TIM8->CNT;
			//				Encode[2] = TIM4->CNT;	
						
			//			TIM1->CNT = 0;
			//			TIM8->CNT = 0;
			//			TIM4->CNT = 0;
						
					//  printf("X_Angle：%.2f\r\nY_Angle：%.2f\r\nZ_Angle：%.2f\r\nX：%.2f\r\nY：%.2f\r\nZ_w：%.2f\r\n",xangle,yangle,zangle,pos_x,pos_y,w_z);
					}
					
					//计数清零
					if(count >= 100)
						count &= 0;
					
				}

		}		 	
}

void UART4_IRQHandler(void)
{
	static uint8_t ch;
	static union
  {
	 uint8_t data[4];
	 float para_ready;
  }para_get;
	static uint8_t count=0;
	static uint8_t i=0;

	if(USART_GetITStatus(UART4, USART_IT_RXNE)==SET)   
	{
		USART_ClearITPendingBit( UART4,USART_IT_RXNE);
		ch=USART_ReceiveData(UART4);
		 switch(count)
		 {
			 case 0:
				 if(ch=='E')
				 {
					 count++;
					 i=0;
				 }
				 else
					 count=0;
				 break;			 			 
			 case 1:
				 para_get.data[3-i]=ch;
			   i++;
			   if(i>=4)
				 {
					 i=0;
					 count++;
				 }
				 break;
				 
			 case 2:
				 if(ch=='S')
				 {
						speed_set=para_get.para_ready;
				 }
				 else if(ch=='D')
				 {
				    direction_set=para_get.para_ready;
				 }
					 count=0;
				 break;

			 
			 default:
				 count=0;
			   break;		 
		 }		 	 
	 }
} 

void USART1_IRQHandler(void)
{	 
	static uint8_t ch;
	static union
  {
	 uint8_t data[24];
	 float ActVal[6];
  }posture;
	static uint8_t count=0;
	static uint8_t i=0;

	
	if (USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET)//注意！不能使用if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)来判断
  {
			  USART_ClearFlag(USART1, USART_FLAG_ORE);
        USART_ReceiveData(USART1);
				receive_flag=0;
				count=0;
				
  }	
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE)==SET)   
	{
		USART_ClearITPendingBit( USART1,USART_IT_RXNE);
		ch=USART_ReceiveData(USART1);
		 switch(count)
		 {
			 case 0:
				 if(ch==0x0d)
				 {
					 count++;
					 receive_flag=1;
				 }
				 else
					 count=0;
				 break;
				 
			 case 1:
				 if(ch==0x0a)
				 {
					 i=0;
					 count++;
				 }
				 else if(ch==0x0d);
				 else
					 count=0;
				 break;
				 
			 case 2:
				 posture.data[i]=ch;
			   i++;
			   if(i>=24)
				 {
					 i=0;
					 count++;
				 }
				 break;
				 
			 case 3:
				 if(ch==0x0a)
					 count++;
				 else
					 count=0;
				 break;
				 
			 case 4:
				 if(ch==0x0d)
				 {
  				 motion.zangle = posture.ActVal[0];
	  		   motion.xangle = posture.ActVal[1];
		  	   motion.yangle = posture.ActVal[2];
			     motion.pos_x  = posture.ActVal[3];
			     motion.pos_y  = posture.ActVal[4];
			     motion.w_z    = posture.ActVal[5];
//					 timede=run;
//					 run=0; 用于计时
				 }
			   count=0;
				 break;
			 
			 default:
				 count=0;
			   break;	
		 }
	 }
} 

//void USB_LP_CAN1_RX0_IRQHandler(void)
//{
//		CanRxMsg RxMessage; 			    //接收缓冲区  
//		
//		CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
//		/* 比较是否是发送的数据和ID */ 
//		if((RxMessage.StdId==0x1314) && (RxMessage.IDE==CAN_ID_STD)
//					&& (RxMessage.DLC==2) && ((RxMessage.Data[1]|RxMessage.Data[0]<<8)==0xABCD))
//		{


//		}
//		else
//		{

//		}
//}

void TIM7_IRQHandler(void)
{
	if ( TIM_GetITStatus(TIM7 , TIM_IT_Update) != RESET ) 
	{	
		TIM_ClearITPendingBit(TIM7 , TIM_FLAG_Update);
		Key_IRQHandler();
		
	}
}


void EXTI2_IRQHandler()    //外部中断 3 中断函数 
{ 
	if(EXTI_GetITStatus(EXTI_Line2)==SET) 
	{ 
		uint8_t state;

		
		EXTI_ClearITPendingBit(EXTI_Line2);//清除 EXTI 线路挂起位

		NRF_CE_LOW();  	 //进入待机状态
		/*读取status寄存器的值  */               
		state=SPI_NRF_ReadReg(STATUS);
		 
		/* 清除中断标志*/      
		SPI_NRF_WriteReg(NRF_WRITE_REG+STATUS,state);

		/*判断是否接收到数据*/
		if(state&RX_DR)                                 //接收到数据
		{
			SPI_NRF_ReadBuf(RD_RX_PLOAD,rxbuf2401,RX_PLOAD_WIDTH);//读取数据
			SPI_NRF_WriteReg(FLUSH_RX,NOP);          //清除RX FIFO寄存器
		}
		else; 	
		if((rxbuf2401[0]==0x22 || rxbuf2401[0]==0x22 || rxbuf2401[0]==0x22 || rxbuf2401[0]==0x22))
		{
				stopFlag = 1;
				startFlag = 0;
		}
		if((rxbuf2401[0]==0x11 || rxbuf2401[0]==0x11 || rxbuf2401[0]==0x11 || rxbuf2401[0]==0x11))
		{
				stopFlag = 0;
				startFlag = 1;
		}
		NRF_CE_HIGH();
	}   
}
/**
  * @brief  This function handles EXTI interrupt request.
  * @param  None
  * @retval None
  */

void EXTI15_10_IRQHandler(void)
{
//	if(EXTI_GetITStatus(EXTI_Line11) != RESET) //确保是否产生了EXTI Line中断
//	{//PD11 Down
//		EXTI_ClearITPendingBit(EXTI_Line11);     //清除中断标志位

//	}  
//	
//	if(EXTI_GetITStatus(EXTI_Line12) != RESET) //确保是否产生了EXTI Line中断
//	{//PD12 Right
//		EXTI_ClearITPendingBit(EXTI_Line12);     //清除中断标志位

//	}  
//	
//	if(EXTI_GetITStatus(EXTI_Line13) != RESET) //确保是否产生了EXTI Line中断
//	{//PD13 Left
//		EXTI_ClearITPendingBit(EXTI_Line13);     //清除中断标志位

//	}  
//	
//	if(EXTI_GetITStatus(EXTI_Line14) != RESET) //确保是否产生了EXTI Line中断
//	{//PD14 Set
//		EXTI_ClearITPendingBit(EXTI_Line14);     //清除中断标志位

//	}  
//	
//	if(EXTI_GetITStatus(EXTI_Line15) != RESET) //确保是否产生了EXTI Line中断
//	{//PD15 Up
//		EXTI_ClearITPendingBit(EXTI_Line15);     //清除中断标志位

//	}  	
}



/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
