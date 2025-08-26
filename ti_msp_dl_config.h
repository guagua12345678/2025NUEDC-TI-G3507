/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X
#define CONFIG_MSPM0G3505

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)



#define CPUCLK_FREQ                                                     32000000



/* Defines for PWM_0 */
#define PWM_0_INST                                                         TIMA0
#define PWM_0_INST_IRQHandler                                   TIMA0_IRQHandler
#define PWM_0_INST_INT_IRQN                                     (TIMA0_INT_IRQn)
#define PWM_0_INST_CLK_FREQ                                             16000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_0_C0_PORT                                                 GPIOA
#define GPIO_PWM_0_C0_PIN                                          DL_GPIO_PIN_8
#define GPIO_PWM_0_C0_IOMUX                                      (IOMUX_PINCM19)
#define GPIO_PWM_0_C0_IOMUX_FUNC                     IOMUX_PINCM19_PF_TIMA0_CCP0
#define GPIO_PWM_0_C0_IDX                                    DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_0_C1_PORT                                                 GPIOA
#define GPIO_PWM_0_C1_PIN                                          DL_GPIO_PIN_9
#define GPIO_PWM_0_C1_IOMUX                                      (IOMUX_PINCM20)
#define GPIO_PWM_0_C1_IOMUX_FUNC                     IOMUX_PINCM20_PF_TIMA0_CCP1
#define GPIO_PWM_0_C1_IDX                                    DL_TIMER_CC_1_INDEX



/* Defines for TIMG12 */
#define TIMG12_INST                                                     (TIMG12)
#define TIMG12_INST_IRQHandler                                 TIMG12_IRQHandler
#define TIMG12_INST_INT_IRQN                                   (TIMG12_INT_IRQn)
#define TIMG12_INST_LOAD_VALUE                                         (199999U)




/* Defines for I2C_0 */
#define I2C_0_INST                                                          I2C0
#define I2C_0_INST_IRQHandler                                    I2C0_IRQHandler
#define I2C_0_INST_INT_IRQN                                        I2C0_INT_IRQn
#define I2C_0_BUS_SPEED_HZ                                                100000
#define GPIO_I2C_0_SDA_PORT                                                GPIOA
#define GPIO_I2C_0_SDA_PIN                                         DL_GPIO_PIN_0
#define GPIO_I2C_0_IOMUX_SDA                                      (IOMUX_PINCM1)
#define GPIO_I2C_0_IOMUX_SDA_FUNC                       IOMUX_PINCM1_PF_I2C0_SDA
#define GPIO_I2C_0_SCL_PORT                                                GPIOA
#define GPIO_I2C_0_SCL_PIN                                         DL_GPIO_PIN_1
#define GPIO_I2C_0_IOMUX_SCL                                      (IOMUX_PINCM2)
#define GPIO_I2C_0_IOMUX_SCL_FUNC                       IOMUX_PINCM2_PF_I2C0_SCL


/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_FREQUENCY                                            4000000
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM22)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM21)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM21_PF_UART0_TX
#define UART_0_BAUD_RATE                                                  (9600)
#define UART_0_IBRD_4_MHZ_9600_BAUD                                         (26)
#define UART_0_FBRD_4_MHZ_9600_BAUD                                          (3)





/* Port definition for Pin Group BEEP */
#define BEEP_PORT                                                        (GPIOB)

/* Defines for PIN_4: GPIOB.0 with pinCMx 12 on package pin 47 */
#define BEEP_PIN_4_PIN                                           (DL_GPIO_PIN_0)
#define BEEP_PIN_4_IOMUX                                         (IOMUX_PINCM12)
/* Port definition for Pin Group motor_L */
#define motor_L_PORT                                                     (GPIOB)

