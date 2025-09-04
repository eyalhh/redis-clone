#include "main.h"

int main() {

    printf("Welcome to our redis clone! Do you want to use our cli version or web server ?, the web server's default port will be 6004\n (for cli press c, for web server press w)\n");
    char c;
    scanf(" %c", &c);

    while (c != 'c' && c != 'w') {
        printf("invalid answer.\n");
        printf("press w or c:\n");
        scanf(" %c", &c);
    }

    if (c == 'c') {
        main_loop();
        return 0;
    }

    server_loop();
    
    return 0;
}


void free_args(char **args, int argCount) {
    for (int i = 0; i < argCount; i++) {
        free(args[i]);
    }
    free(args);
}

void main_loop(){
    getchar();
    hashmap_t *hashmap = init_hashmap();
    char cmd[MAX_CMD_SIZE];



    while(TRUE){

        printf(">> ");
        fgets(cmd, sizeof(cmd), stdin);
        cmd[strlen(cmd)-1] = 0;

        char *response = parse_request(hashmap, cmd);
        printf("%s", response);
    }


}

char *parse_request(hashmap_t *hashmap, char *request) {

    command current; 
    char *token;
    char **args = malloc(MAX_ARGS_COUNT * sizeof(char*));
    int argCount;
    char *response = calloc(1024, sizeof(char));


    argCount = 0;


    token = strtok(request, " ");


    while(token != NULL){
        if(argCount>=MAX_ARGS_COUNT){
            strcpy(response, "max arguments exceeded\n");
            return response;
        }
        args[argCount] = token;
        token = strtok(NULL, " ");
        argCount++;
    }

    if(!strcmp("GET", args[0])) {
        current = GET;
        if (argCount < 2) {
            strcpy(response, "needs more args.\n");
            return response;
        }
    } else if(!strcmp("SET", args[0])) {
        current = SET;
        if (argCount < 3) {
            strcpy(response, "needs more args.\n");
            return response;
        }
    } else if(!strcmp("DEL", args[0])) {
        current = DEL;
        if (argCount < 2) {
            strcpy(response, "needs more args.\n");
            return response;
        }
    } else if(!strcmp("EXIT", args[0])) {
        current = EXIT;
    } else {
        strcpy(response, "needs more args.\n");
        return response;
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
            snprintf(response, 1023, "the value is: %s\n", get_value(hashmap, key));
            break;
        case DEL:
            del_key(hashmap, key);
            strcpy(response, "the key was deleted.\n");
            break;
        case EXIT:
            strcpy(response, "exiting...\n");
            break;

    }

    return response;

}

void server_loop() {

    hashmap_t *hashmap = init_hashmap();
    int srv_fd = init_server();
    printf("server listening on port 60004\n");

    while (TRUE) {
        int conn_fd = accept_new_client(srv_fd);

        while (TRUE) {
            char *req = get_next_request(conn_fd);
            if (req == NULL) break;
            printf("req incoming: %s\n", req);
            char *res = parse_request(hashmap, req);
            // do some eval
            send_response(conn_fd, res, strlen(res));
        }
    }
}

