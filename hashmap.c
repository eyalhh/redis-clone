#include "hashmap.h"

int hash(int key, int cap) {
    // as for numeric value
    return key % cap;
}

hashmap_t *init_hashmap() {
    hashmap_t *hashmap = malloc(sizeof(hashmap_t));
    hashmap->cap = INITIAL_SIZE;
    hashmap->len = 0;
    hashmap->arr = calloc(hashmap->cap, sizeof(entry_t *));
    return hashmap;
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

    entry_t *current_entry = (hashmap->arr)[hash(key, hashmap->cap)];

    if (current_entry == NULL) {
        (hashmap->arr)[hash(key, hashmap->cap)] = new_entry(key, value);
        hashmap->len++;
        return 1;
    }

    current_entry->next = new_entry(key, value);
    hashmap->len++;

    return 1;
    
}

char* get_value(hashmap_t *hashmap, int key) {
    entry_t* ent = hashmap->arr[hash(key, hashmap->cap)]; // getting the right entry chain
  
    //going over the chain to look for the right key
    while(TRUE){
      if(ent==NULL) // in case of some wrongdoing
        return NULL; 
      if(ent->key == key)
        return ent->value;
      ent = ent->next;
    }
}

void del_key(hashmap_t *hashmap, int key) {
    entry_t *first_entry = hashmap->arr[hash(key, hashmap->cap)];
    if (first_entry == NULL || first_entry->key == key) {
        hashmap->arr[hash(key, hashmap->cap)] = NULL;
        return;
    }
    while (first_entry != NULL) {
        if (first_entry->next != NULL & first_entry->next->key == key) {
            entry_t *del_entry = first_entry->next;
            first_entry->next = first_entry->next->next;
            free(del_entry);
            return;
        }
    }
}

void print_hashmap(hashmap_t *hashmap) {
    printf("{");
    for (int i = 0; i < hashmap->cap; i++) {
        entry_t *current_entry = hashmap->arr[i];
        while (current_entry != NULL) {
            printf(",%d:%s", current_entry->key, current_entry->value);
            current_entry = current_entry->next;

        }
    }
    printf("}\n");
}

