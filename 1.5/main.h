#include <stdint.h>

#ifndef MAIN_H
#define MAIN_H

typedef struct {
    void    (*run)();
    uint32_t interval_ms;
    uint32_t last_ms;
} task_s;

void run_scheduler();

#endif