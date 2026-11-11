#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>
#include "../drivers/adxl343.h"

#define RB_SIZE 32

typedef struct{
    adxl343_accel_s data [RB_SIZE];
    uint16_t head;
    uint16_t tail;
    uint16_t count;
} ring_buffer_s;


void rb_push(ring_buffer_s*rb, const adxl343_accel_s*sample);
int rb_pop(ring_buffer_s *rb, adxl343_accel_s*out);

#endif