/*
 ************************************* Copyright ******************************   
 * File       : Key.c  
 * Author     : Daqo Lee 
 * Version    : v1.0					
 * Date       : 2019-01-08         
 * @brief     ï¼?  
 * 
 *******************************************************************************
 * @attention ï¼?
 *
 *******************************************************************************
 */
#include "Key.h"
/******************************************************************************/
uint8_t KeyStatus=0;
/******************************************************************************/


/* --------------------------------------------------------------------- */
/*
 * @Name    KEY_Init
 * @brief  
 * @param   None
 * @retval
 * @author  Daqo Lee 
 * @Data    2019-01-08
 */
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	RCC_AHB1PeriphClockCmd(KEY_GPIO_CLK, ENABLE); 		
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;   
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
	GPIO_InitStructure.GPIO_Pin   = KEY_PIN;	 
	
	GPIO_Init(KEY_GPIO_PORT, &GPIO_InitStructure);
}

void KeyScan(void)
{
	
	KeyStatus=GPIO_ReadInputDataBit (KEY_GPIO_PORT,KEY_PIN);
}

