#pragma once

#include "stm32f1xx.h"

void eepromWait(void);
HAL_StatusTypeDef eepromRead(uint32_t addr, void *data, uint32_t size);
HAL_StatusTypeDef eepromWrite(uint32_t addr, const void * data, uint32_t size);
