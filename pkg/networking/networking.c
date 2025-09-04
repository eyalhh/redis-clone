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

    if (listen(sockfd, MAX_LISTENERS) < 0) {
        perror("listen");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    return sockfd;
    
}

int accept_new_client(int srv_fd) {

    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    int conn_fd = accept(srv_fd, (struct sockaddr*)&client_addr, &client_len);
    if (conn_fd < 0) {
        perror("accept");
    }

    return conn_fd;
}



char *get_next_request(int conn_fd) {

    char *buffer = malloc(1024);
    unsigned int n = 0;
        
    char c;

    while (n < 1023) {
        int r = read(conn_fd, &c, 1);
        if (r == 1) {
            buffer[n++] = c;
            if (c == '\n') break;
        } else if (r == 0) {
            break;
        } else {
            return NULL;
        }
    }

    buffer[n] = '\0';
    return buffer;

}

void send_response(int conn_fd, char *response, int length) {

    int m = write(conn_fd, response, length);

    if (m < 0) {
        perror("write");
    }

}