/* Defines for PB15: GPIOB.15 with pinCMx 32 on package pin 3 */
#define motor_L_PB15_PIN                                        (DL_GPIO_PIN_15)
#define motor_L_PB15_IOMUX                                       (IOMUX_PINCM32)
/* Defines for PB16: GPIOB.16 with pinCMx 33 on package pin 4 */
#define motor_L_PB16_PIN                                        (DL_GPIO_PIN_16)
#define motor_L_PB16_IOMUX                                       (IOMUX_PINCM33)
/* Port definition for Pin Group motor_R */
#define motor_R_PORT                                                     (GPIOB)

/* Defines for PB2: GPIOB.2 with pinCMx 15 on package pin 50 */
#define motor_R_PB2_PIN                                          (DL_GPIO_PIN_2)
#define motor_R_PB2_IOMUX                                        (IOMUX_PINCM15)
/* Defines for PB3: GPIOB.3 with pinCMx 16 on package pin 51 */
#define motor_R_PB3_PIN                                          (DL_GPIO_PIN_3)
#define motor_R_PB3_IOMUX                                        (IOMUX_PINCM16)
/* Port definition for Pin Group encoder_L */
#define encoder_L_PORT                                                   (GPIOB)

/* Defines for PB6: GPIOB.6 with pinCMx 23 on package pin 58 */
// groups represented: ["encoder_R","encoder_L"]
// pins affected: ["PB8","PB9","PB6","PB7"]
#define GPIO_MULTIPLE_GPIOB_INT_IRQN                            (GPIOB_INT_IRQn)
#define GPIO_MULTIPLE_GPIOB_INT_IIDX            (DL_INTERRUPT_GROUP1_IIDX_GPIOB)
#define encoder_L_PB6_IIDX                                   (DL_GPIO_IIDX_DIO6)
#define encoder_L_PB6_PIN                                        (DL_GPIO_PIN_6)
#define encoder_L_PB6_IOMUX                                      (IOMUX_PINCM23)
/* Defines for PB7: GPIOB.7 with pinCMx 24 on package pin 59 */
#define encoder_L_PB7_IIDX                                   (DL_GPIO_IIDX_DIO7)
#define encoder_L_PB7_PIN                                        (DL_GPIO_PIN_7)
#define encoder_L_PB7_IOMUX                                      (IOMUX_PINCM24)
/* Port definition for Pin Group encoder_R */
#define encoder_R_PORT                                                   (GPIOB)

/* Defines for PB8: GPIOB.8 with pinCMx 25 on package pin 60 */
#define encoder_R_PB8_IIDX                                   (DL_GPIO_IIDX_DIO8)
#define encoder_R_PB8_PIN                                        (DL_GPIO_PIN_8)
#define encoder_R_PB8_IOMUX                                      (IOMUX_PINCM25)
/* Defines for PB9: GPIOB.9 with pinCMx 26 on package pin 61 */
#define encoder_R_PB9_IIDX                                   (DL_GPIO_IIDX_DIO9)
#define encoder_R_PB9_PIN                                        (DL_GPIO_PIN_9)
#define encoder_R_PB9_IOMUX                                      (IOMUX_PINCM26)
/* Defines for PA14: GPIOA.14 with pinCMx 36 on package pin 7 */
#define tracing_PA14_PORT                                                (GPIOA)
#define tracing_PA14_PIN                                        (DL_GPIO_PIN_14)
#define tracing_PA14_IOMUX                                       (IOMUX_PINCM36)
/* Defines for PA15: GPIOA.15 with pinCMx 37 on package pin 8 */
#define tracing_PA15_PORT                                                (GPIOA)
#define tracing_PA15_PIN                                        (DL_GPIO_PIN_15)
#define tracing_PA15_IOMUX                                       (IOMUX_PINCM37)
/* Defines for PA16: GPIOA.16 with pinCMx 38 on package pin 9 */
#define tracing_PA16_PORT                                                (GPIOA)
#define tracing_PA16_PIN                                        (DL_GPIO_PIN_16)
#define tracing_PA16_IOMUX                                       (IOMUX_PINCM38)
/* Defines for PA17: GPIOA.17 with pinCMx 39 on package pin 10 */
#define tracing_PA17_PORT                                                (GPIOA)
#define tracing_PA17_PIN                                        (DL_GPIO_PIN_17)
#define tracing_PA17_IOMUX                                       (IOMUX_PINCM39)
/* Defines for PA22: GPIOA.22 with pinCMx 47 on package pin 18 */
#define tracing_PA22_PORT                                                (GPIOA)
#define tracing_PA22_PIN                                        (DL_GPIO_PIN_22)
#define tracing_PA22_IOMUX                                       (IOMUX_PINCM47)
/* Defines for PB18: GPIOB.18 with pinCMx 44 on package pin 15 */
#define tracing_PB18_PORT                                                (GPIOB)
#define tracing_PB18_PIN                                        (DL_GPIO_PIN_18)
#define tracing_PB18_IOMUX                                       (IOMUX_PINCM44)
/* Defines for PB17: GPIOB.17 with pinCMx 43 on package pin 14 */
#define tracing_PB17_PORT                                                (GPIOB)
#define tracing_PB17_PIN                                        (DL_GPIO_PIN_17)
#define tracing_PB17_IOMUX                                       (IOMUX_PINCM43)
/* Port definition for Pin Group ICM42688 */
#define ICM42688_PORT                                                    (GPIOA)

