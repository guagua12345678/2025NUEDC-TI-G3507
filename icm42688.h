#include "ti_msp_dl_config.h"

#ifndef __ICM42688_H__
#define __ICM42688_H__

#define u8 uint8_t

extern volatile float g_z;
extern volatile float yaw;

#define ICM42688_DEVICE_CONFIG             0x11
#define ICM42688_DRIVE_CONFIG              0x13
#define ICM42688_INT_CONFIG                0x14
#define ICM42688_FIFO_CONFIG               0x16
#define ICM42688_TEMP_DATA1                0x1D
#define ICM42688_TEMP_DATA0                0x1E
#define ICM42688_ACCEL_DATA_X1             0x1F
#define ICM42688_ACCEL_DATA_X0             0x20
#define ICM42688_ACCEL_DATA_Y1             0x21
#define ICM42688_ACCEL_DATA_Y0             0x22
#define ICM42688_ACCEL_DATA_Z1             0x23
#define ICM42688_ACCEL_DATA_Z0             0x24
#define ICM42688_GYRO_DATA_X1              0x25
#define ICM42688_GYRO_DATA_X0              0x26
#define ICM42688_GYRO_DATA_Y1              0x27
#define ICM42688_GYRO_DATA_Y0              0x28
#define ICM42688_GYRO_DATA_Z1              0x29
#define ICM42688_GYRO_DATA_Z0              0x2A
#define ICM42688_INT_STATUS                0x2D
#define ICM42688_PWR_MGMT0                 0x4E
#define ICM42688_GYRO_CONFIG0              0x4F
#define ICM42688_ACCEL_CONFIG0             0x50
#define ICM42688_GYRO_CONFIG1              0x51
#define ICM42688_GYRO_ACCEL_CONFIG0        0x52
#define ICM42688_ACCEL_CONFIG1             0x53
#define ICM42688_INT_CONFIG0               0x63
#define ICM42688_INT_CONFIG1               0x64
#define ICM42688_INT_SOURCE0               0x65
#define ICM42688_WHO_AM_I                  0x75
#define ICM42688_REG_BANK_SEL              0x76

/* 
bw_filter : 低通滤波器 高->低毛刺导致高延迟
ui_filter : 平滑滤波器 高->平滑增加延迟

@g_dps:陀螺仪量程(度每秒)
	0-2000dps 1-1000dps 2-500dps 3-250dps 
	4-125dps 5-62.5dps 6-31.25dps 7-15.625dps

@a_rge:加速度计量程(g)
	0-16g 1-8g 2-4g 3-2g

@g_freq:陀螺仪输出频率
	1-32khz 2-16khz 3-8khz 4-4khz 5-2khz 6-1khz 7-200hz
	8-100hz 9-50hz 10-25hz 11-12.5hz 15-500hz

@a_freq:加速度计输出频率
	1-32khz 2-16khz 3-8khz 4-4khz 5-2khz 6-1khz 7-200hz 8-100hz
	9-50hz 10-25hz 11-12.5hz 12-6.25Hz 13-3.125Hz 14-1.5625Hz 15-500Hz

@g_bw_filt:陀螺仪低通滤波器
@a_bw_filt:加速度计低通滤波器
	高阶->平滑增加延迟
	0  BW=Freq/2                高带宽
	1  BW=max(400Hz, Freq)/4
	2  BW=max(400Hz, Freq)/5 
	3  BW=max(400Hz, Freq)/8 
	4  BW=max(400Hz, Freq)/10 
	5  BW=max(400Hz, Freq)/16 
	6  BW=max(400Hz, Freq)/20 
	7  BW=max(400Hz, Freq)/40   高滤波
	14 BW=max(400Hz, Freq)      低延迟
	15 BW=max(200Hz, 8*Freq)    低延迟

@t_bw_filt:温度传感器低通滤波器
	0-4000Hz (延迟0.125ms)
	1-170Hz  (延迟1ms)
	2-82Hz   (延迟2ms)
	3-40Hz   (延迟4ms)
	4-20Hz   (延迟8ms)
	5-10Hz   (延迟16ms)
	6-5Hz    (延迟32ms)
	
@g_ui_filt:陀螺仪平滑滤波器
@a_ui_filt:加速度计平滑滤波器
	0-1阶 1-2阶 2-3阶
	
@return 1-ok 0-error
*/

u8 ICM42688_Init(u8 g_dps,u8 a_rge,u8 g_freq,u8 a_freq,u8 g_bw_filt,u8 a_bw_filt,u8 t_bw_filt,u8 g_ui_filt,u8 a_ui_filt);
void ICM42688_Read(void);
	
#endif
