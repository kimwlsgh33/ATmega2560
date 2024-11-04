/*
 * util.h
 *
 * Created: 2024-11-01 (금) 오후 16:03:31
 *  Author: FHT
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <avr/sfr_defs.h>

#define sbi(sfr, bit) (sfr |= _BV(bit))
#define cbi(sfr, bit) (sfr &= ~(_BV(bit)))

#endif /* UART1_H_ */
