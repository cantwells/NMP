#ifndef FLIGHT_CONFIG_H //if not defined then define
#define FLIGHT_CONFIG_H

#include <stdint.h>

#define GRAVITY   9.81
#define Z0        0.0
#define V0        0.0
#define FUEL     50
#define A_THRUST  15.0
//not dt bc real time

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

typedef enum {
    FLIGHT_ASCENT,
    FLIGHT_COAST,
    FLIGHT_DESCENT,
    FLIGHT_LANDED
} rocket_state;

#endif