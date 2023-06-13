#include "stm32f10x.h"                 
#include "MPU6050.h"

void TIM2_IRQHandler(void) {
    if(TIM2->SR & TIM_SR_UIF) {
			MPU6050_Counter(); 
			
			TIM2->SR &= ~TIM_SR_UIF; // Clear interrupt flag
    }
}
