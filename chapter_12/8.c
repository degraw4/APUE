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

// fork后，子进程自动继承父进程各种锁的状态
// 子进程只有一个线程，是父进程中执行fork的线程的副本
// 即使父进程中一些锁被非fork的线程锁住，子进程的唯一线程仍继承该锁和锁的状态，因此子进程lock时可能会阻塞，但是可以unlock

pthread_mutex_t mutex;

void* thread(void* argv){
    printf("in the thread of parent process...\n");
    printf("lock the mutex and exit\n");
    pthread_mutex_lock(&mutex);
}

int main(int argc, char** argv)
{
    pthread_t tid;
    pid_t pid;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&tid, NULL, thread, NULL);
    pthread_join(tid, NULL);
    printf("ready to fork\n");
    if((pid = fork()) == 0){
        // printf("child process about to lock mutex\n");
        // pthread_mutex_lock(&mutex);
        // printf("child process lock over\n");
        // pthread_mutex_unlock(&mutex);

        printf("child process about to unlock mutex\n");
        pthread_mutex_unlock(&mutex);
        printf("child process unlock over\n");
    }
    else{
        waitpid(pid, 0, 0);
    }

    return 0;
}
