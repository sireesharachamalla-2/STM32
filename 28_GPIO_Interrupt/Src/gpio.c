#include "stm32f4xx.h"

void GPIO_Init_PA5_Output(void)
{
    // Enable GPIOA clock
    RCC->AHB1ENR |= (1 << 0);

    // Set PA5 as output
    GPIOA->MODER &= ~(3 << (5 * 2));
    GPIOA->MODER |=  (1 << (5 * 2));
}

void GPIO_Init_PC13_Interrupt(void)
{
    // Enable GPIOC and SYSCFG clock
    RCC->AHB1ENR |= (1 << 2);      // GPIOC
    RCC->APB2ENR |= (1 << 14);     // SYSCFG

    // Set PC13 as input
    GPIOC->MODER &= ~(3 << (13 * 2));

    // Select PC13 as EXTI13 source
    SYSCFG->EXTICR[3] &= ~(0xF << 4);   // Clear EXTI13 bits
    SYSCFG->EXTICR[3] |=  (0x2 << 4);   // 0x2 = GPIOC

    // Configure EXTI
    EXTI->IMR  |= (1 << 13);  // Unmask line13
    EXTI->FTSR |= (1 << 13);  // Trigger on falling edge (button press)
    EXTI->RTSR &= ~(1 << 13);

    // Enable NVIC interrupt
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}

// Interrupt handler
void EXTI15_10_IRQHandler(void)
{
    if(EXTI->PR & (1 << 13))
    {
        EXTI->PR |= (1 << 13);  // Clear interrupt flag
        GPIOA->ODR ^= (1 << 5); // Toggle LED
    }
}
