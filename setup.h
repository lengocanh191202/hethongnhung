#ifndef __SETUP_H
#define __SETUP_H

#include "stm32f10x.h" 

void IO_Init(void);
void Timer_Init(void);
void DelayMs(uint32_t TICK);
void GPIO_TogglePIN(GPIO_TypeDef *GPIOx, uint16_t PIN);
#endif
