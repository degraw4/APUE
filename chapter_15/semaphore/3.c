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

int main(int argc, char** argv)
{
    // 打开现有信号量
    sem_t* semaphore = sem_open("sem_test_1", O_CREAT);
    // close是关闭信号量，保留其值，不销毁
        // 即使对信号量减1，close也不会自动+1
    sem_close(semaphore);
    // unlink是删除该信号量的命名，若无进程打开该信号量，则该信号量被删除，否则等到打开的进程关闭再删除
    sem_unlink("sem_test_1");

    return 0;
}
