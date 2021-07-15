#ifndef _BSP_USDHC_H_
#define _BSP_USDHC_H_

#include "fsl_usdhc.h"
#include "board.h"
#include "fsl_sd.h"
#include "fsl_iomuxc.h"

#define SD_HOST_BASEADDR    USDHC2
#define SD_HOST_CLK_FREQ    BOARD_USDHC2_CLK_FREQ

int bsp_usdhc_host_init(char num, sd_card_t *card);
void bsp_usdhc_host_deinit(sd_card_t *card);
int sdcard_init(sd_card_t *card);
void sdcard_test(sd_card_t* sd_struct);

#endif /* _BSP_USDHC_H_ */
