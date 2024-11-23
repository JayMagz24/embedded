#include "main.h"

int main(void)
{
    clock_init();   // Initialize clock
    gpio_init();    // Initialize GPIO
    delay_init();   // Initialize delays

    while (1)
    {
        // Check if PA0 is pressed (low state)
        if ((GPIOA->IDR & GPIO_IDR_ID0_Msk) == RESET)
        {
            // Turn off PC13 (reset pin)
            GPIOC->BSRR |= GPIO_BSRR_BR13;
        }
        else
        {
            // Turn on PC13 (set pin)
            GPIOC->BSRR |= GPIO_BSRR_BS13;
        }
    }
}
