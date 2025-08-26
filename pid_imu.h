#include "ti_msp_dl_config.h"

#ifndef _pid_imu_H_
#define _pid_imu_H_

void pid_turn_angle(float now_theta, float set_theta);
void Reset_pid_imu(void);

#endif
