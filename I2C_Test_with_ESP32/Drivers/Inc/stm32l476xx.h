#ifndef STM32L476XX_H
#define STM32L476XX_H
#include <stdint.h>

/* ---------------- Base Addresses ---------------- */
#define PERIPH_BASE        0x40000000UL
#define AHB2PERIPH_BASE    0x48000000UL
#define APB1PERIPH_BASE    PERIPH_BASE

#define GPIOB_BASE         (AHB2PERIPH_BASE + 0x0400)
#define RCC_BASE           (0x40021000UL)
#define I2C1_BASE          (APB1PERIPH_BASE + 0x5400)
#define NVIC_ISER0         ((volatile uint32_t*)0xE000E100UL)

/* ---------------- Peripheral Structs ---------------- */
typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
    volatile uint32_t BRR;
} GPIO_TypeDef;

typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t OAR1;
    volatile uint32_t OAR2;
    volatile uint32_t TIMINGR;
    volatile uint32_t TIMEOUTR;
    volatile uint32_t ISR;
    volatile uint32_t ICR;
    volatile uint32_t PECR;
    volatile uint32_t RXDR;
    volatile uint32_t TXDR;
} I2C_TypeDef;

typedef struct {
    volatile uint32_t CR;
    volatile uint32_t ICSCR;
    volatile uint32_t CFGR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t PLLSAI1CFGR;
    volatile uint32_t CIER;
    volatile uint32_t CIFR;
    volatile uint32_t CICR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    volatile uint32_t AHB3RSTR;
    volatile uint32_t APB1RSTR1;
    volatile uint32_t APB1RSTR2;
    volatile uint32_t APB2RSTR;
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
    volatile uint32_t AHB3ENR;
    volatile uint32_t APB1ENR1;
    volatile uint32_t APB1ENR2;
    volatile uint32_t APB2ENR;
} RCC_TypeDef;

/* ---------------- Pointer Definitions ---------------- */
#define GPIOB     ((GPIO_TypeDef*)GPIOB_BASE)
#define RCC       ((RCC_TypeDef*)RCC_BASE)
#define I2C1      ((I2C_TypeDef*)I2C1_BASE)

/* ---------------- RCC Bits ---------------- */
#define RCC_AHB2ENR_GPIOBEN    (1 << 1)
#define RCC_APB1ENR1_I2C1EN    (1 << 21)

/* ---------------- I2C Bits ---------------- */
#define I2C_CR1_PE             (1 << 0)
#define I2C_CR1_TXIE           (1 << 1)
#define I2C_CR1_RXIE           (1 << 2)
#define I2C_CR1_STOPIE         (1 << 5)
#define I2C_CR1_TCIE           (1 << 6)

#define I2C_CR2_START          (1 << 13)
#define I2C_CR2_RD_WRN         (1 << 10)

#define I2C_ISR_TXIS           (1 << 1)
#define I2C_ISR_RXNE           (1 << 2)
#define I2C_ISR_TC             (1 << 6)
#define I2C_ISR_STOPF          (1 << 5)

#define I2C_ICR_STOPCF         (1 << 5)

/* ------------- NVIC IRQ Enable ------------- */
static inline void NVIC_EnableIRQ(int IRQn)
{
    NVIC_ISER0[0] = (1 << IRQn);
}

#define I2C1_EV_IRQn 31

#endif
