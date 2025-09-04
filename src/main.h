#include <string.h>
#include <pthread.h>
#include "../pkg/networking/networking.h"
#include "../pkg/aof/aof.h"

#define MAX_ARGS_COUNT 10
#define MAX_CMD_SIZE 1024

typedef enum func{
  GET, // 0
  SET, // 1
  DEL, // 2
  EXIT // 3
} command;

typedef struct argsForThread_s{
    int sec;
    hashmap_t* hashmap;
    char* key;
} argsForThread_t;

void free_args(char **args, int argCount);
void main_loop();
void server_loop();
char *parse_request(hashmap_t *, char *);
