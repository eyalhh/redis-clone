#include "../hashmap/hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AOF_FILENAME "aof.txt"

void aof_append(const char *command);
void aof_load(hashmap_t *);
