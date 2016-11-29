/*
 * Copyright (c) 2016, Swiss Federal Institute of Technology (ETH Zurich).
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Author:  Reto Da Forno
 */

/**
 * @file
 *
 * @brief platform includes and definitions
 * 
 * @note generally, if one of the platform files is needed platform.h
 * should be included instead of the specific file to preserve the 
 * include order and prevent compiler warnings
 */

#ifndef __PLATFORM_H__
#define __PLATFORM_H__

/*
 * include standard libraries
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <isr_compat.h>

/*
 * include MCU definitions
 */

//#include <msp430.h>
#include <cc430f5147.h>

/* compiler info */
#if defined(__GNUC__)
#define COMPILER_DESC               "GCC"
#define COMPILER_VERSION            (__GNUC__ * 10000 + \
                                     __GNUC_MINOR__ * 100 + \
                                     __GNUC_PATCHLEVEL__)
#define COMPILER_VERSION_ENC        ((__GNUC__ << 10) + \
                                     (__GNUC_MINOR__ << 5) + \
                                     (__GNUC_PATCHLEVEL__))
#define COMPILER_INFO               __VERSION__   /* info string */
#elif defined(__IAR_SYSTEMS_ICC__)
#define COMPILER_DESC               "IAR"
#define COMPILER_VERSION            __VER__
#elif defined(__TI_COMPILER_VERSION__)
#define COMPILER_DESC               "TI"
#define COMPILER_VERSION            __TI_COMPILER_VERSION__
#endif

#define MCU_DESC                    "CC430F5147"
#define COMPONENT_ID                0   /* cc430 has ID 0 on the DPP device */
#define SRAM_START                  0x1c00
#define SRAM_END                    0x2bff        /* last valid byte in SRAM */
#define SRAM_SIZE                   4096          /* starting at 0x1C00 */

/*
 * include application specific config
 */
#include "config.h"                 /* application specific configuration */


#ifndef FW_VERSION
#define FW_VERSION                  0x0000
#endif /* FW_VERSION */

/*
 * configuration and definitions (default values, may be overwritten
 * in config.h)
 */
#ifndef WATCHDOG_CONF_ON
#define WATCHDOG_CONF_ON            0
#endif /* WATCHDOG_CONF_ON */

#ifndef LED_CONF_ON 
#define LED_CONF_ON                 1
#endif /* LED_CONF_ON */

#ifndef FRAM_CONF_ON
#define FRAM_CONF_ON                0
#endif /* FRAM_CONF_ON */

#ifndef BOLT_CONF_ON
#define BOLT_CONF_ON                1
#endif /* BOLT_CONF_ON */

#ifndef CLOCK_CONF_XT1_ON
#define CLOCK_CONF_XT1_ON           1
#endif /* CLOCK_CONF_XT1_ON */

#ifndef CLOCK_CONF_FLL_ON
#define CLOCK_CONF_FLL_ON           1
#endif /* CLOCK_CONF_FLL_ON */

#ifndef SVS_CONF_ON
#define SVS_CONF_ON                 0
#endif /* SVS_CONF_ON */

#ifndef RF_CONF_ON
#define RF_CONF_ON                  1
#endif /* RF_CONF_ON */

/* specify the number of timer modules */
#if RF_CONF_ON
#define RTIMER_CONF_NUM_HF          4  /* number of high-frequency timers */
#else /* RF_CONF_ON */
#define RTIMER_CONF_NUM_HF          5
#endif /* RF_CONF_ON */

#define RTIMER_CONF_NUM_LF          3  /* number of low-frequency timers */     

/* specify the number of SPI modules */
#define SPI_CONF_NUM_MODULES        2


/*
 * ERROR checks (verify parameters)
 */
#if !LWB_CONF_USE_XMEM && LWB_CONF_STATS_NVMEM
/* logging to non volatile memory is only available if the external memory is
 * used! */
