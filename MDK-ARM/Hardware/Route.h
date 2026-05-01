#ifndef __ROUTE_H__
#define __ROUTE_H__
#include "main.h"
extern  int a_fruit_flag;
extern  int b_fruit_flag;
extern  int c_fruit_flag;
extern int c_fruit_flag1;
extern unsigned int flower_num;
extern int cross;
extern int Truing_falg;
extern volatile int red1_falg;
extern volatile int red2_falg;
extern volatile int red1_go;
extern volatile int red2_go;
void clear_flag(void);
void A_region_irrigate(void);
void B_region_irrigate(void);
void C_region_irrigate(void);
extern unsigned int d_lcolour,d_rcolour;
#endif
