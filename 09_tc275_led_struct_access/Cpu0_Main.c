#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include <stdio.h>


IfxCpu_syncEvent g_cpuSyncEvent = 0;

typedef struct {
        unsigned int reserved0: 3;
        unsigned int PC0      : 5;
        unsigned int reserved1: 3;
        unsigned int PC1      : 5;
        unsigned int reserved2: 3;
        unsigned int PC2      : 5;
        unsigned int reserved3: 3;
        unsigned int PC3      : 5;
} IOCR_STX;

typedef struct {
        unsigned char P0: 1;
        unsigned char P1: 1;
        unsigned char P2: 1;
        unsigned char P3: 1;
        unsigned char P4: 1;
        unsigned char P5: 1;
        unsigned char P6: 1;
        unsigned char P7: 1;
        unsigned char P8: 1;
        unsigned char P9: 1;
        unsigned char P10: 1;
        unsigned char P11: 1;
        unsigned char P12: 1;
        unsigned char P13: 1;
        unsigned char P14: 1;
        unsigned char P15: 1;
        unsigned short _reserved: 16;
} POUT_STX;

#define H_P10_IOCR0_STX (*(volatile IOCR_STX*)(0xF003B010u))
#define H_P10_OUT       (*(volatile POUT_STX*)(0xF003B000u))

void initLED_STX() {
    H_P10_IOCR0_STX.PC1 = 0x10; // P10.1 output mode
    H_P10_IOCR0_STX.PC2 = 0x10; // P10.2 output mode
}
void sw_delay() {
        for(int i=0; i<5000000; i++); // software delay
}


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


    initLED_STX();


    while(1)
    {
        // red led on/off toggle (P10.1 port drive 5V and 0V)
        H_P10_OUT.P1 = 1;
        sw_delay();


        H_P10_OUT.P1 = 0;
        sw_delay();


        // blue led on/off toggle (P10.2 port drive 5V and 0V)
        H_P10_OUT.P2 = 1;
        sw_delay();


        H_P10_OUT.P2 = 0;
        sw_delay();
    }


    return (1);
}


