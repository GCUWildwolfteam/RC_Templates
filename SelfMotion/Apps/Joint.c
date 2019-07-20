/**
|-------------------------------- Copyright -----------------------------------|
|                                                                              |
|                     (C) Copyright 2019, Daqo Lee                             |
|                                                                              |
|                          By:GCU The wold of team                             |
|                     https://github.com/GCUWildwolfteam                       |
|------------------------------------------------------------------------------|
|  FileName    : Joint.c                                                
|  Version     : v1.0                                                            
|  Author      : Daqo Lee                                                       
|  Date        : 2019-01-09               
|  Libsupports : STM32F4xx_DFP ( 2.9.0)
|  Description :                                                       
|------------------------------declaration of end------------------------------|
 **/
/*--------------------- I N C L U D E - F I L E S ----------------------------*/
#include "Joint.h"
#include "delay.h"
#include "Motor.h"
#include "Servo.h"
#include "DR16.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Curve.h"
#include "Filter.h" 
#include "Gyro.h"
#include "Camera.h"
#include "Photoelectric.h"
#include "Key.h"
#include "User_Config.h"

/*-------------------------- D E F I N E S -----------------------------------*/
Joint_t Joint;

/*-----------L O C A L - F U N C T I O N S - P R O T O T Y P E S--------------*/

static int16_t Joint_getThighTarAng(int16_t TarAng ,float Phase,float Temp);
static int16_t Joint_getCrusTarAng(int16_t TarAng ,float Phase,float Temp);
static int16_t Joint_getHipTarAng(int16_t TarAng ,float Phase,float Temp);

/*------------------G L O B A L - F U N C T I O N S --------------------------*/
	/**
	* @Data    2019-01-08 14:49
	* @brief   关节初始化
	* @param   void
	* @retval  void
	*/
void Joint_Init(void)
{
	Joint.PID_Spin.maxInput=360;
	//大腿
	DigitalServo.MX_64[0].MiddleAngle = 3463;
	DigitalServo.MX_64[2].MiddleAngle = 3000;
	DigitalServo.MX_64[4].MiddleAngle = 3096;
	DigitalServo.MX_64[6].MiddleAngle = 2110;	
	
	//小腿
	DigitalServo.MX_64[1].MiddleAngle = 1000;
	DigitalServo.MX_64[3].MiddleAngle = 3814;
	DigitalServo.MX_64[5].MiddleAngle = 1000;
	DigitalServo.MX_64[7].MiddleAngle = 2473;

	DigitalServo.MX_64[8].MiddleAngle = 2068;
	DigitalServo.MX_64[9].MiddleAngle = 2048;
	DigitalServo.MX_64[10].MiddleAngle = 2048;
	DigitalServo.MX_64[11].MiddleAngle = 2048;
	
	DigitalServo.MX_64[12].MiddleAngle = 3180;//2150
	DigitalServo.MX_64[13].MiddleAngle = 2100;//3050
	
	
	PID_StructInit(&Joint.PID_X, POSITION_PID, 800, 500, 2, 0, 0);
	PID_StructInit(&Joint.PID_Y, POSITION_PID, 800, 500, 2, 0, 0);
	PID_StructInit(&Joint.PID_Z, POSITION_PID, 300, 200, 0, 0, 0);
	PID_StructInit(&Joint.PID_P, POSITION_PID, 500, 200, 0, 0, 0.01);
	PID_StructInit(&Joint.PID_Spin, POSITION_PID, 100, 100, 4, 0, 0);
}
/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-08 14:49
	* @brief   关节电机控制
	* @param   void
	* @retval  void
	*/
void Thigh_M6020Ctrl(void)
{
	Motor.p_M6020setTarAngle(0,-DR16.ch1);
	Motor.p_M6020setTarAngle(1,-DR16.ch1);
	Motor.p_M6020setTarAngle(2,-DR16.ch1);
	Motor.p_M6020setTarAngle(3,-DR16.ch1);
	
	for(uint8_t i=0;i<4;i++)
	{
	  Motor.M6020[i].targetCurrent=PID_Calc(&Motor.M6020[i].OutPID, \
	  Motor.M6020[i].realAngle, Motor.M6020[i].targetAngle);
	}
	Motor.p_M6020setCur(CAN_1);  
}


///*------------------------------80 Chars Limit--------------------------------*/

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-09 11:33
	* @brief   对角步态关节运动模型
	* @param   void
	* @retval  void
	*/
