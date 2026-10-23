#include <stdint.h>
#include <time.h>
#include "timer.h"

uint32_t get_ms(void)
{
return (uint32_t)(
(double)clock() * 1000.0 / CLOCKS_PER_SEC
);
}