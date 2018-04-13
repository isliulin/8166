#include "bsp.h"

/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

extern			OS_EVENT		*DBGMutexSem; //	DBG�ӿ�printf�����ź���
static			vu8					DBGMutexFlag	=1;		// �����������OS״̬���ɸñ���ʵ��Printf�������
TYPEDEF_PARA   g_system_para = {0};
/*
*********************************************************************************************************
*                                        GLOBAL VARIABLES
*********************************************************************************************************
*/ 
#define  DEF_ADDR_FALSH_BOOT     0x8000000
#define  DEF_ADDR_FALSH_PARA     0x8004C00
#define  DEF_ADDR_FALSH_APP      0x8005000

#define  DEF_ADDR_NETUP_BASE     0X00

#define DEF_STM_SECTOR_SIZE		2048   				//	FLASH ҳ��С 2 Kbytes	 

#define PARA_SIZE   sizeof(TYPEDEF_PARA)
/*
*********************************************************************************************************
* Function Name  : BSP_NVIC_Configuration
* Description    : 				      
* Input          : 
* Output         : None
* Return         : 
*********************************************************************************************************
*/
void	BSP_NVIC_Configuration(void)
{
		NVIC_InitTypeDef NVIC_InitStructure;
	
		/* Set the Vector Table base location at 0x08005000 */
		NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x5000);
		
		/* Configure one bit for preemption priority */
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

		/* CAN1_IRQn�ж�  */
		NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;	
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
    /* UART4_IRQn�ж�  */
    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;     
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;   
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;    
		NVIC_Init(&NVIC_InitStructure);                        
	  /* USART2_IRQn�ж�  */
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;     
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;    
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;    
		NVIC_Init(&NVIC_InitStructure);                         
    /* USART1_IRQn�ж�  */
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;     
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;    
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;    
		NVIC_Init(&NVIC_InitStructure);
    /* USART3_IRQn�ж�  */
		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;     
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;   
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;    
		NVIC_Init(&NVIC_InitStructure);
    /* UART5_IRQn�ж�  */
		NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;     
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 6;    
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;    
		NVIC_Init(&NVIC_InitStructure);
    /* TIM4_IRQn�ж�  */
		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;     
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 7;    
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;    
		NVIC_Init(&NVIC_InitStructure);
    /* ETH_IRQn�ж�  */
    NVIC_InitStructure.NVIC_IRQChannel = ETH_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		NVIC_InitStructure.NVIC_IRQChannel = ETH_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
}

/*
*********************************************************************************************************
*                                              BSP_GPIO_Init()
*
* Description : Initialize the board's COMMON	GPIO (include led , keyboard and other con and det i/0).
*
* Argument(s) : //���⹦�ܹܽ��磺EXIT�жϽţ�Ҳ������ʱ��ʼ��Ϊ����
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/
void  BSP_GPIO_Init (void)
{
    GPIO_InitTypeDef GPIO_InitStructure; 
    
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | 
	                         RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOE | RCC_APB2Periph_USART1 | RCC_APB2Periph_SPI1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 | RCC_APB1Periph_USART3 | RCC_APB1Periph_UART4 | RCC_APB1Periph_UART5 | 
	                         RCC_APB1Periph_CAN1 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4, ENABLE);
	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ETH_MAC | RCC_AHBPeriph_ETH_MAC_Tx | RCC_AHBPeriph_ETH_MAC_Rx, ENABLE);	
    
	  /*RUN LED*/
		GPIO_InitStructure.GPIO_Pin = BSP_GPIOB_LED_RUN;				    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	
    GPIO_Init(GPIOB, &GPIO_InitStructure);GPIO_SetBits(GPIOB, BSP_GPIOB_LED_RUN);
	
