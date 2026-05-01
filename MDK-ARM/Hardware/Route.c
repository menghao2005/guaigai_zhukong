/****************************************************************************
* @作者：				   YYX
* @创建日期：	   2024/7/10
* @最后更新日期：  2024/8/3
* @所属：				  常熟理工学院
* @功能：	        路线
 ****************************************************************************/
#include "main.h"
int a_fruit_flag=1;//0
int	 b_fruit_flag=0;
int	c_fruit_flag=0;//0
int d_fruit_flag=0;
unsigned int flower_num=0;
int cross=1;//1
int Truing_falg=0;
int infraredB;
int c_fruit_flag1=0;int l_c_fruit=0,r_c_fruit=0;
int d_lflag,d_rflag,c_lflag,c_rflag;
volatile int red1_falg=1;
volatile int red2_falg=1;
int d_jiance=0,c_jiance=0;
volatile int red1_go=0;
volatile int red2_go=0;
uint32_t begin_time;
unsigned int d_lcolour,d_rcolour;
uint32_t temp_FL,temp_FR,temp_RL,temp_RR;
void clear_flag(void)
{
		red1_falg=0;
		red1_go=0;
		red2_falg=0;
		red2_go=0;
		begin_time=0;
}

#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
}
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((UART5->SR&0X40)==0)
	{}//循环发送,直到发送完毕   
    UART5->DR = (uint8_t)ch;      
	return ch;
}

uint8_t value_voice(uint8_t num)
{
	if(num == 1)return 2;
	else if(num == 2)return 6;
	else return 3;
}

uint8_t Value(uint8_t Flowernum)  //B区形参为花盆号，返回值为喷射几次
{ 
	switch(QRcode_B[Flowernum+4])
			{
					case Qing:return 1;
					case Yi:return 2;
					case Yan:return 3;
			}
		 return 0;
}

void HMI_send_number(char* name, int num)
{
    printf("%s=%d\xff\xff\xff", name, num);
}

void drought_A_display(void)   //串口屏
{
	uint32_t number = 0;
	for (int i = 1; i <= 6; i++) 
	{
    number = number * 10 +(int)(Colorcode_A[i]-'0');
	}
	 HMI_send_number("n0.val",number);
}

void drought_B_display(void)
{
	uint32_t number = 0 ;
		for (int i = 1; i < 9; i++) 
	{
		if(i<=4)number = number * 10 +(int)(QRcode_B[i]-'0');
		else  number = number * 10 +(Value(i-4));
	}
	 HMI_send_number("n1.val",number);
}

void drought_C_display_A(void)	
{
	uint32_t number = 0;
		for (int i = 1; i <= 6; i++) 
	{
    number = number * 10 +(int)(QRcode_C[i]-'0');
	}
	 HMI_send_number("n2.val",number);
}

void drought_C_display_B(uint8_t num)
{
		static uint32_t number = 0;
		number = number * 10 + (int)(num-'0');
		HMI_send_number("n3.val",number);
}

