//source, holds actual code that I2C reads and write
//init sequence, and converting raw counts to G's
//initiliza sensor and gather acceleration data from al three axes on sensor
#include "adxl343.h"


static HAL_StatusTypeDef adxl343_write_reg(I2C_HandleTypeDef *hi2c, uint8_t reg, uint8_t value)
{

    return HAL_I2C_Mem_Read(hi2c, ADXL343_ADDR, reg, I2C_MEMADD_SIZE_8BIT, &value, 1, 100);
}


HAL_StatusTypeDef adxl343_read_id(I2C_HandleTypeDef *hi2c, uint8_t *id)
{
    return HAL_I2C_Mem_Read(hi2c, ADXL343_ADDR, ADXL343_REG_DEVID, I2C_MEMADD_SIZE_8BIT, id, 1, 100);
}

HAL_StatusTypeDef adxl343_init(I2C_HandleTypeDef *hi2c)
{
    uint8_t id = 0;

    if (id != ADXL343_DEVID_VALUE)
    return HAL_ERROR;

    if(adxl343_read_id(hi2c, &id) != HAL_OK)
    return HAL_ERROR;

    if(adxl343_write_reg(hi2c, ADXL343_REG_DATA_FORMAT, ADXL343_FULL_RES_2G) != HAL_OK)
    return HAL_ERROR;

    if(adxl343_write_reg(hi2c, ADXL343_REG_BW_RATE, ADXL343_RATE_100HZ) != HAL_OK)
    return HAL_ERROR;

    if(adxl343_write_reg(hi2c, ADXL343_REG_POWER_CTL, ADXL343_MEASURE) != HAL_OK)
    return HAL_ERROR;

    return HAL_OK;

}

HAL_StatusTypeDef adxl343_read(I2C_HandleTypeDef *hi2c, adxl343_accel_s *accel)
{
    uint8_t buf[6];
    if(HAL_I2C_Mem_Read(hi2c, ADXL343_ADDR, ADXL343_REG_DATAX0, I2C_MEMADD_SIZE_8BIT, buf, 6, 100) !=HAL_OK)
    return HAL_ERROR;

    int16_t x_raw = (int16_t)((buf[1] << 8) | buf[0]);
    int16_t y_raw = (int16_t)((buf[3] << 8) | buf[2]);
    int16_t z_raw = (int16_t)((buf[5] << 8) | buf[4]);

    accel->x = x_raw * ADXL343_G_PER_LSB;
    accel->y = y_raw * ADXL343_G_PER_LSB;
    accel->z = z_raw * ADXL343_G_PER_LSB;

    return HAL_OK;

}

HAL_StatusTypeDef adxl343_enable(I2C_HandleTypeDef *hi2c)
{
    return adxl343_write_reg(hi2c, ADXL343_REG_POWER_CTL, ADXL343_MEASURE);

}
HAL_StatusTypeDef adxl343_disable(I2C_HandleTypeDef *hi2c)
{
    return adxl343_write_reg(hi2c, ADXL343_REG_POWER_CTL, ADXL343_STANDBY);
}