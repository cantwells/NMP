#include "sensor.h"
#include "timer.h"
#include <stdio.h>

#define SENSOR_BUFF_SIZE 8
//throws away oldest item when full

static sensor_sample_s sensor_buff[SENSOR_BUFF_SIZE]; //ring, static so telemetry cant mess w it
static int sensor_head = 0;
static int sensor_tail= 0;
static int sensor_count = 0;

static void sensor_buff_add(sensor_sample_s *sample)
{
    if (sensor_count == SENSOR_BUFF_SIZE) {
        sensor_tail = (sensor_tail + 1) % SENSOR_BUFF_SIZE; //wrap around
    sensor_count--;
        //printf("[bufA] full, dropped oldest\n");
    }

    sensor_buff[sensor_head]= *sample;
    sensor_head = (sensor_head+1)% SENSOR_BUFF_SIZE;
    sensor_count++;

}

int sensor_buff_remove(sensor_sample_s *out)
{
    if (sensor_count == 0) {
        return 0;
    }
    *out = sensor_buff[sensor_tail];
    sensor_tail = (sensor_tail + 1) % SENSOR_BUFF_SIZE;
    sensor_count--;
    return 1;
}

void sensor_task(void)
{
    static uint16_t fuel = FUEL;
    sensor_sample_s sample;

    if (fuel > 0) {
        sample.acceleration = A_THRUST - GRAVITY;
        fuel--;
    } else {
        sample.acceleration = -GRAVITY;
    }

    sample.fuel = fuel;
    sample.timestamp = get_ms()/1000.0f; //milli to secs
    sensor_buff_add(&sample);
        
    printf("sensor: t=%.3f a=%.2f fuel=%d\n", sample.timestamp, sample.acceleration, sample.fuel);

}