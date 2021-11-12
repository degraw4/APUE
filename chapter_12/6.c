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

// 多线程的信号屏蔽和处理
// 新线程会继承之前线程的mask
// 多线程中，一个线程屏蔽了某信号，其余线程(包括该线程本身)恢复信号默认处理或者设置处理函数，都会撤销该线程的信号屏蔽

void handler(int signal){
    printf("catch SIGINT\n");
}

void* thread(void* argv){
    sigset_t new, old;
    sigemptyset(&new);
    sigaddset(&new, SIGINT);
    pthread_sigmask(SIG_BLOCK, &new, &old);
    if(sigismember(&old, SIGUSR1)){
        printf("SIGUSR1 is in mask\n");
    }
    else{
        printf("SIGUSR1 is not in mask\n");
    }
    while(1);
}

int main(int argc, char** argv)
{
    pthread_t tid;
    signal(SIGINT, handler);
    sigset_t new_mask, old_mask;
    sigemptyset(&new_mask);
    sigaddset(&new_mask, SIGUSR1);  // 测试新线程继承mask
    sigprocmask(SIG_BLOCK, &new_mask, &old_mask);
    pthread_create(&tid, NULL, thread, NULL);
    while(1);

    return 0;
}
