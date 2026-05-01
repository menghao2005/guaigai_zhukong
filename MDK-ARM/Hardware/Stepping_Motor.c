/****************************************************************************
* @作者：				   YYX
* @创建日期：	   2024/7/10
* @最后更新日期：  20247/24
* @所属：				  常熟理工学院
* @功能：	         存放有关步进电机的函数
 ****************************************************************************/

#include "Stepping_Motor.h"
int left_standard=50;//高为慢50为秒一圈
int right_standard=50;
int Turn_Flag=0;
int flag=0;
int back_flag=0;
OC_Channel OC_channel[NumMotors];

/*****************************************
* @功能介绍： 步进电机直行初始化
* @函数参数：	无
* @返回值：		无
******************************************/
void Stepping_Motor_Go_Init(void)
{
	  back_flag=0;
    // 初始化每个轮子的PWM配置
    OC_channel[FrontLeft].OC_Channel_Duty = 50;
    OC_channel[FrontLeft].OC_Channel_Pulse = left_standard;
    OC_channel[FrontRight].OC_Channel_Duty = 50;
    OC_channel[FrontRight].OC_Channel_Pulse = right_standard;
    OC_channel[RearLeft].OC_Channel_Duty = 50;
    OC_channel[RearLeft].OC_Channel_Pulse = left_standard;
    OC_channel[RearRight].OC_Channel_Duty = 50;
    OC_channel[RearRight].OC_Channel_Pulse = right_standard;

    // 启动定时器通道的中断
    HAL_TIM_OC_Start_IT(&htim3, TIM_CHANNEL_1); // PA6 //输出比较中断
    HAL_TIM_OC_Start_IT(&htim3, TIM_CHANNEL_2); // PA7
    HAL_TIM_OC_Start_IT(&htim3, TIM_CHANNEL_3); // PB0
    HAL_TIM_OC_Start_IT(&htim3, TIM_CHANNEL_4); // PB1

    // 设置正反转控制线 直行

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET); //左前
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);   //右前
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET); //左后	
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);   //右后  
	
}

/*****************************************
* @功能介绍： 步进电机停止初始化
* @函数参数：	无
* @返回值：		无
******************************************/
void Stepping_Motor_Stopping_Init(void)
{
		HAL_TIM_OC_Stop_IT(&htim3,TIM_CHANNEL_1);
		HAL_TIM_OC_Stop_IT(&htim3,TIM_CHANNEL_2);
		HAL_TIM_OC_Stop_IT(&htim3,TIM_CHANNEL_3);
		HAL_TIM_OC_Stop_IT(&htim3,TIM_CHANNEL_4);  
}


/*****************************************
* @功能介绍： 步进电机左转初始化
* @函数参数：	无
* @返回值：		无
******************************************/
void Stepping_Motor_Left_Init(void)
{
    // 初始化每个轮子的PWM配置
    OC_channel[FrontLeft].OC_Channel_Duty = 90;
    OC_channel[FrontLeft].OC_Channel_Pulse = 90;
    OC_channel[FrontRight].OC_Channel_Duty = 90;
    OC_channel[FrontRight].OC_Channel_Pulse = 90;
    OC_channel[RearLeft].OC_Channel_Duty = 90;
    OC_channel[RearLeft].OC_Channel_Pulse = 90;
    OC_channel[RearRight].OC_Channel_Duty = 90;
    OC_channel[RearRight].OC_Channel_Pulse = 90;
		HAL_TIM_OC_Start_IT(&htim3,TIM_CHANNEL_1);
		HAL_TIM_OC_Start_IT(&htim3,TIM_CHANNEL_2);
    HAL_TIM_OC_Start_IT(&htim3, TIM_CHANNEL_3); // PB0
    HAL_TIM_OC_Start_IT(&htim3, TIM_CHANNEL_4); // PB1
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);          //右前前转
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);          //左前后转   
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);          //右后前转
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);          //左后后转
}



