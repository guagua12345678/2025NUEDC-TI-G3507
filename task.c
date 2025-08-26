#include "ti_msp_dl_config.h"
#include "delay.h"
#include "motor.h"
#include "encoder.h"
#include "oled.h"
#include "pid.h"
#include "icm42688.h"
#include "pid_imu.h"
#include "tracing.h"
#include "beepledkey.h"
#include "math.h"

//void task0(void)
//{
////	Key_Read_Task();
////	OLED_ShowChar(0,0,'K',8,1);
////	OLED_ShowNum(6,0,Key_Num,1,8,1);
////	OLED_ShowChar(88,0,'T',8,1);
////	OLED_ShowNum(94,0,Task_Num,1,8,1);
////	OLED_Refresh();
//}

//void task1(void)
//{
//	tracing_read();
//	if(output == 99) Pid_IMU_Go_Straight(200,L_rpm,R_rpm,yaw,0.0f);
//	else 
//	{
//		Beep_ON_Flag = 1;
//		Reset_pid_straight();
//		Reset_pid_encoder();	
//		Left_Wheel_Ctrl(0);
//		Right_Wheel_Ctrl(0);
//		Task_Num = 0;
//	}
//}
////22222222222222222222222222222222222222222222222222222222222222222222
//void task2(void)
//{
//	static uint8_t once_flag = 0;
//	if(once_flag == 0){yaw = 0;once_flag = 1;}
//	else if(once_flag == 1) 
//	{
//		tracing_read();
//		if(output == 99) 
//			Pid_IMU_Go_Straight(200,L_rpm,R_rpm,yaw,0.0f);
//		else
//		{
//			Beep_ON_Flag = 1;
//			Reset_pid_straight();
//			Reset_pid_encoder();
//			Left_Wheel_Ctrl(0);
//			Right_Wheel_Ctrl(0);
//			once_flag = 2;
//		}
//	}
//	else if(once_flag == 2)
//	{
//		tracing_task(L_rpm,R_rpm);
//		if(output == 99 && fabs(yaw) > 177.0f)
//		{
//			once_flag = 3;
//			Beep_ON_Flag = 1;
//			Reset_tracing();
//			Reset_pid_encoder();
//			Left_Wheel_Ctrl(0);
//			Right_Wheel_Ctrl(0);
//		}
//	}
//	else if(once_flag == 3)
//	{
//		tracing_read();
//		if(output == 99) 
//			Pid_IMU_Go_Straight(200,L_rpm,R_rpm,yaw,-180.0f);
//		else
//		{
//			Beep_ON_Flag = 1;
//			Reset_pid_straight();
//			Reset_pid_encoder();
//			Left_Wheel_Ctrl(0);
//			Right_Wheel_Ctrl(0);
//			once_flag = 4;
//		}
//	}
//	else if(once_flag == 4)
//	{
//		tracing_task(L_rpm,R_rpm);
//		if(output == 99 && fabs(yaw) > 353.0f)
//		{
//			once_flag = 5;
//			Reset_pid_encoder();
//			Left_Wheel_Ctrl(0);
//			Right_Wheel_Ctrl(0);
//			Beep_ON_Flag = 1;
//			Reset_tracing();
//			Task_Num = 0;
//		}
//	}
//}
////333333333333333333333333333333333333333333333333333333333333333333333
//void task3(void)
//{
//	static uint8_t once_flag = 0;
//	if(once_flag == 0){yaw = 0;once_flag = 1;}
//	else if(once_flag == 1) 
//	{
//		Pid_IMU_Turn_Angle(L_rpm,R_rpm,yaw,-38.0f);
//		if(yaw<-37.0f) 
//		{
//			once_flag = 2;
//			Reset_pid_angle();
//			Reset_pid_encoder();
//			Left_Wheel_Ctrl(0);
//			Right_Wheel_Ctrl(0);
//		}
//	}
//	else if(once_flag == 2)
//	{
//		tracing_read();
//		if(output == 99) 
//			Pid_IMU_Go_Straight(200,L_rpm,R_rpm,yaw,-38.0f);
//		else
//		{
//			Beep_ON_Flag = 1;
//			Reset_pid_straight();
//			Reset_pid_encoder();
//			Left_Wheel_Ctrl(0);
//			Right_Wheel_Ctrl(0);
//			once_flag = 3;
//		}
//	}
//	else if(once_flag == 3)
//	{
//		Pid_IMU_Turn_Angle(L_rpm,R_rpm,yaw,0.0f);
//		if(yaw>-1.0f) 
//		{
//			once_flag = 4;
//			Reset_pid_angle();
//			Reset_pid_encoder();
//			Left_Wheel_Ctrl(0);
//			Right_Wheel_Ctrl(0);
//		}
//	}
//	else if(once_flag == 4)
//	{
//		tracing_tsk(L_rpm,R_rpm);
//		if(output == 99 && fabs(yaw) > 177.0f)
//		{
//			once_flag = 5;
//			Beep_ON_Flag = 1;
//			Reset_tracing();
//			Reset_pid_encoder();
//			Left_Wheel_Ctrl(0);
//			Right_Wheel_Ctrl(0);
//		}
//	}
//	else if(once_flag == 5)
//	{
//		Pid_IMU_Turn_Angle(L_rpm,R_rpm,yaw,219.0f);
//		if(fabs(yaw) > 218.0f) 
//		{
//			once_flag = 6;
//			Reset_pid_angle();
//			Reset_pid_encoder();
//			Left_Wheel_Ctrl(0);
//			Right_Wheel_Ctrl(0);
//		}
//	}
//	else if(once_flag == 6)
//	{
//		tracing_read();
//		if(output == 99) 
//			Pid_IMU_Go_Straight(200,L_rpm,R_rpm,yaw,219.0f);
//		else
//		{
//			Beep_ON_Flag = 1;
//			Reset_pid_straight();
//			Reset_pid_encoder();
//			Left_Wheel_Ctrl(0);
//			Right_Wheel_Ctrl(0);
//			once_flag = 7;
//		}
//	}
//	else if(once_flag == 7)
//	{
//		Pid_IMU_Turn_Angle(L_rpm,R_rpm,yaw,180.0f);
//		if(yaw<181.0f) 
//		{
//			once_flag = 8;
//			Reset_pid_angle();
//			Reset_pid_encoder();
//			Left_Wheel_Ctrl(0);
//			Right_Wheel_Ctrl(0);
//		}
//	}
//	else if(once_flag == 8)
//	{
//		tracing_task(L_rpm,R_rpm);
//		if(output == 99 && fabs(yaw) < 5.0f)
//		{
//			once_flag = 9;
//			Beep_ON_Flag = 1;
//			Reset_tracing();
//			Reset_pid_encoder();
//			Left_Wheel_Ctrl(0);
//			Right_Wheel_Ctrl(0);
//			Task_Num = 0;
//		}
//	}
//}

