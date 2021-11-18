#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <errno.h>

// socketpair创建UNIX域套接字的全双工管道

int main(int argc, char* argv[])
{
    int fd[2];
    socketpair(AF_UNIX, SOCK_STREAM, 0, fd);
    char buffer[1024] = "";
    if(fork() > 0){ // parent
        close(fd[1]);
        write(fd[0], "parent send 1", 14);
        read(fd[0], buffer, 1024);
        printf("parent read 1: %s\n", buffer);
        waitpid(-1, 0, 0);
    }
    else{           // child
        close(fd[0]);
        write(fd[1], "child send 1", 13);
        read(fd[1], buffer, 1024);
        printf("child read 1: %s\n", buffer);
    }

    return 0;
}
