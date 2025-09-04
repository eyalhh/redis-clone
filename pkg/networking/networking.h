#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LISTENERS 10
#define PORT 6004

int init_server();
int accept_new_client(int);
void send_response(int, char *, int);
char *get_next_request(int);
