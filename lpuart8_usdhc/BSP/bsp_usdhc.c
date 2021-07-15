#include "bsp_usdhc.h"
#include <stdio.h>

extern sd_card_t g_sd;
static sdmmchost_t s_host;

static void usdhc_clock_init(char num)
{
    /*configure system pll PFD0 fractional divider to 24, output clock is 528MHZ * 18 / 24 = 396 MHZ*/
    CLOCK_InitSysPfd(kCLOCK_Pfd0, 24U);

    switch (num) {
        case 1:
            /* Configure USDHC clock source and divider */
            // USDHC clock root frequency maximum: 198MHz.
            CLOCK_SetDiv(kCLOCK_Usdhc1Div, 1U); 
            CLOCK_SetMux(kCLOCK_Usdhc1Mux, 1U);
            break;
        case 2:
            CLOCK_SetDiv(kCLOCK_Usdhc2Div, 1U);
            CLOCK_SetMux(kCLOCK_Usdhc2Mux, 1U);
            break;
        default:
            break;
    }
}

static void usdhc_pin_init(char num, uint32_t freq)
{
    uint32_t speed = 0U, strength = 0U;

    if (freq <= 50000000)
    {
        speed    = 0U;
        strength = 7U;
    }
    else if (freq <= 100000000)
    {
        speed    = 2U;
        strength = 7U;
    }
    else
    {
        speed    = 3U;
        strength = 7U;
    }

    switch (num) {
        case 1:
            IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_00_USDHC1_CMD,
                                IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_SRE_MASK |
                                    IOMUXC_SW_PAD_CTL_PAD_PKE_MASK | IOMUXC_SW_PAD_CTL_PAD_PUE_MASK |
                                    IOMUXC_SW_PAD_CTL_PAD_HYS_MASK | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |
                                    IOMUXC_SW_PAD_CTL_PAD_DSE(strength));
            IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_01_USDHC1_CLK,
                                IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_SRE_MASK |
                                    IOMUXC_SW_PAD_CTL_PAD_HYS_MASK | IOMUXC_SW_PAD_CTL_PAD_PUS(0) |
                                    IOMUXC_SW_PAD_CTL_PAD_DSE(strength));
            IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_02_USDHC1_DATA0,
                                IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_SRE_MASK |
                                    IOMUXC_SW_PAD_CTL_PAD_PKE_MASK | IOMUXC_SW_PAD_CTL_PAD_PUE_MASK |
                                    IOMUXC_SW_PAD_CTL_PAD_HYS_MASK | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |
                                    IOMUXC_SW_PAD_CTL_PAD_DSE(strength));
            break;
        case 2:
            IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_05_USDHC2_CMD,
                                IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_SRE_MASK |
                                    IOMUXC_SW_PAD_CTL_PAD_PKE_MASK | IOMUXC_SW_PAD_CTL_PAD_PUE_MASK |
                                    IOMUXC_SW_PAD_CTL_PAD_HYS_MASK | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |
                                    IOMUXC_SW_PAD_CTL_PAD_DSE(strength));
            IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_04_USDHC2_CLK,
                                IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_SRE_MASK |
                                    IOMUXC_SW_PAD_CTL_PAD_HYS_MASK | IOMUXC_SW_PAD_CTL_PAD_PUS(0) |
                                    IOMUXC_SW_PAD_CTL_PAD_DSE(strength));
            IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_04_USDHC2_DATA0,
                                IOMUXC_SW_PAD_CTL_PAD_SPEED(speed) | IOMUXC_SW_PAD_CTL_PAD_SRE_MASK |
                                    IOMUXC_SW_PAD_CTL_PAD_PKE_MASK | IOMUXC_SW_PAD_CTL_PAD_PUE_MASK |
                                    IOMUXC_SW_PAD_CTL_PAD_HYS_MASK | IOMUXC_SW_PAD_CTL_PAD_PUS(1) |
                                    IOMUXC_SW_PAD_CTL_PAD_DSE(strength));
            break;
        default:
            break;
    }
}


int bsp_usdhc_host_init(char num, sd_card_t *card)
{
    usdhc_clock_init(2);
    
    card->host = &s_host;
    card->host->hostController.base = SD_HOST_BASEADDR;
    card->host->hostController.sourceClock_Hz = SD_HOST_CLK_FREQ;
    
    if(SD_HostInit(card) != kStatus_Success) {
        return -1;
    }
    
    return 0;  
}

int sdcard_init(sd_card_t *card)
{
    /* Init card. */
    if (SD_CardInit(card))//重新初始化SD卡
    {
        printf("\r\nSD card init failed.\r\n");
        return -1;
    }

    printf("\r\nSD card init success.\r\n");
    return 0;
}

void bsp_usdhc_host_deinit(sd_card_t *card)
{
    SD_HostDeinit(card);
}

/**
* 函数功能:通过串口输出SD卡信息
* 函数参数: sd_struct,SD卡结构体指针；
*/
static void CardInformationLog(sd_card_t *card)
{
  assert(card);
  
    printf("\r\ncard size:%d * %d bytes\r\n", card->blockCount, card->blockSize);
      if (card->operationVoltage == kSDMMC_OperationVoltage330V)
      {
        printf("\r\n  sdcard voltage : 3.3V\r\n");
      }
      else if (card->operationVoltage == kSDMMC_OperationVoltage180V)
      {
        printf("\r\n  sdcard voltage : 1.8V\r\n");
      }
      
      if (card->currentTiming == kSD_TimingSDR12DefaultMode)
      {
        if (card->operationVoltage == kSDMMC_OperationVoltage330V)
        {
            printf("\r\n  currentTiming:normal\r\n");
        }
        else if (card->operationVoltage == kSDMMC_OperationVoltage180V)
        {
          printf("\r\n  currentTiming:SDR12\r\n");
        }
      }
      else if (card->currentTiming == kSD_TimingSDR25HighSpeedMode)
      {
        if (card->operationVoltage == kSDMMC_OperationVoltage180V)
        {
          printf("\r\n  currentTiming: SDR25\r\n");
        }
        else
        {
          printf("\r\n  currentTiming: High Speed\r\n");
        }
      }
      else if (card->currentTiming == kSD_TimingSDR50Mode)
      {
        printf("\r\n  currentTiming: SDR50\r\n");
      }
      else if (card->currentTiming == kSD_TimingSDR104Mode)
      {
        printf("\r\n  currentTiming: SDR104\r\n");
      }
      else if (card->currentTiming == kSD_TimingDDR50Mode)
      {
        printf("\r\n  currentTiming: DDR50\r\n");
      }
      
      printf("\r\n  Freq : %d HZ\r\n", card->busClock_Hz);
}

void sdcard_test(sd_card_t* sd_struct)
{
    sd_card_t *card = sd_struct;
    
    /* 打印卡片工作信息 */
    CardInformationLog(card);
//    /* 读写测试 */
//    if(AccessCard(card)==kStatus_Success)
//        printf("\r\nSDCARD test success.\r\n");
//    else
//        printf("\r\nSDCARD test fail.\r\n");
}