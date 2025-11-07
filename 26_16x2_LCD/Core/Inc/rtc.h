/*
 * rtc.h
 *
 *  Created on: Nov 6, 2025
 *      Author: siree
 */


#ifndef __RTC_H
#define __RTC_H

#include "stm32l476xx.h"
#include <stdint.h>

void RTC_Init(void);
void RTC_GetTime12(uint8_t *hours, uint8_t *minutes, uint8_t *seconds, char *am_pm);
void RTC_GetDate(uint8_t *date, uint8_t *month, uint8_t *year);

#endif
