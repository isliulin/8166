#ifndef _PATROL_CONTROL_H
#define _PATROL_CONTROL_H
#include "main.h"
#include <stdio.h>
#include "hal_process_CONTROL.h"
typedef enum
{
	Forward,
	Backward,
	Left,
	Right,
	Stop
} TrackingDir;
extern TrackingDir abcsse;
typedef union{
  float f;
  char  PmBuf[4];
}PmData;

typedef union{
  float pid;
  char  PwBuf[4];
}PwData;

typedef struct PID //�Ӿ�pidѭ���㷨
{ 
	float SetPoint;      // �趨Ŀ��Desired value 
	float Proportion;    // ��������Proportional Const 
	float Integral;      // ���ֳ���Integral Const 
	float Derivative;    // ΢�ֳ���Derivative Const 
	float LastError;     // Error[-1] 
	float PrevError;    // Error[-2] 
	float SumError;    // Sums of Errors 
} PID;


/***************************��������****************************************************/
float PIDCalc( PID *pp, float CurrPoint );
//float getdis(bool Q1, bool Q2, bool Q3, bool Q4, bool Q5, bool Q6, bool Q7, bool Q8,bool Q9, bool Q10, bool Q11, bool Q12, bool Q13, bool Q14);//����Ѳ��ƫ��Ƕȼ����㷨
long getdis(char Q1, char Q2, char Q3, char Q4, char Q5, char Q6, char Q7, char Q8,char Q9, char Q10, char Q11, char Q12, char Q13, char Q14);//����Ѳ��ƫ��Ƕȼ����㷨
void TrackingLR(TrackingDir dir);//90���������ߣ����ݺ��⴫������ʵʱ�������ӽǶ�
void Tracking(TrackingDir dir);//ֱ��ǰ�����ˣ����ݺ��⴫������ʵʱ�������ӽǶ�
void LeftWheel(double turnpos);//����ת������λ����ת
void RightWheel(double turnpos);//����ת������λ����ת
void BackwardWheel(double turnpos);//����ת������λ����ת
void ForwardWheel(double turnpos);//ǰ��ת������λ����ת
float PidFlashAvrB(void);
float PidFlashAvrF(void);
bool isFrontBlimited(void);  //ǰ��λ
bool isBackFlimited(void);	  //����λ	
bool isLeftRlimited(void);   //����λ
bool isRightLlimited(void);  //����λ
void OnReadIR(void);
void ClearFpidBpid(void);

u8 Barrier(u16 wpos1 , u16 wpos2 ,u8 lpos1 , u8 lpos2);
#endif

