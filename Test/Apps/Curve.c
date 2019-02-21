#include "Curve.h"
#include "Encoder.h"
#include <math.h>

#define LEN  1000


/******************************************************************************/
 /*
  * @brief None
  * @param None
  * @retval None
  */
void Curve_Straight(void)
{
	static float xCoords=1120.0f,yCoords=0.0f;
	
	yCoords=Posture.realY_Coords+\
	        sqrt(LEN*LEN-(pow(Posture.realX_Coords-xCoords,2)));
	
	Posture.targetX_Coords=xCoords;
	Posture.targetY_Coords=yCoords;
	
}
/******************************************************************************/
 /*
  * @brief None
  * @param None
  * @retval None
  */
//void Curve_Circle(float r,float a, float b)
//{
//	static float Len=0.0f,k=0.0f;
//  Len=sqrt(pow((Posture.realX_Coords-a),2)-pow((Posture.realY_Coords-b),2));
//	if(Len>r)
//	{
//	  k=(Posture.realY_Coords-b)/(Posture.realX_Coords-a);
//	}
//	else
//	{
//	
//	}
//}


/******************************************************************************/


/*******************************************************************************
 贝塞尔曲线计算公式测试
  static float x1=2.0f,x2=8.0f,x3=16.0f;
	static float y1=2.0f,y2=8.0f,y3=2.0f;
	static float a1,a2,a3;
	static float b1,b2,b3;
  static float t=0.0f;
for(;t<1.0f;)
{
	a1=((1-t)*x1+t*x2);
	b1=((1-t)*y1+t*y2);

	a2=((1-t)*x2+t*x3);
	b2=((1-t)*y2+t*y3);

	a3=((1-t)*a1+t*a2);
	b3=((1-t)*b1+t*b2);
	t+=0.01f;
}

for(;t<1.0f;)
{
	a3=((pow((1-t),2)*x1+(2*t*(1-t)*x2)+pow(t,2)*x3));

	b3=((pow((1-t),2)*y1+(2*t*(1-t)*y2)+pow(t,2)*y3));
	t+=0.01f;
}

*******************************************************************************/

float Curve_Bezier(uint8_t *x,uint8_t n,float t)
{
  for(;n>0;n--)
	{
		for(uint8_t i=0;i<n;i++)
		{
			x[i]=((1-t)*x[i]+t*x[i+1]);
		}

	}
  return x[0];
}


