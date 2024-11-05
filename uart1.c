/*
 * uart1.c
 *
 * Created: 2024-11-01 (금) 오전 11:20:28
 *  Author: FHT
 */
#include "uart1.h"
#include "uart.h"
#include "util.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>

static char tx_buff[UART_BUFF_SIZE];
static uint8_t tx_len = 0;
static uint8_t tx_head = 0;
static uint8_t tx_tail = 0;

static char rx_buff[UART_BUFF_SIZE];
static uint8_t rx_len = 0;
static uint8_t rx_head = 0;
static uint8_t rx_tail = 0;

void init_uart1(uint32_t baud)
{
  UCSR1A |= _BV(U2X1);
  UCSR1B |= _BV(RXCIE1) | _BV(TXCIE1) | _BV(RXC1) | _BV(TXC1);
  UCSR1C |= _BV(UCSZ11) | _BV(UCSZ10);
  uint16_t ubrr = (F_CPU / 8 / baud) - 1;
  UBRR1H = (ubrr >> 8);
  UBRR1L = ubrr;
}

/*
 * @brief: get char from rx buffer
 * */
int uart1_getchar(char *c)
{
  cbi(UCSR1B, RXCIE1);

  if (rx_len > 0) {
    *c = rx_buff[rx_head];
    rx_head = (rx_head + 1) % UART_BUFF_SIZE;
    --rx_len;

    sbi(UCSR1B, RXCIE1);
    return SUCCESS;
  }

  sbi(UCSR1B, RXCIE1);
  return -1;
}

/*
 * @brief: put char to tx buffer
 * */
int uart1_putchar(char c)
{
  cbi(UCSR1B, UDRIE1);
  cbi(UCSR1B, TXCIE1);

  if (tx_len < UART_BUFF_SIZE) {
    tx_buff[tx_tail] = c;
    tx_tail = (tx_tail + 1) % UART_BUFF_SIZE;
    ++tx_len;

    sbi(UCSR1B, UDRIE1);
    return SUCCESS;
  }

  sbi(UCSR1B, UDRIE1);
  return -1;
}

ISR(USART1_UDRE_vect)
{
  if (tx_len > 0) {
    uint8_t c = tx_buff[tx_head];
    UDR1 = c;
    tx_head = (tx_head + 1) % UART_BUFF_SIZE;
    --tx_len;
  }

  cbi(UCSR1B, UDRIE1); // HACK: Why should I to do this?
  sbi(UCSR1B, TXCIE1);
}

ISR(USART1_TX_vect)
{
  if (tx_len > 0) {
    uint8_t c = tx_buff[tx_head];
    UDR1 = c;
    tx_head = (tx_head + 1) % UART_BUFF_SIZE;
    --tx_len;
  }
}

ISR(USART1_RX_vect)
{
  char status, data;
  while ((bit_is_clear(UCSR1B, RXC1)))
    ; // wait for complete

  data = UDR1;

  rx_buff[rx_tail] = data;
  rx_tail = (rx_tail + 1) % UART_BUFF_SIZE;
  ++rx_len;
}
