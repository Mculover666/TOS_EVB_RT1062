#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "bsp_led.h"
#include "bsp_lpuart.h"
#include <stdio.h>
#include "bsp_lpspi.h"
#include "w25q64.h"

int main(void)
{
    uint16_t flash_id;
    
    /* Board pin, clock */
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
	
    /* bsp init */
    bsp_led_init();
    bsp_lpuart_init(8);
    bsp_lpspi_init(1);
    
    printf("Hello World!\r\n");
    flash_id = W25QXX_ReadID();
    printf("flash_id is 0x%x\r\n", flash_id);
    
	while (1) {
        bsp_led_ctl (0);
        SDK_DelayAtLeastUs(100000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
        
        bsp_led_ctl (1);
        SDK_DelayAtLeastUs(100000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    }
}
