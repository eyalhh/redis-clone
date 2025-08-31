#include "hashmap.h"

void test() {

    hashmap_t *hashmap = init_hashmap();
    add_pair(hashmap, 212, "eyal");
    add_pair(hashmap, 304, "roy");
    add_pair(hashmap, 512, "maya");
    print_hashmap(hashmap);
    char *name = get_value(hashmap, 212);
    printf("%s\n", name);
    name = get_value(hashmap, 2000);
    printf("%d\n", (int)name);

}
