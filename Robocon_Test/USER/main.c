/*!
 * @file       main.c
 * @brief      Robocon测试小车主程序
 * @author     HRCT
 * @version    v1.0
 * @date       2016-09-27
 */
 
 
 //由于核心板使用内部时钟，故屏蔽掉SystemInit
 
 #include  "include.h"
  float speed_set=0;
 float direction_set=0;
 uint32_t a,b,c=0;
 
 void LED_GPIO_Config(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启LED的外设时钟*/
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE); 

		/*选择要控制的GPIOB引脚*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	

		/*设置引脚模式为通用推挽输出*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*调用库函数，初始化GPIOB0*/
		GPIO_Init(GPIOB, &GPIO_InitStructure);	
		


		/* 关闭所有led灯	*/
		GPIO_SetBits(GPIOB, GPIO_Pin_0);

}
 
 int main()
 {
	 volatile float temp;
	 

	 RCC_Init();
	 
	 Robocon_PhoTriRacing_Board_Init();
	 
	 Robocon_NVIC_Init();
	 
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5 , ENABLE);	 		
	 LED_GPIO_Config();
	 setOrigin(0,0); 
				 
	 while(1)
	 {

				
//printf("X_Angle：%.2f\r\nY_Angle：%.2f\r\nZ_Angle：%.2f\r\nX：%.2f\r\nY：%.2f\r\nZ_w：%.2f\r\n",motion.xangle,motion.yangle,motion.zangle,motion.pos_x,motion.pos_y,motion.w_z);

	 } 
		
 }
 











