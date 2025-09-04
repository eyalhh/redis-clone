#include "../pkg/hashmap/hashmap.h"

int main() {

    hashmap_t *hashmap = init_hashmap();
    add_pair(hashmap, "foo", "eyal");
    add_pair(hashmap, "bar", "roy");
    add_pair(hashmap, "baz", "maya");
    print_hashmap(hashmap);
    char *name = get_value(hashmap, "bar");
    printf("%s\n", name);
    name = get_value(hashmap, "omg");
    printf("%d\n",name == NULL);

    return 0;

}
