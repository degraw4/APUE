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

// 验证close后不会改变semaphore的值

int main(int argc, char** argv)
{
    sem_t* semaphore = sem_open("sem_test_1", O_CREAT, FILE_MODE, 2);
    int value = 0;

    sem_getvalue(semaphore, &value);
    printf("init value is %d\n", value);

    sem_wait(semaphore);
    sem_getvalue(semaphore, &value);
    printf("after wait value is %d\n", value);
    
    sem_close(semaphore);
    
    semaphore = sem_open("sem_test_1", O_CREAT);
    sem_getvalue(semaphore, &value);
    printf("after close and open value is %d\n", value);

    sem_post(semaphore);
    sem_getvalue(semaphore, &value);
    printf("after post value is %d\n", value);

    sem_unlink("sem_test_1");

    return 0;
}
