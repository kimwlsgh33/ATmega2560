/*
 * Console.c
 *
 * Created: 2024-10-31 (목) 오전 11:06:02
 *  Author: FHT
 */
#include "Console.h"

#define MAX_CMD_SIZE 128

#define STD_UART_INIT init_uart
#define STD_GETCHAR uart_getchar
#define STD_PUTCHAR uart_putchar

static uint8_t cmd_len = 0;
static char cmd[MAX_CMD_SIZE];

// This must be in the above of the `fdevopen()`
int std_putchar(char c, FILE *stream)
{
  if (c == '\n') {
    while (!STD_PUTCHAR('\r'))
      ;
  }

  while (!STD_PUTCHAR(c))
    ;

  return 0;
}

int std_getchar(FILE *stream) {}

void init_cons(uint32_t baud)
{
  STD_UART_INIT(baud);
  fdevopen(std_putchar, std_getchar);
}

/*
 * @brief: get char from rx buffer
 * @return: len: 성공, 0: 진행중, -1: 실패
 * */
int get_packet_from_cons(char *buf)
{
  char c;

  if (STD_GETCHAR(&c)) {
    if (c == CHAR_CR) {
      strcpy(buf, cmd);
      STD_PUTCHAR(CHAR_CR);
      STD_PUTCHAR(CHAR_LF);

      int len = cmd_len;
      cmd_len = 0;
      return len;
    } else {
      // if the buffer is full, discard the character
      if (cmd_len < MAX_CMD_SIZE / 2 - 1) {
        STD_PUTCHAR(c);
        cmd[cmd_len++] = c;
        cmd[cmd_len] = 0;
      }
      return 0;
    }
  }

  return -1;
}

int proc_command_on_cons(char *cmd, uint8_t len)
{
  if ((len <= 0) || (cmd == 0)) {
    fprintf(stderr, "invalid command on console\n");
    return -1;
  }

  printf("command on console: %s\n", cmd);

  if (strcmp(cmd, "ID?") == 0) {
    printf("RC v1.0");
  } else {
    fprintf(stderr, "unknown command on console\n");
  }

  return 0;
}
