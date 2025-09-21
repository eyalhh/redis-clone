
typedef struct {
    int conn_fd; 
} RedisClient_t;

RedisClient_t *NewRedisClient();
char *add_pair(RedisClient_t *rc, char *key, char *value);
char *del_key(RedisClient_t *rc, char *key);
char *get_value(RedisClient_t *rc, char *key);
void closeClient(RedisClient_t *rc);

