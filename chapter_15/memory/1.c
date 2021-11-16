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
#include <sys/shm.h>

int main(int argc, char** argv)
{
    // 创建新的1024B的共享内存
    int shmID = shmget(IPC_PRIVATE, 1024, IPC_CREAT);
    printf("shared memory ID is %d\n", shmID);
    // 映射到内存地址
    void* addr = shmat(shmID, 0, 0);
    // 解除内存的地址映射，但不删除共享内存
    shmdt(addr);
    // 删除内核中的共享内存
    shmctl(shmID, IPC_RMID, NULL);

    return 0;
}
