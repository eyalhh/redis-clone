
#include <stdlib.h>
#include <unistd.h>

#define INITIAL_SIZE 100
#define TRUE 1
#define FALSE 0

typedef int boolean;

typedef struct entry_s{
    int key;
    char *value;
    struct entry_s *next;
} entry_t;

typedef struct {
    int len;
    int cap;
    entry_t **arr;
} hashmap_t;

boolean add_pair(hashmap_t *hashmap, int key, char *value);
boolean get_value(hashmap_t *hashmap, int key);

