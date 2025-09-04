#include "aof.h"
#include <stdio.h>

void aof_append(const char *cmd) {
    FILE *fp = fopen(AOF_FILENAME,"a");
    if (!fp) {perror("fopen"); return;}
    fprintf(fp, "%s", cmd);
    fclose(fp);
}

void aof_load(hashmap_t *hashmap) {
    FILE *fp = fopen(AOF_FILENAME,"r");
    if (!fp) return;

    char line[256];
    while (fgets(line, sizeof(line), fp)) {

        char cmd[16], key[128], val[128];
        int n = sscanf(line, "%15s %127s %127s", cmd, key, val);
        if (n == 2 && !strcmp(cmd, "DEL")) {
            del_key(hashmap, key);
        } else if (n == 3 && !strcmp(cmd, "SET")) {
            add_pair(hashmap, key, val);
        }

    }
    fclose(fp);
}
