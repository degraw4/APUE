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

// pthread_cleanup_push & pthread_cleanup_pop
// 两个函数要在同一作用域内成对使用，否则编译不通过
// push的清理函数clean执行的顺序与push顺序相反
// clean执行的条件如下：
    // 线程调用pthread_exit
    // 线程响应pthread_cancel请求 -> 线程如何响应cancel请求?
    // 线程非0参数调用pthread_cleanup_pop
    // P.S. 线程return不会像pthread_exit调用clean



void clean(void * argv){
    printf("in the clean fucntion of %s\n", (char*)argv);
}

void* thread1(void* argv){
    printf("thread 1 start\n");
    pthread_cleanup_push(clean, (void*)("thread 1 first clean"));
    pthread_cleanup_push(clean, (void*)("thread 1 second clean"));
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    return (void*)(0);
}

void* thread2(void* argv){
    printf("thread 2 start\n");
    pthread_cleanup_push(clean, (void*)("thread 2 first clean"));
    pthread_cleanup_push(clean, (void*)("thread 2 second clean"));
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
    return (void*)(0);
}

void* thread3(void* argv){
    printf("thread 3 start\n");
    pthread_cleanup_push(clean, (void*)("thread 3 first clean"));
    pthread_cleanup_push(clean, (void*)("thread 3 second clean"));
    pthread_exit((void*)0);
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
}

void* thread4(void* argv){
    printf("thread 4 start\n");
    pthread_cleanup_push(clean, (void*)("thread 4 first clean"));
    pthread_cleanup_push(clean, (void*)("thread 4 second clean"));
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    pthread_exit((void*)0);
}

void* thread5(void* argv){
    printf("thread 5 start\n");
    pthread_cleanup_push(clean, (void*)("thread 5 first clean"));
    pthread_cleanup_push(clean, (void*)("thread 5 second clean"));
    return (void*)(0);
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
}

// 线程如何响应cancel请求?  
void* thread6(void* argv){
    printf("thread 6 start\n");
    pthread_cleanup_push(clean, (void*)("thread 6 first clean"));
    pthread_cleanup_push(clean, (void*)("thread 6 second clean"));
    while(1);
    pthread_cleanup_pop(0); // just for compile...
    pthread_cleanup_pop(0);
}

int main(int argc, char** argv)
{
    pthread_t tid1, tid2, tid3, tid4, tid5, tid6;
    pthread_create(&tid1, NULL, thread1, NULL);
    pthread_join(tid1, NULL);
    
    pthread_create(&tid2, NULL, thread2, NULL);
    pthread_join(tid2, NULL);
    
    pthread_create(&tid3, NULL, thread3, NULL);
    pthread_join(tid3, NULL);
    
    pthread_create(&tid4, NULL, thread4, NULL);
    pthread_join(tid4, NULL);
    
    pthread_create(&tid5, NULL, thread5, NULL);
    pthread_join(tid5, NULL);

    pthread_create(&tid6, NULL, thread6, NULL);
    sleep(1);
    pthread_cancel(tid6);

    return 0;
}
