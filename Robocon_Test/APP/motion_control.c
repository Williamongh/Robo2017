/**
******************************************************************************
* @file    Action_motion_control.c
* @author  ACTION
* @version V1.0
* @date    2016.4.5
* @brief   motion control
*/
/* Includes -------------------------------------------------------------------*/
#include "motion_control.h"

/* Private  typedef -----------------------------------------------------------*/
/* Private  define ------------------------------------------------------------*/
#define Kp_ANG       10.0f    //�Ƕȱջ���PID���� 
#define Ki_ANG       0.0f
#define Kd_ANG       0.0f

#define Kp_POS       1.0f    //λ�ñջ���PID����
#define Ki_POS       0.0f
#define Kd_POS       0.0f

#define Kp_END       1.0f    //�յ�ջ���PID����
#define Ki_END		   0.0f
#define Kd_END		   0.0f

#define PID_ANG_OUT_MAX     1000     //�Ƕȱջ���������ֵ
#define PID_POS_OUT_MAX       45     //λ�ñջ���������ֵ

#define END_ERR_ALLOW       100
#define END_VEL_ALLOW       100

#define ACC_MAX   100.0f  //�������������

#define dt 0.005f            // �������� 5ms
/* Private  macro -------------------------------------------------------------*/
#define ANGLE_TO_RAD(x) (x)/180.0f*3.14159f
#define RAD_TO_ANGLE(x) (x)/3.14159f*180.0f
/* Private  variables ---------------------------------------------------------*/
static float origin_cll_x=0;   //λ�ñջ��͵㵽������
static float origin_cll_y=0;
static float err_pos_sum = 0, err_ang_sum = 0;
static float err_pos_last = 0, err_ang_last = 0;
/* Extern   variables ---------------------------------------------------------*/
/* Extern   function prototypes -----------------------------------------------*/
/* Private  function prototypes -----------------------------------------------*/
/* Private  functions ---------------------------------------------------------*/
/* Exported function prototypes -----------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/
/**
* @brief  ����ֱ�߼�����ת
* @param  Vel:���ĺ��ٶȣ����� Vel>0��
* @param  ward:�����н�����
                -180��+180
* @param  Rotate:���������ת�ٶȣ�����ʱ���� ����ͼ��
* @param  selfAngle:���������̬�Ƕ�
* @retval wheel_speed:����Ӧ�ôﵽ���ٶ�
* @author ACTION
*/
wheel_speed basicLine(float vel, float ward, float Rotate,float selfAngle)
{
  wheel_speed speed_out;
	float vx,vy;
  /* ���㵱������ת�����Ӧ�õ�ǰ������ */
  ward = ward - selfAngle; 

  /* ����ϵת�� */
//  ward=-ward;

  /* �ֽ����������ֵ��ٶ� */
	vx=vel*(float)cos(ANGLE_TO_RAD(ward));
	vy=vel*(float)cos(ANGLE_TO_RAD(90-ward));
  speed_out.v1 = vy - Rotate;
  speed_out.v3 = vy + Rotate;
  speed_out.v2 = vx - Rotate;
  speed_out.v4 = vx + Rotate;
	
  speed_out.status = FAILURE;
  return speed_out;
}

/**
* @brief  ֱ�߱ջ���ԭ������
* @param  pos_x:��������
* @param  pos_y:��������
* @retval none
* @author ACTION
*/
void setOrigin(float pos_x, float pos_y)
{
	origin_cll_x = pos_x;
	origin_cll_y = pos_y;

	err_ang_sum = 0;
	err_pos_sum = 0;

	err_pos_last = 0;
	err_ang_last = 0;
}
/**
* @brief  �㵽ֱ�߾������
* @param  ward:ֱ�߷���
* @param  line_posx��ֱ���ϵ�x����
* @param  line_posy��ֱ���ϵ�y����
* @param  posx���ο�ֵ
* @param  posy��ʵ��ֵ
* @retval err_pos�� ����
* @author ACTION
*/
float distanceCal(float ward,
	              float line_posx, float line_posy,
	              float posx,      float posy)
{
	float err_pos;
	float dir_x, dir_y;//��������
	float act_x, act_y;
	/* ����λ����� */
	ward = ward + 90;
	if (ward > 180)
		ward = ward - 360;
	if (ward < -180)
		ward = ward + 360;
	ward = (float)ANGLE_TO_RAD(ward);

	/* �㵽ֱ�߾�����㣬���������� */
	dir_x = (float)cos(ward);
	dir_y = (float)sin(ward);
	act_x = line_posx - posx;
	act_y = line_posy - posy;

	err_pos = dir_x*act_x + dir_y*act_y;

	return err_pos;
}
/**
* @brief  ֱ�߱ջ�
* @param  vel:�����ٶȣ����� Vel>0��
* @param  ward��ǰ������
          -180��+180
* @param  ex_Ang���ο�ֵ
* @param  act_Ang��ʵ��ֵ
* @param  pos_x:��������
* @param  pos_y:��������
* @retval wheel_speed:����Ӧ�ôﵽ���ٶ�
* @author ACTION
*/
wheel_speed closeLoopLine(float vel,    float ward,
	                      float ex_Ang, float act_Ang,
	                      float now_x,  float now_y)
{
	float err_pos, err_pos_v;
	float err_ang, err_ang_v;

	float PID_ang_out;
	float PID_pos_out;

	float pos_x,pos_y;
	wheel_speed speed_out;
	pos_x = (now_y + now_x) * 0.70710678;
	pos_y = (now_y - now_x) * 0.70710678;
	err_pos = distanceCal(ward,origin_cll_x,origin_cll_y,pos_x,pos_y);

	/* ����λ��PID�������� */
	err_pos_sum = err_pos_sum + err_pos;
	err_pos_v = err_pos - err_pos_last;
	err_pos_last = err_pos;
	PID_pos_out = Kp_POS*err_pos + Ki_POS*err_pos_sum + Kd_POS*err_pos_v;
	/* ���������� */
	if (PID_pos_out > PID_POS_OUT_MAX)
	{
		PID_pos_out = PID_POS_OUT_MAX;
	}
	else if (PID_pos_out < -PID_POS_OUT_MAX)
	{
		PID_pos_out = -PID_POS_OUT_MAX;
	}

	/* ����Ƕ�PID�������� */
	err_ang = -ex_Ang + act_Ang;
	err_ang_sum = err_ang_sum + err_ang;
	err_ang_v = err_ang - err_ang_last;
	err_ang_last = err_ang;
	PID_ang_out = Kp_ANG*err_ang + Ki_ANG*err_ang_sum + Kd_ANG*err_ang_v;
	if (PID_ang_out > PID_ANG_OUT_MAX)
	{
		PID_ang_out = PID_ANG_OUT_MAX;
	}
	else if (PID_ang_out < -PID_ANG_OUT_MAX)
	{
		PID_ang_out = -PID_ANG_OUT_MAX;
	}
	
	speed_out=basicLine(vel / (float)cos(ANGLE_TO_RAD(PID_pos_out)), ward + PID_pos_out, PID_ang_out, act_Ang);
	speed_out.status = FAILURE;
	return speed_out;
}