/*****************************************
* @功能介绍： 步进电机右转初始化
* @函数参数：	无
* @返回值：		无
******************************************/
void Stepping_Motor_Right_Init(void)
{
    // 初始化每个轮子的PWM配置
    OC_channel[FrontLeft].OC_Channel_Duty = 90;
    OC_channel[FrontLeft].OC_Channel_Pulse =90;
    OC_channel[FrontRight].OC_Channel_Duty =90;
    OC_channel[FrontRight].OC_Channel_Pulse = 90;
    OC_channel[RearLeft].OC_Channel_Duty = 90;
    OC_channel[RearLeft].OC_Channel_Pulse =90;
    OC_channel[RearRight].OC_Channel_Duty = 90;
    OC_channel[RearRight].OC_Channel_Pulse = 90;
		HAL_TIM_OC_Start_IT(&htim3,TIM_CHANNEL_1);
		HAL_TIM_OC_Start_IT(&htim3,TIM_CHANNEL_2);
    HAL_TIM_OC_Start_IT(&htim3, TIM_CHANNEL_3); // PB0
    HAL_TIM_OC_Start_IT(&htim3, TIM_CHANNEL_4); // PB1

	
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);  //左前前转
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);  //右前后转
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);  //左后前转
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);  //右后后转
}
/*****************************************
* @功能介绍： 步进电机后退初始化
* @函数参数：	无
* @返回值：		无
******************************************/
void Stepping_Motor_Back_Init(void)
{
	  back_flag=1;
    // 初始化每个轮子的PWM配置
    OC_channel[FrontLeft].OC_Channel_Duty = 50;
    OC_channel[FrontLeft].OC_Channel_Pulse = 70;
    OC_channel[FrontRight].OC_Channel_Duty = 50;
    OC_channel[FrontRight].OC_Channel_Pulse = 70;
    OC_channel[RearLeft].OC_Channel_Duty = 50;
    OC_channel[RearLeft].OC_Channel_Pulse = 70;
    OC_channel[RearRight].OC_Channel_Duty = 50;
    OC_channel[RearRight].OC_Channel_Pulse = 70;

    // 启动定时器通道的中断
    HAL_TIM_OC_Start_IT(&htim3, TIM_CHANNEL_1); // PA6
    HAL_TIM_OC_Start_IT(&htim3, TIM_CHANNEL_2); // PA7
    HAL_TIM_OC_Start_IT(&htim3, TIM_CHANNEL_3); // PB0
    HAL_TIM_OC_Start_IT(&htim3, TIM_CHANNEL_4); // PB1
    // 设置正反转控制线
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET); 
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET); 
}
/*****************************************
* @功能介绍： 步进电机左右调整
* @函数参数：	无
* @返回值：		无
******************************************/
void Direction_correction(void)
{
		if(Turn_Flag==0)
		{
			if(back_flag==0)
			{
				Gyro_PID(Gyro_Variable.Yaw_Calibration,0);
				OC_channel[FrontLeft].OC_Channel_Pulse=left_standard+PID_Groud.out;
				OC_channel[RearLeft].OC_Channel_Pulse=left_standard+PID_Groud.out;
				OC_channel[FrontRight].OC_Channel_Pulse=right_standard-PID_Groud.out;				
				OC_channel[RearRight].OC_Channel_Pulse=right_standard-PID_Groud.out;
			}
			if(back_flag==1)
			{
				Gyro_PID(Gyro_Variable.Yaw_Calibration,0);
				OC_channel[FrontLeft].OC_Channel_Pulse=left_standard-PID_Groud.out;
				OC_channel[RearLeft].OC_Channel_Pulse=left_standard-PID_Groud.out;
				OC_channel[FrontRight].OC_Channel_Pulse=right_standard+PID_Groud.out;				
				OC_channel[RearRight].OC_Channel_Pulse=right_standard+PID_Groud.out;
			}
		}	
}
/*****************************************
* @功能介绍： 步进电机转动指定角度
* @函数参数1：转动方向
* @函数参数2：转动角度
* @返回值：		无
******************************************/
void Stepping_Motor_Turn(int direction,float angle)
{
		if(direction==left)
		{
			if(flag==0)
			{
					Turn_Flag=1;//转弯标志位   置1后不会进行左右调整
					Stepping_Motor_Stopping_Init();
					HAL_Delay(600);
					Stepping_Motor_Left_Init();
					Gyro_Variable.init_Yaw_age=angle+Gyro_Variable.init_Yaw_age;
					if(Gyro_Variable.init_Yaw_age>=360)Gyro_Variable.init_Yaw_age=Gyro_Variable.init_Yaw_age-360.000;
					Gyro_Get();
					HAL_Delay(500);
					flag=1;
			}
			else if(flag==1)
			{
				Gyro_Get();
				if(   ((Gyro_Variable.Yaw_Calibration<=1)&&(Gyro_Variable.Yaw_Calibration>=0))    ||   ((Gyro_Variable.Yaw_Calibration>=358)&& (Gyro_Variable.Yaw_Calibration<=360)))
				{
						
						Stepping_Motor_Stopping_Init();
						HAL_Delay(2500);
						flag=0;
			  			Turn_Flag=0;
						cross++;
						Stepping_Motor_Go_Init();
				}
			}
		}
		if(direction==right)
		{
			if(flag==0)
			{
					Turn_Flag=1;
					Stepping_Motor_Stopping_Init();
					HAL_Delay(600);
					Stepping_Motor_Right_Init();
					Gyro_Variable.init_Yaw_age=Gyro_Variable.init_Yaw_age-angle;
					if(Gyro_Variable.init_Yaw_age<=0)Gyro_Variable.init_Yaw_age=Gyro_Variable.init_Yaw_age+360.000;
					Gyro_Get();
					HAL_Delay(500);
					flag=1;
			}
			else if(flag==1)
			{
					Gyro_Get();
					if(((Gyro_Variable.Yaw_Calibration<=1)&&(Gyro_Variable.Yaw_Calibration>=0))||((Gyro_Variable.Yaw_Calibration>=358)&& (Gyro_Variable.Yaw_Calibration<=360)))
					{
							Stepping_Motor_Stopping_Init();
							HAL_Delay(2500);
						    flag=0;
							Turn_Flag=0;
							cross++;
							Stepping_Motor_Go_Init();
					}
			}
		}
}


