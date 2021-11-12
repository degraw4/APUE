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

// 多线程中的pending分为两种：进程整体的pending和每个线程单独的pending
// 创建新线程时，新线程会继承mask，清空自身的pending
// 但任意时刻，由sigpending获取的线程的pending是该线程本身的pending和进程pending的集合

void* thread(void* argv){
    sigset_t pending;
    sigpending(&pending);
    if(sigismember(&pending, SIGINT)){
        printf("SIGINT is in pending at thread\n");
    }
    else{
        printf("SIGINT is not in pending at thread\n");
    }
}

int main(int argc, char** argv)
{
    sigset_t new_mask, old_mask, pending_mask;
    sigemptyset(&new_mask);
    sigaddset(&new_mask, SIGINT);
    sigprocmask(SIG_BLOCK, &new_mask, &old_mask);

    // make SIGINT pending...
    printf("\nmain thread before sleep\n");
    // sleep是ctrl+C发送的SIGINT是给整个进程，因此即使新线程在此之后创建，其sigpending得到的pending也包含SIGINT
    //sleep(5);

    // pthread_kill发送的SIGINT是给main线程，进程本身没有收到，因此新线程sigpending得到的pending不包含SIGINT
    pthread_kill(pthread_self(), SIGINT);
    pthread_kill(pthread_self(), SIGINT);
    pthread_kill(pthread_self(), SIGINT);
    pthread_kill(pthread_self(), SIGINT);

    printf("\nmain thread after sleep\n");
    sigpending(&pending_mask);
    if(sigismember(&pending_mask, SIGINT)){
        printf("SIGINT is in pending at main\n");
    }
    else{
        printf("SIGINT is not in pending at main\n");
    }

    pthread_t tid;
    pthread_create(&tid, NULL, thread, NULL);
    pthread_join(tid, NULL);

    return 0;
}
