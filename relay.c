/*
 * relay.c
 *
 * Created: 2024-11-01 (금) 오전 8:45:56
 *  Author: FHT
 */ 
void init_relays()
{
	DDRC |= _BV(PINC7) | _BV(PINC6) | _BV(PINC5) | _BV(PINC4);
}
void toggle_relays()
{
	PORTC ^= _BV(PINC7) | _BV(PINC6) | _BV(PINC5) | _BV(PINC4);
}