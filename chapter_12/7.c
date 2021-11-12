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

// 在一个线程中调用signal或者sigaction，会改变所有线程中的信号处理函数，而不是仅仅是该线程的信号处理函数
// sigwait：
    // signum显示为wait到的信号，可以用作信号处理函数的case
    // 监听被阻塞(BLOCK, 此处可以理解为屏蔽)的信号，如果所监听的信号产生了，由于BLOCK，会自动变为pending
    // 如果要确保线程sigwait收到该信号，所有线程必须block这个信号，因为如果自己不block就没有未决状态(阻塞状态)信号，别的线程不block就有可能当信号过来时被其他的线程处理掉
    // sigwait结束后，将该信号从整个进程的pending中移除，但是若某个线程自身pending中仍有该信号，则该线程的pending不会被移除
    // sigwait并不改变信号的mask

// sigwait具体实现：
    // 取消等待信号的屏蔽(解除阻塞/BLOCK)，然后等待信号到来 or 从现有的pending上捕捉该信号
    // 从解除阻塞到wait信号是原子操作
    // wait结束后，恢复信号的屏蔽字(BLOCK)

void* thread(void* argv){
    int signum;
    sigset_t pending, wait;
    sigemptyset(&wait);
    sigaddset(&wait, SIGINT);
    sigpending(&pending);
    if(sigismember(&pending, SIGINT)){
        printf("SIGINT is in pending at thread\n");
    }
    else{
        printf("SIGINT is not in pending at thread\n");
    }
    sigwait(&wait, &signum);
    if(signum == SIGINT){
        printf("SIGINT wait over\n");
    }
    sigpending(&pending);
    if(sigismember(&pending, SIGINT)){
        printf("After wait, SIGINT is in pending at thread\n");
    }
    else{
        printf("After wait, SIGINT is not in pending at thread\n");
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
    //sleep(3);

    // pthread_kill发送的SIGINT是给main线程，进程本身没有收到，因此新线程sigpending得到的pending不包含SIGINT
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

    sigpending(&pending_mask);
    if(sigismember(&pending_mask, SIGINT)){
        printf("After wait, SIGINT is in pending at main\n");
    }
    else{
        printf("After wait, SIGINT is not in pending at main\n");
    }

    return 0;
}