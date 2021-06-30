#include "bsp_elcdif.h"

uint16_t s_frameBuffer[2][LCD_HEIGHT][LCD_WIDTH];
/* 帧中断标志 */
volatile bool s_frameDone = false;

volatile uint32_t s_frame_count = 0;

static void elcdif_pixel_clock_init(void)
{
    /*
     * The desired output frame rate is 60Hz. So the pixel clock frequency is:
     * (800 + 1 + 22 + 46) * (480 + 1 + 22 + 23) * 60 = 27.4M.
     * (800 + 10 + 2 + 2) * (480 + 2 + 2 + 2) * 60 = 814 * 486 * 60 = 23.7M.
     * Here set the LCDIF pixel clock to 23M.
     */

    /*
     * Initialize the Video PLL.
     * Video PLL output clock is OSC24M * (loopDivider + (denominator / numerator)) / postDivider = 108MHz.
     * Video PLL output clock is OSC24M * (loopDivider + (denominator / numerator)) / postDivider = 92MHz.
     */
    clock_video_pll_config_t config = {
        .loopDivider = 36,
        .postDivider = 8,
        .numerator   = 0,
        .denominator = 0,
    };

    CLOCK_InitVideoPll(&config);

    /*
     * 000 derive clock from PLL2
     * 001 derive clock from PLL3 PFD3
     * 010 derive clock from PLL5
     * 011 derive clock from PLL2 PFD0
     * 100 derive clock from PLL2 PFD1
     * 101 derive clock from PLL3 PFD1
     */
    
    /* select PLL5 */
    CLOCK_SetMux(kCLOCK_LcdifPreMux, 2);

    /* set clock pre div */
    CLOCK_SetDiv(kCLOCK_LcdifPreDiv, 1);

    /* set clock div */
    CLOCK_SetDiv(kCLOCK_LcdifDiv, 1);
}

void bsp_elcdif_init(void)
{
    const elcdif_rgb_mode_config_t config = {
        .panelWidth    = LCD_WIDTH,
        .panelHeight   = LCD_HEIGHT,
        .hsw           = LCD_HSW,
        .hfp           = LCD_HFP,
        .hbp           = LCD_HBP,
        .vsw           = LCD_VSW,
        .vfp           = LCD_VFP,
        .vbp           = LCD_VBP,
        .polarityFlags = LCD_POL_FLAGS,
        .bufferAddr    = (uint32_t)s_frameBuffer[0],
        .pixelFormat   = LCDIF_PIXEL_FORMAT,
        .dataBus       = LCDIF_DATA_BUS,
    };
    
    ELCDIF_RgbModeInit(LCDIF, &config);
    
    elcdif_pixel_clock_init();
    
    /* ELCDIF interrupt */
    EnableIRQ(LCDIF_IRQn);
    ELCDIF_EnableInterrupts(LCDIF, kELCDIF_CurFrameDoneInterruptEnable);
}

void bsp_elcdif_deinit(void)
{
    ELCDIF_Deinit(LCDIF);
}

void bsp_elcdif_start(void)
{
    ELCDIF_RgbModeStart(LCDIF);
}

void bsp_elcdif_stop(void)
{
    ELCDIF_RgbModeStop(LCDIF);
}

void APP_FillFrameBuffer(uint16_t frameBuffer[LCD_HEIGHT][LCD_WIDTH], uint16_t color)
{
    memset(frameBuffer, 0, LCD_WIDTH * LCD_HEIGHT);
    
    uint32_t i,j; 
    
    for (i = 0; i < LCD_HEIGHT; i++) {
        for (j = 0; j < LCD_WIDTH; j++) {
            frameBuffer[i][j] = color;
        }
    }
}

void LCDIF_IRQHandler(void)
{
    uint32_t intStatus;

    intStatus = ELCDIF_GetInterruptStatus(LCDIF);

    ELCDIF_ClearInterruptStatus(LCDIF, intStatus);

    if (intStatus & kELCDIF_CurFrameDone) {
        /* 当前帧处理完成标志 */
        s_frameDone = true;
        /* 帧计数器 */
        s_frame_count++;
    }
}

void LCD_ChangeAndSetNextBuffer(void)
{
    static uint8_t frameBufferIndex = 0;

    /* 切换缓冲区号 */
    frameBufferIndex ^= 1U;

    /* 设置 ELCDIF 的下一个缓冲区地址 */
    ELCDIF_SetNextBufferAddr(LCDIF, (uint32_t)s_frameBuffer[frameBufferIndex]);

    /* 更新中断标志 */
    s_frameDone = false;
    /* 等待直至中断完成 */
    while (!s_frameDone) {
    }
}
