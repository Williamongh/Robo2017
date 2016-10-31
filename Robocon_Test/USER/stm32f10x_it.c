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

#include "include.h"
volatile u32 count = 0;
u32 count1;
uint8_t receive_flag=0;
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
void TIM5_IRQHandler(void)
{
	if ( TIM_GetITStatus(TIM5 , TIM_IT_Update) != RESET ) 
	{	
	
		
		it_count++;
		count++;
	
		if(it_count%100==0)
			{
					GPIOB->ODR ^= GPIO_Pin_0;
			}	 
		
		//5ms执行一次
		if(!(count%5))						
		{
			
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
			motion_mode = 1;
			if(it_count > 20000 && receive_flag)
			{

					Motor_Cal();
					Motor_Run();

			}
		}
		
		//50ms执行一次
		//编码器测速 位置发送
		if(!(count%50))						
		{
			Encode[0] = TIM1->CNT;
			Encode[1] = TIM8->CNT;
			Encode[2] = TIM4->CNT;
			
//			TIM1->CNT = 0;
//			TIM8->CNT = 0;
//			TIM4->CNT = 0;
			
		//  printf("X_Angle：%.2f\r\nY_Angle：%.2f\r\nZ_Angle：%.2f\r\nX：%.2f\r\nY：%.2f\r\nZ_w：%.2f\r\n",xangle,yangle,zangle,pos_x,pos_y,w_z);
		}
		
		//计数清零
		if(count >= 100)
			count &= 0;
		
		TIM_ClearITPendingBit(TIM5 , TIM_FLAG_Update);  		
	}		 	
}

void USART1_IRQHandler(void)
{
	static uint8_t ch;
	static union
  {
	 uint8_t data[4];
	 float para_ready;
  }para_get;
	static uint8_t count=0;
	static uint8_t i=0;

	if(USART_GetITStatus(USART1, USART_IT_RXNE)==SET)   
	{
		USART_ClearITPendingBit( USART1,USART_IT_RXNE);
		ch=USART_ReceiveData(USART1);
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

void UART4_IRQHandler(void)
{	 
	static uint8_t ch;
	static union
  {
	 uint8_t data[24];
	 float ActVal[6];
  }posture;
	static uint8_t count=0;
	static uint8_t i=0;

	
	if (USART_GetFlagStatus(UART4, USART_FLAG_ORE) != RESET)//注意！不能使用if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)来判断
  {
			  USART_ClearFlag(USART2, USART_FLAG_ORE);
        USART_ReceiveData(UART4);
				receive_flag=0;
				count=0;
				
  }	
	
	if(USART_GetITStatus(UART4, USART_IT_RXNE)==SET)   
	{
		USART_ClearITPendingBit( UART4,USART_IT_RXNE);
		ch=USART_ReceiveData(UART4);
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
			     motion.pos_x  = -posture.ActVal[3];
			     motion.pos_y  = -posture.ActVal[4];
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


/**
  * @brief  This function handles EXTI interrupt request.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) == SET) //确保是否产生了EXTI Line中断
	{
		//中断处理事件
		
		count1++;
		
		EXTI_ClearITPendingBit(EXTI_Line0);     //清除中断标志位
	}  
}
void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1) == RESET) //确保是否产生了EXTI Line中断
	{
		//中断处理事件
		count1 += 2;
		
		
		EXTI_ClearITPendingBit(EXTI_Line1);     //清除中断标志位
	}  
}
void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2) == RESET) //确保是否产生了EXTI Line中断
	{
		//中断处理事件
		
		
		
		EXTI_ClearITPendingBit(EXTI_Line2);     //清除中断标志位
	}  
}
void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line3) == RESET) //确保是否产生了EXTI Line中断
	{
		//中断处理事件
		
		
		
		EXTI_ClearITPendingBit(EXTI_Line3);     //清除中断标志位
	}  
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
