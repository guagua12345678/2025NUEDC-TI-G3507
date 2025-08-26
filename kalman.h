#ifndef __KALMAN_H__
#define __KALMAN_H__

#include "ti_msp_dl_config.h"
#include <math.h>

extern float K_roll, K_pitch, K_yaw;

void Kalman_Init(void);
void Attitude_Update(float gx, float gy, float gz, float ax, float ay, float az, float dt);

#endif
