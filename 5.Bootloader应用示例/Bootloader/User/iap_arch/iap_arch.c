/**
  ******************************************************************************
  * @file    iap_arch.c
  * @author  long
  * @version V1.0
  * @date    2019-11-23
  * @brief   xmodem 对外接口文件
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 STM32 F429 开发板  
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./iap_arch/iap_arch.h"   
#include <stdio.h>
#include "./usart/bsp_debug_usart.h"
#include "./internalFlash/bsp_internalFlash.h" 

/***************************************** Xmodem 接收数据相关 API *****************************************/

/**
 * @brief   Xmodem 接收数据的接口.
 * @param   *data ：接收数据
 * @param   *len ：接收数据的长度
 * @return  接收数据的状态
 */

int x_receive(__IO uint8_t **data, uint32_t len)
{
	__IO uint32_t timeout = RECEIVE_TIMEOUT;
	
	while (data_rx_flag == 0 && timeout--)   // 等待数据接收完成
	{
		if (timeout == 0)
		{
			return -1;    // 超时错误
		}
	}
	
	/* 获取接收数据 */
	*data = get_rx_data();
//	(void)data;
	get_rx_len();
	// if (len != )
	// {
	// 	return -1;    // 长度不正确返回错误
	// }
		
	return 0;
}

/**
 * @brief   Xmodem 发送一个字符的接口.
 * @param   ch ：发送的数据
 * @return  返回发送状态
 */
int x_transmit_ch(uint8_t ch)
{
	Usart_SendByte(DEBUG_USART, ch);
	
	return 0;
}

/**
 * @brief   Xmodem 擦除要保存接收数据的扇区.
 * @param   address ：根据地址来擦除扇区
 * @return  返回当前扇区剩余的大小
 */
uint32_t x_receive_flash_erasure(uint32_t address)
{
  sector_t sector_info;
  if (erasure_sector(address, 1))    // 擦除当前地址所在扇区
  {
    return 0;    // 擦除失败
  }

  sector_info = GetSector(address);    // 得到当前扇区的信息

  return (sector_info.size + sector_info.start_addr - address);     // 返回当前扇区剩余大小
}

/**
  * @brief   Xmodem 将接受到的数据保存到flash.
  * @param  start_address ：要写入的起始地址
  * @param  *data : 需要保存的数据
	* @param  len ：长度
  * @return 写入状态
 */
int x_receive_flash_writea(uint32_t start_address, const void *data, uint32_t len)
{
  if (flash_write_data(start_address, (uint8_t *)data, len) == 0)    // 擦除当前地址所在扇区
  {
    return 0;    // 写入成功
  }
  else
  {
    return -1;    // 写入失败
  }
  
}

/**************************************** Xmodem 接收数据相关 API END *****************************************/

/********************************************* APP 升级相关 API ************************************************/

/**
  * @brief  获取更新标志.
  * @param  无
  * @return 1：有可更新的app, 0：没有可更新的app
  */
uint8_t get_update_flag(void)
{
	uint8_t update_flag = 0;
	
	
	
	return update_flag;    // 返回标志
}

/**
  * @brief  获取 app 数据.
  * @param  start_address ：要获取的app的起始地址
  * @param  *data : 读数据缓冲区
	* @param  len ：长度
  * @return 写入状态
 */
int get_app_data(uint32_t start_address, const void *data, uint32_t len)
{
  if (flash_write_data(start_address, (uint8_t *)data, len) == 0)    // 擦除当前地址所在扇区
  {
    return 0;    // 写入成功
  }
  else
  {
    return -1;    // 写入失败
  }
  
}

/**
 * @brief   擦除app需要使用的扇区.
 * @param   address ：根据地址来擦除扇区
 * @return  返回当前扇区剩余的大小
 */
uint32_t app_flash_erasure(uint32_t address)
{
  sector_t sector_info;
  if (erasure_sector(address, 1))    // 擦除当前地址所在扇区
  {
    return 0;    // 擦除失败
  }

  sector_info = GetSector(address);    // 得到当前扇区的信息

  return (sector_info.size + sector_info.start_addr - address);     // 返回当前扇区剩余大小
}

/**
  * @brief  将 app 写到到flash.
  * @param  start_address ：要写入的起始地址
  * @param  *data : 需要保存的数据
	* @param  len ：长度
  * @return 写入状态
 */
int app_flash_writea(uint32_t start_address, const void *data, uint32_t len)
{
  if (flash_write_data(start_address, (uint8_t *)data, len) == 0)    // 擦除当前地址所在扇区
  {
    return 0;    // 写入成功
  }
  else
  {
    return -1;    // 写入失败
  }
  
}


