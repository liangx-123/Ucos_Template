#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "includes.h"
/************************************************
 ALIENTEK MiniSTM32开发板UCOS实验
 例1-1 UCOSII移植
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

//START 任务
//设置任务优先级
#define START_TASK_PRIO			10  ///开始任务的优先级为最低
//设置任务堆栈大小
#define START_STK_SIZE			128
//任务任务堆栈
OS_STK START_TASK_STK[START_STK_SIZE];
//任务函数
void start_task(void *pdata);

//LED0任务
//设置任务优先级
#define LED0_TASK_PRIO			3
//设置任务堆栈大小
#define LED0_STK_SIZE			64
//任务堆栈
OS_STK LED0_TASK_STK[LED0_STK_SIZE];
//任务函数
void led0_task(void *pdata);

#define KEY_TASK_PRIO			8
//设置任务堆栈大小
#define KEY_STK_SIZE			64
//任务堆栈
OS_STK KEY_TASK_STK[KEY_STK_SIZE];
//任务函数
void keytask(void *pdata);



//任务函数
void float_task(void *pdata);

int main(void)
{
	delay_init();       //延时初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //中断分组配置

	LED_Init();  	//LED初始化
	
	OSInit();  		//UCOS初始化
	OSTaskCreate(start_task,(void*)0,(OS_STK*)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO); //创建开始任务
	OSStart(); 	//开始任务
}

//开始任务
void start_task(void *pdata)
{
	OS_CPU_SR cpu_sr=0;
	pdata=pdata;
	OSStatInit();  //开启统计任务
	
	OS_ENTER_CRITICAL();  //进入临界区(关闭中断)
	OSTaskCreate(led0_task,(void*)0,(OS_STK*)&LED0_TASK_STK[LED0_STK_SIZE-1],LED0_TASK_PRIO);//创建LED0任务
	OSTaskCreate(keytask,(void*)0,(OS_STK*)&KEY_TASK_STK[KEY_STK_SIZE-1],KEY_TASK_PRIO);//创建LED0任务
	OSTaskSuspend(START_TASK_PRIO);//挂起开始任务
	OS_EXIT_CRITICAL();  //退出临界区(开中断)
}
 

//LED0任务
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
if(KEY0==0)	  //按键KEY2
	{
	LED0 = 1;			//熄灭LED2
	}	}
			OSTimeDlyHMSM(0,0,0,20);
}
