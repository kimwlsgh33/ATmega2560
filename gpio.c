/*
 * gpio.c
 *
 * Created: 2024-10-31 (목) 오전 11:32:52
 *  Author: FHT
 */ 

void init_gpios()
{
	DDRF |= _BV(PINF7) | _BV(PINF6) | _BV(PINF5) | _BV(PINF4) | _BV(PINF3) | _BV(PINF2) | _BV(PINF1) | _BV(PINF0);
}

void toggle_gpios()
{
	PORTF ^= _BV(PINF7) | _BV(PINF6) | _BV(PINF5) | _BV(PINF4) | _BV(PINF3) | _BV(PINF2) | _BV(PINF1) | _BV(PINF0);
}