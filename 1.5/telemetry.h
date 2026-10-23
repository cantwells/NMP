#ifndef TELEMETRY_H
#define TELEMETRY_H

#include "flight_config.h"

void telemetry_task(void);
int telem_buff_remove(telemetry_packet_s *out);

#endif