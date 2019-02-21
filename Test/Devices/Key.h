#ifndef _KEY_H
#define _KEY_H
#include "stm32f4xx.h"

/******************************************************************************/

/******************************************************************************/
#define KEY_GPIO_CLK             	RCC_AHB1Periph_GPIOD
#define KEY_PIN                  	GPIO_Pin_7
#define KEY_GPIO_PORT           	GPIOD

extern uint8_t KeyStatus;
void KEY_Init(void);
void KeyScan(void);
/******************************************************************************/
#endif

