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
#include <errno.h>

// mutex的robust属性
// 该属性用在多线程共享mutex时，也可以用在多进程共享mutex
// 当占有锁的线程退出时，robust属性保证其余线程仍然lock成功，但是返回EOWNERDEAD，此时需要在解锁前调用pthread_mutex_consistent保持mutex的一致性

static pthread_mutex_t mutex;

void* thread1(void* argv){
    printf("\n[thread 1] Setting lock...\n");
    pthread_mutex_lock(&mutex);
    printf("[thread 1] Locked. Now exiting without unlocking.\n");
    pthread_exit(NULL);
}

void* thread2(void* argv){
    printf("\n[thread 2] Setting lock...\n");
    pthread_mutex_lock(&mutex);
    printf("[thread 2] Locked. Now exiting without unlocking.\n");
    pthread_exit(NULL);
}

void* thread3(void* argv){
    int i = 5;
    while(i--){
        int s = pthread_mutex_lock(&mutex);
        if(s == EOWNERDEAD){
            printf("\n[main thread] pthread_mutex_lock() returned EOWNERDEAD\n");
            printf("[main thread] Now make the mutex consistent\n");
            pthread_mutex_consistent(&mutex);
            printf("[main thread] Mutex is now consistent; unlocking\n");
            pthread_mutex_unlock(&mutex);
        }
        else if(s < 0){
            printf("\n[main thread] pthread_mutex_lock() unexpectedly failed\n");
            pthread_exit(0);
        }
        else{
            printf("\n[main thread] pthread_mutex_lock success.\n");
            printf("do somthing.... \n");
            pthread_mutex_unlock(&mutex);
        }
        sleep(1);
    }
}

int main(int argc, char** argv)
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    //pthread_mutexattr_setrobust(&attr, PTHREAD_MUTEX_ROBUST);
    pthread_mutexattr_setrobust(&attr, PTHREAD_MUTEX_STALLED);
    pthread_mutex_init(&mutex, &attr);

    pthread_t tid;
    pthread_create(&tid, NULL, thread1, NULL);
    sleep(1);
    pthread_create(&tid, NULL, thread2, NULL);
    sleep(1);
    pthread_create(&tid, NULL, thread3, NULL);
    sleep(1);

    int i = 5;
    while(i--){
        int s = pthread_mutex_lock(&mutex);
        if(s == EOWNERDEAD){
            printf("\n[main thread] pthread_mutex_lock() returned EOWNERDEAD\n");
            printf("[main thread] Now make the mutex consistent\n");
            pthread_mutex_consistent(&mutex);
            printf("[main thread] Mutex is now consistent; unlocking\n");
            pthread_mutex_unlock(&mutex);
        }
        else if(s < 0){
            printf("\n[main thread] pthread_mutex_lock() unexpectedly failed\n");
            pthread_exit(0);
        }
        else{
            printf("\n[main thread] pthread_mutex_lock success.\n");
            printf("do somthing.... \n");
            pthread_mutex_unlock(&mutex);
        }
        sleep(1);
    }

    return 0;
}
