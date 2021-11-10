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

void handler(){
    printf("catch\n");
}

int main(int argc, char** argv)
{
    if(fork() == 0){
        // 子进程
        if(fork() == 0){
            // 子子进程
            exit(0); // SIGCHLD
        }
        else{
            while(1);
        }
    }
    else{
        // 父进程
        signal(SIGCHLD, handler);
        waitpid(-1, 0, 0);
    }

    return 0;
}
