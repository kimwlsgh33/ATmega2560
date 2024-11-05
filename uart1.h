/*
 * uart1.h
 *
 * Created: 2024-11-01 (금) 오전 11:18:45
 *  Author: FHT
 */

#ifndef UART1_H_
#define UART1_H_

#include <stdint.h>

void init_uart1(uint32_t baud);
int uart1_putchar(char c);
int uart1_getchar(char *c);

#endif /* UART1_H_ */
