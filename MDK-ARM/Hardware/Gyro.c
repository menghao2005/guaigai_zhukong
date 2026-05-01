/****************************************************************************
* @作者：				   笙歌凌缘
* @创建日期：	     2023年7月24日
* @最后更新日期：  2023年9月16日
* @所属：				   常熟理工学院
* @功能：	         存放有关陀螺仪的函数
 ****************************************************************************/
#include "Gyro.h"
Gyro_variable Gyro_Variable;

/*有关变量*/
int Start_Receiving;   //开始接收标志位
unsigned char data[11];//陀螺仪返回数据存放
uint8_t colour_data[18];
uint8_t lora_byte_received; 
unsigned int C_colour[12];

/*****************************************
* @功能介绍： 	四舍五入
* @函数参数：	需要四舍五入的值
* @返回值：		该数据四舍五入后的结果
******************************************/
int half_adjust(float a)
{
float b=a-(int)a;
	if(b<0.5)
		return (int)a;
	else 
		return (int)a+1;
}


/*****************************************
* @功能介绍： 	陀螺仪初始化
* @函数参数：	无
* @返回值：		无
******************************************/
void Gyro_Init(void)
{
		HAL_UART_Receive_IT(&huart3,&Gyro_Variable.shujv,1);
		HAL_Delay(1000);
		Gyro_Variable.init_Yaw_age = Gyro_Variable.Yaw;	
		
}


/*****************************************
* @功能介绍： 	获取陀螺仪的校正差值
* @函数参数：	无
* @返回值：		无
******************************************/
void Gyro_Get(void)
{
//		int now_Yaw_age;
//		now_Yaw_age=half_adjust(Gyro_Variable.Yaw);//四舍五入yaw
		Gyro_Variable.Yaw_Calibration=Gyro_Variable.Yaw-Gyro_Variable.init_Yaw_age;
		if(Gyro_Variable.Yaw_Calibration>=360)Gyro_Variable.Yaw_Calibration=0.000;
		if(Gyro_Variable.Yaw_Calibration<0)Gyro_Variable.Yaw_Calibration=Gyro_Variable.Yaw_Calibration+360.000;
}


/*****************************************
* @功能介绍： 	串口3的回调函数，处理陀螺仪发回来的数据
* @函数参数：	无
* @返回值：		无
******************************************/
void HAL_UART_GyroRxCallback(void)
{
	    static int i ;
			if(Gyro_Variable.shujv==0x55)//帧头0x55
				{
					Start_Receiving=1;
				}
				
		  	if(Start_Receiving==1)
		    {
					data[i]=Gyro_Variable.shujv;
					i++;
					if(i==11)//接受完毕，停止接收
					{
							Start_Receiving=0;
							i=0;
							if(data[1]==0x53)//进入了0x53数据包
							{
								Gyro_Variable.Yaw=(float)((data[7]<<8)|data[6])/32768*180;
							}
							
					}
		    }
			HAL_UART_Receive_IT(&huart3,&Gyro_Variable.shujv,1);
}


//void HAL_UART_LoraRxCallback(void)  // openmv
//{
//	static int t ;
//	if(lora_byte_received>='0'&&lora_byte_received<='9') //cheat
//	{
//		colour_data[t++] = lora_byte_received-'0';	
//	}
//	if(t==18)	
//	{
//		start_flag=1;
//		HAL_UART_AbortReceive_IT(&huart4);
//	}

//	if(!start_flag)
//		HAL_UART_Receive_IT(&huart4, &lora_byte_received, 1);
//    
//}






