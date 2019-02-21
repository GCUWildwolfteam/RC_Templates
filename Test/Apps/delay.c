/**
  ******************************************************************************
  * @file    delay.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   ��ʱӦ�ú����ӿ�
  ******************************************************************************
  */
  
  
#include "delay.h"

/**
  * @brief  ���뼶��ʱ
  * @param  _ms ��ʱ������
  * @retval None
  */
void delay_ms(uint32_t _ms){
	SysTick_Config(SystemCoreClock/1000);
	for(u32 i = 0; i < _ms; i++){
		while(!((SysTick->CTRL)&(1<<16)));
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

/**
  * @brief  ΢�뼶��ʱ
  * @param  _us ��ʱ΢����
  * @retval None
  */
void delay_us(uint32_t _us){
	SysTick_Config(SystemCoreClock/1000000);
	for(u32 i = 0; i < _us; i++){
		while(!((SysTick->CTRL)&(1<<16)));
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}


