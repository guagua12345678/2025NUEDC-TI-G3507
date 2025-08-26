#include "ti_msp_dl_config.h"

#ifndef __ENCODER_H__
#define __ENCODER_H__

extern volatile uint16_t L_rpm;
extern volatile uint16_t R_rpm;

void Encoder_init(void);
void Encoder_50ms_task(void);

#endif