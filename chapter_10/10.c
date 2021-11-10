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
// 要对调用者(a.out中的父进程)忽略SIGITN和SIGQUIT， 阻塞SIGCHLD

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
        waitpid(pid, 0, 0);
    }
    
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    sigprocmask(SIG_SETMASK, &old_mask, NULL);

}

int main(int argc, char** argv)
{
    

    return 0;
}
