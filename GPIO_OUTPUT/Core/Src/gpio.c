#include "gpio.h"

// Function to initialize GPIO
void gpio_init(void)
{
    // Enable the GPIOA, GPIOB and GPIOC clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN;

    /*--------------------------Configure PA0 as input mode------------------------------*/
    GPIOA->MODER &= ~GPIO_MODER_MODER0_Msk;          // Clear mode bits for PA0 (00: Input mode)
    GPIOA->OTYPER &= ~GPIO_OTYPER_OT0;               // Ensure PA0 is not push-pull (default for input)
    GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED0_Msk;     // Set low speed for PA0 (optional for input)
    GPIOA->PUPDR |= GPIO_PUPDR_PUPD0_0;              // Enable pull-up on PA0

    /*--------------------------Configure PB0 as output mode-----------------------------*/
    GPIOB->MODER &= ~GPIO_MODER_MODER0_Msk;          // Clear mode bits for PB0
    GPIOB->MODER |= GPIO_MODER_MODER0_0;             // Set as output mode (01)
    GPIOB->OTYPER &= ~GPIO_OTYPER_OT0;               // Set to push-pull for PB0 (default)
    GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED0_Msk;     // Set low speed for PB0 (optional)
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD0_Msk;           // No pull-up, pull-down for PB0 (optional)

    /*--------------------------Configure PB1 as output mode-----------------------------*/
    GPIOB->MODER &= ~GPIO_MODER_MODER1_Msk;          // Clear mode bits for PB1
    GPIOB->MODER |= GPIO_MODER_MODER1_0;             // Set as output mode (01)
    GPIOB->OTYPER &= ~GPIO_OTYPER_OT1;               // Set to push-pull for PB1 (default)
    GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED1_Msk;     // Set low speed for PB1 (optional)
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD1_Msk;           // No pull-up, pull-down for PB1 (optional)

    /*--------------------------Configure PB2 as output mode-----------------------------*/
    GPIOB->MODER &= ~GPIO_MODER_MODER2_Msk;          // Clear mode bits for PB2
    GPIOB->MODER |= GPIO_MODER_MODER2_0;             // Set as output mode (01)
    GPIOB->OTYPER &= ~GPIO_OTYPER_OT2;               // Set to push-pull for PB2 (default)
    GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED2_Msk;     // Set low speed for PB2 (optional)
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD2_Msk;           // No pull-up, pull-down for PB2 (optional)

    /*--------------------------Configure PB3 as output mode-----------------------------*/
    GPIOB->MODER &= ~GPIO_MODER_MODER3_Msk;          // Clear mode bits for PB3
    GPIOB->MODER |= GPIO_MODER_MODER3_0;             // Set as output mode (01)
    GPIOB->OTYPER &= ~GPIO_OTYPER_OT3;               // Set to push-pull for PB3 (default)
    GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED3_Msk;     // Set low speed for PB3 (optional)
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD3_Msk;           // No pull-up, pull-down for PB3 (optional)

    /*--------------------------Configure PB4 as output mode-----------------------------*/
    GPIOB->MODER &= ~GPIO_MODER_MODER4_Msk;          // Clear mode bits for PB4
    GPIOB->MODER |= GPIO_MODER_MODER4_0;             // Set as output mode (01)
    GPIOB->OTYPER &= ~GPIO_OTYPER_OT4;               // Set to push-pull for PB4 (default)
    GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED4_Msk;     // Set low speed for PB4 (optional)
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD4_Msk;           // No pull-up, pull-down for PB4 (optional)

    /*--------------------------Configure PB5 as output mode-----------------------------*/
    GPIOB->MODER &= ~GPIO_MODER_MODER5_Msk;          // Clear mode bits for PB5
    GPIOB->MODER |= GPIO_MODER_MODER5_0;             // Set as output mode (01)
    GPIOB->OTYPER &= ~GPIO_OTYPER_OT5;               // Set to push-pull for PB5 (default)
    GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED5_Msk;     // Set low speed for PB5 (optional)
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD5_Msk;           // No pull-up, pull-down for PB5 (optional)

    /*--------------------------Configure PB6 as output mode-----------------------------*/
    GPIOB->MODER &= ~GPIO_MODER_MODER6_Msk;          // Clear mode bits for PB6
    GPIOB->MODER |= GPIO_MODER_MODER6_0;             // Set as output mode (01)
    GPIOB->OTYPER &= ~GPIO_OTYPER_OT6;               // Set to push-pull for PB6 (default)
    GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED6_Msk;     // Set low speed for PB6 (optional)
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD6_Msk;           // No pull-up, pull-down for PB6 (optional)

    /*--------------------------Configure PB7 as output mode-----------------------------*/
    GPIOB->MODER &= ~GPIO_MODER_MODER7_Msk;          // Clear mode bits for PB7
    GPIOB->MODER |= GPIO_MODER_MODER7_0;             // Set as output mode (01)
    GPIOB->OTYPER &= ~GPIO_OTYPER_OT7;               // Set to push-pull for PB7 (default)
    GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED7_Msk;     // Set low speed for PB7 (optional)
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD7_Msk;           // No pull-up, pull-down for PB7 (optional)

    /*--------------------------Configure PC13 as output mode-----------------------------*/
    GPIOC->MODER &= ~GPIO_MODER_MODER13;            // Clear mode bits for PC13
    GPIOC->MODER |= GPIO_MODER_MODER13_0;           // Set as output mode (01)
    GPIOC->OTYPER &= ~GPIO_OTYPER_OT13;             // Set to push-pull for PC13 (default)
    GPIOC->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED13;       // Set low speed for PC13 (optional)
    GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD13;             // No pull-up, pull-down for PC13 (optional)

}
