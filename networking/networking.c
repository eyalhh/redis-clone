#include "networking.h"


int init_server() {

    int sockfd;
    struct sockaddr_in addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET; // using ipv4
    addr.sin_port = htons(PORT); // converting port number go big endian
    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // converting addr string to ipv4 number

    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    return sockfd;
    
}

int handle_func(int sockfd, char *(handler)(char *, char *)) {
    return 0;
}

