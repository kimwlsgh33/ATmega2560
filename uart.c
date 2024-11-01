/*
 * uart.c
 *
 * Created: 2024-10-31 (목) 오전 11:15:40
 *  Author: FHT
 */ 
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>

#define UART_BUFF_SIZE	128

#define sbi(sfr, bit) (sfr |= _BV(bit))
#define cbi(sfr, bit) (sfr &= ~(_BV(bit)))

static uint8_t tx_buff[UART_BUFF_SIZE];
static uint8_t tx_len = 0;
static uint8_t tx_head = 0;
static uint8_t tx_tail = 0;

void init_uart(uint32_t baud)
{
	UCSR0A |= _BV(U2X0);
	UCSR0B |= _BV(RXCIE0) | _BV(TXCIE0) | _BV(RXC0) | _BV(TXC0);
	UCSR0C |= _BV(UCSZ01) | _BV(UCSZ00);
	uint16_t ubrr = (F_CPU / 8 / baud) - 1;
	UBRR0H = (ubrr >> 8);
	UBRR0L = ubrr;
}


int uart_putchar(uint8_t c)
{
	cbi(UCSR0B, UDRIE0);
	cbi(UCSR0B, TXCIE0);
	if (tx_len < UART_BUFF_SIZE) {
		tx_buff[tx_tail] = c;
		tx_tail = (tx_tail + 1) % UART_BUFF_SIZE;
		++tx_len;
		
		sbi(UCSR0B, UDRIE0);
		return 1; // success
	}
	
	sbi(UCSR0B, UDRIE0);
	return 0; // fail
}

ISR(USART0_UDRE_vect)
{
	if(tx_len > 0) {
		uint8_t c = tx_buff[tx_head];
		UDR0 = c;
		tx_head = (tx_head + 1) % UART_BUFF_SIZE;
		--tx_len;
	}
	
	cbi(UCSR0B, UDRIE0); // HACK: Why should I to do this?
	sbi(UCSR0B, TXCIE0);
}

ISR(USART0_TX_vect)
{
	if(tx_len > 0) {
		uint8_t c = tx_buff[tx_head];
		UDR0 = c;
		tx_head = (tx_head + 1) % UART_BUFF_SIZE;
		--tx_len;
	}
}