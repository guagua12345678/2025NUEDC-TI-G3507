#include "ti_msp_dl_config.h"
#include "icm42688.h"
#include <math.h>

// 姿态四元数
float kalman_q0 = 1.0f;
float kalman_q1 = 0.0f;
float kalman_q2 = 0.0f;
float kalman_q3 = 0.0f;

// 欧拉角 (弧度)
float kalman_roll = 0.0f;
float kalman_pitch = 0.0f;
float kalman_yaw = 0.0f;

//最终结果
float K_roll = 0.0f;
float K_pitch = 0.0f;
float K_yaw = 0.0f;

// 卡尔曼滤波器状态变量 (Roll轴)
static float kalman_roll_angle = 0.0f;
static float kalman_roll_bias = 0.0f;
static float kalman_roll_P[2][2] = {{0}};

// 卡尔曼滤波器状态变量 (Pitch轴)
static float kalman_pitch_angle = 0.0f;
static float kalman_pitch_bias = 0.0f;
static float kalman_pitch_P[2][2] = {{0}};

// 卡尔曼滤波器参数
#define Q_ANGLE  0.001f   // 角度过程噪声
#define Q_GYRO   0.003f   // 陀螺仪过程噪声
#define R_ACCEL  0.03f    // 加速度计观测噪声

// 初始化卡尔曼滤波器
void Kalman_Init(void) {
    // Roll轴初始化
    kalman_roll_angle = 0.0f;
    kalman_roll_bias = 0.0f;
    kalman_roll_P[0][0] = 0.0f;
    kalman_roll_P[0][1] = 0.0f;
    kalman_roll_P[1][0] = 0.0f;
    kalman_roll_P[1][1] = 0.0f;
    
    // Pitch轴初始化
    kalman_pitch_angle = 0.0f;
    kalman_pitch_bias = 0.0f;
    kalman_pitch_P[0][0] = 0.0f;
    kalman_pitch_P[0][1] = 0.0f;
    kalman_pitch_P[1][0] = 0.0f;
    kalman_pitch_P[1][1] = 0.0f;
    
    // 姿态四元数初始化
    kalman_q0 = 1.0f;
    kalman_q1 = 0.0f;
    kalman_q2 = 0.0f;
    kalman_q3 = 0.0f;
    
    // 欧拉角初始化
    kalman_roll = 0.0f;
    kalman_pitch = 0.0f;
    kalman_yaw = 0.0f;
}

// 卡尔曼滤波更新 (单轴)
static float Kalman_Update(float *angle, float *bias, float P[2][2], 
                          float accel_angle, float gyro_rate, float dt) {
    // 1. 预测状态
    *angle += (gyro_rate - *bias) * dt;
    
    // 2. 更新协方差矩阵
    P[0][0] += dt * (dt * P[1][1] - P[0][1] - P[1][0] + Q_ANGLE);
    P[0][1] -= dt * P[1][1];
    P[1][0] -= dt * P[1][1];
    P[1][1] += Q_GYRO * dt;
    
    // 3. 计算卡尔曼增益
    float S = P[0][0] + R_ACCEL;
    float K0 = P[0][0] / S;
    float K1 = P[1][0] / S;
    
    // 4. 更新状态估计
    float y = accel_angle - *angle;
    *angle += K0 * y;
    *bias += K1 * y;
    
    // 5. 更新协方差
    float P00_temp = P[0][0];
    float P01_temp = P[0][1];
    
    P[0][0] -= K0 * P00_temp;
    P[0][1] -= K0 * P01_temp;
    P[1][0] -= K1 * P00_temp;
    P[1][1] -= K1 * P01_temp;
    
    return *angle;
}

// 姿态更新函数
void Attitude_Update(float gx, float gy, float gz, float ax, float ay, float az, float dt) {
    static uint8_t isKalmanInit = 0;
    
    // 初始化卡尔曼滤波器 (只初始化一次)
    if (!isKalmanInit) {
        Kalman_Init();
        isKalmanInit = 1;
    }
    
    // 1. 归一化加速度计数据
    float norm = sqrt(ax*ax + ay*ay + az*az);
    if (norm == 0.0f) return;
    ax /= norm;
    ay /= norm;
    az /= norm;
    
    // 2. 计算加速度计姿态角
    float accel_roll = atan2(ay, az);
    float accel_pitch = -atan2(ax, sqrt(ay*ay + az*az));
    
    // 3. 卡尔曼滤波融合陀螺仪和加速度计
    float roll = Kalman_Update(&kalman_roll_angle,&kalman_roll_bias,kalman_roll_P,accel_roll,gx,dt);
    float pitch = Kalman_Update(&kalman_pitch_angle,&kalman_pitch_bias,kalman_pitch_P,accel_pitch,gy,dt);
    
    // 4. 使用四元数微分方程更新姿态
    float q0 = kalman_q0;
    float q1 = kalman_q1;
    float q2 = kalman_q2;
    float q3 = kalman_q3;
    
    // 陀螺仪测量值转换为弧度/秒
    gx *= 0.0174533f; // deg/s to rad/s
    gy *= 0.0174533f;
    gz *= 0.0174533f;
    
    // 四元数微分方程
    float qDot0 = 0.5f * (-q1 * gx - q2 * gy - q3 * gz);
    float qDot1 = 0.5f * (q0 * gx + q2 * gz - q3 * gy);
    float qDot2 = 0.5f * (q0 * gy - q1 * gz + q3 * gx);
    float qDot3 = 0.5f * (q0 * gz + q1 * gy - q2 * gx);
    
    // 积分四元数
    q0 += qDot0 * dt;
    q1 += qDot1 * dt;
    q2 += qDot2 * dt;
    q3 += qDot3 * dt;
    
    // 归一化四元数
    norm = sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
    if (norm == 0.0f) return;
    q0 /= norm;
    q1 /= norm;
    q2 /= norm;
    q3 /= norm;
    
    // 保存更新后的四元数
    kalman_q0 = q0;
    kalman_q1 = q1;
    kalman_q2 = q2;
    kalman_q3 = q3;
    
    // 5. 四元数转欧拉角
    kalman_roll = atan2(2.0f * (q0*q1 + q2*q3), 1.0f - 2.0f*(q1*q1 + q2*q2));
    kalman_pitch = asin(2.0f * (q0*q2 - q3*q1));
    kalman_yaw = atan2(2.0f * (q0*q3 + q1*q2), 1.0f - 2.0f*(q2*q2 + q3*q3));
	
	K_roll = kalman_roll * 57.29578f;
	K_pitch = kalman_pitch * 57.29578f;
	K_yaw = kalman_yaw * 57.29578f;
}
