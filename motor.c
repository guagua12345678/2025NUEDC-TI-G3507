#include "ti_msp_dl_config.h"

//use tima0 pa8(left) pa9(right) as pwm out
//use b15 b16 as left direction ctrl
//use b2 b3 as right direction ctrl

void Left_Wheel_Ctrl(uint16_t set_rpm)
{
    set_rpm = (set_rpm > 800) ? 800 : set_rpm;

    if(set_rpm == 0)  //刹车
    {
		DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_15);
	    DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_16);
    }
    else	//正转
    {
		DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_15);
	    DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_16);
		DL_Timer_setCaptureCompareValue(TIMA0,set_rpm,DL_TIMER_CC_0_INDEX);
    }
}

void Right_Wheel_Ctrl(uint16_t set_rpm)
{
    set_rpm = (set_rpm > 800) ? 800 : set_rpm;

    if(set_rpm == 0)//刹车
    {
        DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_2);
	    DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_3);
    }
    else// 正转
    {
        DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_2);
	    DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_3);
		DL_Timer_setCaptureCompareValue(TIMA0,set_rpm,DL_TIMER_CC_1_INDEX);
    }
}

