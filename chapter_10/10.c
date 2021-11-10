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

// 实现system函数
// system: a.out -> bash -> cmmand
// 为什么要阻塞SIGCHLD：
    // 为了防止其他程序(main除了会调用system还会使用其他程序)设置了SIGCHLD信号处理函数
    // 如果其他程序设置了SIGCHLD信号处理函数，在waitpid等待子程序的返回前，要去处理SIGCHLD信号处理程序
    // 如果阻塞了该信号，就不会去处理该信号处理程序，防止多余信息在system()中的出现

int system(const char* command){
    if(command == NULL)
        return 1;

    pid_t pid;
    sigset_t child_mask, old_mask;
    
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    sigemptyset(&child_mask);
    sigaddset(&child_mask, SIGCHLD);
    sigprocmask(SIG_BLOCK, &child_mask, &old_mask);

    if((pid == fork()) == 0){
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        sigprocmask(SIG_SETMASK, &old_mask, NULL);
        execl("bin/bash", "sh", "-c", command, (char*)0);
        exit(127);  // if error
    }
    else{
        waitpid(pid, 0, 0); // waitpid并不是靠SIGCHLD工作的
    }
    
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    sigprocmask(SIG_SETMASK, &old_mask, NULL);

}

int main(int argc, char** argv)
{
    

    return 0;
}
