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

// 自旋锁

int main(int argc, char** argv)
{
    pthread_spinlock_t spin;
    pthread_spin_init(&spin, 0);
    pthread_spin_lock(&spin);
    pthread_spin_unlock(&spin);
    pthread_spin_destroy(&spin);

    return 0;
}
