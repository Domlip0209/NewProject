#include "UART_IT.h"

 #define LINE_MAX_LENGTH 80

static char line_buffer[LINE_MAX_LENGTH + 1];
static uint32_t line_length;
 
void line_append(uint8_t value)
{
  if (value == '\r' || value == '\n') {
    // odebraliśmy znak końca linii
    if (line_length > 0) {
      // dodajemy 0 na końcu linii
      line_buffer[line_length] = '\0';
      // przetwarzamy dane
      if (strcmp(line_buffer, "on") == 0) {
        HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
      } else if (strcmp(line_buffer, "off") == 0) {
        HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
      }
 
      // zaczynamy zbieranie danych od nowa
      line_length = 0;
    }
  }
  else {
    if (line_length >= LINE_MAX_LENGTH) {
      // za dużo danych, usuwamy wszystko co odebraliśmy dotychczas
      line_length = 0;
    }
    // dopisujemy wartość do bufora
    line_buffer[line_length++] = value;
  }
}

static uint8_t uart_rx_buffer;
 
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart == &huart2) {
    line_append(uart_rx_buffer);
    HAL_UART_Receive_IT(&huart2, &uart_rx_buffer, 1);
  }
}
