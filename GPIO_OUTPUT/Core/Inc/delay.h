#ifndef DELAY_H
#define DELAY_H

#include "stm32f4xx.h"  // STM32F4 library for hardware access

// Function prototypes
void delay_init(void);  // Initializes Timer 11
void delay_ms(uint32_t ms);  // Millisecond delay function using Timer 11

#endif // DELAY_H
