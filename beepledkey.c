#include "ti_msp_dl_config.h"
#include "delay.h"

volatile uint8_t key1_flag = 0;
volatile uint8_t key2_flag = 0;
volatile uint8_t key3_flag = 0;

volatile uint8_t Beep_Count = 0;
volatile uint8_t Beep_ON_Flag = 0;

void Beep_ONOFF(void)
{
	if(Beep_ON_Flag == 1) {Beep_Count = 11;Beep_ON_Flag = 0;}
	if(Beep_Count > 0) Beep_Count--;
	if(Beep_Count == 10) DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_0);
	if(Beep_Count == 0) DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_0);
}

//定时刷新就行 如果按下会置按键标志位 需要手动清零按键标志
void Key_Read(void)
{
	static uint32_t last_key1_state = 1;
	static uint32_t last_key2_state = 1;
	static uint32_t last_key3_state = 1;
	uint32_t now_key1_state = DL_GPIO_readPins(GPIOB, DL_GPIO_PIN_1);
	uint32_t now_key2_state = DL_GPIO_readPins(GPIOB, DL_GPIO_PIN_11);
	uint32_t now_key3_state = DL_GPIO_readPins(GPIOB, DL_GPIO_PIN_14);
	if(now_key1_state != 0 && last_key1_state == 0) key1_flag = 1;
	if(now_key2_state != 0 && last_key2_state == 0) key2_flag = 1;
	if(now_key3_state != 0 && last_key3_state == 0) key3_flag = 1;
	last_key1_state = now_key1_state;
    last_key2_state = now_key2_state;
	last_key3_state = now_key3_state;
}

void LED_ONOFF(uint8_t status)
{
	if(status == 0) 
	{
		DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_21);
		DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_22);
	}
	else if(status == 1)
	{
		DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_21);
	    DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_22);
	}
	else 
	{
		DL_GPIO_togglePins(GPIOB,DL_GPIO_PIN_21);
	    DL_GPIO_togglePins(GPIOB,DL_GPIO_PIN_22);
	}
}