// 	  /*DATA LED*/
//		GPIO_InitStructure.GPIO_Pin = BSP_GPIOD_NET_RESET;				    
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	
//    GPIO_Init(GPIOD, &GPIO_InitStructure);
//	    GPIO_ResetBits(GPIOB, BSP_GPIOD_NET_RESET);
	
	  /*ALARM*/
	  GPIO_InitStructure.GPIO_Pin = BSP_GPIOE_ALARM;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    

		/*DIN 1-8*/
	  GPIO_InitStructure.GPIO_Pin = BSP_GPIOE_DIN1 | BSP_GPIOE_DIN2 | BSP_GPIOE_DIN3 | BSP_GPIOE_DIN4 | BSP_GPIOE_DIN5 | BSP_GPIOE_DIN6 | BSP_GPIOE_DIN7 | BSP_GPIOE_DIN8;       
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
    GPIO_Init(GPIOE, &GPIO_InitStructure);					 

		
    /*USART1*/
		GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
		GPIO_InitStructure.GPIO_Pin = BSP_GPIOB_TXD1;	 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);		
		GPIO_InitStructure.GPIO_Pin = BSP_GPIOB_RXD1;   		
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
    GPIO_Init(GPIOB, &GPIO_InitStructure);
			
    /*USART2*/
		GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);
		GPIO_InitStructure.GPIO_Pin = BSP_GPIOD_TXD2;	 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOD, &GPIO_InitStructure);	
		GPIO_InitStructure.GPIO_Pin = BSP_GPIOD_RXD2;	           
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
    GPIO_Init(GPIOD, &GPIO_InitStructure);		
		
    /*USART3*/
		GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);
		GPIO_InitStructure.GPIO_Pin = BSP_GPIOB_DIR;				 //PB15�˿�����  USART3 485 DIR3�ӿ�
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = BSP_GPIOD_TXD3;	 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOD, &GPIO_InitStructure);	
		GPIO_InitStructure.GPIO_Pin = BSP_GPIOD_RXD3;	           
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;				
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOB, GPIO_Pin_15);		
	
    /*UART4*/
		GPIO_InitStructure.GPIO_Pin = BSP_GPIOE_DIR;				 
 	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
 	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	  GPIO_Init(GPIOE, &GPIO_InitStructure);
	  GPIO_InitStructure.GPIO_Pin = BSP_GPIOC_TXD4;	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure); 
    GPIO_InitStructure.GPIO_Pin = BSP_GPIOC_RXD4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOE, BSP_GPIOE_DIR);		

    /*UART5*/
		GPIO_InitStructure.GPIO_Pin = BSP_GPIOC_TXD5;	 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);	
		GPIO_InitStructure.GPIO_Pin = BSP_GPIOD_RXD5;	           
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;				
    GPIO_Init(GPIOD, &GPIO_InitStructure);	

    /*CAN*/
	  GPIO_PinRemapConfig(GPIO_Remap2_CAN1, ENABLE);
    GPIO_InitStructure.GPIO_Pin = BSP_GPIOD_CAN1TX;		
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);  
    GPIO_InitStructure.GPIO_Pin = BSP_GPIOD_CAN1RX;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
		
	  /*TIM3 input*/
		GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);
		GPIO_InitStructure.GPIO_Pin=BSP_GPIOC_TIM3_IN1 | BSP_GPIOC_TIM3_IN2;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	  /*TIM4 input*/
		GPIO_PinRemapConfig(GPIO_Remap_TIM4,ENABLE);
		GPIO_InitStructure.GPIO_Pin = BSP_GPIOD_TIM4_IN1 | BSP_GPIOD_TIM4_IN2;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOD,&GPIO_InitStructure);

    /*SPI*/
		GPIO_InitStructure.GPIO_Pin = BSP_GPIOB_SPI1_SCK | BSP_GPIOB_SPI1_MOSI;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = BSP_GPIOB_SPI1_MISO;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
		GPIO_PinRemapConfig(GPIO_Remap_SPI1, ENABLE);

    /*74HC595 DOUT 1-24 , 74HC597 DIN 9-24*/
		GPIO_InitStructure.GPIO_Pin = BSP_GPIOE_H595RCLK;			
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 		  
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
		GPIO_Init(GPIOE, &GPIO_InitStructure);					  

		GPIO_InitStructure.GPIO_Pin = BSP_GPIOD_H595EN | BSP_GPIOD_SPISD_CS;			
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 		 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		  
		GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = BSP_GPIOD_HC597_LOADIN | BSP_GPIOD_HC597_RLCK ;		
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);  
		
		GPIO_InitStructure.GPIO_Pin = BSP_GPIOA_SPIFLASH_CS;			
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
		GPIO_Init(GPIOA, &GPIO_InitStructure);					
		
//		/*ETH RMII*/
//  	GPIO_InitStructure.GPIO_Pin = BSP_GPIOA_ETH_MDIO;
//  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  	GPIO_Init(GPIOA, &GPIO_InitStructure);

//  	GPIO_InitStructure.GPIO_Pin = BSP_GPIOC_ETH_MDC;
//  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  	GPIO_Init(GPIOC, &GPIO_InitStructure);

//  	GPIO_InitStructure.GPIO_Pin = BSP_GPIOB_ETH_TX_EN | BSP_GPIOB_ETH_TXD0 | BSP_GPIOB_ETH_TXD1;
//  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  	GPIO_Init(GPIOB, &GPIO_InitStructure);

//		GPIO_InitStructure.GPIO_Pin = BSP_GPIOA_ETH_REF_CLK | BSP_GPIOA_ETH_CRS_DV;
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//		GPIO_Init(GPIOA, &GPIO_InitStructure);

