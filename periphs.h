/*
 * pariphs.h
 *
 * Created: 2024-11-05 (화) 오전 09:18:23
 *  Author: FHT
 */

#ifndef PERIPHS_H_
#define PERIPHS_H_

#include <stdint.h>

typedef struct _pstate {
  char state;
  uint8_t rstate;
  char door;
  uint8_t monitorPosition;
  uint8_t plasticCups;
  uint8_t paperCups;
  uint8_t purifiedTankLevel;
  uint8_t wasteTankLevel;
  uint8_t errorCode;
  uint8_t errorRoboSeq;
} PState;

int init_periphs(void);
void send_periphs_state();

#endif /* PERIPHS_H_ */