/**
* @brief  ��һ�㵽��һ��ֱ��
* @param  vel:�����ٶȣ����� Vel>0��
* @param  end_posx��Ŀ���x����
* @param  end_posy��Ŀ���y����
* @param  ex_Ang���ο�ֵ
* @param  act_Ang��ʵ��ֵ
* @retval wheel_speed:���̵��ٶȷ���
          SUCCESS:�ɹ������յ�
          FAILURE:��δ�����յ�
* @author ACTION
*/

wheel_speed point_to_point(float vel,
	float end_posx, float end_posy,
	float now_x, float now_y,
	float ex_Ang, float act_Ang)
{
	wheel_speed speed_out;
	float reduce_distance=0;
	static float distance;  //���پ��룬��ǰ����
	float ward;

	float  act_vel, ex_vel, err, err_vel;
	static float err_sum = 0, last_err = 0;
	static float last_distance = 0;
	float PID_out;

	static uint8_t flag = 0;
	static uint8_t flag_start = 0;

	float pos_x,pos_y;//,end_posx,end_posy;
	
	pos_x = (now_y + now_x) * 0.70710678;
	pos_y = (now_y - now_x) * 0.70710678;
	
	/* ֱ�߷������ */
	ward = RAD_TO_ANGLE((float)atan2(end_posy - pos_y, end_posx - pos_x));
	/* ������һ�εľ���ֵ*/
	last_distance = distance;
	/* ��ǰ������� */
	distance = distanceCal(ward-90 , end_posx, end_posy, pos_x, pos_y);
	
	if (flag_start)
	{
		/* ���̿����ٶȼ��� */
		act_vel = (-distance + last_distance)*1.0f/dt;
		/* ���پ������ */
		reduce_distance = (float) 0.5*act_vel*act_vel / ACC_MAX;


	}
	else
	{
		flag_start = 1;
		reduce_distance = 0;

	}

	/* �ж��յ�ջ��Ƿ���� */

    if(!flag)
		if (fabs(distance) <= reduce_distance)
		{
			flag = 1;
			err_sum = 0;
			last_err = 0;
		}
	if (flag)
	{
		/* �������ٶ� */
		ex_vel= (float)sqrt(2 * fabs(distance)*ACC_MAX)*distance/ (float)fabs(distance);

		/* PID��������� */
		err = ex_vel - act_vel;
		err_sum = err_sum + err;
		err_vel = err - last_err;
		last_err = err;

		PID_out = Kp_END*err + Ki_END* err_sum + Kd_END*err_vel;
	
		ex_vel = ex_vel + PID_out;

    
//		/* �жϵ�ǰ״̬�Ƿ�����ͣ���� */		
//		if (fabs(distance) < END_ERR_ALLOW&&fabs(act_vel) < END_VEL_ALLOW)
//		{
//			speed_out.status = SUCCESS;	
//			flag = 0;
//			flag_start = 0;
//			speed_out.v1 = 0;
//			speed_out.v2 = 0;
//			speed_out.v3 = 0;
//			speed_out.v4 = 0;
//			return speed_out;
//		}

		/* ������ͣ���������� */
		speed_out.status = FAILURE;		
		speed_out = closeLoopLine(ex_vel, ward, ex_Ang, act_Ang, now_x, now_y);
		return speed_out;
	}
	/* δ������ٷ�Χ���������յ�ջ� */
	speed_out.status = FAILURE;
	speed_out = closeLoopLine(vel, ward, ex_Ang, act_Ang, now_x, now_y);
	return speed_out;
}
/************************ (C) COPYRIGHT 2016 ACTION *****END OF FILE****/