/*****************************************
* @功能介绍： 定时器输出比较中断，用于产生驱动步进电机的脉冲
* @函数参数：	定时器编号
* @返回值：		无
* @其他：     每1/10000秒计数器加一，改变Pulse的值可以改变周期，改变Duty的值可以改变占空比。
							Duty的取值范围为0-100
******************************************/
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
    uint16_t OC_Capture = 0;
    if (htim->Instance == TIM3)
    {
        // 处理 PA6Channel_1
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
        {
            OC_channel[FrontLeft].Sum++;
            OC_Capture = __HAL_TIM_GetCompare(&htim3, TIM_CHANNEL_1);
            if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6))
            {
                __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, OC_Capture + OC_channel[FrontLeft].OC_Channel_Pulse - OC_channel[FrontLeft].OC_Channel_Duty * OC_channel[FrontLeft].OC_Channel_Pulse / 100.0);
            }
            else 
            {
                __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, OC_Capture + OC_channel[FrontLeft].OC_Channel_Duty * OC_channel[FrontLeft].OC_Channel_Pulse / 100.0);
            }
        }

        // 处理 PA7Channel_2
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
        {
            OC_channel[FrontRight].Sum++;
            OC_Capture = __HAL_TIM_GetCompare(&htim3, TIM_CHANNEL_2);
            if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7))
            {
                __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, OC_Capture + OC_channel[FrontRight].OC_Channel_Pulse - OC_channel[FrontRight].OC_Channel_Duty * OC_channel[FrontRight].OC_Channel_Pulse / 100.0);
            }
            else 
            {
                __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, OC_Capture + OC_channel[FrontRight].OC_Channel_Duty * OC_channel[FrontRight].OC_Channel_Pulse / 100.0);
            }
        }

        // 处理 PB0Channel_3
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
        {
            OC_channel[RearLeft].Sum++;
            OC_Capture = __HAL_TIM_GetCompare(&htim3, TIM_CHANNEL_3);
            if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0))
            {
                __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, OC_Capture + OC_channel[RearLeft].OC_Channel_Pulse - OC_channel[RearLeft].OC_Channel_Duty * OC_channel[RearLeft].OC_Channel_Pulse / 100.0);
            }
            else 
            {
                __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, OC_Capture + OC_channel[RearLeft].OC_Channel_Duty * OC_channel[RearLeft].OC_Channel_Pulse / 100.0);
            }
        }

        // 处理 PB1Channel_4
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)
        {
            OC_channel[RearRight].Sum++;
            OC_Capture = __HAL_TIM_GetCompare(&htim3, TIM_CHANNEL_4);
            if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1))
            {
                __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, OC_Capture + OC_channel[RearRight].OC_Channel_Pulse - OC_channel[RearRight].OC_Channel_Duty * OC_channel[RearRight].OC_Channel_Pulse / 100.0);
            }
            else 
            {
                __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, OC_Capture + OC_channel[RearRight].OC_Channel_Duty * OC_channel[RearRight].OC_Channel_Pulse / 100.0);
            }
        }
    }
}

/*****************************************
* @功能介绍： 车辆走固定距离
* @函数参数：	距离（CM）
* @返回值：		无
******************************************/

void Go_Distance(float distance)
{		
	  OC_channel[FrontLeft].Sum=0;
		OC_channel[FrontRight].Sum=0;
		OC_channel[RearLeft].Sum=0; 
	  OC_channel[RearRight].Sum=0;
		while(((OC_channel[FrontLeft].Sum)+(OC_channel[FrontRight].Sum)+(OC_channel[RearLeft].Sum)+(OC_channel[RearRight].Sum))/8  <  ((distance/(9.50*3.1415926535)) *400 ))
		{
			Gyro_Get();
		}
		Stepping_Motor_Stopping_Init();
}


