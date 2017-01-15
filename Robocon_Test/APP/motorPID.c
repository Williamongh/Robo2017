#include "motorPID.h"

//电机控制的过程：给定电压变化，电流跟随发生变化（非线性地），电流决定转矩（线性地），转矩决定加速度（线性地），最终速度随之改变
//							 以往单闭环控制，本质上是粗略认为，电压变化决定了速度终值，速度是斜坡上升的，加速度是阶跃的（即认为在速度变化过程，电流是不变的），
//							实际上，随着靠近速度终值，加速度逐渐变小，原因是速度增加反向电动势增加，电枢电流减小，而电枢电流决定转矩
//							故采用电流双闭环，控制电流值恒定，以理想加速度加速。

float Vel_Set;

float Vel_Read()			//得到当前速度
{
		static uint16_t encode, encode_last;
		float K=1.0f , Vel_Get;
	
		encode_last = encode;			//上一次编码器值
		encode = TIM8->CNT;		  	//本次编码器值
		K= 1;										//比例系数，用于换算为轮子真实线速度（为方便起见）。只调节PID也可。
		Vel_Get = (encode - encode_last) * K;			//轮子速度
	
		return Vel_Get;					//用于V_PID的输入
}

float V_PID(float Vel_Set, float Vel_Get)			//速度环PID 增量式 外环
{
		static float V_Error, V_ErrorLast, Vel_Output, K = 1;	
	  float V_ErrorLast2, Vel_deltaOutput, I_Set;

	
		V_ErrorLast2 = V_ErrorLast; 	 //上上次的误差
		V_ErrorLast = V_Error;				 //上次的误差
		V_Error = Vel_Set - Vel_Get;	 //本次误差
	
		Vel_deltaOutput = V_P * (V_Error - V_ErrorLast)
												+ V_I * V_Error
													+ V_D * (V_Error - V_ErrorLast*2 + V_ErrorLast2) ;
	

		Vel_Output += Vel_deltaOutput ; 		//为达到指定速度所需要的转矩（加速度） 
		
		I_Set = Vel_Output * K;   	  			//乘以一比例系数，作为电流环的输入(电流的设定值，即电流的终值)；只调节PID也可。
	
		if( fabs(I_Set) > IMAX )						//重要！限制电流为三倍电机额定电流 防止烧毁电机
		{
				I_Set = I_Set / fabs(I_Set) * IMAX;
		}
		
		return I_Set;
}

int16_t I_PID(float I_Set, float I_Get)			//电流环PID 位置式 内环
{
		static float I_Error, I_ErrorSum;
		float I_ErrorLast;
		int16_t I_Output;
		
	  I_ErrorLast = I_Error;					
		I_Error = I_Set - I_Get ;
		I_ErrorSum += I_Error;	
		I_Output = I_P*I_Error + I_I*I_ErrorSum + I_D*(I_Error-I_ErrorLast);  //I_Output的输出即为PWM的赋值，相当于通过调节电压
																																					//使电流保持不变，即给定了加速度
		//注意！在此限幅的原因是： CCR1<2或CCR1>（999-2）时输出不正常。 所以CCR1的范围应为3-996 （不知为何）
		if(I_Output > 996)
			 I_Output = 996;
		else if (I_Output>=0 && I_Output<3)
			 I_Output = 3;
		else if(I_Output < -996)
			 I_Output = -996;
		else if (I_Output<=0 && I_Output>-3)
			 I_Output = -3;
		
		return I_Output;
}

void Speed_Output(int16_t I_Output)
{

		if(I_Output > 0)
		{
				TIM1->CCR1 = I_Output ;
				TIM1->CCR2 = 0; 
		}
		
		else if(I_Output < 0)
		{
				TIM1->CCR1 = 0 ;
				TIM1->CCR2 = -I_Output; 
		}
		
}
