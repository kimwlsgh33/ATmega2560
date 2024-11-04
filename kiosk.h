/*
 * kiosk.h
 *
 * Created: 2024-11-01 (금) 오후 13:15:48
 *  Author: FHT
 */

#ifndef KIOSK_H_
#define KIOSK_H_

#include "Console.h"
#include "uart1.h"
#include <stdio.h>
#include <string.h>

#define init_kiosk init_uart1

void proc_kiosk();
int get_packet_from_kiosk(char *buf);
int proc_command_on_kiosk(char *cmd, uint8_t len);
static int send_to_kiosk(char *buf);

#endif /* KIOSK_H_ */
