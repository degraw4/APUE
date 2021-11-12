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

// pthread_once
// once flag只能是全局变量或者静态变量，因为要所有线程共享
pthread_once_t flag = PTHREAD_ONCE_INIT;

// pthread_once调用的函数
void init(void){
    printf("This function will be called only once...\n");
    printf("And at the first time\n");
}

void* thread1(void* argv){
    pthread_once(&flag, init);
}

void* thread2(void* argv){
    pthread_once(&flag, init);
}

int main(int argc, char** argv)
{
    pthread_t tid;
    pthread_create(&tid, NULL ,thread1, NULL);
    pthread_create(&tid, NULL ,thread2, NULL);
    
    pthread_once(&flag, init);
    pthread_exit(0);

    return 0;
}
