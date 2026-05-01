#ifndef __STEPPINGMOTOR_H__
#define __STEPPINGMOTOR_H__
#include "main.h"
#define left 0
#define right 1

typedef struct
{
	uint16_t OC_Channel_Pulse;
	uint16_t OC_Channel_Duty;
	uint16_t Sum;
}OC_Channel;                                 //创建结构体类型OC_Channel
typedef enum
{
    FrontLeft,  // 前左轮    枚举值0
    FrontRight, // 前右轮    枚举值1
    RearLeft,   // 后左轮    枚举值2
    RearRight,  // 后右轮    枚举值3
    NumMotors,  // 总轮子数  枚举值4
} Motor_Number;
extern OC_Channel OC_channel[NumMotors];     //创建一个成员数为4（NumMotors代表4）的结构体变量数组OC_channel[NumMotors]
extern int Turn_Flag;
extern int left_standard;
extern int right_standard;
void Stepping_Motor_Go_Init(void);
void Stepping_Motor_Left_Init(void);
void Stepping_Motor_Right_Init(void);
void Stepping_Motor_Stopping_Init(void);
void Stepping_Motor_Back_Init(void);
void Stepping_Motor_Turn(int direction,float angle);
void Direction_correction(void);
void Go_Distance(float distance);
void Back_Distance(float distance);
void GO_Distance_hongwai_A(float distance , float error ); //使用前加上前进初始化
void GO_Distance_hongwai_C(float distance , float error ); //使用前加上前进初始化
#endif
