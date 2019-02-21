/**
|-------------------------------- Copyright -----------------------------------|
|                                                                              |
|                        (C) Copyright 2019, Daqo Lee,                         |
|                                                                              |
|                            By:GCU The wold of team                           |
|                         https://github.com/GCUWildwolfteam                   |
|------------------------------------------------------------------------------|
|--FileName    : Joint.h                                                
|--Version     : v1.0                                                            
|--Author      : Daqo Lee                                                       
|--Date        : 2019-02-20               
|--Libsupports : STM32F4xx_DFP ( 2.9.0)
|--Description :                                                       
|---------------------------------declaration of end----------------------------|
 **/
#ifndef __JOINT_H 
#define __JOINT_H 

  
/*--------------------- I N C L U D E - F I L E S ----------------------------*/

#include "stm32f4xx.h"

/*-------------------------G L O B A L - T Y P E S----------------------------*/



/*------------------------G L O B A L - M A C R O S --------------------------*/



/*----------------------G L O B A L - D E F I N E S---------------------------*/



/*-----------G L O B A L - F U N C T I O N S - P R O T O T Y P E S------------*/

void Thigh_M6020Ctrl(void);
void Joint_MotionModel(int16_t Vx, int16_t Vy, int16_t Omega);
void Joint_MotionTest(void);

#endif	// __JOINT_H
/*----------------------------------FILE OF END-------------------------------*/



 

