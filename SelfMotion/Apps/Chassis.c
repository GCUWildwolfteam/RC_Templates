/**
|-------------------------------- Copyright -----------------------------------|
|                                                                              |
|                     (C) Copyright 2019, Daqo Lee                             |
|                                                                              |
|                          By:GCU The wold of team                             |
|                     https://github.com/GCUWildwolfteam                       |
|------------------------------------------------------------------------------|
|  FileName    : Chassis.c                                                
|  Version     : v1.0                                                            
|  Author      : Daqo Lee                                                       
|  Date        : 2019-02-20               
|  Libsupports : STM32F4xx_DFP ( 2.9.0)
|  Description :                                                       
|------------------------------declaration of end------------------------------|
 **/
/*--------------------- I N C L U D E - F I L E S ----------------------------*/
#include "Chassis.h"
#include "RoboModule.h"
#include "math.h"
#include "DR16.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Encoder.h"
#include "Curve.h"
#include "Filter.h"
/*-------------------------- D E F I N E S -----------------------------------*/
const float Radian=PI/6;

Chassis_t Chassis;

static float Slope[]=
{
	0.000000, 0.085480, 0.170623, 0.255093, 0.338556, 
	0.420682, 0.501149, 0.579638, 0.655839, 0.729451, 
	0.800185, 0.867761, 0.931913, 0.992386, 1.048943, 
	1.101361, 1.149432, 1.192966, 1.231792, 1.265758, 
	1.294727, 1.318587, 1.337243, 1.350622, 1.358670, 
	1.361357, 1.358670, 1.350622, 1.337243, 1.318587, 
	1.294727, 1.265758, 1.231792, 1.192966, 1.149432, 
	1.101361, 1.048943, 0.992386, 0.931913, 0.867761, 
	0.800185, 0.729451, 0.655839, 0.579638, 0.501149, 
	0.420682, 0.338556, 0.255093, 0.170623, 0.085480, 
	0.000000, -0.085480, -0.170623, -0.255093, -0.338556, 
	-0.420682, -0.501149, -0.579638, -0.655839, -0.729451, 
	-0.800185, -0.867761, -0.931913, -0.992386, -1.048943, 
	-1.101361, -1.149432, -1.192966, -1.231792, -1.265758, 
	-1.294727, -1.318587, -1.337243, -1.350622, -1.358670, 
	-1.361357, -1.358670, -1.350622, -1.337243, -1.318587, 
	-1.294727, -1.265758, -1.231792, -1.192966, -1.149432, 
	-1.101361, -1.048943, -0.992386, -0.931913, -0.867761, 
	-0.800185, -0.729451, -0.655839, -0.579638, -0.501149, 
	-0.420682, -0.338556, -0.255093, -0.170623, -0.085480, 
	-0.000000, 0.085480, 0.170623, 0.255093, 0.338556, 
	0.420682, 0.501149, 0.579638, 0.655839, 0.729451, 
	0.800185, 0.867761, 0.931913, 0.992386, 1.048943, 
	1.101361, 1.149432, 1.192966, 1.231792, 1.265758, 
	1.294727, 1.318587, 1.337243, 1.350622, 1.358670, 
	1.361357, 1.358670, 1.350622, 1.337243, 1.318587, 
	1.294727, 1.265758, 1.231792, 1.192966, 1.149432, 
	1.101361, 1.048943, 0.992386, 0.931913, 0.867761, 
	0.800185, 0.729451, 0.655839, 0.579638, 0.501149, 
	0.420682, 0.338556, 0.255093, 0.170623, 0.085480, 
	0.000000, -0.085480, -0.170623, -0.255093, -0.338556, 
	-0.420682, -0.501149, -0.579638, -0.655839, -0.729451, 
	-0.800185, -0.867761, -0.931913, -0.992386, -1.048943, 
	-1.101361, -1.149432, -1.192966, -1.231792, -1.265758, 
	-1.294727, -1.318587, -1.337243, -1.350622, -1.358670
};
/*-----------L O C A L - F U N C T I O N S - P R O T O T Y P E S--------------*/
void SpinRuning(void);

/*------------------G L O B A L - F U N C T I O N S --------------------------*/

