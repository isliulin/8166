#include "bsp_tim.h"

/*
*********************************************************************************************************
*                                             BSP_TIM3_Init()
*
* Description : TIM3 init  output PWM
*
* Argument(s) : none
*
* Return(s)   : none.
*
* Note(s)     : 
*********************************************************************************************************
*/
void BSP_TIM3_Output_PWM_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;//����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx

	TIM_TimeBaseInitStructure.TIM_Period = 900;	   //����Ƶ,PWM Ƶ��=72000/900=8Khz//�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = 0;//����������ΪTIMxʱ��Ƶ��Ԥ��Ƶֵ��100Khz����Ƶ��
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, & TIM_TimeBaseInitStructure);

	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//PWM���ʹ��
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low;

	TIM_OC1Init(TIM3,&TIM_OCInitStructure);
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);
	
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);//ʹ�ܻ���ʧ��TIMx��CCR1�ϵ�Ԥװ�ؼĴ��� 
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);//ʹ�ܻ���ʧ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
	
	TIM_SetCompare1(TIM3, 100);
	TIM_SetCompare2(TIM3, 300);
	
	TIM_Cmd(TIM3,ENABLE);//ʹ�ܻ���ʧ��TIMx����	
}
/*
*********************************************************************************************************
*                                             BSP_TIM4_Init()
*
* Description : TIM5 init  catch input
*
* Argument(s) : USARTx , baud
*
* Return(s)   : none.
*
* Note(s)     : 
*********************************************************************************************************
*/
void BSP_TIM4_Input_Capture_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;//����һ���ṹ�������������ʼ����ʱ��
	TIM_ICInitTypeDef TIM_ICInitStructure;

	TIM_ClearITPendingBit(TIM4,TIM_IT_Update | TIM_IT_CC1 | TIM_IT_CC2); //����жϺͲ����־λ

	TIM_TimeBaseInitStructure.TIM_Period = 0xffff;	 //�趨�������Զ���װֵ 	
	TIM_TimeBaseInitStructure.TIM_Prescaler = 71;   //��1Mhz��Ƶ�ʼ��� һ�μ���1us
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;	  //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	 //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1 | TIM_Channel_2; //ѡ������� IC1ӳ�䵽TI1�� 
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; //�����ز��� 
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1�� 
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; //���������Ƶ,����Ƶ 
	TIM_ICInitStructure.TIM_ICFilter = 0x00; //IC1F=0000 ���������˲��� ���˲� 
	TIM_ICInit(TIM4, &TIM_ICInitStructure); //��ʼ��TIM5���벶��ͨ��1	
	
	TIM_Cmd(TIM4,ENABLE); //ʹ�ܻ���ʧ��TIMx����
	TIM_ITConfig(TIM4, TIM_IT_Update | TIM_IT_CC1 | TIM_IT_CC2, ENABLE );	//ʹ�ܻ���ʧ��ָ����TIM�ж�
		
}

/*******************************************************************************
�������ܣ���ʼ����ʱ��3
*******************************************************************************/
void BSP_TIM3_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//����
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOC,GPIO_Pin_6);//����
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//����
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOC,GPIO_Pin_7);//����	
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);
  /* Timer configuration in Encoder mode */
  TIM_DeInit(TIM3);
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;  // No prescaling 
  TIM_TimeBaseStructure.TIM_Period =0xffff-1;     //(4*ENCODER_PPR)-1
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
  TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;
  TIM_ICInit(TIM3, &TIM_ICInitStructure);   
  TIM3->CNT = 0; 
  TIM_Cmd(TIM3, ENABLE); 
}
/*******************************************************************************
�������ܣ���ʼ����ʱ��4
*******************************************************************************/
void BSP_TIM4_Init(void)			  
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//����
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOD,GPIO_Pin_12);//����

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//����
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOD,GPIO_Pin_13);//����
	GPIO_PinRemapConfig(GPIO_Remap_TIM4,ENABLE);
  /* Timer configuration in Encoder mode */
  TIM_DeInit(TIM4);
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;  // No prescaling 
  TIM_TimeBaseStructure.TIM_Period =0xffff-1;     //(4*ENCODER_PPR)-1
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
 
  TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
  
  TIM4->CNT = 0; 
  TIM_Cmd(TIM4, ENABLE); 
                         
}
