#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "bsp_led.h"
#include "bsp_lpuart.h"
#include <stdio.h>

void ccm_clock_list(void)
{
    printf("--CPU: %d Hz\r\n", CLOCK_GetFreq(kCLOCK_CpuClk));
    printf("--AHB: %d Hz\r\n", CLOCK_GetFreq(kCLOCK_AhbClk));
    printf("--SEMC: %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SemcClk));
    printf("--SYSPLL: %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllClk));
    printf("--SYSPLLPFD0: %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllPfd0Clk));
    printf("--SYSPLLPFD1: %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllPfd1Clk));
    printf("--SYSPLLPFD2: %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllPfd2Clk));
    printf("--SYSPLLPFD3: %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllPfd3Clk));
}

int main(void)
{
    /* Board pin, clock */
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
	
    /* bsp init */
    bsp_led_init();
    bsp_lpuart_init(8);
    
    printf("Hello World!\r\n");
    
    ccm_clock_list();
    
	while (1) {
        bsp_led_ctl (0);
        SDK_DelayAtLeastUs(100000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
        
        bsp_led_ctl (1);
        SDK_DelayAtLeastUs(100000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    }
}
