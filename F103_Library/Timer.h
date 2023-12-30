#ifndef __Timer_H
#define __Timer_H

#include "stm32f10x.h"

#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */
#define   	__I     volatile const       /*!< Defines 'read only' permissions */
	
#define	TIM_Channel_1	1
#define	TIM_Channel_2	2
#define	TIM_Channel_3	3
#define	TIM_Channel_4	4



/*----------------Timer General Function-----------------*/
//Timer Slave Mode Define
#define	SLAVE_DISABLED			0
#define SLAVE_EncoderMode_1	1
#define SLAVE_EncoderMode_2	2
#define SLAVE_EncoderMode_3	3
#define SLAVE_ResetMode			4
#define	SLAVE_GatedMode			5
#define	SLAVE_TriggerMode		6

//Timer Channel Define
#define	TIM_Channel_1	1
#define	TIM_Channel_2	2
#define	TIM_Channel_3	3
#define	TIM_Channel_4	4

//Timer Channel Polarity Define
#define TIM_EDGE_RISING	0
#define TIM_EDGE_FALING	1

//Timer Channel Direction
#define	TIM_Channel_OUTPUT	0
#define	TIM_Channel_INPUT		1



void TIM_ChannelConfig(uint8_t channel);
void TIM_EnableTimerClock(TIM_TypeDef* Timer);
void TIM_SetSlaveMode(TIM_TypeDef* Timer, uint8_t SlaveMode);
void TIM_SetPolarity(TIM_TypeDef* Timer, uint8_t Channel, uint8_t Edge);
void TIM_SetChannelDirection(TIM_TypeDef* Timer, uint8_t Channel, uint8_t ChannelDir);
void TIM_EnableCounter(TIM_TypeDef* Timer);

void PWM_EnableUpdateGeneration();
void TIM_EnableCCOutput(uint8_t channel);




/*-----------------PWM User Function---------------------*/
void TIM_PWM_Init(TIM_TypeDef* Timer, uint16_t channel, uint16_t prescaler, uint16_t arrValue, uint16_t CCRxValue);
void TIM_PWM_Start(TIM_TypeDef* Timer, uint8_t Channel);
void TIM_PWM_SetPrescaler(uint16_t prescalerValue);
void TIM_PWM_SetARRReg(uint16_t ARRValue);
void TIM_PWM_SetCCRxReg(uint16_t CCRxValue, uint16_t channel);
void TIM_TIM_ChannelMode_1(uint8_t channel);



#endif //__Timer_H