/**
|-------------------------------- Copyright -----------------------------------|
|                                                                              |
|                     (C) Copyright 2019, Daqo Lee                             |
|                                                                              |
|                          By:GCU The wold of team                             |
|                     https://github.com/GCUWildwolfteam                       |
|------------------------------------------------------------------------------|
|--FileName    : Camera.c                                              
|--Version     : v1.0                                                          
|--Author      : Daqo Lee                                                     
|--Date        : 2019-03-17             
|--Libsupports : STM32F4xx_DFP ( 2.9.0)
|--Description :                                                     
|-----------------------------declaration of end-----------------------------|
 **/
/*--------------------- I N C L U D E - F I L E S ----------------------------*/
#include "Camera.h" 
#include "User_Config.h"
/*-------------------------- D E F I N E S -----------------------------------*/

Camera_t Camera;

uint8_t walk_status_flag;

/*
	λ��0				1		 		2				3			
			90��	 135��    ��			��
*/

/*-----------L O C A L - F U N C T I O N S - P R O T O T Y P E S--------------*/



/*------------------G L O B A L - F U N C T I O N S --------------------------*/

void Camera_getMassage(uint8_t *CameraBuff)
{
  for(uint8_t i=0;i<15;i++)
	{
		if(CameraBuff[i]=='$')
		{
		  if(CameraBuff[i+4] == ',' && CameraBuff[i+8] == ',')
			{
				if(CameraBuff[i+1]=='0')
				{
					Camera.Angle =  ((CameraBuff[i+2] - '0') * 10
							           + (CameraBuff[i+3] - '0'))*-1;
				}
				else
        {
					Camera.Angle = (CameraBuff[i+2] - '0') * 10
					               + (CameraBuff[i+3] - '0');
				}


				Camera.Offset =
			  	(CameraBuff[i+5] - '0') * 100
			  +	(CameraBuff[i+6] - '0') * 10
        + (CameraBuff[i+7] - '0');

				Camera.Flag = CameraBuff[i+9] - '0';
			}
			else
			{
				
			}
			
		}
	}
	
	/*

	90�㣺2
	135�㣺4
 	����5 
	�죺6
	*/
	
	switch(Camera.Flag)
	{
		case RIGHT_ANGLE://90��
			walk_status_flag |= 1<<RIGHT_ANGLE;
			break;
		case OBTUSE_ANGLE://135��
			walk_status_flag |= 1<<OBTUSE_ANGLE;
			break;
		case BLUE://��
			walk_status_flag |= 1<<BLUE;
			break;
		case RED://��
			walk_status_flag |= 1<<RED;
			break;
		default:
			break;
	}
	
}



	/**
	* @brief   ��ȡ�Ӿ�ʶ��״̬
	* @param   ����
	* @retval  ״̬
	*/
uint8_t GetCameraFlag(uint8_t Action)
{
	if(Action == LIMIT)
	{
#if CAMP_COLOR == 0 //��
		return walk_status_flag & (1<<RED);
#elif	CAMP_COLOR == 1 //��
		return walk_status_flag & (1<<BLUE);
#endif
	}
	else
	{
		return walk_status_flag & (1<<Action);
	}
	
	
}

void ResetCameraFlag(uint8_t Action)
{
	if(Action == LIMIT)
	{
#if CAMP_COLOR == 0 //��
		walk_status_flag &= ~(1<<RED);
#elif CAMP_COLOR == 1 //��
		walk_status_flag &= ~(1<<BLUE);
#endif
	}
	else
	{
		walk_status_flag &= ~(1<<Action);
	}
	
}




/*---------------------L O C A L - F U N C T I O N S--------------------------*/



/*-----------------------------------file of end------------------------------*/


