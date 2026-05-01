#include "PID.h"
#include <math.H>
/*有关变量*/
int All_clear=0;												//PID清零位
PID PID_Groud;
/*****************************************
* @功能介绍： PID数据初始化
* @函数参数：	无
* @返回值：		无
******************************************/

void PID_Init(void)
{
		PID_Groud.Kp=2.0f;  		//比例
		PID_Groud.Ki=0; 				//积分
		PID_Groud.Kd=1.0f;   		//微分
}


/*****************************************
* @功能介绍： 	陀螺仪PID计算
* @函数参数1：	陀螺仪的现在值
* @函数参数2：	陀螺仪的目标值
* @返回值：		  无
******************************************/
void Gyro_PID(float yaw_value,float target_yaw)//位置式PID
{
	
	if(yaw_value>180)
	yaw_value=yaw_value-360.0000;
	static float error,last_error,delta_error,errorInt;
	last_error=error;
	error=target_yaw-yaw_value;
	delta_error=error-last_error;
	
	if(fabs(error)<3.0f)
	{
		errorInt+=error;
	}
	else
	{
		errorInt = 0;
	}
	errorInt = fminf(fmaxf(errorInt, -30.0f), 30.0f);
	PID_Groud.out=PID_Groud.Kp*error + PID_Groud.Ki*errorInt + PID_Groud.Kd*delta_error ;
	PID_Groud.out = fminf(fmaxf(PID_Groud.out, -20.0f), 20.0f);
	
//	 if(All_clear == 1)
//	 {
//		 error=0;last_error=0;delta_error=0;
//		 All_clear=0;
//	 }
}

