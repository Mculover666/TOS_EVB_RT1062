#ifndef _BSP_LPSPI_H_
#define _BSP_LPSPI_H_

#include "fsl_lpspi.h"
#include "board.h"

/* Select USB1 PLL PFD0 (720 MHz) as lpspi clock source */
#define LPSPI_CLOCK_SOURCE_SELECT (1U)
/* Clock divider for master lpspi clock source */
#define LPSPI_CLOCK_SOURCE_DIVIDER (7U)

/* Transfer baudrate - 500k */
#define TRANSFER_BAUDRATE 80000000U

#define LPSPI_MASTER_PCS_FOR_INIT     (kLPSPI_Pcs2)
#define LPSPI_MASTER_PCS_FOR_TRANSFER (kLPSPI_MasterPcs2)

#define LPSPI_MASTER_CLK_FREQ (CLOCK_GetFreq(kCLOCK_Usb1PllPfd0Clk) / (LPSPI_CLOCK_SOURCE_DIVIDER + 1U))

void bsp_lpspi_init(char num);
void bsp_lpspi_deinit(char num);

#endif /* _BSP_LPSPI_H_ */
