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

// pending和mask的区别
// 处理某信号时，该信号自动被隐式的设为mask， 但是没有设为pending
// 推测在处理该信号时，若再来该信号，则设为pending
sigset_t new_mask, old_mask, pending_mask;

void handler(){
    // in the signal handler process
    sigprocmask(0, NULL, &new_mask);    // 得到当前的mask
    sigpending(&pending_mask);          // 得到当前的pending
    if(sigismember(&pending_mask, SIGINT)){
        printf("SIGINT is in pending\n");
    }
    else{
        printf("SIGINT is not in pending\n");
    }
    if(sigismember(&new_mask, SIGINT)){
        printf("SIGINT is in mask\n");
    }
    else{
        printf("SIGINT is not in mask\n");
    }

}

int main(int argc, char** argv)
{
    sigprocmask(0, NULL, &new_mask);    // 得到当前的mask
    sigpending(&pending_mask);          // 得到当前的pending
    if(sigismember(&pending_mask, SIGINT)){
        printf("SIGINT is in pending\n");
    }
    else{
        printf("SIGINT is not in pending\n");
    }
    if(sigismember(&new_mask, SIGINT)){
        printf("SIGINT is in mask\n");
    }
    else{
        printf("SIGINT is not in mask\n");
    }

    signal(SIGINT, handler);
    sleep(5);

    sigprocmask(0, NULL, &new_mask);    // 得到当前的mask
    sigpending(&pending_mask);          // 得到当前的pending
    if(sigismember(&pending_mask, SIGINT)){
        printf("SIGINT is in pending\n");
    }
    else{
        printf("SIGINT is not in pending\n");
    }
    if(sigismember(&new_mask, SIGINT)){
        printf("SIGINT is in mask\n");
    }
    else{
        printf("SIGINT is not in mask\n");
    }

    return 0;
}
