#include "ti_msp_dl_config.h"

#ifndef __TRACING_H__
#define __TRACING_H__

extern volatile float Tracing_Return;
extern volatile uint16_t Tracing_None_Count;
extern volatile int8_t L3,L2,L1,M,R1,R2,R3;

void Read_gpio_input(void);
void tracing_ctrl(float Basic_speed);
	
#endif