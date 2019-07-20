/**
  ******************************************************************************
  * @file     delay.c
  * @author   Hare
  * @version  V1.4
  * @date     2019-04-01
  * @brief    ��ʱӦ�ú����ӿڣ�OS���ã�����DWTʵ����ʱ
  * @Note     1.�������OS����Systick�жϷ���������д��������ʽ����FreeRTOSΪ����
  *             ������ʼ���Ⱥ��ٵ���ϵͳ��SystickHandle
  *             ���������ϵͳ��ʼ����ǰ����������жϻ�ʹ�������ж���
  *             void SysTick_Handler(void)
  *             {
	*               if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)
  *               {
  *                 xPortSysTickHandler();	
  *               }
  *             }
  *           2.�ǵ���main�г�ʼ��Systick
  *             SysTick_Config(SystemCoreClock/1000);
  *           3.��Systick����ԭ�򣬵�tStart��71990��������ֿ���whileѭ����
  *             �ָ���DWTʵ�֣��ǵó�ʼ��dwt�ſ�����ʹ��delay
  ******************************************************************************
  */
  
  
#include "delay.h"

/* DWT �Ĵ�����ַ */
#define  DWT_CYCCNT  *(volatile unsigned int *)0xE0001004
#define  DWT_CR      *(volatile unsigned int *)0xE0001000
#define  DEM_CR      *(volatile unsigned int *)0xE000EDFC
#define  DBGMCU_CR   *(volatile unsigned int *)0xE0042004

#define  DEM_CR_TRCENA               (1 << 24)
#define  DWT_CR_CYCCNTENA            (1 <<  0)


void delay_init(void)
{
	DEM_CR         |= (unsigned int)DEM_CR_TRCENA;   /* Enable Cortex-M4's DWT CYCCNT reg.  */
	DWT_CYCCNT      = (unsigned int)0u;
	DWT_CR         |= (unsigned int)DWT_CR_CYCCNTENA;
}

///**
//  * @brief  ΢�뼶��ʱ,�ο�������DWT����ʱ��ֵ��Сʱ����0.25us�������
//  * @Note 	����32λ�޷������������ȡ�Ľ���ٸ�ֵ��32λ�޷�������Ȼ������ȷ�Ļ�ȡ��ֵ��
//  *			����A,B,C����32λ�޷�������
//  *              ���A > B  ��ôA - B = C������ܺ���⣬��ȫû������
//  *              ���A < B  ��ôA - B = C�� C����ֵ����0xFFFFFFFF - B + A + 1��
//  * @param  _us ��ʱ΢������32λ������������2^32/SystemCoreClock��
//  * @retval None
//  */
void delay_us(uint32_t _us)
{
  uint32_t tCnt, tDelayCnt;
	uint32_t tStart;

	tStart = DWT_CYCCNT;                                     /* �ս���ʱ�ļ�����ֵ */
	tCnt = 0;
	tDelayCnt = _us * (SystemCoreClock / 1000000);	 /* ��Ҫ�Ľ����� */ 		      

	while(tCnt < tDelayCnt)
	{
  	tCnt = DWT_CYCCNT - tStart; /* ��������У����������һ��32λ���������¼�������Ȼ������ȷ���� */	
	}
}

/**
  * @brief  ���뼶��ʱ
  * @param  _ms ��ʱ������
  * @retval None
  */
void delay_ms(uint32_t _ms)
{
	uint32_t i;
	for(i=0;i<_ms;i++){
		delay_us(1000);
	}
}

/* ��F1ʹ��systickʵ�ֻ�����⣬�˴������� */
///**
//  * @brief  ΢�뼶��ʱ,�ο�������DWT����ʱ��ֵ��Сʱ����0.25us�������
//  * @Note 	����32λ�޷������������ȡ�Ľ���ٸ�ֵ��32λ�޷�������Ȼ������ȷ�Ļ�ȡ��ֵ��
//  *			����A,B,C����32λ�޷�������
//  *              ���A > B  ��ôA - B = C������ܺ���⣬��ȫû������
//  *              ���A < B  ��ôA - B = C�� C����ֵ����0xFFFFFFFF - B + A + 1��
//  * @param  _us ��ʱ΢������32λ������������2^32/SystemCoreClock��
//  * @retval None
//  */
//void delay_us(uint32_t _us)
//{
//	uint32_t tCnt, tDelayCnt;
//	uint32_t tStart;
//	
//	tStart = SysTick->VAL;
//	tCnt = 0;
//	tDelayCnt = _us * (SystemCoreClock / 1000000);	 /* ��Ҫ�Ľ����� */ 
//	
//	while(tCnt < tDelayCnt)
//	{
//		tCnt = tStart - SysTick->VAL; /* ��������У����������һ��32λ���������¼�������Ȼ������ȷ���� */	
//	}
//	
//}