void GO_Distance_hongwai_A(float distance , float error ) //使用前加上前进初始化
{	
		
	  OC_channel[FrontLeft].Sum=0;
		OC_channel[FrontRight].Sum=0;
		OC_channel[RearLeft].Sum=0;
	  OC_channel[RearRight].Sum=0;
		while(((OC_channel[FrontLeft].Sum)+(OC_channel[FrontRight].Sum)+(OC_channel[RearLeft].Sum)+(OC_channel[RearRight].Sum))/8  <  (((distance+error)/(9.50*3.1415926535)) *400 ))
		{
			Gyro_Get();
			if(((OC_channel[FrontLeft].Sum)+(OC_channel[FrontRight].Sum)+(OC_channel[RearLeft].Sum)+(OC_channel[RearRight].Sum))/8  >  (((distance-error)/(9.50*3.1415926535)) *400 ))red1_falg = 0;
			if(red1_go == 1)
			{
				break;
			}
		}
}

void GO_Distance_hongwai_C(float distance , float error ) //使用前加上前进初始化
{	
	  OC_channel[FrontLeft].Sum=0;
		OC_channel[FrontRight].Sum=0;
		OC_channel[RearLeft].Sum=0;
	  OC_channel[RearRight].Sum=0;
		while(((OC_channel[FrontLeft].Sum)+(OC_channel[FrontRight].Sum)+(OC_channel[RearLeft].Sum)+(OC_channel[RearRight].Sum))/8  <  (((distance+error)/(9.50*3.1415926535)) *400 ))
		{
			Gyro_Get();
			if(((OC_channel[FrontLeft].Sum)+(OC_channel[FrontRight].Sum)+(OC_channel[RearLeft].Sum)+(OC_channel[RearRight].Sum))/8  >  (((distance-error)/(9.50*3.1415926535)) *400 ))red2_falg = 0;
			if(red2_go == 1)
			{
				break;
			}
		}
}

void Back_Distance(float distance)
{   
	  Stepping_Motor_Back_Init();
	  OC_channel[FrontLeft].Sum=0;
		OC_channel[FrontRight].Sum=0;
		OC_channel[RearLeft].Sum=0;
	  OC_channel[RearRight].Sum=0;
		while(((OC_channel[FrontLeft].Sum)+(OC_channel[FrontRight].Sum)+(OC_channel[RearLeft].Sum)+(OC_channel[RearRight].Sum))/8  <  ((distance/(9.50*3.1415926535)) *400 ))
		{
			Gyro_Get();
		}
		Stepping_Motor_Stopping_Init();
}

//void Go_Distance_bizhang_A(float distance)
//{
//	  OC_channel[FrontLeft].Sum=0;
//		OC_channel[FrontRight].Sum=0;
//		OC_channel[RearLeft].Sum=0;
//	  OC_channel[RearRight].Sum=0;
//		while(((OC_channel[FrontLeft].Sum)+(OC_channel[FrontRight].Sum)+(OC_channel[RearLeft].Sum)+(OC_channel[RearRight].Sum))/8  <  ((distance/(9.50*3.1415926535)) *400 ))
//		{
//			Gyro_Get();
//				if(red1_go == 1)		 //前提red1_flag==0；
//				{
//					Turn_Flag=1;
//				  OC_channel[FrontLeft].OC_Channel_Duty = 50;
//					OC_channel[FrontLeft].OC_Channel_Pulse =20;  //越小越快
//					OC_channel[FrontRight].OC_Channel_Duty =50;
//					OC_channel[FrontRight].OC_Channel_Pulse =90;
//					OC_channel[RearLeft].OC_Channel_Duty = 50;
//					OC_channel[RearLeft].OC_Channel_Pulse =20;
//					OC_channel[RearRight].OC_Channel_Duty = 50;
//					OC_channel[RearRight].OC_Channel_Pulse =90;
//					HAL_Delay(800);
//					
//					OC_channel[FrontLeft].OC_Channel_Duty = 50;
//					OC_channel[FrontLeft].OC_Channel_Pulse =80;
//					OC_channel[FrontRight].OC_Channel_Duty =50;
//					OC_channel[FrontRight].OC_Channel_Pulse =20;
//					OC_channel[RearLeft].OC_Channel_Duty = 50;
//					OC_channel[RearLeft].OC_Channel_Pulse =80;
//					OC_channel[RearRight].OC_Channel_Duty = 50;
//					OC_channel[RearRight].OC_Channel_Pulse =20;
//					HAL_Delay(800);
//					
//					Turn_Flag = 0 ;
//					
//					distance = distance + 10;
//					red1_falg = 1;
//					red1_go = 0;
//				}
//		}
//	
//		
//		Stepping_Motor_Stopping_Init();
//}
