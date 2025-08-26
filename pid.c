#include "ti_msp_dl_config.h"
#include "motor.h"
#include "encoder.h"

// 全局PID参数
float Kp_Encoder = 2.5f;       // 比例系数
float Ki_Encoder = 0.5f;       // 积分系数
float Kd_Encoder = 0.05f;      // 微分系数

float max_increase = 10.0f;    // 增量限幅
float max_output = 800.0f;     // 输出限幅

// 电机历史误差
float L_prev_error = 0.0f;
float L_prev_prev_error = 0.0f;
float R_prev_error = 0.0f;
float R_prev_prev_error = 0.0f;

// 电机转速
float L_speed = 0.0f;
float R_speed = 0.0f;

void Reset_pid_speed(void)
{
	L_prev_error = 0.0f;
	L_prev_prev_error = 0.0f;
	R_prev_error = 0.0f;
	R_prev_prev_error = 0.0f;

	L_speed = 0.0f;
	R_speed = 0.0f;
	Left_Wheel_Ctrl(0);
	Right_Wheel_Ctrl(0);
}

void Reset_left_speed(void)
{
	L_prev_error = 0.0f;
	L_prev_prev_error = 0.0f;
	L_speed = 0.0f;
	Left_Wheel_Ctrl(0);
}

// 左电机速度控制
void pid_set_left_speed(float set_rpm_L) 
{
    // 计算误差
    float error_L = set_rpm_L - L_rpm;
    // 计算增量
    float delta_L = Kp_Encoder * (error_L - L_prev_error)
                  + Ki_Encoder *  error_L
                  + Kd_Encoder * (error_L - 2*L_prev_error + L_prev_prev_error);
    
    // 输出限幅
    if(delta_L > max_increase) delta_L = max_increase;
    else if(delta_L < -max_increase) delta_L = -max_increase;
    
    // 更新历史误差
    L_prev_prev_error = L_prev_error;
    L_prev_error = error_L;
    L_speed += delta_L;
    
    if(L_speed > max_output) L_speed = max_output;
    else if(L_speed < 0) L_speed = 0;

    Left_Wheel_Ctrl((uint16_t)L_speed);
}

// 右电机速度控制
void pid_set_right_speed(float set_rpm_R) 
{
    // 计算误差
    float error_R = set_rpm_R - R_rpm;
    // 计算增量
    float delta_R = Kp_Encoder * (error_R - R_prev_error)
                  + Ki_Encoder *  error_R
                  + Kd_Encoder * (error_R - 2*R_prev_error + R_prev_prev_error);
    
    // 输出限幅
    if(delta_R > max_increase) delta_R = max_increase;
    else if(delta_R < -max_increase) delta_R = -max_increase;
    
    // 更新历史误差
    R_prev_prev_error = R_prev_error;
    R_prev_error = error_R;
    R_speed += delta_R;
    
    if(R_speed > max_output) R_speed = max_output;
    else if(R_speed < 0) R_speed = 0;

    Right_Wheel_Ctrl((uint16_t)R_speed);
}