/*------------------------------80 Chars Limit--------------------------------*/
  /**
  * @Data    2019-02-20 16:59
  * @brief  底盘运动模型分解
  * @param  [in] Vx     X 轴方向速度
  *         [in] Vy     Y 轴方向速度
  *         [in] Omega  自旋速度
  *         [in] *Speed 速度分解缓存 
  * @retval None
  */
void Chassis_MotionModel(float Vx, float Vy, float Omega, int16_t *Speed)								
{
#if   MECANUM == 1
  Speed[0] = -Vx - Vy + Omega;
  Speed[1] = -Vx + Vy + Omega;
  Speed[2] =  Vx + Vy + Omega;
  Speed[3] =  Vx - Vy + Omega;
#elif	THROMNI == 1
	Speed[0] = -Vx + Omega;
  Speed[1] =  Vx*sin(Radian) - Vy*cos(Radian) + Omega;
  Speed[2] =  Vx*sin(Radian) + Vy*cos(Radian) + Omega;
#elif FOROMNI == 1
	Speed[0] = -Vx - Vy + Omega;
  Speed[1] = -Vx + Vy + Omega;
  Speed[2] =  Vx + Vy + Omega;
  Speed[3] =  Vx - Vy + Omega;
	
#endif

}

/*---------------------L O C A L - F U N C T I O N S--------------------------*/

/**
  * @Data    2019-03-19 10:56
  * @brief   底盘参数初始化
  * @param   void
  * @retval  void
  */
  void Chassis_Init(void)
  {
		
    PID_StructInit(&Chassis.PID_X, POSITION_PID, 800, 500, 2, 0, 0);
    PID_StructInit(&Chassis.PID_Y, POSITION_PID, 800, 500, 2, 0, 0);
    PID_StructInit(&Chassis.PID_Spin, POSITION_PID, 800, 500, -50, 0, 0);
		
    Posture.targetZ_Angle=0;
		Chassis.Vy=0;
		Chassis.Vx=0;
		
  }
