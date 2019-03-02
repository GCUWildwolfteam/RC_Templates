/**
|-------------------------------- Copyright -----------------------------------|
|                                                                              |
|                     (C) Copyright 2019, Daqo Lee                             |
|                                                                              |
|                          By:GCU The wold of team                             |
|                     https://github.com/GCUWildwolfteam                       |
|------------------------------------------------------------------------------|
|  FileName    : Task_Ctrl.c                                                
|  Version     : v1.0                                                            
|  Author      : Daqo Lee                                                       
|  Date        : 2019-02-20               
|  Libsupports : STM32F4xx_DFP ( 2.9.0)
|  Description :                                                       
|------------------------------declaration of end------------------------------|
 **/
/*--------------------- I N C L U D E - F I L E S ----------------------------*/
#include "Task_Ctrl.h" 
#include "Joint.h"
#include "FreeRTOS.h"
#include "task.h"
#include "DR16.h"
#include "Servo.h"

/*-------------------------- D E F I N E S -----------------------------------*/

static TaskHandle_t xHandleCtrlChassis = NULL;
static TaskHandle_t xHandleCtrlGimbal = NULL;
static TaskHandle_t xHandleCtrlJoint = NULL;

/*-----------L O C A L - F U N C T I O N S - P R O T O T Y P E S--------------*/

static void vTaskCtrlChassis(void *pvParameters);
static void vTaskCtrlGimbal(void *pvParameters);
static void vTaskCtrlJoint(void *pvParameters);

/*------------------G L O B A L - F U N C T I O N S --------------------------*/
/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-02-20 15:18
	* @brief   控制任务创建函数
	* @param   void
	* @retval  void
	*/
void ControlTaskCreate(void)
{
	xTaskCreate(vTaskCtrlChassis,            /* 任务函数  */   
						  "vTaskCtrlChassis",          /* 任务名    */ 
						  128,       			             /* 任务栈大小*/
						  NULL,                        /* 任务参数  */
					    2,       			               /* 任务优先级*/
						  &xHandleCtrlChassis);        /* 任务句柄  */ 
	xTaskCreate(vTaskCtrlGimbal,            
					    "vTaskCtrlGimbal",          
				    	128,       			   
				    	NULL,                 
					    2,       			   
					    &xHandleCtrlGimbal);
	xTaskCreate(vTaskCtrlJoint,            
					    "vTaskCtrlJoint",          
				    	128,       			   
				    	NULL,                 
					    2,       			   
					    &xHandleCtrlJoint);
}

/*---------------------L O C A L - F U N C T I O N S--------------------------*/
/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-02-20 15:18
	* @brief   底盘控制任务
	* @param   void
	* @retval  void
	*/
static void vTaskCtrlChassis(void *pvParameters)
{
	portTickType CurrentControlTick = 0;
  while(1)
	{
	  vTaskDelayUntil(&CurrentControlTick, 5 / portTICK_RATE_MS);/*5ms延时*/
	}
}

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-02-20 15:18
	* @brief   云台控制任务
	* @param   void
	* @retval  void
	*/
static void vTaskCtrlGimbal(void *pvParameters)
{
	portTickType CurrentControlTick = 0;
  while(1)
	{
		
		
	  vTaskDelayUntil(&CurrentControlTick, 5 / portTICK_RATE_MS);/*5ms延时*/
	}
}

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-02-20 15:18
	* @brief   关节控制任务
	* @param   void
	* @retval  void
	*/
static void vTaskCtrlJoint(void *pvParameters)
{
	portTickType CurrentControlTick = 0;
	vTaskDelay(500);
	Dynamixel1_setSyncMsg(SPEED,2,0x01,100,0x02,0);
	vTaskDelay(5);
	Dynamixel1_setSyncMsg(ACC,2,0x01,80,0x02,0);
  while(1)
	{
//		Thigh_M6020Ctrl();
//		Joint_MotionModel(DR16.ch1,DR16.ch2,DR16.ch3);
		
    Joint_MotionTest();
	  vTaskDelayUntil(&CurrentControlTick, 5 / portTICK_RATE_MS);/*5ms延时*/
	}
}
/*-----------------------------------FILE OF END------------------------------*/

