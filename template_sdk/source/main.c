#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

int main(void)
{
    /* Board pin, clock */
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
	
    
	while(1);
}