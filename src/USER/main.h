#ifndef _MAIN_H_
#define _MAIN_H_

#include "bsp.h"
#include "ucos_ii.h"
#include "os_cpu.h"


//�������ȼ�
#define  APP_CFG_TASK_START_PRIO							6u



#define  APP_CFG_TASK_LWIP_PRIO               9u
#define  APP_CFG_TASK_CONTROL_PRIO            8u

#define  APP_CFG_TASK_DATACOLLECT_PRIO        7u


#define  APP_CFG_TASK_TOGGLELED_PRIO          10u
#define  APP_CFG_TASK_DEBUG_PRIO              11u

#define  LWIP_TASK_START_PRIO                  12u
#define  LWIP_TASK_END_PRIO                    14u


//#define  OS_TASK_TMR_PRIO              (OS_LOWEST_PRIO - 2)
//�����ջ��С
#define	 APP_CFG_TASK_START_STK_SIZE          128
#define	 APP_CFG_TASK_LWIP_STK_SIZE           256 
#define	 APP_CFG_TASK_ToggleLED_STK_SIZE      64
#define	 APP_CFG_TASK_DataCollect_STK_SIZE    128   
#define  APP_CFG_TASK_CONTROL_STK_SIZE        256
#define  APP_CFG_TASK_DEBUG_STK_SIZE          256



extern   OS_EVENT							*DBGMutexSem;							// DBG printf���������Ϣ�����ź���
extern   OS_EVENT							*NetMutexSem;
extern   OS_EVENT							*USART1Mbox;						  // ����1����
extern   OS_EVENT							*USART2Mbox;						  // ����2����
extern   OS_EVENT							*USART3Mbox;						  // ����3����
extern   OS_EVENT							*UART4Mbox;						    // ����4����
extern   OS_EVENT							*UART5Mbox;						    // ����5����
extern   OS_EVENT							*GSMBtAppMbox;						// ������ȡҵ��״̬����
extern   OS_EVENT							*CANItMbox;						    // can�ж���Ϣ
extern   OS_EVENT							*NetCmdMbox;						    // ��������
extern   OS_EVENT							*NetOutMbox;						    // ��������
extern   OS_EVENT							*DebugMbox;						    // ����
#endif
