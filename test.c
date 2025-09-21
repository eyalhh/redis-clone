#include "pkg/hashmap/hashmap.h"

int main() {
    hashmap_t *hashmap = init_hashmap();
    char *key;
    char *value;
    key = "EYAL";
    value = "FOO";
    add_pair(hashmap, key, value);
    key = "ENFKL";
    value = "FOO";
    add_pair(hashmap, key, value);
    key = "EYABRUHL";
    value = "FOO";
    add_pair(hashmap, key, value);
    key = "RUHL";
    value = "FOO";
    add_pair(hashmap, key, value);
}
