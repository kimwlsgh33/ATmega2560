/*
 * us.h
 *
 * Created: 2024-11-05 (화) 오전 10:44:37
 *  Author: FHT
 */
#ifndef US_H_
#define US_H_

#include <stdint.h>

void send_sensor_state();

extern uint8_t sv_send_mode; // defined in us.c

#endif /* US_H_ */
