/**
	************************************************************
	************************************************************
	************************************************************
	*	??????? 	key.c
	*
	*	????? 		?????
	*
	*	????? 		2016-11-23
	*
	*	?汾?? 		V1.0
	*
	*	????? 		key???????????
	*
	*	???????	
	************************************************************
	************************************************************
	************************************************************
**/

//?????????
#include "stm32f10x.h"

//???????
#include "key.h"
#include "delay.h"
#include "led.h"


uint8_t ONorOFF=0;
/*
************************************************************
*	?????????	key_Init
*
*	?????????	???????????
*
*	????????	??
*
*	?????????	??
*
*	?????		
************************************************************
*/
void key_Init(void)
{
	
	GPIO_InitTypeDef gpio_initstruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;	
	//开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	//GPIO初始化
	
	gpio_initstruct.GPIO_Mode = GPIO_Mode_IPU;				
	gpio_initstruct.GPIO_Pin = GPIO_Pin_13;						
	gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;				
	GPIO_Init(GPIOB, &gpio_initstruct);	

		/*AFIO选择中断引脚*/
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,  GPIO_PinSource13);
	
//中断初始化
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line13;            
    EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;      
    EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;
    EXTI_InitStruct.EXTI_LineCmd=ENABLE;   					
	EXTI_Init(&EXTI_InitStruct);

	/*NVIC中断分组*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//配置NVIC为分组2
																//即抢占优先级范围：0~3，响应优先级范围：0~3
																//此分组配置在整个工程中仅需调用一次
																//若有多个中断，可以把此代码放在main函数内，while循环之前
																//若调用多次配置分组的代码，则后执行的配置会覆盖先执行的配置
	
	/*NVIC配置*/
						//定义结构体变量
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;		//选择配置NVIC的EXTI1线
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//指定NVIC线路使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//指定NVIC线路的抢占优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;			//指定NVIC线路的响应优先级为1
	NVIC_Init(&NVIC_InitStructure);								//将结构体变量交给NVIC_Init，配置NVIC外设
}


void EXTI15_10_IRQHandler(void){
	
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==RESET){
		DelayXms(10);											//延时消抖
		while (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==RESET);	//等待按键松手
		DelayXms(10);
		//延时消抖
		if(ONorOFF==0){
			led_Set(led_ON);
			ONorOFF=1;
		}
		else if(ONorOFF==1){
			led_Set(led_OFF);
			ONorOFF=0;
		}
		
	}
	EXTI_ClearITPendingBit(EXTI_Line13);
}
