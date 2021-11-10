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

// 接收线程退出时的返回值
// pthread_join: 挂起等待线程退出，并获取其返回值

void* thread1(void* argv){
    printf("thread 1\n");
    return (void*)1;    // 返回 void*
}

void* thread2(void* argv){
    printf("thread 2\n");
    pthread_exit((void*)2); // 返回 void*
}

int main(int argc, char** argv)
{
    pthread_t tid_1, tid_2;
    void* ret;   // void*
    pthread_create(&tid_1, NULL, thread1, NULL);
    pthread_create(&tid_2, NULL, thread2, NULL);
    pthread_join(tid_1, &ret);
    printf("thread %ld return with %ld\n", tid_1, (long)ret);    // 用void**接收
    pthread_join(tid_2, &ret);
    printf("thread %ld return with %ld\n", tid_2, (long)ret);    // 用void**接收

    return 0;
}
