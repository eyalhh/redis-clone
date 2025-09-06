#include "../aof/aof.h"

hash_t hash(unsigned char *key, int cap) { // djb2 hash 
    hash_t hash = 5381;
    int c;
    while ((c = *key++)) 
        hash = ((hash << 5) + hash) + c;
    return hash % cap;

}

hashmap_t *init_hashmap() {
    hashmap_t *hashmap = calloc(1 ,sizeof(hashmap_t));
    hashmap->cap = INITIAL_SIZE;
    hashmap->len = 0;
    hashmap->arr = calloc(hashmap->cap, sizeof(entry_t *));
    return hashmap;
}

char *copy_string(char *str) {
    int len = strlen(str) + 1;
    char *result = malloc(len);
    strncpy(result, str, len);
    return result;
}


entry_t *new_entry(char *key, char *value) {
    entry_t *new = malloc(sizeof(entry_t));
    char *copy_key = copy_string(key);
    char *copy_value = copy_string(value);

    new->key = copy_key;
    new->value = copy_value;
    new->next = NULL;
    return new;
}

boolean add_pair(hashmap_t *hashmap, char *key, char *value) {

    if (hashmap->len == hashmap->cap) {
        hashmap->cap *= 2;
        entry_t* new_arr = calloc(hashmap->cap, sizeof(entry_t *));


        for(int i=0; i<hashmap->len; i++)
            new_arr[hash((unsigned char*)(hashmap->arr[i])->key, hashmap->cap)] = (hashmap->arr)[i];
        
        free(hashmap->arr);
        hashmap->arr = new_arr;

    }

    entry_t *current_entry = (hashmap->arr)[hash((unsigned char*)key, hashmap->cap)];

    if (current_entry == NULL) {
        (hashmap->arr)[hash((unsigned char*)key, hashmap->cap)] = new_entry(key, value);
        hashmap->len++;
        return TRUE;
    }

    while(current_entry->next!=NULL){
        if(!strcmp(current_entry->key, key)){
            current_entry->value = copy_string(value);
            hashmap->len++;
            return TRUE;
        }
    }
    current_entry->next = new_entry(key, value);
    hashmap->len++;
    return TRUE;
    
}

char* get_value(hashmap_t *hashmap, char *key) {
    entry_t* ent = hashmap->arr[hash((unsigned char*)key, hashmap->cap)]; // getting the right entry chain
  
    //going over the chain to look for the right key
    while(TRUE){
      if(ent==NULL) // in case of some wrongdoing
        return NULL; 
      if(!strcmp(ent->key, key))
        return ent->value;
      ent = ent->next;
    }
}

void del_key(hashmap_t *hashmap, char *key) {

    entry_t *first_entry = hashmap->arr[hash((unsigned char*)key, hashmap->cap)];
    if (first_entry == NULL) {
        return;
    }
    if (!strcmp(first_entry->key, key)) {
        hashmap->arr[hash((unsigned char*)key, hashmap->cap)] = first_entry->next;
        free(first_entry);
        (hashmap->len)--;
        return;
    }
    while (first_entry != NULL) {
        if (first_entry->next != NULL && !strcmp(first_entry->next->key, key)) {
            entry_t *del_entry = first_entry->next;
            first_entry->next = first_entry->next->next;
            free(del_entry);
            (hashmap->len)--;
            return;
        }
    }
}

void print_hashmap(hashmap_t *hashmap) {
    int count = 0;
    printf("{");
    for (int i = 0; i < hashmap->cap; i++) {
        entry_t *current_entry = hashmap->arr[i];
        while (current_entry != NULL) {
            int len = strlen(current_entry->value);
            if (current_entry->value[len-1] == '\n') current_entry->value[len-1] = '\0';
            if (count == 0) {
                printf("%s:%s", current_entry->key, current_entry->value);
            } else {
                printf(",%s:%s", current_entry->key, current_entry->value);
            }
            current_entry = current_entry->next;
            count++;

        }
    }
    printf("}\n");
}

