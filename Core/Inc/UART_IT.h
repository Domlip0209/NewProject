#pragma once

#include "stm32f1xx.h"
#include "WS2812B.h"

//this function can be used to turn on / off the lights in a room
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
