#include "hashmap.h"
#include "main.h"

int main_loop();

int main() {

   main_loop();
   return 0;
}

int main_loop(){
  enum func funcType; 
  char cmd[MAX_CMD_SIZE];
  char* token;
  char** args = malloc(MAX_ARGS_COUNT * sizeof(char*));
  int cmdCount;

  while(TRUE){
    cmdCount = 0;

    printf(">> ");
    fgets(cmd, sizeof(cmd), stdin);
    
    token = strtok(cmd, " ");

    while(token != NULL){
      if(cmdCount>=MAX_ARGS_COUNT){
        printf("max args count execeded\n");
        break;
      }
      args[cmdCount] = token;
      token = strtok(NULL, " ");
      cmdCount++;
    }

    if(strcmp("GET", args[0])) 
      funcType = GET;
    if(strcmp("SET", args[0])) 
      funcType = SET;
    if(strcmp("DEL", args[0])) 
      funcType = DEL;
    if(strcmp("EXIT", args[0])) 
      funcType = EXIT;

    // call each fucntion 

  }
  


  // free args 
  return 0;
}

