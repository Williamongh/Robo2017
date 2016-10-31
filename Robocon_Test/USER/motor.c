#include "include.h"

wheel_speed speed_get = {0};
uint8_t motion_mode = 0;

void Motor_Cal()
{
		if(motion_mode==0)
		{
			//	speed_get = basicLine(speed_set*100, direction_set-180, 0,0);
		}
		else if (motion_mode == 1)
		{
				speed_get = point_to_point(150, -100, 100, motion.pos_x, motion.pos_y, 0, motion.zangle);
			
//				speed_get = closeLoopLine(300, 90,
//	                     0, motion.zangle,
//	                      motion.pos_x, motion.pos_y)	;		
				
		}
		if(speed_get.v1>1000)
			speed_get.v1=1000;
		if(speed_get.v2>1000)
			speed_get.v2=1000;
		if(speed_get.v3>1000)
			speed_get.v1=1000;
}

void Motor_Run()
{
	if(!speed_get.status)
	{
		if(speed_get.v1>=0)
		{
				Motor1_Z(speed_get.v1);
				Motor1_F(0);
		}
		else if(speed_get.v1<0)
		{
				Motor1_Z(0);			
				Motor1_F(-speed_get.v1);
		}	

		if(speed_get.v2>=0)
		{
				Motor2_Z(speed_get.v2);
				Motor2_F(0);
		}
		else if(speed_get.v2<0)
		{
				Motor2_Z(0);			
				Motor2_F(-speed_get.v2);
		}			

		if(speed_get.v3>=0)
		{
				Motor3_Z(speed_get.v3);
				Motor3_F(0);
		}
		else if(speed_get.v3<0)
		{
				Motor3_Z(0);
				Motor3_F(-speed_get.v3);
		}					
	}
	else
	{
				Motor1_Z(0);
				Motor1_F(0);				
				Motor2_Z(0);
				Motor2_F(0);				
				Motor3_Z(0);
				Motor3_F(0);	
	}
}
