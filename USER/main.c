#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "includes.h"
/************************************************
 ALIENTEK MiniSTM32������UCOSʵ��
 ��1-1 UCOSII��ֲ
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

//START ����
//�����������ȼ�
#define START_TASK_PRIO			10  ///��ʼ��������ȼ�Ϊ���
//���������ջ��С
#define START_STK_SIZE			128
//���������ջ
OS_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *pdata);

//LED0����
//�����������ȼ�
#define LED0_TASK_PRIO			3
//���������ջ��С
#define LED0_STK_SIZE			64
//�����ջ
OS_STK LED0_TASK_STK[LED0_STK_SIZE];
//������
void led0_task(void *pdata);

#define KEY_TASK_PRIO			8
//���������ջ��С
#define KEY_STK_SIZE			64
//�����ջ
OS_STK KEY_TASK_STK[KEY_STK_SIZE];
//������
void keytask(void *pdata);



//������
void float_task(void *pdata);

int main(void)
{
	delay_init();       //��ʱ��ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�жϷ�������

	LED_Init();  	//LED��ʼ��
	
	OSInit();  		//UCOS��ʼ��
	OSTaskCreate(start_task,(void*)0,(OS_STK*)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO); //������ʼ����
	OSStart(); 	//��ʼ����
}

//��ʼ����
void start_task(void *pdata)
{
	OS_CPU_SR cpu_sr=0;
	pdata=pdata;
	OSStatInit();  //����ͳ������
	
	OS_ENTER_CRITICAL();  //�����ٽ���(�ر��ж�)
	OSTaskCreate(led0_task,(void*)0,(OS_STK*)&LED0_TASK_STK[LED0_STK_SIZE-1],LED0_TASK_PRIO);//����LED0����
	OSTaskCreate(keytask,(void*)0,(OS_STK*)&KEY_TASK_STK[KEY_STK_SIZE-1],KEY_TASK_PRIO);//����LED0����
	OSTaskSuspend(START_TASK_PRIO);//����ʼ����
	OS_EXIT_CRITICAL();  //�˳��ٽ���(���ж�)
}
 

//LED0����
void led0_task(void *pdata)
{
	while(1)
	{
//		LED0=0; 
//		delay_ms(2000);
//		LED0=1;
//		delay_ms(2000);
		LED0=0; 
		OSTimeDlyHMSM(0,0,0,20);


	


	}
}

void keytask(void *pdata){
	while(1){
if(KEY0==0)	  //����KEY2
	{
	LED0 = 1;			//Ϩ��LED2
	}	}
			OSTimeDlyHMSM(0,0,0,20);
}
