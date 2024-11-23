#ifndef CLOCK_H
#define CLOCK_H

#include "stm32f4xx.h"

/**
 * @brief Initializes the system clock to use HSE as the clock source without PLL.
 */
void clock_init(void);

#endif // CLOCK_H
