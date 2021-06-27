#include "bsp_lpi2c.h"

int bsp_lpi2c_init(char num)
{
    lpi2c_master_config_t masterConfig;
    status_t status;
    
    /*Clock setting for LPI2C*/
    CLOCK_SetMux(kCLOCK_Lpi2cMux, LPI2C_CLOCK_SOURCE_SELECT);
    CLOCK_SetDiv(kCLOCK_Lpi2cDiv, LPI2C_CLOCK_SOURCE_DIVIDER);
    
   /*
     * masterConfig.debugEnable = false;
     * masterConfig.ignoreAck = false;
     * masterConfig.pinConfig = kLPI2C_2PinOpenDrain;
     * masterConfig.baudRate_Hz = 100000U;
     * masterConfig.busIdleTimeout_ns = 0;
     * masterConfig.pinLowTimeout_ns = 0;
     * masterConfig.sdaGlitchFilterWidth_ns = 0;
     * masterConfig.sclGlitchFilterWidth_ns = 0;
     */
    LPI2C_MasterGetDefaultConfig(&masterConfig);
    
    switch (num) {
        case 1:
            break;
        case 2:
             /* Change the default baudrate configuration */
            masterConfig.baudRate_Hz = 100000U;
        
            /* Initialize the LPI2C master peripheral */
            LPI2C_MasterInit(LPI2C2, &masterConfig, LPI2C_MASTER_CLOCK_FREQUENCY);
            break;
        case 3:

            break;
        case 4:

            break;
        
        default:
            status = kStatus_Fail;
            break;
    }
    
    return status == kStatus_Success ? 0 : -1;
}

void bsp_lpi2c_deinit(char num)
{
    switch (num) {
        case 1:
            break;
        case 2:
            LPI2C_MasterDeinit(LPI2C2);
            break;
        case 3:
            break;
        case 4:
            break;
        defalut:
            break;
    }
}
