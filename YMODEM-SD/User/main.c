/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ʹ�ð������Ʋʵ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� STM32 F429 ������
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "./led/bsp_led.h"
#include "./key/bsp_key.h" 
#include "./usart/bsp_debug_usart.h"
#include "./ymodem/ymodem.h"
#include "./FATFS/ff.h"

FATFS fs;													/* FatFs�ļ�ϵͳ���� */

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	uint8_t update_flag = 0;
  FRESULT res_sd;                /* �ļ�������� */
	
  /*��ʼ������*/
  LED_GPIO_Config();
  Key_GPIO_Config();
	Debug_USART_Config();
  
  //���ⲿ sd �����ļ�ϵͳ
	res_sd = f_mount(&fs, "0:" ,1);
	if(res_sd!=FR_OK)
  {
    LED1_ON;
    printf("����SD�������ļ�ϵͳʧ�ܡ�(%d)\r\n",res_sd);
    printf("��������ԭ��SD����ʼ�����ɹ���\r\n");
		while(1);
  }

	/* ��ѯ����״̬��������������תLED */ 
	while(1)
	{
		if( Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON  )
		{
			/* ��ȡ�������� */
      update_flag = 1;
		}
		
		if (update_flag)
		{
      LED2_ON;
			ymodem_receive();
      update_flag = 0;
      LED2_OFF;
		}
	}
}



/*********************************************END OF FILE**********************/