//		GPIO_InitStructure.GPIO_Pin = BSP_GPIOC_ETH_RXD0 | BSP_GPIOC_ETH_RXD1;
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//		GPIO_Init(GPIOC, &GPIO_InitStructure);
//     
//		GPIO_InitStructure.GPIO_Pin = BSP_GPIOA_ETH_MCO;
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//		GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*
*********************************************************************************************************
*                                         BSP_WDTDOG_Init()
*
* Description : Init the watchdog time
*
* Argument(s) : none.
*
* Return(s)   : 
*
* Caller(s)   : BSP_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/
void	BSP_WDTDOG_Init(void)
{
		
		/* IWDG timeout equal to 280 ms (the timeout may varies due to LSI frequency
	     dispersion) */
	  /* Enable write access to IWDG_PR and IWDG_RLR registers */
	  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	
	  /* IWDG counter clock: 40KHz(LSI) 256/40 ÿ��һ����ʱ��Ϊ�� 6.4ms*/ 
	  IWDG_SetPrescaler(IWDG_Prescaler_256);
	
	  /* Set counter reload value to 349 �ܼ�ʱʱ��Ϊ��6.4ms * 1875 = OS_SYSWDG_TIMES */ 
		IWDG_SetReload((u16)(SYSWDG_TIMEOUT * 1000 /6.4 + 0.5));  
	
	  /* Reload IWDG counter */
	  IWDG_ReloadCounter();

}
/*
*********************************************************************************************************
*                                            BSP_CPU_DisAllInterupt()
*
* Description : ��ֹ�����жϷ�ֹbootloader��ʹ���жϺ�Ӧ�ó�����δ��ʼ��֮ǰ����(Ӧ����OSʹ��֮ǰ����,�������ж�)
*
* Argument(s) : none.
*
* Return(s)   : 
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/
void	BSP_CPU_DisAllInterupt	(void)
{
		SysTick->CTRL  = SysTick_CTRL_ENABLE_Msk;  
}

/*
*********************************************************************************************************
*                                            BSP_CPU_Reset()
*
* Description : CPU SOFT RESET 
*
* Argument(s) : none.
*
* Return(s)   : 
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/
void	BSP_CPU_Reset(void)
{
		NVIC_SystemReset();		// ������core_m3.c��
		while(1);
}



/*
*********************************************************************************************************
* Function Name  : BSP_RCC_Configuration
* Description    : 				      
* Input          : 
* Output         : None
* Return         : 
*********************************************************************************************************
*/
void	BSP_RCC_Configuration (void)
{		
		RCC_ClocksTypeDef RCC_ClockFreq;
		
		SystemInit();		//Դ��system_stm32f10x.c�ļ�,ֻ��Ҫ���øú����Ϳ�ʵ�ֶ�RCC������
		
		// ʹ��LSI���Ź�����
		RCC_LSICmd(ENABLE);//��LSI
 		while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY)==RESET);//�ȴ�ֱ��LSI�ȶ�
		
		/**************************************************
		��ȡRCC����Ϣ,������
		��ο�RCC_ClocksTypeDef�ṹ�������,��ʱ��������ɺ�,
		���������ֵ��ֱ�ӷ�ӳ�������������ֵ�����Ƶ��
		***************************************************/
		RCC_GetClocksFreq(&RCC_ClockFreq);
		
		/* ������ÿ�ʹ�ⲿ����ͣ���ʱ��,����һ��NMI�ж�,����Ҫ�õĿ����ε�*/
		//RCC_ClockSecuritySystemCmd(ENABLE);

}

/*******************************************************************************
* Function Name  : BSP_SYSCLKConfig_FromStop
* Description    : Configures system clock after wake-up from STOP: enable HSE, PLL
*                  and select PLL as system clock source.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BSP_SYSCLKConfig_FromStop (void)
{
		ErrorStatus 			HSEStartUpStatus;
		
		/* Enable HSE */
		RCC_HSEConfig(RCC_HSE_ON);
		
		/* Wait till HSE is ready */
		HSEStartUpStatus = RCC_WaitForHSEStartUp();
		
		if(HSEStartUpStatus == SUCCESS)
		{
			
#ifdef STM32F10X_CL	
				/* Enable PLL2 */ 
				RCC_PLL2Cmd(ENABLE);

				/* Wait till PLL2 is ready */
				while(RCC_GetFlagStatus(RCC_FLAG_PLL2RDY) == RESET)
				{
				}
#endif
			
				/* Enable PLL */ 
				RCC_PLLCmd(ENABLE);
				
				/* Wait till PLL is ready */
				while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
				{
				}
				
				/* Select PLL as system clock source */
				RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
				
				/* Wait till PLL is used as system clock source */
				while(RCC_GetSYSCLKSource() != 0x08)
				{
				}
		}
}

