/**
  ******************************************************************************
  * @file    delay.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   延时应用函数接口
  ******************************************************************************
  */
  
  
#include "delay.h"

/**
  * @brief  毫秒级延时
  * @param  _ms 延时毫秒数
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
  * @brief  微秒级延时
  * @param  _us 延时微秒数
  * @retval None
  */
void delay_us(uint32_t _us){
	SysTick_Config(SystemCoreClock/1000000);
	for(u32 i = 0; i < _us; i++){
		while(!((SysTick->CTRL)&(1<<16)));
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}


