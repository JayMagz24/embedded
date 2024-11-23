#include "delay.h"

// Function to initialize Timer 11 for delay purposes
void delay_init(void)
{
    // Enable clock for Timer 11
    RCC->APB2ENR |= RCC_APB2ENR_TIM11EN;

    // Set the prescaler to 16000 to get a 1ms tick (Assuming 16 MHz system clock)
    TIM11->PSC = 25000 - 1;  // Prescaler to achieve 1 ms tick

    // Set the auto-reload value for Timer 11
    TIM11->ARR = 0xFFFF;  // Set the maximum count value (timer will count to 0xFFFF)

    // Reset the counter and disable the timer
    TIM11->CNT = 0;
    TIM11->CR1 &= ~TIM_CR1_CEN;  // Ensure the timer is disabled initially
}

// Millisecond delay function using Timer 11
void delay_ms(uint32_t ms)
{
    TIM11->ARR = ms - 1;  // Set the auto-reload register for the delay

    TIM11->CNT = 0;  // Reset counter
    TIM11->CR1 |= TIM_CR1_CEN;  // Enable the timer

    // Wait until the timer reaches the value in ARR
    while (!(TIM11->SR & TIM_SR_UIF));  // Wait for the update interrupt flag (UIF)

    TIM11->SR &= ~TIM_SR_UIF;  // Clear the update interrupt flag
    TIM11->CR1 &= ~TIM_CR1_CEN;  // Disable the timer after the delay
}
