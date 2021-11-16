#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <errno.h>
#include <semaphore.h>

// POSIX无名信号量，只存在于内存中
// 适用于单个进程使用，若在多个进程中使用，要保证sem参数指向多个进程的共享内存区域

int main(int argc, char** argv)
{
    sem_t semaphore;
    sem_init(&semaphore, 0, 2);
    sem_wait(&semaphore);
    sem_post(&semaphore);
    sem_destroy(&semaphore);

    return 0;
}
