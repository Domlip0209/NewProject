#include "lsm303d.h"
 
#define LSM303D_ADDR			0x3a
#define LSM303D_TEMP_OUT_L 		0x05
#define LSM303D_TEMP_OUT_H 		0x06

#define TIMEOUT                 100
 
 

void lsm_write_reg(uint8_t reg, uint8_t value)
{
	HAL_I2C_Mem_Write(&hi2c1, LSM303D_ADDR, reg, 1, &value, sizeof(value), TIMEOUT);
}
 
static uint8_t lsm_read_reg(uint8_t reg)
{
	uint8_t value = 0;
 
	HAL_I2C_Mem_Read(&hi2c1, LSM303D_ADDR, reg, 1, &value, sizeof(value), TIMEOUT);
 
	return value;
}
 
float lsm_read_value(uint8_t reg)
{
	float value = 0;
 
	if (HAL_I2C_Mem_Read(&hi2c1, LSM303D_ADDR, LSM303D_TEMP_OUT_L | 0x80, 1, (uint8_t*)&temp, sizeof(temp), TIMEOUT) != HAL_OK)
         Error_Handler();
 
	return 42.5f + temp / 480.0f;
}
