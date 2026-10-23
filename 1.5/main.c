#include <stdio.h>
#include <stdint.h>
#include "main.h"
#include "timer.h"
#include "flight_config.h"
#include "sensor.h"
#include "telemetry.h"
#include "print.h"
#include "run_state.h"

task_s tasks[] = {
    {sensor_task, 100, 0 },
    {telemetry_task, 500, 0 },
    {print_task, 500,0},
    {run_state_task, 500,0}

};

#define NUM_TASKS (sizeof(tasks) / sizeof(tasks[0]))

void run_scheduler(void)
{
    uint32_t now = get_ms();
    for (int i = 0; i < NUM_TASKS; i++) 
    {
        if (now - tasks[i].last_ms >= tasks[i].interval_ms) 
        {
            tasks[i].last_ms = now;
            tasks[i].run();
        }
    }
}

int main(void)
{
   while (get_state() != FLIGHT_LANDED)
    {
    run_scheduler();
    }
}