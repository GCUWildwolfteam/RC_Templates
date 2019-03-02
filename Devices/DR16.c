/**
|-------------------------------- Copyright -----------------------------------|
|                                                                              |
|                     (C) Copyright 2019, Daqo Lee                             |
|                                                                              |
|                          By:GCU The wold of team                             |
|                     https://github.com/GCUWildwolfteam                       |
|------------------------------------------------------------------------------|
|  FileName    : DR16.c                                                
|  Version     : v1.0                                                            
|  Author      : Daqo Lee                                                       
|  Date        : 2019-01-08               
|  Libsupports : STM32F4xx_DFP ( 2.9.0)
|  Description :                                                       
|------------------------------declaration of end------------------------------|
 **/
/*--------------------- I N C L U D E - F I L E S ----------------------------*/
#include "DR16.h" 
	
/*-------------------------- D E F I N E S -----------------------------------*/

DR16_t DR16;

/*-----------L O C A L - F U N C T I O N S - P R O T O T Y P E S--------------*/

static void DR16_getMessage(uint8_t *DR16Buffer);

/*------------------G L O B A L - F U N C T I O N S --------------------------*/

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-08 17:08
	* @brief   
	* @param   void
	* @retval  void
	*/
void DR16_Init(void)
{
	DR16.ch1=0;
	DR16.ch2=0;
	DR16.ch3=0;
	DR16.ch4=0;
	DR16.keyBoard.key_code=0;
	
	DR16.switch_left = 0;
	DR16.switch_right =0 ;
	
	DR16.mouse.x = 0;	
	DR16.mouse.y = 0;
	DR16.mouse.z =0;
	
	DR16.mouse.press_left 	= 0;	
	DR16.mouse.press_right 	=0;
	
	DR16.p_DR16getMsg=DR16_getMessage;
}

/*---------------------L O C A L - F U N C T I O N S--------------------------*/

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-08 17:08
	* @brief   
	* @param   *DR16Buffer
	* @retval  void
	*/
static void DR16_getMessage(uint8_t *DR16Buffer)
{
	DR16.ch1 = (DR16Buffer[0] | DR16Buffer[1]<<8) & 0x07FF;
	DR16.ch1 -= 1024;
	DR16.ch2 = (DR16Buffer[1]>>3 | DR16Buffer[2]<<5 ) & 0x07FF;
	DR16.ch2 -= 1024;
	DR16.ch3 = (DR16Buffer[2]>>6 | DR16Buffer[3]<<2 | DR16Buffer[4]<<10) & 0x07FF;
	DR16.ch3 -= 1024;
	DR16.ch4 = (DR16Buffer[4]>>1 | DR16Buffer[5]<<7) & 0x07FF;		
	DR16.ch4 -= 1024;
	
	DR16.switch_left = ( (DR16Buffer[5] >> 4)& 0x000C ) >> 2;
	DR16.switch_right =  (DR16Buffer[5] >> 4)& 0x0003 ;
	
	DR16.mouse.x = DR16Buffer[6] | (DR16Buffer[7] << 8);	
	DR16.mouse.y = DR16Buffer[8] | (DR16Buffer[9] << 8);
	DR16.mouse.z = DR16Buffer[10]| (DR16Buffer[11] << 8);
	
	DR16.mouse.press_left 	= DR16Buffer[12];	
	DR16.mouse.press_right 	= DR16Buffer[13];
	
	DR16.keyBoard.key_code 	= DR16Buffer[14] | DR16Buffer[15] << 8; 
}


/*-----------------------------------FILE OF END------------------------------*/



