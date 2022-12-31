#include "UART_IT.h"

#define LINE_MAX_LENGTH 80

static char line_buffer[LINE_MAX_LENGTH + 1];
static uint32_t line_length;
static uint8_t r = gamma8[rand() % 256];
static uint8_t g = gamma8[rand() % 256];
static uint8_t b = gamma8[rand() % 256];
 
void line_append(uint8_t value)
{
  if (value == '\r' || value == '\n') {
  
    if (line_length > 0) {
 
      line_buffer[line_length] = '\0';
  
      if (strcmp(line_buffer, "on") == 0) {
       
  		for (int led = 0; led < 6; led++) {
   			ws2812b_set_color(led, r, g, b);
   			ws2812b_update();}
      } else if (strcmp(line_buffer, "off") == 0) {
        ws2812b_init();
      }
 
      line_length = 0;
    }
  }
  else {
    if (line_length >= LINE_MAX_LENGTH) {
      line_length = 0;
    }
    line_buffer[line_length++] = value;
  }
}

static uint8_t uart_rx_buffer;
 // my usart is build in my microcontroler and using "huart2"
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart == &huart2) {
    line_append(uart_rx_buffer);
    HAL_UART_Receive_IT(&huart2, &uart_rx_buffer, 1);
  }
}
