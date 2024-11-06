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
#define TEST_KIOSK 1
#define TEST_TIMER 1
#define TEST_PERIPHS 1

#define TOGGLE_LED() tbi(PORTB, PB7)

static uint8_t tid_op = 0;
static uint8_t tid_st = 0;

static int st_interval_sec = 10;

int main(void)
{
  //==================================================
  // initialize
  //==================================================
  asm("sei");

#if TEST_CONSOLE
  init_cons(115200L);
#endif

#if TEST_GPIO
  init_gpios();
#endif

#if TEST_RELAY
  init_relays();
#endif

#if TEST_KIOSK
  init_kiosk(115200L);
#endif

#if TEST_TIMER
  init_timer();
  tid_op = alloc_timer();
  set_timer(tid_op, 0);
  tid_st = alloc_timer();
#endif

#if TEST_PERIPHS
  init_periphs();
#endif

  //==================================================
  // loop
  //==================================================
  while (1) {
#if TEST_TIMER
    // NOTE: send sensor state every 500ms
    if (timer_isfired(tid_op)) {
      set_timer(tid_op, 500);
      TOGGLE_LED();

      send_sensor_state();
    }
#endif
#if TEST_CONSOLE
    printf("CONSOLE WORKS!!\n");
#endif

#if TEST_GPIO
    toggle_gpios();
#endif

#if TEST_RELAY
    toggle_relays();
#endif
    proc_kiosk();
#if TEST_KIOSK
#endif
#if TEST_TIMER
    // NOTE: send periphs state every st_send_interval seconds
    if (timer_isfired(tid_st)) {
      set_timer(tid_st, st_interval_sec * 1000UL);
      send_periphs_state();
    }
#endif
    _delay_ms(1000);
  }
}
