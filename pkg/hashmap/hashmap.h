#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define INITIAL_SIZE 2
#define TRUE 1
#define FALSE 0

typedef int boolean;
typedef unsigned long hash_t;

typedef struct entry_s{
    char *key;
    char *value;
    struct entry_s *next;
} entry_t;

typedef struct {
    int len;
    int cap;
    entry_t **arr;
} hashmap_t;

boolean add_pair(hashmap_t *hashmap, char *key, char *value);
void print_hashmap(hashmap_t *hashmap);
hashmap_t *init_hashmap(int cap);
char* get_value(hashmap_t *hashmap, char *key);
void del_key(hashmap_t *hashmap, char *key);
int exists(hashmap_t *hashmap, char *key);
