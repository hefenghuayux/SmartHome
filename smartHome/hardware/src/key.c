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
	*	?��?? 		V1.0
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
	//����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	//GPIO��ʼ��
	
	gpio_initstruct.GPIO_Mode = GPIO_Mode_IPU;				
	gpio_initstruct.GPIO_Pin = GPIO_Pin_13;						
	gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;				
	GPIO_Init(GPIOB, &gpio_initstruct);	

		/*AFIOѡ���ж�����*/
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,  GPIO_PinSource13);
	
//�жϳ�ʼ��
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line13;            
    EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;      
    EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;
    EXTI_InitStruct.EXTI_LineCmd=ENABLE;   					
	EXTI_Init(&EXTI_InitStruct);

	/*NVIC�жϷ���*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//����NVICΪ����2
																//����ռ���ȼ���Χ��0~3����Ӧ���ȼ���Χ��0~3
																//�˷������������������н������һ��
																//���ж���жϣ����԰Ѵ˴������main�����ڣ�whileѭ��֮ǰ
																//�����ö�����÷���Ĵ��룬���ִ�е����ûḲ����ִ�е�����
	
	/*NVIC����*/
						//����ṹ�����
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;		//ѡ������NVIC��EXTI1��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//ָ��NVIC��·ʹ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//ָ��NVIC��·����ռ���ȼ�Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;			//ָ��NVIC��·����Ӧ���ȼ�Ϊ1
	NVIC_Init(&NVIC_InitStructure);								//���ṹ���������NVIC_Init������NVIC����
}


void EXTI15_10_IRQHandler(void){
	
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==RESET){
		DelayXms(10);											//��ʱ����
		while (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==RESET);	//�ȴ���������
		DelayXms(10);
		//��ʱ����
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
