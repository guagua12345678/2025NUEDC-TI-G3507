#include "ti_msp_dl_config.h"
#include "math.h"
#include "pid.h"

// 旋转PID参数
float Kp_Turn = 0.0f;         // 旋转比例系数
float Ki_Turn = 1.0f;         // 旋转积分系数
float Kd_Turn = 0.0f;         // 旋转微分系数

#define Angle_Tolerance 1.0f   // 角度容差
#define MAX_TURN_SPEED  100.0f // 最大旋转速度 (RPM)

// 旋转状态变量
float prev_turn_error = 0.0f;
float prev_prev_turn_error = 0.0f;

void Reset_pid_imu(void)
{
	prev_turn_error = 0.0f;
	prev_prev_turn_error = 0.0f;
}

// 原地旋转函数 (+-180度范围)
void pid_turn_angle(float now_theta, float set_theta)
{
    // 1.计算角度误差并归一化到[-180, 180]
    float error = now_theta - set_theta;
    while (error > 180.0f) error -= 360.0f;
    while (error < -180.0f) error += 360.0f;
    
    // 3.计算PID增量
    float delta = Kp_Turn * (error - prev_turn_error)
                + Ki_Turn *  error
                + Kd_Turn * (error - 2*prev_turn_error + prev_prev_turn_error);
    
    // 4.限幅处理
    if (delta > MAX_TURN_SPEED) delta = MAX_TURN_SPEED;
    else if (delta < -MAX_TURN_SPEED) delta = -MAX_TURN_SPEED;
    
    // 5.更新历史误差
    prev_prev_turn_error = prev_turn_error;
    prev_turn_error = error;
    
    // 6.执行旋转策略
    if (error > 0) 
	{ 
        pid_set_left_speed(fabs(delta));
        pid_set_right_speed(0.0f);
    } 
	else 
	{
        pid_set_left_speed(0.0f);
        pid_set_right_speed(fabs(delta));
    }
}
