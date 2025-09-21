#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "redis.h"

RedisClient_t *NewRedisClient() {
    int sockfd;
    struct sockaddr_in server_addr;
    const char *server_ip = "127.0.0.1";
    int server_port = 6004;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        return NULL;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        close(sockfd);
        return NULL;
    }
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        close(sockfd);
        return NULL;
    }

    RedisClient_t *res = calloc(1, sizeof(RedisClient_t));
    res->conn_fd = sockfd;
    return res;
}

char *add_pair(RedisClient_t *rc, char *key, char *value) {
    int sockfd = rc->conn_fd;
    
    char write_buf[1024];
    memset(write_buf, 0, 1024);
    snprintf(write_buf, 1024, "SET %s %s\n", key, value);
    send(sockfd, write_buf, strlen(write_buf), 0);

    char *read_buf = calloc(1024, sizeof(char));
    ssize_t n = read(sockfd, read_buf, 1023);
    if (n > 0) {
        read_buf[n] = '\0';
        return read_buf;
    }

    return NULL;

}

char *del_key(RedisClient_t *rc, char *key) {

    int sockfd = rc->conn_fd;
    
    char write_buf[1024];
    memset(write_buf, 0, 1024);
    snprintf(write_buf, 1024, "DEL %s\n", key);
    send(sockfd, write_buf, strlen(write_buf), 0);

    char *read_buf = calloc(1024, sizeof(char));
    ssize_t n = read(sockfd, read_buf, 1023);
    if (n > 0) {
        read_buf[n] = '\0';
        return read_buf;
    }

    return NULL;


}

char *get_value(RedisClient_t *rc, char *key) {

    int sockfd = rc->conn_fd;
    
    char write_buf[1024];
    memset(write_buf, 0, 1024);
    snprintf(write_buf, 1024, "GET %s\n", key);
    send(sockfd, write_buf, strlen(write_buf), 0);

    char *read_buf = calloc(1024, sizeof(char));
    ssize_t n = read(sockfd, read_buf, 1023);
    if (n > 0) {
        read_buf[n] = '\0';
        return read_buf;
    }

    return NULL;

}

void closeClient(RedisClient_t *rc) {
    close(rc->conn_fd);
    free(rc);
}
