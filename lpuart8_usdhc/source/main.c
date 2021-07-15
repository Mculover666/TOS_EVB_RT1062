#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "bsp_led.h"
#include "bsp_lpuart.h"
#include <stdio.h>
#include "bsp_usdhc.h"

sd_card_t g_sd;

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
    ccm_clock_list();
    bsp_usdhc_host_init(2, &g_sd);
    
    printf("Hello World!\r\n");
    
    sdcard_init(&g_sd);
    
    sdcard_test(&g_sd);
    
    
	while (1) {
        bsp_led_ctl (0);
        SDK_DelayAtLeastUs(1000000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
        printf("LED on!\r\n");
        
        bsp_led_ctl (1);
        SDK_DelayAtLeastUs(1000000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
        printf("LED off!\r\n");
    }
}
