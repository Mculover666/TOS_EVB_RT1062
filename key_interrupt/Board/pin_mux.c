/*
 * Copyright 2019 NXP.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v6.0
processor: MIMXRT1062xxxxA
mcu_data: ksdk2_0
processor_version: 0.0.20
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

#include "fsl_common.h"
#include "pin_mux.h"
#include "fsl_iomuxc.h"

/* �����жϼ�����ŵ�PAD���� */
#define KEY_PAD_CONFIG_DATA            (SRE_0_SLOW_SLEW_RATE| \
                                        DSE_0_OUTPUT_DRIVER_DISABLED| \
                                        SPEED_2_MEDIUM_100MHz| \
                                        ODE_0_OPEN_DRAIN_DISABLED| \
                                        PKE_1_PULL_KEEPER_ENABLED| \
                                        PUE_1_PULL_SELECTED| \
                                        PUS_3_22K_OHM_PULL_UP| \
                                        HYS_1_HYSTERESIS_ENABLED)   

/* FUNCTION ************************************************************************************************************
 * 
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 * 
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void) {
    BOARD_InitPins();
}

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', enableClock: 'true'}
- pin_list: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_Iomuxc);           /* iomuxc clock (iomuxc_clk_enable): 0x03u */

  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_B0_00_GPIO1_IO00,        /* GPIO_AD_B0_00 is configured as GPIO1_IO00 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
    
    IOMUXC_SetPinMux(
      IOMUXC_SNVS_PMIC_ON_REQ_GPIO5_IO01,     /* SNVS_PMIC_ON_REQ is configured as GPIO5_IO01 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  
    IOMUXC_SetPinMux(
      IOMUXC_SNVS_PMIC_STBY_REQ_GPIO5_IO02,   /* SNVS_PMIC_STBY_REQ is configured as GPIO5_IO02 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_AD_B0_00_GPIO1_IO00,        /* GPIO_AD_B0_00 PAD functional properties : */
      0x10B0u);                               /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: R0/6
                                                 Speed Field: medium(100MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Keeper
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Down
                                                 Hyst. Enable Field: Hysteresis Disabled */
//  IOMUXC_SetPinConfig(
//    IOMUXC_SNVS_PMIC_ON_REQ_GPIO5_IO01,       /* IOMUXC_SNVS_PMIC_ON_REQ_GPIO5_IO01 PAD functional properties : */
//    KEY_PAD_CONFIG_DATA);                     /* Slew Rate Field: Slow Slew Rate
//    
//                                              */
 
    

}

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
