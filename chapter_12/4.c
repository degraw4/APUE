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

// pthread_key和线程私有数据
// 使用barrier防止malloc过快退出导致地址一致

pthread_key_t key;
pthread_barrier_t barrier;

void func(void* argv){
    // 每个线程对于key对应的私有数据的释放函数/析构函数
    // 该函数的参数自动设为key对应的数据的地址
    // 对于malloc的线程私有数据，该函数可直接设为free
    // 线程正常退出，析构函数调用
    // 线程exit或者abort，析构函数不调用
    printf("key data deconstructed\n");
}

void func_malloc(void* argv){
    printf("key data deconstructed\n");
    free(argv);
}

void* thread1(void* argv){
    int data = 10;
    pthread_setspecific(key, &data);
    int* addr = pthread_getspecific(key);
    printf("thread 1 key addr is %p\n", addr);
    // 测试线程例程正常退出
}

void* thread2(void* argv){
    int data = 10;
    pthread_setspecific(key, &data);
    int* addr = pthread_getspecific(key);
    printf("thread 2 key addr is %p\n", addr);
    // 测试pthread_exit
    pthread_exit(0);
}

void* thread3(void* argv){
    int data = 10;
    pthread_setspecific(key, &data);
    int* addr = pthread_getspecific(key);
    printf("thread 3 key addr is %p\n", addr);
    // 测试exit or abort
    abort();
    //exit(0);
}

void* thread1_malloc(void* argv){
    int* data = (int*)malloc(sizeof(int));
    pthread_setspecific(key, data);
    int* addr = pthread_getspecific(key);
    printf("thread 1 key addr is %p\n", addr);
    pthread_barrier_wait(&barrier);
    // 测试线程例程正常退出
}

void* thread2_malloc(void* argv){
    int* data = (int*)malloc(sizeof(int));
    pthread_setspecific(key, data);
    int* addr = pthread_getspecific(key);
    printf("thread 2 key addr is %p\n", addr);
    pthread_barrier_wait(&barrier);
    // 测试pthread_exit
    pthread_exit(0);
}

void* thread3_malloc(void* argv){
    int* data = (int*)malloc(sizeof(int));
    pthread_setspecific(key, data);
    int* addr = pthread_getspecific(key);
    printf("thread 3 key addr is %p\n", addr);
    pthread_barrier_wait(&barrier);
    // 测试exit or abort
    //abort();
    //exit(0);
}

int main(int argc, char** argv)
{
    pthread_barrier_init(&barrier, NULL, 4);
    //pthread_key_create(&key, func);
    pthread_key_create(&key, func_malloc);
    pthread_t tid;
    pthread_create(&tid, NULL, thread1_malloc, NULL);
    pthread_create(&tid, NULL, thread2_malloc, NULL);
    pthread_create(&tid, NULL, thread3_malloc, NULL);

    pthread_barrier_wait(&barrier);
    sleep(1);

    // key的delete不会调用数据的析构函数
    pthread_key_delete(key);

    return 0;
}
