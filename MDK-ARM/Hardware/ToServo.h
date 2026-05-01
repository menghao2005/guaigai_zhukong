#ifndef __TOSERVO_H__
#define __TOSERVO_H__
#include "main.h"
typedef struct
{
		uint8_t data;
		int Receive_Flag;
		uint8_t Data[2];
		int num;
}Servo_Receive;
extern Servo_Receive Servo_receive_data;
void Servo_Tx(uint8_t data);
void Servo_Init(void);
#endif

