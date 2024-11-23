#include "clock.h"

void clock_init(void)
{
    // 1. Enable HSE (High-Speed External) Clock
    RCC->CR |= RCC_CR_HSEON; // Set the HSEON bit to turn on HSE

    // 2. Wait until HSE is ready
    while (!(RCC->CR & RCC_CR_HSERDY))
    {
        // Wait until HSERDY (HSE Ready) flag is set
    }

    // 3. Select HSE as the system clock source
    RCC->CFGR &= ~RCC_CFGR_SW;    // Clear the SW bits
    RCC->CFGR |= RCC_CFGR_SW_HSE; // Set SW to HSE

    // 4. Wait until HSE is used as the system clock
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSE)
    {
        // Wait until SWS (System Clock Switch Status) is set to HSE
    }

    // 5. Configure AHB, APB1, and APB2 prescalers
    RCC->CFGR &= ~RCC_CFGR_HPRE;  // Clear AHB prescaler bits (Set to /1)
    RCC->CFGR &= ~RCC_CFGR_PPRE1; // Clear APB1 prescaler bits (Set to /1)
    RCC->CFGR &= ~RCC_CFGR_PPRE2; // Clear APB2 prescaler bits (Set to /1)

    // 6. Disable the PLL (optional, as it is not used)
    RCC->CR &= ~RCC_CR_PLLON; // Ensure PLL is off

    // 7. Update the SystemCoreClock variable (optional)
    SystemCoreClock = 25000000; // HSE frequency = 25 MHz
}
