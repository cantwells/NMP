#include "ring_buffer.h"

void rb_push(ring_buffer_s*rb, const adxl343_accel_s*sample){
    if(rb->count == RB_SIZE)
    {
        rb->tail = (rb->tail + 1) % RB_SIZE;
        rb->count--;
    //prrintf("[data] full, dropped oldest");
    }

    rb->data[rb->head] = *sample;
    rb->head = (rb->head+1) % RB_SIZE;
    rb->count++;
}

int rb_pop(ring_buffer_s *rb, adxl343_accel_s*out)
{
    if(rb->count ==0)
    {
        return 0;
    }

    *out = rb->data[rb->tail];
    rb->tail = (rb->tail + 1) % RB_SIZE;
    rb->count--;
    return 1;
}