void A_region_irrigate(void)
{
				Servo_Tx(TRIGGER_CMD_A);  //向C8T6发送接收A区的指令
				while(Colorcode_A[7]!=FrameEnder_A)
			{Stepping_Motor_Stopping_Init();}//接收完成，死循环（待改进）
					Voice_Select(5);
				drought_A_display(); 
	
				Stepping_Motor_Go_Init();//初始化步进电机。
				GO_Distance_hongwai_A(62,5);
				HAL_Delay(130);
				Stepping_Motor_Stopping_Init();
				red1_falg = 1;
				red1_go = 0;//复位
//				Servo_Tx(0x1A);  // 发送指令给舵机。
//				HAL_Delay(2000);
//				Voice_Select((int)(Colorcode_A[1]-'0'));   // 根据 colour_data 数组中的值选择并播放语音。
//				HAL_Delay(500);
//				begin_time=HAL_GetTick();
//				HAL_Delay(10);
//				while(HAL_GetTick()-begin_time<800);
//				waterpump((int)(Colorcode_A[1]-'0'),1);//控制水泵
//				begin_time=HAL_GetTick(); 
//				HAL_Delay(10);
//				while(HAL_GetTick()-begin_time<3500);
//				
//				Servo_Tx(0x2A);  // 发送指令给舵机。
//				HAL_Delay(2000);
//				Voice_Select((int)(Colorcode_A[2]-'0'));   // 根据 colour_data 数组中的值选择并播放语音。
//				HAL_Delay(500);
//				begin_time=HAL_GetTick();
//				HAL_Delay(10);
//				while(HAL_GetTick()-begin_time<800);
//				waterpump((int)(Colorcode_A[2]-'0'),1);//控制水泵
//				begin_time=HAL_GetTick(); 
//				HAL_Delay(10);
//				while(HAL_GetTick()-begin_time<3000);

				Stepping_Motor_Go_Init();
				GO_Distance_hongwai_A(100,5);
				HAL_Delay(100);
				Stepping_Motor_Stopping_Init();
				red1_falg = 1;
				red1_go = 0;//复位
//				Servo_Tx(0x1A);  // 发送指令给舵机。
//				HAL_Delay(2000);
//				Voice_Select((int)(Colorcode_A[3]-'0'));   
//				HAL_Delay(500);
//				begin_time=HAL_GetTick();
//				HAL_Delay(10);
//				while(HAL_GetTick()-begin_time<800);
//				waterpump((int)(Colorcode_A[3]-'0'),1);//控制水泵
//				begin_time=HAL_GetTick(); 
//				HAL_Delay(10);
//				while(HAL_GetTick()-begin_time<3500);

//				Servo_Tx(0x2A);  // 发送指令给舵机。
//				HAL_Delay(2000);
//				Voice_Select((int)(Colorcode_A[4]-'0'));  
//				HAL_Delay(500);				
//				begin_time=HAL_GetTick();
//				HAL_Delay(10);
//				while(HAL_GetTick()-begin_time<800);
//				waterpump((int)(Colorcode_A[4]-'0'),1);//控制水泵
//				begin_time=HAL_GetTick(); 
//				HAL_Delay(10);
//				while(HAL_GetTick()-begin_time<3000);
				
				Stepping_Motor_Go_Init();
				GO_Distance_hongwai_A(100,5);
				HAL_Delay(100);
				Stepping_Motor_Stopping_Init();
				red1_falg = 1;
				red1_go = 0;//复位
//				Servo_Tx(0x1A);  // 发送指令给舵机。
//				HAL_Delay(2000);
//				Voice_Select((int)(Colorcode_A[5]-'0')); 
//				HAL_Delay(500);				
//				begin_time=HAL_GetTick();
//				HAL_Delay(10);
//				while(HAL_GetTick()-begin_time<800);
//				waterpump((int)(Colorcode_A[5]-'0'),1);//控制水泵
//				begin_time=HAL_GetTick(); 
//				HAL_Delay(10);
//				while(HAL_GetTick()-begin_time<3500);

//				Servo_Tx(0x2A);  // 发送指令给舵机。
//				HAL_Delay(2000);
//				Voice_Select((int)(Colorcode_A[6]-'0'));
//				HAL_Delay(500);				
//				begin_time=HAL_GetTick();
//				HAL_Delay(10);
//				while(HAL_GetTick()-begin_time<800);
//				waterpump((int)(Colorcode_A[6]-'0'),1);//控制水泵
//				begin_time=HAL_GetTick(); 
//				HAL_Delay(10);
//				while(HAL_GetTick()-begin_time<3000);


				Stepping_Motor_Go_Init();		
				Go_Distance(45);//待调试
		
					if(cross==1)//转弯2
				{
					while(cross==1)
					{
						Stepping_Motor_Turn(right,90);
					}
				}	
				
	
				red2_falg = 0; //开启红外
				Stepping_Motor_Go_Init();
				while(red2_go != 1); //没扫到障碍物时一直前进
				red2_falg = 1;//一旦扫到关闭红外
				red2_go = 0;
				
				HAL_Delay(800);
						
				red2_falg = 0; //开启红外
				Stepping_Motor_Go_Init();
				while(red2_go != 1); //没扫到障碍物时一直前进
				red2_falg = 1;//一旦扫到关闭红外
				red2_go = 0;
				Stepping_Motor_Stopping_Init();
				HAL_Delay(100); 
			 	QRread_Init('B');
				HAL_Delay(100); 
			  Triggerreading(TRIGGER_CMD_B);
				HAL_Delay(1000);
  			while(QRcode_B[9]!=FrameEnder_B)
			 {
				 QRread_Init('B');
				 HAL_Delay(100);
				Triggerreading(TRIGGER_CMD_B);
					HAL_Delay(1000);
			 }
						Voice_Select(5);
			 
					drought_B_display();
			 
			 
				Stepping_Motor_Go_Init();
				Go_Distance(52);

			if(cross==2)
			{
				while(cross==2)
				{
					Stepping_Motor_Turn(right,90);
				}
			}
			Stepping_Motor_Stopping_Init();

}

