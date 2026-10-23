#ifndef SENSOR_H          
#define SENSOR_H        

#include "flight_config.h"

void sensor_task(void);                     
int sensor_buff_remove(sensor_sample_s *out);

#endif