/**
  * @Data    2019-03-19 11:08
  * @brief   
  * @param   void
  * @retval  void
  */
  void Chassis_Ctrl(void)
  {
    static uint16_t temp = 0;
		static uint8_t temp1=1;
    int16_t velBuff[3];

#if 0
		if(DR16.switch_right==3)
		{
		  Posture.targetX_Coords= -DR16.ch1 * 5;
			Posture.targetY_Coords= -DR16.ch2 * 5;
			Posture.targetZ_Angle = -DR16.ch3 / 6;

//		  Chassis.Vx=PID_Calc(&Chassis.PID_X,
//                        Posture.realX_Coords,Posture.targetX_Coords);
//      Chassis.Vy=PID_Calc(&Chassis.PID_Y,
//                        Posture.realY_Coords,Posture.targetY_Coords);
			Chassis.Vspin=PID_Calc(&Chassis.PID_Spin,
										Posture.realZ_Angle,Posture.targetZ_Angle);
			SpinRuning();
			
		}
		else
		{
			Chassis.Vx = -10*DR16.ch3;
			Chassis.Vy = -10*(DR16.ch2+DR16.ch4);
			Chassis.Vspin=5*DR16.ch1;
		}

#endif

#if 0
    Posture.targetX_Coords=DR16.ch1;
		Posture.targetY_Coords=DR16.ch2;

//		
    Chassis.Vx=PID_Calc(&Chassis.PID_X,
                        Posture.realX_Coords,Posture.targetX_Coords);
    Chassis.Vy=PID_Calc(&Chassis.PID_Y,
                        Posture.realY_Coords,Posture.targetY_Coords);
    Chassis.Vspin=PID_Calc(&Chassis.PID_Spin,
                        Posture.realZ_Angle,Posture.targetZ_Angle);
//		
#endif	


#if 1 /*全场定位测试切线跑曲线*/

  if(temp<162 && DR16.switch_right == 3)/*一共取了170个点*/
	{
		//Chassis.Vy = Chassis.Vy < -1500 ? -1500 : Chassis.Vy - 10; /*起步缓慢加速*/
    Posture.targetZ_Angle=0;
		Chassis.Vy = -1000 - 500*ABS(Slope[temp]); /*直线提速，拐弯减速*/
//		Filter.p_Limit(&Chassis.Vy,-2500,-1000); /*限幅滤波*/
		if((30*(temp+1)) + Posture.realY_Coords < 5) /*每隔30mm取一个点，误差接近5mm更新*/
		{
			Chassis.Vx = -Chassis.Vy*Slope[temp]; /*计算Vx*/
			temp++;
		}
			Chassis.Vspin = PID_Calc(&Chassis.PID_Spin,
			Posture.realZ_Angle,Posture.targetZ_Angle); /*陀螺仪伺服*/
	}
	else if(DR16.switch_right == 3&&temp1<3)
	{
		switch(temp1)
		{
			case 1:

			  Curve_Straight(1000);
			
		  	Posture.targetZ_Angle=0;
				Chassis.Vspin = PID_Calc(&Chassis.PID_Spin,
				         Posture.realZ_Angle,Posture.targetZ_Angle);
			
				Chassis.Vx=PID_Calc(&Chassis.PID_X,
                        Posture.realX_Coords,Posture.targetX_Coords);
        Chassis.Vy=PID_Calc(&Chassis.PID_Y,
                        Posture.realY_Coords,Posture.targetY_Coords);
			  
			  if(-8000-Posture.realY_Coords>-100
					&& Posture.realX_Coords-725<100)
				{
					temp1=2;
				}
				break;
			case 2:
			  Curve_Straight1(1500);
		  	Posture.targetZ_Angle=Posture.targetZ_Angle>90?90:Posture.targetZ_Angle+0.9f;

				Chassis.Vspin = PID_Calc(&Chassis.PID_Spin,
				         Posture.realZ_Angle,Posture.targetZ_Angle);
			  SpinRuning();
				if(-8500-Posture.realY_Coords>-100
					&& 2500-Posture.realX_Coords<100)
				{
					temp1=3;
				}
				break;
		}
	}
	else/*跑完点切回遥控*/
	{
		Chassis.Vx = -10*DR16.ch3;
		Chassis.Vy = -10*(DR16.ch2+DR16.ch4);
		Chassis.Vspin=5*DR16.ch1;
//			Chassis.Vspin = PID_Calc(&Chassis.PID_Spin,
//			Posture.realZ_Angle,Posture.targetZ_Angle);
	}  
#endif	
	
    Chassis_MotionModel(Chassis.Vx,Chassis.Vy,Chassis.Vspin,velBuff);
//  Chassis_MotionModel(-10*DR16.ch3,-10*(DR16.ch2+DR16.ch4),10*DR16.ch1,velBuff);
		
		
    RoboModule_DRV_Velocity_Mode(0,1,3000,velBuff[0]);
    RoboModule_DRV_Velocity_Mode(0,2,3000,velBuff[1]);
    RoboModule_DRV_Velocity_Mode(0,3,3000,velBuff[2]);
  }

/**
* @Data    2019-03-24 12:53
* @brief   
* @param   void
* @retval  void
*/
void SpinRuning(void)
{
	static float Vx=0.0f,Vy=0.0f,Vxy=0.0f;
	static float Length=0.0f,CoordsErrX=0.0f,CoordsErrY=0.0f;

	Vx=PID_Calc(&Chassis.PID_X,
					Posture.realX_Coords,Posture.targetX_Coords);
    Vy=PID_Calc(&Chassis.PID_Y,
					Posture.realY_Coords,Posture.targetY_Coords);

	Vxy=sqrt(pow(Vx,2)+pow(Vy,2));

    CoordsErrX = Posture.targetX_Coords - Posture.realX_Coords;
    CoordsErrY = Posture.targetY_Coords - Posture.realY_Coords;
		
	Length=sqrt(pow(CoordsErrX,2) + pow(CoordsErrY,2));
	
	Chassis.Vx = ((Vxy * CoordsErrX)/Length)*cos(Posture.realZ_Angle*(PI/180))
							+((Vxy * CoordsErrY)/Length)*sin(Posture.realZ_Angle*(PI/180));

	Chassis.Vy = -((Vxy * CoordsErrX)/Length)*sin(Posture.realZ_Angle*(PI/180))
							+((Vxy * CoordsErrY)/Length)*cos(Posture.realZ_Angle*(PI/180));
}
/*-----------------------------------FILE OF END------------------------------*/

