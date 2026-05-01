/****************************************************************************
* @作者：				   YYX
* @创建日期：	   2024/7/10
* @最后更新日期：  2024
* @所属：				  常熟理工学院
* @功能：	        初始化与MP3与定时器中断回调
 ****************************************************************************/
 /*
						   _oo0oo_
						  o8888888o
						  88" . "88
						  (| -_- |)
						  0\  =  /0
						___/`---'\___
					 .' \\|     |// '.
					 / \\|||  :  |||// \
					/ _||||| -:- |||||- \
				 |   | \\\  -  /// |   |
	  +         | \_|  ''\---/''  |_/ |
					\  .-\__  '-'  ___/-. /
				___'. .'  /--.--\  `. .'___
			 ."" '<  `.___\_<|>_/___.' >' "".
			 | | :  `- \`.;`\ _ /`;.`/ - ` : | |
			 \  \ `_.   \_ __\ /__ _/   .-` /  /
		 =====`-.____`.___ \_____/___.-`___.-'=====
						   `=---='
	
		 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
	
		 佛祖保佑       永不宕机     永无BUG
 * 
 *        佛曰:  
 *                写字楼里写字间，写字间里程序员；  
 *                程序人员写程序，又拿程序换酒钱。  
 *                酒醒只在网上坐，酒醉还来网下眠；  
 *                酒醉酒醒日复日，网上网下年复年。  
 *                但愿老死电脑间，不愿鞠躬老板前；                                          */
//******************************************************//专项赛
#include "MPU.h"
#include "Gyro.h"
#include "Route.h"

uint8_t MPU_unlock=0;
void MPU_Init(void)
{
	HAL_TIM_Base_Start_IT(&htim6); //启动定时器6的中断
	HAL_Delay(500);
		voice_init();
    waterpump_init(); //初始化水泵模块
    HAL_Delay(600);
   Voice_Select(4);
	PID_Init();//初始化PID控制器。
	Gyro_Init();//初始化陀螺仪。
	Servo_Init();//初始化c8t6串口接收
	Servo_Tx(0x30);//向伺服电机发送数据
	HAL_Delay(500);
	HAL_TIM_Base_Start_IT(&htim6); //再次启动定时器6的中断。
}


/*****************************************
* @功能介绍： 定时器6的中断回调函数
* @函数参数：	无
* @返回值：		无
******************************************/
//void HAL_TIM_BaseCallback(void)  //每个1MS进一次
//{
//		static int cnt;
//		cnt++;
//		if(cnt>10000)cnt=0;
//		if(cnt%3==0){Gyro_Get();}
//		if(cnt%4==0){Red_flag();}
//		if(cnt%20==0){Direction_correction();}
//}
/* 1 ms 周期主回调 —— 无斜坡，仅提高采样频率 */
void HAL_TIM_BaseCallback(void)
{
    static uint16_t cnt = 0;
    cnt++;

    /* 2 ms 陀螺仪采样 */
    if (cnt % 2 == 0)
        Gyro_Get();

    /* 4 ms 红外/标志检测 */
    if (cnt % 4 == 0)
        Red_flag();

    /* 4 ms 方向修正（PID 直接写） */
    if (cnt % 10 == 0)
        Direction_correction();
}

void voice_init(void)  
{
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,GPIO_PIN_SET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_1,GPIO_PIN_SET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9,GPIO_PIN_SET);
	HAL_Delay(10);	
  HAL_GPIO_WritePin(GPIOE,GPIO_PIN_15,GPIO_PIN_SET);
	HAL_Delay(10);	
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,GPIO_PIN_SET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_SET);
	HAL_Delay(10);	
}
void Voice_Select(unsigned int colour) //D15 F1 D9
{
	switch(colour)
	{
		case 1:
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,GPIO_PIN_RESET);
			HAL_Delay(500);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,GPIO_PIN_SET);
		break;
		case 2:
			HAL_GPIO_WritePin(GPIOF,GPIO_PIN_1,GPIO_PIN_RESET);
			HAL_Delay(500);
			HAL_GPIO_WritePin(GPIOF,GPIO_PIN_1,GPIO_PIN_SET);
		break;
		case 3:
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9,GPIO_PIN_RESET);
			HAL_Delay(500);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9,GPIO_PIN_SET);
		break;
     case 4:
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_15,GPIO_PIN_RESET);
			HAL_Delay(500);
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_15,GPIO_PIN_SET);
		break;
     case 5:
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,GPIO_PIN_RESET);
			HAL_Delay(500);
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,GPIO_PIN_SET);
		break;
     case 6:
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_RESET);
			HAL_Delay(500);
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_SET);
		break;        
	}
}
void waterpump_init(void) //E14 E12 E11 F4
{
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,GPIO_PIN_RESET);
}
void l_water(void) //左边喷一次
{
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,GPIO_PIN_RESET);
	HAL_Delay(300);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,GPIO_PIN_RESET);
}
void r_water(void) //右边喷一次
{
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_4,GPIO_PIN_RESET);
	HAL_Delay(300);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_4,GPIO_PIN_RESET);
}
void common_water(void)  //左右边各喷一次
{
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_4,GPIO_PIN_RESET);
	HAL_Delay(300);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_4,GPIO_PIN_RESET);
}
void waterpump(unsigned int water_time,unsigned int modeselect) //次数时间 模式
{
	if(modeselect==1)
	{
		if(water_time==1)
		{
			l_water();
		}
		if(water_time==2)
		{
			l_water();
			HAL_Delay(700);
			l_water();
		}
		if(water_time==3)
		{
			l_water();
			HAL_Delay(700);
			l_water();
			HAL_Delay(700);
			l_water();
		}
	}
	if(modeselect==2)
	{		
		if(water_time==1)
		{
			r_water();
		}
		if(water_time==2)
		{
			r_water();
			HAL_Delay(500);
			r_water();
		}
		if(water_time==3)
		{
			r_water();
			HAL_Delay(500);
			r_water();
			HAL_Delay(500);
			r_water();
		}
	}
	if(modeselect==3)
	{	
		if(water_time==1)
		{
			common_water();
		}
		if(water_time==2)
		{
			common_water();
			HAL_Delay(500);
			common_water();
		}
		if(water_time==3)
		{
			common_water();
			HAL_Delay(500);
			common_water();
			HAL_Delay(500);
			common_water();
		}
	}
}

