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

// 条件变量

void* thread1(void* argv){
    pthread_mutex_lock(&mutex);
    // do something...
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&cond);
}

void* thread2(void* argv){
    pthread_mutex_lock(&mutex);
    while(!flag)
        pthread_cond_wait(&cond, &mutex);
    // do something...
    pthread_mutex_unlock(&)
}

int main(int argc, char** argv)
{
    pthread_mutex_t mutex;
    pthread_cont_t cond;
    int flag = 0;   // some flags...
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, thread1, NULL);
    pthread_create(&tid2, NULL, thread2, NULL);
    pthread_exit(0);

    return 0;
}
