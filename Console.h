/*
 * Console.h
 *
 * Created: 2024-10-31 (목) 오전 11:11:28
 *  Author: FHT
 */

#ifndef CONSOLE_H_
#define CONSOLE_H_
#define INVALID_CMD -1

#include <stdint.h>

void init_cons(uint32_t baud);
int get_packet_from_cons(char *buf);
int proc_command_on_cons(char *cmd, uint8_t len);

#endif /* CONSOLE_H_ */