/* Defines for PIN_0: GPIOA.24 with pinCMx 54 on package pin 25 */
#define ICM42688_PIN_0_PIN                                      (DL_GPIO_PIN_24)
#define ICM42688_PIN_0_IOMUX                                     (IOMUX_PINCM54)
/* Defines for PIN_1: GPIOA.25 with pinCMx 55 on package pin 26 */
#define ICM42688_PIN_1_PIN                                      (DL_GPIO_PIN_25)
#define ICM42688_PIN_1_IOMUX                                     (IOMUX_PINCM55)
/* Defines for PIN_2: GPIOA.26 with pinCMx 59 on package pin 30 */
#define ICM42688_PIN_2_PIN                                      (DL_GPIO_PIN_26)
#define ICM42688_PIN_2_IOMUX                                     (IOMUX_PINCM59)
/* Defines for PIN_3: GPIOA.27 with pinCMx 60 on package pin 31 */
#define ICM42688_PIN_3_PIN                                      (DL_GPIO_PIN_27)
#define ICM42688_PIN_3_IOMUX                                     (IOMUX_PINCM60)
/* Port definition for Pin Group KEY */
#define KEY_PORT                                                         (GPIOB)

/* Defines for PB1: GPIOB.1 with pinCMx 13 on package pin 48 */
#define KEY_PB1_PIN                                              (DL_GPIO_PIN_1)
#define KEY_PB1_IOMUX                                            (IOMUX_PINCM13)
/* Defines for PB11: GPIOB.11 with pinCMx 28 on package pin 63 */
#define KEY_PB11_PIN                                            (DL_GPIO_PIN_11)
#define KEY_PB11_IOMUX                                           (IOMUX_PINCM28)
/* Defines for PB14: GPIOB.14 with pinCMx 31 on package pin 2 */
#define KEY_PB14_PIN                                            (DL_GPIO_PIN_14)
#define KEY_PB14_IOMUX                                           (IOMUX_PINCM31)
/* Port definition for Pin Group LED */
#define LED_PORT                                                         (GPIOB)

/* Defines for PB21: GPIOB.21 with pinCMx 49 on package pin 20 */
#define LED_PB21_PIN                                            (DL_GPIO_PIN_21)
#define LED_PB21_IOMUX                                           (IOMUX_PINCM49)
/* Defines for PB22: GPIOB.22 with pinCMx 50 on package pin 21 */
#define LED_PB22_PIN                                            (DL_GPIO_PIN_22)
#define LED_PB22_IOMUX                                           (IOMUX_PINCM50)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_0_init(void);
void SYSCFG_DL_TIMG12_init(void);
void SYSCFG_DL_I2C_0_init(void);
void SYSCFG_DL_UART_0_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
