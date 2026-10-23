#include "telemetry.h"
#include "sensor.h"
#include <stdio.h>

#define TELEM_BUFF_SIZE 5
//rejects new item when full

static telemetry_packet_s telem_buff[TELEM_BUFF_SIZE];
static int telem_front = 0;
static int telem_back = 0;
static int telem_count = 0;

static int telem_buff_add(const telemetry_packet_s *packet)
{
    if (telem_count == TELEM_BUFF_SIZE) {
        return 0;
    }

    telem_buff[telem_front] = *packet;
    telem_front = (telem_front + 1) % TELEM_BUFF_SIZE;
    telem_count++;
    return 1;
}

int telem_buff_remove(telemetry_packet_s *out)
{
    if (telem_count == 0) {
        return 0;
    }
    *out = telem_buff[telem_back];
    telem_back = (telem_back + 1) % TELEM_BUFF_SIZE;
    telem_count--;
    return 1;
}

void telemetry_task(void)
{
    sensor_sample_s sample;
    telemetry_packet_s packet = {0};

    while (sensor_buff_remove(&sample)) {
        packet.sensor = sample;

        if (telem_buff_add(&packet)) {
            printf("  telemetry: added t=%.3f\n", sample.timestamp);
        } else {
            printf("  telemetry: REJECTED t=%.3f (buffer full)\n", sample.timestamp);
        }
    }
}