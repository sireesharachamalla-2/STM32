/*
 * gpio.h
 *
 *  Created on: Nov 6, 2025
 *      Author: siree
 */

#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include "stm32f4xx.h"     // This provides RCC, GPIO, SYSCFG, EXTI register structs

void GPIO_Init_PA0_Interrupt(void);
void GPIO_Init_PA5_Output(void);

#endif


