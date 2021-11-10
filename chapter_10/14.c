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

// sigsuspend作用思考
// sigsuspend效果：使进程挂起，直至某信号发生并处理
// 关于sigsuspend如何保护代码临界区：
    // 在临界区中要屏蔽某些信号，退出临界区要解除屏蔽
    // 被屏蔽的信号也需要被处理，若在临界区发生了，则退出临界区解除阻塞后自然会处理
    // 若在临界区没有发生，则不知何时会发生，此处可以使用pause挂起进程等待其发生
    // 将上述功能合并，演化出sigsuspend函数
// 关于sigsuspend等待信号处理程序设置全局变量
    // 见此例，其应用可以作为父子进程通信

static int flag = 0;
void handler(){
    printf("\ncatch\n");
    flag = 1;
}

int main(int argc, char** argv)
{
    signal(SIGINT, handler);
    sigset_t new_mask, old_mask, empty_mask;
    sigemptyset(&new_mask);
    sigemptyset(&empty_mask);
    sigaddset(&new_mask, SIGINT);
    // 先屏蔽该信号，以免意外调用信号处理程序
    sigprocmask(SIG_BLOCK, &new_mask, &old_mask);
    // 需要该信号时，使用sigsuspend临时解除屏蔽，并且pause等待全局变量的设置
    if(!flag)
        sigsuspend(&empty_mask);
    flag = 0;
    // 不再需要该信号设置全局变量后，解除对于该信号的屏蔽和handler
    signal(SIGINT, SIG_DFL);
    sigprocmask(SIG_SETMASK, &old_mask, NULL);

    return 0;
}
