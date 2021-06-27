#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "bsp_led.h"
#include "bsp_lpuart.h"
#include <stdio.h>

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
    
	while (1) {
        bsp_led_ctl (0);
        SDK_DelayAtLeastUs(100000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
        
        bsp_led_ctl (1);
        SDK_DelayAtLeastUs(100000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    }
}
