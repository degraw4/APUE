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

// pthread_atfork来保证在fork后父子进程的锁都是unlock的
    // prepare：lock所有锁(阻塞则等待)  ->      在调用fork后，创建新进程前调用
    // parent：unlock父进程的所有锁     ->      在父进程上下文的fork返回前调用
    // child：unlock子进程的所有锁      ->      在子进程上下文的fork返回前调用

// 作用：
    // 对于父进程，由于prepare加锁，parent解锁，因此fork前后锁状态不变
    // 对于子进程，fork得到的锁都是锁上的，状态已知，且通过child都解锁了，因此fork返回后得到的都是unlock的锁

// 多个atfork，prepare的顺序和atfork相反，parent和child与atfork相同

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void* thread(void* argv){
    printf("a thread \n");
    pthread_mutex_lock(&mutex1);
    pthread_mutex_lock(&mutex2);
    // block the fork...
    printf("thread lock over...\n");
    sleep(5);
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);
    printf("thread unlock over...\n");
}

void prepare(void){
    printf("prepare locks...\n");
    pthread_mutex_lock(&mutex1);
    pthread_mutex_lock(&mutex2);
}

void parent(void){
    printf("parent unlocks...\n");
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);
}

void child(void){
    printf("child unlocks...\n");
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);
}

int main(int argc, char** argv)
{
    pthread_t tid;
    pthread_atfork(prepare, parent, child);
    pthread_create(&tid, NULL, thread, NULL);
    //sleep(1);
    printf("parent about to fork...\n");
    if(fork() == 0){
        printf("child fork over\n");
    }
    else{
        printf("parent fork over\n");
    }

    return 0;
}
