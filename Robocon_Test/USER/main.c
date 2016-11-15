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
 

 
 int main()
 {

	 

	 RCC_Init();
	 
	 Robocon_PhoTriRacing_Board_Init();
	 
	 Robocon_NVIC_Init();
	 
	 DAC1_Init();
	 
	 setOrigin(0,0); 
			 
	 while(1)
	 {


//printf("X_Angle：%.2f\r\nY_Angle：%.2f\r\nZ_Angle：%.2f\r\nX：%.2f\r\nY：%.2f\r\nZ_w：%.2f\r\n",motion.xangle,motion.yangle,motion.zangle,motion.pos_x,motion.pos_y,motion.w_z);

	 } 
		
 }
 











