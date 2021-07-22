#ifndef _BSP_UART_H_
#define _BSP_UART_H_

#include "fsl_lpuart.h"
#include "board.h"

int bsp_lpuart_init(char num);
void bsp_lpuart_deinit(char num);

#endif /* _BSP_UART_H_ */
