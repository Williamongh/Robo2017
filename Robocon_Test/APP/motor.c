#include "motor.h"



wheel_speed speed_get = {0};
uint8_t motion_mode = 0;

/**
* @brief  从一点到另一点直线
* @param  vel:车的速度（正数 Vel>0）
* @param  end_posx：目标点x坐标
* @param  end_posy：目标点y坐标
* @param  ex_Ang：参考值
* @param  act_Ang：实际值
* @retval wheel_speed:底盘的速度分配
          SUCCESS:成功到达终点
          FAILURE:还未到达终点
* @author ACTION
*/
//wheel_speed point_to_point(float vel,
//	float end_posx, float end_posy,
//	float pos_x, float pos_y,
//	float ex_Ang, float act_Ang)
void Motor_Cal()
{
	float xx=0,yy=0;
//		if(motion_mode==0)
//		{
			//	speed_get = basicLine(1200, 45, 700,motion.zangle);
//		}
//		else if (motion_mode == 1)
//		{
////				xx=-1000/1.414-1000/1.414;//全局定位坐标系的x y 方向
////				yy=-1000/1.414+1000/1.414;	//
				speed_get = point_to_point(1000, 1000, 1000, motion.pos_x, motion.pos_y, 0, motion.zangle);
			
//				speed_get = closeLoopLine(300, 90,
//	                     0, motion.zangle,
//	                      motion.pos_x, motion.pos_y)	;		
				
//		}
//		if(speed_get.v1>1000)
//			speed_get.v1=1000;
//		if(speed_get.v2>1000)
//			speed_get.v2=1000;
//		if(speed_get.v3>1000)
//			speed_get.v3=1000;
//		if(speed_get.v4>1000)
//			speed_get.v4=1000;
		if(speed_get.status == SUCCESS || stopFlag || !startFlag)
		{
				speed_get.v1=0;	
				speed_get.v2=0;	
				speed_get.v3=0;	
				speed_get.v4=0;				
		}
}

void Motor_Run()
{
		if(!speed_get.status)
		{
				CAN_RoboModule_DRV_Current_Velocity_Mode(0,1,10000,speed_get.v1);
				CAN_RoboModule_DRV_Current_Velocity_Mode(0,2,10000,speed_get.v2);
				CAN_RoboModule_DRV_Current_Velocity_Mode(0,3,10000,speed_get.v3);
				CAN_RoboModule_DRV_Current_Velocity_Mode(0,4,10000,speed_get.v4);		
		}
}

void Motor_Stop()
{
		if(stopFlag || !startFlag)
		{
				speed_get.v1=0;	
				speed_get.v2=0;	
				speed_get.v3=0;	
				speed_get.v4=0;			
				CAN_RoboModule_DRV_Current_Velocity_Mode(0,1,10000,speed_get.v1);
				CAN_RoboModule_DRV_Current_Velocity_Mode(0,2,10000,speed_get.v2);
				CAN_RoboModule_DRV_Current_Velocity_Mode(0,3,10000,speed_get.v3);
				CAN_RoboModule_DRV_Current_Velocity_Mode(0,4,10000,speed_get.v4);					
		}
}
