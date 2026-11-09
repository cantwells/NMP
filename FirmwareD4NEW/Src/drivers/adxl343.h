//driver's public interface
//registar address, data structs, and function prototype
//other files #include it
#ifndef ADXL343_H
#define ADXL_343_H

#include "main.h"
#define ADXL343_ADDR              0xA6 //0x53 << 1 shifted by one bit
#define ADXL343_REG_DEVID         0x00 //registar number asking for
#define ADXL343_DEVID_VALUE       0xE5 //answer
#define ADXL343_FULL_RES_2G       0x08   // data format full res
#define ADXL343_RATE_100HZ        0x0A   // 100 Hz output rate
#define ADXL343_MEASURE           0x08   // measurement mode
#define ADXL343_STANDBY           0x00   // standby mode
#define ADXL343_REG_BW_RATE       0x2C
#define ADXL343_REG_POWER_CTL     0x2D
#define ADXL343_REG_DATA_FORMAT   0x31
#define ADXL343_REG_DATAX0        0x32      // first of the 6 data registers
#define ADXL343_G_PER_LSB         0.0039f   // 3.9 mg per count

typedef struct {
double acceleration;
uint16_t fuel;
float timestamp;
} sensor_sample_s;
typedef struct {
sensor_sample_s sensor;
double velocity;
double altitude;
} telemetry_packet_s;
typedef struct {
    float x;   // in g
    float y;
    float z;
} adxl343_accel_s;


HAL_StatusTypeDef adxl343_read_id(I2C_HandleTypeDef *hi2c, uint8_t *id); //prototype
HAL_StatusTypeDef adxl343_init(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef adxl343_read(I2C_HandleTypeDef *hi2c, adxl343_accel_s*accel);



#endif
