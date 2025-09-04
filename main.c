#include "hashmap/hashmap.h"
#include "main.h"

int main() {

    main_loop();
    
    return 0;
}

void* ttl(void* args){
    int sec = *((int*) args)
    hashmap_t* hashmap = (hashmap_t*)(args+sizeof(int*))
    char* key = (char*) (args+sizeof(int*) + sizeof(hashmap_t*));

    sleep(sec);
    // lock mutex
    del_key(hashmap, key);
    // free mutex
    return;
 
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
        cmd[strlen(cmd)-1] = '\0';

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
        char *key = args[1];
        char *value = args[2];
        pthread_t t_id;

        switch(current) {
            case SET:
              // checks for flags
              for(int i=3; i<argscount; i++){
                  if(!strcmp(args[i], "--ttl")){
                      // checks whether there is arg after -ttl
                      if(i == argscount){
                          printf("needs more args! --help\n");
                          break;
                      }
                      // TODO: check if the arg is a number
                      argsForThread_t* argsToFunc = (argsForThread_t*)malloc(sizeof(argsForThread_t));
                      argsToFunc->key = key;
                      argsToFunc->hashmap = hashmap;
                      argsToFunc->sec = atoi(args[i+1]);
                      pthread_create(argsToFunc, NULL, ttl, (void*)argsToFunc);
                  }
              }
              add_pair(hashmap, key, value);
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

