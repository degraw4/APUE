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
    // 删除内核中的共享内存
    int ret1 = shmctl(819205, IPC_RMID, NULL);
    int ret2 = shmctl(851974, IPC_RMID, NULL);
    printf("ret1 is %d\n", ret1);
    printf("ret2 is %d\n", ret2);

    return 0;
}