/*
*********************************************************************************************************
*                                             BSP_PVD_Init()
*
* Description : Initialize the board's PVD
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : PvdLevel:PWR_PVDLevel_2V2 ~ PWR_PVDLevel_2V9.
*********************************************************************************************************
*/
void	BSP_PVD_Init (u32 PvdLevel)
{
		// Enbale PWR & BKP
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE); // ʹ��PVD���ܱ���ʹ��PWR��BKP

		// Configure the PVD Level to 2.9V */
  	PWR_PVDLevelConfig(PvdLevel);

  	// Enable the PVD Output */
  	PWR_PVDCmd(ENABLE);
}
/*
*********************************************************************************************************
*                                             BSP_PVDEXIT_IT_CON()
*
* Description : PVD EXIT Control
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : newSta :DEF_ENABLE or DEF_DISABLE
*********************************************************************************************************
*/
void	BSP_PVDEXIT_IT_CON (u8 newSta)
{
		EXTI_InitTypeDef EXTI_InitStructure;

		EXTI_ClearITPendingBit(EXTI_Line16);	 // PVD�ж�

		// PVD_EXIT (PVD����SWT����)
	  EXTI_InitStructure.EXTI_Line 		= EXTI_Line16;
	  EXTI_InitStructure.EXTI_Mode 		= EXTI_Mode_Interrupt;
	  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	  EXTI_InitStructure.EXTI_LineCmd = (FunctionalState)newSta;
	  EXTI_Init(&EXTI_InitStructure);
}



/*
*********************************************************************************************************
*                                  myPrintf
*
* Description: ���·�װPrintf�����������ʻ����жϣ������Դռ�������ϵͳ���ȴ�
*
* Argument(s): none.
*
* Return(s)  : 0: �ɹ��� -1: ʧ��
*********************************************************************************************************
*/
s8	myPrintf (const char * format, ...)
{	
		INT8U	err = OS_ERR_NONE;
		int n = 0;
		va_list arg;
  
    n = n;
	
		if(OSRunning > 0)
				OSSemPend(DBGMutexSem,	3000,	&err);		//	���ȴ�3s
		else
				if(DBGMutexFlag	== 1)
						DBGMutexFlag	=	0;
				else
						return	-1;			

		if(err != OS_ERR_NONE)
				return	-1;
		else
		{
				va_start(arg,format);
				n = vprintf(format,arg);
				va_end(arg);
		}
		if(OSRunning > 0)
				OSSemPost(DBGMutexSem);									//	�ͷ��ź���
		else
				DBGMutexFlag	=	1;
		
		return 0;
}



/*
*********************************************************************************************************
*                                     		GLOBLE APP Tool
*********************************************************************************************************
*/