void B_region_irrigate(void)
{
				Servo_Tx(0x32);
				Stepping_Motor_Go_Init();
				Go_Distance(65);  //待调试

//		if(Travelarr(0x31)!=0||Travelarr(0x32)!=0)
//				{
//					if(Travelarr(0x31)!=0)
//					{
//			
//						Servo_Tx(0x1B);
//						HAL_Delay(2000);	
//						Voice_Select(Travelarr(0x31));
//						HAL_Delay(500);
//						begin_time=HAL_GetTick(); 
//						HAL_Delay(10);
//						while(HAL_GetTick()-begin_time<800);
//						waterpump(Travelarr(0x31),1);
//						begin_time=HAL_GetTick(); 
//						HAL_Delay(10);
//						while(HAL_GetTick()-begin_time<3000);
//					}
//         if(Travelarr(0x32)!=0)
//					{	
//			
//						Servo_Tx(0x2B);
//						HAL_Delay(2000);
//						Voice_Select(Travelarr(0x32));
//						HAL_Delay(500);						
//						begin_time=HAL_GetTick(); 
//						HAL_Delay(10);
//						while(HAL_GetTick()-begin_time<800);
//						waterpump(Travelarr(0x32),1);
//						begin_time=HAL_GetTick(); 
//						HAL_Delay(10);
//						while(HAL_GetTick()-begin_time<2500);
//					}
//				}
				Stepping_Motor_Go_Init();
					Go_Distance(74);
				
//				if(Travelarr(0x33)!=0||Travelarr(0x34)!=0)
//				{
//				if(Travelarr(0x33)!=0)
//					{

//						Servo_Tx(0x1B);
//						HAL_Delay(2000);
//						Voice_Select(Travelarr(0x33));
//						HAL_Delay(500);						
//						begin_time=HAL_GetTick(); 
//						HAL_Delay(10);
//						while(HAL_GetTick()-begin_time<800);
//						waterpump(Travelarr(0x33),1);
//						begin_time=HAL_GetTick(); 
//						HAL_Delay(10);
//						while(HAL_GetTick()-begin_time<3000);
//					}
//       if(Travelarr(0x34)!=0)
//					{

//						Servo_Tx(0x2B);
//						HAL_Delay(2000);
//						Voice_Select(Travelarr(0x34));
//						HAL_Delay(500);						
//						begin_time=HAL_GetTick(); 
//						HAL_Delay(10);
//						while(HAL_GetTick()-begin_time<800);
//						waterpump(Travelarr(0x34),1);
//						begin_time=HAL_GetTick(); 
//						HAL_Delay(10);
//						while(HAL_GetTick()-begin_time<2500);
//					}
//						
//				}
					Stepping_Motor_Go_Init();
					Go_Distance(75);
//					if(Travelarr(0x35)!=0||Travelarr(0x36)!=0)
//				{
//					 if(Travelarr(0x35)!=0)
//					{
//				
//						Servo_Tx(0x1B);
//						HAL_Delay(2000);
//						Voice_Select(Travelarr(0x35));
//						HAL_Delay(500);						
//						begin_time=HAL_GetTick(); 
//						HAL_Delay(10);
//						while(HAL_GetTick()-begin_time<800);
//						waterpump(Travelarr(0x35),1);
//						begin_time=HAL_GetTick(); 
//						HAL_Delay(10);
//						while(HAL_GetTick()-begin_time<3000);
//					}
//           if(Travelarr(0x36)!=0)
//					{

//						Servo_Tx(0x2B);
//						HAL_Delay(2000);
//						Voice_Select(Travelarr(0x36));
//						
//						HAL_Delay(500);						
//						begin_time=HAL_GetTick(); 
//						HAL_Delay(10);
//						while(HAL_GetTick()-begin_time<800);
//						waterpump(Travelarr(0x36),1);
//						begin_time=HAL_GetTick(); 
//						HAL_Delay(10);
//						while(HAL_GetTick()-begin_time<2500);
//					}
//						
//				}
				Stepping_Motor_Go_Init();
						Go_Distance(70);
}

