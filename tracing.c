#include "ti_msp_dl_config.h"
#include "pid.h"

volatile float Tracing_Return = 0.0f;
volatile uint8_t Tracing_None_Count = 0;
volatile int8_t L3=0,L2=0,L1=0,M=0,R1=0,R2=0,R3=0;

#define Max_factor 9.0f
#define Mid_factor 6.0f
#define Min_factor 3.0f

//right:+,left-.
void Read_gpio_input(void)
{
	static float last_tracing_return = 0.0f;
	if( DL_GPIO_readPins(GPIOA, DL_GPIO_PIN_22) != 0 ) R3=1;else R3=0;
	if( DL_GPIO_readPins(GPIOA, DL_GPIO_PIN_17) != 0 ) R2=1;else R2=0;
	if( DL_GPIO_readPins(GPIOA, DL_GPIO_PIN_16) != 0 ) R1=1;else R1=0;
	if( DL_GPIO_readPins(GPIOA, DL_GPIO_PIN_15) != 0 ) M =1;else M =0;
	if( DL_GPIO_readPins(GPIOA, DL_GPIO_PIN_14) != 0 ) L1=1;else L1=0;
	if( DL_GPIO_readPins(GPIOB, DL_GPIO_PIN_18) != 0 ) L2=1;else L2=0;
	if( DL_GPIO_readPins(GPIOB, DL_GPIO_PIN_17) != 0 ) L3=1;else L3=0;
	
	if(R3+R2+R1+M+L1+L2+L3==0) 
		Tracing_Return = last_tracing_return;
	else if(R3+R2+R1+M+L1+L2+L3==1) 
		Tracing_Return = Max_factor *(R3 - L3) + Mid_factor*(R2 - L2) + Min_factor*(R1 - L1);
	else if(R3+R2+R1+M+L1+L2+L3==2)
	{
		if(R3+R2 == 2)        Tracing_Return = (Mid_factor+Max_factor)*0.5f;
		else if(R2+R1 == 2)   Tracing_Return = (Mid_factor+Min_factor)*0.5f;
		else if(R1+M == 2)    Tracing_Return = (Min_factor)*0.5f;
		else if(M+L1 == 2)    Tracing_Return = (Min_factor)*-0.5f;
		else if(L1+L2 == 2)   Tracing_Return = (Mid_factor+Min_factor)*-0.5f;
		else if(L2+L3 == 2)   Tracing_Return = (Mid_factor+Max_factor)*-0.5f;
		else Tracing_Return = Tracing_Return;
	}
	else if(R3+R2+R1+M+L1+L2+L3==3)
	{
		if(R3+R2+R1 == 3) Tracing_Return = Mid_factor;
		else if(R2+R1+M == 3) Tracing_Return = Min_factor;
		else if(M+L1+L2 == 3) Tracing_Return = -Min_factor;
		else if(L1+L2+L3 == 3) Tracing_Return = -Mid_factor;
		else if(L1+M+R1 == 3) Tracing_Return = 0.0f;
		else Tracing_Return = Tracing_Return;
	}
	else Tracing_Return = last_tracing_return;
	
	if(R3+R2+R1+M+L1+L2+L3==0) Tracing_None_Count++;else Tracing_None_Count = 0;
	
	last_tracing_return = Tracing_Return;
}

float Tracing_Kp = 3.0f;
float T_max_output = 50.0f;

void tracing_ctrl(float Basic_speed)
{
	static uint8_t last_error = 0;
	Read_gpio_input();

    float delta_T = Tracing_Return * Tracing_Kp;

    if(delta_T > T_max_output) delta_T = T_max_output;
    else if(delta_T < -T_max_output) delta_T = -T_max_output;
	
	last_error = Tracing_Return;
	
	pid_set_left_speed(Basic_speed + delta_T);
	pid_set_right_speed(Basic_speed - delta_T);
}
