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

// 使用sigsuspend实现sleep，避免非局部跳转和pause阻塞

void handler(){
    // nothing to do, just wake up the sigsuspend...
}

int Sleep(int second){
    signal(SIGALRM, handler);
    sigset_t new_mask, old_mask, suspend_mask;
    sigemptyset(&new_mask);
    sigaddset(&new_mask, SIGALRM);
    // 在sleep之前先阻塞SIGALRM
    sigprocmask(SIG_BLOCK, &new_mask, &old_mask);
    alarm(second);
    // 在sigsuspend中临时解除对SIGALRM的阻塞
    suspend_mask = old_mask;
    sigdelset(&suspend_mask, SIGALRM);
    // 等待alarm
    sigsuspend(&suspend_mask);
    int unslept = alarm(0);
    // 恢复环境
    signal(SIGALRM, SIG_DFL);
    sigprocmask(SIG_SETMASK, &old_mask, NULL);
    return unslept;
}

int main(int argc, char** argv)
{
    int ret = Sleep(5);
    printf("%d\n", ret);

    return 0;
}