/*
*********************************************************************************************************
* Function Name  : GetCpuHwID
* Description    : ��ȡCPU Ӳ��ID�� 96λ 12�ֽ�         
* Input          : 
* Output         : None
* Return         : 
*********************************************************************************************************
*/
void	GetCpuHwID (u8 *idBuf)
{
		u8	i=0;
		vu32	CPU_ID_Addr = 0x1FFFF7E8;

		for(i=0;	i<12;	i++)
		{
				*(idBuf + i) = *(vu8*)(CPU_ID_Addr + i);				
		}
}
/*
*********************************************************************************************************
* Function Name  : SoftDelayMS
* Description    : Dead loop         
* Input          : dllay time
* Output         : None
* Return         : 
*********************************************************************************************************
*/
void	SoftDelayMS(u32	Nms)
{
		u32	i=0,tmploop=0;
		tmploop	=	Nms; 
		while(tmploop--)
		{
			for(i=0;	i<=8980;	i++)
			{}
		}
}
/*
******************************************************************************
* Function Name  : HEX2BCD
* Description    : ���������ֵת����ʮ���Ƶ�BCDģʽ
* Input          : None
* Output         : None
* Return         : 
******************************************************************************
*/
u8 Hex2BCD (u8 hex_data)
{
    u8 bcd_data=0;
    u8 temp=0;
    temp=hex_data%10;
    bcd_data=hex_data/10<<4;
    bcd_data=bcd_data|temp;
    return bcd_data;
}
/*
*********************************************************************************************************
* Function Name  : IsIntString
* Description    : �ж��Ƿ�Ϊ�Ϸ����������ַ�������
* Input          : 
* Output         : None
* Return         : �ɹ�-����ʵ�ʳ��ȣ�ʧ��-����0xffff
*********************************************************************************************************
*/
u16	IsIntString (u8 *pBuf,	u16	len)
{
		u16	i=0;
		for(i=0;	i<len;	i++)
		{
				if(Is_0to9(*(pBuf+i)))
				{
						;
				}
				else
						return	0xffff;
		}
		return	i;
}
/*
*********************************************************************************************************
* Function Name  : IsA2ZString
* Description    : �ж��Ƿ�Ϊ�Ϸ���A~Z��a~z���ַ�������
* Input          : 
* Output         : None
* Return         : �ɹ�-����ʵ�ʳ��ȣ�ʧ��-����0xffff
*********************************************************************************************************
*/
u16	IsA2ZString (u8 *pBuf,	u16	len)
{
		u16	i=0;
		for(i=0;	i<len;	i++)
		{
				if(Is_atoz(*(pBuf+i)) || Is_AtoZ(*(pBuf+i)))
				{
						;
				}
				else
						return	0xffff;
		}
		return	i;
}
/*
*********************************************************************************************************
* Function Name  : IsHexString
* Description    : �ж��Ƿ�Ϊ�Ϸ���ʮ����ֹ��ʽ�ַ�������
* Input          : 
* Output         : None
* Return         : �ɹ�-����ʵ�ʳ��ȣ�ʧ��-����0xffff
*********************************************************************************************************
*/
u16	IsHexString (u8 *pBuf,	u16	len)
{
		u16	i=0;
		for(i=0;	i<len;	i++)
		{
				if(Is_0to9(*(pBuf+i)) || Is_atof(*(pBuf+i)) || Is_AtoF(*(pBuf+i)))
				{
						;
				}
				else
						return	0xffff;
		}
		return	i;
}
/*
*********************************************************************************************************
* Function Name  : IsDotIntString
* Description    : �ж��Ƿ�Ϊ�Ϸ���С���������ַ�������
* Input          : 
* Output         : None
* Return         : �ɹ�-����ʵ�ʳ��ȣ�ʧ��-����0xffff
*********************************************************************************************************
*/
u16	IsDotIntString (u8 *pBuf,	u16	len)
{
		u16	i=0,j=0;

		for(i=0;	i<len;	i++)
		{
				if(*(pBuf+i) == '.')
				{
						j++;
						if((j>=2) || (i == 0) || (i == len-1))
								return	0xffff;
				}
		}
		for(i=0;	i<len;	i++)
		{
				if(Is_0to9(*(pBuf+i)) || *(pBuf+i) == '.')
				{
						;
				}
				else
						return	0xffff;
		}
		return	i;
}
/*
*********************************************************************************************************
*                                           Asc2Hex()
*
* Description : two bit asc code transfor one hex asc code range from '0' to '9'
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : 
*********************************************************************************************************
*/
u8	Asc2Hex(u8	*buf)
{
		u8 hex =0,tmpdataH=0,tmpdataL=0;
		hex = hex;
		tmpdataH = *buf;
		tmpdataH = (tmpdataH - 0x30) * 16;
		tmpdataL = *(buf+1);
		tmpdataL = tmpdataL - 0x30;
		hex	= tmpdataH | tmpdataL;
		return hex;
}
/*
*********************************************************************************************************
* Function Name  : 										String2HexArray()
* Description    : ���ַ�������ת������ֵ���飬��������ֵ���鳤��(������ַ������鳤�ȱ���Ϊż��)        
* Input          : 
* Output         : 
* Return         : �ɹ�:������ֵ���鳤��;ʧ��:����0xffff
*********************************************************************************************************
*/
u16		String2HexArray (u8	*pSrc,	u16	SrcLen,	u8 *pObj)
{    
    u8  tmpBuf[3]="";
    u16	i=0;

    memset(tmpBuf,'\0',sizeof(tmpBuf));

    if(SrcLen % 2 != 0)
        return  0xffff;

    for(i=0; i<SrcLen; i++)
    {
        if((Is_0to9(*(pSrc+i)))|| (Is_AtoF(*(pSrc+i))) || (Is_atof(*(pSrc+i))))
        {
            ;
        }
        else
            return  0xffff;
    }

    for(i=0; i<SrcLen; i+=2)
    {
        memcpy(tmpBuf,(pSrc+i), 2);
#pragma diag_suppress 181
        sscanf((char *)tmpBuf,	"%02X",	(pObj+i/2))	;		// ��HEX�ַ�������ת������ֵ
#pragma diag_default  181
    }
    return  i/2;
}
/*
*********************************************************************************************************
* Function Name  : 										ADCalculateProcess()
* Description    : ��Դ����ȥ�����ֵȥ����Сֵ��ȡƽ��ֵ���        
* Input          : 
* Output         : 
* Return         : ��������򷵻�0xffff ���򷵻�ʵ��ֵ
*********************************************************************************************************
*/
u16	ADCalculateProcess(u16 *pBuf,	u16 len) 
{ 		
		u16	i=0,max=0,min=0;
		u32	sum=0;
		
		if(len == 0)
				return	0xffff;

		max = *pBuf;
	  min = *pBuf;

		for(i=0;  i<len;	i++)
		{
		   if (*(pBuf + i) > max)
		   		max=*(pBuf + i);
		   if (*(pBuf + i) < min)
		   		min=*(pBuf + i);
				
				sum=sum+*(pBuf + i);
		}
		sum = (sum - max - min) / (len -2);
		return (u16)sum;	  
}
/*
*********************************************************************************************************
* Function Name  : 										CheckIsNum()
* Description    : ��������ָ�룬�����Ƿ�ȫΪ��ֵ(��.��Ҳ����Ϊ��ֵ��Ϊ�п����������С��)        
* Input          : 
* Output         : 
* Return         : ���ȫΪ��ֵ���򷵻�0���򷵻�-1
*********************************************************************************************************
*/
s8		CheckIsNum (u8 *pBuf,	u16 len)
{
		u16	i;
		for(i=0;	i<len;	i++)
		{
				if(Is_0to9(*(pBuf + i)) || (*(pBuf + i) == '.'))
				{}
				else
					return	-1;
		}
		return	0;
}	 
/*
*********************************************************************************************************
* Function Name  : 										CheckIsVerb()
* Description    : ���汾�źϷ���(�Ϸ���ʽ"XX.XX" XX-10����ASCII������) 
* Input          : 
* Output         : 
* Return         : �Ϸ�����0���Ƿ�����-1
*********************************************************************************************************
*/
s8		CheckIsVerb (u8 *pVerb)
{
		if((Is_0to9(*(pVerb + 0))) &&
			 (Is_0to9(*(pVerb + 1))) &&
			 (*(pVerb + 2) == '.') &&
			 (Is_0to9(*(pVerb + 3))) &&
			 (Is_0to9(*(pVerb + 4))))
		{
				return	0;
		}
		else
				return -1;
}	 
/*
*********************************************************************************************************
* Function Name  : 										MakeStrNum2USC2()
* Description    : �����ַ�����ֵ����ָ�룬�������USC2����ַ������س�����"1234"->"0031003200330034"        
* Input          : 
* Output         : 
* Return         : ����ַ�����Ϊ��ֵ�򷵻�0xffff���򷵻س���
*********************************************************************************************************
*/
u16		MakeStrNum2USC2 (u8 *pSrc,	u16 srcLen,	u8	*pObj)
{
		u8	tmpBuf[10];
		u16 i,j;
	  if(CheckIsNum(pSrc,	srcLen) != 0)
			return	0xffff;
		else
		{
				for(i=0,j=0;	i<srcLen;	i++,j+=4)
				{
						sprintf((char *)tmpBuf,	"%04X",	*(pSrc + i));
						memcpy((pObj + j),	tmpBuf,	4);				
				}
				return	j;
		}
}
/*
*********************************************************************************************************
* Function Name  : 										CheckPhoneFormat()
* Description    : ���������ַ����Ƿ���ϱ����绰�ĸ�ʽ��12349584#123947584#1239495#�����������绰���        
* Input          : ���ĳһ�绰������Ϊ<4��>16�򳤶ȷ���0xffff�����������Ϊ0����Ϊ�Ϸ�ֱ��д0
* Output         : 
* Return         : ����Ƿ���0�����򷵻�-1
*********************************************************************************************************
*/
s8		CheckPhoneFormat (u8 *pSrc,	u16 srcLen,	u8	*pObj1,	u16 *obj1Len,	u8	*pObj2,	u16 *obj2Len, u8	*pObj3,	u16 *obj3Len)
{
		u16 i,j;
		
		// ��顮#�����Ƿ�Ϊ3���������һ���Ƿ�Ϊ��#��
		j=0;
		for(i=0;	i<srcLen;	i++)
		{
				if(*(pSrc + i) == '#')
						j++;
		}
		if((j != 3) || (*(pSrc + srcLen -1) != '#')) // �Ϸ���ʽ��β��������3����#�����ҽ�β�ǡ�#��
				return	-1;
		else
		{
				// ���ƺ���1
				for(i=0,j=0;	(*(pSrc + i) != '#');	i++,j++)
				{
						*(pObj1 + j) = *(pSrc + i);
				}
				*(pObj1 + j) = '\0';
				if(((j < 4) && (j != 0)) || (j > 16))
						*obj1Len	=	0xffff;
				else
						*obj1Len 	= j;
				
				// ���ƺ���2
				i++;
				for(j=0;	(*(pSrc + i) != '#');	i++,j++)
				{
						*(pObj2 + j) = *(pSrc + i);
				}
				*(pObj2 + j) = '\0';
				if(((j < 4) && (j != 0)) || (j > 16))
						*obj2Len	=	0xffff;
				else
						*obj2Len 	= j;

				// ���ƺ���3
				i++;
				for(j=0;	(*(pSrc + i) != '#');	i++,j++)
				{
						*(pObj3 + j) = *(pSrc + i);
				}
				*(pObj3 + j) = '\0';
				if(((j < 4) && (j != 0)) || (j > 16))
						*obj3Len	=	0xffff;
				else
						*obj3Len 	= j;
				return	0;
		}
}

