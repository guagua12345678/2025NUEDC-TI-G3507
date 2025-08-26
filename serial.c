#include "ti_msp_dl_config.h"
#include <string.h>    

volatile unsigned char uart_data = 0;

void hc05_init(void)
{
	NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
}

//串口发送单个字符
void uart0_send_char(char ch)
{
    //当串口0忙的时候等待，不忙的时候再发送传进来的字符
    while( DL_UART_isBusy(UART_0_INST) == true );
    //发送单个字符
    DL_UART_Main_transmitData(UART_0_INST, ch);
}

//串口发送字符串
void uart0_send_string(const uint8_t *buf, uint16_t len)
{
    while (len--) uart0_send_char(*buf++);
}

//串口的中断服务函数
void UART_0_INST_IRQHandler(void)
{
    //如果产生了串口中断
    switch( DL_UART_getPendingInterrupt(UART_0_INST) )
    {
        case DL_UART_IIDX_RX://如果是接收中断
            //接发送过来的数据保存在变量中
            uart_data = DL_UART_Main_receiveData(UART_0_INST);
            //将保存的数据再发送出去
            uart0_send_char(uart_data);
            break;

        default://其他的串口中断
            break;
    }
}

typedef union {float f; uint8_t b[2];} fbytes_t;

void VOFA_Send(float a, float b)
{
    uint8_t frame[12];
    fbytes_t fb;

    fb.f = a;
    memcpy(&frame[0], fb.b, 4);

    fb.f = b;
    memcpy(&frame[4], fb.b, 4);

    frame[8] = 0x00;
    frame[9] = 0x00;
    frame[10] = 0x80;
    frame[11] = 0x7F;

    uart0_send_string(frame, sizeof(frame));
}
