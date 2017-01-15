#include "motorPID.h"

//������ƵĹ��̣�������ѹ�仯���������淢���仯�������Եأ�����������ת�أ����Եأ���ת�ؾ������ٶȣ����Եأ��������ٶ���֮�ı�
//							 �������ջ����ƣ��������Ǵ�����Ϊ����ѹ�仯�������ٶ���ֵ���ٶ���б�������ģ����ٶ��ǽ�Ծ�ģ�����Ϊ���ٶȱ仯���̣������ǲ���ģ���
//							ʵ���ϣ����ſ����ٶ���ֵ�����ٶ��𽥱�С��ԭ�����ٶ����ӷ���綯�����ӣ����������С���������������ת��
//							�ʲ��õ���˫�ջ������Ƶ���ֵ�㶨����������ٶȼ��١�

float Vel_Set;

float Vel_Read()			//�õ���ǰ�ٶ�
{
		static uint16_t encode, encode_last;
		float K=1.0f , Vel_Get;
	
		encode_last = encode;			//��һ�α�����ֵ
		encode = TIM8->CNT;		  	//���α�����ֵ
		K= 1;										//����ϵ�������ڻ���Ϊ������ʵ���ٶȣ�Ϊ�����������ֻ����PIDҲ�ɡ�
		Vel_Get = (encode - encode_last) * K;			//�����ٶ�
	
		return Vel_Get;					//����V_PID������
}

float V_PID(float Vel_Set, float Vel_Get)			//�ٶȻ�PID ����ʽ �⻷
{
		static float V_Error, V_ErrorLast, Vel_Output, K = 1;	
	  float V_ErrorLast2, Vel_deltaOutput, I_Set;

	
		V_ErrorLast2 = V_ErrorLast; 	 //���ϴε����
		V_ErrorLast = V_Error;				 //�ϴε����
		V_Error = Vel_Set - Vel_Get;	 //�������
	
		Vel_deltaOutput = V_P * (V_Error - V_ErrorLast)
												+ V_I * V_Error
													+ V_D * (V_Error - V_ErrorLast*2 + V_ErrorLast2) ;
	

		Vel_Output += Vel_deltaOutput ; 		//Ϊ�ﵽָ���ٶ�����Ҫ��ת�أ����ٶȣ� 
		
		I_Set = Vel_Output * K;   	  			//����һ����ϵ������Ϊ������������(�������趨ֵ������������ֵ)��ֻ����PIDҲ�ɡ�
	
		if( fabs(I_Set) > IMAX )						//��Ҫ�����Ƶ���Ϊ������������ ��ֹ�ջٵ��
		{
				I_Set = I_Set / fabs(I_Set) * IMAX;
		}
		
		return I_Set;
}

int16_t I_PID(float I_Set, float I_Get)			//������PID λ��ʽ �ڻ�
{
		static float I_Error, I_ErrorSum;
		float I_ErrorLast;
		int16_t I_Output;
		
	  I_ErrorLast = I_Error;					
		I_Error = I_Set - I_Get ;
		I_ErrorSum += I_Error;	
		I_Output = I_P*I_Error + I_I*I_ErrorSum + I_D*(I_Error-I_ErrorLast);  //I_Output�������ΪPWM�ĸ�ֵ���൱��ͨ�����ڵ�ѹ
																																					//ʹ�������ֲ��䣬�������˼��ٶ�
		//ע�⣡�ڴ��޷���ԭ���ǣ� CCR1<2��CCR1>��999-2��ʱ����������� ����CCR1�ķ�ΧӦΪ3-996 ����֪Ϊ�Σ�
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
