#include "main.h"
#include <stdio.h>

#define GRAVITY 9.81 //macro!
#define Z0 0.0
#define V0 0.0
#define FUEL 50
#define A_THRUST 15.0
#define DELTA_T 0.1
#define MAX_STEPS 300

void update_sensor_sample(sensor_sample_s *sensor) //ptr
{
    static uint32_t step = 0;

    if (sensor->fuel > 0) {//(*sensor).fuel pointer to struct
        sensor->acceleration = A_THRUST - GRAVITY;
        sensor->fuel--; //-- is -1 vv ++
    } else {
        sensor->acceleration = -GRAVITY;
    }

    step++;
    sensor->timestamp = step * DELTA_T;
}

void update_telemetry_state(const sensor_sample_s *sensor, telemetry_packet_s *telemetry)
{
    telemetry->sensor = *sensor;
    telemetry->velocity += sensor->acceleration * DELTA_T; //+= adds to existing
    telemetry->altitude += telemetry->velocity * DELTA_T;
}



static rocket_state state = FLIGHT_ASCENT; //only this file

void run_rocket_state(const telemetry_packet_s *telemetry){
    switch (state){
        case FLIGHT_ASCENT:
        if(telemetry->sensor.fuel ==0){
            state = FLIGHT_COAST;
        }
        break;

        case FLIGHT_COAST:
        if(telemetry->velocity <=0){
            state=FLIGHT_DESCENT;
        }
            break;

        case FLIGHT_DESCENT:
        if(telemetry->altitude <=0){
            state=FLIGHT_LANDED;
            break;
        }

        case FLIGHT_LANDED:
            break;

        default:
            break;
 }
}
const char *state_str(rocket_state s)
{
    switch (s) {
        case FLIGHT_ASCENT:  return "ASCENT";
        case FLIGHT_COAST:   return "COAST";
        case FLIGHT_DESCENT: return "DESCENT";
        case FLIGHT_LANDED:  return "LANDED";
        default:             return "UNKNOWN";
    }
}
int main(void){
    sensor_sample_s sensor = {0};
    telemetry_packet_s telemetry ={0};

    sensor.fuel = FUEL;
    telemetry.velocity = V0;
    telemetry.altitude = Z0;
    
    while (state != FLIGHT_LANDED) {
        update_sensor_sample(&sensor); //& = address
        update_telemetry_state(&sensor, &telemetry);
        run_rocket_state(&telemetry);
        printf("t=%.1f s  %s  alt=%.2f m  vel=%.2f m/s  fuel=%d\n", 
            telemetry.sensor.timestamp,
            state_str(state), 
            telemetry.altitude, 
            telemetry.velocity, 
            telemetry.sensor.fuel);
    }
    return 0;
}