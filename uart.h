/*
 * uart.h
 *
 * Created: 2024-10-31 (목) 오전 11:15:30
 *  Author: FHT
 */ 


#ifndef UART_H_
#define UART_H_

void init_uart(uint32_t baud);
int uart_putchar(uint8_t c);


#endif /* UART_H_ */