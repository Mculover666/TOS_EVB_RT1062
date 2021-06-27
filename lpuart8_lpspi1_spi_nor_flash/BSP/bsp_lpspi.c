#include "bsp_lpspi.h"

void bsp_lpspi_init(char num)
{
    lpspi_master_config_t masterConfig;
    
    CLOCK_SetMux(kCLOCK_LpspiMux, LPSPI_CLOCK_SOURCE_SELECT);
    CLOCK_SetDiv(kCLOCK_LpspiDiv, LPSPI_CLOCK_SOURCE_DIVIDER);
    
    /*Master config*/
    LPSPI_MasterGetDefaultConfig(&masterConfig);
    
    switch (num) {
        case 1:
            masterConfig.baudRate = TRANSFER_BAUDRATE;
            masterConfig.whichPcs = LPSPI_MASTER_PCS_FOR_INIT;
            LPSPI_MasterInit(LPSPI1, &masterConfig, LPSPI_MASTER_CLK_FREQ);
            break;
        default:
            break;
    }

}

void bsp_lpspi_deinit(char num)
{
    switch (num) {
        case 1:
            LPSPI_Deinit(LPSPI1);
            break;
        defalut:
            break;
    }
}
