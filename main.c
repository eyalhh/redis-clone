#include "hashmap/hashmap.h"
#include "networking/networking.h"
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
        switch(current) {
            case SET:
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

void server_loop() {
    int srv_fd = init_server();

    while (TRUE) {
        pid_t pid = fork();
        if (pid == 0) {
            int conn_fd = accept_new_client(srv_fd);

            while (TRUE) {
                char *req = get_next_request(conn_fd);
                printf("%s\n", req);
                if (req == NULL) break;
                // do some eval
                send_response(conn_fd, "wow bruh!", 9);
            }

            return;
        }
    }
}

