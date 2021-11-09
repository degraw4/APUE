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

// 当某个信号被屏蔽且pending，若使用sigprocmask解除屏蔽
// 进程先处理该信号，然后进行sigprocmask的返回

void handler(){
    printf("catch\n");
    signal(SIGINT, SIG_DFL);
}

int main(int argc, char** argv)
{
    sigset_t new_mask, old_mask, pending_mask;
    signal(SIGINT, handler);

    sigemptyset(&new_mask);
    sigaddset(&new_mask, SIGINT);
    sigprocmask(SIG_BLOCK, &new_mask, &old_mask);
    sleep(5);

    sigpending(&pending_mask);
    if(sigismember(&pending_mask, SIGINT)){
        printf("\nSIGINT is pending\n");
    }

    sigprocmask(SIG_SETMASK, &old_mask, NULL);
    printf("SIGINT unblock\n");
    sleep(5);

    return 0;
}
