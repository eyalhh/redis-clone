#include "hashmap/hashmap.h"
#include "main.h"

int main() {

    main_loop();
    
    return 0;
}


void free_args(char **args, int argCount) {
    for (int i = 0; i < argCount; i++) {
        free(args[i]);
    }
    free(args);
}

void main_loop(){
    hashmap_t *hashmap = init_hashmap();

    command current; 
    char cmd[MAX_CMD_SIZE];
    char *token;
    char **args = malloc(MAX_ARGS_COUNT * sizeof(char*));
    int argCount;

    while(TRUE){
        argCount = 0;

        printf(">> ");
        fgets(cmd, sizeof(cmd), stdin);

        token = strtok(cmd, " ");

        while(token != NULL){
            if(argCount>=MAX_ARGS_COUNT){
                printf("max args count execeded\n");
                break;
            }
            args[argCount] = token;
            token = strtok(NULL, " ");
            argCount++;
        }

        if(!strcmp("GET", args[0])) {
            current = GET;
            if (argCount < 2) {
                printf("needs more args.\n");
                continue;
            }
        } else if(!strcmp("SET", args[0])) {
            current = SET;
            if (argCount < 3) {
                printf("needs more args.\n");
                continue;
            }
        } else if(!strcmp("DEL", args[0])) {
            current = DEL;
            if (argCount < 2) {
                printf("needs more args.\n");
                continue;
            }
        } else if(!strcmp("EXIT", args[0])) {
            current = EXIT;
        } else {
            printf("command not availabe\n");
            continue;
        }



        // call each fucntion 
        int key = atoi(args[1]);
        char *value = args[2];
        char *copy_value = calloc(strlen(value), sizeof(char));
        switch(current) {
            case SET:
            strncpy(copy_value, value, strlen(value));
            add_pair(hashmap, key, copy_value);
            printf("the pair was added\n");
            print_hashmap(hashmap);
            break;
            case GET:
            print_hashmap(hashmap);
            printf("the value is: %s\n", get_value(hashmap, key));
            break;
            case DEL:
            del_key(hashmap, key);
            printf("the key was deleted.\n");
            print_hashmap(hashmap);
            break;
            case EXIT:
            printf("exiting...\n");
            return;

        }

    }

}

