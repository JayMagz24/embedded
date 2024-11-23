#include "stm32f4xx.h"

void clock_init(void);
void gpio_init(void);
void timer_init(void);
void delay(uint32_t ms);

int main(void)
{
    clock_init();   // Initialize clock
    gpio_init();    // Initialize GPIO
    timer_init();   // Initialize delays

    while (1)
    {
        GPIOC->ODR ^= GPIO_ODR_OD13;
        delay(100);
    }
}

// Function to initialize CLOCK
void clock_init(void)
{
    // Enable HSE (High-Speed External) Clock
    RCC->CR |= RCC_CR_HSEON; // Set the HSEON bit to turn on HSE

    // Wait until HSE is ready
    while (!(RCC->CR & RCC_CR_HSERDY)); // Wait until HSERDY (HSE Ready) flag is set

    /*--------------------------Select HSE as system clock source--------------------------*/
    RCC->CFGR &= ~RCC_CFGR_SW;    // Clear the SW bits
    RCC->CFGR |= RCC_CFGR_SW_HSE; // Set SW to HSE (system clock source)

    // Wait until HSE is used as the system clock
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSE); // Wait until SWS matches HSE

    /*----------------------Configure AHB, APB1, and APB2 prescalers-----------------------*/
    RCC->CFGR &= ~RCC_CFGR_HPRE;  // Clear AHB prescaler bits (set division factor to /1)
    RCC->CFGR &= ~RCC_CFGR_PPRE1; // Clear APB1 prescaler bits (set division factor to /1)
    RCC->CFGR &= ~RCC_CFGR_PPRE2; // Clear APB2 prescaler bits (set division factor to /1)

    /*------------------------------Disable the PLL (optional)-----------------------------*/
    RCC->CR &= ~RCC_CR_PLLON;     // Ensure PLL is turned off (not used)

    // Update the SystemCoreClock variable
    SystemCoreClock = 25000000;   // Set system clock to HSE frequency (25 MHz)
}

// Function to initialize GPIO
void gpio_init(void)
{
    // Enable the GPIOA, GPIOB and GPIOC clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    /*--------------------------Configure PC13 as output mode-----------------------------*/
    GPIOC->MODER &= ~GPIO_MODER_MODER13;            // Clear mode bits for PC13
    GPIOC->MODER |= GPIO_MODER_MODER13_0;           // Set as output mode (01)
    GPIOC->OTYPER &= ~GPIO_OTYPER_OT13;             // Set to push-pull for PC13 (default)
    GPIOC->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED13;       // Set low speed for PC13 (optional)
    GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD13;             // No pull-up, pull-down for PC13 (optional)
}

// Function to initialize Timer 11 for delay purposes
void timer_init(void)
{
    // Enable clock for Timer 11
    RCC->APB2ENR |= RCC_APB2ENR_TIM11EN;

    // Set the prescaler to 25000 to get a 1ms tick (Assuming 25 MHz system clock)
    TIM11->PSC = 25000 - 1;  // Prescaler to achieve 1 ms tick

    // Set the auto-reload value for Timer 11
    TIM11->ARR = 0xFFFF;  // Set the maximum count value (timer will count to 0xFFFF)

    // Reset the counter and disable the timer
    TIM11->CNT = 0;
    TIM11->CR1 &= ~TIM_CR1_CEN;  // Ensure the timer is disabled initially
}

// Millisecond delay function using Timer 11
void delay(uint32_t ms)
{
    TIM11->ARR = ms - 1;  // Set the auto-reload register for the delay

    TIM11->CNT = 0;  // Reset counter
    TIM11->CR1 |= TIM_CR1_CEN;  // Enable the timer

    // Wait until the timer reaches the value in ARR
    while (!(TIM11->SR & TIM_SR_UIF));  // Wait for the update interrupt flag (UIF)

    TIM11->SR &= ~TIM_SR_UIF;  // Clear the update interrupt flag
    TIM11->CR1 &= ~TIM_CR1_CEN;  // Disable the timer after the delay
}
