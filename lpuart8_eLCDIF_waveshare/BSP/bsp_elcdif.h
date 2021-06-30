#ifndef _BSP_LCDIF_H_
#define _BSP_LCDIF_H_

#include "fsl_elcdif.h"
#include "board.h"

#define LCD_WIDTH   10
#define LCD_HEIGHT  480

#define LCD_HSW     1
#define LCD_HFP     22
#define LCD_HBP     46
#define LCD_VSW     1
#define LCD_VFP     22
#define LCD_VBP     22
#define LCD_POL_FLAGS       (kELCDIF_DataEnableActiveHigh | \
                            kELCDIF_VsyncActiveLow | \
                            kELCDIF_HsyncActiveLow | \
                            kELCDIF_DriveDataOnRisingClkEdge)

#define LCDIF_DATA_BUS      kELCDIF_DataBus16Bit
#define LCDIF_PIXEL_FORMAT  kELCDIF_PixelFormatRGB565

/* Frame buffer data alignment, for better performance, the LCDIF frame buffer should be 64B align. */
#define FRAME_BUFFER_ALIGN 64

/** 
  * @brief  LCD color  
  * @note   RGB565
  */ 
#define LCD_COLOR_BLUE          0x001F
#define LCD_COLOR_GREEN         0x07E0
#define LCD_COLOR_RED           0xF800
#define LCD_COLOR_CYAN          0x07FF
#define LCD_COLOR_MAGENTA       0xF81F
#define LCD_COLOR_YELLOW        0xFFE0
#define LCD_COLOR_LIGHTBLUE     0x841F
#define LCD_COLOR_LIGHTGREEN    0x87F0
#define LCD_COLOR_LIGHTRED      0xFC10
#define LCD_COLOR_LIGHTCYAN     0x87FF
#define LCD_COLOR_LIGHTMAGENTA  0xFC1F
#define LCD_COLOR_LIGHTYELLOW   0xFFF0
#define LCD_COLOR_DARKBLUE      0x0010
#define LCD_COLOR_DARKGREEN     0x0400
#define LCD_COLOR_DARKRED       0x8000
#define LCD_COLOR_DARKCYAN      0x0410
#define LCD_COLOR_DARKMAGENTA   0x8010
#define LCD_COLOR_DARKYELLOW    0x8400
#define LCD_COLOR_WHITE         0xFFFF
#define LCD_COLOR_LIGHTGRAY     0xD69A
#define LCD_COLOR_GRAY          0x8410
#define LCD_COLOR_DARKGRAY      0x4208
#define LCD_COLOR_BLACK         0x0000
#define LCD_COLOR_BROWN         0xA145
#define LCD_COLOR_ORANGE        0xFD20

/*RGB565 颜色转换 */
/* 将 8 位 R,G,B 转化为 16 位 RGB565 格式 */
#define RGB(R,G,B) (((R >> 3) << 11) | ((G >> 2) << 5) | (B >> 3))

/* 常用颜色 */
enum {
    CL_WHITE = RGB(255,255,255), /* 白色 */
    CL_BLACK = RGB( 0, 0, 0), /* 黑色 */
    CL_RED = RGB(255, 0, 0), /* 红色 */
    CL_GREEN = RGB( 0,255, 0), /* 绿色 */
    CL_BLUE = RGB( 0, 0,255), /* 蓝色 */
    CL_YELLOW = RGB(255,255, 0), /* 黄色 */
/*... 省略其余大部分颜色...*/
};

extern uint16_t s_frameBuffer[2][LCD_HEIGHT][LCD_WIDTH];
extern volatile bool s_frameDone;
extern volatile uint32_t s_frame_count;

void bsp_elcdif_init(void);
void bsp_elcdif_deinit(void);
void bsp_elcdif_start(void);
void bsp_elcdif_stop(void);
void APP_FillFrameBuffer(uint16_t frameBuffer[LCD_HEIGHT][LCD_WIDTH], uint16_t color);
void LCD_ChangeAndSetNextBuffer(void);

#endif /* _BSP_LCDIF_H_ */
