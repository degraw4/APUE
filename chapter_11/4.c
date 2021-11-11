#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <pthread.h>

// 多个互斥锁

int main(int argc, char** argv)
{
    pthread_mutex_t hashlock, itemlock;
    pthread_mutex_init(&hashlock, NULL);
    pthread_mutex_init(&itemlock, NULL);

    pthread_mutex_lock(&hashlock);
    // do something ablout hashtable...
    pthread_mutex_lock(&itemlock);
    pthread_mutex_unlock(&hashlock);
    // do something ablout item...
    pthread_mutex_unlock(&itemlock);

    return 0;
}
