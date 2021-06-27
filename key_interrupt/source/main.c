#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "bsp_led.h"
#include "bsp_key.h"

int main(void)
{
    int s;
    /* Board pin, clock */
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
	
    /* bsp init */
    bsp_led_init();
    //bsp_key_init(1);
    bsp_key_init(2);
    
    /* led on */
    bsp_led_ctl (0);
    s = 0;
    
	while (1) {
        if (g_KEY2_Signal) {
            g_KEY2_Signal = false;
            if (s) {
                s = 0;
                bsp_led_ctl (0);
            } else {
                s = 1;
                bsp_led_ctl (1);
            }
            
        }
    }
}
