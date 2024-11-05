/*
 * us.c
 *
 * Created: 2024-11-05 (화) 오전 10:40:15
 *  Author: FHT
 */
#include "us.h"
#include "kiosk.h"
#include <stdio.h>

// TODO: categorizing
static uint16_t us_value = 6000; // 6000 mm
static char tmp_buf[128];

// NOTE: I want to use status variables
static int us_updated = 0;
uint8_t sv_send_mode;

static int is_sensor_updated() { return us_updated; }
static int get_sensor() { return 0; }

void send_sensor_state()
{
  if (sv_send_mode == 1) {
    if (is_sensor_updated()) {
      sprintf(tmp_buf, "RM: %d", get_sensor());
      send_to_kiosk(tmp_buf);
    }
  }
}
