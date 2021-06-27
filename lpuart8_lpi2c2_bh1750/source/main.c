#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "bsp_led.h"
#include "bsp_lpuart.h"
#include <stdio.h>
#include "bsp_lpi2c.h"
#include "bh1750.h"

int main(void)
{
    uint8_t dat[2];
    
    /* Board pin, clock */
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
	
    /* bsp init */
    bsp_led_init();
    bsp_lpuart_init(8);
    bsp_lpi2c_init(2);
    
    printf("BH1750<--->LPI2C2 Test!\r\n");
    
	while (1) {
        if(-1 == BH1750_Send_Cmd(ONCE_H_MODE)) {
            printf("send fail\n");
        } else {
            printf("send ok\n");
        }

        SDK_DelayAtLeastUs(200000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

        if(-1 == BH1750_Read_Dat(dat)) {
            printf("recv fail\r\n");
        } else {
            printf("recv ok\r\n");
            printf("current: %5d lux\n", BH1750_Dat_To_Lux(dat));
        }
        
        SDK_DelayAtLeastUs(1000000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    }
}
