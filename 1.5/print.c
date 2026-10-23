#include "print.h"
#include "telemetry.h"
#include <stdio.h>

void print_task(void) //removes from B
{
    telemetry_packet_s packet;
    while (telem_buff_remove(&packet)) {
printf("t=%.2f s  alt=%.2f m  vel=%.2f m/s  fuel=%d\n",
    packet.sensor.timestamp, packet.altitude, packet.velocity, packet.sensor.fuel);
        }
}