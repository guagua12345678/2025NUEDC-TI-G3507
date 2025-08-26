#include "ti_msp_dl_config.h"
#include "delay.h"
#include "motor.h"
#include "encoder.h"
#include "pid.h"
#include "icm42688.h"
#include "pid_imu.h"
#include "tracing.h"
#include "beepledkey.h"
#include "serial.h"
#include "math.h"
#include "oled.h"

volatile uint8_t res = 0;

volatile uint8_t flag_50ms = 0;
volatile float Set_theta = 0.0f;
volatile uint8_t task_count = 0;

volatile uint8_t key_num = 0;
volatile uint8_t N = 0;

volatile uint8_t Task_Process = 0;
#define Task_Ready 0
#define Task_OnGoing 1

volatile uint8_t Task_Status = 0;
#define Task_Tacing 0
#define Task_Turning 1

volatile uint8_t Turned_Count = 0;

void task_ctrl(void)//任务处理
{
	if(Task_Process == Task_Ready)//无任务/完成指定圈数
	{
		if(N) Task_Process = Task_OnGoing;
		pid_set_left_speed(0);
		pid_set_right_speed(0);
	}
	else if(Task_Process == Task_OnGoing)//有任务
	{
		if(Task_Status == Task_Tacing)//总是先进循迹
		{
			tracing_ctrl(130.0f);
			if(Tracing_None_Count > 4)//该转弯了
			{
				if(--N == 0) //回空任务
				{
					Reset_pid_speed();
					Task_Process = Task_Ready;
					Task_Status = Task_Tacing;
				}
				else//转弯去
				{
					Reset_left_speed();
					Task_Status = Task_Turning;
				}
				Set_theta = yaw + 90.0f;
			}
		}
		else if(Task_Status == Task_Turning)//转弯
		{
			Read_gpio_input();
			pid_turn_angle(yaw,Set_theta);
			if(fabs(Set_theta-yaw) <= 3.0f || L1 == 1 || L3 == 1 || L2 == 1)//退出转弯
			{
				Reset_pid_imu();
				Task_Status = Task_Tacing;
			}
		}
	}
}

int main()
{
	SYSCFG_DL_init();
	NVIC_ClearPendingIRQ(TIMG12_INT_IRQn);
    NVIC_EnableIRQ(TIMG12_INT_IRQn);   
	hc05_init();
	Encoder_init();
	OLED_Init();
	res = ICM42688_Init(3,3,8,8,3,3,2,1,1);
	if(res) 
	{
		OLED_ShowString(80,0,"ok",8,1);
		OLED_Refresh();
	}
	
    while (1)
    {
		if(flag_50ms == 1)
		{
			ICM42688_Read();
			Encoder_50ms_task();
			
			Key_Read();
			if(key1_flag == 1) {key1_flag = 0;N = key_num * 4 + 1;}
			if(key2_flag == 1) {key2_flag = 0;if(key_num > 0) key_num--;}
			if(key3_flag == 1) {key3_flag = 0;if(key_num < 5) key_num++;}
			
			//VOFA_Send(yaw,Tracing_Return);			
			OLED_ShowChar(0,0,'N',8,1);
			OLED_ShowNum(10,0,N,1,8,1);
			OLED_ShowChar(30,0,'K',8,1);
			OLED_ShowNum(40,0,key_num,1,8,1);
			OLED_Refresh();
			
			task_ctrl();
			
			LED_ONOFF(2);
			flag_50ms = 0;
		}
	}
}

void TIMG12_INST_IRQHandler(void) //@50ms
{
    switch( DL_Timer_getPendingInterrupt(TIMG12) )
    {
        case DL_TIMER_IIDX_ZERO:
			flag_50ms = 1;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
            break;

        default:
            break;
    }
}


