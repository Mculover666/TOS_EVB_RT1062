#include "bsp_lpuart.h"

int bsp_lpuart_init(char num)
{
    lpuart_config_t config;
    status_t status;
    
    /*
     * config.baudRate_Bps = 115200U;
     * config.parityMode = kLPUART_ParityDisabled;
     * config.stopBitCount = kLPUART_OneStopBit;
     * config.txFifoWatermark = 0;
     * config.rxFifoWatermark = 0;
     * config.enableTx = false;
     * config.enableRx = false;
     */
    LPUART_GetDefaultConfig(&config);
    
    switch (num) {
        case 1:
            config.baudRate_Bps = 115200;
            config.enableTx     = true;
            config.enableRx     = true;
            status = LPUART_Init(LPUART1, &config, BOARD_DEBUG_UART_CLK_FREQ);
            break;
        case 2:
            config.baudRate_Bps = 115200;
            config.enableTx     = true;
            config.enableRx     = true;
            status = LPUART_Init(LPUART2, &config, BOARD_DEBUG_UART_CLK_FREQ);
            break;
        case 3:
            config.baudRate_Bps = 115200;
            config.enableTx     = true;
            config.enableRx     = true;
            status = LPUART_Init(LPUART3, &config, BOARD_DEBUG_UART_CLK_FREQ);
            break;
        case 4:
            config.baudRate_Bps = 115200;
            config.enableTx     = true;
            config.enableRx     = true;
            status = LPUART_Init(LPUART4, &config, BOARD_DEBUG_UART_CLK_FREQ);
            break;
        case 5:
            config.baudRate_Bps = 115200;
            config.enableTx     = true;
            config.enableRx     = true;
            status = LPUART_Init(LPUART5, &config, BOARD_DEBUG_UART_CLK_FREQ);
            break;
        case 6:
            config.baudRate_Bps = 115200;
            config.enableTx     = true;
            config.enableRx     = true;
            status = LPUART_Init(LPUART6, &config, BOARD_DEBUG_UART_CLK_FREQ);
            break;
        case 7:
            config.baudRate_Bps = 115200;
            config.enableTx     = true;
            config.enableRx     = true;
            status = LPUART_Init(LPUART7, &config, BOARD_DEBUG_UART_CLK_FREQ);
            break;
        case 8:
            config.baudRate_Bps = 115200;
            config.enableTx     = true;
            config.enableRx     = true;
            status = LPUART_Init(LPUART8, &config, BOARD_DEBUG_UART_CLK_FREQ);
            break;
        default:
            status = kStatus_Fail;
            break;
    }
    
    return status == kStatus_Success ? 0 : -1;
}

void bsp_lpuart_deinit(char num)
{
    switch (num) {
        case 1:
            LPUART_Deinit(LPUART1);
            break;
        case 2:
            LPUART_Deinit(LPUART2);
            break;
        case 3:
            LPUART_Deinit(LPUART3);
            break;
        case 4:
            LPUART_Deinit(LPUART4);
            break;
        case 5:
            LPUART_Deinit(LPUART5);
            break;
        case 6:
            LPUART_Deinit(LPUART6);
            break;
        case 7:
            LPUART_Deinit(LPUART7);
            break;
        case 8:
            LPUART_Deinit(LPUART8);
            break;
        defalut:
            break;
    }
}
#if 1
#include <stdio.h>
int fputc(int ch, FILE *stream)
{
    while (!(kLPUART_TxDataRegEmptyFlag & LPUART_GetStatusFlags(LPUART8)));
        
    LPUART_WriteByte(LPUART8, ch);
    
    return ch;
}
#endif