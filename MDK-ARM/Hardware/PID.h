#ifndef __PID_H__
#define __PID_H__
#include "main.h"
extern int PID_Clear;

typedef struct
{
  float Kp;
	float Ki;
	float Kd;
	int out;
}PID;

extern PID PID_Groud;

void PID_Init(void);
void Gyro_PID(float yaw_value,float target_yaw);//YAWÆ«º½
#endif
