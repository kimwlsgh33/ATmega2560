/*
 * timer.c
 *
 * Created: 2024-11-04 (월) 오후 17:14:33
 *  Author: FHT
 */

#include "timer.h"
#include "util.h"
#include <avr/io.h>

#define TIMER_MAX_SIZE 16
#define TIMER_CNT F_CPU / 256 / 1000 // -> 1s/1000 -> 1ms
#define ERR_INVALID_ID -1
#define ERR_INVALID_FLAG -2

typedef struct _sys_timer {
  uint8_t flag;
  uint16_t value;
} sys_timer;

static sys_timer timer_list[TIMER_MAX_SIZE];

void init_timer()
{
  for (int i = 0; i < TIMER_MAX_SIZE; ++i) {
    timer_list[i].flag = 0;
    timer_list[i].value = 0;
  }

  // CS02: clk/256, WGM13: CTC
  TCCR1B |= _BV(CS12) | _BV(WGM13);
  OCR1AL = TIMER_CNT;
  TIMSK1 |= _BV(OCIE1A);
}

uint8_t alloc_timer()
{
  for (int i = 0; i < TIMER_MAX_SIZE; ++i) {
    if (timer_list[i].flag == 0) {
      timer_list[i].flag = 0x80;
      return i;
    }
  }

  return -1;
}

int get_timer(uint8_t id)
{
  if (id >= TIMER_MAX_SIZE) {
    return ERR_INVALID_ID;
  }

  if (timer_list[id].flag == 0x81)
    return timer_list[id].value ? 1 : 0;

  return ERR_INVALID_FLAG;
}

int set_timer(uint8_t id, uint16_t value)
{
  if (id >= TIMER_MAX_SIZE) {
    return ERR_INVALID_ID;
  }

  if (timer_list[id].flag == 0x80) {
    timer_list[id].flag = 0x81;
    timer_list[id].value = value;
    return SUCCESS;
  }

  return ERR_INVALID_FLAG;
}
