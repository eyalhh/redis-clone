#include <string.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct flag_s {
    char *flag;
    void *val;
} flag_t;

typedef struct parsed_s {
    flag_t *flags;
    int size;
} parsed_t;

parsed_t *parse(char *);


