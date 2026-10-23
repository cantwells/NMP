#include "sensor.h"
#include "timer.h"
#include <stdio.h>

#define SENSOR_BUFF_SIZE 5
//throws away oldest item when full

static sensor_sample_s sensor_buff[SENSOR_BUFF_SIZE]; //ring, static so telemetry cant mess w it
static int sensor_front = 0;
static int sensor_back= 0;
static int sensor_count = 0;

static void sensor_buff_add(sensor_sample_s *sample)
{
    if (sensor_count == SENSOR_BUFF_SIZE) {
        sensor_back = (sensor_back + 1) % SENSOR_BUFF_SIZE; //wrap around
    sensor_count--;
    }

    sensor_buff[sensor_front]= *sample;
    sensor_front = (sensor_front+1)% SENSOR_BUFF_SIZE;
    sensor_count++;
}

int sensor_buff_remove(sensor_sample_s *out)
{
    if (sensor_count == 0) {
        return 0;
    }
    *out = sensor_buff[sensor_back];
    sensor_back = (sensor_back + 1) % SENSOR_BUFF_SIZE;
    sensor_count--;
    
    return 1;
}

void sensor_task(void)
{
    sensor_sample_s sample = {0};
    sample.timestamp = get_ms() / 1000.0f;
    sensor_buff_add(&sample);
    printf("sensor: pushed t=%.3f\n", sample.timestamp);
}