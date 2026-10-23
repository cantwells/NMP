#include "print.h"
#include "telemetry.h"
#include <stdio.h>

void print_task(void)
{
    telemetry_packet_s packet;
    while (telem_buff_remove(&packet)) {
        printf("    print: t=%.3f\n", packet.sensor.timestamp);
    }
}