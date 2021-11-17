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
    // 解除该进程对共享内存的地址映射，但不删除共享内存数据和其ID
    shmdt(addr);
    // 删除内核中的共享内存
        // 当最后一个使用共享内存的进程结束，共享内存的存储段才删除
        // 但是会立刻删除该共享内存的ID，所以任何进程不能使用该ID和shmat创建新的映射
    shmctl(shmID, IPC_RMID, NULL);

    return 0;
}
