#include <stdio.h>
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
void print_hashmap(hashmap_t *hashmap);
hashmap_t *init_hashmap();
char* get_value(hashmap_t *hashmap, int key);
void del_key(hashmap_t *hashmap, int key);

