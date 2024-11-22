/**********************************************************************************************************************
 * \file Cpu0_Main.c
 * \copyright Copyright (C) Infineon Technologies AG 2019
 * 
 * Use of this file is subject to the terms of use agreed between (i) you or the company in which ordinary course of 
 * business you are acting and (ii) Infineon Technologies AG or its licensees. If and as long as no such terms of use
 * are agreed, use of this file is subject to following:
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization obtaining a copy of the software and 
 * accompanying documentation covered by this license (the "Software") to use, reproduce, display, distribute, execute,
 * and transmit the Software, and to prepare derivative works of the Software, and to permit third-parties to whom the
 * Software is furnished to do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including the above license grant, this restriction
 * and the following disclaimer, must be included in all copies of the Software, in whole or in part, and all 
 * derivative works of the Software, unless such copies or derivative works are solely in the form of 
 * machine-executable object code generated by a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE 
 * COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN 
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
 * IN THE SOFTWARE.
 *********************************************************************************************************************/
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include <stdio.h>
IfxCpu_syncEvent g_cpuSyncEvent = 0;

int core0_main(void)
{
    IfxCpu_enableInterrupts();
    
    /* !!WATCHDOG0 AND SAFETY WATCHDOG ARE DISABLED HERE!!
     * Enable the watchdogs and service them periodically if it is required
     */
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());
    
    /* Wait for CPU sync event */
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);
    
    typedef struct {
        unsigned char ST   : 1;
        unsigned char CLK  : 7;
        unsigned char SPEED: 3;
        unsigned char RES  : 5;
        unsigned int MODE  : 16;
    } ADC_REG;

    // ADC_REG 설계도를 이용하여 메모리에 공간 할당.
    ADC_REG adc1;
    adc1.ST    = 1;
    adc1.CLK   = 0x7F;
    adc1.SPEED = 0x7;
    adc1.RES   = 0x1F;
    adc1.MODE  = 0xFFBB;

    printf("adc1 is allocated in sram @ 0x%p\n", &adc1);

  //#define ADC_HAL  *((unsigned int*)0x70019600)
    #define ADC_HAL (*((     ADC_REG*)0x70019600))

    ADC_HAL.ST    = 1;
    ADC_HAL.CLK   = 0x7F;
    ADC_HAL.SPEED = 0x7;
    ADC_HAL.RES   = 0x1F;
    ADC_HAL.MODE  = 0xFFBB;



    // 공용체 - 어떤 HW영역을 여러가지 타입으로 바라보게 해줌.
    // 이미 정의된 타입을 묶어주면됨.
    typedef union {
            unsigned int  u;
            unsigned char b[4];
            ADC_REG       adc;
    } ADC_IF;
    #define ADC_UHAL (*((     ADC_IF*)0x70019600))

    ADC_UHAL.u = 0xAABBCCDD;
    ADC_UHAL.b[0] = 0x5A;
    ADC_UHAL.adc.MODE = 0x1234;


    adc1.ST    = 0;
    adc1.CLK   = 0;
    adc1.SPEED = 0;
    adc1.RES   = 0;
    adc1.MODE  = 0;

    ADC_HAL.ST    = 0;
    ADC_HAL.CLK   = 0;
    ADC_HAL.SPEED = 0;
    ADC_HAL.RES   = 0;
    ADC_HAL.MODE  = 0;

    while(1)
    {
    }
    return (1);
}
