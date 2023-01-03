/*
 * lcd.c
 *
 *  Created on: 3 sty 2023
 *      Author: Dominik
 */


static uint16_t frame_buffer[LCD_WIDTH * LCD_HEIGHT];

void lcd_put_pixel(int x, int y, uint16_t color)
{
	frame_buffer[x + y * LCD_WIDTH] = color;
}
void lcd_copy(void)
{
	lcd_set_window(0, 0, LCD_WIDTH, LCD_HEIGHT);
	lcd_cmd(ST7735S_RAMWR);
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, (uint8_t*)frame_buffer, sizeof(frame_buffer), HAL_MAX_DELAY);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}

