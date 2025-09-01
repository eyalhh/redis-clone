#include <string.h>

#define MAX_ARGS_COUNT 10
#define MAX_CMD_SIZE 1024

typedef enum func{
  GET, // 0
  SET, // 1
  DEL, // 2
  EXIT // 3
} command;

void free_args(char **args, int argCount);
void main_loop();
