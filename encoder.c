#include "ti_msp_dl_config.h"

#define PulseToRpm 1.15385f

volatile uint16_t temp_L_pulse = 0;
volatile uint16_t temp_R_pulse = 0;

volatile uint16_t L_rpm = 0;
volatile uint16_t R_rpm = 0;

void Encoder_init(void)
{
	NVIC_ClearPendingIRQ(GPIOB_INT_IRQn);
	NVIC_EnableIRQ(GPIOB_INT_IRQn);
}

void Encoder_50ms_task(void)
{
	L_rpm = (uint16_t)(temp_L_pulse * PulseToRpm);
	R_rpm = (uint16_t)(temp_R_pulse * PulseToRpm);
	temp_L_pulse = 0;
	temp_R_pulse = 0;
}

void GROUP1_IRQHandler(void)
{
	uint32_t gpio_status = DL_GPIO_getEnabledInterruptStatus(GPIOB,DL_GPIO_PIN_6|DL_GPIO_PIN_7|DL_GPIO_PIN_8|DL_GPIO_PIN_9);
	if((gpio_status & DL_GPIO_PIN_6) == DL_GPIO_PIN_6) temp_L_pulse++;
	if((gpio_status & DL_GPIO_PIN_7) == DL_GPIO_PIN_7) temp_L_pulse++;
	if((gpio_status & DL_GPIO_PIN_8) == DL_GPIO_PIN_8) temp_R_pulse++;
	if((gpio_status & DL_GPIO_PIN_9) == DL_GPIO_PIN_9) temp_R_pulse++;
	DL_GPIO_clearInterruptStatus(GPIOB,DL_GPIO_PIN_6|DL_GPIO_PIN_7|DL_GPIO_PIN_8|DL_GPIO_PIN_9);
}
