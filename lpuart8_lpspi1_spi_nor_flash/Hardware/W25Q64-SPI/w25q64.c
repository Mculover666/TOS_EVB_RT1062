/**
 * @file    w25q64.c
 * @brief   W25Q64��������
 * @author  Mculover666<http://www.mculover666.cn>
 * @note    �������������STM32CubeMX���ɵ�SPI1��ʼ������
*/

#include "w25q64.h"

/* ��ֲ��غ��� */

/**
 * @brief    SPI����ָ�����ȵ�����
 * @param    send_buf  ���� �������ݻ������׵�ַ
 * @param    size      ���� Ҫ�������ݵ��ֽ���
 * @retval   �ɹ�����0
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
    
    status = LPSPI_MasterTransferBlocking(SPI_Handle, &masterXfer);
    
    return status == kStatus_Success ? 0 : -1;
}

/**
 * @brief   SPI����ָ�����ȵ�����
 * @param   recv_buf  ���� �������ݻ������׵�ַ
 * @param   size      ���� Ҫ�������ݵ��ֽ���
 * @retval  �ɹ�����0
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
    status = LPSPI_MasterTransferBlocking(SPI_Handle, &masterXfer);
    
    return status == kStatus_Success ? 0 : -1;
}

/**
 * @brief   ��ȡFlash�ڲ���ID
 * @param   none
 * @retval  �ɹ�����device_id
 */
uint16_t W25QXX_ReadID(void)
{
    uint8_t recv_buf[2] = {0};    //recv_buf[0]���Manufacture ID, recv_buf[1]���Device ID
    uint16_t device_id = 0;
    uint8_t send_data[4] = {ManufactDeviceID_CMD,0x00,0x00,0x00};   //���������ݣ�����+��ַ
    
    /* ���Ͳ���ȡ���� */
    if (0 == SPI_Transmit(send_data, 4)) {
        if (0 == SPI_Receive(recv_buf, 2)) {
            device_id = (recv_buf[0] << 8) | recv_buf[1];
        }
    }
    
    return device_id;
}

/**
 * @brief     ��ȡW25QXX��״̬�Ĵ�����W25Q64һ����2��״̬�Ĵ���
 * @param     reg  ���� ״̬�Ĵ������(1~2)
 * @retval    ״̬�Ĵ�����ֵ
 */
static uint8_t W25QXX_ReadSR(uint8_t reg)
{
    uint8_t result = 0; 
    uint8_t send_buf[4] = {0x00,0x00,0x00,0x00};
    switch(reg)
    {
        case 1:
            send_buf[0] = READ_STATU_REGISTER_1;
        case 2:
            send_buf[0] = READ_STATU_REGISTER_2;
        case 0:
        default:
            send_buf[0] = READ_STATU_REGISTER_1;
    }

    if (0 == SPI_Transmit(send_buf, 4)) {
        if (0 == SPI_Receive(&result, 1)) {
            
            return result;
        }
    }
    
    return 0;
}

/**
 * @brief    �����ȴ�Flash���ڿ���״̬
 * @param   none
 * @retval  none
 */
static void W25QXX_Wait_Busy(void)
{
    while((W25QXX_ReadSR(1) & 0x01) == 0x01); // �ȴ�BUSYλ���
}

/**
 * @brief   ��ȡSPI FLASH����
 * @param   buffer      ���� ���ݴ洢��
 * @param   start_addr  ���� ��ʼ��ȡ�ĵ�ַ(���32bit)
 * @param   nbytes      ���� Ҫ��ȡ���ֽ���(���65535)
 * @retval  �ɹ�����0��ʧ�ܷ���-1
 */
int W25QXX_Read(uint8_t* buffer, uint32_t start_addr, uint16_t nbytes)
{
    uint8_t cmd = READ_DATA_CMD;
    
    start_addr = start_addr << 8;
    
	W25QXX_Wait_Busy();
    
    SPI_Transmit(&cmd, 1);
    
    if (0 == SPI_Transmit((uint8_t*)&start_addr, 3)) {
        if (0 == SPI_Receive(buffer, nbytes)) {
           
            
            return 0;
        }
    }
    
   
    return -1;
}

/**
 * @brief    W25QXXдʹ��,��S1�Ĵ�����WEL��λ
 * @param    none
 * @retval
 */
void W25QXX_Write_Enable(void)
{
    uint8_t cmd= WRITE_ENABLE_CMD;

    SPI_Transmit(&cmd, 1);

    W25QXX_Wait_Busy();

}

/**
 * @brief    W25QXXд��ֹ,��WEL����
 * @param    none
 * @retval    none
 */
void W25QXX_Write_Disable(void)
{
    uint8_t cmd = WRITE_DISABLE_CMD;
    
    SPI_Transmit(&cmd, 1);
    
    W25QXX_Wait_Busy();
}

/**
 * @brief    W25QXX����һ������
 * @param   sector_addr    ���� ������ַ ����ʵ����������
 * @retval  none
 * @note    ��������
 */
void W25QXX_Erase_Sector(uint32_t sector_addr)
{
    uint8_t cmd = SECTOR_ERASE_CMD;
    
    sector_addr *= 4096;    //ÿ������16��������ÿ�������Ĵ�С��4KB����Ҫ����Ϊʵ�ʵ�ַ
    sector_addr <<= 8;
    
    W25QXX_Write_Enable();  //����������д��0xFF����Ҫ����дʹ��
    W25QXX_Wait_Busy();        //�ȴ�дʹ�����
    
    SPI_Transmit(&cmd, 1);
    
    SPI_Transmit((uint8_t*)&sector_addr, 3);
    
    W25QXX_Wait_Busy();       //�ȴ������������
}

/**
 * @brief    ҳд�����
 * @param    dat ���� Ҫд������ݻ������׵�ַ
 * @param    WriteAddr ���� Ҫд��ĵ�ַ
 * @param   byte_to_write ���� Ҫд����ֽ�����0-256��
 * @retval    none
 */
void W25QXX_Page_Program(uint8_t* dat, uint32_t WriteAddr, uint16_t nbytes)
{
    uint8_t cmd = PAGE_PROGRAM_CMD;
    
    WriteAddr <<= 8;
    
    W25QXX_Write_Enable();
    
    SPI_Transmit(&cmd, 1);

    SPI_Transmit((uint8_t*)&WriteAddr, 3);
    
    SPI_Transmit(dat, nbytes);
    
    W25QXX_Wait_Busy();
}
