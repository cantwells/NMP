#include <stdio.h>
#include <stdint.h>
#include "main.h"
#include "timer.h"
#include "flight_config.h"
#include "sensor.h"
#include "telemetry.h"

task_s tasks[] = {
    { sensor_task,    100, 0 },
    { telemetry_task, 1000, 0 },
};

#define NUM_TASKS (sizeof(tasks) / sizeof(tasks[0]))

void run_scheduler(void)
{
    uint32_t now = get_ms();
    for (int i = 0; i < NUM_TASKS; i++) {
        if (now - tasks[i].last_ms >= tasks[i].interval_ms) {
            tasks[i].last_ms = now;
            tasks[i].run();
        }
    }
}

int main(void)
{
    while (1) {
        run_scheduler();
    }
}