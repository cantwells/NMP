#include "telemetry.h"
#include "sensor.h"
#include <stdio.h>

#define TELEM_BUFF_SIZE 8
//rejects new item when full

static telemetry_packet_s telem_buff[TELEM_BUFF_SIZE];
static int telem_head = 0;
static int telem_tail = 0;
static int telem_count = 0;

static int telem_buff_add(const telemetry_packet_s *packet)
{
    if (telem_count == TELEM_BUFF_SIZE) {
        return 0;
    }

    telem_buff[telem_head] = *packet;
    telem_head = (telem_head + 1) % TELEM_BUFF_SIZE;
    telem_count++;
    return 1; //so can print instead of A w zero that doesnt print
}

int telem_buff_remove(telemetry_packet_s *out)
{
    if (telem_count == 0) {
        return 0;
    }
    *out = telem_buff[telem_tail];
    telem_tail = (telem_tail + 1) % TELEM_BUFF_SIZE;
    telem_count--;
    return 1;
}

static telemetry_packet_s latest = {0};

void telemetry_task(void)
{
    static double velocity = V0;
    static double altitude = Z0;
    static float last_t = 0.0f;
    sensor_sample_s sample;
    telemetry_packet_s packet;

    while (sensor_buff_remove(&sample)) 
    {
        double dt = sample.timestamp - last_t;
        last_t = sample.timestamp;

        velocity += sample.acceleration * dt; //physics equations from d2
        altitude += velocity * dt;

        packet.sensor = sample; //d2
        packet.velocity = velocity;
        packet.altitude = altitude;
        latest = packet;

        if (!telem_buff_add(&packet)) { //saftey print statement
            printf("  telemetry: REJECTED t=%.3f\n", sample.timestamp);
        }
    }

    //printf("[telemetry] t=%.1f alt=%.2f vel=%.2f\n", sample.timestamp, altitude, velocity);

}

void telem_get_latest(telemetry_packet_s *out)
{
    *out = latest;
}