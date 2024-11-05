/*
 * timer.h
 *
 * Created: 2024-11-04 (월) 오후 17:13:18
 *  Author: FHT
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

#define timer_isfired(x) ((get_timer(x) == 0))

void init_timer();
uint8_t alloc_timer();
int get_timer(uint8_t id);
int set_timer(uint8_t id, uint16_t value);

#endif /* TIMER_H_ */
