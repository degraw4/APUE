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

// pipe重定向

int main(int argc, char** argv)
{
    int fd[2];
    fd[0] = dup(0);
    fd[1] = dup(0);
    printf("fd[0] is %d\n", fd[0]);
    printf("fd[1] is %d\n", fd[1]);
    pipe(fd);
    printf("fd[0] is %d\n", fd[0]);
    printf("fd[1] is %d\n", fd[1]);

    while(1);

    return 0;
}
