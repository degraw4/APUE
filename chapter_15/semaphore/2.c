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

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

// POSIX有名信号量
// gcc -lpthread

int main(int argc, char** argv)
{
    // 创建新信号量
    sem_t* semaphore = sem_open("sem_test_1", O_CREAT, FILE_MODE, 2);
    sem_close(semaphore);

    return 0;
}