/*
*********************************************************************************************************
* Function Name  : 										SNCode2barCode()
* Description    :         
* Input          : 
* Output         : 
* Return         : ���󷵻�0xffff ��ȷ����0
*********************************************************************************************************
*/
u16		SNCode2barCode (u32 *srcID,	u32 *objID)
{
		if((*srcID & 0xff000000) >> 24 != 0x1A)
				return	0xffff;
		else
				*objID	=	*srcID ^ 0x1ABCDEF2;
		return	0;
}
/*
*********************************************************************************************************
* Function Name  : 										StringAdd()
* Description    : Dead loop         
* Input          : dllay time
* Output         : None
* Return         : Len of pStr
*********************************************************************************************************
*/
u16		StringAdd (u8	*pStr,	u8	*pStrF) 
{ 
	  u16 i=0,j=0; 
	
	  for(i=0;	*(pStr+i)!='\0';	i++)
		{;}
		
		for(j=0;	*(pStrF + j)!='\0';	j++)
		{
				*(pStr + i + j)=*(pStrF + j);
		}
	
		pStr[i+j]='\0';
		
		return	(i+j);
} 
/*
*********************************************************************************************************
* Function Name  : 										StringConnect()
* Description    : �ַ������Ӻ���       
* Input          : 
* Output         : 
* Return         : 
*********************************************************************************************************
*/
u16		StringConnect (u8	*pStr,	u8	*pStrF,		u8	*pStrB) 
{ 
	  u16 i=0,j=0; 
	  for(i=0;	*(pStrF+i)!='\0';	i++) 
	  		*(pStr + i)=*(pStrF + i); 
	   
	  for(j=0;	*(pStrB+j)!='\0';	j++)  
	  		*(pStr + i + j)=*(pStrB + j); 
	
		pStr[i+j]='\0';
	
		return	(i+j);
} 
/*
*********************************************************************************************************
* Function Name  : 										Hex2StringArray()
* Description    : ����ֵ����ת�����ַ������飬�������ַ�����ֵ����        
* Input          : 
* Output         : 
* Return         : ���ȫΪ��ֵ���򷵻�0���򷵻�-1
*********************************************************************************************************
*/
u16		Hex2StringArray (u8	*pSrc,	u16	SrcLen,	u8 *pObj)
{
		u16	i=0;

		for(i=0;	i<SrcLen;	i++)
		{
				sprintf((char *)(pObj + i * 2),	"%02X",	*(pSrc + i));
		}
	  *(pObj + i * 2) = '\0';
		return	(i * 2);
}
/*
*********************************************************************************************************
*                                     StringSearch()
*
* Description: 	Search and matching the string form the source to object and point the position of the first
*							 	byte . ��ע:����Աȵ�ԭ�ַ�����Ŀ���ַ���Ϊ���򷵻ش���
*
* Argument(s): 	*pSource - Point to the first byte of the source.
*        				*pObject - Point to the first byte of the object.
*        				SrcLen   - The length of the source array.
*        				ObjLen   - The length of the object array.
*
* Return(s)  :  j 					- success	 //���ص�λ���Ƕ�Ӧ�������е�λ�ü�Ϊj����ʵ��λ��N j=N-1
*								0xffff 			- failure	 //[ע]֧��ͨ���������*��
* Note(s)    : 
*********************************************************************************************************
*/
u16 	StringSearch(u8 *pSource,u8 *pObject,u16 SrcLen,u16 ObjLen)
{
    u16 i=0,j=0;

		if((SrcLen == 0) || (ObjLen == 0))
				return	0xffff;									/* ���ԭ�ַ�����Ŀ���ַ�����һ������Ϊ0��Ϊ����Ƿ��˳� */
    
		while(j<SrcLen)								 			/* �ж��Ƿ�Դ�ַ���ָ���Ѿ��Ƶ���� */
		{
        if((j+ObjLen) > SrcLen)
				{
            return 0xffff;		 					/* ˵�����յ����ַ���(Դ�ַ���)����<Ŀ���ַ������� ��ζ�Ž��ճ��Ȳ��� */
        }
        for(i=0;i<ObjLen;i++)
				{
            if(*(pSource+i) != *(pObject+i))
						{
								if(*(pObject+i) == '*')		/* �����ͨ�����*�������� */
								{}
								else
	                	break;
						}
						else
						{}										 			/* �ɹ�ƥ����һ���ַ�Ȼ��Ŀ���ַ���ָ�뽫����1λ */
        }
        if(i==ObjLen)						  
            return j;							 			/* ˵��ѭ���ȶ����(����Ŀ���ַ�����Դ�ַ�������ͬ�Ĳ��ֱ���Ϊ�������ֲ��У���֧�ּ�ϱȶ�) */
        else											 			/* �����жϼ�ϵ�ƥ�������ͨ�����*����ռλ */
				{
            pSource++;						 			/* Դ�ַ���ָ����ƣ������ȶ� */
            j++;
        }  
    }
    return 0xffff;
}


