/**
|-------------------------------- Copyright -----------------------------------|
|                                                                              |
|                     (C) Copyright 2019, Daqo Lee                             |
|                                                                              |
|                          By:GCU The wold of team                             |
|                     https://github.com/GCUWildwolfteam                       |
|------------------------------------------------------------------------------|
|  FileName    : BSP_TIM.c                                                
|  Version     : v1.0                                                            
|  Author      : Daqo Lee                                                       
|  Date        : 2019-01-18               
|  Libsupports : STM32F4xx_DFP ( 2.9.0)
|  Description :                                                       
|------------------------------declaration of end------------------------------|
 **/
/*--------------------- I N C L U D E - F I L E S ----------------------------*/
#include "BSP_TIM.h" 
	
/*-------------------------- D E F I N E S -----------------------------------*/



/*-----------L O C A L - F U N C T I O N S - P R O T O T Y P E S--------------*/



/*------------------G L O B A L - F U N C T I O N S --------------------------*/

void BSP_TIM1PWMOutput(u16 prescaler, u16 period, u16 Pulse)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  /*ʹ��GPIOʱ��*/
	RCC_AHB1PeriphClockCmd(TIM1_CH1_GPIO_CLK | TIM1_CH2_GPIO_CLK \
	  | TIM1_CH3_GPIO_CLK | TIM1_CH4_GPIO_CLK, ENABLE);

	/*ʹ�ܶ�ʱ��ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_InitStructure.GPIO_Pin = TIM1_CH1_Pin;
	GPIO_Init(TIM1_CH1_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(TIM1_CH1_GPIO_PORT,TIM1_CH1_PINSOURCE, GPIO_AF_TIM1);

	GPIO_InitStructure.GPIO_Pin = TIM1_CH2_Pin;
	GPIO_Init(TIM1_CH2_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(TIM1_CH2_GPIO_PORT,TIM1_CH2_PINSOURCE, GPIO_AF_TIM1);

	GPIO_InitStructure.GPIO_Pin = TIM1_CH3_Pin;
	GPIO_Init(TIM1_CH3_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(TIM1_CH3_GPIO_PORT,TIM1_CH3_PINSOURCE, GPIO_AF_TIM1);

	GPIO_InitStructure.GPIO_Pin = TIM1_CH4_Pin;
	GPIO_Init(TIM1_CH4_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(TIM1_CH4_GPIO_PORT,TIM1_CH4_PINSOURCE, GPIO_AF_TIM1);

	/* ����ʱ���ṹ�� */
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	/*���ö�ʱ��ʱ�ӷ�Ƶ*/
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
	/*�����Զ���װ�ؼĴ�����ֵ*/
	TIM_TimeBaseStructure.TIM_Period = period;
	/*��������ʱ��������˲���Ƶ������Ƶ*/
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	/*���ü���ģʽ�����ϼ���*/
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	/*��������ȽϽṹ��*/
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	/*�������ģʽ��PWM1ģʽ*/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	/*ʹ�����*/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	/*��ʹ�ܻ������*/
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	/*���ó�ʼռ�ձ�*/
	TIM_OCInitStructure.TIM_Pulse = Pulse;
	/*����PWM���ԣ���ʼ��ƽΪ��*/
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	/*���ÿ���ʱ�����ƽ*/
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	
	/*���û������PWM���ԣ���ʼ��ƽΪ��(����ҲҪ���ã�����������ܳ���)*/
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	/*���û����������ʱ����͵�ƽ(����ҲҪ���ã�����������ܳ���)*/
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);

	/*ʹ�ܶ�ʱ��*/
	TIM_Cmd(TIM1, ENABLE);
	/* �߼���ʱ����Ҫʹ��PWM��� */
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	
}

/*---------------------L O C A L - F U N C T I O N S--------------------------*/



/*-----------------------------------FILE OF END------------------------------*/





