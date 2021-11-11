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

// 读写锁

int main(int argc, char** argv)
{
    pthread_rwlock_t rwlock;
    pthread_rwlock_init(&rwlock, NULL);
    pthread_rwlock_rdlock(&rwlock);
    pthread_rwlock_unlock(&rwlock);
    pthread_rwlock_wrlock(&rwlock);
    pthread_rwlock_unlock(&rwlock);
    pthread_rwlock_destroy(&rwlock);

    return 0;
}