void Joint_TrotMotionModel(int16_t Vx, int16_t Vy, int16_t Omega,float T)
{	
	static float temp=0;
	static int16_t  thighErr=-400,crusErr=-800,hipErr=-50;
	
	if(Vx == 0 && Vy == 0 && Omega == 0)
		temp=0;
	else
	  temp = (temp>2*PI)?0:(temp+T);
	
	Joint.Vz = PID_Calc(&Joint.PID_Z,GY955.Roll,GY955.targetRoll);
	Joint.Vp = PID_Calc(&Joint.PID_P,GY955.Pitch,GY955.targetPitch);

	DXL1_setSyncMsg(USART_6,POSITION,12,
	0x01, DigitalServo.MX_64[0].MiddleAngle +thighErr - Joint.Vz + Joint_getThighTarAng(Vy,0,temp), /*LH*/
	0x02,DigitalServo.MX_64[1].MiddleAngle +crusErr + Joint.Vz + Joint.Vp 
	+ Joint_getCrusTarAng(Filter.p_ABS(Vy) + Filter.p_ABS(Vx) + Filter.p_ABS(Omega), 0.25f, temp),
	
	0x03,DigitalServo.MX_64[2].MiddleAngle +thighErr- Joint.Vz + Joint_getThighTarAng(Vy,1.0f,temp), /*RH*/ 
	0x04,DigitalServo.MX_64[3].MiddleAngle +crusErr+ Joint.Vz - Joint.Vp 
	+ Joint_getCrusTarAng(Filter.p_ABS(Vy) + Filter.p_ABS(Vx) + Filter.p_ABS(Omega), 1.25f, temp),
	
	0x05,DigitalServo.MX_64[4].MiddleAngle +thighErr + Joint.Vz + Joint_getThighTarAng(Vy,0,temp), /*RF*/
	0x06,DigitalServo.MX_64[5].MiddleAngle +crusErr - Joint.Vz - Joint.Vp
	+ Joint_getCrusTarAng(Filter.p_ABS(Vy) + Filter.p_ABS(Vx) + Filter.p_ABS(Omega), 0.25f, temp),

	0x07,DigitalServo.MX_64[6].MiddleAngle +thighErr + Joint.Vz + Joint_getThighTarAng(Vy,1.0f,temp), /*LF*/
	0x08,DigitalServo.MX_64[7].MiddleAngle +crusErr- Joint.Vz + Joint.Vp
	+ Joint_getCrusTarAng(Filter.p_ABS(Vy) + Filter.p_ABS(Vx) + Filter.p_ABS(Omega), 1.25f, temp),
	
	0x09,DigitalServo.MX_64[8].MiddleAngle + hipErr + Joint_getHipTarAng(Omega + Vx, 0, temp),
	0x0A,DigitalServo.MX_64[9].MiddleAngle - hipErr + Joint_getHipTarAng(Omega + Vx, 1.0f, temp),
	0x0B,DigitalServo.MX_64[10].MiddleAngle + hipErr + Joint_getHipTarAng(Omega - Vx, 0, temp),
	0x0C,DigitalServo.MX_64[11].MiddleAngle - hipErr + Joint_getHipTarAng(Omega - Vx, 1.0f, temp));
}

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-09 11:33
	* @brief   三角步态关节运动模型
	* @param   void
	* @retval  void
	*/
