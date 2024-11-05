/*
 * periphs.c
 *
 * Created: 2024-11-05 (화) 오전 09:20:53
 *  Author: FHT
 */
#include "periphs.h"
#include "kiosk.h"
#include "timer.h"
#include "util.h"
#include <stdio.h>
#include <string.h>

#define P_ST_UNKNOWN 'U'
#define P_ST_INIT 'I'
#define P_ST_READY 'R'
#define P_ST_RUNNING 'r'
#define P_ST_STOPPED 'S'

PState pstate;
static char tmp_buf[128];

static uint8_t tid_op = 0;

int init_periphs(void)
{
  memset(&pstate, 0, sizeof(pstate));
  pstate.state = P_ST_UNKNOWN;

  // init_rc();
  // init_us();
  // init_gd();
  // init_ma();

  tid_op = alloc_timer();
  set_timer(tid_op, 1000);
  return SUCCESS;
}

static PState get_periphs_state() { return pstate; }

void send_periphs_state()
{
  PState ps = get_periphs_state();
  sprintf(tmp_buf, "ST=%c,%d,%c,%d,%d,%d,%d,%d,%d,%d", ps.state, ps.rstate,
          ps.door, ps.monitorPosition, ps.plasticCups, ps.paperCups,
          ps.purifiedTankLevel, ps.wasteTankLevel, ps.errorCode,
          ps.errorRoboSeq);
  send_to_kiosk(tmp_buf);
}
