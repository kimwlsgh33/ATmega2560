/*
 * kiosk.h
 *
 * Created: 2024-11-01 (금) 오후 13:15:48
 *  Author: FHT
 */

#ifndef KIOSK_H_
#define KIOSK_H_

#include <stdint.h>

#define init_kiosk init_uart1
// indicate that the kiosk is connected to the uart1
#define KIOSK_GETCHAR uart1_getchar
#define KIOSK_PUTCHAR uart1_putchar

void proc_kiosk();
static int get_packet_from_kiosk(char *buf);
static int proc_command_on_kiosk(char *cmd, uint8_t len);
int send_to_kiosk(char *buf);

#endif /* KIOSK_H_ */