////444444444444444444444444444444444444444444444444444
//void task4(void)
//{
//	static uint8_t once_flag = 0;
//	static uint8_t count = 0;
//	if(count <= 3)
//	{
//		if(once_flag == 0){yaw = 0;once_flag = 1;}
//		else if(once_flag == 1) 
//		{
//			Pid_IMU_Turn_Angle(L_rpm,R_rpm,yaw,-38.0f);
//			if(yaw<-37.0f) 
//			{
//				once_flag = 2;
//				Reset_pid_angle();
//				Reset_pid_encoder();
//				Left_Wheel_Ctrl(0);
//				Right_Wheel_Ctrl(0);
//			}
//		}
//		else if(once_flag == 2)
//		{
//			tracing_read();
//			if(output == 99) 
//				Pid_IMU_Go_Straight(200,L_rpm,R_rpm,yaw,-38.0f);
//			else
//			{
//				Beep_ON_Flag = 1;
//				Reset_pid_straight();
//				Reset_pid_encoder();
//				Left_Wheel_Ctrl(0);
//				Right_Wheel_Ctrl(0);
//				once_flag = 3;
//			}
//		}
//		else if(once_flag == 3)
//		{
//			Pid_IMU_Turn_Angle(L_rpm,R_rpm,yaw,0.0f);
//			if(yaw>-1.0f) 
//			{
//				once_flag = 4;
//				Reset_pid_angle();
//				Reset_pid_encoder();
//				Left_Wheel_Ctrl(0);
//				Right_Wheel_Ctrl(0);
//			}
//		}
//		else if(once_flag == 4)
//		{
//			tracing_tsk(L_rpm,R_rpm);
//			if(output == 99 && fabs(yaw) > 177.0f)
//			{
//				once_flag = 5;
//				Beep_ON_Flag = 1;
//				Reset_tracing();
//				Reset_pid_encoder();
//				Left_Wheel_Ctrl(0);
//				Right_Wheel_Ctrl(0);
//			}
//		}
//		else if(once_flag == 5)
//		{
//			Pid_IMU_Turn_Angle(L_rpm,R_rpm,yaw,219.0f);
//			if(fabs(yaw) > 218.0f) 
//			{
//				once_flag = 6;
//				Reset_pid_angle();
//				Reset_pid_encoder();
//				Left_Wheel_Ctrl(0);
//				Right_Wheel_Ctrl(0);
//			}
//		}
//		else if(once_flag == 6)
//		{
//			tracing_read();
//			if(output == 99) 
//				Pid_IMU_Go_Straight(200,L_rpm,R_rpm,yaw,219.0f);
//			else
//			{
//				Beep_ON_Flag = 1;
//				Reset_pid_straight();
//				Reset_pid_encoder();
//				Left_Wheel_Ctrl(0);
//				Right_Wheel_Ctrl(0);
//				once_flag = 7;
//			}
//		}
//		else if(once_flag == 7)
//		{
//			Pid_IMU_Turn_Angle(L_rpm,R_rpm,yaw,180.0f);
//			if(yaw<181.0f) 
//			{
//				once_flag = 8;
//				Reset_pid_angle();
//				Reset_pid_encoder();
//				Left_Wheel_Ctrl(0);
//				Right_Wheel_Ctrl(0);
//			}
//		}
//		else if(once_flag == 8)
//		{
//			tracing_task(L_rpm,R_rpm);
//			if(output == 99 && fabs(yaw) < 5.0f)
//			{
//				count++;
//				once_flag = 0;
//				Beep_ON_Flag = 1;
//				Reset_tracing();
//				Reset_pid_encoder();
//				Left_Wheel_Ctrl(0);
//				Right_Wheel_Ctrl(0);
//			}
//		}
//	}
//}
