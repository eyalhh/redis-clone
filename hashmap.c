#include "hashmap.h"

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

boolean add_pair(hashmap_t *hashmap, int key, char *value) {
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

boolean get_value(hashmap_t *hashmap, int key) {
    return 1;

}
