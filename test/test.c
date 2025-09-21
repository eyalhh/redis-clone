#include "../pkg/redis/redis.h"
#include <stdio.h>

int main() {

    RedisClient_t *rc = NewRedisClient();

    char *ans = add_pair(rc, "eyal", "foo");
    if (ans == NULL) {
        printf("error\n");
        return 1;
    }

    printf("%s", ans);
    return 0;




}
