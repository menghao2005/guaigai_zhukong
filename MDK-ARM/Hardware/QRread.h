#ifndef __QRread_H__
#define __QRread_H__

#include "main.h"

#define Initial 0
#define Num_A 8
#define Num_B 10
#define Num_C 8
#define Num_D 3

#define Yi 0x80 
#define Qing 0xBB 
#define Yan 0xA5 

#define TRIGGER_CMD_A 0xAA
#define TRIGGER_CMD_B 0xBB
#define TRIGGER_CMD_C 0xCC
#define TRIGGER_CMD_D 0xDD

#define FrameHeader_A 0xAF
#define FrameEnder_A 0xFA

#define FrameHeader_B 0xBF
#define FrameEnder_B 0xFB

#define FrameHeader_C 0xCF
#define FrameEnder_C 0xFC

#define FrameHeader_D 0xDF
#define FrameEnder_D 0xFD
uint8_t Travelarr(unsigned char Flowernum);

void QRread_Init(uint8_t area);

void Triggerreading(uint8_t cmd);

extern uint8_t Colorcode_A[Num_A],QRcode_B[Num_B],QRcode_C[Num_C],drought_D[Num_D],ARR[7];

void Conversion(void);
#endif 
