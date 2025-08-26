#include "ti_msp_dl_config.h"

#ifndef __PID_SPEED_H__
#define __PID_SPEED_H__

void Reset_pid_speed(void);
void pid_set_left_speed(float set_rpm_L);
void pid_set_right_speed(float set_rpm_R);
void Reset_left_speed(void);

#endif
