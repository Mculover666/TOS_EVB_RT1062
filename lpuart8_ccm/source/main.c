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
    printf("--kCLOCK_ArmPllClk: %d Hz\r\n", CLOCK_GetFreq(kCLOCK_ArmPllClk));
    printf("--kCLOCK_SysPllClk: %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllClk));
    printf("--kCLOCK_Usb1PllClk: %d Hz\r\n", CLOCK_GetFreq(kCLOCK_Usb1PllClk));
    printf("--kCLOCK_AudioPllClk: %d Hz\r\n", CLOCK_GetFreq(kCLOCK_AudioPllClk));
    printf("--kCLOCK_EnetPll0Clk: %d Hz\r\n", CLOCK_GetFreq(kCLOCK_EnetPll0Clk));
    printf("--kCLOCK_VideoPllClk: %d Hz\r\n", CLOCK_GetFreq(kCLOCK_VideoPllClk));
    printf("--kCLOCK_Usb2PllClk: %d Hz\r\n", CLOCK_GetFreq(kCLOCK_Usb2PllClk));
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
        SDK_DelayAtLeastUs(1000000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
        printf("LED on!\r\n");
        
        bsp_led_ctl (1);
        SDK_DelayAtLeastUs(1000000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
        printf("LED off!\r\n");
    }
}
