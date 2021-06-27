/**
 * @Copyright 			(c) 2019,mculover666 All rights reserved	
 * @filename  			bh1750_i2c_drv.h
 * @breif				Drive BH1750 based on iic1 commucation interface
 * @version
 *            			v1.0    完成基本驱动程序              mculover666    2019/7/15
 * @note            	移植说明（非常重要）：	
 *						1. bh1750_i2c_drv.h文件中的BH1750读写地址即可；
 * 						2. 此驱动程序需要STM32CubeMX生成的I2C初始化文件i2c.h和i2c.c支持;
 * 						3. 每次写完指令之后需要延时再读取数据（大于等于该模式的测量时间）。
 */

#include "bh1750.h"

/**
 * @brief		向BH1750发送一条指令
 * @param		cmd —— BH1750工作模式指令（在BH1750_MODE中枚举定义）
 * @retval		成功返回HAL_OK
*/
int	BH1750_Send_Cmd(BH1750_MODE cmd)
{
    lpi2c_master_transfer_t masterXfer = {0};
    status_t status;
    
    masterXfer.slaveAddress = BH1750_ADDR_WRITE >> 1;    // 7bit
    masterXfer.direction = kLPI2C_Write;
    masterXfer.subaddress = cmd;
    masterXfer.subaddressSize = 1;
    masterXfer.data = NULL;
    masterXfer.dataSize = 0;
    masterXfer.flags = kLPI2C_TransferDefaultFlag;
    
    status = LPI2C_MasterTransferBlocking(LPI2C2, &masterXfer);
    return status == kStatus_Success ? 0 : -1;
}
/**
 * @brief		从BH1750接收一次光强数据
 * @param		dat —— 存储光照强度的地址（两个字节数组）
 * @retval		成功 —— 返回HAL_OK
*/
int BH1750_Read_Dat(uint8_t* dat)
{
    lpi2c_master_transfer_t masterXfer = {0};
    status_t status;
    
    masterXfer.slaveAddress = BH1750_ADDR_WRITE >> 1;    // 7bit
    masterXfer.direction = kLPI2C_Read;
    masterXfer.subaddress = 0;
    masterXfer.subaddressSize = 0;
    masterXfer.data = dat;
    masterXfer.dataSize = 2;
    masterXfer.flags = kLPI2C_TransferDefaultFlag;
    
    status = LPI2C_MasterTransferBlocking(LPI2C2, &masterXfer);
    return status == kStatus_Success ? 0 : -1;
}
/**
 * @brief		将BH1750的两个字节数据转换为光照强度值（0-65535）
 * @param		dat  —— 存储光照强度的地址（两个字节数组）
 * @retval		成功 —— 返回光照强度值
*/
uint16_t BH1750_Dat_To_Lux(uint8_t* dat)
{
		uint16_t lux = 0;
		lux = dat[0];
		lux <<= 8;
		lux += dat[1];
		lux = (int)(lux / 1.2);
	
		return lux;
}
