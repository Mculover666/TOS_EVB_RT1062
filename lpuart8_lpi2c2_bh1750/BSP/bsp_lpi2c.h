#ifndef _BSP_LPI2C_H_
#define _BSP_LPI2C_H_

#include "fsl_lpi2c.h"
#include "board.h"

/* Select USB1 PLL (480 MHz) as master lpi2c clock source */
#define LPI2C_CLOCK_SOURCE_SELECT (0U)
/* Clock divider for master lpi2c clock source */
#define LPI2C_CLOCK_SOURCE_DIVIDER (5U)
/* Get frequency of lpi2c clock */
#define LPI2C_CLOCK_FREQUENCY ((CLOCK_GetFreq(kCLOCK_Usb1PllClk) / 8) / (LPI2C_CLOCK_SOURCE_DIVIDER + 1U))
#define LPI2C_MASTER_CLOCK_FREQUENCY LPI2C_CLOCK_FREQUENCY

int bsp_lpi2c_init(char num);
void bsp_lpi2c_deinit(char num);

#endif /* _BSP_LPI2C_H_ */
