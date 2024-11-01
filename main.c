/*
 * Gcc_UART.c
 *
 * Created: 2024-10-31 (목) 오전 10:17:05
 * Author : FHT
 */ 
#include "main.h"

#define TEST_GPIO 1
#define TEST_CONSOLE 1
#define TEST_RELAY 1

int main(void)
{
	//==================================================
	// initialize
	//==================================================
	
	#if TEST_CONSOLE
	init_cons(115200L);
	asm("sei");
	#endif
	
	#if TEST_GPIO
	init_gpios();
	#endif
	
	#if TEST_RELAY
	init_relays();
	#endif TEST_RELAY
	
	//==================================================
	// loop
	//==================================================
    while (1)
    {
		#if TEST_CONSOLE
		printf("CONSOLE WORKS!!\n");
		#endif
		
		#if TEST_GPIO
		toggle_gpios();
		#endif
		
		#if TEST_RELAY
		toggle_relays();
		#endif
		_delay_ms(1000);
    }
}