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

// 父子进程的同步函数
// 当信号发生时，信号处理程序对一个全局变量设1
// 通过测试全局变量来验证信号是否发生

static int flag = 0;
static sigset_t new_mask, old_mask, zero_mask;

void handler(){
    flag = 1;
}

void TELL_WAIT_INIT(){
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);

    sigemptyset(&zero_mask);
    sigemptyset(&new_mask);
    sigaddset(&new_mask, SIGUSR1);
    sigaddset(&new_mask, SIGUSR2);

    sigprocmask(SIG_BLOCK, &new_mask, &old_mask);
}

void TELL_PARENT(pid_t pid){
    kill(pid, SIGUSR2);
}

void WAIT_CHILD(){
    if(flag == 0){
        sigsuspend(&zero_mask);
    }
    flag = 0;
    sigprocmask(SIG_SETMASK, &old_mask, NULL);
}

void TELL_CHILD(pid_t pid){
    kill(pid, SIGUSR1);
}

void WAIT_PARENT(){
    if(flag == 0){
        sigsuspend(&zero_mask);
    }
    flag = 0;
    sigprocmask(SIG_SETMASK, &old_mask, NULL);
}

int main()
{
    return 0;
}