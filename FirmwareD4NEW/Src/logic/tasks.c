#include "tasks.h"
#include "ring_buffer.h"
#include "../drivers/adxl343.h"
#include <math.h>
#include <stdio.h>

extern I2C_HandleTypeDef hi2c1; //connect them
static ring_buffer_s buffer1 = {0};
static ring_buffer_s buffer2 = {0}; //check samples, 2 to 3

void sample_task(void)
{
    static GPIO_PinState last_button = GPIO_PIN_SET; //released
    static int sensor_enabled = 0; //starting
    GPIO_PinState button = HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin); //read button PA0

    if(last_button == GPIO_PIN_SET && button == GPIO_PIN_RESET) //released then pressed?
    {
        sensor_enabled = !sensor_enabled; //every press flips 
        if(sensor_enabled)
        {
            adxl343_enable(&hi2c1);  //pwr ctrl 0x08 Measure
        } 
        else
        {
            adxl343_disable(&hi2c1); //pwr ctrl 0x00 standby
        }
    }

    last_button = button; //remember for next time

    if(sensor_enabled)
    {
        adxl343_accel_s sample; //so can have somwhere to put sample for now
        if(adxl343_read(&hi2c1, &sample) == HAL_OK)
        {
            rb_push(&buffer1, &sample);
        }
    }
}

void check_task(void)
{
    adxl343_accel_s sample;
    while(rb_pop(&buffer1, &sample))
    {
        //mag = sqrt(x2 + y2 + z2)
        float mag = sqrtf(sample.x * sample.x + 
            sample.y * sample.y +
            sample.z * sample.z);
        if(mag > ACCEL_THRESHOLD_G)
        {
            HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET); //on PC13 low
        }
        else
        {
            HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET); //off PC13
        }

    }

    rb_push(&buffer2, &sample); //to buffer2 yay
}

void print_task(void)
{
    adxl343_accel_s sample;
    while (rb_pop(&buffer2, &sample)) //while rb_pop = 1
    {
        printf("X: %.3f Y: %.3f Z: %.3f g\r\n", sample.x, sample.y, sample.z);

    }
}