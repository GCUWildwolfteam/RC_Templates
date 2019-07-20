/**
|-------------------------------- Copyright -----------------------------------|
|                                                                              |
|                     (C) Copyright 2019, Daqo Lee                             |
|                                                                              |
|                          By:GCU The wold of team                             |
|                     https://github.com/GCUWildwolfteam                       |
|------------------------------------------------------------------------------|
|  FileName    : Task_Can.c                                                
|  Version     : v1.0                                                            
|  Author      : Daqo Lee                                                       
|  Date        : 2019-01-11               
|  Libsupports : STM32F4xx_DFP ( 2.9.0)
|  Description :                                                       
|------------------------------declaration of end------------------------------|
 **/
/*--------------------- I N C L U D E - F I L E S ----------------------------*/

#include "stm32f4xx.h"
#include "Task_Init.h"


/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-11 11:13
	* @brief   
	* @param   void
	* @retval  void
	*/
int main(void)
{	
  /* ������ʼ���� */
	xTaskCreate(vTaskStart,           /* ������  */        
					  	"vTaskStart",         /* ������    */      
						  512,       			      /* ����ջ��С*/  
						  NULL,                 /* �������  */    
					  	1,       			        /* �������ȼ�*/
					  	&StartTaskHandler);   /* ������  */ 
	
  /* �������ȣ���ʼִ������ */
	vTaskStartScheduler(); 
	return 0;           
}

/*-----------------------------------FILE OF END------------------------------*/
