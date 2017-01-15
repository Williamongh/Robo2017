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
int16 var[6];    //上位机 虚拟示波器需要配置成 波形数为6，数据类型为 uint8_t

uint16 var1,var2,var3,var4,var5,var6;
uint8_t receive_buff[4];//接收缓冲

 int main()
 {

		Sys_Init();


//	 DAC1_Set_Vol(2.55);
//	 DAC2_Set_Vol(0.75);
//	 

//	 TIM1->CCR1=5 ;
//	 TIM1->CCR2=500;    

	 ;
//    delay_ms(100);
//    CAN_RoboModule_DRV_Reset(0,1);                      //对0组1号驱动器进行复位
//    delay_ms(1000);                                     //发送复位指令后的延时必须要有，等待驱动器复位完毕。
//    CAN_RoboModule_DRV_Config(0,1,100,0);               //配置为1s传回一次数据
//    delay_ms(1);
//    CAN_RoboModule_DRV_Mode_Choice(0,1,OpenLoop_Mode);  //选择进入开环模式
//    delay_ms(500);                                      //发送模式选择指令后，要等待驱动器进入模式就绪。所以延时也不可以去掉。

//    CAN_RoboModule_DRV_OpenLoop_Mode(0,1,0);
//    delay_ms(500);
//    CAN_RoboModule_DRV_OpenLoop_Mode(0,1,500);
//    delay_ms(500);
//    CAN_RoboModule_DRV_OpenLoop_Mode(0,1,1000);
//    delay_ms(10000);
//    CAN_RoboModule_DRV_OpenLoop_Mode(0,1,500);
//    delay_ms(500);
//    CAN_RoboModule_DRV_OpenLoop_Mode(0,1,0);
//    delay_ms(500);
//    
//    CAN_RoboModule_DRV_Reset(0,1);

//Site_t site[3] = {{10,20},{101,21},{12,122}};   //3个点，坐标分别是  {10,20},{11,21},{12,22}
//LCD_points(site,3, RED);			
//Site_t site2 = {5,80};   //x = 10 ,y = 20
//LCD_str(site2,"www.vcan123.com", BLUE,RED);			
//LCD_rectangle((Site_t){0,0}, (Size_t){10,10}, RED);

//LCD_cross((Site_t){50,50},30,GREEN);	

    while(1)
		{			
          var_display(VAR_MAX);
          deal_key_event();
			
//                  var[3]=100;
//                  var[2]=200;
//                  var[1]=300;//ad[i].ADFilted;
//                  var[0]=400;
//			            vcan_sendware(var, sizeof(var));
				//		NRF_Rx_Dat(receive_buff);

		}	
		
		
 }
 