#error "must enable LWB_CONF_USE_XMEM in order to use LWB_CONF_STATS_NVMEM"
#endif
#if LWB_CONF_USE_XMEM && !FRAM_CONF_ON
#error "LWB_CONF_USE_XMEM is not available if FRAM is disabled"
#endif 


/*
 * pin mapping
 */
#define LED_0                       PORT3, PIN0
#define LED_STATUS                  LED_0
#define LED_ERROR                   LED_0
#define COM_MCU_INT1                PORT3, PIN5
#define COM_MCU_INT2                PORT3, PIN4
#define COM_MCU_SPARE1              PORT3, PIN6         /* spare GPIO pin */
#define COM_MCU_SPARE2              PORT3, PIN7         /* spare GPIO pin */

/* select multiplexer channel (high = UART, low = SPI) */
#define MUX_SEL_PIN                 PORT2, PIN7

//#define DEBUG_PRINT_CONF_TASK_ACT_PIN    PORT2, PIN0
#ifndef GLOSSY_START_PIN
#define GLOSSY_START_PIN            LED_0
#endif /* GLOSSY_START_PIN */
//#define GLOSSY_RX_PIN             COM_MCU_INT1
//#define GLOSSY_TX_PIN             COM_MCU_INT2
//#define RF_GDO0_PIN               COM_MCU_INT1
//#define RF_GDO1_PIN               COM_MCU_INT1
#ifndef RF_GDO2_PIN
#define RF_GDO2_PIN                 COM_MCU_INT1
#endif /* RF_GDO2_PIN */
//#define MCLK_PIN                  COM_MCU_INT1
//#define ACLK_PIN                  COM_MCU_INT2
//#define SMCLK_PIN                 COM_MCU_INT1

/* the following pins assignments are given by FlockLAB, do not change */
#define FLOCKLAB_LED1               LED_0
#define FLOCKLAB_INT1               COM_MCU_INT1  /* for GPIO tracing */
#define FLOCKLAB_INT2               COM_MCU_INT2  /* for GPIO tracing */

#if FRAM_CONF_ON
  #define FRAM_CONF_CTRL_PIN        PORT2, PIN0
  #define FRAM_CONF_SIZE            125000      /* 1 Mbit */
  #define FRAM_CONF_SPI             SPI_0       
  //#ifndef DEBUG_PRINT_CONF_USE_XMEM
  //#define DEBUG_PRINT_CONF_USE_XMEM 1
  //#endif /* DEBUG_PRINT_CONF_USE_XMEM */
  #ifndef DEBUG_PRINT_CONF_NUM_MSG
  #define DEBUG_PRINT_CONF_NUM_MSG  20
  #endif /* DEBUG_PRINT_CONF_NUM_MSG */
  #define FRAM_SLEEP                fram_sleep()
#else /* FRAM_CONF_ON */
  #define FRAM_SLEEP
#endif /* FRAM_CONF_ON */

#if BOLT_CONF_ON
  #define BOLT_CONF_SPI             SPI_1
  #define BOLT_CONF_IND_PIN         PORT2, PIN2
  #define BOLT_CONF_MODE_PIN        PORT2, PIN3
  #define BOLT_CONF_REQ_PIN         PORT2, PIN4
  #define BOLT_CONF_ACK_PIN         PORT2, PIN5
  /* IND pin for the outgoing queue (sent messages) */
  #define BOLT_CONF_IND_OUT_PIN     PORT1, PIN1
  #define BOLT_CONF_TIMEREQ_PIN     PORT2, PIN1
  #define BOLT_CONF_FUTUREUSE_PIN   PORT2, PIN6
 #if BOLT_CONF_TIMEREQ_HF_MODE
  /* Note: HF mode cannot be used if LWB_CONF_USE_LF_FOR_WAKEUP is enabled! */
  #define BOLT_CONF_TIMEREQ_TIMERID RTIMER_HF_0
  #define BOLT_CONF_TIMEREQ_DMATRG  DMA_TRGSRC_TA0CCR0
  #define BOLT_CONF_TIMEREQ_PINMAP  PM_TA0CCR0A
  #define BOLT_CONF_TIMEREQ_CCR     TA0CCR0
 #else /* BOLT_CONF_TIMEREQ_HF_MODE */
  #define BOLT_CONF_TIMEREQ_TIMERID RTIMER_LF_0
  #define BOLT_CONF_TIMEREQ_DMATRG  DMA_TRCSRC_TA1CCR0
  #define BOLT_CONF_TIMEREQ_PINMAP  PM_TA1CCR0A
  #define BOLT_CONF_TIMEREQ_CCR     TA1CCR0
 #endif /* BOLT_CONF_TIMEREQ_HF_MODE */
