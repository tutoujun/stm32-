#include "stm32f10x.h"                  // Device header
void Timer_Init(void){
	//���ö�ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	//ѡ��ʱ��2ʱ����Ԫ
	TIM_InternalClockConfig(TIM2);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	//��ʱ1s
	TIM_TimeBaseInitStruct.TIM_Period=10000-1;
	TIM_TimeBaseInitStruct.TIM_Prescaler=3600-1;
	//�ظ����������߼���ʱ�����еģ�����Ҫ�ã�����
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	TIM_Cmd(TIM2,ENABLE);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	TIM_SelectOutputTrigger(TIM2,TIM_TRGOSource_Update);
	
	//ѡ��ʱ��2ʱ����Ԫ
	TIM_ITRxExternalClockConfig(TIM1,TIM_TS_ITR1);//tim3�Ĵ�������
	TIM_SelectSlaveMode(TIM1,TIM_SlaveMode_External1);//ѡ��TIM3�Ĵ�ģʽ
	TIM_TimeBaseInitTypeDef TIM1_TimeBaseInitStruct;
	TIM1_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM1_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	//��ʱ1s
	TIM1_TimeBaseInitStruct.TIM_Period=2-1;
	TIM1_TimeBaseInitStruct.TIM_Prescaler=1-1;
	//�ظ����������߼���ʱ�����еģ�����Ҫ�ã�����
	TIM1_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM1,&TIM1_TimeBaseInitStruct);
	TIM_Cmd(TIM1,ENABLE);
	TIM_ClearFlag(TIM1, TIM_FLAG_Update);
	
	
	
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);
}

