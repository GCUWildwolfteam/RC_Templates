
/**
  ************************************* Copyright ******************************   
  * (C) Copyright 2018,Daqo Lee,China, GCU.
  *		All Rights Reserved
  *
  * By(ZHE WOLF TEAM OF GCU ROBOT)
  * https://github.com/GCUWildwolfteam
  *
  * FileName   : LED.h   
  * Version    : v1.0		
  * Author     : Daqo Lee			
  * Date       : 2018-12-11         
  * Description:    
  * Function List:  
  	1. ....
  	   <version>: 		
  <modify staff>:
  		  <data>:
   <description>:  
  	2. ...
  ******************************************************************************
 */
#ifndef _LED_H_
#define _LED_H_
#include "stm32f4xx.h"

typedef enum
{
	LED0=0,
	LED1,
	LED2,
	LED3,
	LED4,
	LED5,
	LED6,
	LED_R, 
	LED_G		 
}LED_State_e;

/******************************************************************************/
#define LED_R_GPIO_CLK            RCC_AHB1Periph_GPIOB
#define LED_R_PIN                 GPIO_Pin_4
#define LED_R_GPIO_PORT           GPIOB

#define LED_G_GPIO_CLK            RCC_AHB1Periph_GPIOB
#define LED_G_PIN                 GPIO_Pin_5
#define LED_G_GPIO_PORT           GPIOB

#define LED0_GPIO_CLK             RCC_AHB1Periph_GPIOE
#define LED0_PIN                  GPIO_Pin_9
#define LED0_GPIO_PORT            GPIOE

#define LED1_GPIO_CLK             RCC_AHB1Periph_GPIOE
#define LED1_PIN                  GPIO_Pin_10
#define LED1_GPIO_PORT            GPIOE

#define LED2_GPIO_CLK             RCC_AHB1Periph_GPIOE
#define LED2_PIN                  GPIO_Pin_11
#define LED2_GPIO_PORT            GPIOE

#define LED3_GPIO_CLK             RCC_AHB1Periph_GPIOE
#define LED3_PIN                  GPIO_Pin_12
#define LED3_GPIO_PORT            GPIOE

#define LED4_GPIO_CLK             RCC_AHB1Periph_GPIOE
#define LED4_PIN                  GPIO_Pin_13
#define LED4_GPIO_PORT            GPIOE

#define LED5_GPIO_CLK             RCC_AHB1Periph_GPIOE
#define LED5_PIN                  GPIO_Pin_14
#define LED5_GPIO_PORT            GPIOE

#define LED6_GPIO_CLK             RCC_AHB1Periph_GPIOE
#define LED6_PIN                  GPIO_Pin_15
#define LED6_GPIO_PORT            GPIOE
/******************************************************************************/

#define LED_ON(x)			if((LED_State_e)x==LED_R)     {GPIOB->BSRRH|=LED_R_PIN;}\
											else if((LED_State_e)x==LED_G){GPIOB->BSRRH|=LED_G_PIN;}\
											else {GPIOE->BSRRH|=1<<(9+(LED_State_e)x);}
													
#define LED_OFF(x)		if((LED_State_e)x==LED_R)     {GPIOB->BSRRL|=LED_R_PIN;}\
											else if((LED_State_e)x==LED_G){GPIOB->BSRRL|=LED_G_PIN;}\
											else {GPIOE->BSRRL|=1<<(9+(LED_State_e)x);}
													
#define LED_TOGGLE(x)	if((LED_State_e)x==LED_R)			 {GPIOB->ODR ^=LED_R_PIN;}\
											else if((LED_State_e)x==LED_G) {GPIOB->ODR ^=LED_G_PIN;}\
											else {GPIOE->ODR ^= 1<<(9+(LED_State_e)x);}

/******************************************************************************/


void LED_Init(void);
#endif

