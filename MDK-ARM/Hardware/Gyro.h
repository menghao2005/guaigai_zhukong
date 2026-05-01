#ifndef __GYRO_H__
#define __GYRO_H__
#include "main.h"
typedef struct {
    uint8_t shujv;             // 一个8位无符号整数，可能用于存储某些标志或简单的计数值
    float Yaw;                 // 当前的Yaw（偏航角）值
    float init_Yaw_age;        // 初始的Yaw（偏航角）值
    float Yaw_Calibration;     // 校正的Yaw（偏航角）值
} Gyro_variable;
extern Gyro_variable Gyro_Variable;
extern int j;
extern uint8_t colour_data[18];
extern uint8_t lora_byte_received;
/*相关函数存放*/
void Gyro_Init(void);
void Gyro_Get(void);

#endif
