#ifndef __MPU_H__
#define __MPU_H__
#include "main.h"
extern uint8_t MPU_unlock;
void MPU_Init(void);
void MP3(int x);
void voice_init(void);
void K210_Init(void);
void Voice_Select(unsigned int colour);
void K210_ldetect(void);
void K210_rdetect(void);
void waterpump_init(void);
void waterpump(unsigned int water_time,unsigned int modeselect);
void l_water(void);
void r_water(void);
void common_water(void);

#endif


