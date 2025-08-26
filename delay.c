#include "ti_msp_dl_config.h"

void delay_us(uint16_t us)
{
    SysTick->LOAD = 32 * us;
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;
    while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
    SysTick->CTRL = 0;
}

void delay_ms(uint16_t ms)
{
	while(ms--)
	{
		delay_us(1000);
	}
}

void delay_s(uint16_t sec)
{
	while(sec--)
	{
		delay_ms(1000);
	}
}
