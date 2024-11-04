/*
 * kiosk.c
 *
 * Created: 2024-11-01 (금) 오후 13:07:32
 *  Author: FHT
 */
#include "kiosk.h"

// indicate that the kiosk is connected to the uart1
#define KIOSK_GETCHAR uart1_getchar
#define KIOSK_PUTCHAR uart1_putchar

static uint8_t tx_len = 0;
static char tx_buf[UART_BUFF_SIZE];
static uint8_t rx_len = 0;
static char rx_buff[UART_BUFF_SIZE];

/*
 * @brief
 * */
void proc_kiosk()
{
  if ((tx_len = get_packet_from_kiosk(tx_buf))) {
    proc_command_on_kiosk(tx_buf, tx_len);
  }

  if ((tx_len = get_packet_from_cons(tx_buf))) {
    proc_command_on_cons(tx_buf, tx_len);
  }
}

/*
 * @brief 키오스크에서 받은 문자열을 처리한다.
 * @param buf 처리할 문자열을 담을 버퍼
 * @return 처리한 문자열의 길이
 */
int get_packet_from_kiosk(char *buf)
{
  char c;

  if (KIOSK_GETCHAR(&c)) {
    // separate the packet into the commands by '\r'
    if (c == CHAR_CR) {
      int len = rx_len;
      rx_buff[rx_len] = 0;
      memcpy(buf, rx_buff, len);
      rx_len = 0;
      return len;
    } else {
      rx_buff[rx_len] = c;
    }

    return 0;
  }

  return -1;
}

int proc_command_on_kiosk(char *cmd, uint8_t len)
{
  if ((len <= 0) || (cmd == NULL)) {
    fprintf(stderr, "invalid command on kiosk\n");
    return -1;
  }

  printf("command on kiosk: %s\n", cmd);

  if (strcmp(cmd, "ID?") == 0) {
    send_to_kiosk("RC v1.0");
  }

  return 0;
}

static int send_to_kiosk(char *buf)
{
  int len = strlen(buf);
  int i;

  for (i = 0; i < len; ++i) {
    KIOSK_PUTCHAR(buf[i]);
  }

  KIOSK_PUTCHAR(CHAR_CR);
  KIOSK_PUTCHAR(CHAR_LF);

  return 1;
}
