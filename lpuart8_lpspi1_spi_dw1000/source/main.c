#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "bsp_led.h"
#include "bsp_lpuart.h"
#include <stdio.h>
#include "bsp_lpspi.h"

/**
 * @brief    SPI发送指定长度的数据
 * @param    send_buf  —— 发送数据缓冲区首地址
 * @param    size      —— 要发送数据的字节数
 * @retval   成功返回0
 */
static int SPI_Transmit(uint8_t* send_buf, uint16_t size)
{
    lpspi_transfer_t masterXfer;
    status_t status;
    
    /*Start master transfer, transfer data to slave.*/
    masterXfer.txData   = send_buf;
    masterXfer.rxData   = NULL;
    masterXfer.dataSize = size;
    masterXfer.configFlags =
        LPSPI_MASTER_PCS_FOR_TRANSFER | kLPSPI_MasterPcsContinuous | kLPSPI_MasterByteSwap;
    
    status = LPSPI_MasterTransferBlocking(LPSPI1, &masterXfer);
    
    return status == kStatus_Success ? 0 : -1;
}

/**
 * @brief   SPI接收指定长度的数据
 * @param   recv_buf  —— 接收数据缓冲区首地址
 * @param   size      —— 要接收数据的字节数
 * @retval  成功返回0
 */
static int SPI_Receive(uint8_t* recv_buf, uint16_t size)
{
    lpspi_transfer_t masterXfer;
    status_t status;
    
    /*Start master transfer, transfer data to slave.*/
    masterXfer.txData   = NULL;
    masterXfer.rxData   = recv_buf;
    masterXfer.dataSize = size;
    masterXfer.configFlags =
        LPSPI_MASTER_PCS_FOR_TRANSFER | kLPSPI_MasterPcsContinuous | kLPSPI_MasterByteSwap;
    status = LPSPI_MasterTransferBlocking(LPSPI1, &masterXfer);
    
    return status == kStatus_Success ? 0 : -1;
}

uint32_t dw1000_read_device_id(void)
{
	int ret;
	uint8_t header = 0x00;
	uint32_t device_id = 0x0000;

	
	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	
	ret = SPI_Transmit(&header, 1);
	if (ret == -1) {
		printf("send header fail, err is %d\r\n", ret);
		return 0;
	}
	
	ret = SPI_Receive((uint8_t *)&device_id, 4);
	if (ret == -1) {
		printf("read device id fail, err is %d\r\n", ret);
		return 0;
	}
	
	return device_id;
}

int main(void)
{
    uint32_t device_id;
    
    /* Board pin, clock */
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
	
    /* bsp init */
    bsp_led_init();
    bsp_lpuart_init(8);
    bsp_lpspi_init(1);
    
    printf("Hello World!\r\n");
    
    device_id = dw1000_read_device_id();
    if (device_id != 0) {
        printf("device id is 0x%8x\r\n", device_id);
    } else {
        printf("device id read fail\r\n");
    }
        
	while (1) {
        bsp_led_ctl (0);
        SDK_DelayAtLeastUs(100000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
        
        bsp_led_ctl (1);
        SDK_DelayAtLeastUs(100000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    }
}