void C_region_irrigate(void)
{
		Servo_Tx(0x31);
			if(cross==3)
		{
			while(cross==3)
		  {
				Stepping_Motor_Turn(left,90);
			}
		}
		Stepping_Motor_Stopping_Init();
	
		red1_falg = 0; //开启红外
		Stepping_Motor_Go_Init();
		while(red1_go != 1); //没扫到障碍物时一直前进
		red1_falg = 1;//一旦扫到关闭红外
		red1_go = 0;
		
		HAL_Delay(800);
		
		
		Stepping_Motor_Stopping_Init();
		
		red1_falg = 0; //开启红外
		Stepping_Motor_Go_Init();
		while(red1_go != 1); //没扫到障碍物时一直前进
		red1_falg = 1;//一旦扫到关闭红外
		red1_go = 0;
	Stepping_Motor_Stopping_Init();
		HAL_Delay(100); 
	  	QRread_Init('C');
			HAL_Delay(100); 
	Triggerreading(TRIGGER_CMD_C);
			HAL_Delay(800);
  	while(QRcode_C[7]!=FrameEnder_C)
			 { QRread_Init('C');
				 HAL_Delay(100);
				Triggerreading(TRIGGER_CMD_C);
					HAL_Delay(800);}
				HAL_Delay(100);
			drought_C_display_A();
				HAL_Delay(100);
				Conversion(); //这里有转化
		
			Voice_Select(5);
		
     Stepping_Motor_Go_Init();
				Go_Distance(53);  //需要实地调试！！！


						if(cross==4)
		{
			while(cross==4)
		  {
				Stepping_Motor_Turn(left,90);
			}
		}
		switch(QRcode_C[1])
					{
						case 1:
										GO_Distance_hongwai_A(40,8);
										HAL_Delay(120);
										Stepping_Motor_Stopping_Init();
										HAL_Delay(100);
										red1_falg = 1;
										red1_go = 0;//复位
									  if(ARR[1]==0)Servo_Tx(0x1C);
								    else Servo_Tx(0x2C);
										HAL_Delay(1200); //等两秒等舵机转过去
						
										
						
										QRread_Init('D');
										HAL_Delay(100); 
									 Triggerreading(TRIGGER_CMD_D); //开始扫描
						
										HAL_Delay(1000);
						
										while(drought_D[2]!=FrameEnder_D)
										{HAL_Delay(100);
											QRread_Init('D');
											HAL_Delay(100);
											Triggerreading(TRIGGER_CMD_D);
											begin_time=HAL_GetTick();
											HAL_Delay(10);
											while(HAL_GetTick()-begin_time<2000);
										};
										
										
										drought_C_display_B(drought_D[1]);
										Voice_Select(drought_D[1]-'0');   // 根据 colour_data 数组中的值选择并播放语音。
										HAL_Delay(500);
										begin_time=HAL_GetTick();
										HAL_Delay(10);
										while(HAL_GetTick()-begin_time<800);
										
										
										waterpump((drought_D[1]-'0'),1);//控制水泵
										begin_time=HAL_GetTick(); 
										HAL_Delay(10);
										while(HAL_GetTick()-begin_time<1500);
										Servo_Tx(0x5C);
										drought_D[2] = 0;
										break;
						
					  case 3:
									  GO_Distance_hongwai_A(140,10);
										HAL_Delay(120);
										Stepping_Motor_Stopping_Init();HAL_Delay(100);
										red1_falg = 1;
										red1_go = 0;//复位
									  if(ARR[1]==0)Servo_Tx(0x1C);
								    else Servo_Tx(0x2C);
										HAL_Delay(1200); //等两秒等舵机转过去
						
						
										QRread_Init('D');
										HAL_Delay(100); 
									  Triggerreading(TRIGGER_CMD_D); //开始扫描
						
										HAL_Delay(1000);
						
										while(drought_D[2]!=FrameEnder_D)
										{HAL_Delay(100);
											QRread_Init('D');
											HAL_Delay(100);
											Triggerreading(TRIGGER_CMD_D);
											begin_time=HAL_GetTick();
											HAL_Delay(10);
											while(HAL_GetTick()-begin_time<2000);
										};
										
										
										drought_C_display_B(drought_D[1]);
										Voice_Select(drought_D[1]-'0');   // 根据 colour_data 数组中的值选择并播放语音。
										HAL_Delay(500);
										begin_time=HAL_GetTick();
										HAL_Delay(10);
										while(HAL_GetTick()-begin_time<800);
										waterpump((int)(drought_D[1]-'0'),1);//控制水泵
										begin_time=HAL_GetTick(); 
										HAL_Delay(10);
										while(HAL_GetTick()-begin_time<1500);
										Servo_Tx(0x5C);
										drought_D[2] = 0;
										break;
						case 5:
								    GO_Distance_hongwai_A(240,20);
									  HAL_Delay(120);
									  Stepping_Motor_Stopping_Init();HAL_Delay(100);
										red1_falg = 1;
										red1_go = 0;//复位
										if(ARR[1]==0)Servo_Tx(0x1C);
									  else Servo_Tx(0x2C);
										HAL_Delay(1200); //等2秒等舵机转过去

						
										QRread_Init('D');
										HAL_Delay(100); 
									  Triggerreading(TRIGGER_CMD_D); //开始扫描
						
										HAL_Delay(1000);
						
										while(drought_D[2]!=FrameEnder_D)
										{HAL_Delay(100);
											QRread_Init('D');
											HAL_Delay(100);
											Triggerreading(TRIGGER_CMD_D);
											begin_time=HAL_GetTick();
											HAL_Delay(10);
											while(HAL_GetTick()-begin_time<2000);
										};
										
										
										drought_C_display_B(drought_D[1]);
										Voice_Select(drought_D[1]-'0');   // 根据 colour_data 数组中的值选择并播放语音。
										HAL_Delay(500);
										begin_time=HAL_GetTick();
										HAL_Delay(10);
										while(HAL_GetTick()-begin_time<800);
										waterpump((int)(drought_D[1]-'0'),1);//控制水泵
										begin_time=HAL_GetTick(); 
										HAL_Delay(10);
										while(HAL_GetTick()-begin_time<1500);
										Servo_Tx(0x5C);
										drought_D[2] = 0;
										break;
					}
					
		for(uint8_t i = 1 ; i <= 5 ; i++ )
				{
					if((QRcode_C[i+1])-(QRcode_C[i]) == 0)
				 {
					 HAL_Delay(2500); //不能少
					 Stepping_Motor_Stopping_Init();		//原地停
					 
					 if(ARR[i+1]==0)Servo_Tx(0x1C);
					else Servo_Tx(0x2C);
						HAL_Delay(1200); //等3秒等舵机转过去
					 
						QRread_Init('D');
						HAL_Delay(100); 
						 Triggerreading(TRIGGER_CMD_D); //开始扫描
						
										HAL_Delay(1000);
						
										while(drought_D[2]!=FrameEnder_D)
										{HAL_Delay(100);
											QRread_Init('D');
											HAL_Delay(100);
											Triggerreading(TRIGGER_CMD_D);
											begin_time=HAL_GetTick();
											HAL_Delay(10);
											while(HAL_GetTick()-begin_time<2000);
										};
						
						drought_C_display_B(drought_D[1]);
						Voice_Select(drought_D[1]-'0');   // 根据 colour_data 数组中的值选择并播放语音。
						HAL_Delay(500);
						begin_time=HAL_GetTick();
						HAL_Delay(10);
						while(HAL_GetTick()-begin_time<800);
						waterpump((int)(drought_D[1]-'0'),1);//控制水泵
						begin_time=HAL_GetTick(); 
						HAL_Delay(10);
						while(HAL_GetTick()-begin_time<1500);
						Servo_Tx(0x5C);
						drought_D[2] = 0;
				 }	
				 else if((QRcode_C[i+1])-(QRcode_C[i]) == 2)
				 {
					 
					 Stepping_Motor_Go_Init();
					 GO_Distance_hongwai_A(100,5);
					 HAL_Delay(120);
					 Stepping_Motor_Stopping_Init(); //下面写舵机
					 HAL_Delay(100);
										red1_falg = 1;
										red1_go = 0;//复位
					 
					 if(ARR[i+1]==0)Servo_Tx(0x1C);
					else Servo_Tx(0x2C);
					 
						HAL_Delay(1200); //等3秒等舵机转过去
										QRread_Init('D');
										HAL_Delay(100); 
							 Triggerreading(TRIGGER_CMD_D); //开始扫描
						
										HAL_Delay(1000);
						
										while(drought_D[2]!=FrameEnder_D)
										{HAL_Delay(100);
											QRread_Init('D');
											HAL_Delay(100);
											Triggerreading(TRIGGER_CMD_D);
											begin_time=HAL_GetTick();
											HAL_Delay(10);
											while(HAL_GetTick()-begin_time<2000);
										};
						drought_C_display_B(drought_D[1]);
						Voice_Select(drought_D[1]-'0');   // 根据 colour_data 数组中的值选择并播放语音。
						HAL_Delay(500);
						begin_time=HAL_GetTick();
						HAL_Delay(10);
						while(HAL_GetTick()-begin_time<800);
						waterpump((int)(drought_D[1]-'0'),1);//控制水泵
						begin_time=HAL_GetTick(); 
						HAL_Delay(10);
						while(HAL_GetTick()-begin_time<1500);
						Servo_Tx(0x5C);
						drought_D[2] = 0;
				 }
				 
				 
				else if((QRcode_C[i+1])-(QRcode_C[i]) == 4)
				 {
					 Stepping_Motor_Go_Init();
					 GO_Distance_hongwai_A(200,10);
					 HAL_Delay(120);
					 Stepping_Motor_Stopping_Init(); HAL_Delay(100);
										red1_falg = 1;
										red1_go = 0;//复位
					 if(ARR[i+1]==0)Servo_Tx(0x1C);
						else Servo_Tx(0x2C);
						HAL_Delay(1200); //等3秒等舵机转过去
										QRread_Init('D');
										HAL_Delay(100); 
									  Triggerreading(TRIGGER_CMD_D); //开始扫描
						
										HAL_Delay(1000);
						
										while(drought_D[2]!=FrameEnder_D)
										{HAL_Delay(100);
											QRread_Init('D');
											HAL_Delay(100);
											Triggerreading(TRIGGER_CMD_D);
											begin_time=HAL_GetTick();
											HAL_Delay(10);
											while(HAL_GetTick()-begin_time<2000);
										};
						drought_C_display_B(drought_D[1]);
						Voice_Select(drought_D[1]-'0');   // 根据 colour_data 数组中的值选择并播放语音。
						HAL_Delay(500);
						begin_time=HAL_GetTick();
						HAL_Delay(10);
						while(HAL_GetTick()-begin_time<800);
						waterpump((int)(drought_D[1]-'0'),1);//控制水泵
						begin_time=HAL_GetTick(); 
						HAL_Delay(10);
						while(HAL_GetTick()-begin_time<1500);
						Servo_Tx(0x5C);
						drought_D[2] = 0;
				 }	

				 
				else if((QRcode_C[i+1])-(QRcode_C[i]) == (-2))
				 {
					Stepping_Motor_Back_Init();
					GO_Distance_hongwai_A(100,10);
					HAL_Delay(140);
					Stepping_Motor_Stopping_Init();
					 HAL_Delay(100);
					red1_falg = 1;
					red1_go = 0;//复位
					 if(ARR[i+1]==0)Servo_Tx(0x3C);
						else Servo_Tx(0x4C);
						HAL_Delay(1200); //等3秒等舵机转过去
										QRread_Init('D');
										HAL_Delay(100); 
					 Triggerreading(TRIGGER_CMD_D); //开始扫描
						
										HAL_Delay(1000);
						
										while(drought_D[2]!=FrameEnder_D)
										{HAL_Delay(100);
											QRread_Init('D');
											HAL_Delay(100);
											Triggerreading(TRIGGER_CMD_D);
											begin_time=HAL_GetTick();
											HAL_Delay(10);
											while(HAL_GetTick()-begin_time<2000);
										};
						drought_C_display_B(drought_D[1]);
						Voice_Select(drought_D[1]-'0');   // 根据 colour_data 数组中的值选择并播放语音。
						HAL_Delay(500);
						begin_time=HAL_GetTick();
						HAL_Delay(10);
						while(HAL_GetTick()-begin_time<800);
						waterpump((int)(drought_D[1]-'0'),1);//控制水泵
						begin_time=HAL_GetTick(); 
						HAL_Delay(10);
						while(HAL_GetTick()-begin_time<1500);
						Servo_Tx(0x5C);
					 drought_D[2] = 0;
				 }		

				 
				else if((QRcode_C[i+1])-(QRcode_C[i]) == (-4))
				 {
					 Stepping_Motor_Back_Init();
					GO_Distance_hongwai_A(200,15);
					 HAL_Delay(140);
					 Stepping_Motor_Stopping_Init();
					 
					 HAL_Delay(100);
						red1_falg = 1;
						red1_go = 0;//复位
					 if(ARR[i+1]==0)Servo_Tx(0x3C);
						else Servo_Tx(0x4C);
						HAL_Delay(1200); //等3秒等舵机转过去
									QRread_Init('D');
										HAL_Delay(100); 
							 Triggerreading(TRIGGER_CMD_D); //开始扫描
						
										HAL_Delay(1000);
						
										while(drought_D[2]!=FrameEnder_D)
										{HAL_Delay(100);
											QRread_Init('D');
											HAL_Delay(100);
											Triggerreading(TRIGGER_CMD_D);
											begin_time=HAL_GetTick();
											HAL_Delay(10);
											while(HAL_GetTick()-begin_time<2000);
										};
						drought_C_display_B(drought_D[1]);
						Voice_Select(drought_D[1]-'0');   // 根据 colour_data 数组中的值选择并播放语音。
						HAL_Delay(500);
						begin_time=HAL_GetTick();
						HAL_Delay(10);
						while(HAL_GetTick()-begin_time<800);
						waterpump((int)(drought_D[1]-'0'),1);//控制水泵
						begin_time=HAL_GetTick(); 
						HAL_Delay(10);
						while(HAL_GetTick()-begin_time<1500);
						Servo_Tx(0x5C);
						drought_D[2] = 0;
				 }	
			 }
				Stepping_Motor_Go_Init();

			 
			 	switch(QRcode_C[6])
			{
			  case 1:Go_Distance(265);break;
				case 3:Go_Distance(165);break;
				case 5:Go_Distance(65);break;
			}
			Stepping_Motor_Stopping_Init();
				
		}