#endif /* BOLT_CONF_ON */

/* specify what needs to be done every time before UART is enabled */
#define UART_BEFORE_ENABLE {\
  uart_reinit();\
  PIN_SET(MUX_SEL_PIN);\
}

/*
 * The application should define the following two macros for better
 * performance (otherwise glossy will disable all active interrupts).
 */
#define GLOSSY_DISABLE_INTERRUPTS
#define GLOSSY_ENABLE_INTERRUPTS

#define UART_ACTIVE             (UCA0STAT & UCBUSY)

#define LWB_AFTER_DEEPSLEEP()   if(UCSCTL6 & XT2OFF) { \
                                  SFRIE1  &= ~OFIE; \
                                  ENABLE_XT2(); \
                                  WAIT_FOR_OSC(); \
                                  UCSCTL4  = SELA | SELS | SELM; \
                                  __delay_cycles(100); /* errata PMM11/12? */\
                                  UCSCTL5  = DIVA | DIVS | DIVM; \
                                  UCSCTL7  = 0; /* errata UCS11 */ \
                                  SFRIE1  |= OFIE; \
                                  TA0CTL  |= MC_2; \
                                  P1SEL    = (BIT2 | BIT3 | BIT4 | BIT5 | \
                                              BIT6 | BIT7); \
                                }

/* disable all peripherals, reconfigure the GPIOs and disable XT2 */
#define LWB_BEFORE_DEEPSLEEP()  {\
                                  FRAM_SLEEP; \
                                  TA0CTL &= ~MC_3; /* stop TA0 */\
                                  PIN_CLR(MUX_SEL_PIN); \
                                  P1SEL = 0; /* reconfigure GPIOs */\
                                  /* DPP has a pullup on P1.5! */\
                                  P1DIR = (BIT2 | BIT3 | BIT4 | BIT6 | BIT7); \
                                  P1OUT = 0; \
                                  /* set clock source to DCO */\
                                  UCSCTL4 = SELA__XT1CLK | SELS__DCOCLKDIV | \
                                            SELM__DCOCLKDIV; \
                                  UCSCTL5 |= DIVM__4; /* errata PMM11 */ \
                                  UCSCTL7  = 0; \
                                  DISABLE_XT2(); \
                                }

/* specify what needs to be done every time before SPI is enabled */
#define SPI_BEFORE_ENABLE(spi) {\
  if(spi == SPI_0) { spi_reinit(SPI_0); }\
  PIN_CLR(MUX_SEL_PIN); \
}


/*
 * include MCU specific drivers
 */
#include "rf1a-SmartRF-settings/868MHz-2GFSK-250kbps.h" /* RF1A config */
#include "adc.h"
#include "clock.h"
#include "dma.h"
#include "flash.h"
#include "gpio.h"
#include "pmm.h"
#include "rf1a.h"        /* RF1A config must be included BEFORE rf1a.h */
#include "rtimer.h"
#include "spi.h"
#include "uart.h"
#include "usci.h"
#include "watchdog.h"

#endif /* __PLATFORM_H__ */

