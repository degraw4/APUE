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

// pipe
// 一般只用于父子进程的单向通信，也可双向，但是同步处理不好就会被自己读取

int main(int argc, char** argv)
{
    int fd[2];
    pid_t pid;
    char buffer[1024] = "";
    pipe(fd);
    if(fork() > 0){
        write(fd[1], "pipe test 1\n", 12);
        sleep(1);
        read(fd[0], buffer, 20);
        printf("parent read: %s", buffer);
    }
    else{
        read(fd[0], buffer, 20);
        write(fd[1], "pipe test 2\n", 12);
        printf("child read: %s", buffer);
    }

    return 0;
}
