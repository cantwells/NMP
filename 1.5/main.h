#include <stdint.h>

typedef struct {
    void    (*run)();
    uint32_t interval_ms;
    uint32_t last_ms;
} task_s;

void run_scheduler();