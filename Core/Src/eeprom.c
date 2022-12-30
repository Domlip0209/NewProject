#include "eeprom.h"
#include "i2c.h"

#define eepromAddr		0xA0
#define writeTimeout	6

static uint32_t last_write;
 
void eepromWait(void)
{
    while (HAL_GetTick() - last_write <= WRITE_TIMEOUT){}
}
 
HAL_StatusTypeDef eepromRead(uint32_t addr, void* data, uint32_t size)
{
    eepromWait();
    return HAL_I2C_Mem_Read(&hi2c1, EEPROM_ADDR, addr, 1, data, size, HAL_MAX_DELAY);
}
 
HAL_StatusTypeDef eepromWrite(uint32_t addr, const void* data, uint32_t size)
{
    HAL_StatusTypeDef rc;
 
    eepromWait();
    rc = HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDR, addr, 1, (void*)data, size, HAL_MAX_DELAY);
    last_write = HAL_GetTick();
 
    return rc;
}
