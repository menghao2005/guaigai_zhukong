#include "QRread.h"

uint8_t Colorcode_A[Num_A]={0},QRcode_B[Num_B]={0},QRcode_C[Num_C]={0},drought_D[Num_D]={0},ARR[7]={0};
volatile uint8_t QRflag_C =0;

void Triggerreading(uint8_t cmd)//发送指令
{
  HAL_UART_Transmit(&huart4,&cmd,1,HAL_MAX_DELAY);
}



void QRread_Init(uint8_t area) 		//初始化串口4接收缓冲区
{
	if(area == 'B')HAL_UART_Receive_IT(&huart4,QRcode_B,10);
	if(area == 'C')HAL_UART_Receive_IT(&huart4,QRcode_C,8);
	if(area == 'D')HAL_UART_Receive_IT(&huart4,drought_D,3);
}



uint8_t Travelarr(uint8_t Flowernum)  //B区形参为花盆号，返回值为喷射几次
{  
  for(uint8_t i=1;i<=4;i++)
	{
	  if(QRcode_B[i] == Flowernum)
		{
			switch(QRcode_B[i+4])
				{
					case Qing:
						return 1;
					case Yi:
						return 2;
					case Yan:
						return 3;
				}
		}
	}
	return 0;
}


void Conversion(void)  								 //转化C区
{
	for( uint8_t i = 1;i <= 6; i++ )
	{
		uint32_t temp ;
	  temp = QRcode_C[i]- '0';
		QRcode_C[i] = temp;
		if(QRcode_C[i]%2 == 0)
		{
		  QRcode_C[i]--; //将偶数246变成135便于计算
			ARR[i] = 1;  	 //从246变成135的对应ARR位置变成1
		}	
	}
}



void HAL_UART_MaixCamRxCallback(void)  // Maix Cam
{
	
//	if(FrameHeader_B == QRcode_B[Initial])
//	{
//		QRcode_B[Initial] = Initial;
////		HAL_UART_Receive_IT(&huart4,QRcode_B+1,9);
//	}
//	 if(FrameHeader_C == QRcode_C[Initial])
//	{
//		QRcode_C[Initial] = Initial;
//		
////		HAL_UART_Receive_IT(&huart4,QRcode_C+1,7);
//	}
//	else if(FrameHeader_D == drought_D[Initial])
//	{
//		drought_D[Initial] = Initial;
//	}
//	else
//		HAL_UART_AbortReceive_IT(&huart4);
//	  
}
