#include "ti_msp_dl_config.h"

#ifndef __BEEPLEDKEY_H__
#define __BEEPLEDKEY_H__

extern volatile uint8_t key1_flag;
extern volatile uint8_t key2_flag;
extern volatile uint8_t key3_flag;
extern volatile uint8_t Beep_ON_Flag;

void Beep_ONOFF(void);
void Key_Read(void);
void LED_ONOFF(uint8_t status);


#endif