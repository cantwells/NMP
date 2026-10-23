#include "run_state.h"
#include "telemetry.h"
#include <stdio.h>

static rocket_state state = FLIGHT_ASCENT;

void run_state_task(void)
{
    telemetry_packet_s t;
    telem_get_latest(&t);

    switch (state) { //d2 switch case
    case FLIGHT_ASCENT:
        if (t.sensor.fuel == 0) {
            state = FLIGHT_COAST;
            printf("STATE: COAST\n");
        }
        break;

    case FLIGHT_COAST:
        if (t.velocity <= 0) {
            state = FLIGHT_DESCENT;
            printf("STATE: DESCENT\n");
        }
        break;

    case FLIGHT_DESCENT:
        if (t.altitude <= 0) {
            state = FLIGHT_LANDED;
            printf("STATE: LANDED\n");
        }
        break;

    case FLIGHT_LANDED:
        break;
    }
}

rocket_state get_state(void)
{
    return state;
}