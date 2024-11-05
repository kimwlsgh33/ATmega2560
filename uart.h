/*
 * uart.h
 *
 * Created: 2024-10-31 (목) 오전 11:15:30
 *  Author: FHT
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>

#define UART_BUFF_SIZE 128

void init_uart(uint32_t baud);
int uart_getchar(char *c);
int uart_putchar(char c);

#endif /* UART_H_ */
