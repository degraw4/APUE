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

// 不采取pthread_join或pthread_exit的情况下，主线程终止，整个进程也终止，不管其余线程是否运行完成
// 主线程调用pthread_join，会挂起等待其join的线程结束
// 主线程调用pthread_exit，会挂起等待所有线程结束，然后退出进程

void* thread(void* argv){
    printf("in the thread...\n");
}

int main(int argc, char** argv)
{
    pthread_t tid;
    pthread_create(&tid, NULL, thread, NULL);
    printf("in main...\n");
    //pthread_join(tid, NULL);
    pthread_exit(NULL);

    return 0;
}
