/*
 * Console.c
 *
 * Created: 2024-10-31 (목) 오전 11:06:02
 *  Author: FHT
 */ 
#include <stdio.h>
#include "uart.h"

#define STD_UART_INIT	init_uart
#define STD_PUTCHAR		uart_putchar

// This must be in the above of the `fdevopen()`
int std_putchar(char c, FILE* stream)
{
	if (c == '\n') {
		while(!STD_PUTCHAR('\r'));
	}
	
	while(!STD_PUTCHAR(c));
	
	return 0;
}

int std_getchar(FILE* stream){}


void init_cons(uint32_t baud)
{
	STD_UART_INIT(baud);
	fdevopen(std_putchar, std_getchar);
}