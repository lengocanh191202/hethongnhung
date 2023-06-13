#include "stm32f10x.h"                 

uint32_t volatile milliseconds = 0;
uint32_t volatile ledTicks = 0;

// Interrupt handler function
void SysTick_Handler(void) {
	milliseconds++;
	ledTicks++;
}

// Function to create delay in milliseconds
void DelayMs(uint32_t ticks) {
	uint32_t temp = milliseconds;
	while(milliseconds < ticks + temp);
	milliseconds = 0;
}
