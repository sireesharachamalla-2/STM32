/*
 * stm32f4xx.h
 * Minimal Bare-metal Header (GPIO + RCC + EXTI + NVIC)
 *
 * Author: Siree
 */

#ifndef STM32F4XX_H
#define STM32F4XX_H

#include <stdint.h>

/* ===========================================================
 * Base addresses
 * =========================================================== */
#define PERIPH_BASE           0x40000000U
#define AHB1PERIPH_BASE       (PERIPH_BASE + 0x00020000U)
#define APB1PERIPH_BASE       (PERIPH_BASE + 0x00000000U)
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000U)

/* ===========================================================
 * RCC Base
 * =========================================================== */
#define RCC_BASE              (AHB1PERIPH_BASE + 0x3800U)

/* RCC Register Map */
typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    volatile uint32_t AHB3RSTR;
    uint32_t RESERVED1;
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
    uint32_t RESERVED2[2];
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
    volatile uint32_t AHB3ENR;
    uint32_t RESERVED3;
    volatile uint32_t APB1ENR;
    volatile uint32_t APB2ENR;
} RCC_TypeDef;

#define RCC   ((RCC_TypeDef *) RCC_BASE)

/* Clock enable bits */
#define RCC_AHB1ENR_GPIOAEN    (1U << 0)
#define RCC_AHB1ENR_GPIOBEN    (1U << 1)
#define RCC_AHB1ENR_GPIOCEN    (1U << 2)
#define RCC_AHB1ENR_GPIODEN    (1U << 3)
#define RCC_AHB1ENR_GPIOEEN    (1U << 4)

/* ===========================================================
 * GPIO Base Addresses
 * =========================================================== */
#define GPIOA_BASE            (AHB1PERIPH_BASE + 0x0000U)
#define GPIOB_BASE            (AHB1PERIPH_BASE + 0x0400U)
#define GPIOC_BASE            (AHB1PERIPH_BASE + 0x0800U)
#define GPIOD_BASE            (AHB1PERIPH_BASE + 0x0C00U)
#define GPIOE_BASE            (AHB1PERIPH_BASE + 0x1000U)

typedef struct
{
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFRL;
    volatile uint32_t AFRH;
} GPIO_TypeDef;

#define GPIOA   ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB   ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC   ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD   ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE   ((GPIO_TypeDef *) GPIOE_BASE)

/* ===========================================================
 * SYSCFG (needed for EXTI)
 * Base: 0x40013800
 * =========================================================== */
#define SYSCFG_BASE           (APB2PERIPH_BASE + 0x3800U)

typedef struct
{
    volatile uint32_t MEMRMP;
    volatile uint32_t PMC;
    volatile uint32_t EXTICR[4];  // EXTICR1..4
} SYSCFG_TypeDef;

#define SYSCFG               ((SYSCFG_TypeDef *) SYSCFG_BASE)
#define SYSCFG_CLK_ENABLE()  (RCC->APB2ENR |= (1 << 14))

/* ===========================================================
 * EXTI Base
 * =========================================================== */
#define EXTI_BASE             (APB2PERIPH_BASE + 0x3C00U)

typedef struct
{
    volatile uint32_t IMR;
    volatile uint32_t EMR;
    volatile uint32_t RTSR;
    volatile uint32_t FTSR;
    volatile uint32_t SWIER;
    volatile uint32_t PR;
} EXTI_TypeDef;

#define EXTI   ((EXTI_TypeDef *) EXTI_BASE)

/* ===========================================================
 * NVIC Registers (Cortex-M4)
 * =========================================================== */
#define NVIC_ISER0           (*(volatile uint32_t *)0xE000E100U)
#define NVIC_ISER1           (*(volatile uint32_t *)0xE000E104U)
#define NVIC_ICPR0           (*(volatile uint32_t *)0xE000E280U)

/* NVIC IRQ numbers (important ones) */
#define EXTI0_IRQn           6
#define EXTI1_IRQn           7
#define EXTI2_IRQn           8
#define EXTI3_IRQn           9
#define EXTI4_IRQn           10
#define EXTI9_5_IRQn         23
#define EXTI15_10_IRQn       40

/* Macro to enable IRQ */
#define NVIC_EnableIRQ(IRQn)    ( NVIC_ISER0 |= (1 << ((uint32_t)(IRQn) & 0x1F)) )

#endif /* STM32F4XX_H */