/*
*********************************************************************************************************
* Function Name  : Mktime
* Description    : ����1970�굽���ڵ�������ʱ����ת������
* Input          : None
* Output         : None
* Return         : 
*********************************************************************************************************
*/
u32 Mktime (u32 year, u32 mon,u32 day, u32 hour,u32 min, u32 sec)
{
    if (0 >= (int) (mon -= 2))
		{    /**//* 1..12 -> 11,12,1..10 */
         mon += 12;      /**//* Puts Feb last since it has leap day */
         year -= 1;
    }

    return (((
             (u32) (year/4 - year/100 + year/400 + 367*mon/12 + day) +
             year*365 - 719499
          )*24 + hour /**//* now have hours */
       )*60 + min /**//* now have minutes */
    )*60 + sec; /**//* finally seconds */
}

/*
*********************************************************************************************************
* Function Name  : Gettime
* Description    : ����1970�������ת����������ʱ����
* Input          : None
* Output         : None
* Return         : 
*********************************************************************************************************
*/
void Gettime (u32 count,	SYS_DATETIME *cnt)
{
		time_t t=count;
		struct tm *p;
	
		p=localtime(&t); 
		
		cnt->year		=1900+p->tm_year;
		cnt->month	=1+p->tm_mon;
		cnt->day		=p->tm_mday;
		cnt->hour		=p->tm_hour;
		cnt->minute	=p->tm_min;
		cnt->second	=p->tm_sec;
}
/*
*********************************************************************************************************
* Function Name  : SumCheck16Pro
* Description    : 16λ�ۼӺͼ��麯��
* Input          : *srcBuf :Ŀ����������ָ��(������ϸ�ʽsumH+sumL+data......��ʽ)
*								 : srcLen  :Ŀ������������
* Output         : None
* Return         : 0
*********************************************************************************************************
*/
u16	 SumCheck16Pro (u8 *srcBuf,	u16	srcLen)
{
		u16 i=0,	sum=0;
		sum = *srcBuf;
		for(i=1;	i<srcLen;	i++)
		{
				sum += *(srcBuf + i);
		}
		return	sum;
}