void Joint_WalkMotionModel(int16_t Vx, int16_t Vy, int16_t Omega)
{	
	static float temp=0.0f;
  static int16_t  thighErr=-350,crusErr=-700,hipErr=-50;
	if(Vx == 0 && Vy == 0 && Omega == 0)
		temp=0;
	else
	  temp=(temp>2*PI)?0:(temp+0.2f);
	
	DXL1_setSyncMsg(USART_6,POSITION,12,
	0x01,DigitalServo.MX_64[0].MiddleAngle +thighErr - 0*Joint.Vz+ Joint_getThighTarAng(Vy,-0.5f,temp), /*LF*/               
	0x02,DigitalServo.MX_64[1].MiddleAngle +crusErr + Joint.Vz + Joint.Vp
	+ Joint_getCrusTarAng(Filter.p_ABS(Vy) + Filter.p_ABS(Vx) + Filter.p_ABS(Omega),-0.25f,temp),
	
	0x03,DigitalServo.MX_64[2].MiddleAngle +thighErr - 0*Joint.Vz+ Joint_getThighTarAng(Vy,-1.5f,temp), /*RH*/ 
	0x04,DigitalServo.MX_64[3].MiddleAngle +crusErr + Joint.Vz + Joint.Vp
	+ Joint_getCrusTarAng(Filter.p_ABS(Vy) + Filter.p_ABS(Vx) + Filter.p_ABS(Omega),-1.25f,temp),

	0x05,DigitalServo.MX_64[4].MiddleAngle +thighErr - 0*Joint.Vz+ Joint_getThighTarAng(Vy,-1.0,temp), /*RH*/ 
	0x06,DigitalServo.MX_64[5].MiddleAngle +crusErr + Joint.Vz + Joint.Vp
	+ Joint_getCrusTarAng(Filter.p_ABS(Vy) + Filter.p_ABS(Vx) + Filter.p_ABS(Omega),-0.75f,temp),

	0x07,DigitalServo.MX_64[6].MiddleAngle +thighErr - 0*Joint.Vz+ Joint_getThighTarAng(Vy,0.0f,temp), /*LF*/ 
	0x08,DigitalServo.MX_64[7].MiddleAngle +crusErr + Joint.Vz + Joint.Vp
	+ Joint_getCrusTarAng(Filter.p_ABS(Vy) + Filter.p_ABS(Vx) + Filter.p_ABS(Omega),0.25f,temp),
	
	0x09,DigitalServo.MX_64[8].MiddleAngle + hipErr 
	+ Joint_getHipTarAng(Omega + Vx,0,temp),
	0x0A,DigitalServo.MX_64[9].MiddleAngle - hipErr
	+ Joint_getHipTarAng(Omega + Vx,1.0f,temp),
	0x0B,DigitalServo.MX_64[10].MiddleAngle + hipErr
	+ Joint_getHipTarAng(Omega - Vx,0,temp),
	0x0C,DigitalServo.MX_64[11].MiddleAngle - hipErr
	+ Joint_getHipTarAng(Omega - Vx,1.0f,temp));
}


/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-03-06 15:31
	* @brief   关节控制状态机
	* @param   void
	* @retval  void
	*/
	void Joint_StateMachine(void)
	{


	}


/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-03-06 15:31
	* @brief   机械臂控制
	* @param   UpperarmTarang:上臂目标值、ForearmTarang ：前臂目标值
	* @retval  void
	*/
void Joint_RobotArmCtrl(uint16_t UpperarmTarang,uint16_t ForearmTarang)
{
	DXL1_setSyncMsg(USART_6,POSITION,2,0x0D,UpperarmTarang,0x0E,ForearmTarang);
}
/*------------------------------80 Chars Limit--------------------------------*/

/*------------------------------80 Chars Limit--------------------------------*/

/*------------------------------80 Chars Limit--------------------------------*/

/*---------------------L O C A L - F U N C T I O N S--------------------------*/

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-09 11:33
	* @brief   髋关节控制
	* @param   TarAng 目标角度， Phase相位 ，Rate 倍率
	* @retval  滤波后的角度
	*/

static int16_t Joint_getHipTarAng(int16_t TarAng ,float Phase,float Rate)
{
	  TarAng=TarAng>100?100:TarAng;
		TarAng=TarAng<-100?-100:TarAng;
	  return ((Curve_Sin(TarAng,1,Phase,0,Rate)));
}


/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-09 11:33
	* @brief   大腿控制
	* @param   TarAng 目标角度， Phase相位 ，Rate 倍率
	* @retval  滤波后的角度
	*/

static int16_t Joint_getThighTarAng(int16_t TarAng ,float Phase,float Rate)
{
	  TarAng=TarAng>400?400:TarAng;
		TarAng=TarAng<-400?-400:TarAng;
	  return ((Curve_Sin(TarAng,1,Phase,0,Rate)));
}

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-09 11:33
	* @brief   小腿控制
	* @param   TarAng 目标角度， Phase相位 ,Rate 倍率
	* @retval  滤波后的角度
	*/
static int16_t Joint_getCrusTarAng(int16_t TarAng ,float Phase,float Rate)
{
	static int16_t temp=0;
	TarAng=TarAng>800?800:TarAng;
	TarAng=TarAng<-800?-800:TarAng;
	temp=Curve_Sin(Filter.p_ABS(TarAng),1,Phase,0,Rate);
	
  if(temp<0)
	  return temp;
	else
		return 0;
}

/*-----------------------------------FILE OF END------------------------------*/






