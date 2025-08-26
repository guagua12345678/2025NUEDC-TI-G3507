#include "ti_msp_dl_config.h"
#include "icm42688.h"
#include "delay.h"

// 软件SPI引脚定义
#define Set_NSS 	DL_GPIO_setPins(GPIOA,DL_GPIO_PIN_24);
#define Clear_NSS 	DL_GPIO_clearPins(GPIOA,DL_GPIO_PIN_24);
#define Set_SCLK 	DL_GPIO_setPins(GPIOA,DL_GPIO_PIN_25);
#define Clear_SCLK 	DL_GPIO_clearPins(GPIOA,DL_GPIO_PIN_25);
#define Set_MOSI 	DL_GPIO_setPins(GPIOA,DL_GPIO_PIN_26);
#define Clear_MOSI 	DL_GPIO_clearPins(GPIOA,DL_GPIO_PIN_26);
#define Read_MISO 	DL_GPIO_readPins(GPIOA, DL_GPIO_PIN_27)

volatile int16_t real_g_z = 0;
volatile int16_t offset_g_z = 0;
volatile float g_z = 0.0f;
volatile float yaw = 0.0f;

//延时
void Spi_Delay_40ns(void)
{
	__nop();__nop();__nop();__nop();__nop();
}

// 软件SPI初始化函数
void SoftSPI_Init(void)
{
    Set_NSS
    Clear_SCLK
}

// 软件SPI传输函数
uint8_t SoftSPI_Transfer(uint8_t data)
{
    uint8_t received = 0;
    
    for(int i = 0; i < 8; i++)
    {
        if(data & 0x80) Set_MOSI
        else Clear_MOSI
        data <<= 1;

        Spi_Delay_40ns();
        Set_SCLK
		
        Spi_Delay_40ns();
        received <<= 1;
        if(Read_MISO)
            received |= 0x01;
		
        Spi_Delay_40ns();
        Clear_SCLK
        Spi_Delay_40ns();
    }
    return received;
}

// SPI写寄存器函数
void SoftSPI_WriteReg(uint8_t reg, uint8_t value)
{
    Clear_NSS
    SoftSPI_Transfer(reg & 0x7F);
    SoftSPI_Transfer(value);
    Set_NSS
}

// SPI读寄存器函数
uint8_t SoftSPI_ReadReg(uint8_t reg)
{
    uint8_t value;
    Clear_NSS
    SoftSPI_Transfer(reg | 0x80);
    value = SoftSPI_Transfer(0x00);
	Set_NSS
    return value;
}

//我是谁
uint8_t ICM42688_WhoAmI(void)
{
	uint8_t temp = 0;
	temp = SoftSPI_ReadReg(ICM42688_WHO_AM_I); 
	if(temp == 0x47) return 1;
	else return 0;
}

void ICM42688_Gyro_Settings(uint8_t dps, uint8_t freq)
{
    uint8_t config = 0;

    if (dps <= 7) config |= (dps << 5);
	else config |= (0 << 5);
	
	if(freq <= 11 || freq == 15) config |= freq;
	else config |= 6;

    SoftSPI_WriteReg(ICM42688_GYRO_CONFIG0, config);
}

void ICM42688_Accel_Settings(uint8_t range, uint8_t freq)
{
    uint8_t config = 0;
    
    if(range <= 3) config |= (range << 5);
    else config |= (0x00 << 5);

	if(freq <= 15) config |= freq;
	else config |= 6;

    SoftSPI_WriteReg(ICM42688_ACCEL_CONFIG0, config);
}

void ICM42688_Gyro_Filter_Settings(uint8_t temp_bw, uint8_t ui_filt_ord)
{
    uint8_t config = 0;

    if(temp_bw <= 6) config |= (temp_bw << 5);
    else config |= (0 << 5);

    if(ui_filt_ord <= 2) config |= (ui_filt_ord << 2);
    else config |= (0 << 2);
    
    config |= 0x02;
    
    SoftSPI_WriteReg(ICM42688_GYRO_CONFIG1, config);
}

void ICM42688_Filter_BW_Settings(uint8_t accel_bw, uint8_t gyro_bw)
{
    uint8_t config = 0;
    
    if(accel_bw <= 7 || accel_bw ==14 || accel_bw ==15) config |= (accel_bw << 4);
    else config |= (0x01 << 4);
    
    if(gyro_bw <= 7 || gyro_bw ==14 || gyro_bw <=15) config |= gyro_bw;
    else config |= 0x01;
    
    SoftSPI_WriteReg(ICM42688_GYRO_ACCEL_CONFIG0, config);
}

void ICM42688_Accel_Filter_Order(uint8_t ui_filt_ord)
{
    uint8_t config = 0;
    
    if(ui_filt_ord <= 2) config |= (ui_filt_ord << 3);
    else config |= (0x01 << 3);

    config |= 0x04;
   
    SoftSPI_WriteReg(ICM42688_ACCEL_CONFIG1, config);
}

void ICM42688_Calibration(void)
{
	static uint8_t count = 0;
	static int32_t total_g_z = 0;
	delay_ms(1000);
	while(++count <= 10)
	{
		uint8_t buf[2];
		buf[0] = SoftSPI_ReadReg(ICM42688_GYRO_DATA_Z1);
		buf[1] = SoftSPI_ReadReg(ICM42688_GYRO_DATA_Z0);
		int16_t real_g_z = (buf[0] << 8) | buf[1];
		total_g_z += real_g_z;
		delay_ms(100);
	}
	offset_g_z = total_g_z/10;
}

u8 ICM42688_Init(u8 G_dps,u8 A_rge,u8 G_freq,u8 A_freq,u8 G_bw_filt,u8 A_bw_filt,u8 T_bw_filt,u8 G_ui_filt,u8 A_ui_filt)
{
	uint8_t res = 0;
	SoftSPI_Init();
	if(ICM42688_WhoAmI()) res = 1;
	else res = 0;
	if(res)
	{
		SoftSPI_WriteReg(ICM42688_DEVICE_CONFIG,0x01);//软复位
		delay_ms(2);
		SoftSPI_WriteReg(ICM42688_PWR_MGMT0,0x0F);//开温度 陀螺 加速度 高性能
		delay_ms(2);
		ICM42688_Gyro_Settings(G_dps,G_freq);
		delay_ms(2);
		ICM42688_Accel_Settings(A_rge,A_freq);
		delay_ms(2);
		ICM42688_Gyro_Filter_Settings(T_bw_filt,G_ui_filt);
		delay_ms(2);
		ICM42688_Accel_Filter_Order(A_ui_filt);
		delay_ms(2);
		ICM42688_Filter_BW_Settings(A_bw_filt,G_bw_filt);
		delay_ms(2);
		
		ICM42688_Calibration();
	}
	return res;
}

void ICM42688_Read(void)
{
	uint8_t buf[2];
	buf[0] = SoftSPI_ReadReg(ICM42688_GYRO_DATA_Z1);
	buf[1] = SoftSPI_ReadReg(ICM42688_GYRO_DATA_Z0);
	int16_t real_g_z = (buf[0] << 8) | buf[1];
	g_z = (float)(real_g_z - offset_g_z)/131.0f;
	if(g_z > 0.1f || g_z < -0.1f) yaw += g_z * 0.05f; 
}