/*
*********************************************************************************************************
* Function Name  : XorCheck16Pro
* Description    : 8λ�������
* Input          : *srcBuf :Ŀ����������ָ��(������ϸ�ʽsumH+sumL+data......��ʽ)
*								 : srcLen  :Ŀ������������
* Output         : None
* Return         : 0
*********************************************************************************************************
*/
u8 XorCheck16Pro(u8 *srcBuf,	u16	srcLen)
{
		u8 i = 0;
		u8 check_temp = srcBuf[0];
		for(i = 1;i<srcLen;i++)
			check_temp ^= srcBuf[i];
		return(check_temp);

}
/*
*********************************************************************************************************
*                                     OSTmr_Count_Start
*
* Description: Time Count start base on OS [note]Must use after OS start!!!!!
*
* Argument(s): Max count 0xFFFFFFFF (49.7Сʱ)
*
* Return(s)  : 
*
* Note(s)    : 
*********************************************************************************************************
*/
void	OSTmr_Count_Start(vu32	*pCounter)
{
		OS_CPU_SR  cpu_sr=0;

		/* Get system os time */
		OS_ENTER_CRITICAL();
		*pCounter	=	OSTime;
		OS_EXIT_CRITICAL();	
}
/*
*********************************************************************************************************
*                                     OSTmr_Count_Get
*
* Description: Time Count stop [note]Must use after OS start!!!!!
*
* Argument(s): none.
*
* Return(s)  : time * ms (os tick must be 1000HZ)
*
* Note(s)    : 
*********************************************************************************************************
*/
u32	OSTmr_Count_Get(vu32	*pCounter)
{
		OS_CPU_SR  cpu_sr=0;
		vu32	tmptime = 0;
		/* Get system os time */
		OS_ENTER_CRITICAL();
		tmptime	=	OSTime;
		OS_EXIT_CRITICAL();
		/* Overflow */
		if(tmptime < *pCounter)
				return	(0xffffffff - *pCounter + tmptime);	
		else
				return  (tmptime - *pCounter);	
}
/*
*********************************************************************************************************
*                                     BSP_Write_Para
*
* Description: write system para
*
* Argument(s): none.
*
* Return(s)  : 1 OK  0 ERRO
*
* Note(s)    : 
*********************************************************************************************************
*/
u8 BSP_Write_Para(TYPEDEF_PARA* para)
{
	  u16 i = 0;
	  u8 buf[PARA_SIZE] = {0};
		FLASH_Unlock();
	  FLASH_ErasePage(DEF_ADDR_FALSH_PARA);
    memcpy(buf ,(u8*)para ,  PARA_SIZE);
		for(;i<PARA_SIZE;)
		{
			 if((PARA_SIZE-i)/4)
			 {
				 FLASH_ProgramWord(DEF_ADDR_FALSH_PARA+i,*(u32*)&buf[i]);
				 i+=4;
			 }
			 else if((PARA_SIZE-i)/2)
			 {
				 FLASH_ProgramHalfWord(DEF_ADDR_FALSH_PARA+i,*(u16*)&buf[i]);
				 i+=2;
			 }
			 else 
			 {
				 FLASH_ProgramOptionByteData(DEF_ADDR_FALSH_PARA+i,*(u8*)&buf[i]);
				 i++;
			 }			 
		}
		FLASH_Lock();	
	  if(memcmp((u8*)DEF_ADDR_FALSH_PARA , (u8*)para,  PARA_SIZE) == 0)
			  return 1;
		else 
			  return 0;
}
/*
*********************************************************************************************************
*                                     BSP_ReadPara
*
* Description: read system para
*
* Argument(s): none.
*
* Return(s)  : none
*
* Note(s)    : 
*********************************************************************************************************
*/
void  BSP_Read_Para(TYPEDEF_PARA * para)
{
		memcpy(para , (u8*)DEF_ADDR_FALSH_PARA , sizeof(TYPEDEF_PARA));
}
