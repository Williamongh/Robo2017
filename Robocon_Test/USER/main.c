/*!
 * @file       main.c
 * @brief      Robocon����С��������
 * @author     HRCT
 * @version    v1.0
 * @date       2016-09-27
 */
 
 
 //���ں��İ�ʹ���ڲ�ʱ�ӣ������ε�SystemInit
 
 #include  "include.h"
 float speed_set=0;
 float direction_set=0;
 uint32_t a,b,c=0;
int16 var[6];    //��λ�� ����ʾ������Ҫ���ó� ������Ϊ6����������Ϊ uint8_t

uint16 var1,var2,var3,var4,var5,var6;
uint8_t receive_buff[4];//���ջ���

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
//    CAN_RoboModule_DRV_Reset(0,1);                      //��0��1�����������и�λ
//    delay_ms(1000);                                     //���͸�λָ������ʱ����Ҫ�У��ȴ���������λ��ϡ�
//    CAN_RoboModule_DRV_Config(0,1,100,0);               //����Ϊ1s����һ������
//    delay_ms(1);
//    CAN_RoboModule_DRV_Mode_Choice(0,1,OpenLoop_Mode);  //ѡ����뿪��ģʽ
//    delay_ms(500);                                      //����ģʽѡ��ָ���Ҫ�ȴ�����������ģʽ������������ʱҲ������ȥ����

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

//Site_t site[3] = {{10,20},{101,21},{12,122}};   //3���㣬����ֱ���  {10,20},{11,21},{12,22}
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
 











