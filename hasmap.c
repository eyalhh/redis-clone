#include <stdlib.h>
#include <unistd.h>

#define INITIAL_SIZE 100
#define TRUE 1
#define FALSE 0

typedef int bool;

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

int hash(int key, int cap) {
    return key % cap;
}

void init_hashmap(hashmap_t *hashmap) {
    hashmap->cap = INITIAL_SIZE;
    hashmap->len = 0;
    hashmap->arr = calloc(hashmap->cap, sizeof(entry_t *));
}

entry_t *new_entry(int key, char *value) {
    entry_t *new = malloc(sizeof(entry_t));
    new->key = key;
    new->value = value;
    return new;
}

bool add_pair(hashmap_t *hashmap, int key, char *value) {
    if (hashmap->len == hashmap->cap) {
        hashmap->cap *= 2;
        hashmap->arr = calloc(hashmap->cap, sizeof(entry_t *));
    }

    entry_t *current_value = (hashmap->arr)[hash(key, hashmap->cap)];

    if (current_value == NULL) {
        (hashmap->arr)[hash(key, hashmap->cap)] = new_entry(key, value);
        return 1;
    }

    current_value->next = new_entry(key, value);

    return 1;
    
}

bool get_value(hashmap_t *hashmap, int key) {

}
